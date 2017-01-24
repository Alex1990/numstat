#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "numstat.h"
#include "measure.h"

extern const char* VERSION;

void print_version() {
  printf("%s\n", VERSION);
  exit(0);
}

void print_help() {
  printf("Usage: numstat [option]... <number_list>                       \n"
        "Output the measures of an list of numbers, such as count, sum,  \n"
        "minimum, maximum and so on.                                     \n"
        "                                                                \n"
        "  -m, --measure=[type] Specify the measure, the valid measure   \n"
        "                       can be count, sum, min, max, avg, median,\n"
        "                       avg, var, sd. The var is variance. The   \n"
        "                       sd is standard derivation. The default   \n"
        "                       meausre type is count                    \n"
        "  -h, --help      Print the help                                \n"
        "  -v, --version   Print the version\n");
  exit(0);
}

static struct option long_options[] = {
  {"measure", optional_argument, NULL, 'm'},
  {"help", no_argument, NULL, 'h'},
  {"version", no_argument, NULL, 'v'},
  {NULL, 0, NULL, 0}
};

int main (int argc, char **argv) {
  int c;
  char *measure;
  char *numstr;

  while (1) {
    int option_index = 0;

    c = getopt_long(argc, argv, "vhm::", long_options, &option_index);

    if (c == -1) break;

    switch (c) {
      case 'v':
        print_version();
        break;
      case 'h':
        print_help();
        break;
      case 'm':
        measure = malloc(strlen(optarg));
        strcpy(measure, optarg);
        break;
      default:
        abort();
    }
  }

  if (optind < argc) {
    numstr = argv[optind];
    printf("%s\n", numstr);
  }

  return 0;
}
