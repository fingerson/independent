#include <stdio.h>

#define TAMX 20
#define TAMY 20

char maromba[TAMX][TAMY+1];
void desenho()
{
    int i,j;
    for(i=0;i<TAMY;i++)
        printf("\n");
    for(i=0;i<TAMX;i++)
    {
        for(j=0;j<TAMY+1;j++)
        {
            printf("%2c",maromba[i][j]);
        }
    }
}

int main()
{
    char url[]="labirinto.txt";
	char ch;
	unsigned short int i,j;
	FILE *arq;
	int pos[2];
	int posF[2];
	int loopcontrol=1;
	int comando;
	int moves = 0;

	arq = fopen(url, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	else
    {
            for(i=0;i<TAMX;i++)
            {
               for(j=0;j<TAMY+1;j++)
               {
                   if( (ch=fgetc(arq))!= EOF )
                   {
                       maromba[i][j]=ch;
                   }
                   if (ch=='2')
                   {
                       pos[0]=i;
                       pos[1]=j;
                    }
                    if (ch=='F')
                    {
                       posF[0]=i;
                       posF[1]=j;
                    }
               }
            }

    }
	fclose(arq);
    desenho();
    printf("\nMoves: %d", moves);
    while(loopcontrol==1)
    {
        desenho();
        printf("\nMoves: %d", moves);
        printf("\n\nDigite o comando (8 4 2 6): ");
        scanf("%d", &comando);
        if(comando==4 && pos[1]!=0 && (maromba[pos[0]][pos[1]-1]=='_' || maromba[pos[0]][pos[1]-1]==2 || maromba[pos[0]][pos[1]-1]=='F'))
        {
            maromba[pos[0]][pos[1]] = '_';
            maromba[pos[0]][pos[1]-1] = '2';
            pos[1]--;
            moves++;
        }
        if(comando==8 && pos[0]!=0 && (maromba[pos[0]-1][pos[1]]=='_' || maromba[pos[0]-1][pos[1]]==2 || maromba[pos[0]-1][pos[1]]=='F'))
        {
            maromba[pos[0]][pos[1]] = '_';
            maromba[pos[0]-1][pos[1]] = '2';
            pos[0]--;
            moves++;

        }
        if(comando==6 && pos[1]!=(TAMY-1) && (maromba[pos[0]][pos[1]+1]=='_' || maromba[pos[0]][pos[1]+1]==2 || maromba[pos[0]][pos[1]+1]=='F'))
        {
            maromba[pos[0]][pos[1]] = '_';
            maromba[pos[0]][pos[1]+1] = '2';
            pos[1]++;
            moves++;

        }
        if(comando==2 && pos[0]!=(TAMX-1) && (maromba[pos[0]+1][pos[1]]=='_' || maromba[pos[0]+1][pos[1]]==2 || maromba[pos[0]+1][pos[1]]=='F'))
        {
            maromba[pos[0]][pos[1]] = '_';
            maromba[pos[0]+1][pos[1]] = '2';
            pos[0]++;
            moves++;
        }
        if(pos[0] == posF[0] && pos[1] == pos[1])
        {
           break;
        }

    }
    printf("\n");
    for(i=0;i<TAMY/2;i++)
        printf("PARABAAAAAAAAAAAAAINS!\n");
    printf("PARABAAAAAAAAAAAAAINS!\n");
    for(i=0;i<TAMY/2;i++)
        printf("PARABAAAAAAAAAAAAAINS!\n");
    return 0;
}
