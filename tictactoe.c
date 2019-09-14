#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/*-------------------------------------------------*/
#define GRID_COLS 3


/*-------------------------------------------------*/
typedef struct _optional_t {
    bool valid;
    int num;
} optional_t;


/*-------------------------------------------------*/
typedef enum _difficult_t {
    EASY,
    NORMAL,
    HARD
} difficult_t;


/*-------------------------------------------------*/
static int lives;
static difficult_t difficult;
static char grid[3][3];


/*-------------------------------------------------*/
static inline void clear_screen(void);
static inline void wait_key(void);
static inline optional_t read_int(const char* msg);
static void intro_screen(void);
static void ask_grid_position(void);
static void draw_grid(void);
static void settings_screen(void);
static inline bool check_option(int o, int a, int b);
static inline optional_t func_result(int num, bool valid);


/*-------------------------------------------------*/
static void intro_screen() {
    while (true) {
        clear_screen();
        printf("TIC-TAC-TOE\n\n");
        printf("1 - Start Game\n");
        printf("2 - Settings\n");
        printf("3 - Quit\n\n");

        optional_t r = read_int(">> ");
        if (!r.valid) continue;
        if (!check_option(r.num, 1, 3))
            continue;

        switch (r.num) {
            case 1: break;
            case 2: settings_screen();
            case 3: return;
        }
    }
}


/*-------------------------------------------------*/
static void ask_grid_position() {
    while (true) {
        draw_grid();
        optional_t r = read_int("\n\nEnter position: ");
        if (!r.valid) continue;
        if (!check_option(r.num, 1, 3))
            continue;
    }
}


/*-------------------------------------------------*/
static void draw_grid() {
    printf("-------------------------\n");
    printf("|%c|%c|%c|\n", grid[0][0], grid[0][1], grid[0][2]);
    printf("|%c|%c|%c|\n", grid[1][0], grid[1][1], grid[1][2]);
    printf("|%c|%c|%c|\n", grid[2][0], grid[2][1], grid[2][2]);
    printf("-------------------------");

}


/*-------------------------------------------------*/
static void settings_screen() {
    while (true) {
        clear_screen();
        printf("Settings\n\n");
        printf("1 - Set credits\n");
        printf("2 - Difficult\n");
        printf("3 - Back\n\n");

        optional_t r = read_int(">> ");
        if (!r.valid) continue;
        if (!check_option(r.num, 1, 3))
            continue;

        switch (r.num) {
            case 1: break;
            case 2: break;
            case 3: intro_screen();
        }
    }
}


/*-------------------------------------------------*/
static inline bool check_option(int o, int a, int b) {
    if (o < a || o > b) {
        printf(">> Invalid option!!");
        wait_key();
        return false;}
    return true;
}


/*-------------------------------------------------*/
static inline optional_t func_result(int num, bool valid) {
    optional_t op;
    op.num = num;
    op.valid = valid;
    return op;
}


/*-------------------------------------------------*/
static inline void clear_screen() {
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


/*-------------------------------------------------*/
static inline void wait_key() {
    fflush(stdin);
    getchar();
}


/*-------------------------------------------------*/
static inline optional_t read_int(const char* msg) {
    if (msg != NULL)
        printf("%s", msg);
    int num;
    if (scanf(" %d", &num) != 1) {
        printf(">> Invalid input!");
        wait_key();
        return func_result(-1, false);}
    return func_result(num, true);
}


/*-------------------------------------------------*/
int main() {
    intro_screen();
    return 0;
}
