#include "defaults.c"

void cmd_ls(char* path)
{
    // Go back to root

    load_root();

    // Break path into folders

    int i;
    char* delimiter = "/";
    char* tokens = strtok(path, delimiter);

    while (tokens)
    {
        printf("The token is: %s\n", tokens);

        for (i = 0; i < 32; ++i)
        {
            dir_entry_t dir = currentDir[i];

            if (strcmp(dir.filename, tokens) == 0 && dir.attributes == 0)
            {
                // Found file, load folder

                load_folder(dir.first_block);
                break;
            }
        }

        if (i == 32)
        {
            // Folder not found, return with error message

            printf("Folder \"%s\" not found\n", path);
            return;
        }

        tokens = strtok(NULL, delimiter);
    }

    printf("%d\n", currentAddress);

    // We are at the right folder, print files and folders

    for (i = 0; i < 32; i++)
    {
        printf("Panda: %s is %d\n", currentDir[i].filename, currentDir[i].attributes);
        if (currentDir[i].attributes != 0 || strcmp(currentDir[i].filename, "") == 0)
        {
            
        }
    }

}