#include<stdio.h>
#include <termio.h>
#define N 30
int getch(void);
void setO(char[][N][N], char[][N][N], int, int, int, int);
void left(char[][N][N]);
void left_both(char[][N][N]);
void right(char[][N][N]);
void right_both(char[][N][N]);
void up(char[][N][N]);
void up_both(char[][N][N]);
void down(char[][N][N]);
void down_both(char[][N][N]);
void save_move(char[][N][N], char[][N][N]);
void pull(char[][N][N]);
void undo(char[][N][N], char [][N][N]); 
int x, y, z, u;

int main(void)
{
    int i = 0, j = 0, k;
    char map[5][N][N] = {'\0'};
    char sol[5][N][N] = {'\0'};
    char un[5][N][N] = {'\0'};
	char name[20];

    FILE *ifp;
    char c, command;
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

	printf("Start....\n");
	printf("Input name : ");
	scanf("%s",&name);

    for(k = 0; k < 5; k++) 
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                sol[k][i][j] = map[k][i][j];

    //map1
	printf("-----------MAP1-----------\n\n");
    printf("\tHello %s\n",name);
   	x = 0; 
    y = 8;
    z = 12;
    u = -1;
    while(map[0][6][19] != '$' || map[0][7][19] != '$' || map[0][8][19] != '$' || map[0][6][20] != '$' || map[0][7][20] != '$' || map[0][8][20] != '$') { 
        
        for(int i = 0; i < N; i++) 
            for(int j = 0; j < N; j++) 
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();

        if(command == 'h' || command == 'l' || command == 'k' || command == 'j') {
        }
        else
            printf("%c", command);

        printf("\n\n");

        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') {
                            save_move(map, un);
                            left_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        left(map);
                    }
                }

                setO(map, sol, 6, 9, 19, 21);
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#') {
                            save_move(map, un);
                            right_both(map);
                        }
                        else if(map[x][y][z + 2] == 'O') {
                            save_move(map, un);
                            right_both(map);
                            map[x][y][z + 2] = 'O';
                        }
                    }
                    else  {
                        save_move(map, un);
                        right(map);
                    }
                }

                setO(map, sol, 6, 9, 19, 21);
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#') {
                            save_move(map, un);
                            up_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        up(map);
                    }
                }
                setO(map, sol, 6, 9, 19, 21);
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#') {
                            save_move(map, un);
                            down_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        down(map);
                    }
                }

                setO(map, sol, 6, 9, 19, 21);
                break;

            case 'u': //undo
                if(u > -1)
                    undo(map, un);
                break;
        } 
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    printf("\nMAP1을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map2
    printf("-----------MAP2-----------\n\n");
    printf("\tHello %s\n\n",name);
    x = 1;
    y = 5;
    z = 7;
    u = -1;
    for(k = 0; k < 5; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                un[k][i][j] = '\0';
    while(map[x][2][1] != '$' || map[x][2][2] != '$' || map[x][3][1] != '$' || map[x][3][2] != '$' || map[x][4][1] != '$' || map[x][4][2] != '$' || map[x][5][1] != '$' || map[x][5][2] != '$' || map[x][6][1] != '$' || map[x][6][2] != '$') {

        for(i = 1; i< N; i++)
            for(j = 0; j < N; j++)
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();
        if(command == 'h' || command == 'l' || command =='k' || command == 'j') {
        }
        else
            printf("%c", command);

        printf("\n\n");

        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') {
                            save_move(map, un);
                            left_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        left(map);
                    }
                }

                setO(map, sol, 2, 7, 1, 3);
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#') {
                            save_move(map, un);
                            right_both(map);
                        }
                        else if(map[x][y][z + 2] == 'O') {
                            save_move(map, un);
                            right_both(map);
                            map[x][y][z + 2] = 'O';
                        }
                    }
                    else {
                        save_move(map, un);
                        right(map);
                    }
                }

                setO(map, sol, 2, 7, 1, 3);
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#') {
                            save_move(map, un);
                            up_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        up(map);
                    }
                }

                setO(map, sol, 2, 7, 1, 3);
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#') {
                            save_move(map, un);
                            down_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        down(map);

                    }
                }

                setO(map, sol, 2, 7, 1, 3);
                break;

            case 'u': //undo
                if(u > -1)
                    undo(map, un);
                break;
        }
    } 
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    printf("\nMAP2을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map3
    printf("-----------MAP3-----------\n\n");
    printf("\tHello %s\n\n",name);
    x = 2;
    y = 2;
    z = 14;
    u = -1;
    for(k = 0; k < 5; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                un[k][i][j] = '\0';
    while(map[x][7][1] != '$' || map[x][7][2] != '$' || map[x][7][3] != '$' || map[x][7][4] != '$' || map[x][8][2] != '$' || map[x][8][3] != '$' || map[x][8][4] != '$' || map[x][9][1] != '$' || map[x][9][2] != '$' || map[x][9][3] != '$' || map[x][9][4] != '$') {

        for(i = 1; i < N; i++)
            for(j = 0; j < N; j++)
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();
        if(command == 'h' || command == 'l' || command =='k' || command == 'j') {
        }
        else
            printf("%c", command);

        printf("\n\n");

        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') {
                            save_move(map, un);
                            left_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        left(map);
                    }
                }

                setO(map, sol, 7, 10, 1, 5);
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#') {
                            save_move(map, un);
                            right_both(map);
                        }
                        else if(map[x][y][z + 2] == 'O') {
                            save_move(map, un);
                            right_both(map);
                            map[x][y][z + 2] = 'O';
                        }
                    }
                    else {
                        save_move(map, un);
                        right(map);
                    }
                }

                setO(map, sol, 7, 10, 1, 5);
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#') {
                            save_move(map, un);
                            up_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        up(map);
                    }
                }

                setO(map, sol, 7, 10, 1, 5);
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#') {
                            save_move(map, un);
                            down_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        down(map);
                    }
                }

                setO(map, sol, 7, 10, 1, 5);
                break;

            case 'u': //undo
                if(u > -1)
                    undo(map, un);
                break;
        }
    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    printf("\nMAP3을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map4
    printf("-----------MAP4-----------\n\n");
    printf("\tHello %s\n\n",name);
    x = 3; 
    y = 11;
    z = 8;
    u = -1;
    for(k = 0; k < 5; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                un[k][i][j] = '\0';
    while(map[x][2][17] != '$' || map[x][2][18] != '$' || map[x][2][19] != '$' || map[x][2][20] != '$' || map[x][3][17] != '$' || map[x][3][18] != '$' || map[x][3][19] != '$' || map[x][3][20] != '$' || map[x][4][17] != '$' || map[x][4][18] != '$' || map[x][4][19] != '$' || map[x][4][20] != '$' || map[x][5][17] != '$' || map[x][5][18] != '$' || map[x][5][19] != '$' || map[x][5][20] != '$' || map[x][6][17] != '$' || map[x][6][18] != '$' || map[x][6][19] != '$' || map[x][6][20] != '$') {
        for(i = 1; i < N; i++)
            for(j = 0; j < N; j++)
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();
        if(command == 'h' || command == 'l' || command =='k' || command == 'j') {
        }
        else
            printf("%c", command);
        printf("\n\n");


        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') {
                            save_move(map, un);
                            left_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        left(map);
                    }
                }

                setO(map, sol, 2, 7, 17, 21);
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#') {
                            save_move(map, un);
                            right_both(map);
                        }
                        else if(map[x][y][z + 2] == 'O') {
                            save_move(map, un);
                            right_both(map);
                            map[x][y][z + 2] = 'O';
                        }
                    }
                    else {
                        save_move(map, un);
                        right(map);
                    }
                }

                setO(map, sol, 2, 7, 17, 21);
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#') {
                            save_move(map, un);
                            up_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        up(map);
                    }
                }

                setO(map, sol, 2, 7, 17, 21);
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#') {
                            save_move(map, un);
                            down_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        down(map);
                    }
                }

                setO(map, sol, 2, 7, 17, 21);
                break;

            case 'u': //undo
                if(u > -1)
                    undo(map, un);
                break;
        }
    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    printf("\nMAP4을 성공하셨습니다!\n");

    printf("--------------------------\n\n");

    //map5
    printf("-----------MAP5-----------\n\n");
    printf("\tHello %s\n\n",name);
    x = 4;
    y = 8; 
    z = 14;
    u = -1;
    for(k = 0; k < 5; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                un[k][i][j] = '\0';
    while(map[x][6][1] != '$' || map[x][6][2] != '$' || map[x][6][3] != '$' || map[x][6][4] != '$' || map[x][7][1] != '$' || map[x][7][2] != '$' || map[x][7][4] != '$' || map[x][8][1] != '$' || map[x][8][2] != '$' || map[x][8][3] != '$' || map[x][8][4] != '$' || map[x][7][3] != '$') {

        for(i = 1; i < N; i++)
            for(j = 0; j < N; j++)
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();
        if(command == 'h' || command == 'l' || command =='k' || command == 'j') {
        }
        else
            printf("%c", command);

        printf("\n\n");

        switch(command) {
            case 'h': //left
                if(map[x][y][z - 1] != '#') {
                    if(map[x][y][z - 1] == '$') {
                        if(map[x][y][z - 2] != '$' && map[x][y][z - 2] != '#') {
                            save_move(map, un);
                            left_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        left(map);
                    }
                }

                setO(map, sol, 6, 9, 1, 5);
                break;

            case 'l': //right
                if(map[x][y][z + 1] != '#') {
                    if(map[x][y][z + 1] == '$') {
                        if(map[x][y][z + 2] != '$' && map[x][y][z + 2] != '#') {
                            save_move(map, un);
                            right_both(map);
                        }
                        else if(map[x][y][z + 2] == 'O') {
                            save_move(map, un);
                            right_both(map);
                            map[x][y][z + 2] = 'O';
                        }
                    }
                    else {
                        save_move(map, un);
                        right(map);
                    }
                }

                setO(map, sol, 6, 9, 1, 5);
                break;

            case 'k': //up
                if(map[x][y - 1][z] != '#') {
                    if(map[x][y - 1][z] == '$') {
                        if(map[x][y - 2][z] != '$' && map[x][y - 2][z] != '#') {
                            save_move(map, un);
                            up_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        up(map);
                    }
                }

                setO(map, sol, 6, 9, 1, 5);
                break;

            case 'j': //down
                if(map[x][y + 1][z] != '#') {
                    if(map[x][y + 1][z] == '$') {
                        if(map[x][y + 2][z] != '$' && map[x][y + 2][z] != '#') {
                            save_move(map, un);
                            down_both(map);
                        }
                    }
                    else {
                        save_move(map, un);
                        down(map);
                    }
                }

                setO(map, sol, 6, 9, 1, 5);
                break;

            case 'u': //undo
                if(u > -1)
                    undo(map, un);
                break;
        }

    }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    fclose(ifp);

    printf("\n*****축하합니다! 모든 맵을 완수하셨습니다!*****\n");

    return 0;
}

void up(char map[][N][N]) {
    map[x][y--][z] = ' ';
    map[x][y][z] = '@';
}

void up_both(char map[][N][N]) {
    map[x][y - 2][z] = '$';
    up(map);
}

void down(char map[][N][N]) {
    map[x][y++][z] = ' ';
    map[x][y][z] = '@';
}

void down_both(char map[][N][N]) {
    map[x][y + 2][z] = '$';
    down(map);
}

void left(char map[][N][N]) {
    map[x][y][z--] = ' ';
    map[x][y][z] = '@';
}

void left_both(char map[][N][N]) {
    map[x][y][z - 2] = '$';
    left(map);
}

void right(char map[][N][N]) {
    map[x][y][z++] = ' ';
    map[x][y][z] = '@';
}

void right_both(char map[][N][N]) {
    map[x][y][z + 2] = '$';
    right(map);
}

void setO(char map[][N][N], char sol[][N][N], int n, int n_max, int m, int m_max) {
    int i, j;

    for(i = n; i < n_max; i++)
        for(j = m; j < m_max; j++)
            if(sol[x][i][j] != map[x][i][j])
                if(map[x][i][j] == ' ')
                    map[x][i][j] = 'O';
}

void save_move(char map[][N][N], char un[][N][N]) {
    int i, j;

    if(u == 4) {
        pull(un);
        u--;
    }
    for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            un[u + 1][i][j] = map[x][i][j];
    u++;
}

void pull(char un[][N][N]) {
    int i, j, k;

    for(k = 0; k < 4; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                un[k][i][j] = un[k + 1][i][j];
}

void undo(char map[][N][N], char un[][N][N]) {
    int i, j;

   for(i = 0; i < N; i++)
        for(j = 0; j < N; j++)
            map[x][i][j] = un[u][i][j];
    u--;

    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            if(map[x][i][j] == '@') {
                y = i;
                z = j;
                return;
            }
        }
    }
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

