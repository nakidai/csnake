#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "input.h"
#include "screen.h"
#include "player.h"

void drawPlayer(Player *player, Screen *screen)
{
    PlayerNode *node;
    for (node = player->tail; node != NULL; node = node->next)
        *screenGetPoint(screen, node->x, node->y) = '#';
}

int main(int argc, char **argv)
{
    Player *player = playerCreate(DOWN, 0, 0, 0);
    Screen *screen = screenCreate(10, 10, ' ');
    pthread_t input_thread;

    bool *running = malloc(sizeof(bool)); *running = true;
    char *key = malloc(sizeof(char)); *key = 0;
    InputArgs input_args = (InputArgs){ key, running };

    pthread_create(&input_thread, NULL, input, &input_args);
    while (*running)
    {
        if (*key == 'q') *running = false;
    }
    return 0;
}
