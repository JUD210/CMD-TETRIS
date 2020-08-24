/********** TO DO LIST ����!!! **********/

//TD : block_attack (3 lv), block_assistant (5 lv) off ��� �߰�
//TD : Hold �� �޺� ���� ����
//TD : Main menu �� BGM �߰�
//TD : [3 stage���� : �ð� ���� ������ �� �� �ö���� ��� on]
//TD : [5 stage���� : �ؿ� ���� �� ���� ��� off]
//
//TD : map ���� ���� (void, wall, diamond, heart, zigzag, random)
//TDL : stage ���� ����
//

/********** TO DO LIST ��!!! **********/



/********** BGM ON/OFF ***********/
//PlaySound ã�Ƽ� Comment/Uncomment
/********** BGM ON/OFF ***********/

#include <stdio.h>                // main()
#include <stdlib.h>               // ����
#include <time.h>                 // ����
#include <windows.h>              // gotoxy(), setcolor(), GetTickCount();
#include <conio.h>                // _getch(), _kbhit()
#include <mmsystem.h>             // bgm
#pragma comment(lib, "winmm.lib") // bgm

/********** �Լ� ���� ����!!! **********/

void gotoxy(int x, int y);             //�ܼ�â Ŀ�� �̵�
void setcolor(int color, int bgcolor); //�� ���� (0~16,0~16)
void removecursor();                   //Ŀ�� ������ ����

void main_menu(); //���α׷� ���۽� �۵�
void in_game();   //���� ���۽� �۵�

void initiate_variables(); //���������� �ʱ�ȭ

void line_check(); //�� �� ���� ����, �޺��� ����

void draw_ui();            //�⺻ ui �׸���
void draw_score_board();   //������ �׸���
void draw_stored_blocks(); //����� ���� �׸���
void draw_dancer();        //���ߴ� ��� �׸���
void draw_main_game();     //

void create_block();

void song_play();
void speed_ctrl();

void keyboard_ctrl();

void map(int a);
void key_light_on(int input);
void key_light_off();

void block(int input_shape, int input_x, int input_y, int move_x, int move_y, int input_rotate, int input_state);
void block_ctrl(int input_shape, int input_x, int input_y, int input_rotate, int input_state, int input_command);
void block_fall();

void print_debug_info();

/********** �Լ� ���� ��!!! **********/

/********** �������� ����!!! **********/

int game_screen[26][16] = {
    // [0~25][0~11] : MAIN GAME SCREEN, [0~2, 3~5, 6~8, 9~11][12~15] : NEXT LIST, [12~14][12~15] : HOLD
    {7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7}, // (5,0 or 5,1) : �� ���� ��ġ
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // 7:��, 8:���� ���� ���� ����, (8->2 �� �� ���� ����)
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // 9:���� ������ ä��� ��
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // 0:�� ĭ
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // state = (shape * 100~600) + (rotate * 0~30);
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // game_screen[y][x] = state;
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // if (game_screen[y][x] % 10 == 1) { checkCtrl = 1 } // �������� ��
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7}, // if (game_screen[y][x] % 10 == 2) { checkCtrl = 0 } // ������ ��
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}};

int game_over; // ���� ���� ����

int power_all;          // main_menu(), in_game() ����
int power_main_menu;    // ���� �޴� ����
int power_in_game;      // �ΰ��� ����
int power_in_game_loop; //�ΰ��� ���� ����

int draw_again;

int checkCtrl; // 1:������, 0:���� ��

int startTickCount;   // startTickCount = GetTickCount(); 1ȸ
int currentTickCount; // currentTickCount = GetTickCount(); ���

int command; // block_ctrl(); ���� ����Ű �з� ����
int shape;   // block(); ���� ��� ����
int rotate;  // block(); ���� ȸ�� ���� ����
int state;   // block(); ���� ���� ���� ����
             //state = (shape * 100~600) + (rotate * 0~30) + (����/���� �� +1/+2);
int x, y;    // ��ǥ
int i, j, k; // �ݺ���

int input; // input=_getch();

int stage;                  // stage �����Ҽ��� �� �ϰ� �ӵ� ����
int line;                   // next stage line : (10*stage)+(2*(stage-1))-line; ex)1st:10, 2st:12, 3st:14, ...
int line_counter[23] = {0}; // if(line_counter[N]==10) {���� ����}
int score;                  // ���� ���������� �ʿ��� ����

int store_hold;       //������ hold�� block shape ����
int store_hold_ctrl;  //������ -1.ù Ȧ�� ��� ����� 0.����� 1.ù Ȧ�� ��� 2.Ȧ�� ���
int store_hold_count; //������ 0.Ȧ�� ���� �� ���� 1.Ȧ�� �̹� ����!
int store_next[5];    //������ next�� block shape ���� ( 0 : ������ block, 1/2/3/4 : NEXT block )
                      //if (input==99) { store_hold <=> store_next[0]; }

int startTickCount_dance;     // ��
int startTickCount_key_light; // Ű���� ��¦

int song;            // 0.����� 1.BGM001 2.BGM002 3.BGM003  10.next stage  90.title  99.GameOver
int song_counter[3]; // 1. ��� �ȵ� , 0. ��� �� : ���� �� �ߺ� ��� ����
int song_ctrl;       // 1. �뷡 ����  0.�����

int delay;            // �� �������� �ӵ�
int delay_dance;      // ���ߴ� �ӵ�
int delay_dance_ctrl; // if (combo>=3) { delay_dance /= 2, delay_dance_ctrl = 1}
int head;             // �Ӹ� �����̴� �ӵ�

int combo;          // �޺���!!
int combo_ctrl;     // �޺� ����
int combo_continue; // if(combo < combo_continue) { �޺� ���� }

int bgcolor_timer; //���� ��ȭ

int i, j, k; // �ܼ� �ݺ���
int temp;    // ���� ��ȯ��

int debug; // ����� üũ��

/********** �������� ��!!! **********/

/********** main ����!!! **********/

void main()
{
    power_all = 1;
    power_main_menu = 1;

    while (power_all)
    {
        while (power_main_menu)
        {
            main_menu();
            system("cls");
        }
        while (power_in_game)
        {
            in_game();
            system("cls");
        }
    }
}

/********** main ��!!! **********/

/********** �Լ� ���� ����!!! **********/

void main_menu()
{
    gotoxy(21, 4);
    printf("�����������");
    gotoxy(21, 5);
    printf("��                ��");
    gotoxy(21, 6);
    printf("��  T E T R I S   ��");
    gotoxy(21, 7);
    printf("��                ��");
    gotoxy(21, 8);
    printf("�����������");
    gotoxy(21, 11);
    printf("    BETA Ver 1.01   ");
    gotoxy(21, 17);
    printf("    Press ");
    setcolor(11, 0);
    printf("ENTER ");
    setcolor(7, 0);
    printf("!");
    gotoxy(18, 23);
    printf("Made by: Min Hyuk (JUD210)");
	gotoxy(21, 25);
	printf("    2017. 06. 20"); 

    int input;
    input = _getch();
    if (input == 13)
        power_main_menu = 0, power_in_game = 1;
}
void in_game()
{
    srand((unsigned int)time(NULL));
    removecursor();

    initiate_variables();

    draw_ui();

    while (power_in_game_loop)
    {
        currentTickCount = GetTickCount();

        if (draw_again == 1)
        {
            system("cls");
            draw_ui();
            draw_again = 0;
        }
        draw_stored_blocks();
        draw_score_board();

        line_check();

        draw_main_game();

        song_play();
        speed_ctrl();

        create_block();

        keyboard_ctrl();

        draw_dancer();

        key_light_off();

        block_fall();

        print_debug_info();
    }
}

