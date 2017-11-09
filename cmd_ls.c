#include "defaults.c"

void cmd_ls(char* path)
{
    // Break path into folders

    int i;
    char* delimiter = "/";
    char* tokens = strtok(path, delimiter);

    while (tokens)
    {
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

            printf("Folder not found");
            return;
        }

        tokens = strtok(NULL, delimiter);
    }

    // We are at the right folder, print files and folders

}