#include "defaults.c"

// Writes the default root

void cmd_init_writeRootDir(FILE* file)
{
    dir_entry_t emptyFolder = { "", 0, 0, 0, 0 };

    int i;
    for (i = 0; i < 32; ++i) fwrite(&emptyFolder, 32, 1, file);
}

// Writes the default FAT

void cmd_init_writeFATEntry(uint16_t data, FILE* file, int times)
{
    int i;
    for (i = 0; i < times; ++i) fwrite(&data, 2, 1, file);
}
void cmd_init_writeFAT(FILE* file)
{
    cmd_init_writeFATEntry(0xfffd, file, 1);    // Boot Block Entry
    cmd_init_writeFATEntry(0xfffe, file, 8);    // Write FAT entries on FAT
    cmd_init_writeFATEntry(0xffff, file, 1);    // Write EOF to FAT
    cmd_init_writeFATEntry(0x0000, file, 4086); // Write directory entries
}

// Writes the boot block to
// the given file

void cmd_init_writeBootBlock(FILE* file)
{
    int i;
    char data = 0xbb;
    for (i = 0; i < CLUSTER_SIZE; ++i) fwrite(&data, 1, 1, file);
}

// Creates a new filesystem for
// the given filename

FILE* cmd_init(char* filename)
{
    FILE* file = fopen(filename, "w+");

    cmd_init_writeBootBlock(file);
    cmd_init_writeFAT(file);
    cmd_init_writeRootDir(file);

    return file;
}