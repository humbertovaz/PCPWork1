#include <stdio.h>
#define N 4
#define M 6
double G2[N][M];
double A[N*M];
double IA[N+1];
double JA[N*M];

int fillCRSArrays(int* sizeA,int* sizeIA,int* sizeJA){
    int i,j,jj,z=0;
    int vA=0;
    int vIA=0;
    int vJA=0;
    int atual = 0;
    int size=1;
    IA[0]=0;
    
    for(i=0;i<N;i++){
        IA[i+1]=IA[i]; // fica com o elemento anterior
        for(j=0;j<M;j++){
            if (G2[i][j]!=0){
                A[z]=G2[i][j];  //collect non zero elements from G2
                JA[z++]=j;    //certo
                ++vA;
                IA[i+1]++; //soma 1
            }
        }
    }
    vJA=vA; 
    *sizeA=vA;
    *sizeIA=N+1;
    *sizeJA=vJA;        
}
void fill (){
    for (int i=0;i<N ;++i )
        for(int j=0;j<M;++j){
            G2[i][j]=0;
        }
        /*G2[0][0]=10;
        G2[0][1]=20;
        G2[1][1]=30;
        G2[1][3]=40;
        G2[2][2]=50;
        G2[2][3]=60;
        G2[2][4]=70;
        G2[3][5]=80;*/
        G2[1][0]=5;
        G2[1][1]=8;
        G2[2][2]=3;
        G2[3][1]=6;
}
int main(){
    fill();
    int sizeA,sizeIA,sizeJA;
    fillCRSArrays(&sizeA,&sizeIA,&sizeJA);
    printf("A:%d IA:%d JA:%d\n",sizeA,sizeIA,sizeJA);
        for (int i=0;i<N;++i)
            for(int j=0;j<M;++j){
                printf("G2[%d][%d]=%f\n",i,j,G2[i][j]);
            }
            printf("----A----\n ");
            for(int i = 0; i < sizeA; i++){
                printf("%f\n",A[i]);
            }
            
            printf("----IA----\n ");
            for(int i = 0; i < sizeIA; i++){
                printf("%f\n",IA[i]);
            }
            printf("----JA----\n ");
            for(int i = 0; i < sizeJA; i++){
                printf("%f\n",JA[i]);
            }
return 0;
}