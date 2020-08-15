
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX 30
#define LMAX 10

struct movie
{
    char title[MAX];
    float rating;
};

void readFILE(struct movie *movie_list, int *length);
void printMenu(int* ptr_n);
int input_int();
void print_all_items(struct movie* movie_list, int n_items);
void print_an_item(struct movie movie_list[], int n_items);
void edit_an_item(struct movie movie_list[], int n_items);
void add_an_item(struct movie movie_list[], int *n_items);
void insert_an_item(struct movie movie_list[], int *n_items);
void delete_an_item(struct movie movie_list[], int* n_items);
void delete_all_items(struct movie movie_list[], int* n_items);
void save_file(struct movie movies[], int n_items);
void search_by_name(struct movie movie_list[], int n_items);
void quit();

int main()
{
    size_t n_items = 0;

    struct movie movie_list[LMAX];

    readFILE(movie_list, &n_items);

    while (1)
    {
        int choice;

        printMenu(&choice);

        switch (choice)
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
            add_an_item(movie_list, &n_items);
            break;
        case 5:
            insert_an_item(movie_list, &n_items);
            break;
        case 6:
            delete_an_item(movie_list, &n_items);
            break;
        case 7:
            delete_all_items(movie_list, &n_items);
            break;
        case 8:
            save_file(movie_list, n_items);
            break;
        case 9:
            search_by_name(movie_list, n_items);
            break;
        case 10:
            quit();
            break;
        default:
            puts("please input a valid number");
        }
    }

    
    return 0;
}
void printMenu(int* ptr_n)
{
    puts("\nPlease select an option and press enter.");
    printf("1. Print all items\t2. Print an item\n");
    printf("3. Edit an item   \t4. Add an item\n");
    printf("5. Insert an item \t6. Delete an item\n");
    printf("7. Delete all items\t8. Save file\n");
    printf("9. Search by name\t10. Quit\n");
    
    int input = input_int();

    if (input >= 1 && input <= 10)
    {
        *ptr_n = input;
    }
    else
    {
        printf("%d is invalid. Please try again.\n", input);
    }
}

int input_int()
{
    int input;

    while (1)
    {
        printf(">> ");
        if (scanf("%d%*c", &input) == 1) return input;
        else
        {
            puts("please input an integer and press enter. Try again.\n");
            while (getchar() != '\n')
                continue;
        }
    }
    

}

