#ifndef _MEM__
#define _MEM__

#include "elfparse.h" 
#include "vars.h"

// Error Check Malloc
void *ec_malloc(unsigned int mem) {
    void *ptr = malloc(mem);
    if(!ptr) {
        fprintf(stderr, "Failed to Allocate Memory\n");
        exit(1);
    }

    return ptr;
}

// Check if data is empty
uint8_t checkEmpty(void *ptr, const char *szType) {
    if(!strcmp(szType, "Elf32_Ehdr")) {
        Elf32_Ehdr null;

        if(memcmp((Elf32_Ehdr *)ptr, &null, sizeof(Elf32_Ehdr))) {
            return 1;
        }

        return 0;
    } else if(!strcmp(szType, "char")) {
        char null;

        if(memcmp((char *)ptr, &null, sizeof(char))) {
            return 1;
        }

        return 0;
    }
}

// Write Memory To Heap and Store Address
void *writeMemoryHeap(unsigned int uMem, const char *szType) {
    if(!strcmp(szType, "char")) {
        char *ptr = (char *)ec_malloc(uMem);

        bAddressList[bSave] = ptr;

        bSave++;
        return ptr;
    } else if(!strcmp(szType, "Elf32_Ehdr")) {
        Elf32_Ehdr *ptr = (Elf32_Ehdr *)ec_malloc(uMem);

        bAddressList[bSave] = ptr;

        bSave++;
        return ptr;
    }
}

// Free Remaining Memory
void freeMemoryHeap() {
    for(uint8_t i = 0; i < bSave; i++) {
        free(bAddressList[i]);
    }
}

// Free Specific Memory and pop Address off of Save Stack
void freeMemoryHeapP(void *ptr) {
    for(uint8_t i = 0; i < 64; i++) {
        if(bAddressList[i] == ptr) {
            free(bAddressList[i]);

            bSave--;

            bAddressList[i] = 0x0;
            break;
        }
    }

    uint8_t state = 0x0;

    while(!state) {
        for(uint8_t i = 0; i < 64; i++) {
            if(bAddressList[i + 1] && !bAddressList[i]) {
                state = 0x0;
                bAddressList[i] = bAddressList[i + 1];
                bAddressList[i + 1] = 0;
            } else {
                state = 0x1;
            }
        }
    }
}

#endif