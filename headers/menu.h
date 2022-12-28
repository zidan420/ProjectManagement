
// 1st argument --> The database to handle
void menu(const char *database)
{
    int option;                 // contains user-selected option
    while (1)
    {
        list_options();

        get_option(&option);    // Stores the option that user selected into option variable using pointer indirect reference

        if (option == 1) list_projects(database);          // List Projects
        else if (option == 2) add_project(database);       // Add Projects
<<<<<<< HEAD
        else if (option == 3) edit_project(database);      // Edit Projects
        else if (option == 4) remove_project(database);    // Remove Projects
        else if (option == 5) cls();                       // Clear Screen
        else if (option == 6) about_us();                  // About us
        else if (option == 7) break;                       // Exit
=======
        //else if (option == 3) edit_project(database);      // Edit Projects
        else if (option == 3) remove_project(database);    // Remove Projects
        else if (option == 4) cls();                       // Clear Screen
        else if (option == 5) about_us();                  // About us
        else if (option == 6) break;                       // Exit
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
        else print_help();                                 // Show help
    }
}