void gotoxy(int x, int y) //Ŀ�� �̵�
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void setcolor(int color, int bgcolor) //�� ���� (0~16,0~16)
{
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void removecursor() // Ŀ�� ������ ����
{
    CONSOLE_CURSOR_INFO cur;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
    cur.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

void initiate_variables()
{
    startTickCount = GetTickCount(), startTickCount_dance = GetTickCount(), startTickCount_key_light = GetTickCount();
    power_in_game_loop = 1, game_over = 0, debug = 0;
    checkCtrl = 0, combo_continue = 0, head = 0, bgcolor_timer = 1, delay_dance_ctrl = 0;
    song_ctrl = 1, song = rand() % 3 + 1, song_counter[0] = 1, song_counter[1] = 1, song_counter[2] = 1;
    draw_again = 0, store_hold = 0, store_hold_ctrl = -1, store_hold_count = 0;
    stage = 1, line = 0, score = 0, combo = 0;
    map(rand() % 1 + 1); //������ �� �߰��� % n �ٲ��

    for (i = 0; i < 5; i++)
    {
        store_next[i] = rand() % 7 + 1;
    }
}

void line_check()
{
    if (checkCtrl == 0) // lose_ctrl
    {
        combo_ctrl = 0;
        for (i = 23; i >= 1; i--)
        {
            for (j = 0; j <= 10; j++) // �� �� ���� Ž��
            {
                if (j == 0)
                    line_counter[i - 1] = 0;
                if (j > 0 && game_screen[i][j] % 10 == 2)
                    line_counter[i - 1]++;
            }

            for (j = 0; j < 3; j++) // �� �� ���� 3�� ��¦�̱�
            {
                if (line_counter[i - 1] == 10)
                {
                    gotoxy(21, i + 1); // x:+24, y:+1
                    if (j % 2 == 0)
                    {
                        printf("������������");
                    }
                    else
                    {
                        printf("�âââââââââ�");
                    }
                    Sleep(25);
                }
            }

            if (line_counter[i - 1] == 10) // �� �� ���� ǥ��
            {
                line++;
                score++;
                combo_ctrl++;
            }
        }

        if (combo_ctrl > 0) // �޺��� ����
        {
            combo++, combo_ctrl = 0;
            score += combo - 1; // �޺� �� ������ ���� ���� ����
        }

        if (combo <= combo_continue) // �޺� ���� ����
            combo = 0, combo_continue = 0;

        if (combo >= 3 && delay_dance_ctrl == 0) // DANCE TIME BEGIN!!!
            delay_dance /= 2, delay_dance_ctrl = 1;
        if (combo < 3 && delay_dance_ctrl == 1) // end...
            delay_dance *= 2, delay_dance_ctrl = 0;

        i = 23;
        while (i >= 1) // �� �� ���� ����
        {
            if (line_counter[i - 1] == 10)
            {
                for (k = i; k > 1; k--)
                {
                    for (j = 1; j <= 10; j++)
                    {
                        game_screen[k][j] = game_screen[k - 1][j];
                        line_counter[k - 1] = line_counter[k - 2];
                    }
                }
                i = 24;
            }
            i--;
        }
    }
}

void draw_ui()
{
    gotoxy(5, 1);
    printf(" H O L D");
    for (i = 2; i <= 7; i++) // HOLD size : 5~12(8 byte) * 3~5
    {
        gotoxy(3, i);
        if (i == 2 || i == 7)
            printf("$$$$$$$$$$$$");
        else
            printf("$$        $$");
    }

    gotoxy(49, 1);
    printf("  N E X T");
    for (i = 2; i <= 7; i++) // NEXT size : 49~56(8 byte) * 3~5
    {
        gotoxy(43, i);
        if (i == 2 || i == 7)
            printf("      �������");
        else
            printf("      ��        ��");
    }

    for (i = 10; i <= 25; i++) // NEXT List size : 49~56(8 byte) * 9~11 + 13~15 + 17~19 + 21~23
    {
        gotoxy(43, i);
        if (i == 10 || i == 25)
            printf("      �������");
        else
            printf("      ��        ��");
        if (i == 15 || i == 20) //debugging ����
        {
            gotoxy(51, i);
            printf("�����");
        }
    }

    /////////////////////////////////
    gotoxy(1, 8); // Left Side
    printf("  S T A G E : ");
    gotoxy(1, 9);
    printf("    L I N E : ");
    gotoxy(1, 10);
    printf("  S C O R E : ");
    gotoxy(1, 12);
    printf("  next stage");
    gotoxy(1, 13);
    printf("  :    lines");
    gotoxy(1, 15);
    printf("     Rotate");
    gotoxy(8, 16);
    printf("��");
    gotoxy(1, 17);
    printf(" Left��");
    gotoxy(10, 17);
    printf("��Right");
    gotoxy(8, 18);
    printf("��");
    gotoxy(1, 19);
    printf("    Fast Down");
    gotoxy(2, 21);
    printf("[SPACE] : Drop");
    gotoxy(2, 22);
    printf("[Z / X] : Rotate");
    gotoxy(2, 23);
    printf("[  C  ] : Hold");
    gotoxy(2, 24);
    printf("[T A B] : Pause");
    gotoxy(2, 25);
    printf("[E S C] : Quit");
    gotoxy(2, 26);
    printf("[  `  ] : Debug Mode");
}
void draw_score_board()
{
    if ((stage * stage) + 9 * stage - line <= 0)
        stage++, song_ctrl = 1;
    gotoxy(15, 8);
    printf("%d ", stage);
    gotoxy(15, 9);
    printf("%d ", line);
    gotoxy(15, 10);
    printf("%d ", score);
    gotoxy(4, 13);
    printf("%3d ", (stage * stage) + 9 * stage - line);
    //[S=1]10-L, [S=2]10+(10+2)-L, [s=3]10+(10+2)+(10+4)-L, ...
    //[S=n] { k=1 to k=n sigma 10+2(k-1) } - L
    //[S=n] { n^2 + 9n } - L  �Ѱ��������� Ȱ�� : ���α׷��Ӱ� ������ ����� �ϴ� ����
}
void draw_stored_blocks()
{
    if (debug == 1)
        return;
    for (i = 1; i <= 5; i++) // �׸���.
    {                        //i==1 : next, i==2~4 : next list, i==5 hold
        int tx, ty;          // tx:temp_x, ty:temp_y
        if (i == 1)
        {
            switch (store_next[i])
            {
            case 1:
                setcolor(14, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(53, ty + 4);
                    for (tx = 12; tx <= 13; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 2:
                setcolor(12, 0);
                for (ty = 0; ty <= 0; ty++)
                {
                    gotoxy(51, ty + 5);
                    for (tx = 12; tx <= 15; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 3:
                setcolor(10, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(52, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 4:
                setcolor(11, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(52, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 5:
                setcolor(15, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(52, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 6:
                setcolor(9, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(52, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 7:
                setcolor(13, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(52, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            }
        }
        else if (i < 5)
        {
            switch (store_next[i])
            {
            case 1:
                setcolor(14, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(53, ty + 9);
                    if (i == 3)
                        gotoxy(53, ty + 11);
                    if (i == 4)
                        gotoxy(53, ty + 13);
                    for (tx = 12; tx <= 13; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 2:
                setcolor(12, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3; ty++)
                {
                    if (i == 2)
                        gotoxy(51, ty + 10);
                    if (i == 3)
                        gotoxy(51, ty + 12);
                    if (i == 4)
                        gotoxy(51, ty + 14);
                    for (tx = 12; tx <= 15; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 3:
                setcolor(10, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(52, ty + 9);
                    if (i == 3)
                        gotoxy(52, ty + 11);
                    if (i == 4)
                        gotoxy(52, ty + 13);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 4:
                setcolor(11, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(52, ty + 9);
                    if (i == 3)
                        gotoxy(52, ty + 11);
                    if (i == 4)
                        gotoxy(52, ty + 13);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 5:
                setcolor(15, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(52, ty + 9);
                    if (i == 3)
                        gotoxy(52, ty + 11);
                    if (i == 4)
                        gotoxy(52, ty + 13);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 6:
                setcolor(9, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(52, ty + 9);
                    if (i == 3)
                        gotoxy(52, ty + 11);
                    if (i == 4)
                        gotoxy(52, ty + 13);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 7:
                setcolor(13, 0);
                for (ty = (i - 1) * 3; ty <= (i - 1) * 3 + 1; ty++)
                {
                    if (i == 2)
                        gotoxy(52, ty + 9);
                    if (i == 3)
                        gotoxy(52, ty + 11);
                    if (i == 4)
                        gotoxy(52, ty + 13);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            }
        }
        else if (i == 5)
        {
            switch (store_hold)
            {
            case 1:
                setcolor(14, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(7, ty + 4);
                    for (tx = 12; tx <= 13; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 2:
                setcolor(12, 0);
                for (ty = 0; ty <= 0; ty++)
                {
                    gotoxy(5, ty + 5);
                    for (tx = 12; tx <= 15; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 3:
                setcolor(10, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(6, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 4:
                setcolor(11, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(6, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 5:
                setcolor(15, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(6, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 6:
                setcolor(9, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(6, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            case 7:
                setcolor(13, 0);
                for (ty = 0; ty <= 1; ty++)
                {
                    gotoxy(6, ty + 4);
                    for (tx = 12; tx <= 14; tx++)
                    {
                        if (game_screen[ty + 12][tx] % 10 == 1)
                            printf("��");
                        else
                            printf("  ");
                    }
                }
                setcolor(7, 0);
                break;
            }
        }
    }
}
void draw_dancer()
{
    if (
        ((_kbhit() == 0 && currentTickCount - startTickCount_dance >= delay_dance) ||
         ((input == 75 || input == 77 || input == 72 || input == 80 || input == 32 || input == 122 || input == 120) &&
          currentTickCount - startTickCount_dance >= delay_dance)) &&
        debug == 0)
    {
        bgcolor_timer = rand() % 15 + 1;
        if (combo >= 3)
            setcolor(bgcolor_timer, 0);
        gotoxy(43, 20 - stage);
        printf("%3d", combo);
        gotoxy(43, 21 - stage);
        printf("combo!"); //�޺� ��¦
        if (combo >= 3)
            setcolor(7, 0);
        gotoxy(8, 17);
        setcolor(7, bgcolor_timer);
        printf("  "); //���̽�ƽ ��� ��¦
        setcolor(7, 0);
        setcolor(bgcolor_timer, 0);
        if (head == 0)
        {
            gotoxy(43, 22 - stage);
            printf(" ��   ");
        }
        if (head == 1)
        {
            gotoxy(43, 22 - stage);
            printf("  ��  ");
        }
        if (head == 2)
        {
            gotoxy(43, 22 - stage);
            printf("   �� ");
        }
        if (head == 3)
        {
            gotoxy(43, 22 - stage);
            printf("  ��  ");
        }
        if (bgcolor_timer % 4 == 1)
        {
            gotoxy(43, 23 - stage);
            printf(" /�ӣ�");
            gotoxy(43, 24 - stage);
            printf("  ��  ");
            gotoxy(43, 25 - stage);
            printf(" ���� ");
        }
        if (bgcolor_timer % 4 == 2)
        {
            gotoxy(43, 23 - stage);
            printf("����/ ");
            gotoxy(43, 24 - stage);
            printf("  ��  ");
            gotoxy(43, 25 - stage);
            printf(" ���� ");
        }
        if (bgcolor_timer % 4 == 3)
        {
            gotoxy(43, 23 - stage);
            printf("���ӡ�");
            gotoxy(43, 24 - stage);
            printf("  ��  ");
            gotoxy(43, 25 - stage);
            printf(" �� ��");
        }
        if (bgcolor_timer % 4 == 0)
        {
            gotoxy(43, 23 - stage);
            printf("���ӡ�");
            gotoxy(43, 24 - stage);
            printf("  ��  ");
            gotoxy(43, 25 - stage);
            printf(" ���� ");
        }
        setcolor(7, 0);
        bgcolor_timer++;
        head++;
        if (head == 4)
            head = 0;
        setcolor(0, 7);
        gotoxy(43, 26 - stage);
        printf("��%2d��", stage); //�ٴ�
        setcolor(7, 0);
        startTickCount_dance = GetTickCount();
    }
}
void draw_main_game()
{
    if (game_over == 1) // ���� ������ ȭ�� ä��� ����
    {
        for (i = 1; i < 24; i++)
        {
            for (j = 1; j < 11; j++)
            {
                game_screen[i][j] = 9;
            }
        }
    }

    for (i = 0; i < 25; i++) // Main Game size : (0,0)~(24,24)
    {
        if (game_over == 0)
            gotoxy(19, i + 1);

        if (game_over == 1) // gotoxy ��¼����� �ٲ� ���� ��� �ǵ���
        {
            gotoxy(19, 25 - i);
            if (i == 0)
            {
                for (j = 0; j < 12; j++)
                {
                    game_screen[0][j] = game_screen[24][j];
                }
                PlaySound(TEXT("BGM099-Game over"), NULL, SND_ASYNC);
            }
        }

        for (j = 0; j <= 11; j++)
        {
            if (debug == 1)
                printf("%4d", game_screen[i][j]);
            else if (debug == 0)
            {
                if (game_screen[i][j] == 7)
                    printf("��");
                if (game_screen[i][j] == 8)
                {
                    setcolor(12, 0);
                    printf("��");
                    setcolor(7, 0);
                }
                if (game_screen[i][j] == 0)
                    printf("  ");

                if (game_screen[i][j] % 10 == 1)
                {
                    for (k = 1; k < 8; k++)
                    {
                        if (game_screen[i][j] >= k * 100 && game_screen[i][j] < (k + 1) * 100)
                        {
                            if (k == 0)
                                setcolor(7, 0);
                            else if (k == 1)
                                setcolor(14, 0);
                            else if (k == 2)
                                setcolor(12, 0);
                            else if (k == 3)
                                setcolor(10, 0);
                            else if (k == 4)
                                setcolor(11, 0);
                            else if (k == 5)
                                setcolor(15, 0);
                            else if (k == 6)
                                setcolor(9, 0);
                            else if (k == 7)
                                setcolor(13, 0);
                            printf("��");
                            k = 8;
                        }
                    }
                    setcolor(7, 0);
                }
                //system(7,0) ��(14,0)��� �ѻ���(12,0) ��(10,0)�ʷ� ��(11,0)�ϴ� ��rev��(15,0) ���Ķ�(9,0) ��rev����(13,0)
                if (game_screen[i][j] % 10 == 2)
                {
                    for (k = 0; k < 8; k++)
                    {
                        if (game_screen[i][j] >= k * 100 && game_screen[i][j] < (k + 1) * 100)
                        {
                            if (k == 0)
                                setcolor(7, 0);
                            else if (k == 1)
                                setcolor(14, 0);
                            else if (k == 2)
                                setcolor(12, 0);
                            else if (k == 3)
                                setcolor(10, 0);
                            else if (k == 4)
                                setcolor(11, 0);
                            else if (k == 5)
                                setcolor(15, 0);
                            else if (k == 6)
                                setcolor(9, 0);
                            else if (k == 7)
                                setcolor(13, 0);
                            printf("��");
                            k = 8;
                        }
                    }
                    setcolor(7, 0);
                }

                if (game_screen[i][j] == 9) // ���� ������ ȭ�� ä��� ��
                    printf("��");
                if (game_screen[i][j] == 3) // [debug]���� ���� ��ٸ�, ���� ���ſ� ������ ���� ��
                    printf("��");
            }
        }
        if (game_over == 1)
            Sleep(65);
    }

    while (game_over) // retry : r(114) , menu : ESC(27)
    {
        Sleep(280);
        gotoxy(21, 7);
        printf("                    ");
        gotoxy(21, 8);
        printf(" G A M E    O V E R ");
        gotoxy(21, 9);
        printf("                    ");
        gotoxy(21, 14);
        printf("                    ");
        gotoxy(21, 15);
        printf("Press  r  to Restart");
        gotoxy(21, 16);
        printf("                    ");
        gotoxy(21, 17);
        printf("Press ESC to Quit   ");
        gotoxy(21, 18);
        printf("                    ");

        input = _getch();
        if (input == 114) // r
            game_over = 0, power_in_game_loop = 0;
        else if (input == 27) // ESC
            game_over = 0, power_in_game_loop = 0, power_in_game = 0, power_main_menu = 1;
    }
}

void create_block()
{ ///// �� ����
    if (checkCtrl == 0 && game_over == 0)
    {
        checkCtrl = 1;

        if (store_hold_ctrl == 0) // Ȧ�� ��� �����
            store_hold_count = 0;

        if ((store_hold_ctrl == -1 || store_hold_ctrl == 0) && combo >= 1) // �޺� ���� ���� �ľ��ϱ� ����
            combo_continue++;

        // hold
        switch (store_hold_ctrl)
        {
        case 1: // ó������ hold ��� ������
            store_hold = store_next[0];
            break;
        case 2: // hold ��� ������
            temp = store_next[0];
            store_next[0] = store_hold;
            store_hold = temp;
            break;
        default:
            break;
        }

        if (store_hold_ctrl == -1 || store_hold_ctrl == 0 || store_hold_ctrl == 1)
        {
            for (i = 0; i < 4; i++)
            {
                store_next[i] = store_next[i + 1];
            }
            store_next[4] = rand() % 7 + 1;
        }

        if (store_hold_ctrl != -1)
            store_hold_ctrl = 0;

        for (i = 0; i <= 24; i++) //// BLOCK �� NEXT LIST ���� ��ϵ� ���� �����, ...
        {
            for (j = 12; j <= 15; j++)
            {
                game_screen[i][j] = 0;
            }
        }
        for (i = 0; i <= 24; i++)
        {
            if (i >= 3 && i <= 6)
            {
                gotoxy(5, i);
                printf("        ");
                gotoxy(51, i);
                printf("        ");
            }
            else if (i >= 11 && i <= 24 && i != 15 && i != 20)
            {
                gotoxy(51, i);
                printf("        ");
            }
        }

        for (i = 1; i <= 5; i++) //... �ٽ� �����Ͽ�(block), ...
        {
            if (i < 5)
            {
                switch (store_next[i])
                {
                case 1:
                    block(store_next[i], 12, (i - 1) * 3, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 2:
                    block(store_next[i], 12, (i - 1) * 3, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 3:
                    block(store_next[i], 13, (i - 1) * 3 + 1, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 4:
                    block(store_next[i], 13, (i - 1) * 3 + 1, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 5:
                    block(store_next[i], 13, (i - 1) * 3 + 1, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 6:
                    block(store_next[i], 13, (i - 1) * 3 + 1, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                case 7:
                    block(store_next[i], 13, (i - 1) * 3 + 1, 0, 0, 0, store_next[i] * 100 + 1);
                    break;
                }
            }

            else
            {
                switch (store_hold)
                {
                case 1:
                    block(store_hold, 12, 12, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 2:
                    block(store_hold, 12, 12, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 3:
                    block(store_hold, 13, 13, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 4:
                    block(store_hold, 13, 13, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 5:
                    block(store_hold, 13, 13, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 6:
                    block(store_hold, 13, 13, 0, 0, 0, store_hold * 100 + 1);
                    break;
                case 7:
                    block(store_hold, 13, 13, 0, 0, 0, store_hold * 100 + 1);
                    break;
                }
            }
        }

        ///////////////save

        shape = store_next[0], rotate = 0;
        state = shape * 100 + rotate * 10 + 1;

        switch (shape)
        {
        case 1:
            x = 5, y = 0;
            break;
        case 2:
            x = 4, y = 1;
            break;
        case 3:
            x = 5, y = 1;
            break;
        case 4:
            x = 5, y = 1;
            break;
        case 5:
            x = 5, y = 1;
            break;
        case 6:
            x = 5, y = 1;
            break;
        case 7:
            x = 5, y = 1;
            break;
        }

        block(shape, x, y, 0, 0, 0, state);
        //block(shape, x, y, 0, 0, 0, (shape * 100 + rotate * 10 + 1)); �ϸ� ġ���� ���� �߻� (��?)
    }
}

void song_play()
{
    /////1,3,5, ... �������� ���� �뷡 ����
    if (song_ctrl == 1 && (stage % 2 == 1))
    {
        if (stage > 1) // ���� ����!
        {
            PlaySound(TEXT("BGM010-Next Stage"), NULL, SND_ASYNC);

            for (i = 0; i < 3; i++)
            {
                gotoxy(43, 21 - stage);
                printf("      ");
                gotoxy(43, 22 - stage);
                printf("  ��  ");
                gotoxy(43, 23 - stage);
                printf("���ӣ�");
                gotoxy(43, 24 - stage);
                printf("  ��  ");
                gotoxy(43, 25 - stage);
                printf(" ���� ");
                gotoxy(43, 26 - stage);
                printf("      ");
                Sleep(600);

                gotoxy(43, 22 - stage);
                printf("      ");
                gotoxy(43, 23 - stage);
                printf("  ��  ");
                gotoxy(43, 24 - stage);
                printf("���ӡ�");
                gotoxy(43, 25 - stage);
                printf("  ��  ");
                gotoxy(43, 26 - stage);
                printf(" ���� ");
                Sleep(600);
            }
        }

        if (song_counter[0] == 0 && song_counter[1] == 0 && song_counter[2] == 0)
            song_counter[0] = 1, song_counter[1] = 1, song_counter[2] = 1;

        int power = 1;
        while (power)
        {
            song = rand() % 3 + 1;
            if (song_counter[song - 1] == 1) // ���� �� �ߺ� ��� ����
                power = 0;
        }
        song_ctrl = 0;
    }

    if (song == 1 && game_over == 0)
    {
        PlaySound(TEXT("BGM001-Bradinsky"), NULL, SND_ASYNC | SND_LOOP);
        delay_dance = 345;
        song = 0;
        song_counter[0] = 0;
    }
    if (song == 2 && game_over == 0)
    {
        PlaySound(TEXT("BGM002-Troika"), NULL, SND_ASYNC | SND_LOOP);
        delay_dance = 408;
        song = 0;
        song_counter[1] = 0;
    }
    if (song == 3 && game_over == 0)
    {
        PlaySound(TEXT("BGM003-Kalinka"), NULL, SND_ASYNC | SND_LOOP);
        delay_dance = 406;
        song = 0;
        song_counter[2] = 0;
    }
}
void speed_ctrl()
{
    ///// ���̵� ����
    //�� �ϰ� �ӵ� ����
    if (stage < 5)
    {
        delay = 1000 - stage * 200;
    }
    if (stage >= 5 && stage < 10)
    {
        delay = 200 - (stage - 5) * 20;
    }
    if (stage >= 10)
    {
        delay = 100 - (stage - 10) * 10;
    }
}

void keyboard_ctrl()
{
    //// Ű���� ����
    if (_kbhit() == 1 && checkCtrl == 1)
    {
        input = 0;
        input = _getch();

        if (input == 224)
        {
            input = _getch();
            if (input == 75) // �� Left
            {
                key_light_on(input);
                command = 1;
                block_ctrl(shape, x, y, rotate, state, command);
            }
            else if (input == 77) // �� Right
            {
                key_light_on(input);
                command = 2;
                block_ctrl(shape, x, y, rotate, state, command);
            }
            else if (input == 80) // �� Fast Down
            {
                key_light_on(input);
                command = 3;
                block_ctrl(shape, x, y, rotate, state, command);
            }
            else if (input == 72) // �� Rotate(Clock)
            {
                key_light_on(input);
                command = 5;
                block_ctrl(shape, x, y, rotate, state, command);
            }
        }

        if (input == 32) // [SPACE]:Drop (=Fast Down �ڵ� �ݺ�)
        {
			key_light_on(input);
            command = 4;
            block_ctrl(shape, x, y, rotate, state, command);
        }
        if (input == 120) // [X]:Rotate(Clock)
        {
            key_light_on(input);
            command = 5;
            block_ctrl(shape, x, y, rotate, state, command);
        }
        if (input == 122) // [Z]:Rotate(CounterClock)
        {
            key_light_on(input);
            command = 6;
            block_ctrl(shape, x, y, rotate, state, command);
        }
        if (input == 99) // [C]:Hold
        {
            key_light_on(input);

            if (store_hold_count == 0 && store_hold_ctrl == -1)
                store_hold_ctrl = 1, store_hold_count = 1, checkCtrl = 0;
            if (store_hold_count == 0 && store_hold_ctrl == 0)
                store_hold_ctrl = 2, store_hold_count = 1, checkCtrl = 0;
        }
        if (input == 9) // [Tab]:Pause
        {
            key_light_on(input);
            int power = 1;
            while (power)
            {
                input = 0;
                currentTickCount = GetTickCount();

                setcolor(0, 8);
                gotoxy(21, 6);
                printf("                    ");
                gotoxy(21, 7);
                printf("  P  A  U  S  E  D  ");
                gotoxy(21, 8);
                printf("                    ");
                setcolor(7, 0);

                if (_kbhit() == 1)
                    input = _getch();
                if (input == 9) // [Tab]:Pause
                {
                    key_light_on(input);
                    power = 0;
                }
                if (input == 27) // [ESC]:Quit
                {
                    key_light_on(input);
                    power = 0, power_in_game_loop = 0, power_in_game = 0, power_main_menu = 1;
                }

                draw_dancer();
            }
        }
        if (input == 27) // [ESC]:Quit
        {
            key_light_on(input);
            power_in_game_loop = 0, power_in_game = 0, power_main_menu = 1;
        }

        if (input == 96) // [`] : debug!
        {
            if (debug == 1)
            {
                debug = 0;
                draw_again = 1;
            }
            else if (debug == 0)
            {
                debug = 1;
            }
        }

        if (input == 49 && debug == 1)
            line += 10;
        if (input == 50 && debug == 1)
            stage++;
    }
}

void map(int a) // 0.void 1.wall
    //������          2.diamond 3.heart 4.zigzag 5.random)
{
    for (i = 23; i >= 0; i--)
    {
        for (j = 1; j <= 10; j++)
        {
            if (i == 0)
                game_screen[i][j] = 8;
            else
                game_screen[i][j] = 0;
        }

        for (j = 12; j < 16; j++)
        {
            game_screen[i][j] = 0;
        }
    }

    switch (a)
    {
    case 1:
        for (i = 23; i > 12; i--)
        {
            for (j = 1; j < 11; j++)
            {
                if (j != 5 && j != 6)
                    game_screen[i][j] = 2;
            }
        }
        break;
        //case 2:
        //    for (i = 24; i < 15; i--)
        //    {
        //        for()
        //    }
    }
}
void key_light_on(int input) // ��(72) ��(80) ��(75) ��(77)  SP(32)  z(122)  x(120)  c(99)  TAB(9)  ESC(27)
{
    if (input == 72)
    {
        gotoxy(8, 16);
        setcolor(11, 0);
        printf("��");
        setcolor(7, 0);
    }
    else if (input == 80)
    {
        gotoxy(8, 18);
        setcolor(11, 0);
        printf("��");
        setcolor(7, 0);
    }
    else if (input == 75)
    {
        gotoxy(6, 17);
        setcolor(11, 0);
        printf("��");
        setcolor(7, 0);
    }
    else if (input == 77)
    {
        gotoxy(10, 17);
        setcolor(11, 0);
        printf("��");
        setcolor(7, 0);
    }
    else if (input == 32)
    {
        gotoxy(3, 21);
        setcolor(11, 0);
        printf("SPACE");
        setcolor(7, 0);
    }

    else if (input == 122)
    {
        gotoxy(3, 22);
        setcolor(11, 0);
        printf("Z");
        setcolor(7, 0);
    }
    else if (input == 120)
    {
        gotoxy(7, 22);
        setcolor(11, 0);
        printf("X");
        setcolor(7, 0);
    }
    else if (input == 99)
    {
        gotoxy(5, 23);
        setcolor(11, 0);
        printf("C");
        setcolor(7, 0);
    }
    else if (input == 9)
    {
        gotoxy(3, 24);
        setcolor(11, 0);
        printf("T A B");
        setcolor(7, 0);
    }
    else if (input == 27)
    {
        gotoxy(3, 25);
        setcolor(11, 0);
        printf("E S C");
        setcolor(7, 0);
    }
}
void key_light_off()
{ //key_light_off
    if ((_kbhit() == 0 && currentTickCount - startTickCount_key_light >= 70) ||
        ((input == 75 || input == 77 || input == 72 || input == 80 || input == 32 || input == 122 || input == 120) && currentTickCount - startTickCount_key_light >= 70))
    {
        setcolor(7, 0);
        gotoxy(8, 16);
        printf("��");
        gotoxy(8, 18);
        printf("��");
        gotoxy(6, 17);
        printf("��");
        gotoxy(10, 17);
        printf("��");
        gotoxy(3, 21);
        printf("SPACE");
        gotoxy(3, 22);
        printf("Z");
        gotoxy(7, 22);
        printf("X");
        gotoxy(5, 23);
        printf("C");
        gotoxy(3, 24);
        printf("T A B");
        gotoxy(3, 25);
        printf("E S C");

        startTickCount_key_light = GetTickCount();
    }
}

void block_fall()
{ ///// �ð� ����� ���� �� �ϰ� (=Fast Down 1ȸ �Է�)
    if ((_kbhit() == 0 && currentTickCount - startTickCount >= delay) ||
        ((input == 75 || input == 77 || input == 72 || input == 80 || input == 32 || input == 122 || input == 120) && currentTickCount - startTickCount >= delay))
    {
        command = 3;
        block_ctrl(shape, x, y, rotate, state, command);
        startTickCount = GetTickCount();
    }
}
void block(int input_shape, int input_x, int input_y, int move_x, int move_y, int input_rotate, int input_state)
//shape  // 0:system, 1:�� , 2:�� , 3: ��, 4:�� , 5: ��(rev), 6:��, 7:��(rev)
//�� ���� // system(7,0) ��(14,0)��� �ѻ���(12,0) ��(10,0)�ʷ� ��(11,0)�ϴ� ��rev��(15,0) ���Ķ�(9,0) ��rev����(13,0)

//input_x, input_y : block core�� ��ǥ (�浹 ���� ������ �� �߿�!!!!)
//move_x : Left/Right = -1/+1
//move_y : Down = +1
//input_rotate : 0, 1, 2, 3, 0, 1, 2, 3, ...
//input_state : �� ���� : state = (shape * 100~600) + (rotate * 0~30) + (����/���� �� +1/2);
{
    //////////////////
    int i, j;

    for (j = 0; j <= 23; j++)
    {
        if (j == 0)
        {
            for (i = 1; i <= 10; i++)
            {
                if (game_screen[0][i] % 10 == 1)
                    game_screen[0][i] = 8; // �� �� ���� ���� �� �ܻ� ����
                if (game_screen[0][i] % 10 == 2)
                    game_over = 1; // �� �� ���� ���ο� �� ������ ���ӿ��� ó��
            }
        }
        for (i = 1; i <= 10; i++)
        {
            if (game_screen[j][i] % 10 == 1) // �� �ܻ� ����
                game_screen[j][i] = 0;
        }
    }
    //////////////////

    if (game_over == 0)
    {
        // �� (2*2 ���� ���� ��)
        if (input_shape == 1 && (input_rotate == 0 || input_rotate == 1 || input_rotate == 2 || input_rotate == 3))
        {
            if (game_screen[1][5] % 10 == 2 || game_screen[1][6] % 10 == 2)
                game_over = 1;
            else
            {
                for (j = input_y; j <= input_y + 1; j++)
                {
                    for (i = input_x; i <= input_x + 1; i++)
                    {
                        game_screen[j + move_y][i + move_x] = input_state;
                    }
                }
            }
        }

        // �� (4*4 ���� ���� ��) (����!! : �Ӹ����� �� �� �ٷ� ������ ��!!
        else if (input_shape == 2 && (input_rotate == 0 || input_rotate == 2))
        {
            if (game_screen[1][4] % 10 == 2 || game_screen[1][5] % 10 == 2 || game_screen[1][6] % 10 == 2 || game_screen[1][7] % 10 == 2)
                game_over = 1;
            for (j = input_y; j == input_y; j++)
            {
                for (i = input_x; i <= input_x + 3; i++)
                {
                    game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 2 && (input_rotate == 1 || input_rotate == 3))
        {
            for (j = input_y; j <= input_y + 3; j++)
            {
                for (i = input_x + 1; i <= input_x + 1; i++)
                {
                    game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }

        //�� (3*3 ����� ��)
        else if (input_shape == 3 && input_rotate == 0)
        {
            if (game_screen[1][4] % 10 == 2 || game_screen[1][5] % 10 == 2 || game_screen[1][6] % 10 == 2)
                game_over = 1;
            for (j = input_y - 1; j <= input_y; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y - 1 && (i == input_x - 1 || i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 3 && input_rotate == 1)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 || j == input_y + 1) && i == input_x + 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 3 && input_rotate == 2)
        {
            for (j = input_y; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y + 1 && (i == input_x - 1 || i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 3 && input_rotate == 3)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x; i++)
                {
                    if ((j == input_y - 1 || j == input_y + 1) && i == input_x - 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }

        //�� (3*3 ����� ��)
        else if (input_shape == 4 && input_rotate == 0)
        {
            if (game_screen[1][4] % 10 == 2 || game_screen[1][5] % 10 == 2 || game_screen[1][6] % 10 == 2)
                game_over = 1;
            for (j = input_y - 1; j <= input_y; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y - 1 && (i == input_x || i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 4 && input_rotate == 1)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x; i <= input_x + 1; i++)
                {
                    if ((j == input_y || j == input_y + 1) && i == input_x + 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 4 && input_rotate == 2)
        {
            for (j = input_y; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y + 1 && (i == input_x - 1 || i == input_x))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 4 && input_rotate == 3)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x; i++)
                {
                    if ((j == input_y - 1 || j == input_y) && i == input_x - 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }

        //��rev (3*3 ����� ��)
        else if (input_shape == 5 && input_rotate == 0)
        {
            if (game_screen[1][4] % 10 == 2 || game_screen[1][5] % 10 == 2 || game_screen[1][6] % 10 == 2)
                game_over = 1;
            for (j = input_y - 1; j <= input_y; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y - 1 && (i == input_x - 1 || i == input_x))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 5 && input_rotate == 1)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 || j == input_y) && i == input_x + 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 5 && input_rotate == 2)
        {
            for (j = input_y; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if (j == input_y + 1 && (i == input_x || i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 5 && input_rotate == 3)
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x - 1; i <= input_x; i++)
                {
                    if ((j == input_y || j == input_y + 1) && i == input_x - 1)
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }

        //Z (3*3 ����� ��)
        else if (input_shape == 6 && (input_rotate == 0 || input_rotate == 2))
        {
            for (j = input_y - 1; j <= input_y; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 && i == input_x + 1) || (j == input_y && i == input_x - 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 6 && (input_rotate == 1 || input_rotate == 3))
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 && i == input_x) || (j == input_y + 1 && i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }

        //Zrev (3*3 ����� ��)
        else if (input_shape == 7 && (input_rotate == 0 || input_rotate == 2))
        {
            for (j = input_y - 1; j <= input_y; j++)
            {
                for (i = input_x - 1; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 && i == input_x - 1) || (j == input_y && i == input_x + 1))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
        else if (input_shape == 7 && (input_rotate == 1 || input_rotate == 3))
        {
            for (j = input_y - 1; j <= input_y + 1; j++)
            {
                for (i = input_x; i <= input_x + 1; i++)
                {
                    if ((j == input_y - 1 && i == input_x + 1) || (j == input_y + 1 && i == input_x))
                        continue;
                    else
                        game_screen[j + move_y][i + move_x] = input_state;
                }
            }
        }
    }
}
void block_ctrl(int input_shape, int input_x, int input_y, int input_rotate, int input_state, int input_command)
//input_command : 1. ��(75)   2. ��(77)   3. ��(80)  4.[SPACE]Drop(32)
//                5. ��(72) or [X](120)   6.[Z](122)  7.[C]Hold(99)
{
    int drop_power; // drop ����� �ݺ��� ����

    if (input_command == 1) // ��(75)
    {
        if (input_shape == 1)
        {
            if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 2 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 2 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y + 0][input_x + 0] != 7) && (game_screen[input_y + 0][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 3][input_x + 0] != 7) && (game_screen[input_y + 3][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 3 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 4 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x - 2] != 7) && (game_screen[input_y - 1][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 2] != 7) && (game_screen[input_y + 1][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 5 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7) && (game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 2] != 7) && (game_screen[input_y + 1][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x - 2] != 7) && (game_screen[input_y - 1][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 6 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x - 2] != 7) && (game_screen[input_y - 1][input_x - 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 6 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7) && (game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        //
        else if (input_shape == 7 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 2] != 7) && (game_screen[input_y + 0][input_x - 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
        else if (input_shape == 7 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7) && (game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, -1, 0, input_rotate, input_state);
                x -= 1;
            }
        }
    }

    else if (input_command == 2) // ��(77)
    {
        if (input_shape == 1)
        {
            if ((game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 2 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x + 4] != 7) && (game_screen[input_y + 0][input_x + 4] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 2 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 2] != 7) && (game_screen[input_y + 2][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 3][input_x + 2] != 7) && (game_screen[input_y + 3][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 3 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 3 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 4 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7) && (game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x + 2] != 7) && (game_screen[input_y - 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 4 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 5 && input_rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 2] != 7) && (game_screen[input_y - 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 1)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 2)
        {
            if ((game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 5 && input_rotate == 3)
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 6 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 6 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y - 1][input_x + 2] != 7) && (game_screen[input_y - 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        //
        else if (input_shape == 7 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x + 2] != 7) && (game_screen[input_y - 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
        else if (input_shape == 7 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7) && (game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7) && (game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 1, 0, input_rotate, input_state);
                x += 1;
            }
        }
    }

    else if (input_command == 3) // ��(80)
    {
        if (input_shape == 1)
        {
            if ((game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 2 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 3] != 7) && (game_screen[input_y + 1][input_x + 3] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 2 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y + 4][input_x + 1] != 7) && (game_screen[input_y + 4][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 3 && input_rotate == 0)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 3 && input_rotate == 1)
        {
            if ((game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 3 && input_rotate == 2)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 3 && input_rotate == 3)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 4 && input_rotate == 0)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 4 && input_rotate == 1)
        {
            if ((game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 4 && input_rotate == 2)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 4 && input_rotate == 3)
        {
            if ((game_screen[input_y + 2][input_x - 1] != 7) && (game_screen[input_y + 2][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 5 && input_rotate == 0)
        {
            if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 5 && input_rotate == 1)
        {
            if ((game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 5 && input_rotate == 2)
        {
            if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x - 1] != 7) && (game_screen[input_y + 2][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 5 && input_rotate == 3)
        {
            if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 6 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 6 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        //
        else if (input_shape == 7 && (input_rotate == 0 || input_rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
        else if (input_shape == 7 && (input_rotate == 1 || input_rotate == 3))
        {
            if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
            {
                block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                y += 1;
            }
            else
            {
                input_state++;
                block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                checkCtrl = 0;
            }
        }
    }

    else if (input_command == 4) // Drop : [SPACE](32)
    {
        drop_power = 1;
        while (drop_power)
        {
            if (input_shape == 1)
            {
                if ((game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 2 && (input_rotate == 0 || input_rotate == 2))
            {
                if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 2] != 7) && (game_screen[input_y + 1][input_x + 2] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 3] != 7) && (game_screen[input_y + 1][input_x + 3] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 2 && (input_rotate == 1 || input_rotate == 3))
            {
                if ((game_screen[input_y + 4][input_x + 1] != 7) && (game_screen[input_y + 4][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 3 && input_rotate == 0)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 3 && input_rotate == 1)
            {
                if ((game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 3 && input_rotate == 2)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 3 && input_rotate == 3)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 4 && input_rotate == 0)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 4 && input_rotate == 1)
            {
                if ((game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 4 && input_rotate == 2)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 4 && input_rotate == 3)
            {
                if ((game_screen[input_y + 2][input_x - 1] != 7) && (game_screen[input_y + 2][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 5 && input_rotate == 0)
            {
                if ((game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 5 && input_rotate == 1)
            {
                if ((game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 5 && input_rotate == 2)
            {
                if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x - 1] != 7) && (game_screen[input_y + 2][input_x - 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 5 && input_rotate == 3)
            {
                if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 6 && (input_rotate == 0 || input_rotate == 2))
            {
                if ((game_screen[input_y + 0][input_x - 1] != 7) && (game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 6 && (input_rotate == 1 || input_rotate == 3))
            {
                if ((game_screen[input_y + 1][input_x + 1] != 7) && (game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 0] != 7) && (game_screen[input_y + 2][input_x + 0] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            //
            else if (input_shape == 7 && (input_rotate == 0 || input_rotate == 2))
            {
                if ((game_screen[input_y + 0][input_x + 1] != 7) && (game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 1][input_x - 1] != 7) && (game_screen[input_y + 1][input_x - 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
            else if (input_shape == 7 && (input_rotate == 1 || input_rotate == 3))
            {
                if ((game_screen[input_y + 1][input_x + 0] != 7) && (game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                    (game_screen[input_y + 2][input_x + 1] != 7) && (game_screen[input_y + 2][input_x + 1] % 10 != 2))
                {
                    block(input_shape, input_x, input_y, 0, 1, input_rotate, input_state);
                    input_y += 1;
                    y += 1;
                }
                else
                {
                    input_state++;
                    block(input_shape, input_x, input_y, 0, 0, input_rotate, input_state);
                    drop_power = 0;
                    checkCtrl = 0;
                }
            }
        }
    }

    else if (input_command == 5) // Rotate(Clock) : ��(72) or [x](120)
    {
        if (input_shape == 1)
            rotate++, state += 10;
        //
        else if (input_shape == 2 && (rotate == 0 || rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 2][input_x + 1] != 7 && game_screen[input_y + 2][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 3][input_x + 1] != 7 && game_screen[input_y + 3][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 2 && (rotate == 1 || rotate == 3))
        {
            if (x < 1)
                x = 1, input_x = 1;
            if (x > 7)
                x = 7, input_x = 7;
            if ((game_screen[input_y + 0][input_x + 0] != 7 && game_screen[input_y + 0][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 2] != 7 && game_screen[input_y + 0][input_x + 2] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 3] != 7 && game_screen[input_y + 0][input_x + 3] % 10 != 2))
                rotate++, state += 10;
        }
        //
        else if (input_shape == 3 && rotate == 0)
        {
            if (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2)
                rotate++, state += 10;
        }
        else if (input_shape == 3 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2)
                rotate++, state += 10;
        }
        else if (input_shape == 3 && rotate == 2)
        {
            if (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2)
                rotate++, state += 10;
        }
        else if (input_shape == 3 && rotate == 3)
        {
            if (x > 9)
                x = 9, input_x = 9;
            if (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2)
                rotate++, state += 10;
        }
        //
        else if (input_shape == 4 && rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 4 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 4 && rotate == 2)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 4 && rotate == 3)
        {
            if (x > 9)
                x = 9, input_x = 9;
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        //
        else if (input_shape == 5 && rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 5 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 5 && rotate == 2)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 5 && rotate == 3)
        {
            if (x > 9)
                x = 9, input_x = 9;
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        //
        else if (input_shape == 6 && (rotate == 0 || rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 6 && (rotate == 1 || rotate == 3))
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate++, state += 10;
        }
        //
        else if (input_shape == 7 && (rotate == 0 || rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate++, state += 10;
        }
        else if (input_shape == 7 && (rotate == 1 || rotate == 3))
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2))
                rotate++, state += 10;
        }
        ////
        if (rotate == 4)
            rotate = 0, state -= 40;

        block(input_shape, input_x, input_y, 0, 0, rotate, input_state);
    }

    else if (input_command == 6) // Rotate(CounterClock) : [z](122)
    {
        if (input_shape == 1)
            rotate--, state -= 10;
        //
        else if (input_shape == 2 && (rotate == 0 || rotate == 2))
        {
            if (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2 &&
                game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2 &&
                game_screen[input_y + 2][input_x + 1] != 7 && game_screen[input_y + 2][input_x + 1] % 10 != 2 &&
                game_screen[input_y + 3][input_x + 1] != 7 && game_screen[input_y + 3][input_x + 1] % 10 != 2)
                rotate--, state -= 10;
        }
        else if (input_shape == 2 && (rotate == 1 || rotate == 3))
        {
            if (x < 1)
                x = 1, input_x = 1;
            if (x > 7)
                x = 7, input_x = 7;
            if (game_screen[input_y + 0][input_x + 0] != 7 && game_screen[input_y + 0][input_x + 0] % 10 != 2 &&
                game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2 &&
                game_screen[input_y + 0][input_x + 2] != 7 && game_screen[input_y + 0][input_x + 2] % 10 != 2 &&
                game_screen[input_y + 0][input_x + 3] != 7 && game_screen[input_y + 0][input_x + 3] % 10 != 2)
                rotate--, state -= 10;
        }
        //
        else if (input_shape == 3 && rotate == 0)
        {
            if (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2)
                rotate--, state -= 10;
        }
        else if (input_shape == 3 && rotate == 3)
        {
            if (x >= 9)
                x = 9, input_x = 9;
            if (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2)
                rotate--, state -= 10;
        }
        else if (input_shape == 3 && rotate == 2)
        {
            if (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2)
                rotate--, state -= 10;
        }
        else if (input_shape == 3 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2)
                rotate--, state -= 10;
        }
        //
        else if (input_shape == 4 && rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 4 && rotate == 3)
        {
            if (x > 9)
                x = 9, input_x = 9;
            if ((game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 4 && rotate == 2)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 4 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2))
                rotate--, state -= 10;
        }
        //
        else if (input_shape == 5 && rotate == 0)
        {
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x - 1] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 5 && rotate == 3)
        {
            if (x > 9)
                x = 9, input_x = 9;
            if ((game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 5 && rotate == 2)
        {
            if ((game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y - 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 5 && rotate == 1)
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 0][input_x - 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2))
                rotate--, state -= 10;
        }
        //
        else if (input_shape == 6 && (rotate == 0 || rotate == 2))
        {
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 6 && (rotate == 1 || rotate == 3))
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x - 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y - 1][input_x + 0] != 7 && game_screen[input_y + 1][input_x + 0] % 10 != 2))
                rotate--, state -= 10;
        }
        //
        else if (input_shape == 7 && (rotate == 0 || rotate == 2))
        {
            if ((game_screen[input_y + 0][input_x + 1] != 7 && game_screen[input_y + 0][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 1][input_x + 1] != 7 && game_screen[input_y + 1][input_x + 1] % 10 != 2))
                rotate--, state -= 10;
        }
        else if (input_shape == 7 && (rotate == 1 || rotate == 3))
        {
            if (x < 2)
                x = 2, input_x = 2;
            if ((game_screen[input_y - 1][input_x + 1] != 7 && game_screen[input_y - 1][input_x + 1] % 10 != 2) &&
                (game_screen[input_y + 0][input_x - 1] != 7 && game_screen[input_y + 1][input_x - 1] % 10 != 2))
                rotate--, state -= 10;
        }
        ////
        if (rotate == -1)
            rotate = 3, state += 40;

        block(input_shape, input_x, input_y, 0, 0, rotate, input_state);
    }
}
void print_debug_info()
{
    if (debug == 1)
    {
        gotoxy(1, 27);
        setcolor(8, 0);
        printf("<Debug Mode> shape:%d, x:%2d, y:%2d, rotate:%d, state:%d\nstTC:%5d, ctTC:%5d, delay:%4d, delay_dance:%4d\nstore_hold_ctrl:%d", shape, x, y, rotate, state, startTickCount, currentTickCount, delay, delay_dance, store_hold_ctrl);
        setcolor(7, 0);
    }
}

/********** �Լ� ���� ��!!! **********/
