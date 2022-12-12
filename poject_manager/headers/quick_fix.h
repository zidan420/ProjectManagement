
// Always take input from stdin
// pass char array as 1st argument to store user input // must be empty array
// 2nd argument is maximum number of characters including null byte (\0) // max_char = 10 means 9 characters and 1 null byte
// Removes/Deletes characters after the MAXIMUM SIZE
void take_input(char *text, int max_char)
{
    if (fgets(text, max_char, stdin))
    {
        char *p;
        // strchr searches for 1st occurence of char '\n' and returns pointer char
        if(p=strchr(text, '\n'))
        {
            *p = '\0';  // changes \n to null byte
        }
        // Consumes extra buffer upto and including \n
        else
        {
            //scanf("%*[^\n]");
            //scanf("%*c");
            while (fgetc(stdin) != '\n');
        }
    }
}

// Returns number of occurences Found // 0 if no occurence found
// 1st arg --> Text to search for delimiter // text is char array
// 2nd arg --> Delimiter is also char array
// 3rd arg --> Position of all occurences are stored here
// 4th arg --> number of occurences to store (At Most)
int find_all_occurences(const char *text, const char *delimiter, int occur_array[], int array_size)
{
    int array_i = 0, match_start = 0, delimiter_i = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        // break when occur_array can NOT store anymore occurences
        if (array_i >= array_size)
            break;
        // Match each character of delimiter with the character of text
        if (*(delimiter+delimiter_i) == text[i])
        {
            match_start = 1;
            delimiter_i++;

            // If match found
            if (delimiter_i == strlen(delimiter))
            {
                occur_array[array_i] = i - strlen(delimiter) + 1;
                array_i++;

                // reset everything
                delimiter_i = 0;
                match_start = 0;
            }
            //occur_array[array_i] = i;
            //array_i++;
        }
        // If match is true, but the (subsequent) character of delimiter did NOT match
        else if (match_start)
        {
            // reset everything
            delimiter_i = 0;
            match_start = 0;
        }
    }
    // return number of elements successfully stored
    return array_i;
}

// id, name and other parameters are overwritten
void parse_dline(const char *line, const char *delimiter, char *id, char *name, char *comment, char *status, char *mark)
{
    int num_of_occur = 5;
    int all_occur[num_of_occur], j = 0;

    find_all_occurences(line, delimiter, all_occur, num_of_occur);

    // empty variables before parsing
    strcpy(id, "");
    strcpy(name, "");
    strcpy(comment, "");
    strcpy(status, "");
    strcpy(mark, "");

    for (int i = 0; i < all_occur[0]; i++)
    {
        id[j] = line[i];
        j++;
    }
    id[j] = 0;          // add null byte at the end of string
    j = 0;              // reset

    for (int i = all_occur[0] + strlen(delimiter); i < all_occur[1]; i++)
    {
        name[j] = line[i];
        j++;
    }
    name[j] = 0;        // add null byte at the end of string
    j = 0;              // reset

    for (int i = all_occur[1] + strlen(delimiter); i < all_occur[2]; i++)
    {
        comment[j] = line[i];
        j++;
    }
    comment[j] = 0;     // add null byte at the end of string
    j = 0;              // reset

    for (int i = all_occur[2] + strlen(delimiter); i < all_occur[3]; i++)
    {
        status[j] = line[i];
        j++;
    }
    status[j] = 0;      // add null byte at the end of string
    j = 0;              // reset

    for (int i = all_occur[3] + strlen(delimiter); i < all_occur[4]; i++)
    {
        mark[j] = line[i];
        j++;
    }
    mark[j] = 0;       // add null byte at the end of string
}

// name, pass and db are overwritten
void parse_cline(const char*line, const char *delimiter, char *username, char *encoded_pass, char *database_name)
{
    // empty variables
    strcpy(username, "");
    strcpy(encoded_pass, "");
    strcpy(database_name, "");

    int num_of_occur = 3, i, j = 0;
    int all_occur[num_of_occur];

    find_all_occurences(line, delimiter, all_occur, num_of_occur);

    // Retrieve Username
    for (i = 0; i < all_occur[0]; i++)
    {
        username[j] = line[i];
        j++;
    }
    username[j] = 0;
    j = 0;

    // Retrieve Encoded Password
    for (i = all_occur[0] + strlen(delimiter); i < all_occur[1]; i++)
    {
        encoded_pass[j] = line[i];
        j++;
    }
    encoded_pass[j] = 0;
    j = 0;

    // Retrieve Database Name
    for (i = all_occur[1] + strlen(delimiter); i < all_occur[2]; i++)
    {
        database_name[j] = line[i];
        j++;
    }
    database_name[j] = 0;
}

// line is empty if it contains only whitespace characters or \n newline (or \0 null character)
int line_is_empty(char *line)
{
    // -1 to avoid \n or any null characters
    for (int i = 0; i < strlen(line) - 1; i++)
        // line is not empty
        if (line[i] != ' ')
            return 0;
    // line is empty
    return 1;
}

