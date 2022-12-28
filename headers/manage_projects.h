
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

<<<<<<< HEAD
// ENCRYPTED
#define EPROJ_ID      3*(PROJ_ID-1)+1       // 3*(15-1)=42 characters + 1 null byte (\0)
#define EPROJ_NAME    3*(PROJ_NAME-1)+1
#define EPROJ_COMMENT 3*(PROJ_COMMENT-1)+1
#define EPROJ_STATUS  3*(PROJ_STATUS-1)+1
#define EPROJ_MARK    3*(PROJ_MARK-1)+1
=======
#define DELIMITER    "$@$"

// Database
// 3 is DELIMITER length and 5 is number of occurences of DELIMITER in a single line
#define __MAX_DATABASE_LINE__ PROJ_ID + PROJ_NAME + PROJ_COMMENT+ PROJ_STATUS + PROJ_MARK + 3 * 5
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170

// Field Widths
#define ID_FW        10
#define NAME_FW      15
#define COMMENT_FW   25
#define STATUS_FW    15
#define MARK_FW      10

<<<<<<< HEAD
=======
// Declare prototypes
void list_projects(const char *database);
void retrieve_data(const char *database, char *id, char *name, char* comment, char *status, char *mark);
void get_remaining_buffer(char *text, int index, char *output);
void print_row(char *id, char *name, char *comment, char *status, char *mark);
void center_text(char *text, int field_width, char *centered_text);
void add_project(const char *database);
void remove_project(const char *database);
void store_data(const char *database, const char *name, const char *comment, const char *status, const char *mark);

>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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

<<<<<<< HEAD
typedef struct EProjects
{
    char eid[EPROJ_ID];
    char ename[EPROJ_NAME];
    char ecomment[EPROJ_COMMENT];
    char estatus[EPROJ_STATUS];
    char emark[EPROJ_MARK];
} eproj;


// Declare prototypes
void list_projects(const char *database);
void retrieve_data(const char *database);
void get_remaining_buffer(char *text, int index, char *output);
void print_row(proj *p_proj);
void center_text(char *text, int field_width, char *centered_text);
void add_project(const char *database);
void remove_project(const char *database);
void store_data(const char *database, proj *p_proj);

=======
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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

<<<<<<< HEAD
// Stores data to database file in the struct format
void store_data(const char *database, proj *p_proj)
=======
// Stores data to database file in the format: name$@$comment$@$status$@$mark$@$\n
void store_data(const char *database, const char *name, const char *comment, const char *status, const char *mark)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
{
    FILE *fp;
    int id = 1;

    // file exists
    if (access(database, F_OK) == 0)
    {
        // a+ means append to file, also allow reading
        fp = fopen(database, "a+");

<<<<<<< HEAD
        // Create structures to retrieve data to
        eproj _eproj;

        while (fread(&_eproj, sizeof(_eproj), 1, fp))
        {
            if (line_is_empty(_eproj.eid) && line_is_empty(_eproj.ename) && line_is_empty(_eproj.ecomment) &&
                line_is_empty(_eproj.estatus) && line_is_empty(_eproj.emark))
                continue;

            // decrypt id
            decrypt_text(_eproj.eid, p_proj->id, PROJ_ID);

            // match a number and store in id. Then increment id by 1
            id = atoi(p_proj->id);    // integer and ignore rest of the string // if string has no integer, returns 0
=======
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
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
            id++;
        }
    }
    // file does not exist
    else
        fp = fopen(database, "w");

    // Convert id from integer to pointer character
<<<<<<< HEAD
    sprintf(p_proj->id, "%d", id);      // sprintf means string print //Instead of printing to console, it prints (stores) to a buffer

    // Encrypt name, comment, status and mark
    eproj _eproj;
    encrypt_text(p_proj->id,      _eproj.eid,      EPROJ_ID);
    encrypt_text(p_proj->name,    _eproj.ename,    EPROJ_NAME);
    encrypt_text(p_proj->comment, _eproj.ecomment, EPROJ_COMMENT);
    encrypt_text(p_proj->status,  _eproj.estatus,  EPROJ_STATUS);
    encrypt_text(p_proj->mark,    _eproj.emark,    EPROJ_MARK);

    // Write/Append struct to database file
    fwrite(&_eproj, sizeof(eproj), 1, fp);
=======
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
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170

    fclose(fp);
}

