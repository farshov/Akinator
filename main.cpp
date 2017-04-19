#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree_lib.h"
const int SIZE_ANSWER = 301;

void launch(Tree * tree);
char * copy_file(FILE * file);
bool check_answer();
inline void new_(Tree * tree);

int main()
{
    Tree * tree(new Tree);
    FILE * file = fopen("file.txt", "r+w");
    char * buffer = NULL;
    buffer = copy_file(file);
    fseek(file, 0, SEEK_SET);
    tree->Read_tree(buffer);
    printf("Hello, user\n");
    launch(tree);
    tree->Write_tree(file);
    fclose(file);
    delete buffer;
    return 0;
}

bool check_answer()
{
    char answer[SIZE_ANSWER] = "";
    int i = 0;
    size_t len = 0;
    fgets(answer, SIZE_ANSWER, stdin);
    len = strlen(answer);
    answer[len - 1] = '\0';
    while(strncmp(answer, "yes", 3) && strncmp(answer, "Yes", 3) && strncmp(answer, "YES", 3) && strncmp(answer, "yeah", 4) && strncmp(answer, "Yeah", 3) &&
    strncmp(answer, "YEAH", 4) && strncmp(answer, "No", 2) && strncmp(answer, "no", 2) && strncmp(answer, "NO", 2))
    {
        printf("Please, repeat your answer\n");
        fgets(answer, SIZE_ANSWER, stdin);
        len = strlen(answer);
        answer[len - 1] = '\0';
    }
    if(!strncmp(answer, "yes", 3) || !strncmp(answer, "Yes", 3) || !strncmp(answer, "YES", 3))
    {
        return 1;
    }
    else if(!strncmp(answer, "NO", 2) || !strncmp(answer, "no", 2) || !strncmp(answer, "No", 2))
    {
        return 0;
    }
}

void launch(Tree * tree)
{
    static int level = 0;
    bool answer = 0;
    Tree * new_obj = NULL;
    Tree * new_about = NULL;
    Tree * left = tree->Return_left_child();
    Tree * right = tree->Return_right_child();
    level++;
    tree->Print_question();
    answer = check_answer();
    if(answer)
    {
        if(left->Return_left_child() != NULL && left->Return_right_child() != NULL)
        {
            launch(left);
        }
        else
        {
            printf("Is is ");
            left->Print_data();
            printf("?\n");
            answer = check_answer();
            if(answer)
            {
                printf("!!!Nice job!!!\n");
            }
            else if(!answer)
            {
                printf("What is it?\n");
                new_obj = left->Add_tree();
                printf("What is the difference between ");
                new_obj->Print_data();
                printf(" and ");
                left->Print_data();
                printf("?\n");
                new_about = left->Add_tree();
                tree->Add_left(new_about);
                new_about->Add_left(new_obj);
                new_about->Add_right(left);
                printf("Thanks for new object\n\n");
            }
        }
    }
    else if(!answer)
    {
        if(right->Return_left_child() != NULL && right->Return_right_child() != NULL)
        {
            launch(right);
        }
        else
        {
            printf("Is is ");
            right->Print_data();
            printf("?\n");
            answer = check_answer();
            if(answer)
            {
                printf("!!!Nice job!!!\n");
            }
            else if(!answer)
            {
                printf("What is it?\n");
                new_obj = right->Add_tree();
                printf("What is the difference between ");
                new_obj->Print_data();
                printf(" and ");
                right->Print_data();
                printf("?\n");
                new_about = right->Add_tree();
                tree->Add_right(new_about);
                new_about->Add_left(new_obj);
                new_about->Add_right(right);
                printf("Thanks for new object\n");
            }
        }
    }
    level--;
    if(level == 0)
    {
        printf("Do you want play again?\n");
        answer = check_answer();
        if(answer)
        {
            launch(tree);
        }
        else
        {
            printf("Good bye:)\n");
        }
    }
    
}


char * copy_file(FILE * file)
{
    int length = 0;
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char * buffer = new char[length];
    fread(buffer, sizeof(char), length, file);
    buffer[length ] = '\0';
    return buffer;
}