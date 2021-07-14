#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

complex calc_w (int i, int n) {
    complex w;
    w.r = cos(2 * M_PI * i / n);
    w.i = sin(2 * M_PI * i / n);
    return w;
}

int bit_reversal (int i, int n) {
    int r = 0;
    for (int j = 1; j <= n; j <<= 1) {
        r <<= 1;
        r |= (i & 1);
        i >>= 1;
    }
    return r;
}

int butterfly_operator (double* xa, double* xb) {
    *xa = sum_complex(*xa, prod_complex(w, *xb));
    *xb = dif_complex(*xa, prod_complex(w, *xb));
}

int fft (FILE* fpr, FILE* fpw, int n) {
    double* wr;
    double* wi;
    double* xr;
    double* xi;
    int idx;
    double tmp;
    
    wr = (double*)malloc(sizeof(double) * n / 2);
    wi = (double*)malloc(sizeof(double) * n / 2);
    xr = (double*)malloc(sizeof(double) * n);
    xi = (double*)malloc(sizeof(double) * n);
    if (wr == NULL || wi == NULL || xr == NULL || xi == NULL) {
        printf("memory failure");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        idx = bit_reversal(i, n);
        if (fscanf(fpr, "%lf\n", &xr[idx]));
        xi[idx] = 0;
    }
    for (int i = 0; i < (n >> 1); i++) {
        wr[i] = cos(2 * M_PI * i / n);
        wi[i] = sin(2 * M_PI * i / n);
    }

    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += (2 << i)) {
            for (int k = 0; k < (1 << i); k++) {
                
            }
        }
    }

    free(wr);
    free(wi);
    free(xr);
    free(xi);

    return 0;
}

int main(){
    
}
