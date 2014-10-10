
#include "graphicalObject.h"

GraphicalObject::GraphicalObject(){
}

GraphicalObject::~GraphicalObject(){
	for (std::list<GraphicalObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); it++){
		delete *it;
	}	
	objectList.clear();
}

void GraphicalObject::addObj(GraphicalObject* obj){
	this->objectList.push_back(obj);
}

void GraphicalObject::draw(int run){
	for (std::list<GraphicalObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); it++){
		GraphicalObject* g = *it;
		g->draw(run);
	}
}
