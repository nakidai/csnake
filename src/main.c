#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <time.h>

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

void resetCoordinates(void)
{
    printf("\e[1;1H\e[2J");
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    Player *player = playerCreate(DOWN, DEFX, DEFY, 0);
    Screen *screen = screenCreate(SIZE, SIZE, ' ');
    PlayerNode *node;
    thrd_t input_thread;
    int i;
    int head_x, head_y;
    Food food = generateFood(player);

    bool *running = malloc(sizeof(bool)); *running = true;
    char *key = malloc(sizeof(char)); *key = 0;
    InputArgs input_args = (InputArgs){ key, running };

    thrd_create(&input_thread, input, &input_args);
    while (*running)
    {
        switch (*key)
        {
            case 'q':
                *running = false; return 0;
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
        }

        if (playerDoTick(player, food) && player->score >= SIZE*SIZE - 1)
            food = generateFood(player);
        head_x = player->head->x;
        head_y = player->head->y;
        if (head_x >= SIZE || head_x < 0 || head_y >= SIZE || head_y < 0 || playerCheckSelfCollision(player))
        {
            *running = false;
            break;
        }

        screenSet(screen, ' ');
        drawPlayer(player, screen);
        *screenGetPoint(screen, food.x, food.y) = '@';
        resetCoordinates();
        screenShow(screen);
        for (i = 0; i < SIZE*2; ++i) putchar('-');
        printf("\nScore: %d\n", player->score);

        thrd_sleep(&(struct timespec){.tv_sec=1}, NULL);
    }
    return 0;
}
