#ifndef PARSE_NUM_LIST_H__
#define PARSE_NUM_LIST_H__

typedef struct {
  double* value;
  int top;
  int size;
} num_list;

enum {
  PARSE_OK = 0,
  PARSE_EXPECT_VALUE,
  PARSE_INVALID_VALUE,
  PARSE_NUMBER_TOO_BIG
};

int parse_num_list(char *numstr, num_list *list);

#endif /* PARSE_NUM_LIST_H__ */
