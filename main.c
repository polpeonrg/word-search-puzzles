//  main.c
//  Created on 4/9/2562 BE.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//Global
int array_01[12][12]={0};
char array_char[12][12];
char animal[][20]={"PANDA","TIGER","SHARK","SHEEP","GOOSE"}; //it's have 5 words but we used 3 words in this time.
int i,j,r,row,column,word=0;
int panda_column[5], panda_row; //word1 panda :x
int tiger_column, tiger_row[5],ori_column_tiger,new_column_tiger; //word2 tiger  :y
int shark_column[5], shark_row,ori_row_shark,new_row_shark; //word3 shark : x
//prototype
int answer_x (int word,char name[],int row,int column[],int ori_row);
int answer_y (int word,char name[],int row[],int column,int ori_column);
int panda(void);
int tiger(void);
int shark(void);
//main
int main()
{
    printf("Find : PANDA, TIGER, SHARK");
    //random
    srand((unsigned)time(NULL));
    for (i=0; i<12; ++i)
    {
        for (j=0; j<12; ++j)
            array_char[i][j]=rand()%26+65;
    }
    //vocabulary
    panda(); //word1 panda :x
    tiger(); //word2 tiger  :y
    shark(); //word3 shark : x

    //print game corssword
    printf("\n\n"); //print array char
    printf("\n\t\t+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    for (i=0; i<12; ++i)
    {
        printf("\t\t|");
        for (j=0; j<12; ++j)
            printf("%2c |",array_char[i][j]);
        printf("\n\t\t+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    }

    //print Answer
    printf("\n\t\tAnswer\nx:\n");
    answer_x(1,"PANDA", panda_row, panda_column,NULL); //panda
    answer_x(3,"SHARK", shark_row, shark_column,ori_row_shark); //shark

    printf("\ny:\n");
    answer_y(2, "TIGER", tiger_row, tiger_column, ori_column_tiger);//tiger

    printf("\n\n"); //print array 01
    printf("\n\t\t+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    for (i=0; i<12; ++i)
    {
        printf("\t\t|");
        for (j=0; j<12; ++j)
            printf("%2d |",array_01[i][j]);
        printf("\n\t\t+---+---+---+---+---+---+---+---+---+---+---+---+\n");
    }

    printf("\n");return 0;

}
//function

int panda(void)
{
    row = rand()%12;
    column = rand()%8;
    //row = 5;column=3; ///test
    for(j=0,r=0;j<5,r<5;++j,++r)
    {
        array_01[row][column+j]=1;
        array_char[row][column+j]=animal[word][r];
        panda_column[j]= column+j;
    }
    panda_row =row;
    ++word;
    return 0;
}

int tiger(void)
{
    row = rand()%8;
    column = rand()%12;
    //row=3;column=4; ///test
    ori_column_tiger = column;
    for(i=0;i<5;++i) //check
    {
        if (array_01[row+i][column]==1) //change
        {
            if(column>=6)
            {
                while (array_01[row+i][column]==1) //L
                {
                    column -= 1;
                }
            }
            else
            {
                while (array_01[row+i][column]==1) //R
                {
                    column += 1;
                }
            }
            new_column_tiger = column;
        }
    }
    if (column == ori_column_tiger) //not change
        new_column_tiger = ori_column_tiger;
    for(j=0,r=0;j<5,r<5;++j,++r)
    {
        array_01[row+j][new_column_tiger]=1;
        array_char[row+j][new_column_tiger]=animal[word][r];
        tiger_row[j]= row+j;
    }
    tiger_column = new_column_tiger;
    ++word;
    return 0;
}

int shark(void)
{
    int count_6up=0,count_5down=0;
    row = rand()%12;
    column = rand()%8;
   //row=5;column=5; ///test
    ori_row_shark = row;
    for (i=0; i<5; ++i) //chack
    {
        if (array_01[row][column+i]==1)
        {
        while (array_01[row][column+i]==1) //change
        {
            if(row>=6)
            {
                while (array_01[row][column+i]==1)
                {
                    row -= 1;
                }
                count_6up +=1;
                if (count_6up==3) //down again
                {
                    row -=1;
                    count_6up=0;
                }
            }
            else
            {
                while (array_01[row][column+i]==1)
                {
                    row += 1;
                }
                count_5down +=1;
                if (count_5down==3) //up again
                {
                    row+=1;
                    count_5down=0;
                }
            }
            new_row_shark = row;
        }
            i=0;
            continue;
        }
    }
    if (row == ori_row_shark)
        new_row_shark = ori_row_shark;
    for(j=0,r=0;j<5,r<5;++j,++r)
    {
        array_01[new_row_shark][column+j]=1;
        array_char[new_row_shark][column+j]=animal[word][r];
        shark_column[j]= column+j;
    }
    shark_row = new_row_shark;
    ++word;
    return 0;
}


int answer_x (int word_answer,char name[],int row,int column[],int ori_row)
{
    printf("\nWord %d\n",word_answer);
    printf("\tRow of %s is %d and ",name,row+1);
    printf("column is between %d and %d",column[0]+1,column[4]+1);
    if (word_answer>1)
        printf("\n\t\t(ori row %s %d )",name,ori_row+1);
    return 0;
}

int answer_y (int word_answer,char name[],int row[],int column,int ori_column)
{
    printf("\nWord %d\n",word_answer);
    printf("\tColumn of %s is %d and ",name,column+1);
    printf("row is between %d and %d",row[0]+1,row[4]+1);
    printf("\n\t\t(ori column %s %d )",name,ori_column+1);
    return 0;
}


