#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>///
#define MAX 50
///Khuffash


typedef struct //struct for data
{
    char name[MAX];
    int credit_hours;
    char code[MAX];
    char department[MAX];
    ///
    char topics[500];
    ///

} course;


struct node
{
    struct node *left;
    course course_leaf;
    struct node *right;
    int height;
};

struct node *tree=NULL; ///tree root , key = course code ;
struct node *Tree_names=NULL;/// tree root, key= course name

///FUNCTIONS
struct node *Make_Empty(struct node *T)//will make the tree empty
{
    if(T != NULL )
    {
        Make_Empty(T->left);//recursion to traverse the tree
        Make_Empty(T->right);
        free(T);
    }
    return NULL;
};

int Height(struct node *P ) //returns the height of the node
{
    if( P == NULL )
        return -1;
    else
        return P->height;
}

int Max( int Lhs, int Rhs )//compares between two numbers
{
    return Lhs > Rhs ? Lhs : Rhs;//if lhs>rhs , return lhs, else return rhs.. ///linux syntax.
}

struct node *Single_rotate_left(struct node *k2)//rotations for insert function
{
    struct node *k1;

    k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;

    k2->height=Max(Height(k2->left),Height(k2->right))+1;//this to change the hight after inserstion
    k1->height=Max(Height(k1->left),Height(k1->right))+1;

    return k1;

};

struct node *single_rotate_right(struct node *k1)
{
    struct node *k2;

    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;


    k1->height=Max(Height(k1->left),Height(k1->right))+1;
    k2->height=Max(Height(k2->right),k1->height)+1;

    return k2;
};

struct node *Double_rotate_left(struct node *k3)
{
    k3->left=single_rotate_right(k3->left); //rotate k1-k2

    return Single_rotate_left(k3); //rotat k3-k2
};

struct node *Double_rotate_right(struct node *k1)
{
    k1->right=Single_rotate_left(k1->right);//rotate k3-k2

    return single_rotate_right(k1); //rotate k1-k2
};

int getBalance(struct node *N) //returns the balance of a node
{
    if(N==NULL)
        return 0;
    return Height(N->left) - Height(N->right);
}

struct node *Find_min(struct node *T)//returns the most left node,MIN
{
    if(T==NULL)
        return NULL;
    else if (T->left==NULL)
        return T;
    else
        return Find_min(T->left);
};

struct node *Find_max(struct node *T)//return the most right node,MAX
{
    if(T==NULL)
        return NULL;
    else if (T->right==NULL)
        return T;
    else
        return Find_max(T->right);
};

struct node *Insert(course data,struct node *T)//insert function
{
    if(T==NULL)//create the tree
    {
        T=(struct node *)malloc(sizeof(struct node));
        if(T==NULL) printf("Out of Space"); //after malloc'ing if its still null, then no space available;
        else
        {
            T->course_leaf=data;
            T->height=0;
            T->left=NULL;
            T->right=NULL;
        }
    }
    else if ((strcmp(data.code,T->course_leaf.code))==-1)//go to left data is less than the root.
    {
        T->left=Insert(data,T->left);
        if((Height(T->left)-Height(T->right))==2)
        {
            if((strcmp(data.code,T->left->course_leaf.code))==-1)
                T=Single_rotate_left(T);
            else
                T=Double_rotate_left(T);
        }
    }
    else if ((strcmp(data.code,T->course_leaf.code))==1)//go to left data is less than the root.
    {
        T->right=Insert(data,T->right);
        if((Height(T->right)-Height(T->left))==2)
        {
            if((strcmp(data.code,T->right->course_leaf.code))==-1)
                T=single_rotate_right(T);
            else
                T=Double_rotate_right(T);
        }
    }

    T->height=Max(Height(T->left),Height(T->right))+1;
    return T;
};

struct node *Find_code(char data[],struct node *T)//traverse the tree till it finds a  node that has a code =data;
{
    if(T==NULL)
        return NULL;
    if((strcmp(data,T->course_leaf.code))==-1)
        return Find_code(data,T->left);
    else if ((strcmp(data,T->course_leaf.code))==1)
        return Find_code(data,T->right);
    else
        return T;

};

void Display_in_order(struct node *T)//displaying courses in inorder way
{
    if(T != NULL)
    {
        Display_in_order(T->left);
        printf("%-25s\t\t%d\t\t%-20s\t%-20s\n",T->course_leaf.name,T->course_leaf.credit_hours,T->course_leaf.code,T->course_leaf.department);
        Display_in_order(T->right);
    }
}

