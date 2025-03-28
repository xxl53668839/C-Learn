#include <stdio.h>
#include <windows.h>
#include <string.h>

// CRC16 �p��禡
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

// �o�e�M������ƨ禡
int rs485_send_receive(HANDLE hSerial, const char *inputBuffer, unsigned char *receiveBuffer) {
    unsigned char sendData[256];
    DWORD bytesWritten, bytesRead;

    // �N 16 �i��r���ഫ���줸�հ}�C
    int inputLength = strlen(inputBuffer);
    int sendLength = 0;
    for (int i = 0; i < inputLength; i += 3) {
        sscanf(&inputBuffer[i], "%02X ", &sendData[sendLength]);
        sendLength++;
    }

    // �p�� CRC16
    unsigned short crc = calculateCRC16(sendData, sendLength);

    // �N CRC ����X���[���Ƨ��� (�C�r�`�b�e)
    sendData[sendLength] = (unsigned char)(crc & 0xFF);
    sendData[sendLength + 1] = (unsigned char)((crc >> 8) & 0xFF);

    // �o�e��� (�]�t CRC ����X)
    if (!WriteFile(hSerial, sendData, sendLength + 2, &bytesWritten, NULL)) {
        printf("Err! �qCOM�s���𤤼g�J���~!\n");
        return 1;
    }

    // ��ܵo�e����� (16 �i��榡)
    printf("�o�e���: ");
    for (int i = 0; i < sendLength + 2; i++) {
        printf("%02X ", sendData[i]);
    }
    printf("(CRC: 0x%04X)\n", crc);

    // �M�� COM Port �w�İϩM���~
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    ClearCommError(hSerial, NULL, NULL);

    // �����^��
    if (!ReadFile(hSerial, receiveBuffer, sizeof(receiveBuffer) , &bytesRead, NULL)) {
        printf("Err!�q COM �s����Ū�����~!\n");
        return 1;
    }

    // ��ܱ����쪺��� (16 �i��榡)
    if (bytesRead > 0) {
        printf("�^�и��: ");
        for (int i = 0; i < bytesRead; i++) {
            printf("%02X ", receiveBuffer[i]);
        }
        printf("\n");
    } else {
        printf("Err!�S������^�и��!\n");
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

    // �}�� COM Port
    hSerial = CreateFile("\\\\.\\COM3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening COM port!\n");
        return 1;
    }

    // �]�w COM Port �Ѽ�
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

    // �]�w�O��
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

    // ���j��
    while (1) {
        // ��ܥD���
        printf("\nMCTC-KZ-B0S ���դu��\n");
        printf("1. �зǴ��ռҦ�\n");
        printf("2. �۩w�q���ռҦ�\n");
        printf("0. �h�X�{��\n");
        printf("��J1~2��ܼҦ�: ");

        // ���o�ϥΪ̿��
        scanf("%d", &choice);
        getchar(); // �M������Ÿ�

        // �ھڿ�ܰ�������\��
        switch (choice) {
            case 1:
                // �зǴ��դl���
                while (1) {
                    printf("\n�зǴ��ռҦ�\n");
                    printf("1. �t�Ϊ��A \n");
                    printf("2. �����A \n");
                    printf("3. ��e�Ӽh \n");
                    printf("4. �}�������O \n");
                    printf("5. �n�O���s \n");
                    printf("6. AGV����Ҧ�\n");
                    printf("0. �^�W�@��\n");
                    printf("�п�ܴ��ն���: ");
                    scanf("%d", &subChoice);
                    getchar();

                    switch (subChoice) {
                        case 1:
                            // �t�Ϊ��A����
                            printf("\n����t�Ϊ��A����...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 41 00 01", receiveBuffer) != 0) {
                                printf("���ե��ѡC\n");
                            }
                            break;
                        case 2:
                            // �����A����
                            printf("\n��������A����...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 43 00 01", receiveBuffer) != 0) {
                                printf("���ե��ѡC\n");
                            }
                            break;
                        case 3:
                            // ��e�Ӽh����
                            printf("\n�����e�Ӽh����...\n");
                            if (rs485_send_receive(hSerial, "01 03 9C 45 00 01", receiveBuffer) != 0) {
                                printf("���ե��ѡC\n");
                            }
                            break;
                        case 4:
                            // �}�������O�l���
                            while (1) {
                                printf("\n�}�������O\n");
                                printf("1. �e���}�� \n");
                                printf("2. �e������ \n");
                                printf("3. ����}�� \n");
                                printf("4. ������� \n");
                                printf("0. �^�W�@��\n");
                                printf("�п�ܫ��O: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // �e���}��
                                        printf("\n����e���}�����O...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 03", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 2:
                                        // �e������
                                        printf("\n����e���������O...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 04", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 3:
                                        // ����}��
                                        printf("\n�������}�����O...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 05", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 4:
                                        // �������
                                        printf("\n�������������O...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 56 00 06", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 0:
                                        // �^�W�@��
                                        break;
                                    default:
                                        printf("�L�Ī���ܡA�Э��s��J�C\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // ���X�l���j��
                                }
                            }
                            break;

                            case 5:
                            // ���s���O�l���
                            while (1) {
                                printf("\n���s���O\n");
                                printf("1. ��1�h \n");
                                printf("2. ��3�h \n");
                                printf("3. ��5�h \n");
                                printf("4. ��7�h \n");
                                printf("5. ��9�h \n");
                                printf("0. �^�W�@��\n");
                                printf("�п�ܫ��O: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // ���s1C
                                        printf("\n���椺�s���O:��1�h...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 01", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 2:
                                        // ���s3C
                                        printf("\n���椺�s���O:��3�h...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 03", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 3:
                                        // ���s5C
                                        printf("\n���椺�s���O:��5�h...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 05", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 4:
                                        // ���s7C
                                        printf("\n���椺�s���O:��7�h...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 07", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 5:
                                        //���s9C
                                        printf("\n���椺�s���O:��9�h...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C 99 00 09", receiveBuffer) != 0) {
                                            printf("����R�O���ѡC\n");
                                        }
                                        break;
                                    case 0:
                                        // �^�W�@��
                                        break;
                                    default:
                                        printf("�L�Ī���ܡA�Э��s��J�C\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // ���X�l���j��
                                }
                            }
                            break;

                            case 6:
                            // AGV���O�l���
                            while (1) {
                                printf("\nAGV���O\n");
                                printf("1. �i�JAGV���A \n");
                                printf("2. �h�XAGV���A \n");
                                printf("3. AGV���A�T�{ \n");
                                printf("0. �^�W�@��\n");
                                printf("�п�ܫ��O: ");
                                scanf("%d", &subChoice);
                                getchar();
            
                                switch (subChoice) {
                                    case 1:
                                        // �i�JAGV���A
                                        printf("\n�ШD�i�JAGV���A...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C A4 00 01", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 2:
                                        // �h�XAGV���A
                                        printf("\n�ШD�h�XAGV���A...\n");
                                        if (rs485_send_receive(hSerial, "01 06 9C A4 00 00", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 3:
                                        // AGV���A�T�{
                                        printf("\n����AGV���A�T�{...\n");
                                        if (rs485_send_receive(hSerial, "01 03 9C A5 00 01", receiveBuffer) != 0) {
                                            printf("���O���楢�ѡC\n");
                                        }
                                        break;
                                    case 0:
                                        // �^�W�@��
                                        break;
                                    default:
                                        printf("�L�Ī���ܡA�Э��s��J�C\n");
                                        break;
                                }
                                if (subChoice == 0) {
                                    break; // ���X�l���j��
                                }
                            }
                            break;
                    
                        case 0:
                            // �^�W�@��
                            break;
                        default:
                            printf("�L�Ī���ܡA�Э��s��J�C\n");
                            break;
                    }
                    if (subChoice == 0) {
                        break; // ���X�l���j��
                    }
                }
                break;
            case 2:
                // �۩w�q 16 �i���J�Ҧ�
                printf("�п�J�q�T���O (16�i��r��): ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

                // �o�e�M�������
                if (rs485_send_receive(hSerial, inputBuffer, receiveBuffer) != 0) {
                    printf("���ե��ѡC\n");
                }
                break;
            case 0:
                // �h�X�{��
                CloseHandle(hSerial);
                printf("�{������\n");
                return 0;
            default:
                printf("�L�Ī���ܡA�Э��s��J�C\n");
                break;
        }
    }

    return 0;
}