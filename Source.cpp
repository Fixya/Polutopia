#include "settings.h"
#include "game.h"
using namespace sf;
int main()
{
	Game game;
	game.play();
	return 0;
}
//получить координаты мыши
			//пройти по всем игрокам и посмотреть во FloatRect какого попал курсор
			// if (playerBounds.contains(mousePos)){
					//вот этот игрок становится активным
			//}