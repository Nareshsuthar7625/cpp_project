#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

#include <cstdlib>
#include <ctime>
using namespace std;


float ship_p, ship_dp;
float arena_half_size_x = 100;
float arena_half_size_y = 50;
float ship_half_size_x = 2.5, ship_half_size_y = 10;
float rock_p_x = 100, rock_p_y, rock_p_x0 = 100, rock_p_y0, rock_p_x1 = 100, rock_p_y1, rock_p_x2 = 100, rock_p_y2, rock_p_x3 = 100, rock_p_y3;
float rock_dp_x = -100, rock_dp_x0 = - 130, rock_dp_x1 = -90, rock_dp_x2 = -80, rock_dp_x3 = -70, rock_half_size = 5; 


int ship_score;

int random_num(int low, int high) {
    int r = rand() % (high - low + 1) + low;
    return r;
}

static void simulate_ship(float *p , float *dp ,float ddp,float dt){
    ddp -= *dp * 10.f;
    *p = *p + *dp * dt + ddp * dt * dt * .5f;
    *dp = *dp + ddp * dt;

    if(*p + ship_half_size_y > arena_half_size_y){
        *p = arena_half_size_y - ship_half_size_y;
        *dp = 0;
    } else if(*p - ship_half_size_y < -arena_half_size_y){
        *p = -arena_half_size_y + ship_half_size_y;
        *dp = 0;
    }
}


bool collision(float x,float y){
    return (x + rock_half_size > -80 - ship_half_size_x &&
    x - rock_half_size < -80 + ship_half_size_x &&
    y + rock_half_size > ship_p - ship_half_size_y &&
    y - rock_half_size < ship_p + ship_half_size_y);
}

bool game_over = true;

void rock_collide(float x,float y){
    if(collision(x,y)){
        game_over = true;
        }
}

static void simulate_game(Input *input,float dt){
    
if(!game_over){
    draw_rect(0,0,arena_half_size_x,arena_half_size_y,0x0000e);

    float ship_ddp = 0.f; // units per seconds
    if(is_down(BUTTON_UP)) ship_ddp += 2000;
    if(is_down(BUTTON_DOWN)) ship_ddp -= 2000;

    
    
    simulate_ship(&ship_p, &ship_dp, ship_ddp, dt);

    //simulate rock
    rock_p_x += rock_dp_x * dt;
    rock_p_x0 += rock_dp_x0 * dt;
    rock_p_x1 += rock_dp_x1 * dt;
    rock_p_x2 += rock_dp_x2 * dt;
    rock_p_x3 += rock_dp_x3 * dt;

    rock_collide(rock_p_x,rock_p_y);
    rock_collide(rock_p_x0,rock_p_y0);
    rock_collide(rock_p_x1,rock_p_y1);
    rock_collide(rock_p_x2,rock_p_y2);
    rock_collide(rock_p_x3,rock_p_y3);

    
    if(rock_p_x - rock_half_size < -arena_half_size_x - 10){
        rock_p_y = random_num(-50,50);
        rock_p_x = 100;
        ship_score++;
        }
    if(rock_p_x0 - rock_half_size < -arena_half_size_x - 10){
        rock_p_y0 = random_num(-50,50);
        rock_p_x0 = 100;
        ship_score++;
        }
    if(rock_p_x1 - rock_half_size < -arena_half_size_x - 10){
            rock_p_y1 = random_num(-50,50);
            rock_p_x1 = 100;
            ship_score++;
        }
    if(rock_p_x2 - rock_half_size < -arena_half_size_x - 10){
            rock_p_y2 = random_num(-50,50);
            rock_p_x2 = 100;
            ship_score++;
        }
    if(rock_p_x3 - rock_half_size < -arena_half_size_x - 10){
            rock_p_y3 = random_num(-50,50);
            rock_p_x3 = 100;
            ship_score++;
        }

    draw_number(ship_score, 70, 45, 1.f, 0x00ffff);


    //rendering
    draw_rect(rock_p_x,rock_p_y,5,5,0xffffff);//rock 
    draw_rect(rock_p_x0,rock_p_y0,5,5,0xffffff);//rock 0
    draw_rect(rock_p_x1,rock_p_y1,5,5,0xffffff);//rock 1 
    draw_rect(rock_p_x2,rock_p_y2,5,5,0xffffff);//rock 2
    draw_rect(rock_p_x3,rock_p_y3,5,5,0xffffff);//rock 3
    draw_ship(-80,ship_p,2.5,10,0xff0000); //ship
    }
    else{
        draw_rect(0,0,arena_half_size_x,arena_half_size_y,0x0000e);
        if(ship_score != 0){draw_number(ship_score, 0, 20, 5.f, 0x00ffff);
        }
        draw_etp(0,-10,2,0xff0000);
        if (pressed(BUTTON_ENTER)) {
            game_over = !game_over;
            ship_score = 0;
        
            ship_p = 0;
            ship_dp = 0;
        
            rock_p_x = 100; rock_p_y = 0;
            rock_p_x0 = 100; rock_p_y0 = 0;
            rock_p_x1 = 100; rock_p_y1 = 0;
            rock_p_x2 = 100; rock_p_y2 = 0;
            rock_p_x3 = 100; rock_p_y3 = 0;
        
            rock_dp_x = -100; rock_dp_x0 = -130; rock_dp_x1 = -90; rock_dp_x2 = -80; rock_dp_x3 = -70;
        }
    }
}
    


