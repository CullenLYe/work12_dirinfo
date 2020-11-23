#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#define LINE "--------------------------------------------\n"

struct dirent *entry;
struct stat sb;
int sum;
char *direc;
DIR *d;

int main(int argc, char **argv) {
  if (argc>1) direc = argv[1];
  else {
    printf("Please enter a directory: ");
    direc = malloc(100);
    scanf("%s", direc);
  }
  d = opendir(direc);
  if (!d) {
    printf("errno: %d\terror: %s\n", errno, strerror(errno));
    exit(0);
  }
  entry = readdir(d);
  printf("\nStatistics For Directory: %s\n\n", direc);

  // Go through and check for directories.
  printf("%sDirectories:\n%s", LINE, LINE);
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
  printf("%sRegular Files:\n%s", LINE, LINE);
  d = opendir(direc);
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
  printf("%sTotal Directory Size:\n%s", LINE, LINE);
  printf("\t%d Bytes\n\t%f KB\n\t%f MB\n\t%f GB\n", sum, kb, mb, gb);

  return 0;

}
