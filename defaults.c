#ifndef DEFAULTS
#define DEFAULTS

    // Includes

    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>

    // Definitions

    #define SECTOR_SIZE 512
    #define CLUSTER_SIZE 1024
    #define CLUSTER_COUNT 4096
    #define FILENAME "fat.part"

    // Structs

    typedef struct{

        uint8_t filename[18];
        uint8_t attributes;
        uint8_t reserved[7];
        uint16_t first_block;
        uint32_t size;

    } dir_entry_t;

#endif