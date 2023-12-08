#include <stdlib.h>

#include "player.h"

void playerCreate(Player *buffer, Direction direction, int x, int y, int score)
{
    PlayerNode *head = (PlayerNode *)malloc(sizeof(PlayerNode));

    head->x = x;
    head->y = y;
    head->next = NULL;

    buffer->tail = head;
    buffer->head = head;
    buffer->score = score;
    buffer->direction = direction;
}

bool playerCheckFoodCollision(Player player, Food food)
{
    for (PlayerNode *node = player.tail; node != NULL; node = node->next)
        if (node->x == food.x && node->y == food.y)
            return true;
    return false;
}

bool playerCheckSelfCollision(Player player)
{
    PlayerNode *nodei, *nodej;
    for (nodei = player.tail; nodei != NULL; nodei = nodei->next)
        for (nodej = nodei->next; nodej != NULL; nodej = nodej->next)
            if (nodei->x == nodej->x && nodei->y == nodej->y)
                return true;
    return false;
}

bool playerDoTick(Player *player, Food food)
{
    bool food_collision;
    PlayerNode *new_head = (PlayerNode *)malloc(sizeof(PlayerNode));
    new_head->next = NULL;
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

    food_collision = (new_head->x == food.x && new_head->y == food.y);
    if (food_collision)
    {
        ++player->score;
    } else
    {
        PlayerNode *new_tail = player->tail->next;
        free(player->tail);
        player->tail = new_tail;
    }
    return food_collision;
}
