#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <link.h>

const char szFilePath[] = "/home/okole/Projects/C/System_Programming/Pthread_adv/pthread";

void readMagicMZ(char *szPtrELF, Elf32_Ehdr *eHead) {
  for(uint8_t i = 1; i < 4; i++) {
    szPtrELF[i - 1] = eHead->e_ident[i];
  }

  szPtrELF[3] = '\0';
}

void readELFHeader(const char* elfFile, Elf32_Ehdr *eHead) {
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
      memcpy(eHead, 0x0, sizeof(header));
    }
  }

  fclose(file);
}

int main(int argc, char *argv[]) {
  Elf32_Ehdr *eHeader = (Elf32_Ehdr *)malloc(sizeof(Elf32_Ehdr));
  readELFHeader(szFilePath, eHeader);

  if (eHeader->e_ident[0] != 0x7f) {
    fprintf(stderr, "Failed to find ELF Header\n");
  }

  char *szELF = (char *)malloc(sizeof(char) * 4);

  readMagicMZ(szELF, eHeader);
  printf("Magic String: %s\n", szELF);

  free(szELF);

  free(eHeader);
  return 0;
}
