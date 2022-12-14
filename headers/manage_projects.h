
// File Permissions
#define R_OK 4 // Test for read permission.
#define W_OK 2 // Test for write permission.
//#define X_OK 1 // Test for execute permission.
#define F_OK 0 // Test for existence.

// Column Names
#define PROJ_ID      15         // 14 characters + \0
#define PROJ_NAME    50         // 49 characters + 1 null byte (\0) character
#define PROJ_COMMENT 500        // 499 characters + \0
#define PROJ_STATUS  50         // 49 characters + \0
#define PROJ_MARK    15         // 14 characters + \0

#define DELIMITER    "$@$"

// Database
// 3 is DELIMITER length and 5 is number of occurences of DELIMITER in a single line
#define __MAX_DATABASE_LINE__ PROJ_ID + PROJ_NAME + PROJ_COMMENT+ PROJ_STATUS + PROJ_MARK + 3 * 5

// Field Widths
#define ID_FW        10
#define NAME_FW      15
#define COMMENT_FW   25
#define STATUS_FW    15
#define MARK_FW      10

// Declare prototypes
void list_projects(const char *database);
void retrieve_data(const char *database, char *id, char *name, char* comment, char *status, char *mark);
void get_remaining_buffer(char *text, int index, char *output);
void print_row(char *id, char *name, char *comment, char *status, char *mark);
void center_text(char *text, int field_width, char *centered_text);
void add_project(const char *database);
void remove_project(const char *database);
void store_data(const char *database, const char *name, const char *comment, const char *status, const char *mark);

// make 'proj' a new variable type
typedef struct Projects
{
    // As char arrays are NOT assigned to anyting, they will contain random buffers
    // To clear the buffer, use:
    //              while (fgetc(stdin) != '\n');
    // Or:
    //              strcpy(name, "");
    // to overwrite the character array with ""
    char id[PROJ_ID];
    char name[PROJ_NAME];
    char comment[PROJ_COMMENT];
    char status[PROJ_STATUS];
    char mark[PROJ_MARK];
} proj;

// Position the text as center in its field and outputs the centered text in char *centered_text
void center_text(char *text, int field_width, char *centered_text)
{
    // Delete already filled staffs if any
    strcpy(centered_text, "");

    int padding_len = (field_width - strlen(text)) / 2;

    // left padding
    for (int i = 0; i < padding_len; i++)
    {
        strcat(centered_text, " ");
    }

    // text in center
    strcat(centered_text, text);

    // right padding
    for (int i = 0; i < padding_len; i++)
    {
        strcat(centered_text, " ");
    }

    // in case of odd number of paddings in both sides, right side will have 1 more whitespace (padding) than left
    if (strlen(centered_text) != field_width)
    {
        strcat(centered_text, " ");
    }
}

// Stores data to database file in the format: name$@$comment$@$status$@$mark$@$\n
void store_data(const char *database, const char *name, const char *comment, const char *status, const char *mark)
{
    FILE *fp;
    int id = 1;

    // file exists
    if (access(database, F_OK) == 0)
    {
        // a+ means append to file, also allow reading
        fp = fopen(database, "a+");

        char line[__MAX_DATABASE_LINE__];
        // Read file line by line
        // fgets(var to store to, max. no. of characters to read at a time, file stream)
        // if whole line is NOT read, the rest of the characters of that very line will be read in subsquent call
        while (fgets(line, __MAX_DATABASE_LINE__, fp))
        {
            if (line[0] == '\n')
                continue;
            // skip empty lines // if not skipped, atoi() will set id to 0
            if (line_is_empty(line))
                continue;
            // match a number and store in id. Then increment id by 1
            id = atoi(line);    // parse integer and ignore rest of the string // if string has no integer, returns 0
            id++;
        }
    }
    // file does not exist
    else
        fp = fopen(database, "w");

    // Convert id from integer to pointer character
    char id_c[PROJ_ID];
    sprintf(id_c, "%d", id);      // sprintf means string print //Instead of printing to console, it prints (stores) to a buffer

    fprintf(fp, id_c);
    fprintf(fp, DELIMITER);
    fprintf(fp, name);
    fprintf(fp, DELIMITER);
    fprintf(fp, comment);
    fprintf(fp, DELIMITER);
    fprintf(fp, status);
    fprintf(fp, DELIMITER);
    fprintf(fp, mark);
    fprintf(fp, DELIMITER);
    fprintf(fp, "\n");

    fclose(fp);
}

// store everything from database file to variables and then call print_row() to print rows (each projects)
void retrieve_data(const char *database, char *id, char *name, char* comment, char *status, char *mark)
{
    FILE *fp;
    // Read file
    fp = fopen(database, "r");

    char line[__MAX_DATABASE_LINE__];

    // store everything upto $@$, excluding $@$, in name variable -- 50 means name can contain a maximum of 50 characters (max. width)
    // %* means do NOT store [^\n] upto \n character, excluding \n ... %*c means do NOT store a character (in this case \n)
    while(fgets(line, __MAX_DATABASE_LINE__, fp))
    {
        // ignore blank (empty) line
        if (line[0] == '\n')
            continue;
        // ignore lines with only whitespace character
        if (line_is_empty(line))
            continue;
        // parse values from database lines
        parse_dline(line, DELIMITER, id, name, comment, status, mark);
        print_row(id, name, comment, status, mark);
    }

    fclose(fp);
}

