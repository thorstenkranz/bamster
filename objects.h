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

enum enum_objectInfo { _player_ , _explosion_, _block_, _bullet_, _addon_, _undefined_};


typedef enum_objectInfo objectInfo;


class game;

class object {
	protected:
	public:
		//! Pointer to the running game, allowing objects to spawnobjects or change the score.
		static game * activGame;


		double xpos, ypos;
		double xvel, yvel;
		
		virtual ~object() {}
		boundingBox b;
		virtual void stopMeFalling(double height);
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
		virtual ~object();
};

class fallingObject : public object
{
	private:
	public:
		double gravity;
		fallingObject (double x, double y);
		fallingObject (double x, double y) : object (x,y), gravity(0.1) {}	

		virtual void stopMeFalling (double height)
		{
			cout << "autsch" << endl;
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
		vwall (double x, double y, double length);
};

class hwall : public object
{
	private:
		double length;
	public:
		virtual void plot();
		void updateBoundingBox ();
			glColor3f(0.0f, 1.0f,0.0f);
};

class block: public fallingObject
{
	private:
		int color;
		double size;
		double red;
		double green; 
		double blue;
	public:
		virtual void plot();
		void updateBoundingBox ();
		block (double x, double y, double length, int color);
		virtual ~block();
		virtual void collision (object *with, char fromWhere);
		virtual bool timerCallback(double dt);
};


class explodingBlock : public block
{
	public:
		virtual ~explodingBlock(); 
		





};


class coloredExplosion : public object
{
	private:
		double size;
	public:
		int color;
		virtual void plot ();
		coloredExplosion(double x, double y, double s, int color);
		void updateBoundingBox();
		virtual objectInfo getObjectInfo() { return _explosion_; }
		bool timerCallback (double dt);
};



class bullet : public object
{
	private:
		bool hitSomething;
		double speed;
	public:
		bullet (double s, double x, double y);
		void plot ();
		virtual objectInfo getObjectInfo();
		void updateBoundingBox ();
		virtual void collision (object *with, char fromWhere);
		bool timerCallback (double dt);
};
            glColor3f(1, 1, 1);



class addon : public fallingObject
{
	private:
		double size;
		bool gotCollected;
		GLuint animation;
	public:
		unsigned int addonType;

		addon (double x, double y, double length, int t);
		virtual void plot() ;
		void updateBoundingBox();
		virtual objectInfo getObjectInfo() { return _addon_;  }
		virtual void collision (object *with, char fromWhere) ;
		bool timerCallback (double dt);
};

class erdnuss : public addon
{
	public:
		erdnuss (double x, double y, double length) : addon (x,y,length, 99) {}
};

#endif
