#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define INITIAL_CAPACITY 10

// Dynamic Array Document Structure
typedef struct {
    char** lines;
    int count;
    int capacity;
} Document;

// Initialize document memory
void init_doc(Document* doc) {
    doc->count = 0;
    doc->capacity = INITIAL_CAPACITY;
    doc->lines = (char**)malloc(doc->capacity * sizeof(char*));
}

// Display document contents with 1-based line numbers
void display_doc(Document* doc) {
    if (doc->count == 0) {
        printf("\n--- [Document is empty] ---\n\n");
        return;
    }
    printf("\n--- DOCUMENT START ---\n");
    for (int i = 0; i < doc->count; i++) {
        printf("%3d | %s\n", i + 1, doc->lines[i]);
    }
    printf("--- DOCUMENT END ---\n\n");
}

// Insert line at target line number (1-based)
void insert_line(Document* doc, int line_num, const char* text) {
    if (line_num < 1 || line_num > doc->count + 1) {
        printf("Error: Line number %d out of bounds! (Valid range: 1 to %d)\n", line_num, doc->count + 1);
        return;
    }

    // Expand array capacity if full
    if (doc->count >= doc->capacity) {
        doc->capacity *= 2;
        doc->lines = (char**)realloc(doc->lines, doc->capacity * sizeof(char*));
    }

    int idx = line_num - 1;

    // Shift existing lines to the right
    for (int i = doc->count; i > idx; i--) {
        doc->lines[i] = doc->lines[i - 1];
    }

    // Allocate memory for line string and copy text
    doc->lines[idx] = (char*)malloc(strlen(text) + 1);
    strcpy(doc->lines[idx], text);
    doc->count++;

    printf("Line %d inserted successfully.\n", line_num);
}

// Delete line at target line number (1-based)
void delete_line(Document* doc, int line_num) {
    if (doc->count == 0) {
        printf("Error: Document is empty!\n");
        return;
    }
    if (line_num < 1 || line_num > doc->count) {
        printf("Error: Line number %d out of bounds! (Valid range: 1 to %d)\n", line_num, doc->count);
        return;
    }

    int idx = line_num - 1;

    // Free memory of target line
    free(doc->lines[idx]);

    // Shift lines to the left
    for (int i = idx; i < doc->count - 1; i++) {
        doc->lines[i] = doc->lines[i + 1];
    }

    doc->count--;
    printf("Line %d deleted successfully.\n", line_num);
}

// Save document to a text file
void save_file(Document* doc, const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Cannot open file '%s' for writing.\n", filename);
        return;
    }

    for (int i = 0; i < doc->count; i++) {
        fprintf(fp, "%s\n", doc->lines[i]);
    }

    fclose(fp);
    printf("Document saved to '%s' successfully.\n", filename);
}

// Free memory allocation on program exit
void free_doc(Document* doc) {
    for (int i = 0; i < doc->count; i++) {
        free(doc->lines[i]);
    }
    free(doc->lines);
}

// Interactive command loop
int main() {
    Document doc;
    init_doc(&doc);

    char input[MAX_LINE_LEN];
    printf("======================================\n");
    printf("      Simple Command Line Editor      \n");
    printf("======================================\n");
    printf("Commands:\n");
    printf("  I <line_no> <text> : Insert line\n");
    printf("  D <line_no>        : Delete line\n");
    printf("  P                  : Print document\n");
    printf("  S <filename>       : Save to file\n");
    printf("  Q                  : Quit program\n");
    printf("======================================\n\n");

    while (1) {
        printf("editor> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        // Strip trailing newline character
        input[strcspn(input, "\r\n")] = 0;

        if (strlen(input) == 0) continue;

        char cmd = input[0];

        if (cmd == 'Q' || cmd == 'q') {
            break;
        } 
        else if (cmd == 'P' || cmd == 'p') {
            display_doc(&doc);
        } 
        else if (cmd == 'I' || cmd == 'i') {
            int line_num;
            char text[MAX_LINE_LEN];
            if (sscanf(input + 1, "%d %[^\n]", &line_num, text) == 2) {
                insert_line(&doc, line_num, text);
            } else {
                printf("Invalid format! Usage: I <line_number> <text>\n");
            }
        } 
        else if (cmd == 'D' || cmd == 'd') {
            int line_num;
            if (sscanf(input + 1, "%d", &line_num) == 1) {
                delete_line(&doc, line_num);
            } else {
                printf("Invalid format! Usage: D <line_number>\n");
            }
        } 
        else if (cmd == 'S' || cmd == 's') {
            char filename[MAX_LINE_LEN];
            if (sscanf(input + 1, "%s", filename) == 1) {
                save_file(&doc, filename);
            } else {
                printf("Invalid format! Usage: S <filename>\n");
            }
        } 
        else {
            printf("Unknown command! Use I, D, P, S, or Q.\n");
        }
    }

    free_doc(&doc);
    printf("Exiting editor. Goodbye!\n");
    return 0;
}