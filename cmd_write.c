#include "defaults.c"

void cmd_write(char* arg)
{
    if (!loaded) { printf("Please load a filesystem first\n"); return; }

    char* delimiter = "\"";
    char* content = strtok(arg, delimiter);
    content = strtok(NULL, delimiter);

    char content2[1024];
    strcpy(content2, content);

    char* path = strtok(NULL, delimiter); // Ignore o espaço

    delimiter = " ";
    path = strtok(path, delimiter);

    delimiter = "\n";
    path = strtok(path, delimiter);

    // Walk the path

    load_root();

    char* tok;
    delimiter = "/";
    char* prev = strtok(path, delimiter);

    while ((tok = strtok(NULL, delimiter)))
    {
        int i;
        int flag = 0;

        for (i = 0; i < 32; ++i)
        {
            if (currentDir[i].attributes == 0 && 
                strcmp(currentDir[i].filename, prev) == 0)
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
    // podemos escrever no arquivo prev

    int i;
    for (i = 0; i < 32; ++i)
    {
        if (strcmp(currentDir[i].filename, prev) == 0)
        {
            if (strlen(content2) > CLUSTER_SIZE) {

                printf("Size exceeded!\n");
                return;

            }

            fseek(file, currentDir[i].first_block, SEEK_SET);
            fwrite(content2, strlen(content2) * sizeof(char), 1, file);

            content = "\0";
            fwrite(content, sizeof(char), 1, file);

            int size = strlen(content2) - currentDir[i].size;
            currentDir[i].size = strlen(content2);
            dumpToFile();
            
            WalkAndIncrease(size, path);

            printf("Written to \"%s\" successfully!\n", currentDir[i].filename);
            return;
        }
    }

    // Se chegamos aqui, não tem mais espaço
    // pra acomodar ninguém

    printf("Couldn't write to file \"%s\"\n", prev);

}