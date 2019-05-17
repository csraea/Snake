 #include "snake.h"
#include <stdlib.h>
#include <stdio.h>

struct snake* add_snake(struct snake* snake,int x,int y){
	struct snake* newHead = malloc(sizeof(struct snake));
	newHead->x = x;
	newHead->y = y;
	newHead->next = snake;
    return newHead;
}

struct snake* remove_snake(struct snake* snake){
	struct snake *ptr = snake;
	if(snake == NULL) return NULL;
	if(snake->next == NULL) return NULL;
	while(ptr->next->next != NULL) ptr = ptr->next;
	free(ptr->next);
	ptr->next = NULL;
	return snake;
}

void free_snake(struct snake* sn){
	if(sn == NULL) // zase ak by bol hlupy vstup vypise chybu
		return;
	if(sn->next != NULL) // pokial nie je na konci zase vola tutuo funkciu ale pointer je na dalsi clanok.. sa to tu za zacykli .. sa had zacne vymazavat od posledneho clanku.. 
		free_snake(sn->next);
	free(sn); 
	return;
}

int step_state(struct state* st,enum direction dir,int width,int height){  	//	if(direction == DIR_NONE){				
	struct snake *rem = st->snake->next;
	struct snake *snake = st->snake; // len si ulozis st->snake do premennej nech dlhe nemusis pisat :D
	int eaten = 0; // jedlo ktore uz zjdeol.. hra skonci ked sa bude eaten==foodcount

	if(snake->x < 0 || snake->y < 0 || snake->x > width || snake->y > height){ // error pri hlupom vstupe.. ak by sa had nachadzal za stenou pri starte hry
        return END_WALL;
	}
	switch(dir){ // podmienky podla toho kam ma smerovat had, to asi chapes
		case DIR_NONE:
			break;
		case DIR_DOWN:
			st->sx = 0;
            st->sy = 1;
			break;
		case DIR_UP:
			st->sx = 0;
            st->sy = -1;
			break;
		case DIR_LEFT:
			st->sx = -1;
            st->sy = 0;
			break;
		case DIR_RIGHT:
			st->sx = 1;
            st->sy = 0;
			break;
	}
	while(rem != NULL){
		if(((snake->x + st->sx) == rem->x && rem != snake->next) && ((snake->y + st->sy) == rem->y && rem != snake->next)){ 
			return END_SNAKE;
		}
		rem = rem->next; 
	}
	for(int j = 0; j < FOOD_COUNT; j++){ //testujes na novej pozici kde sa bude hlava nachadzat nie je aj jedlo
		if(st->foodx[j] < 0 && st->foody[j] < 0) eaten++;
	}
	for(int j = 0; j < FOOD_COUNT; j++){ //testujes na novej pozici kde sa bude hlava nachadzat nie je aj jedlo
		if((snake->x + st->sx) == st->foodx[j] && (snake->y + st->sy) == st->foody[j] && eaten == FOOD_COUNT-1){
			for(size_t i = 0; i < rand() % FOOD_COUNT+1; i++){
				st->foodx[i] = (rand() % (width-3)+1);
        		st->foody[i] = (rand() % (height-3)+2);
			} 
			st->snake = add_snake(snake, (snake->x + st->sx), (snake->y + st->sy));
			return END_CONTINUE;
		} else if((snake->x + st->sx) == st->foodx[j] && (snake->y + st->sy) == st->foody[j]){
			st->foodx[j] *= -1;
        	st->foody[j] *= -1;
			st->snake = add_snake(snake, (snake->x + st->sx), (snake->y + st->sy));
			return END_CONTINUE;
		}
	}
	if((snake->x + st->sx) > 0 && (snake->y + st->sy) > 1 && (snake->x + st->sx) <= width-2 && (snake->y + st->sy) <= height-2){// nakoniec ak nova pozicia hlavy nie je na nicom zaujimavom tak sa had jednopducho posunie po hracej ploche
        st->snake = add_snake(snake, (snake->x + st->sx), (snake->y + st->sy)); //vytvori sa nova hlava
        remove_snake(snake); // posledny clanok sa odoberie a vyzera ze sa had posunul
        return END_CONTINUE;
    }
	else return END_WALL;

}