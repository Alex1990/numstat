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
        "Output the measures of an list of numbers, such as sum, avg,    \n"
        "minimum, maximum and so on.                                     \n"
        "                                                                \n"
        "  -m, --measure=[type] Specify the measure, the valid measure   \n"
        "                       can be sum, min, max, avg, median,       \n"
        "                       avg, var, sd. The var is variance. The   \n"
        "                       sd is standard derivation. The default   \n"
        "                       measure type is sum                      \n"
        "  -h, --help      Print the help                                \n"
        "  -v, --version   Print the version                             \n"
        "                                                                \n"
        "The <number_list> is a list of numbers separated by commons. \n");
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
  int ret;
  char *measure;
  char *numstr;
  double result;
  num_list nl;

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
        measure = (char *) malloc(sizeof(char) * (strlen(optarg) + 1));
        strcpy(measure, optarg);
        break;
      default:
        abort();
    }
  }

  if (optind < argc) {
    numstr = argv[optind];
    ret = parse_num_list(numstr, &nl);

    if (ret == PARSE_OK) {
      if (strcmp(measure, "min") == 0) {
        result = min(nl.top, nl.value);
      } else if (strcmp(measure, "max") == 0) {
        result = max(nl.top, nl.value);
      } else if (strcmp(measure, "median") == 0) {
        result = median(nl.top, nl.value);
      } else if (strcmp(measure, "avg") == 0) {
        result = avg(nl.top, nl.value);
      } else if (strcmp(measure, "variance") == 0 ||
          strcmp(measure, "var") == 0) {
        result = variance(nl.top, nl.value);
      } else if (strcmp(measure, "standard_deviation") == 0 ||
          strcmp(measure, "sd") == 0) {
        result = standard_deviation(nl.top, nl.value);
      } else {
        result = sum(nl.top, nl.value);
      }
      printf("%f\n", result);
    } else {
      return ret;
    }
  }

  return 0;
}
