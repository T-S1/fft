#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FNAME_R "input.csv"
#define FNAME_W "output.csv"

int bit_reversal (int i, int n) {
    int rev = 0;
    for (int j = 1; j <= n; j <<= 1) {
        rev <<= 1;
        rev |= (i & 1);
        i >>= 1;
    }
    return rev;
}

int fft (FILE* fpr, FILE* fpw, int n) {
    // 回転子の配列
    double* wr;     // 実部
    double* wi;     // 虚部
    
    // 変換対象となる数列
    double* xr;     // 実部
    double* xi;     // 虚部
    
    // 参照用イテレータ
    int i, j, d, r, p;

    double tmp, tr, ti;

    // 動的メモリ確保
    wr = (double*)malloc(sizeof(double) * (n >> 1));
    wi = (double*)malloc(sizeof(double) * (n >> 1));
    xr = (double*)malloc(sizeof(double) * n);
    xi = (double*)malloc(sizeof(double) * n); 
    if (wr == NULL || wi == NULL || xr == NULL || xi == NULL) {
        printf("memory failure");
        return -1;
    }

    // ファイルから数列の読み込み
    for (i = 0; i < n; i++) {
        int idx = bit_reversal(i, n);
        if (fscanf(fpr, "%lf", &xr[idx]));
        xi[idx] = 0;
    }
    for (i = 0; i < (n >> 1); i++) {
        wr[i] = cos(2 * M_PI * i / n);
        wi[i] = sin(2 * M_PI * i / n);
    }

    d = 1;
    r = n;
    while (d < n) {
        i = 0;
        j = d;
        while (j < n) {
            p = 0;
            while (p < (n >> 1)) {
                // x[i] += w[p] * x[j]
                // x[j] = x[i] - w[p] * x[j]
                tr = xr[i];
                ti = xi[i];

                xr[i] += wr[p] * xr[j] - wi[p] * xi[j];
                xi[i] += wi[p] * xr[j] + wr[p] * xi[j];

                tmp = xr[j];
                xr[j] = tr - (wr[p] * tmp - wi[p] * xi[j]);
                xi[j] = ti - (wi[p] * tmp + wr[p] * xi[j]);

                i++;
                j++;
                p += r;
            }
            i = j;
            j = i + d;
        }
        d <<= 1;
        r >>= 1;
    }

    free(wr);
    free(wi);
    free(xr);
    free(xi);

    return 0;
}

int main(){
    FILE* fpr;
    FILE* fpw;

    fpr = fopen(FNAME_R, "r");
    fpw = fopen(FNAME_W, "w");

    fclose(fpr);
    fcolse(fpw);

    return 0;
}