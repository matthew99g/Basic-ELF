#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <link.h>

#define null 0;

const char szFilePath[] = "/home/okole/Projects/C/System_Programming/Pthread_adv/pthread";

int readELFHeader(const char* elfFile) {
  int iRet = null;

  // switch to Elf64_Ehdr for x64 architecture.
  Elf32_Ehdr header;

  FILE* file = fopen(elfFile, "r");
  if(file) {
    // read the header
    fread(&header, 1, sizeof(header), file);

    // check so its really an elf file
    if ((header.e_ident[0] == 0x7f &&
       header.e_ident[1] == 'E' &&
       header.e_ident[2] == 'L' &&
       header.e_ident[3] == 'F') &&
       memcmp(header.e_ident, ELFMAG, SELFMAG) == 0 ) {

       iRet = EXIT_SUCCESS;
    } else {
      fclose(file);

      iRet = EXIT_FAILURE;
    }

    // finally close the file
    fclose(file);
  }

  return iRet;
}

int main(const int argc, const char *argv[]) {
  // Call Function/Error Handle 
  if(readELFHeader(szFilePath)) {
    fprintf(stderr, "Invalid ELF File...\n");
  } else {
    printf("Valid ELF File Found...\n");
  }

  return EXIT_SUCCESS;
}
