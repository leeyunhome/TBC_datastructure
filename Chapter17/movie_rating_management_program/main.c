
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define TSIZE 45
//#define LMAX 7

struct movie
{
    char title[TSIZE];
    float rating;
};

void readFILE(struct movie ** ptr_movie_list, int* ptr_n_items);
int input_menu();
int input_int();
void print_all_items(struct movie* movie_list, int n_items);
void print_an_item(struct movie* movie_list, int n_items);
void edit_an_item(struct movie* movie_list, int n_items);
void add_an_item(struct movie ** ptr_movie_list, int* ptr_n_items);
void insert_an_item(struct movie** ptr_movie_list, int* ptr_n_items);
void delete_an_item(struct movie* ptr_movie_list, int* ptr_n_items);
void write_file(struct movie* movie_list, int n_items);
void search_by_name(struct movie* movie_list, int n_items);

int main()
{
    //struct movie movie_list[LMAX];
    struct movie* movie_list = NULL;
    int n_items = 0;

    readFILE(&movie_list, &n_items);

    while (1)
    {
        printf("\n");
        int s = input_menu();

        switch (s)
        {
        case 1:
            print_all_items(movie_list, n_items);
            break;
        case 2:
            print_an_item(movie_list, n_items);
            break;
        case 3:
            edit_an_item(movie_list, n_items);
            break;
        case 4:
            add_an_item(&movie_list, &n_items);
            break;
        case 5:
            insert_an_item(&movie_list, &n_items);
            break;
        case 6:
            delete_an_item(movie_list, &n_items);
            break;
        case 7:
            n_items = 0;
            break;
        case 8:
            write_file(movie_list, n_items);
            break;
        case 9:
            search_by_name(movie_list, n_items);
            break;
        case 10:
            printf("Good-bye.\n");
            free(movie_list);
            n_items = 0;
            exit(EXIT_SUCCESS);
        default:
            printf("%d is not implemented.\n", s);
        }
    }

    free(movie_list);
    n_items = 0;

    return 0;
}
void readFILE(struct movie ** ptr_movie_list, int* ptr_n_items)
{
    /* Receives a double pointer to allocate memory */
    char filename[TSIZE] = { 0, };
    printf("Please input file name to read and press Enter.\n>> ");
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
    int num;
    if (fscanf(fp, "%d%*c", &num) != 1)
    {
        printf("ERROR: Wrong file format.");
        exit(1);
    }

    // 필요한 만큼 메모리 할당 받기
    *ptr_movie_list = (struct movie*)malloc(sizeof(struct movie) * num);

    if (*ptr_movie_list == NULL)
    {
        printf("Malloc failed.\n");
        exit(1);
    }

    for (int idx = 0; idx < num; ++idx)
    {
        if (fscanf(fp, "%[^\n]%*c", (*ptr_movie_list)[*ptr_n_items].title) != 1 ||
            fscanf(fp, "%f%*c", &(*ptr_movie_list)[*ptr_n_items].rating) != 1)
        {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        *ptr_n_items += 1;
    }

    assert(*ptr_n_items == num);

    fclose(fp);

    printf("%d items have been read from the file.\n", *ptr_n_items);

    //for (int idx = 0; idx < *ptr_n_items; ++idx)
    //{
    //    printf("%d : \"%s\", %.1f", idx, movie_list[idx]->title, movie_list[idx]->rating);
    //}
}
int input_menu()
{
    while (1)
    {
        puts("\nPlease select an option and press enter.");
        printf("1. Print all items\t2. Print an item\n");
        printf("3. Edit an item   \t4. Add an item\n");
        printf("5. Insert an item \t6. Delete an item\n");
        printf("7. Delete all items\t8. Save file\n");
        printf("9. Search by name\t10. Quit\n");

        int input = input_int();
        if (input >= 1 && input <= 10) return input;
        else
        {
            printf("%d is invalid number. Please try again\n", input);
        }
    }
    
}
int input_int()
{
    int input;

    while (1)
    {
        printf("\n>> ");
        int flag = scanf("%d%*c", &input);
        if (flag == 1) return input;
        else
        {
            puts("Please input an integer and press Enter. Try again.\n");
            while (getchar() != '\n')
                continue;
        }
    }
}
void print_all_items(struct movie* movie_list, int n_items)
{
    for (int idx = 0; idx < n_items; ++idx)
    {
        printf("%d : \"%s\", %.1f\n", idx, movie_list[idx].title, movie_list[idx].rating);
    }
}
void print_an_item(struct movie* movie_list, int n_items)
{
    int index;
    while (1)
    {
        puts("input a number of movie to print");
        index = input_int();
        if (index < n_items)
        {
            break;
        }
        else
        {
            puts("Wrong index. try again");
        }
    }
    printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
}
void edit_an_item(struct movie* movie_list, int n_items)
{
    printf("Input the index of item to edit.\n");
    int index = input_int();
    if (index < n_items)
    {
        printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);

        printf("Input new title and press enter.\n");
        printf(">> ");
        int f = scanf("%[^\n]%*c", movie_list[index].title);
        printf("Input new rating and press enter.\n");
        printf(">> ");
        f = scanf("%f%*c", &movie_list[index].rating);

        printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
    }
    else
    {
        printf("Invalid item.\n");
    }
    /*int index;
    while (1)
    {
        puts("input a number of movie to edit.");
        index = input_int();
        if (index < n_items) break;
        else
        {
            puts("input a valid number. try again");
        }
    }
    printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);

    puts("input a new title");
    if (scanf("%[^\n]%*c", movie_list[index].title) != 1)
    {
        printf("Wrong input. Terminating");
        exit(1);
    }
    puts("input a new rating");
    if (scanf("%f%*c", &movie_list[index].rating) != 1)
    {
        printf("Wrong input. Terminating");
        exit(1);
    }
    printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);*/
}
void add_an_item(struct movie ** ptr_movie_list, int* ptr_n_items) // n_items is a pointer
{
    /*if (*ptr_n_items == LMAX)
    {
        puts("No more space");
        exit(1);
    }*/
    /* Resizing allocated memory */
    struct movie* temp = *ptr_movie_list;
    *ptr_movie_list = (struct movie*)malloc(sizeof(struct movie) * (*ptr_n_items + 1));
    if (*ptr_movie_list == NULL)
    {
        printf("malloc() failed.\n");
        exit(1);
    }
    memcpy(*ptr_movie_list, temp, sizeof(struct movie) * *ptr_n_items);
    free(temp);

    const int index = *ptr_n_items;

    puts("input a title");
    if (scanf("%[^\n]%*c", (*ptr_movie_list)[index].title) != 1)
    {
        puts("Wrong input. Terminating");
    }
    puts("input a rating");
    if (scanf("%f%*c", &(*ptr_movie_list)[index].rating) != 1)
    {
        puts("Wrong input. Terminating");
    }
    printf("%d : \"%s\", %.1f\n", index, (*ptr_movie_list)[index].title, (*ptr_movie_list)[index].rating);
    *ptr_n_items += 1;
}
void insert_an_item(struct movie** ptr_movie_list, int* ptr_n_items)
{
    /*if (*ptr_n_items == LMAX)
    {
        puts("No more space");
        return;
    }*/

    /* Resizing allocated memory */
    
    struct movie* temp = *ptr_movie_list;
    *ptr_movie_list = (struct movie*)malloc(sizeof(struct movie) * ((size_t)(*ptr_n_items) + 1));
    if (*ptr_movie_list == NULL)
    {
        puts("malloc() failed.");
        exit(1);
    }
    memcpy(*ptr_movie_list, temp, sizeof(struct movie) * *ptr_n_items);
    free(temp);

    int index;
    printf("input the index of item to insert.\n");
    index = input_int();
    //memmove(&(*ptr_movie_list)[index + 1], &(*ptr_movie_list)[index], sizeof(struct movie) * (*ptr_n_items - index));

    /* For loop implementation */
    for (int idx = *ptr_n_items - 1; idx >= index; --idx)
    {
        fprintf(stderr, "%d = %s\n", __LINE__, __FUNCTION__);
        strcpy((*ptr_movie_list)[idx + 1].title, (*ptr_movie_list)[idx].title);
        (*ptr_movie_list)[idx + 1].rating = (*ptr_movie_list)[idx].rating;
    }
    puts("Input title and press enter.\n");
    printf(">> ");
    if (scanf("%[^\n]%*c", (*ptr_movie_list)[index].title) != 1)
    {
        puts("Wrong input. Terminating");
    }
    puts("input a rating");
    printf(">> ");
    if (scanf("%f%*c", &(*ptr_movie_list)[index].rating) != 1)
    {
        puts("Wrong input. Terminating");
    }
    printf("%d : \"%s\", %.1f\n", index, (*ptr_movie_list)[index].title, (*ptr_movie_list)[index].rating);
    
    *ptr_n_items += 1;
}
void delete_an_item(struct movie* ptr_movie_list, int* ptr_n_items)
{
    int index;
    printf("input an index to delete. >> ");
    index = input_int();
    //memcpy(&(ptr_movie_list)[index], &(ptr_movie_list)[index + 1], sizeof(struct movie) * (*ptr_n_items - index));

    /* for loop implementation */
    for (int idx = index; idx < *ptr_n_items; ++idx)
    {
        strcpy(ptr_movie_list[idx].title, ptr_movie_list[idx + 1].title);
        ptr_movie_list[idx].rating = ptr_movie_list[idx + 1].rating;
    }
    *ptr_n_items -= 1;

    // TODO: resize movie_list to save memory
}
void write_file(struct movie* movie_list, int n_items)
{
    char filename[TSIZE] = { 0, };
    printf("Please input filename to write and press Enter.\n>> ");
    if (scanf("%[^\n]%*c", filename) != 1)
    {
        puts("Wrong input. Terminating.\n");
        exit(1);
    }

    FILE* file;
    file = fopen(filename, "w");

    if (file == NULL)
    {
        puts("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "%d\n", n_items);
    for (int idx = 0; idx < n_items; ++idx)
    {
        fprintf(file, "%s\n", movie_list[idx].title);
        fprintf(file, "%f\n", movie_list[idx].rating);
    }

    fclose(file);

    printf("%d items have been saved to the file.\n", n_items);
}
void search_by_name(struct movie* movie_list, int n_items)
{
    char title_search[TSIZE] = { 0, };
    printf("input a name to search and press enter.");
    printf(">> ");
    int flag = scanf("%[^\n]%*c", title_search);
    if (flag != 1)
    {
        puts("Wrong input. Terminating.");
        exit(1);
    }

    int idx = 0;
    for (; idx < n_items; ++idx)
    {
        if (strcmp(movie_list[idx].title, title_search) == 0) break;
    }

    if (idx == n_items)
    {
        printf("No movie found: %s\n", title_search);
    }
    else
    {
        printf("%d : \"%s\", %.1f\n", idx, movie_list[idx].title, movie_list[idx].rating);
    }
}