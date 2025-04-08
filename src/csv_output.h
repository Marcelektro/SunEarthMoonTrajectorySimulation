#ifndef CSV_OUTPUT_H
#define CSV_OUTPUT_H

#include <stdio.h>

void init_output_file(FILE **file, const char *filename);
void write_output(FILE *file, double t,
                  double earth_x, double earth_y,
                  double moon_x, double moon_y);
void close_output_file(FILE *file);


#endif //CSV_OUTPUT_H
