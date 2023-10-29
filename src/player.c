#include "player.h"
#include <stdlib.h>

Player *playerCreate(Direction direction, int x, int y, int score)
{
    Player *player = (Player *)malloc(sizeof(Player));
    PlayerNode *head = (PlayerNode *)malloc(sizeof(PlayerNode));

    player->tail = head;
    player->head = head;
    player->score = score;
    player->direction = direction;

    head->x = x;
    head->y = y;
    head->next = NULL;
}

void playerFree(Player *player)
{
}

void playerDoTick(Player *player, bool food_collision)
{
    PlayerNode *new_head = (PlayerNode *)malloc(sizeof(PlayerNode));
    int head_x = player->head->x;
    int head_y = player->head->y;
    
    switch(player->direction)
    {
        case UP:
            new_head->x = head_x;
            new_head->y = head_y - 1;
            break;
        case DOWN:
            new_head->x = head_x;
            new_head->y = head_y + 1;
            break;
        case LEFT:
            new_head->x = head_x - 1;
            new_head->y = head_y;
            break;
        case RIGHT:
            new_head->x = head_x + 1;
            new_head->y = head_y;
            break;
    }

    player->head->next = new_head;
    player->head = new_head;

    if (!food_collision)
    {
        PlayerNode *new_tail = player->tail->next;
        free(player->tail);
        player->tail = new_tail;
    }
}
