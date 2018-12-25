
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
  char szElf[4];

  FILE* file = fopen(elfFile, "r+");
  if(file) {
    fread(&header, 1, sizeof(header), file);

    readMagicMZ(szElf, &header);

    if (header.e_ident[0] == 0x7f && strcmp(szElf, "ELF") == 0 &&
       memcmp(header.e_ident, ELFMAG, SELFMAG) == 0 ) {

        memcpy(eHead, &header, sizeof(header));
    }
  }

  fclose(file);
}

#endif