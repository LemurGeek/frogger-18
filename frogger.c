#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture *inicializar_textura_de_archivo(const char* file_name, SDL_Renderer *render); // Pepe
//SDL_Texture *inicializar_texto(const char *fuente, const int tama, SDL_Renderer *render, char *mensaje, SDL_Color *color);
static const int width = 800;
static const int height = 700;

int main(int argc, char **argv)
{
    // Inicia el SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Crea una ventana SDL
    SDL_Window *window = SDL_CreateWindow("Frogger/L18", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,height, SDL_WINDOW_OPENGL); //Ventana

    // Crea un renderer
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //Render

    // COLOR
    SDL_SetRenderDrawColor(render, 39, 64, 139, 0);

    // Inicializar los textos.
    TTF_Init();
    TTF_Font *fuente_berk = TTF_OpenFont("assets/kkberkbm.ttf", 24);
    TTF_Font *fuente_berkG = TTF_OpenFont("assets/kkberkbm.ttf", 62);
    SDL_Color color = {25, 208, 200};
    SDL_Color color2 = {245, 172, 0};
    SDL_Color color3 = {245, 68 , 102};
    SDL_Color color4 = {68, 245, 102};

    // Pausa
    SDL_Surface *textsurface_pausa = TTF_RenderText_Solid(fuente_berkG, "PAUSA", color2);
    SDL_Texture *text_pausa = SDL_CreateTextureFromSurface(render, textsurface_pausa);
    SDL_Rect pos_pausa;
    pos_pausa.x = 1000;//(width/3);
    pos_pausa.y = 1000;//(height/3);
    SDL_QueryTexture(text_pausa, NULL, NULL, &pos_pausa.w, &pos_pausa.h);
    //
    // Perder
    SDL_Surface *textsurface_perder = TTF_RenderText_Solid(fuente_berkG, "PERDISTE", color3);
    SDL_Texture *text_perder = SDL_CreateTextureFromSurface(render, textsurface_perder);
    SDL_Rect pos_perder;
    pos_perder.x = 1000;//(width/3);
    pos_perder.y = 1000;//(height/3);
    SDL_QueryTexture(text_perder, NULL, NULL, &pos_perder.w, &pos_perder.h);

    // Ganar
    SDL_Surface *textsurface_ganar = TTF_RenderText_Solid(fuente_berkG, "GANASTE", color4);
    SDL_Texture *text_ganar = SDL_CreateTextureFromSurface(render, textsurface_ganar);
    SDL_Rect pos_ganar;
    pos_ganar.x = 1000;//(width/3);
    pos_ganar.y = 1000;//(height/3);
    SDL_QueryTexture(text_ganar, NULL, NULL, &pos_ganar.w, &pos_ganar.h);


    //SDL_BlitSurface(message, NULL, window, NULL);

    // Inicializar las imagenes PNG Y JPEG.
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Texture *image_texture = inicializar_textura_de_archivo("assets/frog.png", render);
    SDL_Texture *fondo = inicializar_textura_de_archivo("assets/fondo.png", render);
    SDL_Texture *menu = inicializar_textura_de_archivo("assets/menu.png", render);
    SDL_Texture *carro_rojo = inicializar_textura_de_archivo("assets/carrorojo.png", render);
    SDL_Texture *camion = inicializar_textura_de_archivo("assets/camion.png", render);
    SDL_Texture *carro_rapido = inicializar_textura_de_archivo("assets/rapido.png", render);
    SDL_Texture *tronco = inicializar_textura_de_archivo("assets/tronco.png", render);
    SDL_Texture *vidas = inicializar_textura_de_archivo("assets/pepe.png", render);
    SDL_Texture *tiempo = inicializar_textura_de_archivo("assets/time.png", render);
    SDL_Texture *agua = inicializar_textura_de_archivo("assets/agua.png", render);

    int image_width, image_height;
    int tiempo_contador = 1600;
    // Obtener textura width/height
    SDL_QueryTexture(fondo, NULL, NULL, &image_width, &image_height);

    // Definir donde estará la imagen de Pepe xD
    SDL_Rect posicion_pepe;
    posicion_pepe.x = 370;
    posicion_pepe.y = 550;
    posicion_pepe.w = 50; //image_width;
    posicion_pepe.h = 50; //image_height;

    //POsicion fondo
    SDL_Rect posicion_fondo = {0,0,image_width, image_height};
    SDL_Rect posicion_menu = {0,0, image_width, 700};
    //SDL_Rect posicion_pausa = {0, -5000, image_width, 700};

    //POsicion tiempo y vidas y agua
    SDL_Rect posicion_vida1 = {750, 600, 50, 50};
    SDL_Rect posicion_vida2 = {700, 600, 50, 50};
    SDL_Rect posicion_vida3 = {650, 600, 50, 50};
    SDL_Rect posicion_tiempo = {-75, 600, tiempo_contador, 50}; // 0 600 1600 50

    //Posicion Agua top
    SDL_Rect posicion_agua = {650, 140, 100, 75};
    SDL_Rect posicion_agua2 = {325, 140, 125, 75};
    SDL_Rect posicion_agua3 = {-300, 140, 435, 75};
    //Posicion Agua bot
    SDL_Rect posicion_agua4 = {590, 75, 335, 45};
    SDL_Rect posicion_agua5 = {110, 75, 300, 45};

    /* FIla 2 */
    //POsicion carro rojo

    SDL_Rect posicion_carror = {750,450,75,70};

    //POsicion carro rojo 2
    SDL_Rect posicion_carror2 = {550, 450, 75 ,70};

    //POsicion carro rojo 3
    SDL_Rect posicion_carror3 = {350, 450, 75, 70};

    //POsicion carro rojo 4
    SDL_Rect posicion_carror4 = {150, 450, 75, 70};

    /* FIla 2 */
    //POsicion camion
    SDL_Rect posicion_camion = {-160, 380, 200, 70};

    //POsicion camion2
    SDL_Rect posicion_camion2 = {300, 380, 200, 70};

    /* FIla 3*/
    // Posicion carro rapido
    SDL_Rect posicion_carrera = {-160, 300, 75, 75};

    SDL_Rect posicion_carrera1 = {150, 300, 75, 75};

    SDL_Rect posicion_carrera2 = {300, 300, 75, 75};

    /* Agua 1 */
    //Posicion troncos
    SDL_Rect posicion_tronco = {750, 140, 200, 75};
    SDL_Rect posicion_tronco2 = {450, 140, 200, 75};
    SDL_Rect posicion_tronco3 = {120, 140, 200, 75};

    /*Agua 2*/
    SDL_Rect posicion_tronco4 = {-160, 60, 200, 75};
    //SDL_Rect posicion_tronco5 = {300, 60, 200, 75};
    SDL_Rect posicion_tronco6 = {400, 60, 200, 75};


/////////////////////////////////////////////////////////////////////////////////////
    int vida = 3;
    int ti = tiempo_contador, score = 0, level =0;
    bool running = true;
    bool sg = false;
    bool pause = false;
    SDL_Event event;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }


