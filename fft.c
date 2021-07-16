#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

#define FNAME_R "input.csv"
#define FNAME_W "output.csv"
#define N 65536

/* FFTを行う関数
 * 引数:
 *  xr[]: FFTの対象となるデータの実部配列
 *  xi[]: FFTの対象となるデータの虚部配列
 *  n: データ点数(2のべき乗)
 */
int fft (double xr[], double xi[], int n) {
    int i, j, k, d;
    double tr, ti, wr, wi, theta;

    /* ビットリバーサル */
    for (i = 1; i < n - 1; i++) {
        j = i;
        k = 0;
        for (int l = 1; l < n; l <<= 1) {
            k <<= 1;
            k |= (j & 1);
            j >>= 1;
        }

        if (i < k) {
            tr = xr[i];
            ti = xi[i];
            xr[i] = xr[k];
            xi[i] = xi[k];
            xr[k] = tr;
            xi[k] = ti;
        }
    }

    /* バタフライ演算 */
    theta = M_PI;   // W^0_2
    d = 1;          // バタフライの両端のインデックスの距離
    while (d < n) {
        i = 0;      // W の乗数
        while (i < d) {
            wr = cos(theta * i);
            wi = sin(theta * i);
            j = i;      // バタフライの一方のインデックス
            k = i + d;  // バタフライの他方のインデックス
            while (k < n) {
                // x[j] += w[i] * x[k]
                // x[k] = x[j] - w[i] * x[k]
                tr = wr * xr[k] - wi * xi[k];
                ti = wi * xr[k] + wr * xi[k];

                xr[k] = xr[j] - tr;
                xi[k] = xi[j] - ti;

                xr[j] += tr;
                xi[j] += ti;
                
                j += 2 * d;
                k += 2 * d;
            }
            i++;
        }
        theta *= 0.5;   // W^i_d -> W^i_(d * 2)
        d *= 2;
    }

    return 0;
}

int main() {
    double xr[N];
    double xi[N];
    int i, n;

    FILE* fpr;
    FILE* fpw;

    fpr = fopen(FNAME_R, "r");
    fpw = fopen(FNAME_W, "w");
    if (fpr == NULL || fpw == NULL) {
        printf("file open failure");
        return -1;
    }

    i = 0;
    while (fscanf(fpr, "%lf\n", &xr[i]) != EOF) {
        xi[i] = 0;
        i++;
    }

    n = 1;
    while (i > 1) {
        i >>= 1;
        n <<= 1;
    }

    printf("%d points will be calculated\n", n);

    fft(xr, xi, n);

    for (int i = 0; i < n; i++) {
        fprintf(fpw, "%lf\n", xr[i] * xr[i] + xi[i] * xi[i]);
    }

    fclose(fpr);
    fclose(fpw);

    return 0;
}