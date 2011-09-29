#ifndef objects_h
#define objects_h objects_h

#include <X11/Xlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

#include "imageloader.h"

using namespace std;

struct boundingBox
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};


//const double gravity = 1.0;

const char fromLeft = 1;
const char fromRight = 2;
const char fromUp = 3;
const char fromDown = 4;

const static double colors[5][3] = {
	{1.,0.,0.},
	{0.,1.,0.},
	{0.,0.,1.},
	{1.,0.,1.},
	{0.,1.,1.}
} ;

char otherSide (char side);

enum enum_objectInfo { _player_, _block_, _bullet_, _undefined_};


typedef enum_objectInfo objectInfo;

class object {
	protected:
	public:
		static double gameTime;
		double xpos, ypos;
		boundingBox b;
		virtual void stopMeFalling(double height);
		int hitpoints;
		object (double x, double y); 
		virtual objectInfo getObjectInfo();
		virtual void updateBoundingBox();
		GLuint loadTexture(Image *image);
		char collidesWith (object &o);
		virtual void plot();
		virtual bool timerCallback(double dt);
		virtual void collision(object *with, char fromWhere);
};

class fallingObject : public object
{
	private:
	public:
		float yvel;
		double gravity;
		unsigned int hitpoints;
		fallingObject (double x, double y);
		virtual void stopMeFalling (double height);
		virtual void collision (object *with, char fromWhere);
		virtual objectInfo getObjectInfo();
		virtual bool timerCallback(double dt);
};

class game ;

extern game * activGame;

void spawnObject (object *p);



class vwall : public object
{
	private:
		double length;
	public:
		virtual void plot();
		void updateBoundingBox ();
		vwall (double x, double y, double l);
};

class hwall : public object
{
	private:
		double length;
	public:
		virtual void plot();
		void updateBoundingBox ();
		hwall (double x, double y, double l);
};

class block: public fallingObject
{
	private:
		double size;
		double red;
		double green; 
		double blue;
	public:
		virtual void plot();
		void updateBoundingBox ();
		block (double x, double y, double l);
		virtual ~block();
		virtual void collision (object *with, char fromWhere);
		virtual bool timerCallback(double dt);
};


class bullet : public object
{
	private:
		double speed;
		bool hitSomething;
	public:
		bullet (double s, double x, double y);
		void plot ();
		virtual objectInfo getObjectInfo();
		void updateBoundingBox ();
		virtual void collision (object *with, char fromWhere);
		bool timerCallback (double dt);
};



#endif
