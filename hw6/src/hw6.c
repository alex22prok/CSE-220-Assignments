#include "hw6.h"

void replace_and_write_line(FILE* out, const char* line, const char* search, const char* replace);

int main(int argc, char *argv[]) {
    if (argc < 7) {
        return MISSING_ARGUMENT;
    }

    //Input and output file are always last two arguments
    char* infile = argv[argc - 2];
    char* outfile = argv[argc - 1];

    //Variables to store options
    char *search_text = NULL;
    char *replace_text = NULL;
    char *line_range = NULL;
    int start_line = 1, end_line = -1;  //default start and end

    //Flags for detecting duplicates
    int s_seen = 0, r_seen = 0, l_seen = 0;

    //loop until input file arg
    for (int i = 1; i < argc - 2; i++) { 
        //-s case
        if (strcmp(argv[i], "-s") == 0) { 
            if (s_seen++) 
            {
                return DUPLICATE_ARGUMENT;
            }
            if (i + 1 >= argc - 2 || argv[i + 1][0] == '-') 
            {
                return S_ARGUMENT_MISSING;
            }
            search_text = argv[++i];
        }
        //-r case 
        else if (strcmp(argv[i], "-r") == 0) { 
            if (r_seen++) 
            {
                return DUPLICATE_ARGUMENT;
            }
            if (i + 1 >= argc - 2 || argv[i + 1][0] == '-') 
            {
                return R_ARGUMENT_MISSING;
            }
            replace_text = argv[++i];
        } 
        //-l case
        else if (strcmp(argv[i], "-l") == 0) { 
            if (l_seen++) 
            {
                return DUPLICATE_ARGUMENT;
            }
            if (i + 1 >= argc - 2 || argv[i + 1][0] == '-') 
            {
                return L_ARGUMENT_INVALID;
            }
            line_range = argv[++i];
        }
    }

    //Check if -s and -r were missing or lacked arguments
    if (!search_text) return S_ARGUMENT_MISSING;
    if (!replace_text) return R_ARGUMENT_MISSING;

    //if given line range
    if (line_range) {
        char *token = strtok(line_range, ",");
        if (!token) 
        {
            return L_ARGUMENT_INVALID;
        }
        start_line = strtol(token, NULL, 10);

        token = strtok(NULL, ",");
        if (!token) {
            return L_ARGUMENT_INVALID;
        }
        end_line = strtol(token, NULL, 10);

        if (start_line <= 0 || end_line <= 0 || start_line > end_line)
        {
            return L_ARGUMENT_INVALID;
        }
    }

    //Open input file
    FILE *in_fp = fopen(infile, "r");
    if (!in_fp) {return INPUT_FILE_MISSING;}

    //Open output file
    FILE *out_fp = fopen(outfile, "w");
    if (!out_fp) {
        fclose(in_fp);
        return OUTPUT_FILE_UNWRITABLE;
    }

    char buffer[MAX_LINE + 2];  //+2 for \n and \0
    int line_num = 1;

    while (fgets(buffer, sizeof(buffer), in_fp) != NULL) {
        if (line_num >= start_line && (end_line == -1 || line_num <= end_line)) {
            if (strstr(buffer, search_text)) {
                replace_and_write_line(out_fp, buffer, search_text, replace_text);
            } else {
                fputs(buffer, out_fp);
            }
        } else {
            fputs(buffer, out_fp);
        }
        line_num++;
    }

    fclose(in_fp);
    fclose(out_fp);
    return 0;  //success
}

void replace_and_write_line(FILE* out, const char* line, const char* search, const char* replace) {
    size_t search_len = strlen(search);
    size_t replace_len = strlen(replace);
    const char *p = line;

    while (*p) {
        const char* match = strstr(p, search);
        if (!match) {
            fputs(p, out);  //Write remainder of the line
            break;
        }

        //Write part before the match
        fwrite(p, 1, match - p, out);
        //Write the replacement text
        fwrite(replace, 1, replace_len, out);

        //Move past the matched text
        p = match + search_len;
    }
}
