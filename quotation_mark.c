
int count_char(char *str,char c)
{
    int i;
    int count;

    i = 0;
    count  = 0;
    while (str[i])
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int is_sym_rec(char str[],
             int s, int e)
{
    int i;

    i = 0;
    if (s == e)
        return 0;
    if (count_char(str, '!') % 2 == 0)
    {
        if (str[s] == str[e] && str[s] == '!' && str[e] == '!')
        {
            i++;
            is_sym_rec(str, s + 1, e - 1);
        }

    }
    return i;
}

int is_sym(char str[])
{
    int n;

    n = strlen(str);
    if (n == 0)
        return (0);
    return isPalRec(str, 0, n - 1);
}