#include <stdio.h>

unsigned short CrcCheck(unsigned char *data, unsigned char length) {
unsigned short crc = 0xFFFF;  // 初始 CRC 值
    for (int i = 0; i < length; i++) {
        crc ^= data[i];  // XOR 進行異或運算
        for (int j = 0; j < 8; j++) {  // 處理每個 bit
            if (crc & 0x0001) {
                crc = (crc >> 1) ^ 0xA001;  // 多項式 0xA001
            } else {
                crc >>= 1;
            }
        }
    }
    return crc;
}

int main() {
    unsigned char message[] = { 0x01, 0x03, 0x9C, 0x41, 0x00, 0x02 }; // Modbus 讀取指令
    unsigned short crc = CrcCheck(message, 6);
    printf("CRC-16: 0x%04X\n", crc);  // 輸出 CRC 校驗碼
    return 0;
}
