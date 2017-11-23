#include "defaults.c"

void cmd_ls(char* path)
{
    if (!loaded) { printf("Please load a filesystem first\n"); return; }

    // Go back to root

    load_root();

    // Break path into folders

    int i;
    char* delimiter = "/";
    char* tokens = strtok(path, delimiter);

    while (tokens)
    {
        for (i = 0; i < 32; ++i)
        {
            dir_entry_t dir = currentDir[i];

            if (currentDir[i].attributes == 0 &&
                strcmp(dir.filename, tokens) == 0 && dir.attributes == 0)
            {
                // Found file, load folder

                load_folder(dir.first_block);
                break;
            }
        }

        if (i == 32)
        {
            // Folder not found, return with error message

            printf("Folder \"%s\" not found\n", tokens);
            return;
        }

        tokens = strtok(NULL, delimiter);
    }

    // We are at the right folder, print files and folders

    for (i = 0; i < 32; i++)
    {
        if (currentDir[i].attributes != 0 || strcmp(currentDir[i].filename, "") != 0)
        {
            if (currentDir[i].attributes == 1) printf("File: ");
            if (currentDir[i].attributes == 0) printf("Folder: ");

            printf("%s %d bytes\n", currentDir[i].filename, currentDir[i].size);
        }
    }

    printf("END\n");

}