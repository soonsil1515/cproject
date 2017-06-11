#include<stdio.h>
#include <termio.h>
#include<stdlib.h>
#include <time.h>
#define N 30
int display_rank(char); //게임 순위를 보여주는 함수
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
void save_rank(char [], float , int); //char name[]과 float ex_time, int map_num을 파라미터로 넘긴다.
int move(char, char[][N][N], char [][N][N], char[][N][N], int, int, int, int, char[]); //명령여 (command)를 입력받는 함수

int x, y, z, u; //@의 위치를 나타내기 위한 전역변수
FILE *sfp; // file을 save하기 위한 포인터 변수
time_t start_clock =0 , end_clock =0;
float save_clock=0;
int save_map; // file을 save했을 떄 save한 파일이 몇 번 맵인지를 저장할 변수 

int main(void)
{
    int temp[10];
    int i = 0, j = 0, k, map_num = 0;
    int circle_count = 0 , dollar_count = 0; //O의 갯수와 $의 갯수를 비교하기위해 선언한 변수
    char map[5][N][N] = {'\0'};
    char sol[5][N][N] = {'\0'};
    char un[5][N][N] = {'\0'};
    char name[20];
    FILE *ifp;
    time_t stop_clock=0;
    int store_clock = 0;
    char c, command;
    int n = 1, check = 1;
    ifp = fopen("C:\\Users\\Owner\\Desktop\\2017_1 하정현\\1.txt", "r");
    fgetc(ifp);
    fgetc(ifp);
    fgetc(ifp);
    fgetc(ifp);
    if(ifp==NULL)printf("no");
    for(k=0;k<5;k++)
    {
        circle_count = 0 ; //맵별로 O의 갯수를 초기화
        dollar_count = 0; //각 맵별로 $의 갯수를 초기화
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

                if(map[k][i][j] == 'O') circle_count++; //O의 갯수를 센다
                else if(map[k][i][j] == '$') dollar_count++; //$의 갯수를 센다

            }
            if(map[k][i][0]=='m')
            {
                map[k][i][0]='\0';
                fgetc(ifp);
                fgetc(ifp);
                break;	
            }
            if(map[k][i][0] == 'e')
            {
                map[k][i][0] = '\0';
                break;
            }
            if(map[k][i][j] == 'O' ) circle_count++;
        }
        if(circle_count != dollar_count){
            printf("circle count의 개수 : %d \n", circle_count);
            printf("dollar count의 개수 : %d\n" , dollar_count);
            printf("$와 0의 갯수가 달라 강제 종료 합니다. \n");
            exit(0);
         }
    }
    fgetc(ifp);
    fgetc(ifp);
    fgetc(ifp);


    for(k = 0; k < 5; k++) 
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                sol[k][i][j] = map[k][i][j];

    printf("Start....\n");
    printf("Input name : ");
    scanf("%s", name);//이름 입력받고 저장
    getchar();
    printf("\n");

map1:
    for(k = 0; k < 5; k++)
        for(i = 0; i < N; i++)
            for(j = 0; j < N; j++)
                map[k][i][j] = sol[k][i][j];
    //map1
    printf("-----------MAP1-----------\n\n");
    printf("    Hello %s\n\n",name);
    start_clock = time(NULL); //시간을 재기 시작한다
    //x-> 맵 번호 y, z-> @의 좌표 값, u-> undo가 몇 번째 인지를 보여주는 변수
    x = 0; 
    y = 9;
    z = 12;
    u = -1;
    map_num = 1;
