#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <stdbool.h>
#include "food.h"

typedef enum { UP, RIGHT, DOWN, LEFT} Direction;
typedef struct player_node_t PlayerNode;
typedef struct player_t Player;

struct player_node_t
{
    int x, y;
    PlayerNode *next;
};

struct player_t
{
    PlayerNode *tail, *head;
    Direction direction;
    int score;
};

Player *playerCreate(Direction direction, int x, int y, int score);
void playerFree(Player *player);

bool playerCheckSelfCollision(Player *player);
bool playerCheckFoodCollision(Player *player, Food food);
bool playerDoTick(Player *player, Food food);

#endif /* __PLAYER_H__ */
