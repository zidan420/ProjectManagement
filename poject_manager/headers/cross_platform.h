
void _sleep(int time)
{
    #ifdef WIN32
    Sleep(time);            // defined in windows.h
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
