#include <math.h>

double sum(int size, double *list) {
  double result = 0.0;

  for (int i = 0; i < size; i++)
    result += *list++;

  return result;
}

double min(int size, double *list) {
  double result = *list++;

  for (int i = 0; i < size; i++)
    if (*list < result) result = *list++;

  return result;
}

double max(int size, double *list) {
  double result = *list++;

  for (int i = 0; i < size; i++)
    if (*list > result) result = *list++;

  return result;
}

double median(int size, double *list) {
  int result;

  if (size % 2 != 0) {
    list += (size - 1) / 2;
    result = *list;
  } else {
    list += size / 2 - 1;
    result = *list++;
    result += *list;
    result = result / 2;
  }

  return result;
}

double avg(int size, double *list) {
  return sum(size, list) / (double) size;
}

double variance(int size, double *list) {
  double result = 0.0;
  double list_avg = avg(size, list);

  for (int i = 0; i < size; i++)
    result += (*list - list_avg) * (*list - list_avg);

  return result / (double) size;
}

double standard_deviation(int size, double *list) {
  return sqrt(variance(size, list));
}

