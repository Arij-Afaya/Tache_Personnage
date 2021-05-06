/**
 * @file main.c
*/

#include "player.h"


int main()
{
    int done = 1, run = 0,run1=0;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);//initialisation

    SDL_Surface *screen, *bg;
    SDL_WM_SetIcon(IMG_Load("bg.jpg"),NULL);//photo de l'icone qui apparait au cours de l'execution
    screen = SDL_SetVideoMode(1500, 500, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Mind Units", NULL); //nom de la fenetre


    SDL_Rect bgPos;
    bgPos.x = 0;
    bgPos.y =0;

    //----------------------------------------------------------------------------------------------------------------------
    Hero hero,hero1;
    Input I,I1;
    init_perso(&hero,&I);
    init_perso1(&hero1,&I1);
    char direction[50];

    Uint32 dt, t_prev;

    //----------------------------------------------------------------------------------------------------------------------

    bg = IMG_Load("cc.jpg");
    SDL_Flip(screen);
    SDL_Event event;
    SDL_EnableKeyRepeat(1, 0);//lorsque j'appuie sur le bouton le personnage continue a se deplacer sans lacher
    while (done)
    {
SDL_BlitSurface(bg, NULL, screen, &bgPos);
        t_prev = SDL_GetTicks();//utilisee calcule la duree de chaque iteration

        if (hero.currentMode == 0 || hero.currentMode == 2 || hero.currentMode == 4 || hero.currentMode == 6)
        {
            strcpy(direction, "right");
        }
        else
        {
            strcpy(direction, "left");
        }

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:

                done = 0;
                break;

            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    done = 0;
                    break;

                case SDLK_SPACE:
                    I.jump = 1;
                    break;

                case SDLK_RIGHT:
                    I.right = 1;
                    hero.currentMode = 2;
                    break;

                case SDLK_LEFT:
                    I.left = 1;
                    hero.currentMode = 3;
                    break;

                case SDLK_x:
                    I.attack = 1;
                    if (strcmp(direction, "right") == 0)
                    {
                        hero.currentMode = 6;
                    }
                    else
                    {
                        hero.currentMode = 7;
                    }
                    break;
                           case SDLK_z:
		            I1.jump = 1;//modification
		            break;

		        case SDLK_d:
		            I1.right = 1;//==> curremtmode =5  et run=1 alors : h->heroPos.x += 15;
		            hero1.currentMode = 2;
		            break;

		        case SDLK_q:
		            I1.left = 1;//==> curremtmode =5  et run=1 alors : h->heroPos.x -= 15;
		            hero1.currentMode = 3;
		            break;

		        case SDLK_w:
		            I1.attack = 1;
		            if (strcmp(direction, "right") == 0)
		            {
		                hero1.currentMode = 6;
		            }
		            else
		            {
		                hero1.currentMode = 7;
		            }
		            break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    I.jump = 0;
                    if (I.right == 1)
                    {
                        hero.currentMode = 2;
                    }
                    else if (I.left == 1)
                    {
                        hero.currentMode = 3;
                    }
                    else
                    {
                        if (strcmp(direction, "right") == 0)
                        {
                            hero.currentMode = 0;
                        }
                        else
                        {
                            hero.currentMode = 1;
                        }
                    }

                    break;

                case SDLK_RIGHT:
                    I.right = 0;
                    hero.currentMode = 0;
                    run = 0;
                    break;

                case SDLK_LEFT:
                    I.left = 0;
                    hero.currentMode = 1;
                    run = 0;
                    break;
                case SDLK_x:
                    I.attack = 0;
                    if (strcmp(direction, "right") == 0)
                    {
                        hero.currentMode = 0;
                    }
                    else
                    {
                        hero.currentMode = 1;
                    }
                    break;
                  case SDLK_z:
                    I1.jump = 0;
                    if (I1.right == 1)
                    {
                        hero1.currentMode = 2;

                    }
                    else if (I1.left == 1)
                    {
                        hero1.currentMode = 3;
                    }
                    else
                    {
                        if (strcmp(direction, "right") == 0)
                        {
                            hero1.currentMode = 0;
                        }
                        else
                        {
                            hero1.currentMode = 1;
                        }
                    }

                    break;

                case SDLK_d:
                    I1.right = 0;
                    hero1.currentMode = 0;
                    run1 = 0;
saut(&hero1, I1, &run1);
                    break;

                case SDLK_q:
                    I1.left = 0;
                    hero1.currentMode = 1;
                    run1 = 0;
saut(&hero1, I1, &run1);
                    break;
                case SDLK_w:
                    I1.attack = 0;
                    if (strcmp(direction, "right") == 0)
                    {
                        hero1.currentMode = 0;
                    }
                    else
                    {
                        hero1.currentMode = 1;
                    }
                    break;
                }
                break;
            }
            dt = SDL_GetTicks() - t_prev; //calculer la duree de chaque iteration
        }

       
        deplacerperso(&hero, I, dt);
        Animerperso(&hero, screen, bg, bgPos, run);
        saut(&hero, I, &run);
        afficher_Hero(&hero, screen);

deplacerperso(&hero1, I1, dt);
Animerperso(&hero1, screen, bg, bgPos, run1);
saut(&hero1, I1, &run1);
afficher_Hero1(&hero1, screen);

        SDL_Flip(screen);//mise a jour de l'ecran
        SDL_Delay(1); //temps de vitesse
    }

    SDL_FreeSurface(screen);
    SDL_FreeSurface(bg);
    SDL_Quit();
    return 0;
}
