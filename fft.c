#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct complex {
    double r;
    double i;
} complex;

complex prod_complex(complex za, complex zb) {
    complex z;
    z.r = za.r * zb.r - za.i * zb.i;
    z.i = za.r * zb.i + za.i * zb.r;
    return z;
}

complex sum_complex(complex za, complex zb) {
    complex z;
    z.r = za.r + zb.r;
    z.i = za.i + zb.i;
    return z;
}

complex dif_complex(complex za, complex zb) {
    complex z;
    z.r = za.r - zb.r;
    z.i = za.i - zb.i;
    return z;
}

complex calc_w (int i, int n) {
    complex w;
    w.r = cos(2 * M_PI * i / n);
    w.i = sin(2 * M_PI * i / n);
    return w;
}

int bit_reversal (int i, int n) {
    int r = 0;
    for (int j = 0; (1 << j) <= n; j++) {
        r |= ((i & 1) << (size - i));
        i >>= 1;
    }
    return r;
}

int butterfly_operator (complex* xa, complex* xb, complex w) {
    *xa = sum_complex(*xa, prod_complex(w, *xb));
    *xb = dif_complex(*xa, prod_complex(w, *xb));
}

int fft (FILE* fpr, FILE* fpw, int n) {
    complex* w;
    double* x;
    int* idx;
    
    w = (double*)malloc(sizeof(double) * n / 2);
    x = (double*)malloc(sizeof(double) * n);
    idx = (int*)malloc(sizeof(int) * n);
    if (w == NULL || x == NULL || idx == NULL) {
        printf("memory failure");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        idx[i] = bit_reversal(i, size);
        x[idx[i]] = 
    }
    for (int i = 0; i < n/2; i++) w[i] = calc_w(i, n);

    for (int i = 1; i < n; i <<= 1) {
        for (int j = 1; j < n; j <<= i) {
            for (int k = 1; k <= i; k <<= 1) {
                
            }
        }
    }

    free(w);
    free(x);
    free(idx);

    return 0;
}

int main(){
    
}
