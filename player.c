/**
 * @file player.c
*/
#include "player.h"
#define Ground 690;
#define SPEED 5
#define MAX_SPEED 10
#define MAX_JUMP_SPEED 25

int frameNb = 10;
void setrects(SDL_Rect *crop)/*!<crop=photo encadree*/
{
    int i;
/**
 * @brief animation droite
*/
    crop[0].x = 0;
    crop[0].y = 0;

    crop[0].w = 124;
    crop[0].h = 234;

    for (i = 1; i < frameNb; i++)
    {
        crop[i].w = 124;
        crop[i].h = 234;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 0;
    }

    //animation gauche
    crop[10].x = 0;
    crop[10].y = 234;

    crop[10].w = 124;
    crop[10].h = 234;

    for (i = 11; i < 2 * frameNb; i++)
    {
        crop[i].w = 124;
        crop[i].h = 234;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 234;
    }

    //run right
    crop[20].x = 0;
    crop[20].y = 468;

    crop[20].w = 222;
    crop[20].h = 280;

    for (i = 21; i < 3 * frameNb; i++)
    {
        crop[i].w = 222;
        crop[i].h = 280;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 468;
    }

    //run left
    crop[30].x = 0;
    crop[30].y = 748;

    crop[30].w = 222;
    crop[30].h = 280;

    for (i = 31; i < 4 * frameNb; i++)
    {
        crop[i].w = 222;
        crop[i].h = 280;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 748;
    }

    //jump right
    crop[40].x = 0;
    crop[40].y = 1030;

    crop[40].w = 221;
    crop[40].h = 295;

    for (i = 41; i < 5 * frameNb; i++)
    {
        crop[i].w = 221;
        crop[i].h = 295;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 1030;
    }

    //jump left
    crop[50].x = 0;
    crop[50].y = 1325;

    crop[50].w = 221;
    crop[50].h = 295;

    for (i = 51; i < 6 * frameNb; i++)
    {
        crop[i].w = 221;
        crop[i].h = 295;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 1325;
    }

    //attack right
    crop[60].x = 0;
    crop[60].y = 1620;

    crop[60].w = 352;
    crop[60].h = 325;

    for (i = 61; i < 7 * frameNb; i++)
    {
        crop[i].w = 352;
        crop[i].h = 325;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 1620;
    }

    //attack left
    crop[70].x = 0;
    crop[70].y = 1945;

    crop[70].w = 352;
    crop[70].h = 325;

    for (i = 71; i < 8 * frameNb; i++)
    {
        crop[i].w = 352;
        crop[i].h = 325;

        crop[i].x = crop[i].w + crop[i - 1].x;
        crop[i].y = 1945;
    }
}

void init_perso(Hero *h, Input *I)
{

    I->left = 0;
    I->right = 0;
    I->down = 0;
    I->jump = 0;
    I->attack = 0;
    h->allMvt = IMG_Load("sprite.png");

    h->frame = 0;
    h->currentMode = 0;

    h->heroPos.x = 100;
    h->heroPos.y = 200;

    h->velocity = 0;
    h->speed = 5;

    h->xStep = 20;
    h->yStep = 10;

    setrects(h->rects);
}
void init_perso1(Hero *hero1, Input *I1)
{

    I1->left = 0;
    I1->right = 0;
    I1->down = 0;
    I1->jump = 0;
    I1->attack = 0;
    hero1->allMvt = IMG_Load("sprite1.png");

    hero1->frame = 0;
    hero1->currentMode = 0;

    hero1->heroPos.x = 700;
    hero1->heroPos.y = 200;

    hero1->velocity = 0;
    hero1->speed = 5;

    hero1->xStep = 20;
    hero1->yStep = 10;

    setrects(hero1->rects);
}

void afficher_Hero(Hero *h, SDL_Surface *screen)
{
    SDL_BlitSurface(h->allMvt, &h->rects[h->frame], screen, &h->heroPos);
}
//******************AJOUTITHA TAWA
void afficher_Hero1(Hero *hero1, SDL_Surface *screen)
{
    SDL_BlitSurface(hero1->allMvt, &hero1->rects[hero1->frame], screen, &hero1->heroPos);
}

void deplacerperso(Hero *hero, Input I, Uint32 dt)
{
    if (hero->currentMode == 2 || hero->currentMode == 3)
    {
        if (I.right == 1)
        {
            hero->xStep = 0.5 * hero->velocity * 2.2 * 2.2 + hero->speed * 2.2;   //2.2=dt
            hero->heroPos.x += hero->xStep;
            if (hero->velocity < 8)
            {
                hero->velocity += 0.5;
            }
        }

        if (I.left == 1)
        {
            hero->xStep = 0.5 * hero->velocity * 2.2 * 2.2 + hero->speed * 2.2;//dt au carre=dt * dt
            hero->heroPos.x -= hero->xStep;
            if (hero->velocity < 8)
            {
                hero->velocity += 0.5;
            }
        }
    }
    if (I.right == 0 && I.left == 0)
    {
        hero->velocity = 0;
    }
}