void readFILE(struct movie *movies, int *ptr_n_items)
{
    char filename[MAX] = { 0, };

    int flag;

    printf("Please input filename to read and press Enter.\n>> ");

    flag = scanf("%[^\n]%*c", filename);
    if (flag != 1)
    {
        printf("Wrong input. Terminating.\n");
        exit(1);
    }

    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        puts("Cannot open file");
        exit(1);
    }
    int num;
    fscanf(fp, "%d%*c", &num);

    //char* title[MAX];

    for (int i = 0; i < num; ++i)
    {
        if (fscanf(fp, "%[^\n]%*c", movies[*ptr_n_items].title) != 1 ||
            fscanf(fp, "%f%*c", &movies[*ptr_n_items].rating) != 1)
        {
            printf("ERROR: Wrong file format.\n");
            exit(1);
        }
        
        *ptr_n_items += 1;
    }

    assert(*ptr_n_items == num);

    fclose(fp);

    printf("\n%d items have been read from the file.\n", *ptr_n_items);
}
void print_all_items(struct movie* movies, int n_items)
{
    for (int movie_index = 0; movie_index < n_items; ++movie_index)
    {
        printf("%d : \"%s\", %.1f\n", movie_index, movies[movie_index].title, movies[movie_index].rating);
    }
}
void print_an_item(struct movie movie_list[], int n_items)
{
    int index = 0;
    puts("Please input an integer");
    
    while (index = input_int())
    {
        if (index < 0 || index >= n_items)
        {
            puts("Wrong index. Try again");
        }
        else
        {
            break;
        }
    }
    
    printf("%d : \"%s\", %f\n", index, movie_list[index].title, movie_list[index].rating);
}
void edit_an_item(struct movie movie_list[], int n_items)
{
    int index = 0;
    int flag = 0;
    char new_title[MAX] = { 0, };
    float new_rating = 0.0f;
    puts("Please input a number to edit");

    while (index = input_int())
    {
        if (index < 0 || index >= n_items)
        {
            puts("Wrong index. Try again");
        }
        else
        {
            break;
        }
    }
    printf("\"%s\", %f\n", movie_list[index].title, movie_list[index].rating);

    printf("Please input new title\n>> ");
    flag = scanf("%[^\n]%*c", new_title);
    printf("Please input new rating\n>> ");
    flag = scanf("%f%*c", &new_rating);
    strcpy(movie_list[index].title, new_title);
    movie_list[index].rating = new_rating;

    printf("%d : \"%s\", %f\n", index, movie_list[index].title, movie_list[index].rating);
}
void add_an_item(struct movie movie_list[], int* n_items)
{
    if (*n_items == LMAX)
    {
        printf("No more space.\n");
        return;
    }
    int flag = 0;
    char new_title[MAX] = { 0, };
    float new_rating = 0.0f;
    puts("Please input a title to add");
    flag = scanf("%[^\n]%*c", new_title);
    puts("Please input a rating to add");
    flag = scanf("%f", &new_rating);
    strcpy(movie_list[*n_items].title, new_title);
    movie_list[*n_items].rating = new_rating;
    printf("%d : \"%s\", %f\n", *n_items, movie_list[*n_items].title, movie_list[*n_items].rating);
    *n_items += 1;
}
void insert_an_item(struct movie movie_list[], int* n_items)
{
    if (*n_items == LMAX)
    {
        printf("No more space.\n");
        return;
    }
    int index = 0;
    int flag = 0;
    index = input_int();

    memmove(&movie_list[index + 1], &movie_list[index], sizeof(struct movie) * (*n_items - index));

    /* For loop implementation */
    /*for (int movie_index = *n_items -1; movie_index >= index; --movie_index)
    {
        strcpy(movie_list[movie_index + 1].title, movie_list[movie_index].title);
        movie_list[movie_index + 1].rating = movie_list[movie_index].rating;
    }*/

    char new_title[MAX] = { 0, };
    float new_rating = 0.0f;
    flag = scanf("%[^\n]%*c", new_title);
    if (flag != 1)
    {
        puts("Wrong input. Terminating");
        exit(1);
    }
    flag = scanf("%f", &new_rating);
    if (flag != 1)
    {
        puts("Wrong input. Terminating");
        exit(1);
    }

    strcpy(movie_list[index].title, new_title);
    movie_list[index].rating = new_rating;
    *n_items += 1;
}
void delete_an_item(struct movie movie_list[], int* n_items)
{
    int index;
    int flag;
    puts("input an index to delete\n>> ");
    flag = scanf("%d", &index);
    if (flag != 1)
    {
        puts("Wrong input. Terminating");
        exit(1);
    }
    //memmove(&movie_list[index], &movie_list[index + 1], sizeof(struct movie) * (*n_items - index));
    for (int movie_index = index; movie_index < *n_items; ++movie_index)
    {
        strcpy(movie_list[movie_index].title, movie_list[movie_index +1].title);
        movie_list[movie_index].rating = movie_list[movie_index +1].rating;
    }
    *n_items -= 1;
}
void delete_all_items(struct movie movie_list[], int* n_items)
{
    for (int movie_index = 0; movie_index < *n_items; ++movie_index)
    {

    }
    *n_items = 0;
}
void save_file(struct movie movies[], int n_items)
{
    char new_filename[MAX] = { 0, };
    puts("Please input filename to write and press Enter.\n");
    printf(">> ");
    if (scanf("%s", new_filename) != 1)
    {
        puts("Wrong input. Terminating.");
        exit(1);
    }
    FILE* fw;
    fw = fopen(new_filename, "w");
    if (fw == NULL)
    {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }

    fprintf(fw, "%d\n", n_items);
    for (int index = 0; index < n_items; ++index)
    {
        fprintf(fw, "%s\n", movies[index].title);
        fprintf(fw, "%f\n", movies[index].rating);
    }

    fclose(fw);

    printf("%d items have been saved to the file[ %s ].\n", n_items, new_filename);
}
void search_by_name(struct movie movie_list[], int n_items)
{
    int flag = 0;
    char title[MAX];
    int index = 0;
    puts("input a title to search");
    flag = scanf("%[^\n]%*c", title);
    for (int movie_index = 0; movie_index < n_items; ++movie_index)
    {
        if (strcmp(movie_list[movie_index].title, title) == 0)
        {
            index = movie_index;
        }
    }

    if (index)
    {
        printf("%d : \"%s\", %.1f\n", index, movie_list[index].title, movie_list[index].rating);
    }
    else
    {
        printf("No movie: %s\n", title);
    }
}
void quit()
{
    puts("good-bye");
    exit(EXIT_SUCCESS);
}