map1_1:
    while(map[0][7][19] != '$' || map[0][8][19] != '$' || map[0][9][19] != '$' || map[0][7][20] != '$' || map[0][8][20] != '$' || map[0][9][20] != '$') { 
        for(int i = 0; i < N; i++) 
            for(int j = 0; j < N; j++) 
                printf("%c", map[x][i][j]);

        printf("(Command) ");
        command = getch();
        if(command == 'n') 
        {
            printf("%c\n\n",command);
            goto map1;//n를 눌르면 게임 시작으로 돌아감
        }
        if(command == 'r') //replay
        {
            for(int i = 0 ; i < N ; i++){
                for(int j = 0 ; j < N ; j++){
                    map[0][i][j] = sol[0][i][j]; //r을 누르면 map의 가장처음상태로 초기화해준다
                }
            }
            x = 0; //r을 누르면 좌표도 초기화해준다
            y = 9;
            z = 12;
            u = -1;
        }
        if(command == 'f') {
            stop_clock =time(NULL);
            load_file(map, un); 
            switch(x) {     
                case 0:  // save한 맵으로 갈 수 있게 해주는 switch문
                    goto map1_1;
                    break;
                case 1:
                    goto map2;
                    break;
                case 2:
                    goto map3;
                    break;
                case 3:
                    goto map4;
                    break;
                case 4:
                    goto map5;
                    break;
            }
        }
        if(!move(command, map, sol, un, 7, 10, 19, 21, name)) //강제종료 
        {
            return 0;} //강제종료
    }


    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);
    end_clock = time(NULL); //시간을 재는 것을 멈춘다
    store_clock = (float)(end_clock - start_clock); //게임을 한 총 시간은 store_clock이라는 변수에 저장된다.
    if(command == 'f')
        store_clock = save_clock + (float)(end_clock-stop_clock);//저장했던 시간을 계산해서 시간을 넣는다
    save_rank(name, store_clock, map_num);
    printf("\nMAP1을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map2
    printf("-----------MAP2-----------\n\n");
    printf("    Hello %s\n\n",name);
    start_clock = time(NULL);
    //x->맵 번호 y, z-> @의 좌표 값, u-> undo기능을 위한
    x = 1;
    y = 5;
    z = 7;
    u = -1;
    map_num = 2;
map2:
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
        if(command == 'n') 
        {
            printf("%c\n\n",command);
            goto map1;
        }

        if(command == 'r') //replay
        {
            for(int i = 0 ; i < N ;i++){
                for(int j = 0 ; j < N ; j++){
                    map[1][i][j] = sol[1][i][j];
                }
            } //r을 누르면 map과 좌표가 초기화된다
            x = 1;
            y = 5;
            z = 7;
            u = -1;
        }

        if(command == 'f') {
            stop_clock = time(NULL);
            load_file(map, un);
            switch(x) {
                case 0:
                    goto map1_1;
                    break;
                case 1:
                    goto map2;
                    break;
                case 2:
                    goto map3;
                    break;
                case 3:
                    goto map4;
                    break;
                case 4:
                    goto map5;
                    break;
            }

        }
        if(!move(command, map, sol, un,2, 7, 1, 3, name)){	
            return 0;}
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);
    end_clock = time(NULL);//map2를 종료하면 시간 재는 것이 종료된다
    store_clock = (float)(end_clock - start_clock); //store_clock이라는 변수에 게임을 시행한 시간을 저장한
    if(command == 'f') 
        store_clock = save_clock + (float)(end_clock-stop_clock);
    save_rank(name, store_clock, map_num);

    printf("\nMAP2을 성공하셨습니다!\n");
    printf("--------------------------\n\n");


    //map3
    printf("-----------MAP3-----------\n\n");
    printf("    Hello %s\n\n",name);
    start_clock = time(NULL); //map3 게임 시행 시간 재는 것을 시작한다
    //x-> 맵 번호 y, z-> @의 좌표 값 u-> undo기능을 위한 변수
    x = 2;
    y = 2;
    z = 14;
    u = -1;
    map_num = 3;
