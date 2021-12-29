#include <stdio.h>
#include <stdlib.h>
#include <Windows.h >

typedef struct field_
{
    int* field_data;
} field;

int fieldsize;

field* scan(field* f){
  scanf("%i", &fieldsize);
  int* data = malloc(sizeof(int) * fieldsize * fieldsize);
  data = memset(data, 0, sizeof(int) * fieldsize * fieldsize);
  f->field_data = data ;
  return f;
}

void visual(field* f)
{
  int pointer = fieldsize;
  int i,j;
  printf("%s","  " );
  for(i = 1; i <= fieldsize; i++){
    printf("%i ",i );
  }
  printf("%s\n", "");
  for(i=1; i<=fieldsize; i++)
  {
    printf ("%d", i);

    for (j= i * fieldsize - pointer; j<fieldsize*i; j++)
    {
      if (f->field_data[j]==0){printf("| ");};
      if (f->field_data[j]==1){printf("|O");};
      if (f->field_data[j]==2){printf("|X");};
    }

  printf ("|\n");
    for(int z = 1; z<= fieldsize + 1; z++){
      printf ("__");
    }
    printf("%s\n", "");
  }
}

/*void hod (int n)
{
  int hi;
  int sto;
  int str;
  int ver=0;
  while (ver==0)
  {

    printf ("Your move. Enter the row and column number.\n");
    scanf("%d", &hi);
    sto=hi%10;
    str=(hi-sto)/10;
    if (a[str][sto]==0 && (hi==11 || hi==12 || hi==13 || hi==21 || hi==22 || hi==23 || hi==31 || hi==32 || hi==33 )) (ver=1);
  }
  if ( n==1) {a[str][sto]=1;}
  if ( n==2) {a[str][sto]=2;}
}
int proverka()
{
}
*/
int main()
{
  field* f = malloc(sizeof(field));\
  visual(scan(f));
  return 0;
}
