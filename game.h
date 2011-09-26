#include "bamster.h"

#include <list>


#include <stdio.h>
#include <stdlib.h>



class game
{

    private:
        object * thePlayer;
		list<object *> otherObjects;
    public:

        game () {
		srand (time(NULL));
		otherObjects.push_back(new bamster( 20, 50));
		otherObjects.push_back(new hwall (50,0,100));
		otherObjects.push_back(new hwall (50,100,100));

		otherObjects.push_back(new vwall (0,50,100));
		otherObjects.push_back(new vwall (100,50,100));
        }
	
		void spawnObject(object *p) {
			otherObjects.push_back (p);
		}

			void handleCollisions();

        void plot()
        {

            glClear ( GL_COLOR_BUFFER_BIT ); //clear pixel buffer
//
//
//            thePlayer -> plot();
				
				list<object *>::iterator it;
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					(*it)->plot();

        }

        void timerCallback()
        {
			  object::gameTime += 1;
			  if (rand() % 100 > 98)
				  otherObjects.push_back( new block (rand() % 100, 80, 5));
				

				list<object *>::iterator it;
  //          thePlayer-> timerCallback(0.5);
				for (it = otherObjects.begin(); it != otherObjects.end(); it ++)
					if  (!(*it)->timerCallback(0.1))
						it = otherObjects.erase (it);
					
				handleCollisions();


        }

};



