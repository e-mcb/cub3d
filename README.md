# cub3d

On stock les valeurs de la map (murs/sol) dans un int **
On applique le floodfill depuis la pos du joueur pour valider la map -> On s'en fout des bouts map exterieurs
{
	Mur == 1
	Sol == 0
	Hors map == -1
}
Il faudra jongler entre les floats du programme et les int du tableau pour la gestion de collision par exemple

____________________________________________________________________________

Partie maths

On travail sur un plan euclidien avec l'int 0,0 comme origine du repere
La position du joueur

On travail avec un angle theta constant (defini par la lettre de spawn du joeuur) que l'on incrementera grace aux hooks des touches flechees droite && gauche (eventuellement de la souris)

Le FOV constant a mettre a l'echelle par rapport a la taille de la fenetre pour definir l'intervalle dans lequel appliquer le DDA -> On utilisera peut etre plutot 


Le DDA qui nous donnera une distance en x ou en y pour definir la distance de chaque rayon -> Definir la taille du mur pour cette colonne de pixels

