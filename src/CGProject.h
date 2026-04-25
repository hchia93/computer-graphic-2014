/********************************************
Course : TGD2151 Computer Graphics Fundamentals /
TCS2111 Computer Graphics
Session: Trimester 2, 2014/15
ID and Name #1 : 1131120642 Chia JianFei
Contacts #1 : 0167634275 hyrex.chia@gmail.com
********************************************/

#ifndef CG_PROJ_H
#define CG_PROJ_H
#include "CGLabmain.h"

namespace CGProject
{
    class St_Basils_Cathedral
    {
        public:
        /* Low-level Element */
        //All Roof Top
        void drawCatholicCross(float R,float G,float B);
        void drawSmallCatholicRoof();
        void drawWhiteArcWindow();
        void drawSemiCylinder_SmallDome();
        void drawSemiCylinder_CenterDome();
        void drawSemiCylinder_MediumDome1();
        void drawSemiCylinder_MediumDome2();
        void drawSemiCylinder_MediumDome2_b();
        void drawSemiCylinder_MediumDome3();
        void drawRedArcSurface_MediumDome3();
        void drawTriangleBase_MediumDome();
        void drawTriangleTop_MediumDome();
        void drawRedArcSurface_CenterDome();
        void drawWhiteArc_CenterDome();
        void drawRedTriangle_CenterDome();

        ///Walls
        void drawWall_Center();
        void drawWall_Small();
        void drawWall_Medium1();
        void drawWall_Medium2();
        void drawWall_Medium3();

        ///Tops
        void drawDomeTop_1(); //Spiral Green Small
        void drawDomeTop_2(); //Spiral blue-red
        void drawDomeTop_3();
        void drawDomeTop_4();
        void drawDomeTop_5();
        void drawDomeTop_6();
        void drawDomeTop_7();
        void drawDomeTop_8();
        void drawDomeTop_9();
        ///Dome
        void drawCenterDome();
        void drawSmallDome1();
        void drawSmallDome2();
        void drawSmallDome3();
        void drawSmallDome4();
        void drawMediumDome1();
        void drawMediumDome2();
        void drawMediumDome3();
        void drawMediumDome4(); //Entrance one


        /*Higher-level Element*/
        void drawBase();

        /* Highest-Level Element */
        void drawKremlinAndRedSquare();


    };


    class MyBoundingBox
    {
        public:
            MyBoundingBox( GLfloat xcenter, GLfloat ycenter, GLfloat zcenter,
            GLfloat xdim, GLfloat ydim, GLfloat zdim )
            {
                GLfloat xdimhalf = xdim/2.0;
                GLfloat ydimhalf = ydim/2.0;
                GLfloat zdimhalf = zdim/2.0;
                y[0] = ycenter + ydimhalf;
                y[1] = y[2] = y[3] = y[0]; //top
                y[4] = ycenter - ydimhalf;
                y[7] = y[6] = y[5] = y[4]; //bottom
                x[1] = xcenter + xdimhalf;
                x[6] = x[5] = x[2] = x[1]; //right
                x[0] = xcenter - xdimhalf;
                x[7] = x[4] = x[3] = x[0]; //left
                z[0] = zcenter + zdimhalf;
                z[5] = z[4] = z[1] = z[0]; //front
                z[2] = zcenter - zdimhalf;
                z[7] = z[6] = z[3] = z[2]; //back
            }
            void draw();
            void drawGrids();
        private:
                GLfloat x[8], y[8], z[8]; //(x,y,z) of 8 corner points
    };

    class MyVirtualWorld
    {
        public:

            MyBoundingBox myboundingbox;
            St_Basils_Cathedral KremlinAndRedSquare;
            MyVirtualWorld() : myboundingbox(0.0, 0.0, 0.0, 120.0, 0.0, 120.0){} //only X, and Z, no Y
            void draw()
            {
                KremlinAndRedSquare.drawKremlinAndRedSquare();


            }
            void tickTime()
            {
                //do nothing, reserved for doing animation
            }
            //for any one-time only initialization of the
            // virtual world before any rendering takes place
            // BUT after OpenGL has been initialized
            void init()
            {

            }
    };
}


#endif
