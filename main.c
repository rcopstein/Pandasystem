#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR_SIZE 512
#define CLUSTER_SIZE 1024
#define CLUSTER_COUNT 4096

typedef struct{

    uint8_t filename[18];
    uint8_t attributes;
    uint8_t reserved[7];
    uint16_t first_block;
    uint32_t size;

} dir_entry_t;

void fillFile(FILE* file, void* data, int size, int quant)
{
    int i = 0;
    for (; i < quant; ++i) fwrite(data, size, 1, file);
}

void main()
{
    // Create / Read the file

    char* access = "w+";
    char* filename = "fat.part";
    FILE* file = fopen(filename, access);

    fseek(file, 0, SEEK_SET);

    // Load basic structure

    char data[2];

    data[0] = 0xbb;
    fillFile(file, &data, 1, CLUSTER_SIZE); // Fill boot block

    data[0] = 0xff;
    data[1] = 0xfd;
    fwrite(&data, 2, 1, file); // Write boot block entry on FAT

    int i;
    data[0] = 0xff;
    data[1] = 0xfe;
    for (i = 0; i < 8; ++i) fwrite(&data, 2, 1, file); // Write FAT entries on FAT

    data[0] = 0xff;
    data[1] = 0xff;
    fwrite(&data, 2, 1, file); // Write EOF to FAT

    data[0] = 0x00;
    data[1] = 0x00;
    for (i = 0; i < 4086; ++i) fwrite(&data, 2, 1, file); // Write directory entries on FAT

    // Fill root block

    dir_entry_t emptyFolder = { "", 0, 0, 0, 0 };
    fillFile(file, &emptyFolder, 32, 32);

}

/*

    Boot Block -> 1 Cluster
    FAT -> 4096 entradas de 2 bytes = 8 Clusters = 8192 Bytes
    root -> 1 Cluster (32 entradas de diretórios)
    data clusters -> 4086 Clusters

*/