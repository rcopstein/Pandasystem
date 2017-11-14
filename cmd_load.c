#include "defaults.c"

FILE* file;
uint16_t currentAddress;
dir_entry_t currentDir[32];
uint16_t FAT[CLUSTER_COUNT];

void dumpToFile()
{
    fseek(file, currentAddress, SEEK_SET);
    fwrite(currentDir, CLUSTER_SIZE, 1, file);
}

void load_folder(uint16_t address)
{
    currentAddress = address;
    fseek(file, address, SEEK_SET);
    memcpy(&currentDir, file, CLUSTER_SIZE);
}

void load_root()
{
    load_folder(CLUSTER_SIZE * 9);
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

    load_root();

    // Print success message

    printf("PandaSystem loaded successfully from \"%s\"\n", filename);

}