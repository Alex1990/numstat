#include <math.h>

void swap(double *a, double *b) {
  double tmp = *a;
  *a = *b;
  *b = tmp;
}

void sort(int size, double *list) {
  for (int i = 0; i < size; i++)
    for (int j = i + 1; j < size; j++)
      if (list[i] > list[j]) swap(&list[i], &list[j]);
}

double sum(int size, double *list) {
  double result = 0.0;

  for (int i = 0; i < size; i++)
    result += list[i];

  return result;
}

double min(int size, double *list) {
  double result = list[0];

  for (int i = 1; i < size; i++)
    if (list[i] < result) result = list[i];

  return result;
}

double max(int size, double *list) {
  double result = list[0];

  for (int i = 1; i < size; i++)
    if (list[i] > result) result = list[i];

  return result;
}

double median(int size, double *list) {
  double result;

  sort(size, list);

  if (size % 2 != 0)
    result = list[(size - 1) / 2];
  else
    result = (list[size / 2] + list[size / 2 - 1]) / 2.0;

  return result;
}

double avg(int size, double *list) {
  return sum(size, list) / (double) size;
}

double variance(int size, double *list) {
  double result = 0.0;
  double list_avg = avg(size, list);

  for (int i = 0; i < size; i++)
    result += (list[i] - list_avg) * (list[i] - list_avg);

  return result / (double) size;
}

double standard_deviation(int size, double *list) {
  return sqrt(variance(size, list));
}

