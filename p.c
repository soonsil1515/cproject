#include<stdio.h>
#include <termio.h>
#define N 30
int getch(void);
void left(char [][N][N], int *, int *, int *);
void left_both(char [][N][N], int *, int *, int *);
void right(char [][N][N], int *, int *, int *);
void right_both(char[][N][N], int *, int *, int *);
void up(char [][N][N], int *, int *, int *);
void up_both(char[][N][N], int *, int *, int *);
void down(char [][N][N], int *, int *, int *);
void down_both(char[][N][N], int *, int *, int *);

int main(void)
{
    int i = 0, j = 0, k, x, y, z;
    char map[5][N][N]={0};

    FILE *ifp;
    char c, command;
    ifp = fopen("C:\\cygwin64\\home\\이송희\\cpro\\map.txt","r");

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

    //map1
    x = 0; 
    y = 8;
    z = 12;
    while(map[0][6][19] != '$' || map[0][7][19] != '$' || map[0][8][19] != '$' || map[0][6][20] != '$' || map[0][7][20] != '$' || map[0][8][20] != '$') {    
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                printf("%c", map[0][i][j]);
        printf("(Command) ");
        command = getch();
        printf("\n\n");
        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') 
                            left_both(map, &x, &y, &z);
                    }
                    else 
                        left(map, &x, &y, &z);
                }
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#')
                            right_both(map, &x, &y, &z);
                    }
                    else {
                        //if(map[x][y][z + 1] == 'O') {
                        //    right(map, &x, &y, &z);
                        //    map[x][y][z] = 'O';
                       // }
                       // else
                            right(map, &x, &y, &z);
                    }
                }
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#')
                            up_both(map, &x, &y, &z);
                    }
                    else
                        up(map, &x, &y, &z);
                }
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#')
                            down_both(map, &x, &y, &z);
                    }
                    else
                        down(map, &x, &y, &z);
                }
                break;
        }
    }

    fclose(ifp);

    printf("*****축하합니다! 모든 맵을 완수하셨습니다!*****\n");

    return 0;

}
void up(char map[][N][N], int *x, int *y, int *z) {
    map[*x][(*y)--][*z] = ' ';
    map[*x][*y][*z] = '@';
}

void up_both(char map[][N][N], int *x, int *y, int *z) {
    map[*x][(*y) - 2][*z] = '$';
    up(map, x, y, z);
}

void down(char map[][N][N], int *x, int *y, int *z) {
    map[*x][(*y)++][*z] = ' ';
    map[*x][*y][*z] = '@';
}

void down_both(char map[][N][N], int *x, int *y, int *z) {
    map[*x][(*y) + 2][*z] = '$';
    down(map, x, y, z);
}

void left(char map[][N][N], int *x, int *y, int *z) {
    map[*x][*y][(*z)--] = ' ';
    map[*x][*y][*z] = '@';
}

void left_both(char map[][N][N], int *x, int *y, int *z) {
    map[*x][*y][(*z) - 2] = '$';
    left(map, x, y, z);
}

void right(char map[][N][N], int *x, int *y, int *z) {
    map[*x][*y][(*z)++] = ' ';
    map[*x][*y][*z] = '@';
}

void right_both(char map[][N][N], int *x, int *y, int *z) {
    map[*x][*y][(*z) + 2] = '$';
    right(map, x, y, z);
}

int getch() {
    int ch;

    struct termios buf;
    struct termios save;

    tcgetattr(0, &save);
    buf = save;

    buf.c_lflag&=~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &buf);

    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);

    return ch;
}

