
#define ALLOWED_CHAR 64          // 10+26*2+2=64

char ENCRYPT_DICT[ALLOWED_CHAR][2][4] = {
                    // 0 - 9
                        // _.
                        {"0", "___"},{"1", "__."},{"2", "_.."},{"3", "..."},
                        {"4", ".._"},{"5", ".__"},{"6", "._."},{"7", "_._"},
                        // _+
                        {"8", "__+"},{"9", "_++"},
                    // A - Z
                        // _+ (continue)
                        {"A", "+++"},{"B", "++_"},{"C", "+__"},{"D", "+_+"},
                        {"E", "_+_"},
                        // .+
                        {"F", "..+"},{"G", ".++"},{"H", "++."},{"I", "+.."},
                        {"J", "+.+"},{"K", ".+."},
                        // _.+
                        {"L", "_.+"},{"M", ".+_"},{"N", "+_."},{"O", "+._"},
                        {"P", "_+."},{"Q", "._+"},
                        // _-
                        {"R", "__-"},{"S", "_--"},{"T", "---"},{"U", "--_"},
                        {"V", "-__"},{"W", "-_-"},{"X", "_-_"},
                        // .-
                        {"Y", "..-"},{"Z", ".--"},
                    // a - z
                        // .- (continue)
                        {"a", "--."},{"b", "-.."},{"c", "-.-"},{"d", ".-."},
                        // +-
                        {"e", "++-"},{"f", "+--"},{"g", "--+"},{"h", "-++"},
                        {"i", "-+-"},{"j", "+-+"},
                        // _.-
                        {"k", "_.-"},{"l", ".-_"},{"m", "-_."},{"n", "-._"},
                        {"o", "_-."},{"p", "._-"},
                        // _+-
                        {"q", "_+-"},{"r", "+-_"},{"s", "-_+"},{"t", "-+_"},
                        {"u", "_-+"},{"v", "+_-"},
                        // .+-
                        {"w", ".+-"},{"x", "+-."},{"y", "-.+"},{"z", "-+."},
                    // Special Characters (@, SPACE)
                        // .+- (Continue)
                        {"@", ".-+"},{" ", "+.-"}
                   };


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

// name, pass and db are overwritten
// parse creds line
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
int line_is_empty(const char *line)
{
    if (strlen(line) == 0)
        return 1;

    // -1 to avoid \n or any null characters
    for (int i = 0; i < strlen(line) - 1; i++)
        // line is not empty
        if (line[i] != ' ')
            return 0;
    // line is empty
    return 1;
}

// Returns 0 or 1 // 1 --> success // 0 --> fail
// 1st arg --> char to encrypt
// 2nd arg --> stores encrypted argument
int encrypt_char(const char character, char *encrypted_text)
{
    for (int i = 0; i < ALLOWED_CHAR; i++)
    {
        if (character == ENCRYPT_DICT[i][0][0])
        {
            strcat(encrypted_text, ENCRYPT_DICT[i][1]);
            return 1;
        }
    }
    return 0;
}

// Returns 0 or 1 // 1 --> success // 0 --> fail
// 1st arg --> text to encrypt
// 2nd arg --> stores encrypted argument
// 3rd arg --> Max. size of encrypted text
// To calculate encrypted size:
//      encrypted_size = 3 * max_number_of_characters + 1
int encrypt_text(const char *text, char *encrypted_text, int encrypted_size)
{
    strcpy(encrypted_text, "");
    int i, max_num_of_char;

    // if remainder is 1 or 2
    if (encrypted_size % 3 > 0)
        max_num_of_char = encrypted_size / 3;
    // if remainder is 0
    else
        max_num_of_char = encrypted_size / 3 - 1;

    for (i = 0; i < strlen(text); i++)
    {
        // if text is larger than the max no. of characters allowed to encrypt
        if (i >= max_num_of_char)
        {
            encrypted_text[i*3] = 0;    // add null byte
            return 1;
        }
        if (!encrypt_char(text[i], encrypted_text))
        {
            // if encryption fails
            strcpy(encrypted_text, "");     // clear (empty) the encrypted text
            return 0;
        }
    }
    encrypted_text[i*3] = 0;
    return 1;
}

int decrypt_char(const char *text, char *decrypted_text)
{
    char temp[4];

    // Extract 3 characters from (encrypted) text
    // because 3 characters = 1 decrypted char
    for (int i = 0; i < 3; i++)
        temp[i] = text[i];
    temp[3] = '\0';

    for (int i = 0; i < ALLOWED_CHAR; i++)
        if (strcmp(temp, ENCRYPT_DICT[i][1]) == 0)
        {
            strcat(decrypted_text, ENCRYPT_DICT[i][0]);
            return 1;
        }
    return 0;
}

int decrypt_text(const char *text, char *decrypted_text, int decrypted_size)
{
    int i, j = 1;
    strcpy(decrypted_text, "");

    for (i = 0; i < strlen(text); i += 3)
    {
        if (j >= decrypted_size)
        {
            decrypted_text[j-1] = 0;    // add null byte
            return 1;
        }
        // match with text[i], text[i+1] and text[i+2] and decrypt
        if (!decrypt_char((text+i), decrypted_text))
        {
            strcpy(decrypted_text, "");
            return 0;
        }
        j++;
    }
    return 1;
}
