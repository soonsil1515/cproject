#include<stdio.h>
#include <termio.h>
#include<stdlib.h>
#define N 30
void load_file(char[][N][N],char[][N][N]); //file을 load해주는 함수
void save_file(char[][N][N], char[][N][N]); // file을 save해주는 함수
void display(void);  //명령 내용을 보여주는 함수
int getch(void); //명령어를 입력 받는 함수
void setO(char[][N][N], char[][N][N], int, int, int, int); //O자리에 $가 아닐 때 O로 메꿔주는 함수
void left(char[][N][N]); //왼쪽으로 이동하는 함수
void left_both(char[][N][N]); //왼쪽으로 이동하고 $도 왼쪽으로 같이 이동하는 함수
void right(char[][N][N]); //오른쪽으로 이동하는 함수
void right_both(char[][N][N]); //오른쪽으로 이동하고 $도 오른쪽으로 같이 이동하는 함수
void up(char[][N][N]); //위쪽으로 이동하는 함수
void up_both(char[][N][N]); //위쪽으로 이동하고 $도 위쪽으로 같이 이동하는 함수
void down(char[][N][N]); //아래쪽으로 이동하는 함수
void down_both(char[][N][N]); //아래쪽으로 이동하고 $도 아래쪽으로 같이 이동하는 함수
void save_move(char[][N][N], char[][N][N]); //undo기능을 위해 움직일 때 마다 전 단게를 저장하는 함수
void pull(char[][N][N]); //5개의 저장공간이 가득 찼을 시 공간의 맨 뒷부분을 비우게 당겨주는 함수
void undo(char[][N][N], char [][N][N]); //되돌리기 기능의 함수
int x, y, z, u; //@의 위치를 나타내기 위한 전역변수
FILE *sfp; // file을 save하기 위한 포인터 변수
char save_un[5][N][N];

int main(void)
{
    int i = 0, j = 0, k;
    char map[5][N][N] = {'\0'};
    char sol[5][N][N] = {'\0'};
    char un[5][N][N] = {'\0'};

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

    for(k = 0; k < 5; k++) 
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                sol[k][i][j] = map[k][i][j];

    //map1
    printf("-----------MAP1-----------\n\n");
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
            case 'd': //display help
                display();
                break;
            case 's' : //save file
                save_file(map,un);
                break;
            case 'f' : //file load
                load_file(map,un);
                //setO(map, sol, 6, 9, 19, 21);
                break;
                
            case 'e': //game exit and save game
                save_file(map, un);
                return 0;
        } 
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);

    printf("\nMAP1을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map2
    printf("-----------MAP2-----------\n\n");
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
            case 'd': //display help
                display();
                break;
            case 's' : //save file
                save_file(map,un);
                break;
            case 'f' : //file load
                load_file(map,un);
                setO(map, sol, 2, 7, 1, 3);
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
            case 'd': //display help
                display();
                break;
            case 's' : //save file
                save_file(map,un);
                break;
            case 'f' : //file load
                load_file(map,un);
                setO(map, sol, 7, 10, 1, 5);
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
            case 'd': //display help
                display();
                break;
            case 's' : //save file
                save_file(map,un);
                break;
            case 'f' : //file load
                load_file(map,un);
                setO(map, sol, 2, 7, 17, 21);
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
            case 'd': //display help
                display();
                break;
            case 's' : //save file
                save_file(map,un);
                break;
            case 'f' : //file load
                load_file(map,un);
                setO(map, sol, 6, 9, 1, 5);
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
void display(void){
    printf("* h(왼쪽), j(아래), k(위), l(오른쪽) : 창고지기 조정\n\n");
    printf("* u(undo) : 최대 5번 할 수 있음\n\n");
    printf("* r(reply) : 현재 뱁을 처음부터 다시 시작(게임시간은 계속 유지\n\n");
    printf("* n(new) : 첫 번째 맵부터 다시 시작(현재까지의 시간 기록 삭제)\n\n");
    printf("* e(exit) : 게임 종료. 종료하기 전 필요한 정보 저장해야 함\n\n");
    printf("* s(save) : 현재 상태 파일에 저장\n\n");
    printf("* f(file load) : sokoban 파일에서 저장된 내용을 읽어 save 시점에서부터 이어서 게임하게 함\n\n");
    printf("* d(display help) : 명령 내용 보여줌\n\n");
    printf("* t(top) : 게임 순위 보여줌. t만 입력하면 전체 순위. t 다음 숫자가 오면 해당 맵의 순위\n\n");
}
void save_file(char map[][N][N],char un[][N][N]){
    int i,j, k;

    sfp = fopen("sokoban","w");

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            fprintf(sfp,"%c",map[x][i][j]);
    fprintf(sfp,"*");

    for(i = 0; i < 5; i ++)
        for(j = 0; j < N; j++)
            for(k = 0; k < N; k++)
                fprintf(sfp,"%c", un[i][j][k]);
    fclose(sfp);	
}
void load_file(char map[][N][N],char un[][N][N]){
    int i,j, k;
    char temp;

    sfp = fopen("sokoban","r");
    if(sfp==NULL){
        printf("save한 파일이 존재하지 않습니다.\n");
        exit(1);
    }
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            fscanf(sfp,"%c",&temp);
            if(temp=='@')
            {
                map[x][i][j] = temp;
                y=i;
                z=j;
            }
            else if(temp=='*')break;
            else 
                map[x][i][j] = temp;
        }
        if(temp=='*') {
            map[x][i][j] = '\0';
            break;
        }
    }
    fgetc(sfp);

    for(i=0;i < 5;i++)
        for(j=0;j<N;j++)
            for(k = 0; k < N; k++) {
               fscanf(sfp,"%c",&un[i][j][k]);
            }

    fclose(sfp);

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

