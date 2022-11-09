#ifndef _ARRAY_PROCESSING_H_
#define _ARRAY_PROCESSING_H_

int input(int* n, int** numerators, int** denomenators);
int initializing_array(int n, int* a, int who);
int insert(int *n, int** numerators, int** denomenators);
int delete_el(int* n, int** numerators, int** denomenators, int mode);                
void output(int n_or, int* numer, int* denom, int n_res, int* res_num, int* res_den, int comp_flag);     
                                                                             
#endif  // _ARRAY_PROCESSING_H_ 