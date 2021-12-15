#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#define MAXINPUT 150
int read_input(char str[])
{
    int ch,i=0;
    while((ch=getchar())!='\n')
    {
        str[i++]=ch;
    }

    str[i]='\0';
    return i;
}

int get_int()
{
    char buf[MAXINPUT];
    int val;
    fgets(buf, MAXINPUT, stdin);
    sscanf(buf, "%d", &val);
    return val;
}

char * read_stdin (void)
{
    size_t cap = MAXINPUT, /* Initial capacity for the char buffer */
           len =    0; /* Current offset of the buffer */
    char *buffer = malloc(cap * sizeof (char));
    int c;

    /* Read char by char, breaking if we reach EOF or a newline */
    while ((c = fgetc(stdin)) != '\n' && !feof(stdin))
    {
        buffer[len] = c;

        /* When cap == len, we need to resize the buffer
         * so that we don't overwrite any bytes
         */
        if (++len == cap)
            /* Make the output buffer twice its current size */
            buffer = realloc(buffer, (cap *= 2) * sizeof (char));
    }

    /* Trim off any unused bytes from the buffer */
    buffer = realloc(buffer, (len + 1) * sizeof (char));

    /* Pad the last byte so we don't overread the buffer in the future */
    buffer[len] = '\0';

    return buffer;
}

int str_len(char* str)
{
    int length;
    for(length=0; str[length]!='\0'; ++length);

    return length;
}


int str_compare(char a[],char b[])
{
    int flag=1,i=0;
    if(str_len(a)==str_len(b))
    {
        while(a[i]!='\0' && b[i]!='\0')
        {
            if(a[i]!=b[i])
            {
                flag=0;
                break;
            }
            i++;
        }
        return flag;
    }
    else return 0;
}


void str_cpy(char a[],char b[]) //from,to
{
    int i=0;
    while(a[i]!='\0')  // while loop
    {
        b[i]=a[i];
        i++;
    }
    b[i]='\0';
}

char* removeLeadingSpaces(char* str)
{
    static char str1[400];
    int count = 0, j, k;

    // Iterate String until last
    // leading space character
    while (str[count] == ' ')
    {
        count++;
    }

    // Putting string into another
    // string variable after
    // removing leading white spaces
    for (j = count, k = 0;
            str[j] != '\0'; j++, k++)
    {
        str1[k] = str[j];
    }
    str1[k] = '\0';

    return str1;
}

void str_append(char *a,char b[])
{
    int i,j;
    for(i=0; a[i]!='\0'; ++i);

    for(j=0; b[j]!='\0'; ++j, ++i)
    {
        a[i]=b[j];
    }
    // \0 represents end of string
    a[i]='\0';
}

#endif // LIB_H_INCLUDED
