#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

#define FNAME_R "input.csv"
#define FNAME_W "output.csv"
#define N 32768

int bit_reversal (int i, int n) {
    int rev = 0;
    for (int j = 1; j < n; j <<= 1) {
        rev <<= 1;
        rev |= (i & 1);
        i >>= 1;
    }
    return rev;
}

int fft (double xr[], doouble xi[], int n) {
    // 参照用イテレータ
    int i, j, k, d, r;

    double tr, ti, wr, wi;

    for (i = 1; i <= (n >> 1); i++) {
        j = i;
        k = 0;
        while (j != 0) {
            k <<= 1;
            k |= (j & 1);
            j >>= 1;
        }
        if (j < k) {
            tr = xr[j];
            ti = xi[j];
            xr[j] = xr[k];
            xi[j] = xi[k];
            xr[k] = tr;
            xi[k] = ti;
        }
    }
    for (i = 0; i < (n >> 1); i++) {
        wr[i] = cos(2 * M_PI * i / n);
        wi[i] = sin(2 * M_PI * i / n);
    }

    d = 1;
    r = (n >> 1);
    while (d < n) {
        i = 0;
        j = 0;
        while (i <= (n >> 2)) {
            wr = cos(theta * i);
            wi = sin(theta * i);
            while (k < n) {
                // x[i] += w[j] * x[k]
                // x[k] = x[k] - w[j] * x[k]
                tr = wr[j] * xr[k] - wi[j] * xi[k];
                ti = wi[j] * xr[k] + wr[j] * xi[k];

                xr[k] = xr[i] - tr;
                xi[k] = xi[i] - ti;

                xr[i] += tr;
                xi[i] += ti;

                i++;
                k++;
            }
            i++;
        }
        d <<= 1;
        r >>= 1;
    }    

    return 0;
}

int main() {
    double xr[N];
    double xi[N];

    FILE* fpr;
    FILE* fpw;

    fpr = fopen(FNAME_R, "r");
    fpw = fopen(FNAME_W, "w");
    if (fpr == NULL || fpw == NULL) {
        printf("file open failure");
        return -1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(fpr, "%lf\n", &xr[i])
        xr[i] = 0;
    }

    fft(xr, xi, N);

    for (i = 0; i < n; i++) {
        fprintf(fpw, "%lf\n", xr[i] * xr[i] + xi[i] * xi[i]);
    }

    fclose(fpr);
    fclose(fpw);

    return 0;
}