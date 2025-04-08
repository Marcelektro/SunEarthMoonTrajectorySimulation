#include "csv_output.h"


void init_output_file(FILE **file, const char *filename) {

    *file = fopen(filename, "w");
    if (*file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    fprintf(*file, "time,earth_x,earth_y,moon_x,moon_y\n");

}

void write_output(FILE *file, const double t,
                 const double earth_x, const double earth_y,
                 const double moon_x, const double moon_y) {

    fprintf(file, "%f,%f,%f,%f,%f\n",
            t,
            earth_x, earth_y,
            moon_x, moon_y);

}

void close_output_file(FILE *file) {

    fclose(file);

}
