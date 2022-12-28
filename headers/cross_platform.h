
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