void get_remaining_buffer(char *text, int index, char *output)
{
    int j = 0;
    for (int i = index; i < strlen(text)+1; i++)        // +1 to include null character
    {
        output[j] = text[i];
        j++;
    }
}

// calls center_text() to center texts in its field and then print each rows (projects)
// doesnot work only for texts greater than field width
void print_row(char *id, char *name, char *comment, char *status, char *mark)
{
    // Create object with name a
    proj a;

    // Clear the data
    strcpy(a.id, "");
    strcpy(a.name, "");
    strcpy(a.comment, "");
    strcpy(a.status, "");
    strcpy(a.mark, "");

    // When text is greater than field width
    int buffer = 0;
    if (strlen(id) > 10 || strlen(name) > 15 || strlen(comment) > 25 || strlen(status) > 15 || strlen(mark) > 10)
    {
        buffer = 1;
    }
    while (buffer)
    {
        // Remaining or extra staffs
        char remaining_id[PROJ_ID], remaining_name[PROJ_NAME], remaining_comment[PROJ_COMMENT], remaining_status[PROJ_STATUS], remaining_mark[PROJ_MARK];

        // Defaults
        /*strcpy(remaining_id, "");
        strcpy(remaining_name, "");
        strcpy(remaining_comment, "");
        strcpy(remaining_status, "");
        strcpy(remaining_mark, "");*/

        // ID
        if (strlen(id) > ID_FW)
        {
            // Set id and the remaining id (part)
            get_remaining_buffer(id, ID_FW, remaining_id);     // store name skipping first 10 characters // pointer arithmatic
            // id now contains only 10 characters (excluding null byte)
            id[ID_FW] = '\0';                // adding null byte means variable id ends at 11th character containing \0 at the 11th character
            strcpy(a.id, id);                // replace a.id with the value of id because a.id will be printed
            strcpy(id, remaining_id);        // replace id with remaining_id  because remaining_id will be re-initialised and may get buffer again from id
        }
        else
        {
            center_text(id, ID_FW, a.id);
            // Nore more buffer is left
            strcpy(id, "");
        }

        // Name
        if (strlen(name) > NAME_FW)
        {
            get_remaining_buffer(name, NAME_FW, remaining_name);
            name[NAME_FW] = '\0';

            // Set a.name with max characters allowed
            strcpy(a.name, name);
            strcpy(name, remaining_name);
        }
        else
        {
            center_text(name, NAME_FW, a.name);
            // Nore more buffer is left
            strcpy(name, "");
        }

        // Comment
        if (strlen(comment) > COMMENT_FW)
        {
            get_remaining_buffer(comment, COMMENT_FW, remaining_comment);
            comment[COMMENT_FW] = '\0';
            strcpy(a.comment, comment);
            strcpy(comment, remaining_comment);
        }
        else
        {
            center_text(comment, COMMENT_FW, a.comment);
            // Nore more buffer is left
            strcpy(comment, "");
        }

        // Status
        if (strlen(status) > STATUS_FW)
        {
            get_remaining_buffer(status, STATUS_FW, remaining_status);
            status[STATUS_FW] = '\0';
            strcpy(a.status, status);
            strcpy(status, remaining_status);
        }
        else
        {
            center_text(status, STATUS_FW, a.status);
            // Nore more buffer is left
            strcpy(status, "");
        }

        // Mark
        if (strlen(mark) > MARK_FW)
        {
            get_remaining_buffer(mark, MARK_FW, remaining_mark);
            mark[MARK_FW] = '\0';
            strcpy(a.mark, mark);
            strcpy(mark, remaining_mark);
        }
        else
        {
            center_text(mark, MARK_FW, a.mark);
            // Nore more buffer is left
            strcpy(mark, "");
        }

        // print data with buffer
        printf("%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|\n", KYEL, KNRM, a.id, KYEL, KNRM, a.name, KYEL, KNRM, a.comment, KYEL, KNRM, a.status, KYEL, KNRM, a.mark, KYEL);

        // Check for remaining buffer
        if (strlen(id) == 0 && strlen(name) == 0 && strlen(comment) == 0 && strlen(status) == 0 && strlen(mark) == 0)
        {
            // end line
            printf("|__________|_______________|_________________________|_______________|__________|%s\n", KNRM);
            return;         // if no buffer remains
        }
    }

    // Center Texts
    center_text(id, ID_FW, a.id);                    // ID
    center_text(name, NAME_FW, a.name);              // Name
    center_text(comment, COMMENT_FW, a.comment);     // Comment
    center_text(status, STATUS_FW, a.status);        // Status
    center_text(mark, MARK_FW, a.mark);              // Mark

    // data lines
    printf("%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|\n", KYEL, KNRM, a.id, KYEL, KNRM, a.name, KYEL, KNRM, a.comment, KYEL, KNRM, a.status, KYEL, KNRM, a.mark, KYEL);
    // end line
    printf("|__________|_______________|_________________________|_______________|__________|%s\n", KNRM);
}