/////////////////////////////////////////////////////////////////////////////////////
        while(vida>0 && ti > 0 && sg == true && pause == false)
        {
            // Movimiento carro
            float velocidad = 1.5;

                if(posicion_carror.x <  780){
                    posicion_carror.x = posicion_carror.x - velocidad;
                }
                if (posicion_carror.x <-2){
                    posicion_carror.x = 750;
                }

                if(posicion_carror2.x <  780){
                    posicion_carror2.x = posicion_carror2.x - velocidad;
                }
                if (posicion_carror2.x <-2){
                    posicion_carror2.x = 750;
                }

                if(posicion_carror3.x <  780){
                    posicion_carror3.x = posicion_carror3.x - velocidad;
                }
                if (posicion_carror3.x <-2){
                    posicion_carror3.x = 750;
                }

                if(posicion_carror4.x <  780){
                    posicion_carror4.x = posicion_carror4.x - velocidad;
                }
                if (posicion_carror4.x <-2){
                    posicion_carror4.x = 750;
                }
    /////////////////////////////////////////////////////////////////////////////////////
            // Movimiento CAMION
                if(posicion_camion.x >  -200){
                    posicion_camion.x = posicion_camion.x + velocidad;
                }
                if (posicion_camion.x > 800){
                    posicion_camion.x = -120;
                }

                if(posicion_camion2.x >  -200){
                    posicion_camion2.x = posicion_camion2.x + velocidad;
                }
                if (posicion_camion2.x > 800){
                    posicion_camion2.x = -120;
                }


    /////////////////////////////////////////////////////////////////////////////////////
            // Movimiento CARRO RAPIDO
            float velocidad2 = 4.5;
                if(posicion_carrera.x >  -200){
                    posicion_carrera.x = posicion_carrera.x + velocidad2;
                }
                if (posicion_carrera.x > 800){
                    posicion_carrera.x = -150;
                }

                if(posicion_carrera1.x >  -200){
                    posicion_carrera1.x = posicion_carrera1.x + velocidad2;
                }
                if (posicion_carrera1.x > 800){
                    posicion_carrera1.x = -150;
                }

                if(posicion_carrera2.x >  -200){
                    posicion_carrera2.x = posicion_carrera2.x + velocidad2;
                }
                if (posicion_carrera2.x > 800){
                    posicion_carrera2.x = -150;
                }

    /////////////////////////////////////////////////////////////////////////////////////
            //Movimiento troncos
            float velocidad3 = 3;
                if(posicion_tronco.x <  1000){
                    posicion_tronco.x = posicion_tronco.x - velocidad3;
                }
                if (posicion_tronco.x <-250){
                    posicion_tronco.x = 980;
                }

                if(posicion_tronco2.x <  1000){
                    posicion_tronco2.x = posicion_tronco2.x - velocidad3;
                }
                if (posicion_tronco2.x <-250){
                    posicion_tronco2.x = 980;
                }

                if(posicion_tronco3.x <  1000){
                    posicion_tronco3.x = posicion_tronco3.x - velocidad3;
                }
                if (posicion_tronco3.x <-250){
                    posicion_tronco3.x = 980;
                }

            //Movimiento troncos 2

                if(posicion_tronco4.x >  -500){
                    posicion_tronco4.x = posicion_tronco4.x + velocidad;
                }
                if (posicion_tronco4.x > 900){
                    posicion_tronco4.x = -200;
                }
    /*
                if(posicion_tronco5.x > -500){
                    posicion_tronco5.x = posicion_tronco5.x + velocidad;
                }
                if (posicion_tronco5.x > 900){
                    posicion_tronco5.x = -390;
                }
    */
                if(posicion_tronco6.x  > -500){
                    posicion_tronco6.x = posicion_tronco6.x + velocidad;
                }
                if (posicion_tronco6.x > 900){
                    posicion_tronco6.x = -200;
                }

    /////////////////////////////////////////////////////////////////////////////////////
            //Agua movimientos
                if(posicion_agua.x <  1000){
                    posicion_agua.x = posicion_agua.x - velocidad3;
                }
                if (posicion_agua.x <-250){
                    posicion_agua.x = 980;
                }

                if(posicion_agua2.x <  1000){
                    posicion_agua2.x = posicion_agua2.x - velocidad3;
                }
                if (posicion_agua2.x <-250){
                    posicion_agua2.x = 980;
                }

                if(posicion_agua3.x <  1200){
                    posicion_agua3.x = posicion_agua3.x - velocidad3;
                }
                if (posicion_agua3.x <-450){
                    posicion_agua3.x = 780;
                }
                //////////////////////////////////////////////
                if(posicion_agua4.x > -800){
                    posicion_agua4.x = posicion_agua4.x + velocidad;
                }
                if (posicion_agua4.x > 900){
                    posicion_agua4.x = -200;
                }

                if(posicion_agua5.x >  -800){
                    posicion_agua5.x = posicion_agua5.x + velocidad;
                }
                if (posicion_agua5.x > 900){
                    posicion_agua5.x = -200;
                }

                /*if(posicion_agua3.x <  1200){
                    posicion_agua3.x = posicion_agua3.x - velocidad3;
                }
                if (posicion_agua3.x <-450){
                    posicion_agua3.x = 780;
                } */
    /////////////////////////////////////////////////////////////////////////////////////         525 original y

            // Muerte carros rojos
            if(posicion_pepe.y > 400)
            {
                if((posicion_pepe.x == posicion_carror.x-50 || posicion_pepe.x == posicion_carror.x+50) && (posicion_pepe.y-25 < posicion_carror.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO!\n");
                        vida--;
                        if(score>0)
                            score -= 10;
                }
            }

            if(posicion_pepe.y > 400)
            {
                if((posicion_pepe.x == posicion_carror2.x-50 || posicion_pepe.x == posicion_carror2.x+50) && (posicion_pepe.y-25 < posicion_carror2.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO!\n");
                        vida--;
                        if(score>0)
                            score -= 10;
                }
            }

            if(posicion_pepe.y > 400)
            {
                if((posicion_pepe.x == posicion_carror3.x-50 || posicion_pepe.x == posicion_carror3.x+50) && (posicion_pepe.y-25 < posicion_carror3.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO!\n");
                        vida--;
                        if(score>0)
                            score -= 10;
                }
            }

            if(posicion_pepe.y > 400)
            {
                if((posicion_pepe.x == posicion_carror4.x-50 || posicion_pepe.x == posicion_carror4.x+50) && (posicion_pepe.y-25 < posicion_carror4.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO!\n");
                        vida--;
                        if(score>0)
                            score -= 10;
                }
            }

    /////////////////////////////////////////////////////////////////////////////////////
            // Muerte camiones
            if(posicion_pepe.y > 320)
            {
                if((posicion_pepe.x == posicion_camion.x-50 || posicion_pepe.x == posicion_camion.x || posicion_pepe.x == posicion_camion.x+200 ) && (posicion_pepe.y-25 < posicion_camion.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CAMION1!\n");
                        vida--;
                        if(score>0)
                            score -= 22;
                }
            }


            if(posicion_pepe.y > 320)
            {
                if((posicion_pepe.x == posicion_camion2.x-200 || posicion_pepe.x == posicion_camion2.x || posicion_pepe.x == posicion_camion2.x+200 ) && (posicion_pepe.y-25 < posicion_camion2.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CAMION2!\n");
                        vida--;
                        if(score>0)
                            score -= 22;
                }
            }

    /////////////////////////////////////////////////////////////////////////////////////
            // Muerte carro rapido
            if(posicion_pepe.y > 300)
            {
                if((posicion_pepe.x == posicion_carrera.x-50 || posicion_pepe.x == posicion_carrera.x || posicion_pepe.x == posicion_carrera.x+50 ) && (posicion_pepe.y-25 < posicion_carrera.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO DE CARRERA!\n");
                        vida--;
                        if(score>0)
                            score -= 32;
                }
            }


            if(posicion_pepe.y > 300)
            {
                if((posicion_pepe.x == posicion_carrera1.x-50 || posicion_pepe.x == posicion_carrera1.x || posicion_pepe.x == posicion_carrera1.x+50 ) && (posicion_pepe.y-25 < posicion_carrera1.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO DE CARRERA!\n");
                        vida--;
                        if(score>0)
                            score -= 32;
                }
            }

            if(posicion_pepe.y > 300)
            {
                if((posicion_pepe.x == posicion_carrera2.x-50 || posicion_pepe.x == posicion_carrera2.x || posicion_pepe.x == posicion_carrera2.x+50 ) && (posicion_pepe.y-25 < posicion_carrera2.y))
                {
                        posicion_pepe.x = 370;
                        posicion_pepe.y = 550;
                        printf("MUERTE POR CARRO DE CARRERA!\n");
                        vida--;
                        if(score>0)
                            score -= 32;
                }
            }

    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
        // AGUAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA

            bool collision4(SDL_Rect *rect1, SDL_Rect* rect2){
                if(rect1->y >= rect2->y +rect2->h)
                    return 0;
                if(rect1->x >= rect2->x+160 +rect2->w-155)
                    return 0;
                if(rect1->y + rect2->h <= rect2->y)
                    return 0;
                if(rect1->x + rect2->w-155 <= rect2->x+160)
                    return 0;
                return 1;
            }

            bool collision3(SDL_Rect *rect1, SDL_Rect* rect2){
                if(rect1->y >= rect2->y +rect2->h)
                    return 0;
                if(rect1->x >= rect2->x+200 +rect2->w-250)
                    return 0;
                if(rect1->y + rect2->h <= rect2->y)
                    return 0;
                if(rect1->x + rect2->w-250 <= rect2->x+200)
                    return 0;
                return 1;
            }

            bool collision2(SDL_Rect *rect1, SDL_Rect* rect2){
                if(rect1->y >= rect2->y +rect2->h)
                    return 0;
                if(rect1->x >= rect2->x +rect2->w-30)
                    return 0;
                if(rect1->y + rect2->h <= rect2->y)
                    return 0;
                if(rect1->x + rect2->w-30 <= rect2->x)
                    return 0;
                return 1;
            }

            bool collision(SDL_Rect *rect1, SDL_Rect* rect2){
                if(rect1->y >= rect2->y +rect2->h)
                    return 0;
                if(rect1->x >= rect2->x+20 +rect2->w-100)
                    return 0;
                if(rect1->y + rect2->h <= rect2->y)
                    return 0;
                if(rect1->x + rect2->w-100 <= rect2->x+20)
                    return 0;
                return 1;
            }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // Movimiento por tronco
            if(posicion_pepe.y <200 && posicion_pepe.y >100 ){
                if(collision(&posicion_pepe, &posicion_tronco)){
                    posicion_pepe.x -= velocidad3;
                }

                if(collision(&posicion_pepe, &posicion_tronco2)){
                    posicion_pepe.x -= velocidad3;
                }

                if(collision(&posicion_pepe, &posicion_tronco3)){
                    posicion_pepe.x -= velocidad3;
                }
            }

            //2

            if(posicion_pepe.y <125 && posicion_pepe.y >50){
                if(collision(&posicion_pepe, &posicion_tronco4)){
                    posicion_pepe.x += velocidad;
                }

                if(collision(&posicion_pepe, &posicion_tronco6)){
                    posicion_pepe.x += velocidad;
                }
            }
////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if(posicion_pepe.y <200 && posicion_pepe.y >100 ){
                if(collision2(&posicion_pepe, &posicion_agua)){
                    printf("MUERTE POR AGUA111**********************************");
                    posicion_pepe.x = 370;
                    posicion_pepe.y = 550;
                    vida--;
                        if(score>0)
                            score -= 42;

                }

                if(collision(&posicion_pepe, &posicion_agua2)){
                    printf("MUERTE POR AGUA222");
                    posicion_pepe.x = 370;
                    posicion_pepe.y = 550;
                    vida--;
                        if(score>0)
                            score -= 42;
                }

                if(collision3(&posicion_pepe, &posicion_agua3)){
                    printf("MUERTE POR AGUA333");
                    posicion_pepe.x = 370;
                    posicion_pepe.y = 550;
                    vida--;
                        if(score>0)
                            score -= 42;
                }
            }

////////////////////////////////////////////////////////////////////////////////////////////////////////////

            // Segundos
            if(posicion_pepe.y <125 && posicion_pepe.y >50){
                if(collision4(&posicion_pepe, &posicion_agua4)){
                    printf("MUERTE POR AGUA44444444444444444");
                    posicion_pepe.x = 370;
                    posicion_pepe.y = 550;
                    vida--;
                        if(score>0)
                            score -= 78;
                }


                if(collision4(&posicion_pepe, &posicion_agua5)){
                    printf("MUERTE POR AGUA5555555555555555");
                    posicion_pepe.x = 370;
                    posicion_pepe.y = 550;
                    vida--;
                        if(score>0)
                            score -= 78;
                }

            } else


            // WIN.
            if(posicion_pepe.y < 50){
                printf("WIN!\n");
                posicion_pepe.x = 370;
                posicion_pepe.y = 550;
                level += 1;
                if(tiempo_contador > 500){
                    tiempo_contador -=100;
                }
                ti = tiempo_contador;
                posicion_tiempo.w = tiempo_contador;
                pos_ganar.x = (width/3.5);
                pos_ganar.y = (height/3);
            }

/////////////////////////////////////////////////////////////////////////////////////
            // VIDAS CONTADOR
            if(vida == 2){
                posicion_vida3.x = 1000;
            }
            if(vida == 1){
                posicion_vida2.x = 1000;
            }
            if(vida == 0){
                posicion_vida1.x = 1000;
                pos_perder.x = (width/3.5);
                pos_perder.y = (height/3);
            }

/////////////////////////////////////////////////////////////////////////////////////
        //Tiempo


            ti--;
            printf("%i\n", ti);
            posicion_tiempo.w -= 1;
            if(ti == 0){
                pos_perder.x = (width/3.5);
                pos_perder.y = (height/3);
            }
/////////////////////////////////////////////////////////////////////////////////////
            //Score
            char pp2[50];
            sprintf(pp2, "Score: %d", score);
            SDL_Surface *textsurface = TTF_RenderText_Solid(fuente_berk, pp2, color);
            SDL_Texture *text = SDL_CreateTextureFromSurface(render, textsurface);
            SDL_Rect textREct;
            textREct.x = 50;
            textREct.y = 650;
            SDL_QueryTexture(text, NULL, NULL, &textREct.w, &textREct.h);
            SDL_FreeSurface(textsurface);

            //Level
            char nivel[50];
            sprintf(nivel, "Level: %d", level);
            SDL_Surface *textsurface_lvl = TTF_RenderText_Solid(fuente_berk, nivel, color2);
            SDL_Texture *text_lvl = SDL_CreateTextureFromSurface(render, textsurface_lvl);
            SDL_Rect pos_lvl;
            pos_lvl.x = 600;
            pos_lvl.y = 655;
            SDL_QueryTexture(text, NULL, NULL, &pos_lvl.w, &pos_lvl.h);
            SDL_FreeSurface(textsurface_lvl);


/////////////////////////////////////////////////////////////////////////////////////
            //Limpiar ventana
            SDL_RenderClear(render);

            // DIBUJAR

            SDL_RenderCopy(render, fondo, NULL, &posicion_fondo);


            SDL_RenderCopy(render, tiempo, NULL, &posicion_tiempo);
            SDL_RenderCopy(render, vidas, NULL, &posicion_vida1);
            SDL_RenderCopy(render, vidas, NULL, &posicion_vida2);
            SDL_RenderCopy(render, vidas, NULL, &posicion_vida3);
            //
            SDL_RenderCopy(render, agua, NULL, &posicion_agua);
            SDL_RenderCopy(render, agua, NULL, &posicion_agua2);
            SDL_RenderCopy(render, agua, NULL, &posicion_agua3);
            //
            SDL_RenderCopy(render, agua, NULL, &posicion_agua4);
            SDL_RenderCopy(render, agua, NULL, &posicion_agua5);
            //
            SDL_RenderCopy(render, tronco, NULL, &posicion_tronco);
            SDL_RenderCopy(render, tronco, NULL, &posicion_tronco2);
            SDL_RenderCopy(render, tronco, NULL, &posicion_tronco3);
            SDL_RenderCopy(render, tronco, NULL, &posicion_tronco4);
            SDL_RenderCopy(render, tronco, NULL, &posicion_tronco6);

            SDL_RenderCopy(render, image_texture, NULL, &posicion_pepe);

            SDL_RenderCopy(render, carro_rojo, NULL, &posicion_carror);
            SDL_RenderCopy(render, carro_rojo, NULL, &posicion_carror2);
            SDL_RenderCopy(render, carro_rojo, NULL, &posicion_carror3);
            SDL_RenderCopy(render, carro_rojo, NULL, &posicion_carror4);

            SDL_RenderCopy(render, camion, NULL, &posicion_camion);
            SDL_RenderCopy(render, camion, NULL, &posicion_camion2);

            SDL_RenderCopy(render, carro_rapido, NULL, &posicion_carrera);
            SDL_RenderCopy(render, carro_rapido, NULL, &posicion_carrera1);
            SDL_RenderCopy(render, carro_rapido, NULL, &posicion_carrera2);
            SDL_RenderCopy(render, text, NULL, &textREct);
            SDL_RenderCopy(render, text_lvl, NULL, &pos_lvl);
            SDL_RenderCopy(render, text_pausa, NULL, &pos_pausa);
            SDL_RenderCopy(render, text_perder, NULL, &pos_perder);
            SDL_RenderCopy(render, text_ganar, NULL, &pos_ganar);



            // Muestra lo dibujado
            SDL_RenderPresent(render);

            //MOVIMIENTO PEPE
            if(SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_p:
                            pos_pausa.x = (width/3);
                            pos_pausa.y = (height/3);

                            SDL_RenderCopy(render, text_pausa, NULL, &pos_pausa);
                            SDL_RenderPresent(render);
                            if(pos_pausa.x = (width/3))
                                pause = true;
                            break;

                        case SDLK_LEFT:
                            posicion_pepe.x -= 78;

                            score +=42;
                            if(posicion_pepe.x < -78){
                                posicion_pepe.x += 78;

                            }
                            break;

                        case SDLK_RIGHT:
                            posicion_pepe.x += 78;

                            score +=27;
                            if(posicion_pepe.x >775){ //800
                                posicion_pepe.x -= 78;
                            }
                            break;

                        case SDLK_UP:
                            posicion_pepe.y -= 78;
                            pos_ganar.x = 1000;
                            pos_ganar.y = 1000;

                            score +=27;
                            if(posicion_pepe.y <-53){ //-78
                                posicion_pepe.y += 78;
                            }
                            break;

                        case SDLK_DOWN:
                            posicion_pepe.y += 78;

                            score +=11;
                            if(posicion_pepe.y >= 575){ //550
                                posicion_pepe.y -= 78;
                            }
                            break;

                        case SDLK_m:
                            posicion_menu.y = 0;
                            sg = false;
                            vida = 3;
                            posicion_vida3.x = 650;
                            posicion_vida2.x = 700;
                            posicion_vida1.x = 750;
                            ti = 1600;
                            posicion_tiempo.w = 1600;
                            tiempo_contador = 1600;
                            posicion_pepe.x = 370;
                            posicion_pepe.y = 550;
                            score = 0;
                            level = 0;
                        break;
                    }
                }
            }
        } // FIN While vida
        if(vida == 0 || pause == true|| ti == 0 || sg == true){
        //printf("PResiona R para volver a jugar");

            if(SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_r:
                            vida = 3;
                            posicion_vida3.x = 650;
                            posicion_vida2.x = 700;
                            posicion_vida1.x = 750;
                            ti = 1600;
                            posicion_tiempo.w = 1600;
                            tiempo_contador = 1600;
                            posicion_pepe.x = 370;
                            posicion_pepe.y = 550;
                            score = 0;
                            level = 0;
                            pos_perder.x = 1000;
                            pos_perder.y = 1000;
                        break;

                        case SDLK_p:
                            pos_pausa.x = 1000;
                            pos_pausa.y = 1000;
                            pause = false;
                        break;
                    }
                }
            }
        }

        while(sg == false){
            SDL_RenderClear(render);
            SDL_RenderCopy(render, menu, NULL, &posicion_menu);
            SDL_RenderPresent(render);

            if(SDL_PollEvent(&event)){
                switch (event.type){
                    case SDL_QUIT:
                        running = false;
                    break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){
                        case SDLK_p:
                            posicion_menu.y = -5000;
                            sg = true;
                        }
                    break;
                }
            }
        }
    } //FIn WHILE running

    // Recursos
    SDL_DestroyTexture(menu);
    IMG_Quit();
    SDL_DestroyTexture(vidas);
    IMG_Quit();
    SDL_DestroyTexture(tiempo);
    IMG_Quit();
    SDL_DestroyTexture(tronco);
    IMG_Quit();
    SDL_DestroyTexture(camion);
    IMG_Quit();
    SDL_DestroyTexture(carro_rapido);
    IMG_Quit();
    SDL_DestroyTexture(fondo);
    IMG_Quit();
    SDL_DestroyTexture(carro_rojo);
    IMG_Quit();
    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}

// Cargar una imagen
SDL_Texture *inicializar_textura_de_archivo(const char* file_name, SDL_Renderer *render){
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(render, image);
    SDL_FreeSurface(image);
    return image_texture;
}

/*SDL_Texture *inicializar_texto(const char *fuente, const int tama, SDL_Renderer *render, char *mensaje, SDL_Color *color){
    TTF_Font *fuente = TTF_OpenFont(fuente, tama);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *textsurface = TTF_RenderText_Solid(fuente, mensaje, color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(render, textsurface);
    SDL_Rect textREct;
    return text;
}*/

