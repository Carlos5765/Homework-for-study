#include <stdio.h>
#include <stdlib.h>

void clear_stdin() {
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}

int main() {
    int weishu, cishu;
    printf("请输入矩阵维数:\n");
    scanf("%d", &weishu);
    clear_stdin();
    
    int jz[weishu][weishu], temp[weishu][weishu], result[weishu][weishu];
    
    for (int i = 0; i < weishu; i++) {
        for (int j = 0; j < weishu; j++) {
            result[i][j] = (i == j) ? 1 : 0;
        }
    }
    
    printf("请输入路的长度:\n");
    scanf("%d", &cishu);
    clear_stdin();
    
    printf("请输入矩阵:\n");
    for (int n = 0; n < weishu; n++) {
        for (int m = 0; m < weishu; m++) {
            scanf("%d", &jz[n][m]);
        }
        clear_stdin();
    }
    
    for (int i = 0; i < cishu; i++) {

        for (int q = 0; q < weishu; q++) {
            for (int p = 0; p < weishu; p++) {
                temp[q][p] = 0;
                for (int k = 0; k < weishu; k++) {
                    temp[q][p] += result[q][k] * jz[k][p];
                }
            }
        }
        
        for (int j = 0; j < weishu; j++) {
            for (int k = 0; k < weishu; k++) {
                result[j][k] = temp[j][k];
            }
        }
    }
    
    printf("结果为：\n");

    for (int n = 0; n < weishu; n++) {
        for (int m = 0; m < weishu; m++) {
            printf("%d", result[n][m]);
            if (m == weishu - 1)
                printf("\n");
            else
                printf(" ");
        }
    }
    system("pause");
    return 0;
}