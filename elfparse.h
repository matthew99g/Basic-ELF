
#ifndef _ELF_PARSE__
#define _ELF_PARSE__

#include "vars.h"

// Copy ELF Magic Number to String
void readMagicMZ(char *szPtrELF, Elf32_Ehdr *eHead) {
  for(uint8_t i = 1; i < 4; i++) {
    szPtrELF[i - 1] = eHead->e_ident[i];
  }

  szPtrELF[3] = '\0';
}

// Find/Check Elf Header
void getELFHeader(const char* elfFile, Elf32_Ehdr *eHead) {
  Elf32_Ehdr header;

  FILE* file = fopen(elfFile, "r+");
  if(file) {
    fread(&header, 1, sizeof(header), file);

    if ((header.e_ident[0] == 0x7f && header.e_ident[1] == 'E' &&
       header.e_ident[2] == 'L' && header.e_ident[3] == 'F') &&
       header.e_type & ET_EXEC &&
       memcmp(header.e_ident, ELFMAG, SELFMAG) == 0 ) {

        memcpy(eHead, &header, sizeof(header));
    } else {
        uint8_t uNull = 0;

        memcpy(eHead, &uNull, sizeof(header));
    }
  }

  fclose(file);
}

#endif