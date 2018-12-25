#define LARGE

#include "memlib.h"
#include "elfparse.h"

// My Test Application
const char szFilePath[] =
"/home/okole/Projects/C/System_Programming/Pthread_adv/pthread";

int main(const int argc, const char *argv[]) {
  // Copy Header
  Elf32_Ehdr *eHeader = (Elf32_Ehdr *)writeMemoryHeap(sizeof(Elf32_Ehdr));
  getELFHeader(szFilePath, eHeader);

  // Double Check Stability
  if (checkEmptyPtr(eHeader)) {
    fprintf(stderr, "Failed to find ELF Header\n");
    exit(1);
  }

  PHEAP_STRING szELF = hStringInit(0);

  // strcpy ELF Magic Number
  readMagicMZ(szELF->iValue, eHeader);
  printf("Magic String: %s\n", szELF->iValue);

  // Free Specific Address
  freeHString(szELF); // or freeMemoryHeapP(szELF)

  // Free Entire Heap
  freeMemoryHeap();
  return 0;
}
