
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        default:
            printf("Not implemented %d\n", s);
        }
    }
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

    fscanf(file, "%d%*c", &*ptr_n_items);

    *ptr_movie_list = malloc(sizeof(struct movie) * *ptr_n_items);
    if (ptr_movie_list == NULL)
    {
        printf("malloc() failed.\n");
    }

    for (int idx = 0; idx < *ptr_n_items; ++idx)
    {
        if (fscanf(file, "%[^\n]%*c", (*ptr_movie_list)[idx].title) != 1 ||
            fscanf(file, "%f%*c", &(*ptr_movie_list)[idx].rating) != 1)
        {
            printf("Wrong file format. Terminating.\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("%d items has been saved to file", *ptr_n_items);

    fclose(file);
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