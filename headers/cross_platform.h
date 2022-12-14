
void csleep(int time)
{
    #ifdef WIN32
    Sleep(time * 1000);            // defined in windows.h // time is in milliseconds
    #endif

    #ifdef unix
    sleep(time);            // defined in unistd.h
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
