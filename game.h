#include "bamster.h"

#include <list>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <cstdio>



class game
{

	private:
		object * thePlayer;
		list<object *> otherObjects;
	bool firstResize;

		bool firstResize;
		firstResize=1;

		unsigned int noBlockGeneration;

		GLuint loadTexture(Image *image);
		void spawnHoleRow();
		void handleCollisions();

		if (firstResize) {
			glutReshapeWindow(640,480);
			firstResize=0;
			printf("First Reshape");
		}


	public:

		unsigned int score;
		double gameTime;
		game ();
		
		//! spawn an object in the game (to be used by objects) 
		void spawnObject(object *p) ;   

		//! calls the plot function of all objects
		void plot();                   

		//! simulate the game for one frame.
		void timerCallback();

};

