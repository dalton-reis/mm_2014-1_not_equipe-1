
#include "world.h"

World::World(CAMERA *camera){
	stereo = new Stereo(camera);
}

World::~World(){
	for (std::list<GraphicalObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); it++){
		delete *it;
	}
	objectList.clear();
	free(stereo);
}

void World::pushObject(GraphicalObject* obj){
	objectList.push_back(obj);	
}

void World::drawObjects(int run){
	for (std::list<GraphicalObject*>::iterator it = this->objectList.begin(); it != this->objectList.end(); it++){
		GraphicalObject* gObj = *it; 
		gObj->draw(run);
	}
}

void World::draw(int run){
	stereo->viewPre();
		
	stereo->viewRight();
	drawObjects(run);

	stereo->viewLeft();
	drawObjects(run);

	stereo->viewPost();
}