map3:
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
        if(command == 'n') 
        {
            printf("%c\n\n",command);
            goto map1;
        }
        if(command == 'r') //replay
        {
            for(int i = 0 ; i < N ;i++){
                for(int j = 0 ; j < N ; j++){
                    map[2][i][j] = sol[2][i][j];
                }
            } //r을 누르면 map과 좌표가 초기화된다
            x = 2;
            y = 2;
            z = 14;
            u = -1;
        }


        if(command == 'f') {
            stop_clock =time(NULL);
            load_file(map, un);
            switch(x) {
                case 0:
                    goto map1_1;
                    break;
                case 1:
                    goto map2;
                    break;
                case 2:
                    goto map3;
                    break;
                case 3:
                    goto map4;
                    break;
                case 4:
                    goto map5;
                    break;
            }
        }
        if(!move(command, map, sol, un, 7, 10, 1, 5, name)){ 
            return 0;}
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);
    end_clock = time(NULL); //map3이 성공적으 끝나면 시간 재는 것을 종료한다
    store_clock = (float)(end_clock - start_clock); //게임이 시행된 시간은 store_clock이라는 변수에 저장된다
    if(command == 'f')
        store_clock = save_clock + (float)(end_clock-stop_clock);
    save_rank(name, store_clock , map_num);

    printf("\nMAP3을 성공하셨습니다!\n");
    printf("--------------------------\n\n");

    //map4
    printf("-----------MAP4-----------\n\n");
    printf("    Hello %s\n\n",name);
    start_clock = time(NULL); //map4 게임 시행 시간을재는 것을 시작한다
    //x-> 맵 번호 y,z-> @의 좌표 u-> undo를 위한 변수
    x = 3; 
    y = 11;

    z = 8;
    u = -1;
    map_num = 4;
map4:
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
        if(command == 'n') 
        {
            printf("%c\n\n",command);
            goto map1;
        }
        if(command == 'r'){ //replay
            for(int i = 0 ; i < N ; i++){
                for(int j = 0 ; j < N ; j++){
                    map[3][i][j] = sol[3][i][j];
                } //r을 누르면 map과 좌표를 초기화한다
            }
            x = 3;
            y = 11;
            z = 8;
            u = -1;
        }

        if(command == 'f') {
            stop_clock =time(NULL);
            load_file(map, un);
            switch(x) {
                case 0:
                    goto map1_1;
                    break;
                case 1:
                    goto map2;
                    break;
                case 2:
                    goto map3;
                    break;
                case 3:
                    goto map4;
                    break;
                case 4:
                    goto map5;
                    break;
            }
        }
        if(!move(command, map, sol, un, 2, 7, 17, 21, name)){ 
            return 0;}
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);
    end_clock = time(NULL); //map4 게임에 성공하면 시간 재는 것을 종료한다
    store_clock = (float)(end_clock - start_clock); //store_clock이라는 변수에 게임 시행 시간을 저장한다
    if(command == 'f')
        store_clock = save_clock + (float)(end_clock-stop_clock);
    save_rank(name, store_clock, map_num);

    printf("\nMAP4을 성공하셨습니다!\n");

    printf("--------------------------\n\n");

    //map5
    printf("-----------MAP5-----------\n\n");
    printf("    Hello %s\n\n",name);
    start_clock = time(NULL); //map5 게임 시행 시간을 저장한다
    //x-> 맵 번호 y,z-> @의 좌표 u-> undo를 위한 변수
    x = 4;
    y = 8; 
    z = 14;
    u = -1;
    map_num = 5;
