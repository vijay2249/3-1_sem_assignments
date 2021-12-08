#include <stdio.h>

int main(){
  int j=0,tp,fn,pn[50],frames[10],available,cnt=0;
  printf("Enter no of Pages: ");
  scanf("%d", &tp);
  printf("Enter Page Number: ");
  for (int i = 1; i <= tp; i++) scanf("%d", & pn[i]);
  printf("Enter the No. of frames: ");
  scanf("%d", &fn);
  for (int i = 0; i <fn; i++) frames[i] = -1;
  for (int i = 1; i <=tp; i++){
    available=0;
    for (int k = 0; k <fn; k++){
      if (frames[k] == pn[i]) available = 1;
    }
    if (available == 0){
      frames[j] = pn[i];
      j = (j + 1) % fn;
      cnt++;
    }
  }
  printf("Page Fault Is %d\n", cnt);
  return 0;
}