void Display_in_order_topics(struct node *T)
{
    if(T!=NULL)
    {
        Display_in_order_topics(T->left);
        printf("Topics for Course \" %s \": %s\n",T->course_leaf.name,T->course_leaf.topics);
        Display_in_order_topics(T->right);

    }
}

void Display_in_order_department(char data[],struct node *T)//displaying the courses which are in the given department
{
    if(T != NULL)
    {

        Display_in_order_department(data,T->left);
        if(strcasecmp(T->course_leaf.department,data)==0)
        {
            printf("%-25s\t\t%d\t\t%-20s\t%-20s\n",T->course_leaf.name,T->course_leaf.credit_hours,T->course_leaf.code,T->course_leaf.department);
        }
        Display_in_order_department(data,T->right);

    }
}

struct node *Right_Rotate(struct node *y)//rotation for delete only.
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = Max(Height(y->left), Height(y->right))+1;
    x->height = Max(Height(x->left), Height(x->right))+1;

    // Return new root
    return x;
}

struct node *Left_Rotate(struct node *x)//for delete only.
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = Max(Height(x->left), Height(x->right))+1;
    y->height = Max(Height(y->left), Height(y->right))+1;

    // Return new root
    return y;
}

struct node *Delete(struct node *T,char key[])//delete node that has the same code given by user.
{
    if(T==NULL)
        return T;

    if(strcmp(key,T->course_leaf.code)==-1) //the key is less than the root
        T->left=Delete(T->left,key);
    else if(strcmp(key,T->course_leaf.code)==1)//the key is grater than the root
        T->right=Delete(T->right,key);
    else
    {
        if((T->left==NULL) || (T->right==NULL)) //one child or no children
        {
            struct node *temp=T->left ? T->left :T->right; //if T->left == null , then take T->right.. '''unixxxx

            //no children
            if(temp==NULL)
            {
                temp=T;
                T=NULL;
            }
            else //one child
                *T=*temp;

            free(temp);
        }
        else
        {
            struct node *temp=Find_min(T->right);
            strcpy(T->course_leaf.code,temp->course_leaf.code);
            T->right=Delete(T->right,temp->course_leaf.code);
        }

    }

    if(T==NULL)
        return T;

    T->height=1+ Max(Height(T->left),Height(T->right));

    int balance= getBalance(T);

    //left -left
    if(balance>1 && getBalance(T->left)>=0)
    {
       return Right_Rotate(T);
    }

    //left - right
    if(balance >1 && getBalance(T->left)<0)
    {
        T->left=Left_Rotate(T->left);
        return Right_Rotate(T);
    }
    //right-right
    if(balance <-1 && getBalance(T->right)<= 0)
    {
        return Left_Rotate(T);
    }

    //right-left
    if(balance < -1 && getBalance(T->right)>0)
    {
        T->right=Right_Rotate(T->right);
        return Left_Rotate(T);
    }
    return T;
};

void Delete_department(char data[],struct node *T)//deleting all course which in the same department
{
    if(T != NULL)
    {//recurssion to traverse the tree, INORDER
        Delete_department(data,T->left);
        if(strcasecmp(T->course_leaf.department,data)==0) //strcasecmp , compare -> NO case sensitive;
        {
            printf("\n%s\n",T->course_leaf.name);
            //tree= Delete(tree,T->course_leaf.code);
        }
        Delete_department(data,T->right);
    }

}

void Delete_specefic(char data,struct node *T)//deleting the courses that start with same letter given by user
{
    if(T != NULL)
    {

        Delete_specefic(data,T->left);
        if(T->course_leaf.name[0]==data)
        {
            tree=Delete(tree,T->course_leaf.code);
        }
        Delete_specefic(data,T->right);
    }

}

void Delete_specefic_names(char data,struct node *T)//same as above but will do for tree->key:name
{
    if(T != NULL)
    {

        Delete_specefic(data,T->left);
        if(T->course_leaf.name[0]==data)
        {
            Tree_names=Delete(tree,T->course_leaf.code);
        }
        Delete_specefic(data,T->right);
    }

}

void Delete_department_names(char data[],struct node *T)
{
    if(T != NULL)
    {

        Delete_department_names(data,T->left);
        if(strcasecmp(T->course_leaf.department,data)==0)
        {
            Tree_names= Delete(tree,T->course_leaf.code);
        }
        Delete_department_names(data,T->right);
    }

}

