#ifndef LIBRARY_H
#define LIBRARY_H
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char name[21],type,auther[21];
    int borrowing_time,number,borrowing_number;
} Book_Information;//定义书籍相关信息

void Clear_The_Buffer();
void Menu();
int Menu_Jump(int translater);
void Type_Code_Tips();
void Information_Input();
void Information_Browsing();
void Default_Sorting(FILE *fp);//默认排序
void Quantity_Sorting(FILE *fp,char *name);//藏书数量排序
void Heat_Sorting(FILE *fp,char *name);//热度排序
void Loan_Sorting(FILE *fp,char *name);//借出数量排序
void Information_Update();
void Information_Change();
void Information_Deletion();
void Information_Lookup();
void Book_Information_Lookup();
void Author_Information_Lookup();
void Book_Borrowing();
void Book_Returning();
void Borrowing_History();
void User_Searching();
void Print_All(char *filename);
void Print_Name(char *filename1,char *name1);

#endif