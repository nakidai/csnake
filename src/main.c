#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "input.h"
#include "screen.h"
#include "player.h"
#include "food.h"

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
        food = (Food){random() % 10, random() % 10};
    } while (playerCheckFoodCollision(player, food));
    return food;
}

int main(int argc, char **argv)
{
    srandom(time(NULL));
    Player *player = playerCreate(DOWN, 0, 0, 0);
    Screen *screen = screenCreate(10, 10, ' ');
    PlayerNode *node;
    pthread_t input_thread;
    int head_x, head_y;
    Food food = generateFood(player);

    bool *running = malloc(sizeof(bool)); *running = true;
    char *key = malloc(sizeof(char)); *key = 0;
    InputArgs input_args = (InputArgs){ key, running };

    pthread_create(&input_thread, NULL, input, &input_args);
    while (*running)
    {
        switch (*key)
        {
            case 'q':
                *running = false; return 0;
            case 'w':
                player->direction = UP; break;
            case 'd':
                player->direction = RIGHT; break;
            case 's':
                player->direction = DOWN; break;
            case 'a':
                player->direction = LEFT; break;
            sleep(1);
        }

        if (playerDoTick(player, food))
            food = generateFood(player);
        if (playerCheckSelfCollision(player))
        {
            *running = false;
            break;
        }
        head_x = player->head->x;
        head_y = player->head->y;
        if (head_x >= 10 || head_x < 0 || head_y >= 10 || head_y < 0)
        {
            *running = false;
            break;
        }

        screenSet(screen, ' ');
        drawPlayer(player, screen);
        *screenGetPoint(screen, food.x, food.y) = '@';
        screenShow(screen);

        sleep(1);
    }
    return 0;
}
