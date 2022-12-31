
// Database File
#define DEFAULT_DATABASE "Database/corposer.dat"

// Credentials File
#define __CREDS__ "Database/creds.txt"

// Default Credentials
#define DEFAULT_NAME "corposer"
#define DEFAULT_PASS "Corpos3r"

// Maximum Length of Credentials
#define MAX_USER            101                    // max 100 characters + 1 null byte
#define MAX_PASS            101                    // max 100 characters + 1 null byte
#define DATABASE_LENGTH     MAX_USER + 4           // 4 is for '.dat'
// * 3 is because 1 character takes space of 3 characters when encoded.. +1 is for null byte
#define PASS_ENC_SIZE       (MAX_PASS - 1) * 3 + 1      // (101 - 1) * 3 + 1 = 301
#define __MAX_CREDS_LINE__  MAX_USER+PASS_ENC_SIZE+DATABASE_LENGTH+3    // 3 is the total no. of delimiters * each delimiter length

// Returns 0 or 1 // 1 --> success // 0 --> fail
// If credentials match, database name of the corresponding account is stored in 3rd argument
// 2nd arg --> password is encrypted
int check_creds(const char *username, const char *password, char *database_name)
{
    FILE *fp;
    char line[__MAX_CREDS_LINE__], valid_user[MAX_USER], valid_pass[PASS_ENC_SIZE];

    fp = fopen(__CREDS__, "r");                                           // permission verified

    // get creds from file and store to valid_user & valid_pass
    while(fgets(line, __MAX_CREDS_LINE__, fp))
    {
        // ignore blank (empty) line
        if (line[0] == '\n')
            continue;
        // ignore lines with only whitespace character
        if (line_is_empty(line))
            continue;
        parse_cline(line, ":", valid_user, valid_pass, database_name);     // valid_pass is encrypted

        // both username and password correct
        if (strcmp(valid_user, username) == 0 && strcmp(valid_pass, password) == 0)
            return 1;
    }
    // Match Failed
    strcpy(database_name, "");

    fclose(fp);
    return 0;
}

