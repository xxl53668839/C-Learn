#include <stdio.h>
#include <windows.h>
#include <string.h>

// CRC16 計算函式
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
    char sendData[256];
    char receiveBuffer[256];
    DWORD bytesWritten, bytesRead;

    // 開啟 COM Port (同之前的範例)
    hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening COM port!\n");
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

    // 取得使用者輸入
    printf("Enter data to send: ");
    fgets(sendData, sizeof(sendData), stdin);
    sendData[strcspn(sendData, "\n")] = '\0'; // 移除換行符號

    // 計算 CRC16
    unsigned short crc = calculateCRC16((unsigned char *)sendData, strlen(sendData));

    // 將 CRC 校驗碼附加到資料尾端 (低字節在前)
    sendData[strlen(sendData)] = (unsigned char)(crc & 0xFF);
    sendData[strlen(sendData) + 1] = (unsigned char)((crc >> 8) & 0xFF);

    // 發送資料 (包含 CRC 校驗碼)
    if (!WriteFile(hSerial, sendData, strlen(sendData) + 2, &bytesWritten, NULL)) {
        printf("Error writing to COM port!\n");
        CloseHandle(hSerial);
        return 1;
    }
    printf("Sent %d bytes: %s (CRC: 0x%04X)\n", bytesWritten, sendData, crc);

    // 接收回覆 (同之前的範例)
    if (!ReadFile(hSerial, receiveBuffer, sizeof(receiveBuffer) - 1, &bytesRead, NULL)) {
        printf("Error reading from COM port!\n");
        CloseHandle(hSerial);
        return 1;
    }

    if (bytesRead > 0) {
        receiveBuffer[bytesRead] = '\0';
        printf("Received %d bytes: %s\n", bytesRead, receiveBuffer);
    } else {
        printf("No data received.\n");
    }

    // 關閉 COM Port (同之前的範例)
    CloseHandle(hSerial);

    return 0;
}