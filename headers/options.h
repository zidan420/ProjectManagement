
void list_options(void)
{
    printf("%s[%s1%s] %sList Projects\n"  , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s2%s] %sAdd Projects\n"   , KYEL, KRED, KYEL, KGRN);
<<<<<<< HEAD
    printf("%s[%s3%s] %sEdit Projects\n"   , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s4%s] %sRemove Projects\n" , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s5%s] %sClear Screen\n"   , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s6%s] %sAbout Me\n"       , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s7%s] %sExit%s\n"         , KYEL, KRED, KYEL, KGRN, KNRM);
=======
    //printf("%s[%s3%s] %sEdit Projects (BUILT In Progress)\n"   , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s3%s] %sRemove Projects\n" , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s4%s] %sClear Screen\n"   , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s5%s] %sAbout Me\n"       , KYEL, KRED, KYEL, KGRN);
    printf("%s[%s6%s] %sExit%s\n"         , KYEL, KRED, KYEL, KGRN, KNRM);
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
}

void get_option(int *option)
{
    // Store a single character and null byte \0
    char line[2];

    printf("%s>>> %s", KYEL, KNRM);

    // If unsuccessful, remove bad characters
    take_input(line, 2);

    *option = atoi(line);
}

void print_help(void)
{
    printf("%sError:%s Option is out of range. Please select option from 1 to 5 (inclusive).%s\n\n", KRED, KBLU, KNRM);
}
