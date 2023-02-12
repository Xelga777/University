#ifndef MAIN_H_
#define MAIN_H_


// Define structures
typedef struct {
    size_t len;
    int *data;
} Line;

typedef struct {
    size_t lines_num;
    Line *p_lines;
} Matrix;

// Prototypes
void err_handler(int *err_code);
void free_data(Matrix *matrix, int **vector);

int compling_task(Matrix *matrix, int **vector);
int unique_elems(Line line_0, Line line_1);

#endif  // MAIN_H_
