#ifndef _COMPUTATING_H_
#define _COMPUTATING_H_

int data_computating(int n, int* numerators, int* denomenators, int* len_res, int** result);
void search_minmax(int n, int* numers, int* denomers, int* minmax);
int computate_sequence(int n, int* numers, int* denomers, int** result, int* minmax);
void create_res_seqs(int** res_num, int** res_den, int* numers, int* denomers, int* result, int len_res);

int my_abs(int a);
void swap(int* a, int* b);

#endif  // _COMPUTATING_H_