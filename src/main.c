#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#include <process.h>
#else
#include <pthread.h>
#endif

#include "input.h"
#include "screen.h"
#include "player.h"
#include "food.h"
#include "config.h"

void drawPlayer(Player *player, Screen *screen)
{
    PlayerNode *node;
    for (node = player->tail; node != NULL; node = node->next)
        *screenGetPoint(screen, node->x, node->y) = '#';
}

Food generateFood(Player *player)
{
    Food food;
    do
    {
        food = (Food){rand() % SIZE, rand() % SIZE};
    } while (playerCheckFoodCollision(player, food));
    return food;
}

#ifdef _WIN32
void resetCoordinates(void)
{
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, (COORD){0});
}
#else
void resetCoordinates(void)
{
    printf("\e[1;1H\e[2J");
}
#endif

int main(int argc, char **argv)
{
    srand(time(NULL));
    Player *player = playerCreate(DOWN, DEFX, DEFY, 0);
    Screen *screen = screenCreate(SIZE, SIZE, ' ');
    PlayerNode *node;
    pthread_t input_thread;
    int i;
    int head_x, head_y;
    Food food = generateFood(player);

    bool *running = malloc(sizeof(bool)); *running = true;
    int *key = malloc(sizeof(char)); *key = 0;
    bool stopped = false;
    InputArgs input_args = (InputArgs){ key, running };

#ifdef _WIN32
    _beginthread(input, 0, &input_args);
#else
    pthread_create(&input_thread, NULL, input, &input_args);
#endif
    while (*running)
    {
        screenSet(screen, ' ');
        drawPlayer(player, screen);
        *screenGetPoint(screen, food.x, food.y) = '@';
        resetCoordinates();
        screenShow(screen);
        for (i = 0; i < SIZE*2; ++i) putchar('-');
        printf("\nScore: %d\n", player->score);

#ifdef _WIN32
        Sleep(1000L);
#else
        nanosleep(&(struct timespec){.tv_sec = 1}, NULL);
#endif
        switch (*key)
        {
            case 'q':
                *running = false; return 0;
            case 'p':
                stopped = !stopped; break;
            case 'w':
                if (player->direction == DOWN) break;
                player->direction = UP; break;
            case 'd':
                if (player->direction == LEFT) break;
                player->direction = RIGHT; break;
            case 's':
                if (player->direction == UP) break;
                player->direction = DOWN; break;
            case 'a':
                if (player->direction == RIGHT) break;
                player->direction = LEFT; break;
        } *key = 0;
        if (stopped) continue;

        if (playerDoTick(player, food) && player->score < SIZE*SIZE - 1)
            food = generateFood(player);
        head_x = player->head->x;
        head_y = player->head->y;
        if (head_x >= SIZE || head_x < 0 || head_y >= SIZE || head_y < 0 || playerCheckSelfCollision(player))
        {
            *running = false;
            break;
        }
    }
    return 0;
}
