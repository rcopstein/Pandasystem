#include "defaults.c"

FILE* file;
dir_entry_t currentDir[32];
uint16_t FAT[CLUSTER_COUNT];

void load_folder(uint16_t address)
{
    fseek(file, address, SEEK_SET);
    memcpy(&currentDir, file, CLUSTER_SIZE);
}

void cmd_load(char* filename)
{
    file = fopen(filename, "r+");

    // Go to FAT start
    // Copy contents to FAT array

    fseek(file, CLUSTER_SIZE, SEEK_SET);
    memcpy(&FAT, file, CLUSTER_SIZE * 8);

    // Go to root dir start
    // Copy contents of first directory to currentDir

    load_folder(CLUSTER_SIZE * 9);

}