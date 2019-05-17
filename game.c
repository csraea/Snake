#include <termbox.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include "world.h"
#include "snake.h"

// Start is called one in the beginning
void start(struct world* world,int argc, char** argv){
    // Allocate memory for the state
   // Store pointer to the state to the world variable
    world->state = (struct state*)calloc(1,(sizeof(struct state)));
    world->state->snake = NULL;
    world->state->sx = 0;
    world->state->sy = -1;
    int cy = world->height/2; 
    int cx = world->width/2;

    for(size_t i = 0; i < 2; i++){
        world->state->snake = add_snake(world->state->snake,cx + i ,cy);
    }

    int h = world->height;
    int w = world->width;
    
    for(size_t i = 0; i < FOOD_COUNT; i++){
        world->state->foodx[i] = (rand() % (w-3)+1);
        world->state->foody[i] = (rand() % (h-3)+2); 
    }
}

void draw_borders(struct world *w){
    set_character(w,0,1,'#');
    set_character(w,w->width-1,1,'#');
    set_character(w,w->width-1,w->height-1,'#');
    set_character(w,0,w->height-1,'#');
    for(int i = 2; i < w->height-1; i++){
            set_character(w,0,i,'|');
            set_character(w,w->width-1, i,'|');
    }
    for(int j = 1; j < w->width-1; j++){
            set_character(w,j,1,'-');
            set_character(w,j, w->height-1,'-');
    }
}

int determine_score(struct snake *sn){
    int score = 1;
    while (sn->next != NULL){
        score++;
        sn = sn->next;
    }
    return score - 2;
}

void draw_snake(struct world *w, struct snake *sn){
    if(sn->next->x > sn->x){ /// rozpoznava na zaklade toho kde je ybztok tela ako ma byt natocena hlava
        set_character(w,sn->x,sn->y,'<');
    }
    else if(sn->next->x < sn->x){
        set_character(w,sn->x,sn->y,'>');
    }
    else if(sn->next->y < sn->y){
        set_character(w,sn->x,sn->y,'v');
    } //61184
    else if(sn->next->y > sn->y){
        set_character(w,sn->x,sn->y,'^');
    }
    while ((sn = sn->next) && sn->next != NULL){
        set_character(w,sn->x,sn->y,'x');
    }
    set_character(w,sn->x,sn->y,'+');
}
// Step is called in a loop once in interval.
// It should modify the state and draw it.
int step(struct world* w,int key){
    draw_borders(w);
    // Get state pointer
    struct state* st = w->state;
    
    enum direction dir = DIR_NONE;

    switch (key) {
        case TB_KEY_ARROW_LEFT: 
        dir = DIR_LEFT;
        break;
        case TB_KEY_ARROW_RIGHT:
        dir = DIR_RIGHT;
        break;
        case TB_KEY_ARROW_UP:
        dir = DIR_UP;
        break;
        case TB_KEY_ARROW_DOWN:
        dir = DIR_DOWN;
        break;
    }

    int r = step_state(st,dir,w->width,w->height);
    struct snake* sn = st->snake;

    draw_snake(w, sn);
    int score = determine_score(sn);
    char scoreString[5];
    char scoreWord[10] = {"Score: "};
    sprintf(scoreString, "%d", score);
    strcat(scoreWord, scoreString);
    set_message(w, w->width/2 - strlen(scoreWord)/2, 0, scoreWord);
    for (int i = 0 ; i < FOOD_COUNT; i++){
        if (st->foodx[i] >= 0 && st->foody[i] >= 0){
            set_character(w,st->foodx[i],st->foody[i],'@');
        }
    }
    if (r) set_message(w,20,20,"THE END");
    if (key == TB_KEY_ESC) return 1;
    return 0;
}

// Stop is called after game loop is finished
void stop(struct world* world){
    // Free memory for game state
    struct state* st = world->state;
    free_snake(st->snake);
    free(st);
}