// Returns 0 or 1 // 1 --> success // 0 --> fail
// 1st arg --> username or database to check
// 2nd arg --> determines if the 1st arg is a username or database // 0 for username and 1 foor database
int ud_already_taken(const char *text, int ud)
{
    FILE *fp;
    char line[__MAX_CREDS_LINE__], valid_user[MAX_USER], database[DATABASE_LENGTH];
    int num_of_occur = 3, i, j = 0;
    int all_occur[num_of_occur];

    fp = fopen(__CREDS__, "r");             // permission verified

    // get creds from file and store to valid_user & valid_pass
    while(fgets(line, __MAX_CREDS_LINE__, fp))
    {
        // ignore blank (empty) line
        if (line[0] == '\n')
            continue;
        // ignore lines with only whitespace character
        if (line_is_empty(line))
            continue;

        // username
        if (ud == 0)
        {
            find_all_occurences(line, ":", all_occur, num_of_occur);

            // Retrieve Username
            for (i = 0; i < all_occur[0]; i++)
            {
                valid_user[j] = line[i];
                j++;
            }
            valid_user[j] = 0;

            // match user
            if (strcmp(valid_user, text) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
        else if (ud == 1)
        {
            find_all_occurences(line, ":", all_occur, num_of_occur);

            // Retrieve databae
            for (i = all_occur[1] + 1; i < all_occur[2]; i++)   // 1 is for length of delimiter
            {
                database[j] = line[i];
                j++;
            }
            database[j] = 0;

            // match database
            if (strcmp(database, text) == 0)
            {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

void signup(char *username, char *password, char *encrypted_pass, char *database)
{
    // Check if you have both read and write access in credentials file
    // write permission for signup
    // read access is already verified
    if (access(__CREDS__, W_OK) != 0)
    {
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return;
    }

    cls();
    printf("%sTo create a new account, enter the following:\n%s", KGRN, KNRM);

    printf("%sUsername:%s ", KYEL, KNRM);
    if (take_input(username, MAX_USER))
    {
        printf("%sUsername can be at most %d characters\n%s",KRED, MAX_USER-1, KNRM);
        return;
    }

    // If username matches, invalid signup
    if (ud_already_taken(username, 0))
    {
        printf("%sUsername is already taken%s\n", KRED, KNRM);
        return;
    }

    if (strlen(username) == 0)
    {
        printf("%sUsername cannot be empty!\n%s", KRED, KNRM);
        return;
    }

    printf("%sPassword:%s ", KYEL, KNRM);
    if (take_pass(password, MAX_PASS))
    {
        printf("%sPassword can be at most %d characters%s\n", KRED, MAX_PASS-1, KNRM);
        return;
    }

    if (strlen(password) < 8)
    {
        printf("%sPassword has to be atleast 8 characters%s\n", KRED, KNRM);
        return;
    }

    // Encrypt Password before storing
    encrypt_text(password, encrypted_pass, PASS_ENC_SIZE);

    // set database
    strcat(database, "Database/");
    strcat(database, username);
    strcat(database, ".dat");

    FILE *fp;

    fp = fopen(__CREDS__, "a");

    fprintf(fp, username);
    fprintf(fp, ":");
    fprintf(fp, encrypted_pass);
    fprintf(fp, ":");
    fprintf(fp, database);
    fprintf(fp, ":\n");

    fclose(fp);
}

// Returns 0 or 1 // 1 --> success // 0 --> fail
// sets database name of the corresponding account in 1st argument
int login(char *database_name)
{
    int logged_in = 0;
    char username[MAX_USER];
    char password[MAX_PASS];
    char encrypted_pass[PASS_ENC_SIZE];

    // if file does NOT exist, create default credentials
    if (access(__CREDS__, F_OK) != 0)
    {
        // if database does not exists
        if (access("Database", F_OK) != 0)
        {
            if (access(".", W_OK) != 0)
            {
                printf("%sPermission Denied%s\n", KRED, KNRM);
                return 0;
            }
            // create database file
            system("mkdir Database");
        }

        // Check for write access in Database folder
        if (access("Database", W_OK) != 0)
        {
            printf("%sPermission Denied%s\n", KRED, KNRM);
            return 0;
        }

        // Create a credential file (creds.txt)
        FILE *fp;
        fp = fopen(__CREDS__, "w");

        // Encrypt Default Password
        encrypt_text(DEFAULT_PASS, encrypted_pass, PASS_ENC_SIZE);

        // Default Credentials with default Database
        fprintf(fp, DEFAULT_NAME);
        fprintf(fp, ":");
        fprintf(fp, encrypted_pass);
        fprintf(fp, ":");
        fprintf(fp, DEFAULT_DATABASE);
        fprintf(fp, ":\n");

        fclose(fp);

        // Empty password array
        strcpy(encrypted_pass, "");
    }
    // read permission is to read credential file for checking and validating credentials
    if (access(__CREDS__, R_OK) != 0)
    {
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return 0;
    }

    printf("%sDefault credentials => %s%s%s:%s%s\n%s", KCYN, KBLU, DEFAULT_NAME, KCYN, KGRN, DEFAULT_PASS, KNRM);
    printf("%sTo create a new account, keep both %susername %sand %spassword %sfields empty%s\n", KCYN, KGRN, KCYN, KGRN, KCYN, KNRM);
    while (!logged_in)
    {
        printf("\n%sPlease login...%s\n", KMAG, KNRM);
        printf("%sUsername:%s ", KYEL, KNRM);
        take_input(username, MAX_USER);

        printf("%sPassword:%s ", KYEL, KNRM);
        take_pass(password, MAX_PASS);

        // Sign Up // Create new account
        if (strlen(username) == 0 && strlen(password) == 0)
        {
            signup(username, password, encrypted_pass, database_name);
            continue;
        }

        // Encrypt Password before checking
        encrypt_text(password, encrypted_pass, PASS_ENC_SIZE);
        // Check for match of credentials
        if (check_creds(username, encrypted_pass, database_name))
            return 1;   // logged_in is 1
        else
            printf("%sError: Invalid username or password.\n%s", KRED, KNRM);
    }
    return 0;
}

