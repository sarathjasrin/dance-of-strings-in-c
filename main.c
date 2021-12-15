#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lib.h"
#include "str_logic.h"

int show_menu()
{
    printf("t - Text-Statistik\n");
    printf("s - Zwei Sätze vertauschen\n");
    printf("c - Zwei Sätze verketten\n");
    printf("p - Text mit Zeilennummer ausgeben\n");
    printf("o - Text ohne Zeilennummer ausgeben\n");
    printf("e - Programm beenden\n\n");
    printf("Ihre Wahl: ");
    return 1;
}

bool check_choice(char t[])
{
    return str_compare(t,"t") || str_compare(t,"s") || str_compare(t,"c") || str_compare(t,"p") || str_compare(t,"o") || str_compare(t,"e");
}

char *show_result(char text[],char sentance[],char finalstr[])
{
    int sentance_length=get_sentance(sentance);

    if(sentance_length)
    {
        if(str_compare(text,"t"))
        {
            text_statistics(finalstr);
            return finalstr;
        }
        else if(str_compare(text,"s")) //swap
        {
            sentance_length=get_sentance(finalstr); //calculating sentence length again because. it may updated by other operations
            if(sentance_length > 1)
            {
                int n1,n2,get_n1=1,get_n2=1;
                while(get_n1==1)
                {
                    printf("\nNummer des ersten Satzes: \n");
                    n1=get_int();
                    if(n1<=sentance_length && n1>0)  //should not greater than the sentence length
                    {
                        get_n1=0;
                    }
                    else
                    {
                        get_n1=1;
                    }
                }

                while(get_n2==1)
                {
                    printf("\nNummer des zweiten Satzes: \n");
                    n2=get_int();
                    if(n2>sentance_length || n2<=0 || n2==n1)  //should not greater than the sentence length
                    {
                        get_n2=1;
                    }
                    else
                    {
                        get_n2=0;
                    }
                }


                //convert string to array of string(sentence)
                char **arr=(char **)malloc(sizeof*arr*sentance_length);
                str_to_arr(finalstr,arr);
                char *new_str=str_swap(arr,n1,n2,sentance_length);
                return new_str;
            }
            else
            {
                printf("Nur noch ein Satz vorhanden!\n");
                return finalstr;
            }
        }
        else if(str_compare(text,"c")) //concat
        {
            sentance_length=get_sentance(finalstr); //calculating sentence length again because. it may updated by other operations
            if(sentance_length > 1)
            {
                int n1,n2,get_n1=1,get_n2=1;
                while(get_n1==1)
                {
                    printf("\nNummer des ersten Satzes: \n");
                    n1=get_int();
                    if(n1<=sentance_length && n1>0)  //should not greater than the sentence length
                    {
                        get_n1=0;
                    }
                    else
                    {
                        get_n1=1;
                    }
                }

                while(get_n2==1)
                {
                    printf("\nNummer des zweiten Satzes: \n");
                    n2=get_int();
                    if(n2>sentance_length || n2<=0 || n2==n1)  //should not greater than the sentence length
                    {
                        get_n2=1;
                    }
                    else
                    {
                        get_n2=0;
                    }
                }

                //convert string to array of string(sentence)
                char **arr=(char **)malloc(sizeof*arr*sentance_length);
                str_to_arr(finalstr,arr);
                char *new_str=str_concat(arr,n1,n2,sentance_length);
                return new_str;
            }
            else
            {
                printf("Nur noch ein Satz vorhanden!\n");
                return finalstr;
            }
        }
        else if(str_compare(text,"p"))
        {
            sentance_length=get_sentance(finalstr);
            //convert string to array of string(sentence)
            char **arr=(char **)malloc(sizeof*arr*sentance_length);
            str_to_arr(finalstr,arr);
            print_table(arr,sentance_length);
            return finalstr;
        }
        else if(str_compare(text,"o"))
        {
            printf("%s\n\n",finalstr);
            return finalstr;
        }
        else if(str_compare(text,"e"))
        {
            printf("Programm beenden\n");
            return finalstr;
        }
    }
    else
    {
        printf("Kein Satz gefunden!\n");
        return finalstr;
    }
    return finalstr;
}

void menu_choice(bool menu, char sentance[])
{
    char *finalstr=(char*)malloc((str_len(sentance)+1)*sizeof(char));
    str_cpy(sentance,finalstr);

    while(menu==true)
    {
        char *option=read_stdin();
        if(str_len(option)==1 && check_choice(option))
        {
            char * updated_str=show_result(option,sentance,finalstr);
            str_cpy(updated_str,finalstr);
            if(!str_compare(option,"e"))
            {
                show_menu();
            }
            else
            {
                menu=false;
            }
        }
        else
        {
            show_menu();
        }
    }
}

int main()
{
    bool menu=true;
    printf("Bitte Text eingeben:\n");
    char *sentance = read_stdin();
    int str_length=strlen(sentance);
    if(str_length!=0)
    {
        if(!is_special(sentance[str_length-1])) //check sentence end
        {
            printf("Der Text endet ohne Satzzeichen!\n");
            return 2;
        }
        else
        {
            int sentance_length=get_sentance(sentance);
            if(sentance_length) //check sentence length
            {
                show_menu();
                menu_choice(menu,sentance);
            }
            else
            {
                printf("Kein Satz gefunden!\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Leerer Eingang \n");
    }
    free(sentance);

    return 0;
}

