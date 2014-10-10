
#ifndef graphicalObject_h
#define graphicalObject_h

#include <list>

/**
 * Classe objeto gr�fico
 * @author Gustavo Rufino Feltrin
 * @author Leonardo Fernandes
 */
class GraphicalObject {
	private:
		std::list<GraphicalObject*> objectList;

	public:
		/**
		 * Construtor do objeto grafico
		 * @param primitive Primitiva grafica
		 */
		GraphicalObject();

		/**
		 * Destrutor do objeto grafico
		 */
		~GraphicalObject(void);		

		/**
		 * Adiciona objeto brafico filho
		 * @param obj Objeto grafico
		 */
		void addObj(GraphicalObject* obj);

		/**
		 * Desenha o objeto gr�fico
		 */
		virtual void draw(int run);
};

#endif
