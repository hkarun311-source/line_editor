#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024

typedef struct LineNode {
    char *text;
    struct LineNode *next;
} LineNode;

typedef struct {
    LineNode *head;
    int line_count;
} Document;

/* Initialize empty document */
void init_document(Document *doc) {
    doc->head = NULL;
    doc->line_count = 0;
}

/* Free all nodes */
void clear_document(Document *doc) {
    LineNode *curr = doc->head;
    while (curr != NULL) {
        LineNode *temp = curr;
        curr = curr->next;
        free(temp->text);
        free(temp);
    }
    doc->head = NULL;
    doc->line_count = 0;
}

/* Core 1: Insert Line at 1-based index */
int insert_line(Document *doc, int line_num, const char *content) {
    if (line_num < 1) line_num = 1;
    if (line_num > doc->line_count + 1) line_num = doc->line_count + 1;

    LineNode *new_node = (LineNode *)malloc(sizeof(LineNode));
    if (!new_node) return 0;

    new_node->text = (char *)malloc(strlen(content) + 1);
    if (!new_node->text) {
        free(new_node);
        return 0;
    }
    strcpy(new_node->text, content);
    new_node->next = NULL;

    if (line_num == 1) {
        new_node->next = doc->head;
        doc->head = new_node;
    } else {
        LineNode *curr = doc->head;
        for (int i = 1; i < line_num - 1 && curr->next != NULL; ++i) {
            curr = curr->next;
        }
        new_node->next = curr->next;
        curr->next = new_node;
    }

    doc->line_count++;
    return 1;
}

/* Core 2: Delete Line at 1-based index */
int delete_line(Document *doc, int line_num) {
    if (line_num < 1 || line_num > doc->line_count || doc->head == NULL) {
        return 0;
    }

    LineNode *to_delete = NULL;
    if (line_num == 1) {
        to_delete = doc->head;
        doc->head = doc->head->next;
    } else {
        LineNode *curr = doc->head;
        for (int i = 1; i < line_num - 1; ++i) {
            curr = curr->next;
        }
        to_delete = curr->next;
        curr->next = to_delete->next;
    }

    free(to_delete->text);
    free(to_delete);
    doc->line_count--;
    return 1;
}

/* Core 3: Display Document */
void display_document(const Document *doc) {
    if (doc->head == NULL) {
        printf("[Document is empty]\n");
        return;
    }
    int idx = 1;
    LineNode *curr = doc->head;
    while (curr != NULL) {
        printf("%4d | %s\n", idx++, curr->text);
        curr = curr->next;
    }
}

/* Core 4: Save to file */
int save_file(const Document *doc, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) return 0;

    LineNode *curr = doc->head;
    while (curr != NULL) {
        fprintf(fp, "%s\n", curr->text);
        curr = curr->next;
    }
    fclose(fp);
    return 1;
}

/* Core 4: Load from file */
int load_file(Document *doc, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    clear_document(doc);
    char buffer[MAX_LINE_LEN];

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        insert_line(doc, doc->line_count + 1, buffer);
    }
    fclose(fp);
    return 1;
}

/* Bonus: Search across document */
void search_document(const Document *doc, const char *query) {
    if (doc->head == NULL) {
        printf("[Document is empty]\n");
        return;
    }
    if (strlen(query) == 0) {
        printf("Error: Empty search query.\n");
        return;
    }

    int match_count = 0;
    int idx = 1;
    LineNode *curr = doc->head;

    while (curr != NULL) {
        if (strstr(curr->text, query) != NULL) {
            printf("Found on line %d: %s\n", idx, curr->text);
            match_count++;
        }
        curr = curr->next;
        idx++;
    }

    if (match_count == 0) {
        printf("Pattern \"%s\" not found.\n", query);
    } else {
        printf("Total matches: %d\n", match_count);
    }
}

/* Bonus: Line & Word count */
void document_stats(const Document *doc) {
    int words = 0;
    LineNode *curr = doc->head;
    while (curr != NULL) {
        const char *p = curr->text;
        int in_word = 0;
        while (*p) {
            if (isspace((unsigned char)*p)) {
                in_word = 0;
            } else if (!in_word) {
                in_word = 1;
                words++;
            }
            p++;
        }
        curr = curr->next;
    }
    printf("Lines: %d | Words: %d\n", doc->line_count, words);
}

int main(void) {
    Document doc;
    init_document(&doc);

    char cmd_line[MAX_LINE_LEN];
    printf("Line Editor v1.1 (Type 'h' for help, 'q' to quit)\n");

    while (1) {
        printf("ed> ");
        if (!fgets(cmd_line, sizeof(cmd_line), stdin)) break;

        cmd_line[strcspn(cmd_line, "\r\n")] = '\0';
        if (strlen(cmd_line) == 0) continue;

        char cmd;
        char arg[MAX_LINE_LEN] = {0};
        int num = 0;

        /* Check for search command: / <query> */
        if (cmd_line[0] == '/') {
            char *query = cmd_line + 1;
            while (*query == ' ') query++; /* Skip leading spaces */
            search_document(&doc, query);
            continue;
        }

        if (sscanf(cmd_line, " %c %d", &cmd, &num) == 2 && (cmd == 'i' || cmd == 'd')) {
            if (cmd == 'i') {
                char text_buf[MAX_LINE_LEN];
                printf("text: ");
                if (fgets(text_buf, sizeof(text_buf), stdin)) {
                    text_buf[strcspn(text_buf, "\r\n")] = '\0';
                    insert_line(&doc, num, text_buf);
                    printf("Line inserted at %d.\n", num);
                }
            } else if (cmd == 'd') {
                if (delete_line(&doc, num)) {
                    printf("Line %d deleted.\n", num);
                } else {
                    printf("Error: Invalid line number %d.\n", num);
                }
            }
        } else if (sscanf(cmd_line, " %c %s", &cmd, arg) == 2 && (cmd == 's' || cmd == 'l')) {
            if (cmd == 's') {
                if (save_file(&doc, arg)) printf("Document saved to %s.\n", arg);
                else printf("Error: Could not save to %s.\n", arg);
            } else if (cmd == 'l') {
                if (load_file(&doc, arg)) printf("Document loaded from %s.\n", arg);
                else printf("Error: Could not open %s.\n", arg);
            }
        } else {
            cmd = cmd_line[0];
            switch (cmd) {
                case 'p':
                    display_document(&doc);
                    break;
                case 'w':
                    document_stats(&doc);
                    break;
                case 'h':
                    printf("Commands:\n");
                    printf("  p           Print document\n");
                    printf("  i <n>       Insert line at position <n>\n");
                    printf("  d <n>       Delete line <n>\n");
                    printf("  / <query>   Search for word or phrase\n");
                    printf("  s <file>    Save to file\n");
                    printf("  l <file>    Load from file\n");
                    printf("  w           Print line and word count\n");
                    printf("  q           Quit\n");
                    break;
                case 'q':
                    clear_document(&doc);
                    printf("Goodbye!\n");
                    return 0;
                default:
                    printf("Unknown command. Type 'h' for help.\n");
                    break;
            }
        }
    }

    clear_document(&doc);
    return 0;
}