#include <stdio.h>
#include <stdlib.h>

void clear_stdin() {
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void unions(int parent[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[yroot] = xroot;
}

int main(){
    printf("请输入矩阵维数：\n");
    int weishu,num=0;
    scanf("%d",&weishu);
    clear_stdin();
    int jz[weishu][weishu],jz1[weishu][weishu];
    printf("请输入矩阵:\n");
    for (int n = 0; n < weishu; n++) {
        for (int m = 0; m < weishu; m++) {
            scanf("%d", &jz[n][m]);
            jz1[n][m]=0;
        }
        clear_stdin();
    }
    //
    for(int i=0;i<weishu;i++){
        for(int n=i+1;n<weishu;n++){
            if(jz[i][n]!=0)
            num++;
        }
    }

    int bian[num][3],count=0;
    for(int i=0;i<weishu;i++){///////
        for(int n=i+1;n<weishu;n++){
            if(jz[i][n]!=0){
                bian[count][0]=i;
                bian[count][1]=n;
                bian[count][2]=jz[i][n];
                count++;
                if(count==num)
                break;
            }
        }
        if(count==num)
        break;
    }
    for(int i=0;i<num-1;i++){
        int temp[3];
        for(int n=1;n<num-i;n++){
            if(bian[n][2]<bian[n-1][2]){
                temp[0]=bian[n][0];
                temp[1]=bian[n][1];
                temp[2]=bian[n][2];
                bian[n][0]=bian[n-1][0];
                bian[n][1]=bian[n-1][1];
                bian[n][2]=bian[n-1][2];
                bian[n-1][0]=temp[0];
                bian[n-1][1]=temp[1];
                bian[n-1][2]=temp[2];
            }
        }
    }
    int parent[weishu],shuzhi=0;
    for (int i = 0; i < weishu; i++) {
        parent[i] = i;
    }
    for(int i=0;shuzhi<weishu-1&&i<num;i++){
        int gen=bian[i][0],ye=bian[i][1],quan=bian[i][2],seek_gen=find(parent,gen),seek_ye=find(parent,ye);
        if(seek_gen!=seek_ye){
            jz1[gen][ye]=quan;
            jz1[ye][gen]=quan;
            unions(parent,gen,ye);
            shuzhi++;
        }
    }

    //
    printf("\n运算结果为：\n");
    for (int n = 0; n < weishu; n++) {
        for (int m = 0; m < weishu; m++) {
            printf("%d",jz1[n][m]);
            if(m!=weishu-1)
            printf(" ");
            else
            printf("\n");
        }
    }
    return 0;
}