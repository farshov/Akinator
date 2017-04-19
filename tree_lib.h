#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
const int MAX_SIZE_  = 300;
const int BUF_SIZE_ = 300;

class Tree
{
public:
    Tree();
    explicit Tree(char * str);
    ~Tree();
    void Add_left(Tree * new_left);
    void Add_right(Tree * new_right);
    void Print_tree();
    void Read_tree(char * buffer);
    void Write_tree(FILE * output);
    void Print_data();
    void Print_question();
    void test1();
    Tree * Make_tree();
    Tree * Add_tree();
    Tree * Return_left_child();
    Tree * Return_right_child();

private:
    void Delete_tree();
    char * data_;
    Tree * left_;
    Tree * right_;
};

void Tree::Write_tree(FILE * output)
{
    fprintf(output, "%c", '(');
    fprintf(output, "\"%s\"", data_);
    if(left_ != NULL)
    {
        left_ -> Write_tree(output);
    }
    else
    {
        fprintf(output, "%s", "(\"X\")");
    }
    if(right_ != NULL)
    {
        right_ -> Write_tree(output);
    }
    else
    {
        fprintf(output, "%s", "(\"X\")");
    }
    fprintf(output, "%c", ')');
}

Tree::Tree():
    data_(new char[MAX_SIZE_]),
    left_(NULL),
    right_(NULL)
    {
    }

Tree::Tree(char * str):
    data_(new char[MAX_SIZE_]),
    left_(NULL),
    right_(NULL)
    {
        strncpy(data_, str, MAX_SIZE_ - 1);
    }

Tree::~Tree()
{
    Delete_tree();
}

void Tree::Delete_tree()
{
    if(left_ != NULL)
    {
        left_->Delete_tree();
        left_ = NULL;
    }
    if(right_ != NULL)
    {
        right_->Delete_tree();
        right_ = NULL;
    }
    delete data_;
    delete this;
}

void Tree::Add_left(Tree * new_left)
{
    left_ = new_left;
    new_left->left_ = NULL;
    new_left->right_ = NULL;
}

void Tree::Add_right(Tree * new_right)
{
    right_ = new_right;
    new_right->left_ = NULL;
    new_right->right_ = NULL;
}

void Tree::Print_tree()
{
    if(this != NULL)
    {
        printf("%s\n", data_);
        left_->Print_tree();
        right_->Print_tree();
    }
}

void Tree::Print_question()
{
    printf("%s?\n", data_);
}

Tree * Tree::Return_left_child()
{
    return left_;
}
Tree * Tree::Return_right_child()
{
    return right_;
}

void Tree::Print_data()
{
    printf("%s", data_);
}

Tree * Tree::Add_tree()
{
    Tree * tree(new Tree);
    int i = 0;
    size_t len = 0;
    char buffer[BUF_SIZE_] = {};
    char cur = 0;
    cur = getchar();
    if(cur == '\n')
    {
        i = 0;
    }
    else
    {
        buffer[0] = cur;
        i = 1;
    }
    fgets(buffer + i, BUF_SIZE_, stdin);
    len = strlen(buffer);
    buffer[len - 1] = '\0';
    strcpy(tree->data_, buffer);
    return tree;
}

void Tree::Read_tree(char * str)
{

    static bool ttt = 1;
    static int num = 0;
    //printf("num  %d\n", num);
    size_t i = 0;
    char cur = 0;
    char buffer[BUF_SIZE_] = {};
    if((cur = str[num]) == '(')
    {
        cur = str[++num];
        while((cur = str[++num]) != '"')
            {
                buffer[i] = cur;
                i++;
            }
        buffer[i] = '\0';
        if(strncmp(buffer, "X", 2))
        {
            strncpy(data_, buffer, MAX_SIZE_ - 1);
            if((cur = str[++num]) == '(')
            {
                Tree * left_child(new Tree);
                left_ = left_child;
                left_child->Read_tree(str);
                if(ttt == 0)
                {
                    left_ = NULL;
                    ttt = 1;
                }
            }
            if((cur = str[++num]) == '(')
            {
                Tree * right_child(new Tree);
                right_ = right_child;
                right_child->Read_tree(str);
                if(ttt == 0)
                {
                    right_ = NULL;
                    ttt = 1;
                }
            }
        }
        else
        {
            ttt = 0;
        }
        if(cur = str[++num] == ')')
        {
            return;
        }
        else
        {
            assert(0 && "INCORRECT FILE BECAUSE OF )");
            printf("fail2");
        }
    }
    else
    {
        assert(0 && "INCORRECT FILE BECAUSE OF (");
        printf("fail");
    }
}
