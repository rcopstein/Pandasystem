#include "defaults.c"

void cmd_append(char* arg)
{
    if (!loaded) { printf("Please load a filesystem first\n"); return; }

    char* delimiter = "\"";
    char* content = strtok(arg, delimiter);
    content = strtok(NULL, delimiter);

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
            if (currentDir[i].size + strlen(content) > CLUSTER_SIZE) {

                printf("Size exceeded!\n");
                return;

            }

            int size = strlen(content);

            fseek(file, currentDir[i].first_block, SEEK_SET);
            while (fgetc(file) != '\0') {}
            fseek(file, -1, SEEK_CUR);

            //

            fwrite(content, strlen(content) * sizeof(char), 1, file);

            content = "\0";
            fwrite(content, sizeof(char), 1, file);

            currentDir[i].size += size;
            dumpToFile();

            WalkAndIncrease(size, path);

            //

            printf("Content appended successfully!\n");
            return;
        }
    }

    // Se chegamos aqui, não tem mais espaço
    // pra acomodar ninguém

    printf("Couldn't append to file \"%s\"\n", prev);

}