struct node  *Insert_names(course data,struct node *T)//making new tree , KEY -> course Name
{
    if(T==NULL)//create the tree
    {
        T=(struct node *)malloc(sizeof(struct node));
        if(T==NULL) printf("Out of Space"); //after malloc'ing if its still null, then no space available;
        else
        {
            T->course_leaf=data;
            T->height=0;
            T->left=NULL;
            T->right=NULL;
        }
    }
    else if ((strcmp(data.name,T->course_leaf.name))==-1)//go to left data is less than the root.
    {
        T->left=Insert(data,T->left);
        if((Height(T->left)-Height(T->right))==2)
        {
            if((strcmp(data.name,T->left->course_leaf.name))==-1)
                T=Single_rotate_left(T);
            else
                T=Double_rotate_left(T);
        }
    }
    else if ((strcmp(data.name,T->course_leaf.name))==1)//go to left data is less than the root.
    {
        T->right=Insert(data,T->right);
        if((Height(T->right)-Height(T->left))==2)
        {
            if((strcmp(data.name,T->right->course_leaf.name))==-1)
                T=single_rotate_right(T);
            else
                T=Double_rotate_right(T);
        }
    }

    T->height=Max(Height(T->left),Height(T->right))+1;
    return T;
};


void ToprintNames(struct node *T) //will traverse the code (tree) and insert every node to another tree (Tree_names)
{
    if(T!=NULL)
    {
        ToprintNames(T->left);
        Tree_names=Insert_names(T->course_leaf,Tree_names);
        ToprintNames(T->right);
    }

}

void Display_in_order_file(struct node *T,FILE *f)//to print in file
{
    if(T != NULL)
    {
        Display_in_order_file(T->left,f);
        fprintf(f,"%s:%d#%s#%s/%s\n",T->course_leaf.name,T->course_leaf.credit_hours,T->course_leaf.code,T->course_leaf.department,T->course_leaf.topics);
        Display_in_order_file(T->right,f);
    }
}

