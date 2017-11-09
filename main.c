#include "defaults.c"
#include "cmd_init.c"
#include "cmd_load.c"
#include "cmd_ls.c"

void main()
{
    // Create a new filesystem
    
    cmd_init(FILENAME);
    cmd_load(FILENAME);

    char* buffer = "root/main";
    cmd_ls(buffer);

}

/*

    Boot Block -> 1 Cluster
    FAT -> 4096 entradas de 2 bytes = 8 Clusters = 8192 Bytes
    root -> 1 Cluster (32 entradas de diretórios)
    data clusters -> 4086 Clusters

*/