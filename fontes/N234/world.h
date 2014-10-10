
#ifndef world_h
#define world_h

#include <list>
#include "graphicalObject.h"
#include "stereo.h"
#include "n234.h"

/**
 * Classe mundo, contém todos os objetos gráficos desenhados na cena
 * @author Gustavo Rufino Feltrin
 * @author Leonardo Fernandes
 */
class World {
	private:
		std::list<GraphicalObject*> objectList;
		Stereo *stereo;
		CAMERA *camera;

		/** Desenha os objetos gráficos */
		void drawObjects(int run);
	public:

		/**	Construtor do mundo */
		World(CAMERA *camera);

		/** Destrutor do mundo */
		~World(void);

		/** 
		 * Adiciona um objeto grafico no universo
		 * @param obj Objeto grafico
		 */
		void pushObject(GraphicalObject* obj);

		/**
		* Desenha os objetos graficos do universo
		*/
		void draw(int run);
};

#endif