void sys();
int main()
{
    sys();
    FILE *courses_file;
    courses_file=fopen("courses.txt","r");

    tree=Make_Empty(tree);

///USED VARIABLES ///
    course tempc;
    struct node *tempt;
    char c;
    char code[25];
    int flag=0;
    char dep[25];
    course c1;
    int count = 0;

    while(1)
    {
        printf("1. Read the file courses.txt file and create the tree\n");
        printf("2. Insert a new course from the user with all its associated data.\n");
        printf("3. Find a course and support updating of its information.\n");
        printf("4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics).\n");
        printf("5. List all topics associated with a given course.\n");
        printf("6. List all courses in lexicographic order that belong to the same department.\n");
        printf("7. Delete a course.\n");
        printf("8. Delete all courses that start with a specific letter.\n");
        printf("9. Delete all courses belong to a given department.\n");
        printf("10.Save in File and Close\n");

        int choice;
        printf("Please Enter Your Choise: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case (1):
            system("cls");
            if(!courses_file) printf("Error-File not Found");//checks if the file exists or not.

            char course_info[5000];

            while(!feof(courses_file))
            {
                course temp_course;

                fgets(course_info,500,courses_file);

                int *cutter=strtok(course_info,":#/\n"); //reading the course name
                strcpy(temp_course.name,cutter);

                cutter=strtok(NULL,":#/\n");//reading the course hours;
                temp_course.credit_hours=atoi(cutter);

                cutter=strtok(NULL,":#/\n"); //reading the course code
                strcpy(temp_course.code,cutter);

                cutter=strtok(NULL,":#/\n");//reading the course department
                strcpy(temp_course.department,cutter);

                cutter=strtok(NULL,":#/\n"); //reading the course topics

                strcpy(temp_course.topics,cutter);


                tree=Insert(temp_course,tree);

            }
            ToprintNames(tree);//to make the other tree / names tree


            printf("\nFile Loaded,Data Inserted!\n");
            break;

        case(2):
            system("cls");
            printf("Enter A Course Name: ");
            scanf("%c",&c);
            gets(tempc.name);

            printf("Enter The Credit Hours: ");
            scanf("%d",&tempc.credit_hours);

            printf("Enter The Code: ");
            scanf("%c",&c);
            strupr(gets(tempc.code));

            printf("Enter The Department:  ");
            //scanf("%c",&c);
            gets(tempc.department);

            printf("Enter the Topic: ");
            //scanf("%c",&c);
            gets(tempc.topics);

            tree=Insert(tempc,tree);
            Tree_names=Insert(tempc,Tree_names);
            printf("Course Added!\n");
            break;

        case(3):
            system("cls");
            printf("Please enter the code of the Course: ");
            scanf("%c",&c);
            tempt=Find_code(strupr(gets(code)),tree);

            if(tempt!=NULL)
            {
                printf("%-25s\t\t%d\t\t%-25s\t\t%-25s\n",tempt->course_leaf.name,tempt->course_leaf.credit_hours,tempt->course_leaf.code,tempt->course_leaf.department);
                while(1)
                {
                    printf("Course Found, Hence Choose what u want to update:\n");
                    printf("1. Course Name \n");
                    printf("2. Credit Hours\n");
                    printf("3. Code \n");
                    printf("4. Department\n");
                    printf("5. Topics\n");
                    printf("6. Return to main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d",&choice);

                    switch(choice)
                    {
                    case 1:
                        printf("\nEnter A new Name: ");
                        scanf("%c",&c);
                        gets(tempt->course_leaf.name);
                        flag=0;
                        break;

                    case 2:
                        printf("\nEnter New Credit Hours: ");
                        scanf("%d",&tempt->course_leaf.credit_hours);
                        flag=0;
                        break;

                    case 3:
                        ///delete->insert again.
                        c1=tempt->course_leaf;
                        tree=Delete(tree,tempt->course_leaf.code);

                        printf("\nEnter A new code: ");
                        scanf("%c",&c);
                        strupr(gets(code));

                        while(Find_code(code,tree)!=NULL) //checks if the entered code already exists or not
                        {
                          system("color 4");
                          printf("Code Already exists- Please Re Enter Again:\n");
                          strupr(gets(code));

                        }
                        system("color a");

                        strcpy(c1.code,code);
                        tree=Insert(c1,tree);

                        flag=0;
                        break;

                    case 4:
                        printf("\nEnter A new Department: ");
                        scanf("%c",&c);
                        gets(tempt->course_leaf.department);
                        flag=0;
                        break;

                    case 5:
                        printf("Enter New Topics: ',' separates them\n");
                        scanf("%c",&c);
                        gets(tempt->course_leaf.topics);

                        flag=0;
                        break;

                    case 6:
                        flag=1;
                        break;
                    }
            if(flag)
                {
                system("cls");
                break;
                }

                }

            }
            else
                printf("Course Not Found!\n");

            tempt=NULL;

            break;

        case(4):
            system("cls");

            int choice_sh;
            printf("To print the courses lexicographic order according To\n1. Course Code\n2. Course Name\n");//the user have the choice to print any tree he wants
            scanf("%d",&choice_sh);
            system("cls");

            printf("Course Name\t\t\t Credit Hours\t\tCourse Code\t            Department\n");
            if(choice_sh==1)
            {
                Display_in_order(tree);
                Display_in_order_topics(tree);
            }
            else
            {
                Display_in_order(Tree_names);
                Display_in_order_topics(Tree_names);
            }
            break;

        case(5):
            system("cls");
            printf("Please enter the code of the Course: ");
            scanf("%c",&c);
            tempt=Find_code(strupr(gets(code)),tree);

            printf("Topics for course * %s * Are : %s .",tempt->course_leaf.name,tempt->course_leaf.topics);
            break;

        case(6):
            system("cls");
            printf("Please Enter the department u want to display It's courses: ");
            scanf("%c",&c);
            gets(dep);

            int choice_sh1;
            printf("To print the Courses lexicographic order according To\n1. Course Code\n2. Course Name\n");
            scanf("%d",&choice_sh1);
            system("cls");

            printf("Course Name\t\t\t Credit Hours\t\tCourse Code\t            Department\n");
            if(choice_sh1==1)
            {
                Display_in_order_department(dep,tree);
            }
            else
            {
                Display_in_order_department(dep,Tree_names);
            }

            break;

        case(7):
            system("cls");
            printf("Please enter the code of the Course: ");
            scanf("%c",&c);
            strupr(gets(code));

            if(Find_code(code,tree)!=NULL)
                printf("\nDeleted successfully!!\n");
            else
                printf("\nCourse Not Found!\n");

            tree=Delete(tree,code);
            Tree_names=tree;

            break;

        case(8):
            system("cls");
            printf("Please Enter A Letter to delete the courses that starts with: ");
            scanf("%c",&c);
            scanf("%c",&c);

            Delete_specefic(toupper(c),tree);
            Delete_specefic_names(toupper(c),Tree_names);

            break;

        case(9):
            system("cls");
            printf("Please Enter the department u want to Delete It's courses: ");
            scanf("%c",&c);
            gets(dep);

            Delete_department(dep,tree);
            Delete_department_names(dep,Tree_names);

            break;

        case(10):
            fclose(courses_file);
            courses_file=fopen("courses.txt","w");
            Display_in_order_file(tree,courses_file);
            fclose(courses_file);
            printf("\nThanks for ur time!\nData Saved!\n");
            return;
            break;

        default:
            printf("WRONG CHOICE-REENTER\n");

        }
        printf("\n\n");

    }

    return 0;
}
void sys()
{
    system("color a");
    system("title Khuffash");
}



