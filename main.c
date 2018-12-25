#include "elfparse.h"
#include "mem.h"

const char szFilePath[] =
"/home/okole/Projects/C/System_Programming/Pthread_adv/pthread";

int main(const int argc, const char *argv[]) {
  // Copy Header
  Elf32_Ehdr *eHeader = (Elf32_Ehdr *)writeMemoryHeap(sizeof(Elf32_Ehdr));
  getELFHeader(szFilePath, eHeader);

  // Double Check Stability
  if (checkEmpty(eHeader)) {
    fprintf(stderr, "Failed to find ELF Header\n");
  }

  char *szELF = (char *)writeMemoryHeap(sizeof(char) * 4);

  // strcpy ELF Magic Number
  readMagicMZ(szELF, eHeader);
  printf("Magic String: %s\n", szELF);

  // Free Specific Address
  freeMemoryHeapP(szELF);

  freeMemoryHeap();
  return 0;
}
