
// int return type --> 0 means success, 1 means exceeds max char (overflow)
// 1st argument is the array where input will be stored
// 2nd argument is maximum number of characters including null byte (\0)
int take_pass(char *text, int max_char)
{
    #ifdef WIN32
        for (int i = 0; i < max_char; i++)
        {
            test[i] = getch();
            if (test[i] == '\n')
            {
                test[i] = 0;
                return 0;
            }
            printf("*");
        }
        test[max_char-1] = 0;
        return 1;
    #endif

    #ifdef unix
        strcpy(text, getpass(""));
        if (strlen(text) > max_char-1)
        {
            text[max_char-1] = 0;
            return 1;
        }
        return 0;
    #endif
}

void csleep(int time_in_millisec)
{
    #ifdef WIN32
        Sleep(time_in_millisec);            // defined in windows.h
    #endif

    #ifdef unix
        usleep(time_in_millisec*1000);            // defined in unistd.h
    #endif
}

void cls(void)
{
    #ifdef WIN32
        system("cls");
    #endif
    #ifdef unix
        system("clear");
    #endif
}

void beep(void)
{
    #ifdef WIN32
        // frequency --> 500
        // duration  --> 150 millisecond
        // blocks code until returned
        Beep(500, 150);
    #endif
    #ifdef unix
    #endif
}
