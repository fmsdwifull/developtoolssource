#include <stdio.h>

unsigned long ipstrtoint(const char *ip);
int main(void)
{
    char *p="192.168.1.21";
    unsigned long   ip;
    printf("int size is :%d\n",sizeof(int));
    printf("long size is :%d\n",sizeof(long));
    ip= ipstrtoint(p);
    printf("ip:%ld\n",(unsigned long)ip);
    //getch();
    return 0;
}
//
unsigned long ipstrtoint(const char *ip)
{
    unsigned long   result = 0;
    unsigned long   tmp = 0;
    int   shift = 24;
    const char *pEnd = ip;
    const char *pStart = ip;
    while(*pEnd != '\0')
    {
      while(*pEnd != '.' && *pEnd != '\0')
        pEnd++;
      tmp = 0;
      while(pStart < pEnd)
      {
         tmp = tmp * 10 + (*pStart - '0');
         printf("%c\n",*pStart);
         printf("%d\n",tmp);
         pStart++;
      }
      result += (tmp << shift);
      shift -= 8;
      if (*pEnd == '\0')
         break;
      pStart = pEnd + 1;
      pEnd++;
    }
    return result;
}
