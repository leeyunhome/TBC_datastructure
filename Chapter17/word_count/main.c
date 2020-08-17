
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define STOP '.'

int main()
{
    int ch;
    int nCounts = 0;
    int nWords = 0;
    int nLines = 0;
    int wordFlag = false;
    int lineFlag = false;
    //int flag = scanf("%c", &ch);
    //if (flag != 1)
    //{
    //    puts("Wrong input. Terminating");
    //    exit(1);
    //}
    while ((ch = getchar()) != STOP)
    {
        if (isalnum(ch))
        {
            nCounts++;
        }

        if (!isspace(ch) && !wordFlag)
        {
            nWords++;
            wordFlag = true;
        }

        if (!isspace(ch) && !lineFlag)
        {
            nLines++;
            lineFlag = true;
        }

        if (ch == '\n')
        {
            lineFlag = false;
        }

        if (isspace(ch))
        {
            wordFlag = false;
        }
    }

    printf("%d Words, %d Lines, %d Counts", nWords, nLines, nCounts);

    return 0;
}
