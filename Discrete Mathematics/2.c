#include<stdio.h>
#include <stdlib.h>

void clear_stdin() {
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}

void Matrix1(){

    int weishu,zifan=1,duicheng=1,chuandi=1;
    printf("�������ά��\n");
    scanf("%d",&weishu);
    int k[weishu][weishu];
    printf("���������\n");
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            scanf("%d",&k[n][m]);
        }
        clear_stdin();
    }
    for(int n=0;n<weishu;n++){
        if(k[n][n]!=1){
            zifan=0;
            break;
        }
    }
    for(int n=0;n<weishu;n++){
        if(k[n][n]==1){
            break;
        }
        else if(n==weishu-1)
        zifan=-1;
    }
    for(int n=0;n<weishu-1;n++){
        for(int m=n+1;m<weishu;m++){
            if(k[n][m]!=k[m][n]){
                duicheng=0;
                break;
            }
        }
    }
    for(int n=0;n<weishu-1;n++){
        for(int m=n+1;m<weishu;m++){
            if(k[n][m]==k[m][n]){
                break;
            }
            else if(n==weishu-2&&m==weishu-1)
            duicheng=-1;
        }
    }
    for (int i = 0; i < weishu; i++) {
        for (int j = 0; j < weishu; j++) {
            for (int w = 0; w < weishu; w++) {
                if (k[i][j] && k[j][w] && !k[i][w]) {
                    chuandi=0;
                    break;
                }
            }
            if(chuandi==0)
            break;
        }
        if(chuandi==0)
        break;
    }
    for (int i = 0; i < weishu; i++) {
        for (int j = 0; j < weishu; j++) {
            for (int w = 0; w < weishu; w++) {
                if (k[i][j] && k[j][w] && !k[i][w]) {
                    chuandi=0;
                    break;
                }
            }
            if(chuandi==0)
            break;
        }
        if(chuandi==0)
        break;
    }
    printf("�þ�����:\n");
    if(zifan==1)
    printf("�Է���\n");
    else if(zifan==-1)
    printf("���Է���\n");
    if(duicheng==1)
    printf("�ԳƵ�\n");
    else if(duicheng==-1)
    printf("���ԳƵ�\n");
    if(chuandi==1)
    printf("���ݵ�\n");
    system("pause");
}

void Matrix2(){
    int weishu;
    printf("�������ά��\n");
    scanf("%d",&weishu);
    int k[weishu][weishu],k1[weishu][weishu];
    printf("���������\n");
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            scanf("%d",&k[n][m]);
            k1[n][m]=k[n][m];
        }
        clear_stdin();
    }
    printf("\n�Է��հ�����Ϊ��\n");
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            if(m==n)
            printf("1");
            else
            printf("%d",k[n][m]);
            if(m!=weishu-1)
            printf(" ");
            else
            printf("\n");
        }
    }
    printf("\n�ԳƱհ�����Ϊ��\n");
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            if(k1[n][m]==1)
            k1[m][n]=1;
        }
    }
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            printf("%d",k1[n][m]);
            if(m!=weishu-1)
            printf(" ");
            else
            printf("\n");
        }
    }
    for (int n = 0; n < weishu; n++) {
        for (int i = 0; i < weishu; i++) {
            for (int j = 0; j < weishu; j++)
                k[i][j] = k[i][j] || (k[i][n] && k[n][j]);
        }
    }
    printf("\n���ݱհ�����Ϊ��\n");
    for(int n=0;n<weishu;n++){
        for(int m=0;m<weishu;m++){
            printf("%d",k[n][m]);
            if(m==weishu-1)
            printf("\n");
            else
            printf(" ");
        }
    }
    system("pause");
}

void Main_menu(){
    printf("1.�жϱհ� 2.����հ� 0.�˳�\n");
}

int Main_jump(){
    int j;
    scanf("%d",&j);
    clear_stdin();
    if(j==0)
    return 0;
    else if(j==1){
        Matrix1();
        return 1;
    }
    else if(j==2){
        Matrix2();
        return 1;
    }
    else{
        printf("������Ϸ�����\n");
        system("cls");
        return 1;
    }
}

int main(){
    int j=1;
    while(j){
        system("cls");
        Main_menu();
        j=Main_jump();
    }
    return 0;
}