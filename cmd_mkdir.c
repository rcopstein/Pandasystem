#include "defaults.c"

void cmd_mkdir(char* arg)
{
    // Get current open spot

    load_root();
    char* path = (char*) malloc(sizeof(char) * 50);
    strcpy(path, arg);

    char* tok;
    char* delimiter = "/";
    char* prev = strtok(path, delimiter);

    while ((tok = strtok(NULL, delimiter)))
    {
        int i;
        int flag = 0;

        for (i = 0; i < 32; ++i)
        {
            if (strcmp(currentDir[i].filename, prev) == 0)
            {
                load_folder(currentDir[i].first_block);
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            printf("Path \"%s\" not found\n", arg);
            return;
        }

        prev = tok;
    }

    // Se chegar aqui, estamos no lugar certo e 
    // podemos criar a pasta com o nome prev

    int i;
    for (i = 0; i < 32; ++i)
    {
        if (currentDir[i].attributes == 0 &&
            strcmp(currentDir[i].filename, "") == 0)
            {
                // Encontrou um lugar vazio

                dir_entry_t folder = { prev, 0, 0, 0, 0 };
                currentDir[i] = folder;
                dumpToFile();

                return;
            }
    }

    // Se chegamos aqui, não tem mais espaço
    // pra acomodar ninguém

    printf("Couldn't create folder \"%s\"\n", prev);
    printf("Not enough espace\n");

}