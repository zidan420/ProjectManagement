
// 1st argument --> The database to handle
void menu(const char *database)
{
    int option;                 // contains user-selected option
    while (1)
    {
        int i = 1;
        list_options();

        get_option(&option);    // Stores the option that user selected into option variable using pointer indirect reference

        if (option == i++) list_projects(database);          // List Projects
        else if (option == i++) add_project(database);       // Add Projects
        else if (option == i++) edit_project(database);      // Edit Projects
        else if (option == i++) remove_project(database);    // Remove Projects
        else if (option == i++) cls();                       // Clear Screen
        else if (option == i++) about_us();                  // About us
        else if (option == i++) break;                       // Exit
        else print_help();                                 // Show help
    }
}
