#include "defaults.c"
#include "cmd_init.c"

void main()
{
    // Create a new filesystem

    char* filename = "fat.part";
    FILE* file = cmd_init(filename);

}

/*

    Boot Block -> 1 Cluster
    FAT -> 4096 entradas de 2 bytes = 8 Clusters = 8192 Bytes
    root -> 1 Cluster (32 entradas de diretórios)
    data clusters -> 4086 Clusters

*/