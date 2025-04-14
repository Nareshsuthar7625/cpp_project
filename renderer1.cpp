inline int clamp(int min,int val,int max){
    if(val>max) return max;
    if(val<min) return min;
    return val;
}

static void draw_rect_in_pixels(int x0,int y0, int x1,int y1,unsigned int color ){
    
    x0 = clamp(0,x0,render_state.width);
    y0 = clamp(0,y0,render_state.height);
    x1 = clamp(0,x1,render_state.width);
    y1 = clamp(0,y1,render_state.height);
    
    for(int y = y0; y<y1;y++){
            unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y*render_state.width;
            for(int x = x0;x<x1;x++){
                *pixel++ = color;
            }
        }
}

static float render_scale = 0.01f;

static void draw_rect(float x,float y,float half_size_x,float half_size_y,unsigned int color){
    
    x *= render_state.height*render_scale;
    y *= render_state.height*render_scale;
    half_size_x *= render_state.height*render_scale;
    half_size_y *= render_state.height*render_scale;

    x += render_state.width/2.f;
    y += render_state.height/2.f;

    //change to pixels
    int x0 = x - half_size_x;
    int x1 = x + half_size_x;
    int y0 = y - half_size_y;
    int y1 = y + half_size_y;

    draw_rect_in_pixels(x0,y0,x1,y1,color);
}

draw_ship(float x,float y,float half_size_x,float half_size_y,unsigned int color){
    draw_rect(x,y,half_size_x,half_size_y,color);//main and wing
    draw_rect(x - 10, y, half_size_x / 2, half_size_y / 2, color);//tail
    draw_rect(x - 1, y, half_size_x * 3, half_size_y / 6, 0x0000ff);//body
}

draw_etp(float x, float y, float size, unsigned int color){
    float half_size = size * .5f;
    //T
    draw_rect(x - 13, y + size * 2.f, half_size * 3.f, half_size, color);
    draw_rect(x - 13, y, half_size, 2.5f * size, color);
    //O
    draw_rect(x - size - 6, y, half_size, 2.5f * size, color);
    draw_rect(x + size - 6, y, half_size, 2.5f * size, color);
    draw_rect(x - 6, y + size * 2.f, half_size, half_size, color);
    draw_rect(x - 6, y - size * 2.f, half_size, half_size, color);
    //p
    draw_rect(x + size * 1.5f, y, half_size, 2.5f * size, color);
    draw_rect(x + size * 2.5f, y, 1.5f * size, half_size,color);
    draw_rect(x + size * 2.5f, y + size * 2.f,1.5f * size, half_size,color);
    draw_rect(x + size * 3.5f, y + size, half_size, half_size,color);
    //L
    draw_rect(x - size + 12, y, half_size, 2.5f * size, color);
    draw_rect(x + 12, y - size * 2.f, half_size, half_size, color);
    //A
    draw_rect(x - size + 17, y, half_size, 2.5f * size, color);
    draw_rect(x + size + 17, y, half_size, 2.5f * size, color);
    draw_rect(x + 17, y + size * 2.f, half_size, half_size, color);
    draw_rect(x + 17, y - size * 2.f + 3, half_size, half_size, color);
    //y
    draw_rect(x + size * 2.5f + 20, y, 1.5f * size, half_size,color);
    draw_rect(x + size * 3.5f + 20, y + size, half_size, half_size * 2.75f,color);
    draw_rect(x + size * 3.5f + 16, y + size, half_size, half_size * 2.75f,color);
    draw_rect(x + size * 3.5f + 18, y - 2, half_size, half_size * 2.75f,color);
    //enter
    draw_rect(x - size - 20, y, half_size, 2.5f * size, color);
    draw_rect(x - 25, y - size * 2.f, half_size * 4.f, half_size, color);
    draw_rect(x - size - 25, y - size * 2.f, half_size, half_size * 2.f, color);

}

static void draw_number(int number, float x, float y, float size, unsigned int color){
    float half_size = size * .5f;

    bool drew_number = false;
    while (number || !drew_number){

        drew_number = true;
        int digit = number % 10;
        number = number / 10;

        switch(digit){
            case 0:{
            draw_rect(x - size, y, half_size, 2.5f * size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x, y + size * 2.f, half_size, half_size, color);
            draw_rect(x, y - size * 2.f, half_size, half_size, color);
            x -= size * 4.f;
            }break;

            case 1:{
            draw_rect(x + size, y, half_size, 2.5f * size,color);
            x -= size * 2.f;
            }break;

            case 2:{
            draw_rect(x , y + size * 2.f,1.5f * size, half_size,color);
            draw_rect(x , y, 1.5f * size, half_size,color);
            draw_rect(x , y - size * 2.f, 1.5f * size, half_size,color);
            draw_rect(x + size, y + size, half_size, half_size,color);
            draw_rect(x - size, y - size, half_size, half_size,color);
            x -= size * 4.f;
            }break;

            case 3:{
            draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
            draw_rect(x - half_size, y, size, half_size, color);
            draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            x -= size * 4.f;
            }break;

            case 4:{
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x - size, y + size, half_size, 1.5f * size, color);
            draw_rect(x, y, half_size, half_size, color);
            x -= size * 4.f;
            }break;

            case 5:{
            draw_rect(x , y + size * 2.f,1.5f * size, half_size,color);
            draw_rect(x , y, 1.5f * size, half_size,color);
            draw_rect(x , y - size * 2.f, 1.5f * size, half_size,color);
            draw_rect(x - size, y + size, half_size, half_size,color);
            draw_rect(x + size, y - size, half_size, half_size,color);
            x -= size * 4.f;
            }break;

            case 6:{
            draw_rect(x + half_size, y + size * 2.f, size, half_size,color);
            draw_rect(x + half_size, y, size, half_size,color);
            draw_rect(x + half_size, y - size * 2.f, size, half_size,color);
            draw_rect(x - size, y, half_size, 2.5f * size,color);
            draw_rect(x + size, y - size, half_size, half_size,color);
            x -= size * 4.f;
            }break;

            case 7:{
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x - half_size, y + size * 2.f, size, half_size,color);
            x -= size * 4.f;
            }break;

            case 8:{
            draw_rect(x - size, y, half_size, 2.5f * size, color);
            draw_rect(x + size, y, half_size, 2.5f * size, color);
            draw_rect(x , y + size * 2.f, half_size, half_size,color);
            draw_rect(x , y - size * 2.f, half_size, half_size,color);
            draw_rect(x , y, half_size, half_size,color);
            x -= size * 4.f;
            }break;

            case 9:{
            draw_rect(x - half_size, y + size * 2.f, size, half_size,color);
            draw_rect(x - half_size, y, size, half_size,color);
            draw_rect(x - half_size, y - size * 2.f, size, half_size,color);
            draw_rect(x + size, y, half_size, 2.5f * size,color);
            draw_rect(x - size, y + size, half_size, half_size,color);
            x -= size * 4.f;
            }break;
    }

    }
}