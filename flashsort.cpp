#include <cstring>

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}
void flashSort(int n, int *a) {
    int min_val = a[0], max = 0, m = int(0.45 * n);
    int *l = new int [m];
    memset(l, 0, m);

    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
            continue;
        }
        if (a[i] > a[max]) {
            max = i;
        }
    }

    if (a[max] == min_val) return;
    
    double gap = (m - 1.0) / (a[max] - min_val);
    
    int k;
    for (int i = 0; i < n; i++) {
        k = int(gap * (a[i] - min_val));
        l[k]++;
    }
    for (int i = 1; i < m; i++)
        l[i] += l[i - 1];

    swap(&a[max], &a[0]);
    int move = 0, j = 0, t = 0, flash;
    k = m - 1;
    while (move < n - 1) {
        while (j > l[k] - 1) {
            j++;
            k = int (gap * (a[j] - min_val));
        }
        flash = a[j];
        if (k < 0) break;
        while (j != l[k]) {
            k = int (gap * (flash - min_val));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++move;
        }
    }
    
    delete[] l;

}