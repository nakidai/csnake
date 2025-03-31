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
#include "sleep.h"
#include "platform/screen.h"
#include "platform/game.h"

void drawPlayer(Player player, Screen screen)
{
    PlayerNode *node;
    for (node = player.tail; node != NULL; node = node->next)
        *screenGetPoint(screen, node->x, node->y) = '#';
}

Food generateFood(Player player)
{
    Food food;
    do
    {
        food = (Food){rand() % FIELD_SIZE, rand() % FIELD_SIZE};
    } while (playerCheckFoodCollision(player, food));
    return food;
}

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));
    platformGameInit();

    Player player; playerCreate(&player, DOWN, DEFX, DEFY, 0);
    Screen screen; screenCreate(&screen, FIELD_SIZE, FIELD_SIZE, ' ');
    Food   food =  generateFood(player);

    int  key = 0;
    bool running = true;
    bool stopped = false;
    int  head_x, head_y;

    thrd_t inputthread;
    thrd_create(&inputthread, input, &(InputArgs){ &key, &running });
    while (running)
    {
        screenSet(screen, ' ');
        drawPlayer(player, screen);
        *screenGetPoint(screen, food.x, food.y) = '@';

        resetCoordinates();
        screenShow(screen);
        for (int i = 0; i < FIELD_SIZE*2; ++i) putchar('-');
        printf("\nScore: %d\n", player.score);

        sleepMS(SLEEP);

        switch (key)
        {
            case 'q':
                running = false; return 0;
            case 'p':
                stopped = !stopped; break;
            case 'w':
                if (player.direction == DOWN) break;
                player.direction = UP; break;
            case 'd':
                if (player.direction == LEFT) break;
                player.direction = RIGHT; break;
            case 's':
                if (player.direction == UP) break;
                player.direction = DOWN; break;
            case 'a':
                if (player.direction == RIGHT) break;
                player.direction = LEFT; break;
        } key = 0;
        if (stopped) continue;

        if (playerDoTick(&player, food) && player.score < FIELD_SIZE*FIELD_SIZE - 1)
            food = generateFood(player);

        head_x = player.head->x;
        head_y = player.head->y;
        if (head_x >= FIELD_SIZE || head_x < 0 || head_y >= FIELD_SIZE || head_y < 0 || playerCheckSelfCollision(player))
        {
            running = false;
            break;
        }
    }
    return 0;
}
