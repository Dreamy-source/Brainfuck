 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("usage: %s <file.vnbf>\n", argv[0]);
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("cannot to open file: %s | [fail]\n", argv[1]);
        return 1;
    }
    printf("\n\n\n\n\n\n\n");
    printf("hallo! u started vnbf! let's compile your code!\n");
    putchar('\n');
    printf("opened file <%s> | [ok]\n", argv[1]);
    printf("reading <%s>\n", argv[1]);

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *code = malloc(file_size + 2);
    fread(code, 1, file_size, file);
    code[file_size] = '\0';
    fclose(file);

    putchar('\n');
    printf("yuhh! here is your code:\n");
    printf("------------------------------------------------\n");
    putchar('\n');

    unsigned char tape[30000] = {0};
    int ptr = 0;
    int size = strlen(code);

    for (int i = 0; i < size; i++) {
        char cmd = code[i];

        switch (cmd) {
            case '>': if (ptr < (int)(sizeof(tape) - 1)) ptr++; break;
            case '<': if (ptr > 0) ptr--; break;
            case '+': tape[ptr]++; break;
            case '-': tape[ptr]--; break;
            case '.': putchar(tape[ptr]); break;
            case ',': tape[ptr] = getchar(); break;
            case '[':
                if (tape[ptr] == 0) {
                    int depth = 1;
                    while (depth > 0) {
                        i++;
                        if (code[i] == '[') depth++;
                        if (code[i] == ']') depth--;
                    }
                }
                break;
            case ']':
                if (tape[ptr] != 0) {
                    int depth = 1;
                    while (depth > 0) {
                        i--;
                        if (code[i] == ']') depth++;
                        if (code[i] == '[') depth--;
                    }
                }
                break;
        }
    }
    free(code);
    putchar('\n');
    printf(" \n------------------------------------------------\n");
    printf("VNBF: code completed! (%s)\n goodbye! :3\n", argv[1]);
    printf("\n\n\n\n");

    return 0;
}
