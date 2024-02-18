#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

// function that checks if there is a valid identifier character
int isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// function that checks if there is a integer character
int isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Function to tokenize MiniLang source code
void tokenize(char *sourceCode) {
    int len = strlen(sourceCode);
    int i = 0;

    // iterate over the whole array
    while (i < len) {
        // if there is any white spaces we skip them
        while (isspace(sourceCode[i])) {
            i++;
        }

        // check for any comments in the source file
        if (sourceCode[i] == '/' && sourceCode[i + 1] == '/') {
            printf("Token Type: COMMENT, Lexeme: ");
            while (sourceCode[i] != '\n' && i < len) {
                printf("%c", sourceCode[i]);
                i++;
            }
            printf("\n");
            continue;
        }

        // check for any operators in the file
        if (sourceCode[i] == '+' || sourceCode[i] == '-' || sourceCode[i] == '*' || sourceCode[i] == '/' ||
            sourceCode[i] == '=' || (sourceCode[i] == '=' && sourceCode[i + 1] == '=') ||
            (sourceCode[i] == '!' && sourceCode[i + 1] == '=')) {
            printf("Token Type: OPERATOR, Lexeme: %c\n", sourceCode[i]);
            i++;
            continue;
        }

        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "print", 5) == 0 || strncmp(&sourceCode[i], "false", 5) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 5, &sourceCode[i]);
                i += 5;
                continue;
            }
        }
        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "if", 2) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 2, &sourceCode[i]);
                i += 2;
                continue;
            }
        }
        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "else", 4) == 0 || strncmp(&sourceCode[i], "true", 4) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 4, &sourceCode[i]);
                i += 4;
                continue;
            }
        }

        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "char", 4) == 0 || strncmp(&sourceCode[i], "bool", 4) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 4, &sourceCode[i]);
                i += 4;
                continue;
            }
        }
        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "int", 3) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 3, &sourceCode[i]);
                i += 3;
                continue;
            }
        }
        // check for any keywords in the file
        if (strncmp(&sourceCode[i], "float", 5) == 0) {
            if (isspace(sourceCode[i + 2]) || sourceCode[i + 2] == '(') {
                printf("Token Type: KEYWORD, Lexeme: %.*s\n", 5, &sourceCode[i]);
                i += 5;
                continue;
            }
        }

        // check for any identifiers
        if (isLetter(sourceCode[i])) {
            printf("Token Type: IDENTIFIER, Lexeme: ");
            while (isLetter(sourceCode[i]) || isDigit(sourceCode[i])) {
                printf("%c", sourceCode[i]);
                i++;
            }
            printf("\n");
            continue;
        }

        // check for any integers
        if (isDigit(sourceCode[i])) {
            printf("Token Type: INTEGER, Lexeme: ");
            while (isDigit(sourceCode[i])) {
                printf("%c", sourceCode[i]);
                i++;
            }
            printf("\n");
            continue;
        }

        // check for any parenthesis in the file
        if (sourceCode[i] == '(' || sourceCode[i] == ')' ||
            sourceCode[i] == '{' || sourceCode[i] == '}') {
            printf("Token Type: PARENTHESIS, Lexeme: %c\n", sourceCode[i]);
            i++;
            continue;
        }

        // check for any delimiter in the file
        if (sourceCode[i] == ';') {
            printf("Token Type: DELIMITER, Lexeme: %c\n", sourceCode[i]);
            i++;
            continue;
        }

        // if there is any invalid token output it
        printf("Token Type: ERROR, Lexeme: %c\n", sourceCode[i]);
        i++;
    }
}

int main(int argc, char* argv[]) {

    // check if file name was provided
    if(argc < 2){
        printf("Profile the Source file name as command line argument!\n");
        printf("%s <fileName>\n", argv[0]);
        exit(-1);
    }

    // open the source file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    // get the number of characters in the source file
    off_t fileSize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // allocate memory to store the contents of the source file
    char *sourceCode = (char *)malloc(fileSize + 1);
    if (sourceCode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        close(fd);
        return 1;
    }

    // read the file contents and store it in the allocated array
    ssize_t bytesRead = read(fd, sourceCode, fileSize);
    if (bytesRead != fileSize) {
        fprintf(stderr, "Error reading file.\n");
        close(fd);
        free(sourceCode);
        return 1;
    }
    // add a null termination at the end
    sourceCode[fileSize] = '\0';
    close(fd);

    // call the tokensize function that will tokenize the source code
    tokenize(sourceCode);

    // free the dynamically allocated memory
    free(sourceCode);

    return 0;
}