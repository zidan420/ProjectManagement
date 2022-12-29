
void animate_text(char *str, int index, int count)
{
    char temp[100];
    strcpy(temp, str);

    if (count == strlen(str))
        return;

    if ('a' <= temp[index] && temp[index] <= 'z')
    {
        temp[index] -= ('a' - 'A');
    }
    else if ('A' <= temp[index] && temp[index] <= 'Z')
    {
        temp[index] += ('a' - 'A');
    }

    if (temp[strlen(str)-1] == '\\')
    {
        temp[strlen(str)-1] = '|';
        str[strlen(str)-1] = '|';
        beep();                                     // beep for 150 ms
    }
    else if (temp[strlen(str)-1] == '|')
    {
        temp[strlen(str)-1] = '/';
        str[strlen(str)-1] = '/';
    }
    else if (temp[strlen(str)-1] == '/')
    {
        temp[strlen(str)-1] = '-';
        str[strlen(str)-1] = '-';
    }
    else if (temp[strlen(str)-1] == '-')
    {
        temp[strlen(str)-1] = '\\';
        str[strlen(str)-1] = '\\';
    }

    printf("%s\r", temp);
    fflush(stdout);

    csleep(150);    // milliseconds

    animate_text(str, index+1, count+1);
}

void title(void)
{
    cls();

    printf("%s$$$$$$$\\  $$$$$$$\\   $$$$$$\\     $$$$$\\ $$$$$$$$\\  $$$$$$\\ $$$$$$$$\\\n", KRED);
    printf("$$  __$$\\ $$  __$$\\ $$  __$$\\    \\__$$ |$$  _____|$$  __$$\\\\__$$  __|\n");
    printf("$$ |  $$ |$$ |  $$ |$$ /  $$ |      $$ |$$ |      $$ /  \\__|  $$ |\n");
    printf("$$$$$$$  |$$$$$$$  |$$ |  $$ |      $$ |$$$$$\\    $$ |        $$ |\n");
    printf("$$  ____/ $$  __$$< $$ |  $$ |$$\\   $$ |$$  __|   $$ |        $$ |\n");
    printf("$$ |      $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |  $$\\   $$ |\n");
    printf("$$ |      $$ |  $$ | $$$$$$  |\\$$$$$$  |$$$$$$$$\\ \\$$$$$$  |  $$ |\n");
    printf("\\__|      \\__|  \\__| \\______/  \\______/ \\________| \\______/   \\__|\n\n");

    printf("%s$$\\      $$\\  $$$$$$\\  $$\\   $$\\  $$$$$$\\   $$$$$$\\  $$$$$$$$\\ $$\\      $$\\ $$$$$$$$\\ $$\\   $$\\ $$$$$$$$\\\n", KGRN);
    printf("$$$\\    $$$ |$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$  __$$\\ $$  _____|$$$\\    $$$ |$$  _____|$$$\\  $$ |\\__$$  __|\n");
    printf("$$$$\\  $$$$ |$$ /  $$ |$$$$\\ $$ |$$ /  $$ |$$ /  \\__|$$ |      $$$$\\  $$$$ |$$ |      $$$$\\ $$ |   $$ |\n");
    printf("$$\\$$\\$$ $$ |$$$$$$$$ |$$ $$\\$$ |$$$$$$$$ |$$ |$$$$\\ $$$$$\\    $$\\$$\\$$ $$ |$$$$$\\    $$ $$\\$$ |   $$ |\n");
    printf("$$ \\$$$  $$ |$$  __$$ |$$ \\$$$$ |$$  __$$ |$$ |\\_$$ |$$  __|   $$ \\$$$  $$ |$$  __|   $$ \\$$$$ |   $$ |\n");
    printf("$$ |\\$  /$$ |$$ |  $$ |$$ |\\$$$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |\\$  /$$ |$$ |      $$ |\\$$$ |   $$ |\n");
    printf("$$ | \\_/ $$ |$$ |  $$ |$$ | \\$$ |$$ |  $$ |\\$$$$$$  |$$$$$$$$\\ $$ | \\_/ $$ |$$$$$$$$\\ $$ | \\$$ |   $$ |\n");
    printf("\\__|     \\__|\\__|  \\__|\\__|  \\__|\\__|  \\__| \\______/ \\________|\\__|     \\__|\\________|\\__|  \\__|   \\__|\n\n");

    printf("\t\t\t\t%s~~ %sPowered by Md Zidan Khan%s\n\n", KYEL, KMAG, KNRM);

    char str[] = "[*] Starting the Project Manager...\\";
    animate_text(str, 0, 0);

    cls();
}
