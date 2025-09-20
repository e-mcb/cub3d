#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAP_W 16
#define MAP_H 16
#define FOV (M_PI/2.0)        // 90°
#define SCREEN_W 100          // nombre de colonnes de la fenetre qu'on va afficher
#define SCREEN_H 32           // nombre de lignes de la fenetre qu'on va afficher

// Carte fermée (1 = mur, 0 = vide)
static int map[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,1,1,0,0,0,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,1,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,0,0,0,0,0,1,0,1,1,0,1},
    {1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1},
    {1,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,1,1,0,0,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// ATTENTION: COMME ON UTILISE UN REPERE QUI AUGMENT EN X VERS LA DROITE (normal) MAIS QUI 
// AUGMENTE EN Y EN ALLANT VERS LE BAS , ALORS LE SENS DE ROTATION DE L ANGLE (le signe) EST INVERSE

// Raycast DDA : renvoie distance perpendiculaire et remplit *side (0=face verticale, 1=face horizontale)
static double castRayDDA(double posX, double posY, double angle, int *side) {

    // on utilise deux variables pour pouvoir protéger apres des divisions par zéro
    double rayDirX = cos(angle);
    double rayDirY = sin(angle);

    // Eviter divisions par 0
    if (fabs(rayDirX) < 1e-12) rayDirX = (rayDirX < 0 ? -1e-12 : 1e-12);
    if (fabs(rayDirY) < 1e-12) rayDirY = (rayDirY < 0 ? -1e-12 : 1e-12);

    // mapX et mapY sont les poistion initiales exprimées en entier
    int mapX = (int)posX;
    int mapY = (int)posY;

    // deltaDistX et deltaDisY sont les distances parcourues si l'on touche le prochain entier vers la droite dans un cas, et si c est vers le haut 
    // dans l autre cas. 
    // MAIS, ce n'est pas la premiere distance, c'est la distance uniquement quand on part de coordonnées rondes. ex x = 4 et y = 2 .
    // ce deltaDistX et deltadistY ont tjs la meme valeur.
    double deltaDistX = fabs(1.0 / rayDirX);
    double deltaDistY = fabs(1.0 / rayDirY);

    int stepX, stepY;  //just pour savoir dans quel sens on va

    // au tout début (premiere fois qu on les calcule), sideDistX et sideDistY calculent la distance pour arriver soit 
    // a une arrête verticale soit horizontal depuis la position initiale du joueur (qui n'es pas forcément un entier)
    // quand on se sera décalé alors on sera sur des entier a chaque fois et on incrémentera de deltaDist pour de nouveau comparer.
    // difficile a expliquer ici mais je peux te l'expliquer facilement en vrai sur un dessin
    double sideDistX, sideDistY;

    // les conditions si dessous calculent la distance depuis la positions itiniales jusqu a la premiere arrête
    if (rayDirX < 0) {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    } else {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0) {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    } else {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }

    int hit = 0;
    *side = 0;

    // tant qu'on touche pas un mur on compare les distance pour savoir laquelle est la plus courte et savoir si on
    // décalle verticalement ou horizontallement et direct on incrémente la dist de deltaDist. comme ça le passage d'apres
    // on refait la comparaison etc...
    while (!hit) {
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            *side = 0; // mur vertical
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            *side = 1; // mur horizontal
        }
        if (mapX < 0 || mapX >= MAP_W || mapY < 0 || mapY >= MAP_H) break; // c est une sécurité, je pense que c'est inutile après le parsing
        if (map[mapY][mapX] == 1) hit = 1;
    }

    double perpWallDist;
    // Correction perpendiculaire au mur pour éviter l'effet fish-eye
    // ca je l'ai pris tel quel mais je le comprends pas forcément mathématiquement. 
    if (*side == 0) {
        perpWallDist = fabs((mapX - posX + (1 - stepX) * 0.5) / rayDirX);
    } else {
        perpWallDist = fabs((mapY - posY + (1 - stepY) * 0.5) / rayDirY);
    }

    if (perpWallDist < 1e-6) perpWallDist = 1e-6;

    return perpWallDist;
}

int main(void) {
    // Position / orientation du joueur
    double playerX = 7.5;
    double playerY = 7.5;
    double playerA = -M_PI/6.0; // -30° 
    double rayA;
    int     side;
    double  dist;
    int     z;
    double  wallX;

    rayA = playerA + FOV /2; // je commence depuis l'angle tout a gauche de la fov du joueur
    z = 1;
    while (rayA > playerA - FOV /2) // j'itère jusqu'à cxe que j'arrive à l'angle tout a droite de la FOV du joueur
    {
        side = 0;
        dist = castRayDDA(playerX, playerY, rayA, &side);
        printf("la distance de la colonne %d est de : %f\n", z, dist);
        if(side == 0)
        {
            printf("on touche un mur vertical\n");
            if (cos(rayA) < 0)
                printf("on le touche depuis la droite (on touche la face Est du mur)\n");
            else
                printf("on le touche depuis la gauche (on touche la face Ouest du mur)\n");
            wallX = playerY + dist * sin(rayA); //donne la coordonnée exacte de là où on touche le mur

        }
        else
        {
            printf("on touche un mur horizontal\n");
            if (sin(rayA) < 0)
                printf("on le touche depuis le bas (on touche la face Sud du mur)\n");
            else
                printf("on le touche depuis le haut (on touche la face Nord du mur)\n");
            wallX = playerX + dist * cos(rayA); //donne la coordonnée exacte de là où on touche le mur
        }
        wallX -= floor(wallX); // on garde que la partie décimale de la coordonnée exacte ou on touche le mur (par ex 4.58 donnera 0.58) dui coup on sait ou on est par rapport au début du mur (entre 0 et 1)
        // les ifs du dessous c'est pour éviter l'effet mirroir en fonctin du sens dans lequel on va. par exemple si on va vers la gauche de 0.2 , en réalité on n'est pas a 0.2 du dénut du mur mais à 0.8
        if (side == 0 && cos(rayA) > 0)
            wallX = 1.0 - wallX;
        if (side == 1 && sin(rayA) < 0)
            wallX = 1.0 - wallX;
        printf("on touche la texture (ou le mur c'est pareil du coup) à %f de son début.\n", wallX);
        printf("\n");

        //on décalle pour passer au rayon suivant. (il y en a SCREEN_W en tout)
        // si dessous chat me dit que c'est pas forcément optimal pour décaller l'angle. il y aurait potneitellement un décallage qui se cumulerait..
        // en fait je divise la FOV par le nombre de colonne de la fenetre et je décalle de cet angle là. 
        rayA = rayA - (FOV / SCREEN_W);
        z++;
    }
    
    return 0;
}
