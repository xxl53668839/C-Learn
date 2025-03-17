#include <stdio.h>

/*題目：計算矩陣的行總和
請撰寫一個 C 程式，定義一個函數 row_sums()，用來計算一個 M × N 矩陣 每一行的總和，並將結果儲存到一個陣列中。
在 main() 中，請建立一個 3 × 4 的矩陣，並使用 row_sums() 來計算其每一行的總和，最後在 main() 中印出結果。

要求：

row_sums() 函數應該使用 指標運算 來存取矩陣元素，而不是使用 matrix[i][j]。
在 main() 裡，定義一個 3×4 的整數矩陣，並呼叫 row_sums() 計算每一行的總和*/

void row_sums(int *matrix, int rows, int cols, int sum[]) {
    int i, j;
    for (i = 0; i < rows; i++) {
        sum[i] = 0;  // **修正 1️⃣：先初始化 sum[i]**
        for (j = 0; j < cols; j++) {
            sum[i] += *(matrix + i * cols + j);  // 使用指標運算存取矩陣元素
        }
    }
}

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    int sum[3];

    // **修正 2️⃣：先執行 row_sums()，再用迴圈輸出**
    row_sums((int*)matrix, 3, 4, sum);

    // 正確輸出 sum[]
    for (int i = 0; i < 3; i++) {
        printf("Row %d sum = %d\n", i, sum[i]);
    }

    return 0;
}