// Prints header and calls retrieve_data(), which then calls print_row(), which prints rows (each projects) but first it calls center_text() to align the datas in center
void list_projects(const char *database)
{
    // If file exists, check file read privilege
    if (access(database, F_OK) == 0 && access(database, R_OK) != 0)
    {
        // No read privivlege
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return;
    }
    // I file does NOT exist, check folder read privilege
    else if (access("Database", R_OK) != 0)
    {
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return;
    }

    // Executes when:
    // 1. File exists and read privilege OK
    // 2. File does NOT exist, but read privilege OK

    // --- 10 --- 15 --- 25 --- 15 --- 10 --- = 75
    // || * 6 = 12
    // sum = 75 + 12 = 87

    // Header
    printf(" %s_______________________________________________________________________________ \n", KRED);
    printf("|    %sId    %s|      %sName     %s|         %sComment         %s|    %sStatus     %s|   %sMark   %s|\n", KGRN, KRED, KGRN, KRED, KGRN, KRED, KGRN, KRED, KGRN, KRED);
    printf("|__________|_______________|_________________________|_______________|__________|%s\n", KNRM);

    // If file does NOT exist, just return after printing headers
    if (access(database, F_OK) != 0)
        return;

    // Executes when:
    // 1. File exists and read privilege OK
    char id[PROJ_ID], name[PROJ_NAME], comment[PROJ_COMMENT], status[PROJ_STATUS], mark[PROJ_MARK];

    // Fetch data
    retrieve_data(database, id, name, comment, status, mark);
}

void add_project(const char *database)
{
    // If file does not exist, check forlder privilege (to write new file)
    if (access(database, F_OK) != 0)
    {
        // Check if you have write access in current folder
        if (access("Database", W_OK) != 0)
        {
            printf("%sPermission Denied%s\n", KRED, KNRM);
            return;
        }
    }
    // If file exists, but no write access  (check file privilege) // if access() does NOT return 0, it means you have NO write permission
    else if (access(database, W_OK) != 0)
    {
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return;
    }

    char name[PROJ_NAME], comment[PROJ_COMMENT], status[PROJ_STATUS], mark[PROJ_MARK];

    printf("%sName of project:%s ", KCYN, KNRM);
    take_input(name, PROJ_NAME);

    printf("%sComment:%s ", KCYN, KNRM);
    take_input(comment, PROJ_COMMENT);

    printf("%sStatus:%s ", KCYN, KNRM);
    take_input(status, PROJ_STATUS);

    printf("%sMark:%s ", KCYN, KNRM);
    take_input(mark, PROJ_MARK);

    store_data(database, name, comment, status, mark);
}

void remove_project(const char *database)
{
    FILE *fp;

    // If file exists, check file privilege and then open file for 'r+' (reading allowing writing)
    if (access(database, F_OK) == 0)
    {
        // if access() does NOT return 0, it means you have NO write permission
        if (access(database, W_OK) != 0)
        {
            printf("%sPermission Denied%s\n", KRED, KNRM);
            return;
        }

        // Read file
        fp = fopen(database, "r+");    // Allow reading and writing keeping original file unchanged
    }
    // If file does not exist, check folder privilege
    else if (access("Database", W_OK) != 0)
    {
        printf("%sPermission Denied%s\n", KRED, KNRM);
        return;
    }
    // Required privileges are OK, but file does NOT exist
    else
    {
        printf("%sNo project found%s\n", KYEL, KNRM);
        return;
    }

    char line[__MAX_DATABASE_LINE__];
    int id, current_id;

    printf("%sID:%s ", KCYN, KNRM);
    char id_c[PROJ_ID];
    take_input(id_c, PROJ_ID);
    id = atoi(id_c);

    // iterate each line and replace the line containing id with whitespace characters
    while (fgets(line, __MAX_DATABASE_LINE__, fp))
    {
        sscanf(line, "%d", &current_id);
        if (current_id == id)
        {
            int text_to_be_replaced = strlen(line);
            fseek(fp, text_to_be_replaced * -1, SEEK_CUR);    // get to the start of line which will be replaced (made blank)
            for (int i = 0; i < text_to_be_replaced - 1; i++)
            {
                fprintf(fp, " ");                             // Overwrite with whitespace upto \n newline
            }
            fseek(fp, 1, SEEK_CUR);                           // Cover \n newline
        }
    }
    fclose(fp);
}

void edit_project(const char *database)
{
}

