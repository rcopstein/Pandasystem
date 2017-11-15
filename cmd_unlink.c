#include "defaults.c"

void cmd_unlink(char* arg)
{
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
    // podemos deletar o item com nome prev

    int i;
    for (i = 0; i < 32; ++i)
    {
        printf("Found %s\n", currentDir[i].filename);

        if (strcmp(currentDir[i].filename, prev) == 0)
            {
                // Se for um diretório

                if (currentDir[i].attributes == 0)
                {
                    // Testar se o diretório está vazio

                    uint16_t address = currentAddress;
                    load_folder(currentDir[i].first_block);

                    int j;
                    int flag = 1;

                    for (j = 0; j < 32; ++j)
                    {
                        printf("\tFound %s\n", currentDir[j].filename);
                        if (currentDir[j].attributes != 0 ||
                            strcmp(currentDir[j].filename, "") != 0)
                            {
                                flag = 0;
                                break;
                            }
                    }

                    if (flag == 0) {

                        printf("Folder is not empty, can't delete it\n");
                        return;

                    }
                    else {

                        load_folder(address);
                        printf("Deleting folder \"%s\"\n", currentDir[i].filename);

                        char* emptyFilename = "";
                        strcpy(currentDir[i].filename, emptyFilename);

                        printf("%s is the name\n", currentDir[i].filename);
                        printf("%d is the attribute\n", currentDir[i].attributes);

                        FAT[currentDir[i].first_block / CLUSTER_SIZE] = 0;
                        dumpToFile();
                        return;

                    }

                }
                else
                {
                    // Deletar o arquivo

                    char* emptyFilename = "";
                    strcpy(currentDir[i].filename, emptyFilename);
                    currentDir[i].attributes = 0;

                    FAT[currentDir[i].first_block / CLUSTER_SIZE] = 0;

                    dumpToFile();
                    return;
                }
            }
    }

    // Se chegamos aqui, não encontramos o item

    printf("Couldn't find item \"%s\"\n", prev);

}