#include<stdio.h>

int main() {
  int q[20], p[50], c = 1,fn, k = 0, pn, b[20], c2[20];
  printf("Enter no of pages: ");
  scanf("%d", &pn);
  printf("Enter the reference string: ");
  for (int i = 0; i < pn; i++) scanf("%d", &p[i]);
  printf("Enter no of frames: ");
  scanf("%d", &fn);
  q[k] = p[k];
  k++;
  for (int i = 1; i < pn; i++) {
    int c1 = 0;
    for (int j = 0; j < fn; j++) {
      if (p[i] != q[j]) c1++;
    }
    if (c1 == fn) {
      c++;
      if (k < fn) q[k++] = p[i];
      else {
        for (int r = 0; r < fn; r++) {
          c2[r] = 0;
          for (int j = i - 1; j < pn; j--) {
            if (q[r] != p[j]) c2[r]++;
            else break;
          }
        }
        for (int r = 0; r < fn; r++) b[r] = c2[r];
        for (int r = 0; r < fn; r++){
          for (int j = r; j < fn; j++){
            if (b[r] < b[j]) {
              int t = b[r];
              b[r] = b[j];
              b[j] = t;
            }
          }
        }
        for (int r = 0; r < fn; r++){
          if (c2[r] == b[0]) q[r] = p[i];
        }
      }
    }
  }
  printf("The no of page faults is %d\n", c);
}