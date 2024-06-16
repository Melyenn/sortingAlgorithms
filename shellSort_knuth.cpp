void shellSort_knuth(int n, int *a) {
    int gap = 1;
    while (gap <= n / 3) {
        gap = gap * 3 + 1;
    }
    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int tmp = a[i], j = i;
            while (j  >= gap && a[j - gap] > tmp)  {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = tmp;
        }
        gap = (gap - 1) / 3;
    }
}