#include<stdio.h>
int main(){
  int pn, fn, frames[10], pages[30], temp[10], faults = 0;
  printf("Enter number of pages: ");
  scanf("%d", &pn);
  printf("Enter page reference string: ");
  for(int i = 0; i < pn; ++i) scanf("%d", &pages[i]);
  printf("Enter number of frames: ");
  scanf("%d", &fn);
  for(int i = 0; i < fn; ++i) frames[i] = -1;
  for(int i = 0; i < pn; ++i){
    int flag1 = 0, flag2 = 0;
    for(int j = 0; j <fn; ++j){
      if(frames[j] == pages[i]){
        flag1 = flag2 = 1;
        break;
      }
    }
    if(flag1 == 0){
      for(int j = 0; j < fn; ++j){
        if(frames[j] == -1){
          faults++;
          frames[j] = pages[i];
          flag2 = 1;
          break;
        }
      }
    }
    if(flag2 == 0){
      int flag3 =0, pos;
      for(int j = 0; j < fn; ++j){
        temp[j] = -1;
        for(int k = i+1; k < pn; ++k){
          if(frames[j] == pages[k]){
            temp[j] = k;
            break;
          }
        }
      }
      for(int j = 0; j < fn; ++j){
        if(temp[j] == -1){
          pos = j;
          flag3 = 1;
          break;
        }
      }
      if(flag3 ==0){
        int max = temp[0];
        pos = 0;
        for(int j = 1; j < fn; ++j){
          if(temp[j] > max){
            max = temp[j];
            pos = j;
          }
        }
      }
      frames[pos] = pages[i];
      faults++;
    }
  }
  printf("Total Page Faults: %d ", faults);
  return 0;
}