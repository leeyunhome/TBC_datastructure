
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define TSIZE 45
//#define LMAX 10

struct movie {
    char title[TSIZE];
    float rating;
    struct movie* next;
};

typedef struct movie* p_movie;

int input_int();
int input_menu();
void read_file(p_movie* p_head);
void write_file(p_movie head);
unsigned int count_items(const p_movie head);
void print_all_items(p_movie head);
void print_an_item(p_movie head);
void edit_an_item(p_movie head);
void add_an_item(p_movie* p_head);
void insert_an_item(p_movie* p_head);

int main()
{
    p_movie movie_list = NULL;
    int n_items = 0;

    read_file(&movie_list);

    while (1)
    {
        printf("\n");
        int s = input_menu();

        switch (s)
        {
        case 1:
            print_all_items(movie_list);
            break;
        case 2:
            print_an_item(movie_list);
            break;
        case 3:
            edit_an_item(movie_list);
            break;
        case 4:
            add_an_item(&movie_list);
            break;
        case 5:
            insert_an_item(&movie_list);
            break;
        case 8:
            write_file(movie_list);
            break;
        case 9:
            break;
        case 10:
            printf("Good bye.\n");
            exit(EXIT_SUCCESS);
        default:
            printf("%d is not implemented!\n", s);
        }
    }
    return 0;
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
            printf("Please input an integer and press Enter. Try again.\n");
            while (getchar() != '\n') continue;
        }
    }
}
int input_menu()
{
    int input;
    while (1)
    {
        printf("Select an menu and press Enter.\n");
        printf("1. Print all items.    2. Print an item.\n");
        printf("2. Edit an item.       4. Add an item.\n");
        printf("5. Insert an item.     6. Delete an item.\n");
        printf("7. Delete all items.   8. Save to file.\n");
        printf("9. Search by name.     10. Quit.\n");
        input = input_int();

        if (input >= 1 && input <= 10) return input;
        else
        {
            printf("%d is invalid. Please try again.\n", input);
        }
    }    
}
void read_file(p_movie* p_head)
{
    char filename[TSIZE] = { 0, };
    printf("Please input filename to read and press Enter.\n");
    printf(">> ");
    int flag = scanf("%[^\n]%*c", filename);
    if (flag != 1)
    {
        printf("Wrong input. Terminating.\n");
        exit(EXIT_FAILURE);
    }

    FILE* file;
    if ((file = fopen(filename, "r")) == NULL)
    {
        printf("Cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    /* Get number of items */
    int num = 0;
    flag = fscanf(file, "%d%*c", &num);
    if (flag != 1)
    {
        printf("Wrong file format.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "%d=%s, num=%d\n", __LINE__, __FUNCTION__, num);
    //*ptr_movie_list = (p_movie)malloc(sizeof(struct movie) * num);
    p_movie prev = *p_head;

    /* Create nodes */
    for (int idx = 0; idx < num; ++idx)
    {
        p_movie new_movie = (p_movie)malloc(sizeof(struct movie));
        if (new_movie == NULL)
        {
            printf("malloc() failed.\n");
            exit(EXIT_FAILURE);
        }
        new_movie->next = NULL;

        if (fscanf(file, "%[^\n]%*c", new_movie->title) != 1 ||
            fscanf(file, "%f%*c", &(new_movie->rating)) != 1)
        {
            fprintf(stderr, "%d=%s", __LINE__, __FUNCTION__);
            printf("Wrong file format. Terminating.\n");
            exit(EXIT_FAILURE);
        }

        if (prev == NULL)
        {
            *p_head = new_movie;
            prev = new_movie;
        }
        else
        {
            // Insert front
            //p_movie temp = (*p_head)->next;
            //(*p_head)->next = new_movie;
            //new_movie->next = temp;

            // add at the end
            prev->next = new_movie;
            prev = new_movie;
        }
        //*ptr_n_items += 1;
    }

    //assert(*ptr_n_items == num);

    fclose(file);

    printf("%d items have been read from file.\n", num);
}
void print_all_items(p_movie head)
{
    int numberOfItem = (int)count_items(head);
    int count = 0;
    while (head != NULL)
    {
        printf("%d : \"%s\", %.1f.\n", count, head->title, head->rating);
        head = head->next;
        count++;
    }
    assert(count == numberOfItem);
}

void print_an_item(p_movie head)
{
    printf("Please input an index to print and press Enter.\n");

    int input = input_int();
    int count = 0;

    while (head != NULL)
    {
        if (input == count)
        {
            break;
        }
        count++;
        head = head->next;
    }

    if (head != NULL)
        printf("%d : \"%s\", %.1f.\n", count, head->title, head->rating);
    else
        printf("Invalid item.\n");
}
void add_an_item(p_movie* p_head)
{
    //if (*ptr_n_items == LMAX)
    //{
    //    printf("No more space.\n"); // THIS DOESN'T HAPPNE!
    //    return;
    //}

    //const int index = *ptr_n_items;

    //printf("Input title and press Enter.\n");
    //printf(">> ");

    /* create a node */
    p_movie new_movie = (p_movie)malloc(sizeof(struct movie));
    if (new_movie == NULL)
    {
        printf("ERROR: malloc() failed.\n");
        exit(EXIT_FAILURE);
    }
    new_movie->next = NULL;

    printf("Input title and press Enter.\n");
    printf(">> ");
    int flag = scanf("%[^\n]%*c", new_movie->title);
    printf("Input rating and press Enter.\n");
    printf(">> ");
    flag = scanf("%f%*c", &new_movie->rating);

    //TODO: count
    //TODO: implement find last
    //TODO: find index
    //TODO: implement do all...(using function pointer)

    int count = 0;

    p_movie pnode = *p_head; /* set to start of list */

    if (pnode == NULL)
    {
        *p_head = new_movie;
    }
    else
    {
        while (pnode->next != NULL)
        {
            pnode = pnode->next;
            count++;
        }
        pnode->next = new_movie;
        count++;
    }

    printf("%d : \"%s\", %.1f.\n", count, new_movie->title, new_movie->rating);

}
unsigned int count_items(const p_movie head)
{
    unsigned int count = 0;
    p_movie pnode = head; /* set to start of list */
    while (pnode != NULL)
    { 
        pnode = pnode->next;
        count++;
    }
    return count;
}
void write_file(p_movie head)
{
    char filename[TSIZE] = { 0, };

    printf("Please input filename to write and press Enter.\n");
    printf(">> ");

    if (scanf("%[^\n]%*c", filename) != 1)
    {
        printf("Wrong input. Terminating.\n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("ERROR: Cannot open file.\n");
        exit(EXIT_FAILURE);
    }

    p_movie pnode = head;
    int count = 0;
    int num = count_items(head);
    fprintf(file, "%d\n", (int)num);

    while (pnode != NULL)
    {
        fprintf(file, "%s\n%.1f\n", pnode->title, pnode->rating);
        pnode = pnode->next;
        count++;
    }

    fclose(file);

    assert(count == (int)num);

    printf("%d items have been saved to the file.\n", num);
}
void edit_an_item(p_movie head)
{
    printf("Please input an index to edit and press Enter.\n");
    int index = input_int();
    int count = 0;
    p_movie pnode = head;

    while (pnode != NULL)
    {
        if (index == count) break;
        pnode = pnode->next;
        count++;
    }

    if (pnode != NULL)
    {
        printf("%d : \"%s\", %.1f.\n", count, pnode->title, pnode->rating);
        printf("Input new title and press Enter.\n");
        printf(">> ");
        int flag = scanf("%[^\n]%*c", pnode->title);
        printf("Input new rating and press Enter.\n");
        printf(">> ");
        flag = scanf("%f%*c", &pnode->rating);
        printf("%d : \"%s\", %.1f\n", count, pnode->title, pnode->rating);
    }
    else
    {
        printf("Invalid item.\n");
    }
}
void insert_an_item(p_movie* p_head)
{
    printf("Please input an index to insert and press Enter.\n");
    int index = input_int();
    
    p_movie new_movie = (p_movie)malloc(sizeof(struct movie));
    if (new_movie == NULL)
    {
        printf("ERROR: malloc() failed.\n");
        exit(EXIT_FAILURE);
    }
    new_movie->next = NULL;

    

    p_movie pnode = *p_head;
    p_movie prev = NULL;
    int count = 0;

    while (pnode != NULL)
    {
        if (index == count) break;
        else
        {
            prev = pnode;
            pnode = pnode->next;
            count++;
        }
    }

    printf("%d : \"%s\", %.1f.\n", count, pnode->title, pnode->rating);
    printf("Input new title and press Enter.\n");
    printf(">> ");
    int flag = scanf("%[^\n]%*c", pnode->title);
    printf("Input new rating and press Enter.\n");
    printf(">> ");
    flag = scanf("%f%*c", &pnode->rating);
    printf("%d : \"%s\", %.1f\n", count, pnode->title, pnode->rating);

    if (pnode == NULL)
    {
        pnode = new_movie;
    }
    else
    {
        prev = new_movie;
        new_movie->next = pnode;
    }
}