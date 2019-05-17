#ifndef snake_h_INCLUDED
#define snake_h_INCLUDED


// Number of food items on the plane
#define FOOD_COUNT 4

/**
 * One part of the snake;
 * 
 * The snake is a linked list;
 */
 
struct snake {
    // x position of the snake part
    int x;
    // y position of the snake part
    int y;
    // Pointer to the next snake part.
    // The last part of the snake has NULL pointer to the next part.
    struct snake* next;
};

/**
 * Direction of the snake
 */
 
enum direction {
    // No direction command was given
    DIR_NONE,
    // Up arrow, direction to north
    DIR_UP,
    // Down arrow, direction to south
    DIR_DOWN,
    // Left arow, direction to west
    DIR_LEFT,
    // Right arrow, direction east.
	DIR_RIGHT
};

enum endgame {
    // Continue the game
    END_CONTINUE = 0,
    // Snake hit a wall
    END_WALL,
    // Snake hit itself
    END_SNAKE,
    // No food left
    END_FOOD,
    // Other reason to end
    END_USER
};

/**
 * State of the game.
 * 
 * The state consists of the snake, its speed and food on the plane.
 * 
 * The snake is a linked list of snake parts.
 * 
 * Speed vector is a vector added to the last head position to create a new head.
 * 
 * Food are points on the plane. Food with negative coordinates meads food is already eaten.
 */
 
struct state {
    // Snake as a linked list
    struct snake* snake;
    // X of the speed vector
    int sx;
    // Y of the speed vector
    int sy;
    // X of the food positions
    int foodx[FOOD_COUNT];
    // Y of the food positions
    int foody[FOOD_COUNT];
};

/**
 * Add a new snake part with given position. The new snake part becomes the new head.
 * @param head of the snake.
 * @param x coordinate of the new head;
 * @param y coordinate of the new head.
 * @return new head of the snake.
 */
struct snake* add_snake(struct snake* snake,int x,int y);
/**
 * Remove the last snake part.
 * The last snake part  should always have NULL next pointer.
 * @param head of the snake.
 * @return new head of the snake.
 */
struct snake* remove_snake(struct snake* snake);
/**
 * Remove each snake part;
 * @param head of the snake.
 */
void free_snake(struct snake* sn);
/**
 * Change game state.
 * 
 * The function should first set the speed vector according to the direction.
 * If direction is:
 * - DIR_NONE, speed vector does not change
 * - DIR_UP, speed vector is  0,-1
 * - DIR_DOWN, speed vector is  0,1
 * - DIR_LEFT, speed vector is -1, 0
 * - DIR_RIGHT, speed vector is 1, 0
 * 
 * Then it calculates the new position of the head according to the old position 
 * of the snake head and the speed vector.
 * 
 * - If the new position is on the snake, end the game, return END_SNAKE.
 * - If the new position is on the plane, add new snake part on the new position and remove the last part of the snake, return END_CONTINUE.
 * - If the new position is on the food, mark food as eaten and add new snake part on the position of the food. Return END_CONTINUE.
 * - If there is no food left, end the game, return END_FOOD.
 * 
 * @param old state of the game.
 * @param direction command, one of "enum direction".
 * @param width of the plane.
 * @param height of the plane.
 * @return reason to end the game according to enum endgame.
 */
int step_state(struct state* state,enum direction dir,int width,int height);


#endif // snake_h_INCLUDED

