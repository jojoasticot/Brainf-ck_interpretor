#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

char* read_file(FILE* file) {
    char* buffer = malloc(1024); 

    size_t size = 1024;
    size_t length = 0;

    int c;
    while ((c = fgetc(file)) != EOF) {
        buffer[length++] = c;

        if (length >= size) {
            size *= 2;
            char *temp = realloc(buffer, size);
            if (temp == NULL) {
                fprintf(stderr, "Erreur de réallocation de mémoire.\n");
                fclose(file);
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }
    }

    buffer[length] = '\0';  // Ajoute le caractère nul à la fin de la chaîne
    fclose(file);
    return buffer;
}

int exe(char* string, char*pointer, int i)
{
    int end;
    char value;
    while (string[i] != 0)
    {
        char current = string[i];
        // printf("%c", current);

        switch(current)
        {
            case '+':
                (*pointer)++;
                break;
            case '-':
                (*pointer)--;
                break;
            case '>':
                pointer++;
                break;
            case '<':
                pointer--;
                break;
            case '.':
                printf("%c", *pointer);
                break;
            case ',':
                scanf("%c", &value);
                *pointer = value;
                break;
            case '[':
                end = -1;
                while (*pointer != 0)
                {
                    end = exe(string, pointer, i + 1);
                }

                if (end != -1)
                    i = end;
                else
                {
                    while (string[i] != ']')
                        i++;
                }

                break;
            case ']':
                return i;
            default:
                break;
        }
        i++;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
        errx(1, "Argument missing: ./main <bf_file>");

    char * filename = argv[1];
    
    if (strlen(filename) < 4)
        errx(1, "Invalid file name");

    FILE * f = fopen(filename, "r");
    char* string = read_file(f);
    char* pointer = calloc(10000, 1);
    exe(string, pointer, 0);


    free(pointer);
    return 0;
}
