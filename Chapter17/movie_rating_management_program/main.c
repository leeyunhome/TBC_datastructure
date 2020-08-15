
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TSIZE 30
//#define LMAX 7

struct movie
{
    char title[TSIZE];
    float rating;
};

void readFILE(struct movie** movie_list, int* ptr_n_items);

int main()
{
    struct movie* movie_list;
    int n_items = 0;

    readFILE(&movie_list, &n_items);

    return 0;
}
void readFILE(struct movie** movie_list, int* ptr_n_items)
{
    char filename[TSIZE] = { 0, };
    printf("input file name to open\n");
    int flag = scanf("%[^\n]%*c", filename);
    if (flag != 1)
    {
        printf("Wrong input. Terminating");
        exit(1);
    }
    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Cannot open file\n");
        exit(1);
    }

    // acquire number of movies
    fscanf(fp, "%d", &*ptr_n_items);

    printf("%d items\n", *ptr_n_items);

    *movie_list = (struct movie*)malloc(sizeof(struct movie) * *ptr_n_items);

    for (int idx = 0; idx < *ptr_n_items; ++idx)
    {
        fprintf(stderr, "%d==%s\n", __LINE__, __FUNCTION__);
        fscanf(fp, "%s", *movie_list[idx]->title);
        fscanf(fp, "%f", &movie_list[idx]->rating);
    }

    for (int idx = 0; idx < *ptr_n_items; ++idx)
    {
        printf("%d : \"%s\", %.1f", idx, movie_list[idx]->title, movie_list[idx]->rating);
    }
}