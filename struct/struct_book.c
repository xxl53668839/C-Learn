#include <stdio.h>

struct book
{   
    char title[41];
    char author[31];
    float value;
};

int main()
{
    struct book libry;
    printf("請輸入書名: ");
    gets(libry.title);
    printf("請輸入作者名: ");
    gets(libry.author);
    printf("請輸入售價: ");
    scanf("%f",&libry.value);

    printf("%s %s NTD.%.1f\n",libry.title,libry.author,libry.value);

    return 0;
}