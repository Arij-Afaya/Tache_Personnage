#ifndef player_H_INCLUDED
#define player_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
    int score;
    int vie;
    SDL_Surface *text;
}score;
typedef struct
{
    int left, right, jump, attack, down;

} Input; /*!<STRUCTURE pour initialiser la direction*/
typedef struct
{
    SDL_Surface *allMvt;/*!<sprite sheet*/
    SDL_Rect heroPos;/*!<rectangle*/
    SDL_Rect rects[80];

    int frame;
    float xStep, yStep;/*!<combien le perso va avancer ou monter*/
    float velocity, speed;
    int currentMode;/*!<etat du personnage stable si il est en mouvement ou saut*/

} Hero;


void setrects(SDL_Rect *crop);
void init_perso(Hero *h,Input *I);
void init_perso1(Hero *hero1,Input *I1);
void afficher_Hero(Hero *h, SDL_Surface *screen);
void afficher_Hero1(Hero *hero1, SDL_Surface *screen);
void Animerperso(Hero *h, SDL_Surface *screen, SDL_Surface *bg, SDL_Rect bgPos, int run);
void deplacerperso(Hero *hero, Input I, Uint32 dt);
void saut(Hero *hero, Input I, int *run);

#endif
