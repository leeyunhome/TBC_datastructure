
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TSIZE 45
//#define LMAX 6

struct movie {
    char title[TSIZE];
    float rating;
};

int input_int();
int input_menu();
void read_file(struct movie** ptr_movie_list, int* ptr_n_items);
void print_all_items(struct movie* movie_list, int n_items);
void print_an_item(struct movie* movie_list, int n_items);
void edit_an_item(struct movie* movie_list, int n_items);
void add_an_item(struct movie** ptr_movie_list, int* ptr_n_items);
void insert_an_item(struct movie** ptr_movie_list, int* ptr_n_items);
void delete_an_item(struct movie** ptr_movie_list, int* ptr_n_items);
void write_to_file(struct movie *movie_list, int n_items);
void search_by_name(struct movie *movie_list,int n_items);

int main()
{
    struct movie* movie_list = NULL;

    int n_items = 0;

    read_file(&movie_list, &n_items);

    while (1)
    {
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
            delete_an_item(&movie_list, &n_items);
            break;
        case 7:
            n_items = 0;
            break;
        case 8:
            write_to_file(movie_list, n_items);
            break;
        case 9:
            search_by_name(movie_list, n_items);
            break;
        case 10:
            printf("Good bye.\n");
            free(movie_list);
            n_items = 0;
            exit(EXIT_SUCCESS);
        default:
            printf("Not implemented %d\n", s);
        }
    }

    free(movie_list);
    n_items = 0;

    return 0;
}
void read_file(struct movie** ptr_movie_list, int* ptr_n_items)
{
    char filename[TSIZE] = { 0, };
    printf("Please input a filename to read and press Enter.\n");
    if (scanf("%[^\n]%*c", filename) != 1)
    {
        printf("Wrong input. Terminating\n");
        exit(EXIT_FAILURE);
    }
    FILE* file;
    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    // acquire number of movies
    int num;
    if (fscanf(file, "%d%*c", &num) != 1)
    {
        printf("ERROR: Wrong file format.");
        exit(1);
    }

    *ptr_movie_list = (struct movie*)malloc(sizeof(struct movie) * num);

    if (*ptr_movie_list == NULL)
    {
        printf("malloc() failed.\n");
        exit(1);
    }

    for (int idx = 0; idx < num; ++idx)
    {
        if (fscanf(file, "%[^\n]%*c", (*ptr_movie_list)[*ptr_n_items].title) != 1 ||
            fscanf(file, "%f%*c", &(*ptr_movie_list)[*ptr_n_items].rating) != 1)
        {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        
        *ptr_n_items += 1;
    }
    assert(*ptr_n_items == num);
    fclose(file);
    printf("%d items has been saved to file", *ptr_n_items);

}
int input_menu()
{
    printf("\nPlease input a menu and press Enter.\n");
    printf("1. Print all items.    2. Print an item.\n");
    printf("3. Edit an item.       4. Add an item.\n");
    printf("5. Insert an item.     6. Delete an item.\n");
    printf("7. Delete all item.    8. Save to file.\n");
    printf("9. Search by name.     10. Quit.\n");

    int index = input_int();

    if (index >= 1 && index <= 10) return index;
    else
    {
        printf("Not implemented. try again\n");
        exit(1);
    }
}
int input_int()
{
    printf(">> ");
    int input;

    while (1)
    {
        int flag = scanf("%d%*c", &input);
        if (flag == 1) return input;
        else
        {
            printf("Wrong input. try again\n");
            while(getchar() != '\n')
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
    printf("Please input an index to print and press Enter.\n");
    int flag = scanf("%d%*c", &index);
    if (flag != 1)
    {
        printf("Wrong input. Terminating\n");
        exit(1);
    }

    while (1)
    {
        if (index < n_items)
        {
            printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
            break;
        }
        else
        {
            printf("Wrong input. Try again.\n");
            while (getchar() != '\n')
                continue;
        }
    }

    
}
void edit_an_item(struct movie* movie_list, int n_items)
{
    int index;
    index = input_int();
    printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
    printf("Please input a new title and press Enter.\n");
    scanf("%[^\n]%*c", movie_list[index].title);
    printf("Please input a new rating and press Enter.\n");
    scanf("%f%*c", &(movie_list[index].rating));
    printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
}
void add_an_item(struct movie** ptr_movie_list, int* ptr_n_items)
{
    struct movie* temp = *ptr_movie_list;
    *ptr_movie_list = malloc(sizeof(struct movie) * (*ptr_n_items + 1));

    if (*ptr_movie_list == NULL)
    {
        printf("malloc() failed.\n");
        exit(EXIT_FAILURE);
    }
    memcpy(*ptr_movie_list, temp, sizeof(struct movie) * *ptr_n_items);

    free(temp);
    printf("Please input a title and press Enter.\n");
    scanf("%[^\n]%*c", (*ptr_movie_list)[*ptr_n_items].title);
    printf("Please input a rating and press Enter.\n");
    scanf("%f%*c", &(*ptr_movie_list)[*ptr_n_items].rating);
    *ptr_n_items += 1;
}
void insert_an_item(struct movie** ptr_movie_list, int* ptr_n_items)
{
    /*if (*ptr_n_items == LMAX)
    {
        puts("No more space.\n");
        return;
    }*/

    struct movie* temp = *ptr_movie_list;
    *ptr_movie_list = malloc(sizeof(struct movie) * (*ptr_n_items + 1));
    if (*ptr_movie_list == NULL)
    {
        printf("malloc() failed");
        exit(1);
    }
    memcpy(*ptr_movie_list, temp, sizeof(struct movie) * *ptr_n_items);

    free(temp);

    printf("Please input an index to insert and press Enter.\n");
    int index = input_int();

    memmove(&(*ptr_movie_list)[index + 1], &(*ptr_movie_list)[index], sizeof(struct movie) * (*ptr_n_items - index));
    printf("Please input a title and press Enter.\n");
    scanf("%[^\n]%*c", (*ptr_movie_list)[index].title);
    printf("Please input a rating and press Enter.\n");
    scanf("%f%*c", &(*ptr_movie_list)[index].rating);
    *ptr_n_items += 1;
}
void delete_an_item(struct movie** ptr_movie_list, int* ptr_n_items)
{
    while (1)
    {
        printf("Please input an index to delete and press Enter.\n");
        int index = input_int();

        if (index < *ptr_n_items)
        {
            memmove(&(*ptr_movie_list)[index], &(*ptr_movie_list)[index + 1], sizeof(struct movie) * (*ptr_n_items - index - 1));

            struct movie* temp = *ptr_movie_list;
            *ptr_movie_list = malloc(sizeof(struct movie) * (*ptr_n_items - 1));
            if (*ptr_movie_list == NULL)
            {
                printf("malloc() failed.\n");
                exit(EXIT_FAILURE);
            }

            memmove(*ptr_movie_list, temp, sizeof(struct movie) * (*ptr_n_items - 1));

            free(temp);
            *ptr_n_items -= 1;
            break;
        }
        else
        {
            printf("Wrong index. Try again.\n");
        }
    }
}
void write_to_file(struct movie* movie_list, int n_items)
{
    char filename[TSIZE];
    if (scanf("%[^\n]%*c", filename) != 1)
    {
        printf("Wrong input. Terminating.\n");
        exit(EXIT_FAILURE);
    }

    FILE* file;
    if ((file = fopen(filename, "w")) == NULL)
    {
        printf("Cannot open file %s.", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d\n", n_items);

    for (int idx = 0; idx < n_items; ++idx)
    {
        fprintf(file, "%s\n%f\n", movie_list[idx].title, movie_list[idx].rating);
    }

    fclose(file);
    printf("file write complete.\n");
}
void search_by_name(struct movie* movie_list, int n_items)
{
    char search[TSIZE] = { 0, };
    printf("Please input title to search and press Enter.\n");
    int flag = scanf("%[^\n]%*c", search);
    if (flag != 1)
    {
        printf("Wrong input. Terminating");
        exit(EXIT_FAILURE);
    }
    int idx = 0;
    for (; idx < n_items; ++idx)
    {
        if (strcmp(movie_list[idx].title, search) == 0) break;
    }

    if (idx == n_items)
    {
        printf("no movie found : %s\n", search);
    }
    else
    {
        printf("%d : \"%s\", %.1f\n", idx, movie_list[idx].title, movie_list[idx].rating);
    }
}