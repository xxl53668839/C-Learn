#include <stdio.h>
#include <windows.h>
#include <string.h>

// CRC16 計算函式 (同之前的範例)
unsigned short calculateCRC16(const unsigned char *data, int length) {
    unsigned short crc = 0xFFFF;
    for (int i = 0; i < length; i++) {
        crc ^= data[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    unsigned char sendData[256];
    char inputBuffer[256];
    unsigned char receiveBuffer[256];
    DWORD bytesWritten, bytesRead;

    // 開啟 COM Port (同之前的範例)
    hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Err! COM連接埠開啟失敗!\n");
        return 1;
    }

    // 設定 COM Port 參數 (同之前的範例)
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting COM state!\n");
        CloseHandle(hSerial);
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_38400;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting COM state!\n");
        CloseHandle(hSerial);
        return 1;
    }

    // 設定逾時 (同之前的範例)
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting timeouts!\n");
        CloseHandle(hSerial);
        return 1;
    }

    // 迴圈直到使用者輸入 0
    while (1) {
        // 取得使用者輸入 (16 進制字串)
        printf("請輸入16進制的資料字串 (輸入 0 可退出程式!): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        // 檢查是否輸入 0
        if (strcmp(inputBuffer, "0") == 0) {
            break; // 結束迴圈
        }

        // 將 16 進制字串轉換為位元組陣列
        int inputLength = strlen(inputBuffer);
        int sendLength = 0;
        for (int i = 0; i < inputLength; i += 3) {
            sscanf(&inputBuffer[i], "%02X ", &sendData[sendLength]);
            sendLength++;
        }

        // 計算 CRC16
        unsigned short crc = calculateCRC16(sendData, sendLength);

        // 將 CRC 校驗碼附加到資料尾端 (低字節在前)
        sendData[sendLength] = (unsigned char)(crc & 0xFF);
        sendData[sendLength + 1] = (unsigned char)((crc >> 8) & 0xFF);

        // 發送資料 (包含 CRC 校驗碼)
        if (!WriteFile(hSerial, sendData, sendLength + 2, &bytesWritten, NULL)) {
            printf("Err!COM通訊埠寫入錯誤!\n");
            CloseHandle(hSerial);
            return 1;
        }

        // 顯示發送的資料 (16 進制格式)
        printf("發送資料: ");
        for (int i = 0; i < sendLength + 2; i++) {
            printf("%02X ", sendData[i]);
        }
        printf("(CRC: 0x%04X)\n", crc);

        // 接收回覆
        if (!ReadFile(hSerial, receiveBuffer, sizeof(receiveBuffer) - 1, &bytesRead, NULL)) {
            printf("Err! COM通訊埠沒有回覆!\n");
            CloseHandle(hSerial);
            return 1;
        }

        // 顯示接收到的資料 (16 進制格式)
        if (bytesRead > 0) {
            printf("回覆資料: ");
            for (int i = 0; i < bytesRead; i++) {
                printf("%02X ", receiveBuffer[i]);
            }
            printf("\n");
        } else {
            printf("No data received.\n");
        }
    }

    // 關閉 COM Port
    CloseHandle(hSerial);

    return 0;
}