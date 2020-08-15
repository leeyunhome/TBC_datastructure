
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define MAX 30

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
void save_file();
void search_by_name();
void quit();

int main()
{
    int choice;
    int n;

    struct movie movies[6];

    readFILE(movies, &n);

    while (1)
    {
        printMenu(&choice);

        switch (choice)
        {
        case 1:
            print_all_items(movies, n);
            break;
        case 2:
            print_an_item();
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
            save_file();
            break;
        case 9:
            search_by_name();
            break;
        case 10:
            quit();
            break;
        default:
            puts("please input a valid number");
            break;
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
        while (getchar() != NULL)
            continue;
    }
    return input;
}

void readFILE(struct movie *movies, int *length)
{
    char* filename[MAX];
    int n;
    int flag;

    printf("Please input filename to read and press Enter.\n>>");

    flag = scanf("%[^\n]%*c", filename);

    FILE* fp;
    fp = fopen(filename, "a+");
    if (fp == NULL)
    {
        puts("Cannot open file");
        exit(1);
    }
    
    fscanf(fp, "%d", &n);
    printf("\n%d items have been read from the file.\n", n);
    *length = n;

    //char* title[MAX];

    for (int i = 0; i < n; ++i)
    {
        fscanf(fp, "%[^\n]%*c", &movies[i].title);
        fscanf(fp, "%f", &movies[i].rating);
    }

    for (int movie_index = 0; movie_index < n; ++movie_index)
    {
        printf("%d : %s, %f\n", movie_index, movies[movie_index].title, movies[movie_index].rating);
    }
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
void save_file()
{
    puts("save_file");
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