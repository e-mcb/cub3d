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


DDA vs XiaoLin's anti aliasing

No point since the graphic part doesnt exactly relate to the algo, we are just trying to find out the distance in order to decide the height of our wall








Let the map be an array of strings - char **
We are equating this map to an orthogonal coordinate system with an origin [0, 0] at the address map[0][0] // parsing might have to trim some parts in that case?
We would then need to be turn those integers into floating points (vertical wall in position [0, 0] would span from y = 0 to y = 0.99999...)



The player can move freely inside of the map, rotating freely around the fixed z-axis. The player would then be represented by its coordinate as well as a vector U to modelize the orientation the player, which will always be the center of the window.

The vector U would make an angle Θ with the vector (1, 0) of the plane. 
The player also has a FoV (Field of view) -> Constant angle defined prior to the modelization's beginning, which basically represents what needs to displayed to the window
The vector U will always bisect the FoV.


The simulation takes 2 initial parameters into account

The initial position and orientation of the player
This data can be accessed from the array but needs to be interpreted as we are using floating points -> map [x][y] might be any floating point between 
[x, y]; [x+1, y+1]


 