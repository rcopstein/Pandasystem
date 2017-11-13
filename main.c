#include "defaults.c"
#include "cmd_init.c"
#include "cmd_load.c"
#include "cmd_ls.c"

void prompt(char* destination, char* prompt)
{
    printf("\n");
    printf("%s", prompt);
    scanf("%s", destination);
    printf("\n");
}

void main()
{
    // Clear the screen

    system("clear");

    // Show title

    printf("PandaSystem V1.0\n");
    printf("Created by Rafael Copstein and João Pedro Pianta\n");

    // Prompt the user

    char input[50];
    char buffer[] = "root/main";

    while (strcmp(input, "exit") != 0)
    {
        prompt(input, "> ");

             if (strcmp(input, "exit") == 0) {}
        else if (strcmp(input, "init") == 0) cmd_init(FILENAME);
        else if (strcmp(input, "load") == 0) cmd_load(FILENAME);
        else if (strcmp(input, "ls") == 0) { scanf("%s", buffer); cmd_ls(buffer); }
        else printf("Command \"%s\" not found\n", input);

    }

}

/*

    Boot Block -> 1 Cluster
    FAT -> 4096 entradas de 2 bytes = 8 Clusters = 8192 Bytes
    root -> 1 Cluster (32 entradas de diretórios)
    data clusters -> 4086 Clusters

*/