map5:
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
        if(command == 'n') 
        {
            printf("%c\n\n",command);
            goto map1;
        }
        if(command == 'r') //replay
        {
            for(int i = 0 ; i < N ; i++){
                for(int j = 0 ; j < N ; j++){
                    map[4][i][j] = sol[4][i][j];
                }
            } //r을 누르면 map과 좌표를 초기화한다
            x = 4;
            y = 8;
            z = 14;
            u = -1;
        }

        if(command == 'f') {
            stop_clock =time(NULL);
            load_file(map, un);
            switch(x) {
                case 0:
                    goto map1_1;
                    break;
                case 1:
                    goto map2;
                    break;
                case 2:
                    goto map3;
                    break;
                case 3:
                    goto map4;
                    break;
                case 4:
                    goto map5;
                    break;
            }
        }
        if(!move(command, map, sol, un, 6, 9, 1, 5, name)){
            return 0;}
    }

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            printf("%c", map[x][i][j]);
    end_clock = time(NULL);
    store_clock = (float)(end_clock - start_clock);
    if(command == 'f')
        store_clock = save_clock + (float)(end_clock-stop_clock);
    save_rank(name, store_clock , map_num);

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

	sfp = fopen("C:\\cygwin\\home\\Owner\\sokoban.txt", "w");
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
            fprintf(sfp,"%c",map[x][i][j]);
    fprintf(sfp,"*");

    for(i = 0; i < 5; i ++)
        for(j = 0; j < N; j++)
            for(k = 0; k < N; k++)
                fprintf(sfp,"%c", un[i][j][k]);
    fprintf(sfp, "*");

    fprintf(sfp, "%d\n", u);  //몇 번의 undo가 남았는지 저장
    fprintf(sfp, "%d\n", x);    // 현재 맵이 몇번 째 맵인지 저장
	fprintf(sfp, "%f\n",save_clock);//파일에 시간을 저장

    fclose(sfp);	

}
void load_file(char map[][N][N],char un[][N][N]){
    int i,j, k;
    char temp;

	 sfp = fopen("C:\\cygwin\\home\\Owner\\sokoban.txt", "r");
    if(sfp==NULL){
        printf("save한 파일이 존재하지 않습니다.\n");
        exit(1);
    }

    x = save_map;  // 현재 맵의 번호를 save한 파일의 맵으로 바꿔줌

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            fscanf(sfp,"%c",&temp);
            if(temp=='@')  // 창고지기의 위치를 저장
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

    for(i=0;i < 5;i++) {
        for(j=0;j<N;j++) {
            for(k = 0; k < N; k++) {
                fscanf(sfp, "%c", &temp);
                if(temp != '*') {
                    un[i][j][k] = temp;
                }
                else break;
            }
            if(temp == '*') break;
        }
        if(temp == '*') {
            un[i][j][k] = '\0';
            break;
        }
    }
    fgetc(sfp);

    fscanf(sfp, "%d", &u);
    fscanf(sfp, "%d", &x);	// 맵번호를 받아옴
	fscanf(sfp, "%f", &save_clock);//파일에서 시간을 불러옴

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


int move(char command, char map[][N][N] , char sol[][N][N] , char un[][N][N] , int n, int n_max, int m, int m_max, char name[]){
    char rank_map;

    if(command == 'h' || command == 'l' || command == 'k' || command == 'j') {
    }
    else
        printf("%c", command);
    if(command == 't')
    {
        rank_map = getch();
        printf("%c",rank_map);
        printf("\n\n");
        display_rank(rank_map);
        return 1;
    }

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

            setO(map, sol, n, n_max, m, m_max);
            return 1;

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

            setO(map, sol, n, n_max, m, m_max);
            return 1;

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
            setO(map, sol, n, n_max, m, m_max);
            return 1;

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

            setO(map, sol, n, n_max, m, m_max);
            return 1;

        case 'u': //undo
            if(u > -1)
                undo(map, un);
            return 1;
        case 'd': //display help
            display();
            return 1;
        case 's' : //save file
			end_clock = time(NULL);
            save_clock = (float)(end_clock-start_clock);
            save_map = x;
            save_file(map,un);
            return 1;
        case 'f' : //file load
            load_file(map,un);
            printf("\n");
            setO(map, sol, n, n_max, m, m_max);
            return 1;

        case 'e': //game exit and save game
            end_clock = time(NULL);
			save_clock = (float)(end_clock-start_clock);
            save_file(map, un);
            printf("\nSEE YOU %s . . . .\n", name);
            return 0; //강제종료시 리턴 0
        case 'n':
            start_clock =time(NULL);
            return 1;

    }
}

