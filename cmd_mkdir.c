#include "defaults.c"

void cmd_mkdir(char* arg)
{
    if (!loaded) { printf("Please load a filesystem first\n"); return; }

    char* path = (char*) malloc(sizeof(char) * 50);
    strcpy(path, arg);

    // Get current open spot

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
    // podemos criar a pasta com o nome prev

    int i;
    for (i = 0; i < 32; ++i)
    {
        if (currentDir[i].attributes == 0 &&
            strcmp(currentDir[i].filename, "") == 0)
            {
                // Procurar um cluster vazio e
                // calcula o endereço

                int cluster = findFreeCluster(0);
                if (cluster == -1)
                { 
                    printf("Couldn't create folder \"%s\"\n", prev);
                    printf("No more clusters available\n"); 
                    return;
                }

                uint16_t block_address = cluster * CLUSTER_SIZE;

                // Cria a pasta nova

                dir_entry_t folder;

                folder.first_block = block_address;
                strcpy(&folder.filename, prev);
                folder.attributes = 0;
                folder.size = 0;

                int j;
                for (j = 0; j < 7; ++j) folder.reserved[i] = 0;

                currentDir[i] = folder;

                // Escreve entrada na FAT

                FAT[cluster] = block_address;

                // Escreve a região de memória apontada

                write_empty_folder(block_address);

                // Escreve as mudanças no arquivo

                dumpToFile();

                printf("Created \"%s\" at address %d\n", folder.filename, folder.first_block);

                return;
            }
    }

    // Se chegamos aqui, não tem mais espaço
    // pra acomodar ninguém

    printf("Couldn't create folder \"%s\"\n", prev);
    printf("Not enough espace\n");

}