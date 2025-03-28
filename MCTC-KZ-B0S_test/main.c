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

// 發送和接收資料函式
int rs485_send_receive(HANDLE hSerial, const char *inputBuffer, unsigned char *receiveBuffer) {
    unsigned char sendData[256];
    DWORD bytesWritten, bytesRead;

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
        printf("Err! 從COM連接埠中寫入錯誤!\n");
        return 1;
    }

    // 顯示發送的資料 (16 進制格式)
    printf("發送資料: ");
    for (int i = 0; i < sendLength + 2; i++) {
        printf("%02X ", sendData[i]);
    }
    printf("(CRC: 0x%04X)\n", crc);

    // 清除 COM Port 緩衝區和錯誤
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    ClearCommError(hSerial, NULL, NULL);

    // 接收回覆
    if (!ReadFile(hSerial, receiveBuffer, sizeof(receiveBuffer) , &bytesRead, NULL)) {
        printf("Err!從 COM 連接埠讀取錯誤!\n");
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
        printf("Err!沒有收到回覆資料!\n");
    }

    return 0;
}

int main() {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};
    unsigned char receiveBuffer[256];
    char inputBuffer[256];
    int choice, subChoice;

    // 開啟 COM Port
    hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening COM port!\n");
        return 1;
    }

    // 設定 COM Port 參數
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

    // 設定逾時
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

    // 菜單迴圈
    while (1) {
        // 顯示主菜單
        printf("\nMCTC-KZ-B0S 測試工具\n");
        printf("1. 標準測試模式\n");
        printf("2. 自定義測試模式\n");
        printf("0. 退出程式\n");
        printf("請選擇功能: ");

        // 取得使用者選擇
        scanf("%d", &choice);
        getchar(); // 清除換行符號

        // 根據選擇執行相應功能
        switch (choice) {
            case 1:
                // 標準測試子菜單
                while (1) {
                    printf("\n標準測試模式\n");
                    printf("1. 系統狀態 (01 03 9C 41 00 01)\n");
                    printf("2. 門狀態 (01 03 9C 43 00 01)\n");
                    printf("3. 當前樓層 (01 03 9C 45 00 01)\n");
                    printf("4. 開關門指令 (01 06 9C 56 HH HH)\n");
                    printf("5. 登記內叫 (01 06 9C 99 HH HH)\n");
                    printf("6. AGV控制模式\n");
                    printf("0. 回上一頁\n");
                    printf("請選擇測試項目: ");
                    scanf("%d", &subChoice);
                    getchar();

                    switch (subChoice) {
                        case 1:
                            // 系統狀態測試
                            printf("\n執行系統狀態測試...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 41 00 01", receiveBuffer) != 0) {
                                printf("測試失敗。\n");
                            }
                            break;
                        case 2:
                            // 門狀態測試
                            printf("\n執行門狀態測試...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 43 00 01", receiveBuffer) != 0) {
                                printf("測試失敗。\n");
                            }
                            break;
                        case 3:
                            // 當前樓層測試
                            printf("\n執行當前樓層測試...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 45 00 01", receiveBuffer) != 0) {
                                printf("測試失敗。\n");
                            }
                            break;
                        case 4:
                            // 開關門指令子菜單
                            while (1) {
                                printf("\n開關門指令\n");
                                printf("1. 前門開門 (01 06 9C 56 00 03)\n");
                                printf("2. 前門關門 (01 06 9C 56 00 04)\n");
                                printf("3. 後門開門 (01 06 9C 56 00 05)\n");
                                printf("4. 後門關門 (01 06 9C 56 00 06)\n");
                                printf("0. 回上一頁\n");
                                printf("請選擇指令: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // 前門開門
                                        printf("\n執行前門開門指令...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 03", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 2:
                                        // 前門關門
                                        printf("\n執行前門關門指令...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 04", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 3:
                                        // 後門開門
                                        printf("\n執行後門開門指令...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 05", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 4:
                                        // 後門關門
                                        printf("\n執行後門關門指令...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 06", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 0:
                                        // 回上一頁
                                        break;
                                    default:
                                        printf("無效的選擇，請重新輸入。\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // 跳出子菜單迴圈
                                }
                            }
                            break;

                            case 5:
                            // 內叫指令子菜單
                            while (1) {
                                printf("\n內叫指令\n");
                                printf("1. 第1層 (01 06 9C 99 00 01)\n");
                                printf("2. 第3層 (01 06 9C 99 00 03)\n");
                                printf("3. 第5層 (01 06 9C 99 00 05)\n");
                                printf("4. 第7層 (01 06 9C 99 00 07)\n");
                                printf("5. 第9層 (01 06 9C 99 00 09)\n");
                                printf("0. 回上一頁\n");
                                printf("請選擇指令: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // 內叫1C
                                        printf("\n執行內叫指令:第1層...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 01", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 2:
                                        // 內叫3C
                                        printf("\n執行內叫指令:第3層...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 03", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 3:
                                        // 內叫5C
                                        printf("\n執行內叫指令:第5層...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 05", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 4:
                                        // 內叫7C
                                        printf("\n執行內叫指令:第7層...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 07", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 5:
                                        //內叫9C
                                        printf("\n執行內叫指令:第9層...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 09", receiveBuffer) != 0) {
                                            printf("執行命令失敗。\n");
                                        }
                                        break;
                                    case 0:
                                        // 回上一頁
                                        break;
                                    default:
                                        printf("無效的選擇，請重新輸入。\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // 跳出子菜單迴圈
                                }
                            }
                            break;

                            case 6:
                            // AGV指令子菜單
                            while (1) {
                                printf("\nAGV指令\n");
                                printf("1. 進入AGV狀態 (01 06 9C A4 00 01)\n");
                                printf("2. 退出AGV狀態 (01 06 9C A4 00 00)\n");
                                printf("3. AGV狀態確認 (01 03 9C A5 00 00)\n");
                                printf("0. 回上一頁\n");
                                printf("請選擇指令: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // 進入AGV狀態
                                        printf("\n請求進入AGV狀態...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C A4 00 01", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 2:
                                        // 退出AGV狀態
                                        printf("\n請求退出AGV狀態...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C A4 00 00", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 3:
                                        // AGV狀態確認
                                        printf("\n執行AGV狀態確認...\n");
                                        if (rs485_send_receive(hSerial, "01 03 9C A5 00 01", receiveBuffer) != 0) {
                                            printf("指令執行失敗。\n");
                                        }
                                        break;
                                    case 0:
                                        // 回上一頁
                                        break;
                                    default:
                                        printf("無效的選擇，請重新輸入。\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // 跳出子菜單迴圈
                                }
                            }
                            break;
                    
                        case 0:
                            // 回上一頁
                            break;
                        default:
                            printf("無效的選擇，請重新輸入。\n");
                            break;
                    }
                    if (subChoice == 0) {
                        break; // 跳出子菜單迴圈
                    }
                }
                break;
            case 2:
                // 自定義 16 進制輸入模式
                printf("請輸入通訊指令 (16進制字串): ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

                // 發送和接收資料
                if (rs485_send_receive(hSerial, inputBuffer, receiveBuffer) != 0) {
                    printf("測試失敗。\n");
                }
                break;
            case 0:
                // 退出程式
                CloseHandle(hSerial);
                printf("程式結束\n");
                return 0;
            default:
                printf("無效的選擇，請重新輸入。\n");
                break;
        }
    }

    return 0;
}