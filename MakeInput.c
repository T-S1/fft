#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

#define FNAME "input.csv"
#define N 32768
#define F 1000
#define FS 32000

double func(int i) {
    return sin(2 * M_PI * F * i / FS);
}

int main() {
    double x;
    FILE* fp;

    fp = fopen(FNAME, "w");
    if (fp == NULL) {
        printf("file open failure\n");
        return -1;
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%lf\n", func(i));
    }

    fclose(fp);

    return 0;
}