<<<<<<< HEAD
// retrieve everything from database file to variables and then call print_row() to print rows (each projects)
// store everything from database file to variables and then call print_row() to print rows (each projects)
void retrieve_data(const char *database)
=======
// store everything from database file to variables and then call print_row() to print rows (each projects)
void retrieve_data(const char *database, char *id, char *name, char* comment, char *status, char *mark)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
{
    FILE *fp;
    // Read file
    fp = fopen(database, "r");

<<<<<<< HEAD
    // Create structures to retrieve data to
    proj    _proj;
    eproj   _eproj;

    // Create pointer to struct to pass as parameter
    proj *p_proj = &_proj;

    // parse values from database lines (encrypted)
    while(fread(&_eproj, sizeof(eproj), 1, fp))
    {
        if (line_is_empty(_eproj.eid) && line_is_empty(_eproj.ename) && line_is_empty(_eproj.ecomment) &&
            line_is_empty(_eproj.estatus) && line_is_empty(_eproj.emark))
            continue;

        // decrypt parsed text
        decrypt_text(_eproj.eid, _proj.id, PROJ_ID);
        decrypt_text(_eproj.ename, _proj.name, PROJ_NAME);
        decrypt_text(_eproj.ecomment, _proj.comment, PROJ_COMMENT);
        decrypt_text(_eproj.estatus, _proj.status, PROJ_STATUS);
        decrypt_text(_eproj.emark, _proj.mark, PROJ_MARK);

        // print project
        print_row(p_proj);
=======
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
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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
<<<<<<< HEAD
void print_row(proj *p_proj)
=======
void print_row(char *id, char *name, char *comment, char *status, char *mark)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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
<<<<<<< HEAD
    if (strlen(p_proj->id) > 10 || strlen(p_proj->name) > 15 || strlen(p_proj->comment) > 25 || strlen(p_proj->status) > 15 || strlen(p_proj->mark) > 10)
=======
    if (strlen(id) > 10 || strlen(name) > 15 || strlen(comment) > 25 || strlen(status) > 15 || strlen(mark) > 10)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
    {
        buffer = 1;
    }
    while (buffer)
    {
        // Remaining or extra staffs
        char remaining_id[PROJ_ID], remaining_name[PROJ_NAME], remaining_comment[PROJ_COMMENT], remaining_status[PROJ_STATUS], remaining_mark[PROJ_MARK];

<<<<<<< HEAD
        // ID
        if (strlen(p_proj->id) > ID_FW)
        {
            // Set id and the remaining id (part)
            get_remaining_buffer(p_proj->id, ID_FW, remaining_id);     // store name skipping first 10 characters // pointer arithmatic
            // id now contains only 10 characters (excluding null byte)
            p_proj->id[ID_FW] = '\0';                // adding null byte means variable id ends at 11th character containing \0 at the 11th character
            strcpy(a.id, p_proj->id);                // replace a.id with the value of id because a.id will be printed
            strcpy(p_proj->id, remaining_id);        // replace id with remaining_id  because remaining_id will be re-initialised and may get buffer again from id
        }
        else
        {
            center_text(p_proj->id, ID_FW, a.id);
            // Nore more buffer is left
            strcpy(p_proj->id, "");
        }

        // Name
        if (strlen(p_proj->name) > NAME_FW)
        {
            get_remaining_buffer(p_proj->name, NAME_FW, remaining_name);
            p_proj->name[NAME_FW] = '\0';

            // Set a.name with max characters allowed
            strcpy(a.name, p_proj->name);
            strcpy(p_proj->name, remaining_name);
        }
        else
        {
            center_text(p_proj->name, NAME_FW, a.name);
            // Nore more buffer is left
            strcpy(p_proj->name, "");
        }

        // Comment
        if (strlen(p_proj->comment) > COMMENT_FW)
        {
            get_remaining_buffer(p_proj->comment, COMMENT_FW, remaining_comment);
            p_proj->comment[COMMENT_FW] = '\0';
            strcpy(a.comment, p_proj->comment);
            strcpy(p_proj->comment, remaining_comment);
        }
        else
        {
            center_text(p_proj->comment, COMMENT_FW, a.comment);
            // Nore more buffer is left
            strcpy(p_proj->comment, "");
        }

        // Status
        if (strlen(p_proj->status) > STATUS_FW)
        {
            get_remaining_buffer(p_proj->status, STATUS_FW, remaining_status);
            p_proj->status[STATUS_FW] = '\0';
            strcpy(a.status, p_proj->status);
            strcpy(p_proj->status, remaining_status);
        }
        else
        {
            center_text(p_proj->status, STATUS_FW, a.status);
            // Nore more buffer is left
            strcpy(p_proj->status, "");
        }

        // Mark
        if (strlen(p_proj->mark) > MARK_FW)
        {
            get_remaining_buffer(p_proj->mark, MARK_FW, remaining_mark);
            p_proj->mark[MARK_FW] = '\0';
            strcpy(a.mark, p_proj->mark);
            strcpy(p_proj->mark, remaining_mark);
        }
        else
        {
            center_text(p_proj->mark, MARK_FW, a.mark);
            // Nore more buffer is left
            strcpy(p_proj->mark, "");
=======
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
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
        }

        // print data with buffer
        printf("%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|%s%s%s|\n", KYEL, KNRM, a.id, KYEL, KNRM, a.name, KYEL, KNRM, a.comment, KYEL, KNRM, a.status, KYEL, KNRM, a.mark, KYEL);

        // Check for remaining buffer
<<<<<<< HEAD
        if (strlen(p_proj->id) == 0 && strlen(p_proj->name) == 0 && strlen(p_proj->comment) == 0 && strlen(p_proj->status) == 0 && strlen(p_proj->mark) == 0)
=======
        if (strlen(id) == 0 && strlen(name) == 0 && strlen(comment) == 0 && strlen(status) == 0 && strlen(mark) == 0)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
        {
            // end line
            printf("|__________|_______________|_________________________|_______________|__________|%s\n", KNRM);
            return;         // if no buffer remains
        }
    }

    // Center Texts
<<<<<<< HEAD
    center_text(p_proj->id, ID_FW, a.id);                    // ID
    center_text(p_proj->name, NAME_FW, a.name);              // Name
    center_text(p_proj->comment, COMMENT_FW, a.comment);     // Comment
    center_text(p_proj->status, STATUS_FW, a.status);        // Status
    center_text(p_proj->mark, MARK_FW, a.mark);              // Mark
=======
    center_text(id, ID_FW, a.id);                    // ID
    center_text(name, NAME_FW, a.name);              // Name
    center_text(comment, COMMENT_FW, a.comment);     // Comment
    center_text(status, STATUS_FW, a.status);        // Status
    center_text(mark, MARK_FW, a.mark);              // Mark
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170

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
<<<<<<< HEAD

    // Fetch data
    retrieve_data(database);
=======
    char id[PROJ_ID], name[PROJ_NAME], comment[PROJ_COMMENT], status[PROJ_STATUS], mark[PROJ_MARK];

    // Fetch data
    retrieve_data(database, id, name, comment, status, mark);
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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

<<<<<<< HEAD
    // Create struct to take input to
    proj _proj;

    // Take inputs
    printf("%sName of project:%s ", KCYN, KNRM);
    take_input(_proj.name, PROJ_NAME);

    printf("%sComment:%s ", KCYN, KNRM);
    take_input(_proj.comment, PROJ_COMMENT);

    printf("%sStatus:%s ", KCYN, KNRM);
    take_input(_proj.status, PROJ_STATUS);

    printf("%sMark:%s ", KCYN, KNRM);
    take_input(_proj.mark, PROJ_MARK);

    // Create pointer to struct to pass as argument
    proj *p_proj = &_proj;

    store_data(database, p_proj);
=======
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
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
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

<<<<<<< HEAD
    int id, current_id;
    char id_c[PROJ_ID];

    // Input ID to remove
    printf("%sID:%s ", KCYN, KNRM);
    take_input(id_c, PROJ_ID);

    // convert id from char[] to int
    id = atoi(id_c);

    // Create structs to read data to
    eproj _eproj;

    // iterate each line and replace the line containing id with whitespace characters
    while (fread(&_eproj, sizeof(eproj), 1, fp))
    {
        // decrypt parsed text
        decrypt_text(_eproj.eid, id_c, PROJ_ID);

        // convert id_c to interger and then store in current_id
        sscanf(id_c, "%d", &current_id);
        if (current_id == id)
        {
            #ifdef unix
            fseek(fp, sizeof(_eproj) * -1, SEEK_CUR);    // get to the start of line which will be replaced (made blank)
=======
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
            #ifdef unix
            fseek(fp, strlen(line) * -1, SEEK_CUR);    // get to the start of line which will be replaced (made blank)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
            #endif

            #ifdef WIN32
            // fseek treats \n as 2 characters . So we need to add +1 to cover another character
<<<<<<< HEAD
            fseek(fp, (sizeof(_eproj)+1) * -1, SEEK_CUR); // get to the start of line which will be replaced (made blank)
            #endif
            for (int i = 0; i < sizeof(_eproj)-1; i++)
=======
            fseek(fp, (strlen(line)+1) * -1, SEEK_CUR); // get to the start of line which will be replaced (made blank)
            #endif
            for (int i = 0; i < strlen(line)-1; i++)
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
            {
                fprintf(fp, " ");                             // Overwrite with whitespace upto \n newline
            }

            #ifdef unix
            fseek(fp, 1, SEEK_CUR);                           // Cover \n newline
            #endif

            #ifdef WIN32
            fseek(fp, 2, SEEK_CUR);                           // Cover \n newline  // fseek treats \n as 2 characters
            #endif
        }
    }
    fclose(fp);
}

<<<<<<< HEAD

void edit_project(const char *database)
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

    // Create structs to read data to
    proj  _proj;
    eproj _eproj;
    proj *p_proj = &_proj;      // pointer to proj  // stores address of _proj struct

    // Input ID to edit
    printf("%sID:%s ", KCYN, KNRM);
    take_input(_proj.id, PROJ_ID);

    // convert id from char[] to int
    // this is the id that will be edited
    int id, current_id;
    id = atoi(_proj.id);

    // Take inputs
    printf("%sName of project:%s ", KCYN, KNRM);
    take_input(_proj.name, PROJ_NAME);

    printf("%sComment:%s ", KCYN, KNRM);
    take_input(_proj.comment, PROJ_COMMENT);

    printf("%sStatus:%s ", KCYN, KNRM);
    take_input(_proj.status, PROJ_STATUS);

    printf("%sMark:%s ", KCYN, KNRM);
    take_input(_proj.mark, PROJ_MARK);

    // iterate each line and replace the line containing id with whitespace characters
    while (fread(&_eproj, sizeof(eproj), 1, fp))
    {
        // decrypt parsed text
        decrypt_text(_eproj.eid, _proj.id, PROJ_ID);

        // convert id to interger and then store in current_id
        sscanf(_proj.id, "%d", &current_id);

        // Edit if id matched
        if (current_id == id)
        {
            // Decrypt and retrieve other values (except the changed ones)
            if (strlen(_proj.name) == 0)
            {
                decrypt_text(_eproj.ename, _proj.name, PROJ_NAME);
            }
            if (strlen(_proj.comment) == 0)
            {
                decrypt_text(_eproj.ecomment, _proj.comment, PROJ_COMMENT);
            }
            if (strlen(_proj.status) == 0)
            {
                decrypt_text(_eproj.estatus, _proj.status, PROJ_STATUS);
            }
            if (strlen(_proj.mark) == 0)
            {
                decrypt_text(_eproj.emark, _proj.mark, PROJ_MARK);
            }

            #ifdef unix
            fseek(fp, sizeof(_eproj) * -1, SEEK_CUR);    // get to the start of line which will be replaced (made blank)
            #endif

            #ifdef WIN32
            // fseek treats \n as 2 characters . So we need to add +1 to cover another character
            fseek(fp, (sizeof(_eproj)+1) * -1, SEEK_CUR); // get to the start of line which will be replaced (made blank)
            #endif

            // remove project
            for (int i = 0; i < sizeof(_eproj)-1; i++)
            {
                fprintf(fp, " ");                             // Overwrite with whitespace upto \n newline
            }

            #ifdef unix
            fseek(fp, 1, SEEK_CUR);                           // Cover \n newline
            #endif

            #ifdef WIN32
            fseek(fp, 2, SEEK_CUR);                           // Cover \n newline  // fseek treats \n as 2 characters
            #endif

            // add new project (with the changes applied)
            store_data(database, p_proj);

            break;
        }
    }
    fclose(fp);
}
=======
/*
void edit_project(const char *database)
{
}
*/
>>>>>>> d8f619b09f55600de241cc94b86e7bf261f91170