void Animerperso(Hero *h, SDL_Surface *screen, SDL_Surface *bg, SDL_Rect bgPos, int run)
{

  int i;
    if (h->currentMode == 0) //animation stable vers la droite
    {
        if (h->frame < 0 || h->frame > 9)
        {
            h->frame = 0;
        }
        h->frame++;

        if (h->frame > frameNb - 1)
        {
            h->frame = 0;
        }
    }
    else if (h->currentMode == 1)//animation stable vers la gauche
    {

        if (h->frame < 10 || h->frame > 19)
        {
            h->frame = 10;
        }
        h->frame++;

        if (h->frame > 19)
        {
            h->frame = 10;
        }
    }
   else if (h->currentMode == 2)//animation du mouvement du perso a droite
    {
        if (h->frame < 20 || h->frame > 29)
        {
            h->frame = 20;
        }
        h->frame++;
        if (h->frame > 29)
        {
            h->frame = 20;
        }
    }
    else if (h->currentMode == 3)//animation du mouvement du perso a gauche
    {
        if (h->frame < 30 || h->frame > 39)
        {
            h->frame = 30;
        }
        h->frame++;
        if (h->frame > 39)
        {
            h->frame = 30;
        }
    }

    else if (h->currentMode == 4) // animation saut vers droite 
    {
        for (i = 40; i < 50; i++)
        {
            h->frame = i;

            if (i > 44)
            {
                h->heroPos.y += 25;
            }
            else
            {
                h->heroPos.y -= 25;
            }
            if (run == 1) //si run =1 il est entrain de courir
            {
                h->heroPos.x += 15;
            }
            SDL_BlitSurface(bg,NULL , screen, &bgPos);
            SDL_BlitSurface(h->allMvt, &h->rects[h->frame], screen, &h->heroPos);

            SDL_Flip(screen);
            SDL_Delay(15);//vitesse
        }
    }
    else if (h->currentMode == 5) // animation saut vers gauche
    {
        for (i = 50; i < 60; i++)
        {
            h->frame = i;

            if (i > 54)//quand l'animation est en cours et elle atteint la photo i>54 la position .y va ++ et elle retourne a sa pose initiale
            {
                h->heroPos.y += 25;
            }
            else
            {
                h->heroPos.y -= 25;//quand l'animation est en cours et elle atteint la photo i>54 la position .y va -- et elle retourne a sa pose initiale
            }

            if (run == 1)//if run==1 et currentmode=5 alors pose du perso.x diminue
            {
                h->heroPos.x -= 15;
            }
            SDL_BlitSurface(bg, NULL, screen, &bgPos);
            SDL_BlitSurface(h->allMvt, &h->rects[h->frame], screen, &h->heroPos);
            SDL_Flip(screen);
            SDL_Delay(15);
        }
    }
    
    else if (h->currentMode == 6)// animation du perso en attack a droite
    {
        for (i = 60; i < 69; i++)
        {
            h->frame = i;
            SDL_BlitSurface(bg, NULL, screen, &bgPos);
            SDL_BlitSurface(h->allMvt, &h->rects[h->frame], screen, &h->heroPos);
            SDL_Flip(screen);
            SDL_Delay(15);
        }
    }
    else if (h->currentMode == 7)/*!<animation du perso en attack a gauche*/
    {
        for (i = 70; i < 79; i++)
        {
            h->frame = i;
            SDL_BlitSurface(bg, NULL, screen, &bgPos);
            SDL_BlitSurface(h->allMvt, &h->rects[h->frame], screen, &h->heroPos);
            SDL_Flip(screen);
            SDL_Delay(15);
        }
    }
}




void saut(Hero *hero, Input I, int *run)
{
    if (I.jump == 1)
    {
        if (I.right == 1)
        {
            hero->currentMode = 4;//animation saut a droite+ changement dans axe y
            *run = 1;//currentmode=5 et run=1 alors posehero.x+=15;
        }
        else if (I.left == 1)
        {
            hero->currentMode = 5;//animation saut a gauche + changement dans axe y
            *run = 1;//currentmode=5 et run=1 alors posehero.x-=15;
        }
        else
        {
            if (hero->currentMode == 0)//perso sans mvt a droite = stable
            {
                hero->currentMode = 4;/*!<animation saut a droite+ changement dans axe y*/
                *run = 0;/*!<pas de changement au niveau de l'axe des abscisses x*/
            }
            else if (hero->currentMode == 1)//perso sans mvt a gauche = stable
            {
                hero->currentMode = 5;//animation saut a gauche+ changement dans axe y
                *run = 0;//pas de changement au niveau de l'axe des abscisses x
            }
        }
    }
}
