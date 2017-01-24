#include <errno.h>
#include <math.h>
#include <stdlib.h>

#include "parse_num_list.h"

#ifndef PARSE_STACK_INIT_SIZE
#define PARSE_STACK_INIT_SIZE 8
#endif

#define ISDIGIT(ch) ((ch) >= '0' && (ch) <= '9')
#define ISDIGIT1TO9(ch) ((ch) >= '1' && (ch) <= '9')

void parse_whitespace(char **numstr) {
  char *p = *numstr;
  while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    p++;
  *numstr = p;
}

int parse_number(char **numstr, double* np) {
  char *p = *numstr;
  if (*p == '-') p++;
  if (*p == '0') p++;
  else {
    if (!ISDIGIT1TO9(*p)) return PARSE_INVALID_VALUE;
    for (p++; ISDIGIT(*p); p++);
  }
  if (*p == '.') {
    p++;
    if (!ISDIGIT(*p)) return PARSE_INVALID_VALUE;
    for (p++; ISDIGIT(*p); p++);
  }
  if (*p == 'e' || *p == 'E') {
    p++;
    if (*p == '+' || *p == '-') p++;
    if (!ISDIGIT(*p)) return PARSE_INVALID_VALUE;
    for (p++; ISDIGIT(*p); p++);
  }
  errno = 0;
  *np = strtod(*numstr, NULL);
  if (errno == ERANGE && (*np == HUGE_VAL || *np == -HUGE_VAL))
    return PARSE_NUMBER_TOO_BIG;
  *numstr = p;
  return PARSE_OK;
}

int parse_num_list(char *numstr, num_list *list) {
  int ret;
  double num;

  parse_whitespace(&numstr);

  while ((ret = parse_number(&numstr, &num)) == PARSE_OK) {
    if (list->top >= list->size) {
      if (list->size == 0)
        list->size = PARSE_STACK_INIT_SIZE;
      else
        list->size += list->size >> 1; /* list->size * 1.5 */
      list->value = (double *)realloc(list->value, list->size);
    }

    list->top = list->top + 1;
    list->value[list->top - 1] = num;
    parse_whitespace(&numstr);
    if (*numstr == ',') numstr++;
    if (*numstr == '\n' || *numstr == '\0') break;
  }

  return ret;
}
