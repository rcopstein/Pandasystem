#include "defaults.c"

int loaded = 0;

FILE* file;
uint16_t currentAddress;
dir_entry_t currentDir[32];
uint16_t FAT[CLUSTER_COUNT];

// Find free address in FAT

int findFreeCluster(int startingPoint)
{
    int i;
    for (i = 0; i < CLUSTER_COUNT; ++i)
    {
        if (FAT[(i + startingPoint % CLUSTER_COUNT)] == 0) return i;
    }

    return -1;
}

// Write the changes in memory to the file

void dumpToFile()
{
    // Rewrite the FAT

    fseek(file, CLUSTER_SIZE, SEEK_SET);
    fwrite(FAT, CLUSTER_COUNT * sizeof(uint16_t), 1, file);

    // Rewrite the current directory

    fseek(file, currentAddress, SEEK_SET);
    fwrite(currentDir, CLUSTER_SIZE, 1, file);
}

// Write folders into disk

void write_empty_folder(uint16_t address)
{
    int i;
    dir_entry_t emptyFolder = { "", 0, 0, 0, 0 };

    fseek(file, address, SEEK_SET);
    for (i = 0; i < 32; ++i) fwrite(&emptyFolder, 32, 1, file);
}

// Load folders into memory

void load_folder(uint16_t address)
{
    currentAddress = address;
    fseek(file, address, SEEK_SET);
    fread(&currentDir, CLUSTER_SIZE, 1, file);
}

void load_root()
{
    load_folder(CLUSTER_SIZE * 9);
}

// Load the file into memory

void cmd_load(char* filename)
{
    file = fopen(filename, "r+");

    // Go to FAT start
    // Copy contents to FAT array

    fseek(file, CLUSTER_SIZE, SEEK_SET);
    fread(&FAT, CLUSTER_SIZE * 8, 1, file);

    // Go to root dir start
    // Copy contents of first directory to currentDir

    load_root();

    // Print success message

    loaded = 1;
    printf("PandaSystem loaded successfully from \"%s\"\n", filename);

}