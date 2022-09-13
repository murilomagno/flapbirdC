#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>

typedef struct
{
    int x;
    int y;
    char formato;
}BODY;

char matrizMAPA[20][80]; //[altura][largura]
const int altura=11, largura=79;//altura=y-1,largura=x-1
const int NUM_OBSTACULO=8;
const int H_OBSTACULO=11;
const int MAX_gap=15;
const int delay_maximo=400;
int gap;
const char Obsformato='|';
BODY OBSTACULO[9][12];
BODY passaro;
void printamapa();
void inicioOBSTACULO(int);
void MoveOBSTACULO();
int checaObstaculo();
int pontos;
int vidas;
int cycle;
int modoteste=0;

int main()
{
    int delay=500;
    double kbctr=1;
    char EOG;
    int temp;
INICIO:
    cycle=300;
    pontos=0;
    gap=MAX_gap;
    vidas=3;
    passaro=(BODY){3,6,'p'};
    OBSTACULO[0][0].x=11;
    inicioOBSTACULO(OBSTACULO[0][0].x);
    printamapa();
    printf("USE ESPACO PARA PULAR...\nPRESSIONE QUALQUER TECLA PARA INICIAR");
    getch();
    while(1)
    {
        if (kbhit())
        {
            while(kbhit())
            {
                if (getch()=='g'){modoteste=!modoteste;};
                passaro.y++;
                if (passaro.y>altura)
                    passaro.y=altura;
                printamapa;
            }
            kbctr=0.7;
        }
        else
        {
            kbctr+=0.3;
            passaro.y-=floor(kbctr);
            printamapa;
            if (passaro.y<0)
                passaro.y=0;
            if (kbctr>=2){kbctr=2;}
        }
        MoveOBSTACULO();
        temp=checaObstaculo();
        if (delay_maximo-3*cycle>=100)
            {delay=delay_maximo-3*cycle;}
        else
            {delay=100;}
        if (modoteste)
        {delay=50;}
        vidas=vidas-temp;
        printamapa();
        if (vidas <=0 && !modoteste)break;

        Sleep(delay);
        gap=MAX_gap-cycle/100;
        if (gap<9){gap=9;}

        cycle++;
    }
    printf("\nTU PERDEU\nAPERTE r PARA REINICIAR...\nOU APERTE ESC PARA SAIR...");
    //EOG=getch();
    while((EOG=getch())!=27)
    {
        if (EOG=='r'){goto INICIO;};//esc sai
        //EOG=getch();
    }
    return 0;
}

int checaObstaculo()
{
    int i,j;
    i=0;
    while(i<=NUM_OBSTACULO)
    {   j=0;
        while(j<=H_OBSTACULO)
        {
            if (OBSTACULO[i][j].x==passaro.x && OBSTACULO[i][j].y==passaro.y)
                if  (OBSTACULO[i][j].formato==Obsformato)
                {
                    return 1;
                }
                else
                {
                    pontos++;
                    if (pontos%10==0){vidas++;}
                }
                j++;}
                i++;}
    return 0;
}

void MoveOBSTACULO()
{
    int i,j,temp;
    static int outsider=-1;
    srand((unsigned)time(0));
        i=0;
    while(i<=NUM_OBSTACULO)
    {   j=0;
        while(j<=H_OBSTACULO)
        {
            OBSTACULO[i][j].x=OBSTACULO[i][j].x-1;
        j++;}
        if (OBSTACULO[i][0].x<0)
            {outsider=i;}
    i++;}
    if (outsider!=-1)
    {
        OBSTACULO[outsider][0].x=OBSTACULO[(outsider+NUM_OBSTACULO)%(NUM_OBSTACULO+1)][0].x+gap+rand()%4;
        temp=rand()%(H_OBSTACULO-1);
        for (j=0;j<=H_OBSTACULO;j++)
        {
            OBSTACULO[outsider][j].x=OBSTACULO[outsider][0].x;
            if (j>=temp&&j<=temp+3)
                OBSTACULO[outsider][j].formato=' ';
            else
                OBSTACULO[outsider][j].formato=Obsformato;
        }
    }
    outsider=-1;
}

void inicioOBSTACULO(int x0)
{
    int i,j,temp;
    srand((unsigned)time(NULL));
    i=0;
    while(i<=NUM_OBSTACULO)
    {
        if (i==0)
            OBSTACULO[i][0].x=x0;
        else
            OBSTACULO[i][0].x=OBSTACULO[i-1][0].x+gap;
        temp=rand()%(H_OBSTACULO-1);
        j=0;
        while(j<=H_OBSTACULO)
        {
            OBSTACULO[i][j].x=OBSTACULO[i][0].x;
            OBSTACULO[i][j].y=j;
            OBSTACULO[i][j].formato=Obsformato;
            if (j>=temp&&j<=temp+3)
                OBSTACULO[i][j].formato=' ';
            else
                OBSTACULO[i][j].formato=Obsformato;
        j++;}
    i++;}
    return;
}

void printamapa()
{
    system("cls");

    int i,j,ox,oy;                 //borda superior
        for (j=0;j<=largura;j++ )
    {
         printf("-");
    }
    printf("\n");


    for (i = altura;i>=0;i--) //RESETA O MAPA
    {
        for (j=0;j<=largura;j++ )
        {
            matrizMAPA[i][j]=' ';
        }
    }


    for(ox=0;ox<=NUM_OBSTACULO;ox++) // INSERE OS OBSTACULOS
    {
        for(oy=0;oy<=H_OBSTACULO;oy++)
        {
            if(OBSTACULO[ox][oy].x<=largura)
            {matrizMAPA[OBSTACULO[ox][oy].y][OBSTACULO[ox][oy].x]=OBSTACULO[ox][oy].formato;}
        }
    }


    matrizMAPA[passaro.y][passaro.x]=passaro.formato; //personagem

    i=altura;
    while(i>=0) //mapa
    {
        for (j=0;j<=largura;j++)
        {
            printf("%c",matrizMAPA[i][j]);
        }
        printf("\n");
    i--;}
    j=0;
    while(j<=largura)  //borda inferior
    {
         printf(">");
    j++;}
    printf("\n");
    printf(">>VIDAS: %d\n",vidas);

    printf(">>Seus Pontos; %d\n",pontos);
    if(pontos>=3 && pontos<6){printf("BRONZE ");}
    if(pontos>=6 && pontos<9){printf("PRATA ");}
    if(pontos>=9 && pontos<12){printf("OURO ");}
    if(pontos>=12){printf("PLATINA ");}
    if (modoteste==1){printf("modo de teste\n");}


}
