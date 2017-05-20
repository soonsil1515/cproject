#include<stdio.h>
#define N 30
int main(void)
{
    int i=0,j=0,k;

    char map[5][N][N]={0};

    FILE *ifp;
    char c;
    ifp = fopen("C:\\cygwin64\\home\\USER\\map.txt","r");

    if(ifp==NULL)printf("no");
    for(k=0;k<5;k++)
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++)
            {
                fscanf(ifp,"%c",&map[k][i][j]);
                if(map[k][i][0]=='m')
                    break;	
                if(map[k][i][j]=='\n')
                    break;
				if(map[k][i][0] == 'e')
					break;
			
            }
            if(map[k][i][0]=='m')
            {
                map[k][i][0]='\0';
                break;	
            }
			if(map[k][i][0] == 'e')
			{
				map[k][i][0] = '\0';
				break;
			}
        }
        fgetc(ifp);
       fgetc(ifp);
        fgetc(ifp);
    }	
    for(k = 0; k < 5; k++) {
        for(i=0;i<N;i++)
            for(j=0;j<N;j++)
                printf("%c",map[k][i][j]);
        printf("\n");
    }

    fclose(ifp);
    return 0;
}


