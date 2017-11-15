#include "defaults.c"

void cmd_read(char* arg)
{
    if (!loaded) { printf("Please load a filesystem first\n"); return; }

    char* path = (char*) malloc(sizeof(char) * 50);
    strcpy(path, arg);

    // Walk the path

    load_root();

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
    // podemos ler o arquivo prev

    int i;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(currentDir[i].filename, prev) == 0)
        {
            char* buffer = (char *) malloc(CLUSTER_SIZE);

            fseek(file, currentDir[i].first_block, SEEK_SET);
            fread(buffer, CLUSTER_SIZE, 1, file);

            printf("%s\n", buffer);

            return;
        }
    }

    // Se chegamos aqui, não tem mais espaço
    // pra acomodar ninguém

    printf("Couldn't read file \"%s\"\n", prev);

}