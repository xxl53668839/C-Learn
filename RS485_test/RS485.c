#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    char sendData[] = "Hello RS485!";
    char receiveBuffer[256];
    DWORD bytesWritten, bytesRead;

    // 開啟 COM Port
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
    dcbSerialParams.BaudRate = CBR_9600;
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

    // 發送資料
    if (!WriteFile(hSerial, sendData, sizeof(sendData) - 1, &bytesWritten, NULL)) {
        printf("Error writing to COM port!\n");
        CloseHandle(hSerial);
        return 1;
    }
    printf("Sent %d bytes: %s\n", bytesWritten, sendData);

    // 接收回覆
    if (!ReadFile(hSerial, receiveBuffer, sizeof(receiveBuffer) - 1, &bytesRead, NULL)) {
        printf("Error reading from COM port!\n");
        CloseHandle(hSerial);
        return 1;
    }

    if (bytesRead > 0) {
        receiveBuffer[bytesRead] = '\0'; // 加入字串結束符號
        printf("Received %d bytes: %s\n", bytesRead, receiveBuffer);
    } else {
        printf("No data received.\n");
    }

    // 關閉 COM Port
    CloseHandle(hSerial);

    return 0;
}