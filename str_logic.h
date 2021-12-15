#ifndef STR_LOGIC_H_INCLUDED
#define STR_LOGIC_H_INCLUDED

#include "lib.h"
#define MAX 100
int is_special(char str);
int get_sentance(char str[]);

int char_comp(char a,char b)
{
    return a==b;
}

void text_statistics(char str[])
{
    int i=0,uppercase=0,lowercase=0,chars=0,totlchars=0;
    while(str[i]!='\0')
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            if(str[i]>='A' && str[i]<='Z')
                uppercase++;
            else
                lowercase++;

            chars++;
        }

        if(!char_comp(str[i],' '))
        {
            totlchars++;
        }
        i++;
    }

    int s=get_sentance(str);

    printf("%i Sätze, %i Zeichen\n",s,totlchars);
    printf("%i Buchstaben (%i Großbuchstaben, %i Kleinbuchstaben)\n\n",chars,uppercase,lowercase);
}

int get_sentance(char str[])
{
    int s=0;
    for(int i=0; str[i]!='\0'; i++)
    {
        if(is_special(str[i]))
        {
            s++;
        }
    }
    return s;
}


void str_to_arr(char a[],char **b)
{
    int i=0,j=0,length=str_len(a),sentance_length=get_sentance(a),k=0;
    for(i=0; i<sentance_length; i++)
    {
        b[i]=(char *)malloc(sizeof *b * (length+1));
        int n=0;
        for(j=k; j<length; j++)
        {
            b[i][n]=a[j];

            n++;
            k++;
            if(is_special(a[j]))
            {
                b[i][n]='\0';
                break;
            }

        }
    }
}

int is_special(char str)
{
    return char_comp(str,'?') || char_comp(str,'.') || char_comp(str,'!');
}

void print_table(char **arr,size_t len)
{
    char *row1[] = {"Nr.", "Satz"};
    int **col1=(int **)malloc(len*sizeof(int));
    for(int i=0; i<=len; i++)
    {
        col1[i]=(int *)malloc(sizeof(int));
        col1[i]=(int)i+1;
    }

    printf("\n\n");
    printf("%*s| %*s\n", -2, row1[0], -MAX, row1[1]);
    printf("%*c + %*c\n", -2, '-', -MAX, '-');
    for (int i = 0; i < len; ++i)
    {
        printf("%-2d | %-10s\n", col1[i], arr[i]);
    }
    printf("\n\n");
}

char *str_concat(char **arr,int n1,int n2,int sentance_length)
{
    char *concat_str=(char *)malloc(MAX*sizeof(char));
    int cap=MAX,index=0;
    n1-=1;
    n2-=1;
    for(int i=0; i<sentance_length; i++)
    {
        if(n2!=i)  //skip second sentence
        {
            for(int k=0; k<str_len(arr[i]); k++)
            {
                char ch=arr[i][k];
                if(n1==i && is_special(ch)) //check for special chars if yes then don't include
                {
                    concat_str = realloc(concat_str, (cap *= 2) * sizeof (char));
                    concat_str[index]='\0';
                    str_append(concat_str," und ");
                    str_append(concat_str,arr[n2]);
                    index=(str_len(concat_str))-1;
                }
                else
                {
                    concat_str[index]=ch;
                }

                if (++index == cap)
                {
                    /* Make the output buffer twice its current size */
                    concat_str = realloc(concat_str, (cap *= 2) * sizeof (char));
                }
            }
        }
    }
    concat_str[index]='\0';
    return concat_str;
}

char * str_swap(char **arr,int n1,int n2,int sentance_length)
{
    char *swap_str=(char *)malloc(MAX*sizeof(char));
    int cap=MAX,index=0;
    n1-=1;
    n2-=1;
    for(int i=0; i<sentance_length; i++)
    {
        if(n1==i)  //if n1 sentence then read n2
        {
            for(int k=0; k<str_len(arr[n2]); k++)
            {
                char ch=arr[n2][k];
                swap_str[index]=ch;

                if (++index == cap)
                {
                    /* Make the output buffer twice its current size */
                    swap_str = realloc(swap_str, (cap *= 2) * sizeof (char));
                }
            }
        }
        else if(n2==i)
        {
            for(int k=0; k<str_len(arr[n1]); k++)
            {
                char ch=arr[n1][k];
                swap_str[index]=ch;

                if (++index == cap)
                {
                    /* Make the output buffer twice its current size */
                    swap_str = realloc(swap_str, (cap *= 2) * sizeof (char));
                }
            }
        }
        else
        {
            for(int k=0; k<str_len(arr[i]); k++)
            {
                char ch=arr[i][k];
                swap_str[index]=ch;

                if (++index == cap)
                {
                    /* Make the output buffer twice its current size */
                    swap_str = realloc(swap_str, (cap *= 2) * sizeof (char));
                }
            }
        }
    }
    swap_str[index]='\0';
    return swap_str;
}

#endif // STR_LOGIC_H_INCLUDED
