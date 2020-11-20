#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

#define LINE "--------------------------------------------\n"

DIR *d;
struct dirent *entry;
struct stat sb;
int sum;

int main() {
  d = opendir(".");
  entry = readdir(d);
  printf("\nStatistics For Directory: %s\n\n", entry->d_name);

  // Go through and check for directories.
  printf(LINE);
  printf("Directories:\n");
  printf(LINE);
  while (entry!=NULL) {
    stat(entry->d_name, &sb);
    if (S_ISDIR(sb.st_mode)) {
      printf("File Name: %s\n", entry->d_name);
      printf("\tPermissions: %o\n", sb.st_mode);
      printf("\tLast Access: %s\n", ctime(&(sb.st_atime)));
      sum+=sb.st_size;
    }
    entry = readdir(d);
  }
  closedir(d);

  // Go through once again and check for regular files.
  printf(LINE);
  printf("Regular Files:\n");
  printf(LINE);
  d = opendir(".");
  entry = readdir(d);
  while (entry!=NULL) {
    stat(entry->d_name, &sb);
    if (S_ISREG(sb.st_mode)) {
      printf("File Name: %s\n", entry->d_name);
      printf("\tPermissions: %o\n", sb.st_mode);
      printf("\tLast Access: %s", ctime(&(sb.st_atime)));
      printf("\tFile Size: %ld\n\n", sb.st_size);
      sum+=sb.st_size;
    }
    entry = readdir(d);
  }
  closedir(d);

  // Print total directory size.
  float kb = (double) sum / 1000;
  float mb = (double) sum / 1000000;
  float gb = (double) sum / 1000000000;
  printf(LINE);
  printf("Total Directory Size:\n");
  printf(LINE);
  printf("\t%d Bytes\n\t%f KB\n\t%f MB\n\t%f GB\n", sum, kb, mb, gb);

  return 0;

}