void save_rank(char name[], float store_clock ,int map_num) //랭킹을파일에  저장하는 함수 save_rank
{
    char temp[10] = {'x'}; //map1~5를 지우는 변수 temp
    char rank_name[5][6][20] = {'x'}; //rank에 저장되는 이름을 저장하는 배열
    float rank_time[5][6] = {9999.9};//rank에 저장되는 시간을 저장하는 배열
    float tmp_time = {0};//sorting을 위한 배열 tmp_time
    char tmp_name[20];//sorting을 위한 배열 tmp_name
    FILE *rank; //파일 입출력을 위한 포인터

	rank = fopen("C:\\Users\\Owner\\Desktop\\2017_1 하정현\\ranking.txt", "r");

	  if(rank != NULL){ //만약 파일이 이미 존재한다면

		 for(int i = 0 ; i < 5 ; i++){ //파일을 읽어드려서 함수 안에 있는 배열에 저장한다
			 fscanf(rank, "%s", temp);
			 for(int j = 0 ; j < 5 ; j++){
				 fscanf(rank, "%s", rank_name[i][j]);
				 fscanf(rank, "%f", &rank_time[i][j]);
			 }
		 }
	 }
	 	
	else{ //파일이 존재하지 않는다면
    for(int i = 0 ; i < 5 ; i++){ //배열을 9999.9과 x로 초기화한다
        for(int j = 0 ; j < 6 ; j++){
			  rank_time[i][j] = 9999.9;
			  rank_name[i][j][20] = 'X';
			  }
        }
	} 


    rank = fopen("C:\\Users\\Owner\\Desktop\\2017_1 하정현\\ranking.txt", "w");

    for(int i = 0 ; i < 20 ; i++){ //매개변수로 받은 새로운 이름을 저장한다
        rank_name[map_num -1][5][i] = name[i];
    } 
    rank_time[map_num-1][5] = store_clock; //매개변수로 받은 새로운 시간을 저장한다

    for(int j = 5 ; j >= 0 ; j--){ //새로 받은 이름과 시간을 원래의 rank파일에 있던 시간과 sort하여 다시 넣는 코드
        if((rank_time[map_num - 1][j] < rank_time[map_num - 1][j-1]) && j){
            tmp_time = rank_time[map_num - 1][j];
            rank_time[map_num - 1][j] = rank_time[map_num - 1][j-1];
            rank_time[map_num - 1][j-1] = tmp_time;
            for(int k = 0 ; k < 20 ; k++)	tmp_name[k] = rank_name[map_num - 1][j][k];
            for(int k = 0 ; k < 20 ; k++) rank_name[map_num - 1][j][k] = rank_name[map_num - 1][j-1][k];
            for(int k = 0 ; k < 20 ; k++) rank_name[map_num - 1][j-1][k] = tmp_name[k];

        }
    }


    for(int i = 0 ; i < 5 ; i++){ //위에서 sorting된 랭킹이름,시간을 다시 파일에 출력한다
        fprintf(rank, "map%d\n", i+1);
        for(int j = 0 ; j < 5 ; j++){
            fprintf(rank, "%s\n", rank_name[i][j]);
            fprintf(rank, "%f\n", rank_time[i][j]);
        }
    }
    fclose(rank);
}

int display_rank(char rank_map)
{

    char temp[5][10] = {0};
    char rank_name[5][6][20] = {0};
    float rank_time[5][6] = {0};

    FILE *rank;
    if(rank==NULL)return 0;  // ranking이 갱신된 적이 없는 경우 t가 수행되지 않음
    rank = fopen("C:\\Users\\Owner\\Desktop\\2017_1 하정현\\ranking.txt", "r");
    for(int i = 0 ; i < 5 ; i++){
        fscanf(rank, "%s", temp[i]);
        for(int j = 0 ; j < 5 ; j++){
            fscanf(rank,"%s",rank_name[i][j]);
            fscanf(rank,"%f", &rank_time[i][j]);
        }
    }
    if(rank_map==' ')
    {
        for(int i = 0 ; i < 5 ; i++){
            printf("%s \n",temp[i]);
            for(int j = 0 ; j < 5 ; j++){
                printf("%10s  ",rank_name[i][j]);
                printf("%.1fsec\n", rank_time[i][j]);
            }
        }
    }
    else{
        for(int i = rank_map-'0'-1 ; i < rank_map-'0' ; i++){
            printf("%s \n",temp[i]);
            for(int j = 0 ; j < 5 ; j++){
                printf("%10s  ",rank_name[i][j]);
                printf("%.1fsec\n", rank_time[i][j]);
            }
        }
    }
    printf("\n");
    fclose(rank);
    return 0;
}

