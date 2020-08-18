
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSIZE 45
#define LMAX 6

struct movie {
    char title[TSIZE];
    float rating;
};

int input_int();
int input_menu();
void read_files(struct movie movie_list[], int *ptr_n_items);
void print_all_items(struct movie movie_list[], int n_items);
void print_an_item(struct movie movie_list[], int n_items);
void edit_an_item(struct movie movie_list[], int n_items);


int main()
{
    struct movie movie_list[LMAX];
    int n_items;

    read_files(movie_list, &n_items);
    
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
        default:
            printf("%d is not implemented.\n", s);
        }
    }
    

    return 0;
}
int input_int()
{
    int input;
    printf(">> ");
    while (1)
    {
        if (scanf("%d%*c", &input) == 1) return input;
        else
        {
            printf("input a valid number\n");
            while (getchar() != '\n')
                continue;
        }
    }
    return input;
}
int input_menu()
{
    int index = 0;
    while (1)
    {
        printf("\nPlease input a number\n");
        printf("1. print all item    2. print an item\n");
        printf("3. edit an item      4. add an item\n");
        printf("5. insert an item    6. delete an item\n");
        printf("7. delete all item   8. save to file\n");
        printf("9. search by name    10. quit\n");

        index = input_int();

        if (index >= 1 && index <= 10) return index;
        else
        {
            printf("please input a valid number\n");
        }
    }
}
void read_files(struct movie movie_list[], int* ptr_n_items)
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

    for (int idx = 0; idx < *ptr_n_items; ++idx)
    {
        fscanf(file, "%[^\n]%*c", movie_list[idx].title);
        fscanf(file, "%f%*c", &movie_list[idx].rating);
    }
    printf("%d items has been saved to file", *ptr_n_items);

}
void print_all_items(struct movie movie_list[], int n_items)
{
    for (int item = 0; item < n_items; ++item)
    {
        printf("%d : \"%s\", %.1f\n", item, movie_list[item].title, movie_list[item].rating);
    }
}
void print_an_item(struct movie movie_list[], int n_items)
{
    printf("Input a number to print and press Enter.\n");
    int index = input_int();

    if (index < n_items)
    {
        printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
    }
    else
    {
        printf("Wrong input. try again.\n");
    }
}
void edit_an_item(struct movie movie_list[], int n_items);
