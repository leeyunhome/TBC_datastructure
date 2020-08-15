
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include <string.h>

#define MAX 30
#define LMAX 10

struct movie
{
    char* title[MAX];
    float rating;
};

void readFILE(struct movie *movies, int *length);
void printMenu(int* ptr_n);
int input_int();
void print_all_items(struct movie* movies, int size);
void print_an_item();
void edit_an_item();
void add_an_item();
void insert_an_item();
void delete_an_item();
void delete_all_items();
void save_file(struct movie movies[], int n_items);
void search_by_name();
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
            edit_an_item();
            break;
        case 4:
            add_an_item();
            break;
        case 5:
            insert_an_item();
            break;
        case 6:
            delete_an_item();
            break;
        case 7:
            delete_all_items();
            break;
        case 8:
            save_file(movie_list, n_items);
            break;
        case 9:
            search_by_name();
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
    *ptr_n = input_int();
}

int input_int()
{
    int input;

    printf(">>");
    scanf("%d", &input);

    if (input < 1 && input >10)
    {
        puts("please input a valid number");
        while (getchar() != '\n')
            continue;
    }
    return input;
}

void readFILE(struct movie *movies, int *ptr_n_items)
{
    char filename[MAX] = { 0, };

    int flag;

    printf("Please input filename to read and press Enter.\n>>");

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
void print_all_items(struct movie* movies, int size)
{
    for (int movie_index = 0; movie_index < size; ++movie_index)
    {
        printf("%d : %s, %f\n", movie_index, movies[movie_index].title, movies[movie_index].rating);
    }
}
void print_an_item()
{
    puts("print_an_item");
}
void edit_an_item()
{
    puts("edit_an_item");
}
void add_an_item()
{
    puts("add_an_item");
}
void insert_an_item()
{
    puts("insert_an_item");
}
void delete_an_item()
{
    puts("delete_an_item");
}
void delete_all_items()
{
    puts("delete_all_items");
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

    printf("%d items have been saved to the file[%s].\n", n_items, new_filename);
}
void search_by_name()
{
    puts("search_by_name");
}
void quit()
{
    puts("good-bye");
    exit(EXIT_SUCCESS);
}