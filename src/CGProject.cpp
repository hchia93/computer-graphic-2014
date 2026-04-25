/********************************************
Course : TGD2151 Computer Graphics Fundamentals /
TCS2111 Computer Graphics
Session: Trimester 2, 2014/15
ID and Name #1 : 1131120642 Chia JianFei
Contacts #1 : 0167634275 hyrex.chia@gmail.com
********************************************/

#include <GL/glut.h>
#include "CGProject.h"
using namespace CGProject;

void ComputeNormal(float A[], float B[],float C[]) //Organized check, done
{
	/* Vector CA */
    float v1[3];
    v1[0] = C[0] - A[0];
    v1[1] = C[1] - A[1];
    v1[2] = C[2] - A[2];

	/* Vector BA */
    float v2[3];
    v2[0] = B[0] - A[0];
    v2[1] = B[1] - A[1];
    v2[2] = B[2] - A[2];

    /* Normalizing */
    float magv1 = sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
    float magv2 = sqrt(v2[0]*v2[0]+v2[1]*v2[1]+v2[2]*v2[2]);

	for(int i = 0 ; i < 3; i++)
	{
		v1[i] /= magv1;
		v2[i] /= magv2;
	}

    /* Normal Vector */
    float N[3];
    N[0] = -(v1[1]*v2[2] - v2[1]*v1[2]);
    N[1] = +(v1[0]*v2[2] - v2[0]*v1[2]);
    N[2] = -(v1[0]*v2[1] - v2[0]*v1[1]);
    glNormal3f(N[0],N[1],N[2]);
}

void simpleDisk(float radius, int slices) //Organized check, done
{
	/*This code is use to generate  simple Partial Disks */
    glDisable(GL_CULL_FACE);
	glPushMatrix();
	for(int i = 0 ; i < slices; i++)
	{
		float n = 2*M_PI*(float)i/slices;
		float m = 2*M_PI*(float)(i+1)/slices;
		glBegin(GL_TRIANGLE_STRIP);
			float A[3] = { 0.0f,0.0f,0.0f };
			float B[3] = { radius*cosf(n), 0.0f , radius*sinf(n)};
			float C[3] = { radius*cosf(m), 0.0f , radius*sinf(m)};
			ComputeNormal(A,B,C);
			glVertex3f(A[0],A[1],A[2]);
			glVertex3f(B[0],B[1],B[2]);
			glVertex3f(C[0],C[1],C[2]);
		glEnd();
	}
	glPopMatrix();
    glEnable(GL_CULL_FACE);
}

void RGB_Color(float R,float G,float B) //Organized check, done
{
    glColor3f(R/255.0f, G/255.0f, B/255.0f);
}

void MyBoundingBox::drawGrids() //Organized check, done
{
    int n = 5;
    float Cz,Cy,Cx;
    glLineWidth(0.1);
    glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);

        for(int i = 0 ; i <= n ; i++ )
            for(int j = 0; j <= n ; j++)
                for( int k = 0 ; k <= n ; k++)
                {
                    Cx = (float) i  / (float) n;
                    Cy = (float) j  / (float) n;
                    Cz = (float) k  / (float) n;
                    glVertex3f(Cx * x[6] + (1.0f - Cx) * x[0] ,y[0], Cz * z[7] + (1.0f - Cz) * z[0]);
                    glVertex3f(Cx * x[6] + (1.0f - Cx) * x[0] ,y[7], Cz*  z[7] + (1.0f - Cz) * z[0]);

                    glVertex3f(x[0] ,Cy * y[7] + (1.0f - Cy) * y[0], Cz * z[7] + (1.0f - Cz) * z[0]);
                    glVertex3f(x[6] ,Cy * y[7] + (1.0f - Cy) * y[0], Cz*  z[7] + (1.0f - Cz) * z[0]);

                    glVertex3f(Cx * x[6] + (1.0f - Cx) * x[0] ,Cy * y[7] + (1.0f - Cy) * y[0], z[0]);
                    glVertex3f(Cx * x[6] + (1.0f - Cx) * x[0] ,Cy * y[7] + (1.0f - Cy) * y[0], z[7]);
                }
    glEnd();
}

void St_Basils_Cathedral::drawCatholicCross(float R,float G,float B) //Organized check, done
{
    ///Yellow Gold = 250~255,225~232,0~11
    float cylinder_radius = 5.0f;
    float sphere_radius = 4.0f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	RGB_Color(255.0f,223.0f,11.0f); //yellow-gold
	gluQuadricDrawStyle(pObj, GLU_FILL);

	/* Base Cone , gold*/
	glPushMatrix();
		glTranslatef(0.0f,20.0f,0.0f);
		glRotatef(90.0f,1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 1.5f, cylinder_radius/1.75f, 10.0f, 12,4);
	glPopMatrix();

	/* Base Cone Connector to dome, customer colour, parameter dependant */
	glPushMatrix();
		glTranslatef(0.0f,10.0f,0.0f);
		glRotatef(90.0f,1.0f, 0.0f, 0.0f);
		RGB_Color(R,G,B);
		gluCylinder(pObj, cylinder_radius/1.75f, cylinder_radius, 10.0f, 12,4);
	glPopMatrix();

	/* Sphere, gold */
	glPushMatrix();
		RGB_Color(255.0f,223.0f,11.0f);
		glTranslatef(0.0f,22.0f,0.0f);
		gluSphere(pObj,sphere_radius, 12,6);
	glPopMatrix();

	/* Cross, gold */
	glPushMatrix();
		glTranslatef(0.0f,52.0f,0.0f);
		glRotatef(90.0f,1.0f, 0.0f, 0.0f);
		gluCylinder(pObj, 0.6f, 0.6, 30.0f, 6,2);

		glRotatef(90.0f,1.0f,0.0f,0.0f);
		glTranslatef(0.0f,8.0f,-7.0f);
		gluCylinder(pObj, 0.6f, 0.6, 14.0f, 6,2);

		glTranslatef(0.0f,-5.0f,+5.0f);
		gluCylinder(pObj, 0.6f, 0.6, 4.0f, 6,2);

		glTranslatef(0.0f,+18.0f,+0.5f);
		gluCylinder(pObj, 0.6f, 0.6, 3.0f, 6,2);
	glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawWhiteArcWindow() //Organized check, done
{
    float radius1 = 1.0f;
    float radius2 = 0.5f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

	/* White Frame */
	glPushMatrix();
		for(int i = 0; i < 2; i++)
		{
			///Arc Shape
			glPushMatrix();
				glTranslatef(0.0f,4.0f,0.0f);
				RGB_Color(255.0f,255.0f,255.0f);
				gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
			glPopMatrix();

			glBegin(GL_QUADS);
				///Right
				glVertex3f(1.0f,4.0f,0.0f);
				glVertex3f(0.5f,4.0f,0.0f);
				glVertex3f(0.5f,0.0f,0.0f);
				glVertex3f(1.0f,0.0f,0.0f);
				///Left
				glVertex3f(-1.0f,4.0f,0.0f);
				glVertex3f(-0.5f,4.0f,0.0f);
				glVertex3f(-0.5f,0.0f,0.0f);
				glVertex3f(-1.0f,0.0f,0.0f);
				///Base
				glVertex3f(-1.0f,0.5f,0.0f);
				glVertex3f(-1.0f,0.0f,0.0f);
				glVertex3f(+0.5f,0.0f,0.0f);
				glVertex3f(+0.5f,0.5f,0.0f);
			glEnd();
			glTranslatef(0.0f,0.0f,0.4f);
		}
	glPopMatrix();

	/* White Frame Sides*/
	glPushMatrix();
		glBegin(GL_QUADS);
			///Bottom
			glVertex3f(-1.0f,0.0f,+0.4f);
			glVertex3f(-1.0f,0.0f,0.0f);
			glVertex3f(+1.0f,0.0f,0.0f);
			glVertex3f(+1.0f,0.0f,+0.4f);
			///Side
			glVertex3f(-1.0f,0.0f,+0.4f);
			glVertex3f(-1.0f,4.0f,+0.4f);
			glVertex3f(-1.0f,4.0f,0.0f);
			glVertex3f(-1.0f,0.0f,0.0f);
			///Right
			glVertex3f(+1.0f,0.0f,+0.4f);
			glVertex3f(+1.0f,4.0f,+0.4f);
			glVertex3f(+1.0f,4.0f,0.0f);
			glVertex3f(+1.0f,0.0f,0.0f);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		float ini_x = -10.0f , ini_y = 40.0f ,ini_z = 0.0f;
		int slices = 16;
		glBegin(GL_QUAD_STRIP);
			for(int i = 0 ; i < (slices/2); i++)
			{
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices) +4.0f, ini_z);
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices) +4.0f, ini_z+0.4f);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices) +4.0f, ini_z);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices) +4.0f, ini_z+0.4f);
			}
		glEnd();
	glPopMatrix();

	/* Grey Frame */
	glBegin(GL_POLYGON);
		RGB_Color(208.0f,192.0f,179.0f); //grey
		glTranslatef(0.0f,0.0f,-1.2f);
		glVertex3f(0.5f,0.5f,0.0f);
		glVertex3f(0.5f,4.0f,0.0f);
		glVertex3f(-0.5f,4.0f,0.0f);
		glVertex3f(-0.5f,0.5f,0.0f);
	glEnd();

	glPushMatrix();
		glTranslatef(0.0f,4.0f,0.0f);
		gluPartialDisk(pObj,0.0f,radius2,8,1,270.00,180.0);
	glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawRedArcSurface_MediumDome3()
{
    float radius1 = 4.75f;
    float radius2 = 3.66f;
    float A[3],B[3],C[3];
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        glPushMatrix();
        {
            glTranslatef(-19.0f,0.0f,0.0f);
            for(int i = 0 ; i < 3 ; i++)
            {
                glTranslatef(+9.5f,0.0f,0.0f);
                glBegin(GL_QUADS);
                    //left
                    A[0] = -4.75f, A[1] = 0.0f , A[2] = -0.5f;
                    B[0] = -4.75f, B[1] = 6.0f , B[2] =  1.5f;
                    C[0] = -3.66f, C[1] = 0.0f , C[2] = -0.5f;
                    RGB_Color(224.0f,100.0f,0.0f);
                    ComputeNormal(C,B,A);
                    glVertex3f(-4.75f,0.0f,-0.5f); //1
                    glVertex3f(-4.75f,6.0f,1.5f); //2
                    glVertex3f(-3.66f,6.0f,1.5f);
                    glVertex3f(-3.66f,0.0f,-0.5f); //4

                    A[0] = -3.66f, A[1] = 6.0f , A[2] = 1.5f;
                    B[0] = -3.66f, B[1] = 0.0f , B[2] = -0.5f;
                    C[0] = -3.66f, C[1] = 6.0f , C[2] = -0.5f;
                    RGB_Color(224.0f,65.0f,0.0f);
                    ComputeNormal(A,B,C);
                    glVertex3f(-3.66f,6.0f,1.5f);
                    glVertex3f(-3.66f,0.0f,-0.5f);
                    glVertex3f(-3.66f,0.0f,-0.5f);
                    glVertex3f(-3.66f,6.0f,-0.5f);

                    glVertex3f(-3.66f,0.0f,-0.5f);
                    glVertex3f(-3.66f,6.0f,-0.5f);
                    glVertex3f(-4.75f,6.0f,-0.5f);
                    glVertex3f(-4.75f,0.0f,-0.5f);

                    A[0] = -4.75f, A[1] = 6.0f , A[2] = -0.5f;
                    B[0] = -4.75f, B[1] = 0.0f , B[2] = -0.5f;
                    C[0] = -4.75f, C[1] = 6.0f , C[2] = 1.5f;
                    RGB_Color(224.0f,100.0f,0.0f);
                    ComputeNormal(C,B,A);
                    glVertex3f(-4.75f,6.0f,-0.5f);
                    glVertex3f(-4.75f,0.0f,-0.5f);
                    glVertex3f(-4.75f,0.0f,-0.5f);
                    glVertex3f(-4.75f,6.0f,1.5f);
                glEnd();

                glBegin(GL_QUADS);
                    //right
                    A[0] = +3.66f, A[1] = 6.0f , A[2] = 1.5f;
                    B[0] = +3.66f, B[1] = 0.0f , B[2] = -0.5f;
                    C[0] = -4.75f, C[1] = 6.0f , C[2] = 1.5f;
                    RGB_Color(224.0f,100.0f,0.0f);
                    ComputeNormal(C,B,A);
                    glVertex3f(+3.66f,6.0f,1.5f);
                    glVertex3f(+3.66f,0.0f,-0.5f);
                    glVertex3f(+4.75f,0.0f,-0.5f);
                    glVertex3f(+4.75f,6.0f,1.5f);

                    A[0] = +3.66f, A[1] = 0.0f , A[2] = -0.5f;
                    B[0] = +3.66f, B[1] = 6.0f , B[2] = -0.5f;
                    C[0] = +3.66f, C[1] = 6.0f , C[2] = -0.5f;

                    RGB_Color(224.0f,65.0f,0.0f);
                    ComputeNormal(A,B,C);
                    glVertex3f(+3.66f,0.0f,-0.5f);
                    glVertex3f(+3.66f,6.0f,-0.5f);
                    glVertex3f(+3.66f,6.0f,1.5f);
                    glVertex3f(+3.66f,0.0f,-0.5f);

                    glVertex3f(+4.75f,6.0f,-0.5f);
                    glVertex3f(+4.75f,0.0f,-0.5f);
                    glVertex3f(+3.66f,0.0f,-0.5f);
                    glVertex3f(+3.66f,6.0f,-0.5f);

                    A[0] = +4.75f, A[1] = 0.0f , A[2] = -0.5f;
                    B[0] = +4.75f, B[1] = 6.0f , B[2] = 1.5f;
                    C[0] = +4.75f, C[1] = 6.0f , C[2] = -0.5f;
                    ComputeNormal(C,B,A);
                    glVertex3f(+4.75f,0.0f,-0.5f);
                    glVertex3f(+4.75f,6.0f,1.5f);
                    glVertex3f(+4.75f,6.0f,-0.5f);
                    glVertex3f(+4.75f,0.0f,-0.5f);
                glEnd();

                glBegin(GL_QUADS);
                    A[0] = -3.66f, A[1] = 0.0f , A[2] = -0.5f;
                    B[0] = -3.66f, B[1] = 6.0f , B[2] = -0.0f;
                    C[0] =  3.66f, C[1] = 0.0f , C[2] = -0.5f;
                    ComputeNormal(C,B,A);
                    RGB_Color(224.0f,100.0f,0.0f);
                    glVertex3f(-3.66f,0.0f,-0.5f); //1
                    glVertex3f(-3.66f,6.0f,0.0f); //2
                    glVertex3f(+3.66f,6.0f,0.0f);
                    glVertex3f(+3.66f,0.0f,-0.5f); //4

                glEnd();


            }

            glTranslatef(-28.5f,6.0f,0.0f);
            glPushMatrix();
            for(int i = 0 ; i < 3; i++)
            {
                glTranslatef(9.5f,0.0f,0.0f);
                glPushMatrix();
                {
                     /*Faces*/
                    ///Red Partial Disk
                    glPushMatrix();
                        RGB_Color(224.0f,100.0f,0.0f); //brighter red
                        glTranslatef(0.0f,0.0f,1.5f);
                        gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
                    glPopMatrix();

                    ///Red Partial Disk, smaller one
                    glPushMatrix();
                        gluPartialDisk(pObj,0,radius1*0.85,8,1,270.00,180.0);
                    glPopMatrix();

                    ///Quad Strip
                    glPushMatrix();
                        RGB_Color(224.0f,65.0f,0.0f); //red
                        glBegin(GL_QUAD_STRIP);
                            int slices = 16;
                            for(int i = 0 ; i < (slices/2); i++)
                            {
                                glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
                                glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), -0.1f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
                                glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), -0.1f);
                            }
                        glEnd();
                    glPopMatrix();

                    glPushMatrix();
                        RGB_Color(224.0f,65.0f,0.0f); //red
                        glBegin(GL_QUAD_STRIP);
                            float radius3 = radius2*0.85;
                            float radius4 = radius1*0.70;
                            slices = 16;
                            for(int i = 0 ; i < (slices/2); i++)
                            {
                                glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), -1.5f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
                                glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), -1.5f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
                            }
                        glEnd();
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawWhiteArc_CenterDome()
{
    float radius1 = 4.75f;
    float radius2 = 3.66f;
    float A[3],B[3],C[3];
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        glPushMatrix();
        {
            glTranslatef(-4.25f,5.0f,0.0f);
            glPushMatrix();
            for(int i = 0 ; i < 3; i++)
            {
                glTranslatef(9.25f,0.0f,0.0f);
                glPushMatrix();
                {
                     /*Faces*/
                    ///Red Partial Disk
                    glPushMatrix();
                        RGB_Color(255,255,255);
                        glTranslatef(0.0f,0.0f,1.5f);
                        gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
                    glPopMatrix();

                    glPushMatrix();
                        RGB_Color(224,100,0);
                        gluPartialDisk(pObj,radius2+0.1f,radius1*1.25,8,1,270.00,180.0);
                    glPopMatrix();


                    ///Quad Strip
                    glPushMatrix();
                        RGB_Color(255,255,255);
                        glBegin(GL_QUAD_STRIP);
                            int slices = 16;
                            for(int i = 0 ; i < (slices/2); i++)
                            {
                                glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
                                glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), -0.1f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
                                glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), -0.1f);
                            }
                        glEnd();
                    glPopMatrix();

                    glPushMatrix();
                        RGB_Color(255,255,255);
                        glBegin(GL_QUAD_STRIP);
                            float radius3 = radius2*0.85;
                            float radius4 = radius1*0.70;
                            slices = 16;
                            for(int i = 0 ; i < (slices/2); i++)
                            {
                                glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), -1.5f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
                                glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), -1.5f);
                                glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
                            }
                        glEnd();
                    glPopMatrix();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    glPopMatrix();

    glBegin(GL_QUADS);
       // glVertex3f();

    glEnd();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawRedArcSurface_CenterDome()
{
    float A[3],B[3],C[3];
    float d = 15.0f;
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    //Pillar
    glPushMatrix();
    {
        scaleObjects(0.5);
        glTranslatef(-d,0,0);
        for(int i = 0; i<4;i++)
        {
            glTranslatef(17.4,0,0);
            glPushMatrix();
            {
                glRotatef(270,1,0,0);
                RGB_Color(255,100,0);
                gluCylinder(pObj,4.0f,4.0f,10.0f,6,1);

                RGB_Color(255,255,255);
                glTranslatef(0,0,10);
                gluCylinder(pObj,4.0f,3.5f,1.0f,6,1);

                RGB_Color(255,100,0);
                glTranslatef(0,0,1);
                gluCylinder(pObj,3.5f,3.0f,3.5f,6,1);

                RGB_Color(255,255,255);
                glTranslatef(0,0,3.5);
                gluCylinder(pObj,3.0f,3.3f,0.25f,6,1);

                glTranslatef(0,0,0.25);
                gluCylinder(pObj,3.3f,3.0f,0.25f,6,1);

                RGB_Color(255,100,0);
                glTranslatef(0,0,.25);
                gluCylinder(pObj,3.0f,3.0f,10.0f,6,1);

                RGB_Color(255,255,255);
                glTranslatef(0,0,10);
                gluCylinder(pObj,3.0f,3.5f,0.25f,6,1);

                glTranslatef(0,0,0.25);
                gluCylinder(pObj,3.5f,3.2f,0.25f,6,1);

                glRotatef(270,1,0,0);
                simpleDisk(3.2f,8);
                glDisable(GL_CULL_FACE);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();

    //Face
    glPushMatrix();
    {
        glBegin(GL_QUADS);
        {
            //left
            A[0] = 1.3f, A[1] = 0.0f;
            B[0] = 1.3f, B[1] = 5.0f;
            C[0] = 10.3f,C[1] = 0.0f;
            A[2] = B[2] = C[2] = 2.0f;
            RGB_Color(223,100,0);
            ComputeNormal(C,B,A);
            glVertex3f(+1.3f,0.0f,2.0f);
            glVertex3f(+1.3f,5.0f,2.0f);
            glVertex3f(+10.3f,5.0f,2.0f);
            glVertex3f(+10.3f,0.0f,2.0f);

            A[0] = 1.3f, A[1] = 5.0f;
            B[0] = 1.3f, B[1] = 5.0f;
            C[0] = 10.3f,C[1] = 5.0f;
            A[2] = C[2] = 2.0f, B[2] = -2.0f;
            ComputeNormal(C,B,A);
            glVertex3f(+1.3f,5.0f,2.0f);
            glVertex3f(+1.3f,5.0f,-2.0f);
            glVertex3f(+10.3f,5.0f,-2.0f);
            glVertex3f(+10.3f,5.0f,2.0f);

            A[0] = 3.3f, A[1] = 1.0f;
            B[0] = 3.3f, B[1] = 4.0f;
            C[0] = 8.3f, C[1] = 1.0f;
            A[2] = B[2] = C[2] = 2.1f;
            RGB_Color(255,255,255);
            ComputeNormal(C,B,A);
            glVertex3f(+3.3f,1.0f,2.1f);
            glVertex3f(+3.3f,4.0f,2.1f);
            glVertex3f(+8.3f,4.0f,2.1f);
            glVertex3f(+8.3f,1.0f,2.1f);

            A[0] = 3.8f, A[1] = 1.5f;
            B[0] = 3.8f, B[1] = 3.5f;
            C[0] = 7.8f, C[1] = 1.5f;
            A[2] = B[2] = C[2] = 2.2f;
            RGB_Color(223,100,0);
            ComputeNormal(C,B,A);
            glVertex3f(+3.8f,1.5f,2.2f);
            glVertex3f(+3.8f,3.5f,2.2f);
            glVertex3f(+7.8f,3.5f,2.2f);
            glVertex3f(+7.8f,1.5f,2.2f);

            //Right
            A[0] = 18.3f, A[1] = 0.0f;
            B[0] = 18.3f, B[1] = 5.0f;
            C[0] = 27.3f, C[1] = 0.0f;
            A[2] = B[2] = C[2] = 2.0f;
            RGB_Color(223,100,0);
            ComputeNormal(C,B,A);
            glVertex3f(+18.3f,0.0f,2.0f);
            glVertex3f(+18.3f,5.0f,2.0f);
            glVertex3f(+27.3f,5.0f,2.0f);
            glVertex3f(+27.3f,0.0f,2.0f);

            A[0] = 18.3f, A[1] = 5.0f;
            B[0] = 18.3f, B[1] = 5.0f;
            C[0] = 27.3f,C[1] = 5.0f;
            A[2] = C[2] = 2.0f; B[2] = -2.0f;
            ComputeNormal(C,B,A);
            glVertex3f(+18.3f,5.0f,2.0f);
            glVertex3f(+18.3f,5.0f,-2.0f);
            glVertex3f(+27.3f,5.0f,-2.0f);
            glVertex3f(+27.3f,5.0f,2.0f);

            A[0] = 20.3f, A[1] = 1.0f;
            B[0] = 20.3f, B[1] = 4.0f;
            C[0] = 25.3f, C[1] = 1.0f;
            A[2] = B[2] = C[2] = 2.1f;
            RGB_Color(255,255,255);
            ComputeNormal(C,B,A);
            glVertex3f(+20.3f,1.0f,2.1f);
            glVertex3f(+20.3f,4.0f,2.1f);
            glVertex3f(+25.3f,4.0f,2.1f);
            glVertex3f(+25.3f,1.0f,2.1f);


            A[0] = 20.8f, A[1] = 1.5f;
            B[0] = 20.8f, B[1] = 3.5f;
            C[0] = 24.8f, C[1] = 1.5f;
            A[2] = B[2] = C[2] = 2.2f;
            RGB_Color(223,100,0);
            ComputeNormal(C,B,A);
            glVertex3f(+20.8f,1.5f,2.2f);
            glVertex3f(+20.8f,3.5f,2.2f);
            glVertex3f(+24.8f,3.5f,2.2f);
            glVertex3f(+24.8f,1.5f,2.2f);
        }
        glEnd();

    }
    glPopMatrix();

    //UpperPart
    glPushMatrix();
    {
        glTranslatef(0.0f,7.5f,0.0f);
        drawWhiteArc_CenterDome();
    }
    glPopMatrix();


    glDisable(GL_CULL_FACE);
    gluDeleteQuadric(pObj);
}

void St_Basils_Cathedral::drawRedTriangle_CenterDome()
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    float A[3],B[3],C[3];
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glDisable(GL_CULL_FACE);

   glPushMatrix();
        /* Surface and Frames */
        ///frame
        glPushMatrix();
        glBegin(GL_TRIANGLES);
            RGB_Color(224.0f,100.0f,0.0f); //brighter red
            A[0] = -9.9f , A[1] = 0.0f, A[2] = 0.0f;
            B[0] = 9.9f  , B[1] = 10.0f, B[2] = 0.0f;
            C[1] = 35.0f , C[1] = 0.0f, C[2] = 0.0f;
            ComputeNormal(C,B,A);
            glVertex3f(A[0],A[1],A[2]);
            glVertex3f(0.0f,B[1],B[2]);
            glVertex3f(9.9f,C[1],C[2]);
        glEnd();
        glPopMatrix();
        ///Left Italic white frame
        glPushMatrix();
            RGB_Color(255.0f,255.0f,255.0f); //white
            glRotatef(270,1,0,0); //flip up
            glTranslatef(-9.0f,-0.3f,0.0f);
            glRotatef(42,0,1,0);
            gluCylinder(pObj,0.3f,0.3f,14.0f,6,1);
        glPopMatrix();

        ///Right Italic white frame
        glPushMatrix();
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+9.0f,-0.3f,0.0f);
            glRotatef(-42,0,1,0);
            gluCylinder(pObj,0.3f,0.3f,14.0f,6,1);
        glPopMatrix();

        /* Roof */
        ///left
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glRotatef(270,1,0,0); //flip up
            glTranslatef(-9.8f,-0.6f,0.0f);
            glRotatef(42,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,15.0f,6,1);
        glPopMatrix();

        ///right
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+9.8f,-0.6f,0.0f);
            glRotatef(-42,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,15.0f,6,1);
        glPopMatrix();

        glBegin(GL_QUADS);
            RGB_Color(0,184,150);
            A[0] = -10.0f , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 11.0f, B[2] = 1.1f;
            C[0] = 0.0f   , C[1] = 11.0f, C[2] = -5.1f;
            ComputeNormal(C,A,B);
            glVertex3f(-10.0f,0.0f,1.1f);
            glVertex3f(0.0f,11.0f,1.1f);
            glVertex3f(0.0f,11.0f,-5.1f);
            glVertex3f(-10.0f,0.0f,-5.1f);

            A[0] = +10.0f , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 11.0f, B[2] = 1.1f;
            C[0] = +10.0f   , C[1] = 0.0f, C[2] = -5.1f;

			ComputeNormal(C,B,A);
            glVertex3f(+10.0f,0.0f,1.1f);
            glVertex3f(0.0f,11.0f,1.1f);
            glVertex3f(0.0f,11.0f,-5.1f);
            glVertex3f(+10.0f,0.0f,-5.1f);
        glEnd();
    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void St_Basils_Cathedral::drawSemiCylinder_SmallDome() //Organized check, done
{
    float radius1 = 10.0f;
    float radius2 = 8.5f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

	/*Faces*/
	///Red Partial Disk
	glPushMatrix();
		glTranslatef(0.0f,0.0f,1.5f);
		RGB_Color(224.0f,100.0f,0.0f); //brighter red
		gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
	glPopMatrix();

	///White Ring Disk
	glPushMatrix();
		RGB_Color(255.0f,255.0f,255.0f); //white
		gluPartialDisk(pObj,radius2*0.85,radius1*0.85,8,1,270.00,180.0);
	glPopMatrix();

	///Inner Red Disk
	glPushMatrix();
		RGB_Color(224.0f,65.0f,0.0f); //red
		gluPartialDisk(pObj,0,radius1*0.70,8,1,270.00,180.0);
	glPopMatrix();

	/* Quad Strip */
	glPushMatrix();
		int slices = 16;
		RGB_Color(1.0f,160.0f,138.0f);	//grey
		glBegin(GL_QUAD_STRIP);
			for(int i = 0 ; i < (slices/2); i++)
			{
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
				glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), -0.1f);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
				glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), -0.1f);
			}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		float radius3 = radius2*0.85;
		float radius4 = radius1*0.70;
		slices = 16;
		RGB_Color(1.0f,160.0f,138.0f);
		glBegin(GL_QUAD_STRIP);
			for(int i = 0 ; i < (slices/2); i++)
			{
				glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), -5.5f);
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
				glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), -5.5f);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
			}
		glEnd();
	glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawSemiCylinder_MediumDome1() //Organized check, done
{
    float radius1 = 11.0f;
    float radius2 = 8.5f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        /*Faces*/
        ///Red Partial Disk
        glPushMatrix();
			RGB_Color(224.0f,100.0f,0.0f); //brighter red
            glTranslatef(0.0f,0.0f,1.5f);
            gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
        glPopMatrix();

        ///White Partial Disk
        glPushMatrix();
            RGB_Color(255.0f,255.0f,255.0f); //white
            gluPartialDisk(pObj,0,radius1*0.85,8,1,270.00,180.0);
        glPopMatrix();

        /* Quad Strip */
        glPushMatrix();
			int slices = 16;
            RGB_Color(224.0f,65.0f,0.0f); //red
            glBegin(GL_QUAD_STRIP);
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), -0.1f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), -0.1f);
				}
            glEnd();
        glPopMatrix();

        glPushMatrix();
			float radius3 = radius2*0.85;
            float radius4 = radius1*0.70;
			slices = 16;
            RGB_Color(0.0f,177.0f,149.0f);
            glBegin(GL_QUAD_STRIP);
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), -5.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
					glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), -5.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
				}
            glEnd();
        glPopMatrix();

		/* Red Tile */
        glPushMatrix();
			//Red Back Ground
            glBegin(GL_QUAD_STRIP);
                RGB_Color(224.0f,65.0f,0.0f); //red
                glVertex3f(-3.0f,0.0f,0.1f);
                glVertex3f(-3.0f,6.0f,0.1f);
                glVertex3f(+3.0f,0.0f,0.1f);
                glVertex3f(+3.0f,6.0f,0.1f);
            glEnd();
            ///front
            glBegin(GL_QUAD_STRIP);
				RGB_Color(255,200,200); //white
                glVertex3f(-2.0f,1.0f,1.0f);
                glVertex3f(-2.0f,5.0f,1.0f);
                glVertex3f(+2.0f,1.0f,1.0f);
                glVertex3f(+2.00f,5.0f,1.0f);
            glEnd();
            ///back
            glBegin(GL_QUAD_STRIP);
                glVertex3f(-2.0f,1.0f,0.2f);
                glVertex3f(-2.0f,5.0f,0.2f);
                glVertex3f(+2.0f,1.0f,0.2f);
                glVertex3f(+2.0f,5.0f,0.2f);
            glEnd();
			///sides
            glBegin(GL_QUAD_STRIP);
                glVertex3f(-2.0f,1.0f,1.0f);
                glVertex3f(-2.0f,1.0f,0.2f);
                glVertex3f(-2.0f,5.0f,1.0f);
                glVertex3f(-2.0f,5.0f,0.2f);
                glVertex3f(+2.0f,1.0f,1.0f);
                glVertex3f(+2.0f,1.0f,0.2f);
                glVertex3f(+2.0f,5.0f,1.0f);
                glVertex3f(+2.0f,5.0f,0.2f);
                glVertex3f(-2.0f,1.0f,1.0f);
                glVertex3f(-2.0f,1.0f,0.2f);
            glEnd();
        glPopMatrix();

        /* Surface Details */
        glPushMatrix();
			RGB_Color(190,9,2);
            glTranslatef(0.0f,3.0f,1.2f);
            glRotatef(270.0f,1,0,0);
            simpleDisk(1.0f,8);

			RGB_Color(133,155,91);
            glTranslatef(0.0f,0.1f,0.0f);
            simpleDisk(1.5f,8);

            RGB_Color(237.0f,218.0f,142.0f);
            glTranslatef(1.6f,-0.1f,0.0f);simpleDisk(0.3f,8);
            glTranslatef(-3.2f,0.0f,0.0f);simpleDisk(0.3f,8);
            glTranslatef(+1.6f,0.0f,1.6f);simpleDisk(0.3f,8);
            glTranslatef(0.0f,0.0f,-3.2f);simpleDisk(0.3f,8);
            glTranslatef(+1.6f,0.0f,0.0f);simpleDisk(0.3f,8);
            glTranslatef(0.0f,0.0f,3.2f);simpleDisk(0.3f,8);
            glTranslatef(-3.2,0.0f,0.0f);simpleDisk(0.3f,8);
            glTranslatef(0.0f,0.0f,-3.2f);simpleDisk(0.3f,8);
        glPopMatrix();

        glPushMatrix();
            RGB_Color(114,40,3);
            glTranslatef(-0.7f,1.2f,1.3f);
            glRotatef(270.0f,1,0,0);
            glPushMatrix();
                float r = 1.4f;
                for(int i = 0 ; i < 8;i++)
                {
                    float n = 2*M_PI*(float)i/8;
                    glTranslatef(r*cos(n),0.0f,r*sin(n));
                    simpleDisk(0.1f,8);

                }
            glPopMatrix();
            simpleDisk(0.1f,8);
        glPopMatrix();
    glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawSemiCylinder_MediumDome2() //Organized check, done
{
    float radius1 = 11.0f;
    float radius2 = 8.5f;
    float ini_x = 0.0f , ini_y = 0.0 ,ini_z = 0.0f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        /*Faces*/
        ///Red Partial Disk
        glPushMatrix();
			RGB_Color(224.0f,100.0f,0.0f); //brighter red
            glTranslatef(0.0f,0.0f,1.5f);
            gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
        glPopMatrix();

        ///White Partial Disk
        glPushMatrix();
            RGB_Color(255.0f,255.0f,255.0f); //white
            gluPartialDisk(pObj,0,radius1*0.85,8,1,270.00,180.0);
        glPopMatrix();

        /* Quad Strip */
        glPushMatrix();
			RGB_Color(224.0f,65.0f,0.0f);
			glBegin(GL_QUAD_STRIP);
				int slices = 16;
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), ini_z+1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), ini_z-0.1f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), ini_z+1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), ini_z-0.1f);
				}
			glEnd();
        glPopMatrix();

        glPushMatrix();
            RGB_Color(0.0f,177.0f,149.0f);
            glBegin(GL_QUAD_STRIP);
				float radius3 = radius2*0.85;
				float radius4 = radius1*0.70;
				slices = 16;
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), ini_z-5.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), ini_z+1.5f);
					glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), ini_z-5.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), ini_z+1.5f);
				}
            glEnd();
        glPopMatrix();
    glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawSemiCylinder_MediumDome2_b() //Organized check, done
{
    float radius1 = 3.5f;
    float radius2 = 2.7f;
    float ini_x = 0.0f , ini_y = 0.0 ,ini_z = 0.0f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        /*Faces*/
        ///Red Partial Disk
        glPushMatrix();
			RGB_Color(224.0f,100.0f,0.0f); //brighter red
            glTranslatef(0.0f,0.0f,1.5f);
            gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
        glPopMatrix();

        ///Red Partial Disk, smaller one
        glPushMatrix();
            gluPartialDisk(pObj,0,radius1*0.85,8,1,270.00,180.0);
        glPopMatrix();

        ///Quad Strip
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glBegin(GL_QUAD_STRIP);
				int slices = 16;
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), ini_z+1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), ini_z-0.1f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), ini_z+1.5f);
					glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), ini_z-0.1f);
				}
            glEnd();
        glPopMatrix();

        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glBegin(GL_QUAD_STRIP);
				float radius3 = radius2*0.85;
				float radius4 = radius1*0.70;
				slices = 16;
				for(int i = 0 ; i < (slices/2); i++)
				{
					glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), ini_z-1.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), ini_z+1.5f);
					glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), ini_z-1.5f);
					glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), ini_z+1.5f);
				}
            glEnd();
        glPopMatrix();

        ///Rectangle Basement
        glPushMatrix();
            glBegin(GL_QUADS);
                glVertex3f(-3.5f,0.0f,0.0f);
                glVertex3f(+3.5f,0.0f,0.0f);
                glVertex3f(+3.5f,0.0f,1.5f);
                glVertex3f(-3.5f,0.0f,1.5f);
            glEnd();
        glPopMatrix();

    glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawSemiCylinder_MediumDome3()
{
    float radius1 = 10.0f;
    float radius2 = 8.5f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

	/*Faces*/
	///Red Partial Disk
	glPushMatrix();
		glTranslatef(0.0f,0.0f,1.5f);
		RGB_Color(224.0f,100.0f,0.0f); //brighter red
		gluPartialDisk(pObj,radius2,radius1,8,1,270.00,180.0);
	glPopMatrix();

	///White Ring Disk
	glPushMatrix();
		RGB_Color(255.0f,255.0f,255.0f); //white
		gluPartialDisk(pObj,radius2*0.85,radius1*0.85,8,1,270.00,180.0);
	glPopMatrix();

	///Inner Red Disk
	glPushMatrix();
		RGB_Color(224.0f,65.0f,0.0f); //red
		gluPartialDisk(pObj,0,radius1*0.70,8,1,270.00,180.0);
	glPopMatrix();

	/* Quad Strip */
	glPushMatrix();
		int slices = 16;
		RGB_Color(1.0f,160.0f,138.0f);	//grey
		glBegin(GL_QUAD_STRIP);
			for(int i = 0 ; i < (slices/2); i++)
			{
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
				glVertex3f(radius2*cosf(2*M_PI*(float)i/slices), radius2*sinf(2*M_PI*(float)i/slices), -0.1f);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
				glVertex3f(radius2*cosf(2*M_PI*(float)(i+1)/slices), radius2*sinf(2*M_PI*(float)(i+1)/slices), -0.1f);
			}
		glEnd();
	glPopMatrix();

	glPushMatrix();
		float radius3 = radius2*0.85;
		float radius4 = radius1*0.70;
		slices = 16;
		RGB_Color(1.0f,160.0f,138.0f);
		glBegin(GL_QUAD_STRIP);
			for(int i = 0 ; i < (slices/2); i++)
			{
				glVertex3f(radius3*cosf(2*M_PI*(float)i/slices), radius3*sinf(2*M_PI*(float)i/slices), -5.5f);
				glVertex3f(radius1*cosf(2*M_PI*(float)i/slices), radius1*sinf(2*M_PI*(float)i/slices), +1.5f);
				glVertex3f(radius3*cosf(2*M_PI*(float)(i+1)/slices), radius3*sinf(2*M_PI*(float)(i+1)/slices), -5.5f);
				glVertex3f(radius1*cosf(2*M_PI*(float)(i+1)/slices), radius1*sinf(2*M_PI*(float)(i+1)/slices), +1.5f);
			}
		glEnd();
	glPopMatrix();

	glPushMatrix();
        RGB_Color(200,200,200);
        glTranslatef(0.0f,3.5f,0.1f);
        glRotatef(-90,1,0,0);
        simpleDisk(3,16);
	glPopMatrix();


	glPushMatrix();
        RGB_Color(25,25,25);
        glTranslatef(0.0f,3.5f,0.2f);
        glRotatef(-90,1,0,0);
        simpleDisk(2.5,16);
	glPopMatrix();

	glPushMatrix();
        RGB_Color(25,25,25);
        glRotatef(-90,1,0,0);
        for(int i = 0; i < 4; i++)
        {
            glRotatef(20.0f,0,1,0);
            glPushMatrix();
            glTranslatef(0.0f,-0.15f,7.5f);
            simpleDisk(0.5,8);
            glPopMatrix();
        }
	glPopMatrix();

	glPushMatrix();
        RGB_Color(25,25,25);
        glRotatef(-90,1,0,0);
        for(int i = 0; i < 4; i++)
        {
            glRotatef(-20.0f,0,1,0);
            glPushMatrix();
            glTranslatef(0.0f,-0.15f,7.5f);
            simpleDisk(0.5,8);
            glPopMatrix();
        }
	glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawTriangleBase_MediumDome() //Organized check, done,may have lighting issues
{
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    float A[3],B[3],C[3];
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glPushMatrix();
        /* Surface and Frames */
        ///frame
        glBegin(GL_TRIANGLES);
            RGB_Color(224.0f,100.0f,0.0f); //brighter red
            A[0] = -9.9f , A[1] = 0.0f, A[2] = 0.0f;
            B[0] = 9.9f  , B[1] = 35.0f, B[2] = 0.0f;
            C[1] = 35.0f , C[1] = 0.0f, C[2] = 0.0f;
            ComputeNormal(C,B,A);
            glVertex3f(-9.9f,0.0f,0.0f);
            glVertex3f(0.0f,35.0f,0.0f);
            glVertex3f(+9.9,0.0f,0.0f);
        glEnd();

        ///Left Italic white frame
        glPushMatrix();
            RGB_Color(255.0f,255.0f,255.0f); //white
            glRotatef(270,1,0,0); //flip up
            glTranslatef(-9.0f,-0.3f,0.0f);
            glRotatef(16,0,1,0);
            gluCylinder(pObj,0.3f,0.3f,34.0f,6,1);
        glPopMatrix();

        ///Right Italic white frame
        glPushMatrix();
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+9.0f,-0.3f,0.0f);
            glRotatef(-16,0,1,0);
            gluCylinder(pObj,0.3f,0.3f,34.0f,6,1);
        glPopMatrix();

        ///Middle White frames
        glPushMatrix();
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+4.0f,-0.4f,0.0f);
            gluCylinder(pObj,0.6f,0.6f,18.5f,6,1);
            glTranslatef(-8.0f,0.0f,0.0f);
            gluCylinder(pObj,0.6f,0.6f,18.5f,6,1);
            glTranslatef(8.5f,0.0f,18.5f);
            glRotatef(270.0f,0,1,0);
            gluCylinder(pObj,0.6f,0.6f,8.5f,6,1);
        glPopMatrix();


		///Rectangle
        glBegin(GL_QUADS);
			RGB_Color(255.0f,255.0f,255.0f);
            glTranslatef(0.0f,0.0f,-1.2f);
            A[0] = 2.5f    , A[1] = 0.0f , A[2] = 0.1f;
            B[0] = 2.5f    , B[1] = 13.0f, B[2] = 0.1f;
            C[0] = -2.5f   , C[1] = 13.0f, C[2] = 0.1f;
            ComputeNormal(A,B,C);
            glVertex3f(2.5f,0.0f,0.1f);
            glVertex3f(2.5f,13.0f,0.1f);
            glVertex3f(-2.5f,13.0f,0.1f);
            glVertex3f(-2.5f,0.0f,0.1f);
        glEnd();

		///Arc Shape, Partial Disk
        glPushMatrix();
            glTranslatef(0.0f,13.0f,0.1f);
            gluPartialDisk(pObj,0.0f,2.5f,8,1,270.00,180.0);
        glPopMatrix();

        /* Roof */
        ///left
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glRotatef(270,1,0,0); //flip up
            glTranslatef(-9.8f,-0.6f,0.0f);
            glRotatef(16,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,36.0f,6,1);
        glPopMatrix();

        ///right
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f); //red
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+9.8f,-0.6f,0.0f);
            glRotatef(-16,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,36.0f,6,1);
        glPopMatrix();

        glBegin(GL_QUADS);
            A[0] = -10.0f , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 36.0f, B[2] = 1.1f;
            C[0] = 0.0f   , C[1] = 36.0f, C[2] = -5.1f;
            ComputeNormal(B,A,C);
            glVertex3f(-10.0f,0.0f,1.1f);
            glVertex3f(0.0f,36.0f,1.1f);
            glVertex3f(0.0f,36.0f,-5.1f);
            glVertex3f(-10.0f,0.0f,-5.1f);

            A[0] = +10.0f , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 36.0f, B[2] = 1.1f;
            C[0] = +10.0f   , C[1] = 0.0f, C[2] = -5.1f;

			ComputeNormal(A,B,C);
            glVertex3f(+10.0f,0.0f,1.1f);
            glVertex3f(0.0f,36.0f,1.1f);
            glVertex3f(0.0f,36.0f,-5.1f);
            glVertex3f(+10.0f,0.0f,-5.1f);
        glEnd();
    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void St_Basils_Cathedral::drawTriangleTop_MediumDome() //Organized check, done,may have lighting issues
{
    glDisable(GL_CULL_FACE);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    float A[3],B[3],C[3];
    gluQuadricDrawStyle(pObj, GLU_FILL);
    glPushMatrix();

        ///front-left
        glBegin(GL_TRIANGLES);
            RGB_Color(224.0f,100.0f,0.0f);
            A[0] = -13.5f  , A[1] = 0.0f , A[2] = 0.0f;
            B[0] = 0.0f   , B[1] = +3.0f , B[2] = 8.5f;
            C[0] = 0.0f   , C[1] = 25.0f, C[2] = 0.0f;
            ComputeNormal(A,B,C);
            glVertex3f(A[0],A[1],A[2]);
            glVertex3f(B[0],B[1],B[2]);
            glVertex3f(C[0],C[1],C[2]);
        glEnd();
        ///front-right
        glBegin(GL_TRIANGLES);
            RGB_Color(224.0f,100.0f,0.0f);
            A[0] = 13.5f   , A[1] = 0.0f , A[2] = 0.0f;
            B[0] = 0.0f   , B[1] = +3.0f , B[2] = 8.5f;
            C[0] = 0.0f   , C[1] = 25.0f, C[2] = 0.0f;
            ComputeNormal(C,B,A);
            glVertex3f(A[0],A[1],A[2]);
            glVertex3f(B[0],B[1],B[2]);
            glVertex3f(C[0],C[1],C[2]);
        glEnd();
        ///front-left-grey
        glBegin(GL_TRIANGLES);
            RGB_Color(0.0f,180.0f,153.0f);
            A[0] = -13.5f  , A[1] = 0.0f , A[2] = 0.0f;
            B[0] = 0.0f   , B[1] = +3.0f , B[2] = 8.5f;
            C[0] = 0.0f   , C[1] = -7.0f, C[2] = 7.0f;
            ComputeNormal(C,B,A);
            glVertex3f(A[0],A[1],A[2]);
            glVertex3f(B[0],B[1],B[2]);
            glVertex3f(C[0],C[1],C[2]);
        glEnd();

        ///front-right-grey
        glBegin(GL_TRIANGLES);
            RGB_Color(0.0f,180.0f,153.0f);
            A[0] = +13.5f , A[1] = 0.0f , A[2] = 0.0f;
            B[0] = 0.0f   , B[1] = +3.0f , B[2] = 8.5f;
            C[0] = 0.0f   , C[1] = -7.0f, C[2] = 7.0f;
            ComputeNormal(A,B,C);
            glVertex3f(A[0],A[1],A[2]);
            glVertex3f(B[0],B[1],B[2]);
            glVertex3f(C[0],C[1],C[2]);
        glEnd();

       ///left
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f);
            glRotatef(270,1,0,0); //flip up
            glTranslatef(-13.5f,-0.6f,0.0f);
            glRotatef(27.5,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,29.4f,6,1);
        glPopMatrix();

        ///right
        glPushMatrix();
            RGB_Color(224.0f,65.0f,0.0f);
            glRotatef(270,1,0,0); //flip up
            glTranslatef(+13.5f,-0.6f,0.0f);
            glRotatef(-27.5f,0,1,0);
            gluCylinder(pObj,0.5f,0.5f,29.4f,6,1);
        glPopMatrix();

        glBegin(GL_QUADS);
            A[0] = -13.5f , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 25.0f, B[2] = 1.1f;
            C[0] = 0.0f   , C[1] = 25.0f, C[2] = -5.1f;

			ComputeNormal(B,A,C);
			glVertex3f(A[0],0.0f,1.1f);
            glVertex3f(0.0f,B[1],1.1f);
            glVertex3f(0.0f,B[1],-5.1f);
            glVertex3f(A[0],0.0f,-5.1f);

            A[0] = 13.5f  , A[1] = 0.0f , A[2] = 1.1f;
            B[0] = 0.0f   , B[1] = 25.0f, B[2] = 1.1f;
            C[0] = 13.5f  , C[1] = 25.0f, C[2] = -5.1f;

			ComputeNormal(A,B,C);
			glVertex3f(A[0],0.0f,1.1f);
            glVertex3f(0.0f,B[1],1.1f);
            glVertex3f(0.0f,B[1],-5.1f);
            glVertex3f(A[0],0.0f,-5.1f);
        glEnd();
    glPopMatrix();
    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_1() //green spiral right
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;

    /* Base */
    glPushMatrix();
		RGB_Color(0.0f,109.0f,51.0f);
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,16,1); // Base
    glPopMatrix();

    /* Shape */
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=0; j< 7; j++)
            {
                glBegin(GL_TRIANGLE_STRIP);
					for(int i = 0 ; i <= slices;i++)
					{
						if(flipflop) RGB_Color(89.0f,105.0f,42.0f);
						else RGB_Color(188.0f,181.0f,127.0f);
						float theta = (float) i/slices *2*M_PI;
						float theta_next = (float) (i+1)/slices *2*M_PI;
						float theta_next_2 = (float) (i+2)/slices *2*M_PI;

						/* Normal Calculations */

						float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
						float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
						float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
						float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
						float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};

						ComputeNormal(A,B,C);
						glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
						ComputeNormal(B,D,E);
						glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));
						flipflop = !flipflop;
					}
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

	/* Cross */
    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2f,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(12.0f,112.0f,58.0f);
    glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_2() //darker blue + red spiral left
{
    /* Drawing */
    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;
    glDisable(GL_CULL_FACE);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(0,124,140);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,16,1); // Base
    glPopMatrix();

    ///Head
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glBegin(GL_TRIANGLE_STRIP);
                for(int i = slices ; i > -1 ;i--)
                {
                    if(flipflop) RGB_Color(0,124,140);
                    else RGB_Color(163,103,95);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));
                    flipflop = !flipflop;
                }
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2F,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(0.0f,92.0f,103.0f);
    glPopMatrix();
    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_3() //blue white strips
{
    glDisable(GL_CULL_FACE);
    /* Drawing */
    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;

    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(0.0f,81.0f,172.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,8,1); // Base
    glPopMatrix();

    ///Head
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=0; j< 7; j++)
            {
                glRotatef(-15.0f,0,1,0);
                glBegin(GL_TRIANGLE_STRIP);
                for(int i = 0 ; i <= slices;i++)
                {
                    if(flipflop) RGB_Color(0.0f,76.0f,182.0f);
                    else RGB_Color(241.0f,241.0f,233.0f);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i+1)/(slices) *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
                    float B[3] = { onionRadii[j+1]*cosf(theta),stackheight*j+1,onionRadii[j+1]*sinf(theta)};
                    float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
                    float D[3] = { onionRadii[j+2]*cosf(theta),stackheight*j+2,onionRadii[j+2]*sinf(theta)};
                    float E[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};;

                    ComputeNormal(A,B,C);
                    glVertex3f(onionRadii[j]*cosf(theta),        stackheight*j,  onionRadii[j]*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f(onionRadii[j+1]*cosf(theta),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta));
                    flipflop = !flipflop;
                }
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2f,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(0.0f,66.0f,176.0f);
    glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_4() //double spiral
{
    /* Drawing */
    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;
    glDisable(GL_CULL_FACE);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(0,102,59);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,16,1); // Base
    glPopMatrix();

    ///Head
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glBegin(GL_TRIANGLE_STRIP);
                for(int i = slices ; i > -1 ;i--)
                {
                    RGB_Color(254,179,0);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));
                }
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

    ///Strips, spiral left
    glPushMatrix();
        scaleObjects(1.005);
        glTranslatef(0.0f,0.2f,0.0f);
        slices = 16;
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glBegin(GL_QUAD_STRIP);
                for(int i = slices ; i > -1 ;i--)
                {
                    RGB_Color(0.0f,137.0f,86.0f);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f((onionRadii[j]+0.02f)*cosf(theta),              stackheight*j,  (onionRadii[j]+0.02f)*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f((onionRadii[j+1]+0.02f)*cosf(theta_next),   stackheight*(j+1),  (onionRadii[j+1]+0.02f)*sinf(theta_next));
                }
                glEnd();
            }
    glPopMatrix();

    ///Strips, spiral right
    glPushMatrix();
        scaleObjects(1.005);
        glTranslatef(0.0f,0.2f,0.0f);
        slices = 16;
            for(int j=0; j< 7; j++)
            {
                glBegin(GL_QUAD_STRIP);
                for(int i = 0 ; i <= slices;i++)
                {
                    RGB_Color(0.0f,137.0f,86.0f);
                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i+1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i+2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
                    float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
                    float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f((onionRadii[j]+0.02f)*cosf(theta),              stackheight*j,  (onionRadii[j]+0.02f)*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f((onionRadii[j+1]+0.02f)*cosf(theta_next),   stackheight*(j+1),  (onionRadii[j+1]+0.02f)*sinf(theta_next));
                }
                glEnd();
            }
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2F,0.0f);
        scaleObjects(0.055f);
        drawCatholicCross(0.0f,137.0f,86.0f);
    glPopMatrix();
    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_5() // tetrahedral
{
    glDisable(GL_CULL_FACE);
    /* Drawing */
    int slices = 26;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;

    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(0.0f,109.0f,51.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,16,1); // Base
    glPopMatrix();

    ///Shape
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=7; j>-1; j--)
            {

                for(int i = 0 ; i <= slices;i++)
                {
                    RGB_Color(63,92,25);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i+1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i+2)/slices *2*M_PI;

                    /* Normal Calculations */
                    if(j+1 < 8)
                    {
                        float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
                        float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
                        float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
                        float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
                        float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};
                        glBegin(GL_TRIANGLES);
                            ComputeNormal(A,B,C);
                            glVertex3f(onionRadii[j+1]*cosf(theta),              stackheight*(j+1),  onionRadii[j+1]*sinf(theta));

                            ComputeNormal(B,D,E);
                            glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));

                            glVertex3f(onionRadii[j]*cosf(theta_next-0.13f),              stackheight*j,  onionRadii[j]*sinf(theta_next-0.13f));
                        glEnd();
                        flipflop = !flipflop;
                    }
                }
                 glRotatef(0,0,1,0);

            }
            glShadeModel(GL_SMOOTH);
    glPopMatrix();

    ///BackGround
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=0; j< 7; j++)
            {
                glBegin(GL_TRIANGLE_STRIP);
                for(int i = 0 ; i <= slices;i++)
                {
                    RGB_Color(226,197,69);
                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i+1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i+2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
                    float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
                    float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};


                        ComputeNormal(A,B,C);
                        glVertex3f((onionRadii[j]-0.02)*cosf(theta),              stackheight*j,  (onionRadii[j]-0.02)*sinf(theta));
                        ComputeNormal(B,D,E);
                        glVertex3f((onionRadii[j+1]-0.02)*cosf(theta_next),   stackheight*(j+1),  (onionRadii[j+1]-0.02)*sinf(theta_next));
                }
                glEnd();

            }
            glShadeModel(GL_SMOOTH);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2f,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(12.0f,112.0f,58.0f);
    glPopMatrix();


    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_6() //greed brown spiral left
{
    /* Drawing */
    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;
    glDisable(GL_CULL_FACE);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(0,70,42);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,8,1); // Base
    glPopMatrix();

    ///Head
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glBegin(GL_TRIANGLE_STRIP);
                for(int i = slices ; i > -1 ;i--)
                {
                    if(flipflop) RGB_Color(156,137,104);
                    else RGB_Color(1,119,69);

                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));
                    flipflop = !flipflop;
                }
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2F,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(9,109,57);
    glPopMatrix();
    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_7() //red white zig zag
{
    /* Drawing */
    //RGB_Color(211,127,103); // the red
    //RGB_Color(239,245,243); // the white
    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool top = true;
    glDisable(GL_CULL_FACE);
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    ///Base
    glPushMatrix();
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        RGB_Color(248,67,67); // the red
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,8,1); // Base
    glPopMatrix();

    ///Head
    glPushMatrix();
        glShadeModel(GL_SMOOTH);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glBegin(GL_QUAD_STRIP);
                for(int i = 0 ; i <= slices ;i++)
                {
                    RGB_Color(239,245,243);
                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */
                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
                    ComputeNormal(B,D,E);
                    glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));
                }
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();


    ///Red Strips
    glPushMatrix();
        glTranslatef(0.0f,0.2f,0.0f);
        slices = 24;
            for(int j = 0; j < 7; j++) // 7 stacks
            {
                glRotatef((float)360.0f/slices,0,1,0);
                glBegin(GL_QUAD_STRIP);
                for(int i = slices ; i > -1 ;i--)
                {
                    RGB_Color(211,127,103);
                    float theta = (float) i/slices *2*M_PI;
                    float theta_next = (float) (i-1)/slices *2*M_PI;
                    float theta_next_2 = (float) (i-2)/slices *2*M_PI;

                    /* Normal Calculations */

                    float A[3] = { -onionRadii[j]*cosf(theta)         ,stackheight*j  ,-onionRadii[j]*sinf(theta)};
                    float B[3] = { -onionRadii[j+1]*cosf(theta_next)  ,stackheight*j+1,-onionRadii[j+1]*sinf(theta_next)};
                    float C[3] = { -onionRadii[j]*cosf(theta_next)    ,stackheight*j  ,-onionRadii[j]*sinf(theta_next)};
                    float D[3] = { -onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,-onionRadii[j+2]*sinf(theta_next_2)};
                    float E[3] = { -onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,-onionRadii[j+1]*sinf(theta_next_2)};

                    ComputeNormal(A,B,C);
                    ComputeNormal(B,D,E);
                    if(top)
                    {
                        glVertex3f((onionRadii[j+1]+0.05f)*cosf(theta),   stackheight*(j+1),  (onionRadii[j+1]+0.05f)*sinf(theta));
                        glVertex3f((onionRadii[j+1]+0.00f)*cosf(theta),   stackheight*(j+1)+0.15f,  (onionRadii[j+1]+0.00f)*sinf(theta));
                    }
                    else
                    {

                        glVertex3f((onionRadii[j]+0.05f)*cosf(theta),   stackheight*(j),        (onionRadii[j]+0.05)*sinf(theta));
                        glVertex3f((onionRadii[j]+0.00f)*cosf(theta),   stackheight*(j)+0.15f,  (onionRadii[j]+0.00f)*sinf(theta));
                    }
                    top = !top;
                }
                glEnd();
            }
    glPopMatrix();


    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2F,0.0f);
        scaleObjects(0.055f);
        drawCatholicCross(189,104,83);
    glPopMatrix();
    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_8() //Red,Green,Durian Shape
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;
    bool flipflop = false;

    /* Base */
    glPushMatrix();
		RGB_Color(22,133,74);
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,8,1); // Base
    glPopMatrix();

    /* Shape */
    glPushMatrix();
        glShadeModel(GL_FLAT);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=0; j< 7; j++)
            {
                glRotatef(-22.5f,0,1,0);
                glBegin(GL_QUAD_STRIP);
					for(int i = 0 ; i <= slices;i++)
					{
						if(flipflop) RGB_Color(1,146,107);
						else RGB_Color(252,35,0);
						float theta = (float) i/slices *2*M_PI;
						float theta_next = (float) (i+1)/slices *2*M_PI;
						float theta_next_2 = (float) (i+2)/slices *2*M_PI;

						/* Normal Calculations */

						float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
						float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
						float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
						float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
						float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};

						ComputeNormal(A,B,C);
						glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
						ComputeNormal(B,D,E);
						glVertex3f(onionRadii[j+1]*cosf(theta),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta));
						flipflop = !flipflop;
					}
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

	/* Cross */
    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2f,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(0.0f,107.0f,61.0f);
    glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawDomeTop_9() //Center, very High
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);

    int slices = 24;
    float onionRadii[8] = {1, 1.27f, 1.36f, 1.21f, 1, 0.68f, 0.40f, 0.25f};
    float stackheight = 0.34f;

    /* Base */
    glPushMatrix();
		RGB_Color(193,131,0);
        glRotatef(270,1,0,0);
        glTranslatef(0.0f,0.0f,0.0f);
        gluQuadricDrawStyle(pObj, GLU_FILL);
        gluCylinder(pObj, 1.1f, 0.9f,0.4f,8,1); // Base
    glPopMatrix();

    /* Shape */
    glPushMatrix();
        glShadeModel(GL_SMOOTH);
        glTranslatef(0.0f,0.2f,0.0f);
            for(int j=0; j< 7; j++)
            {
                glBegin(GL_QUAD_STRIP);
					for(int i = 0 ; i <= slices;i++)
					{
						RGB_Color(253,171,0);
						float theta = (float) i/slices *2*M_PI;
						float theta_next = (float) (i+1)/slices *2*M_PI;
						float theta_next_2 = (float) (i+2)/slices *2*M_PI;

						/* Normal Calculations */

						float A[3] = { onionRadii[j]*cosf(theta),stackheight*j,onionRadii[j]*sinf(theta)};
						float B[3] = { onionRadii[j+1]*cosf(theta_next),stackheight*j+1,onionRadii[j+1]*sinf(theta_next)};
						float C[3] = { onionRadii[j]*cosf(theta_next),stackheight*j,onionRadii[j]*sinf(theta_next)};
						float D[3] = { onionRadii[j+2]*cosf(theta_next_2),stackheight*j+2,onionRadii[j+2]*sinf(theta_next_2)};
						float E[3] = { onionRadii[j+1]*cosf(theta_next_2),stackheight*j+1,onionRadii[j+1]*sinf(theta_next_2)};

						ComputeNormal(A,B,C);
						glVertex3f(onionRadii[j]*cosf(theta),              stackheight*j,  onionRadii[j]*sinf(theta));
						ComputeNormal(B,D,E);
						glVertex3f(onionRadii[j+1]*cosf(theta_next),   stackheight*(j+1),  onionRadii[j+1]*sinf(theta_next));

					}
                glEnd();
            }
        glShadeModel(GL_SMOOTH);
    glPopMatrix();

	/* Cross */
    glPushMatrix();
        glTranslatef(0.0f,(0.34f*7)+0.2f,0.0f);
        scaleObjects(0.05f);
        drawCatholicCross(253,171,0);
    glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);



}

void St_Basils_Cathedral::drawWall_Small()
{
    ///For Small Wall, there is 2 part of rendering
    ///1) Cylinder+Disk Top
    ///2) Semi-Circle Architecture Base
    float cylinder_radius = 15.0f;

    glDisable(GL_CULL_FACE);
        GLUquadricObj *pObj;
        pObj = gluNewQuadric();
        gluQuadricDrawStyle(pObj, GLU_LINE);

        glPushMatrix();
            glTranslatef(0.0f,28.0f,0.0f);
            glRotatef(90.0f,1.0f, 0.0f, 0.0f);
            RGB_Color(1.0f,160.0f,138.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, cylinder_radius*1.35, cylinder_radius*1.35, 28.0f, 12, 1); //Lower Dome

            glTranslatef(0.0f,0.0f,-2.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, cylinder_radius*1.15, cylinder_radius*1.35, 4.0f, 12, 1); //Connector1

            glTranslatef(0.0f,0.0f,-1.5f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, cylinder_radius*0.85, cylinder_radius*1.20, 1.5f, 12, 1); //Connector2

            glTranslatef(0.0f,0.0f,-22.5f);
            RGB_Color(224.0f,100.0f,0.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, cylinder_radius*0.95, cylinder_radius*0.95, 23.5f, 16, 1); //Top Dome
        glPopMatrix();

        glPushMatrix();
            for(int h = 0 ; h < 3 ; h++)
            {
                for(int i = 0 ; i < 8 ; i++)
                {
                    glPushMatrix();
                    glRotatef(45.0f*i,0.0f,1.0f,0.0f);
                    glTranslatef(0.0f,0.0f,cylinder_radius+5.5f);
                    drawSemiCylinder_SmallDome();
                    glPopMatrix();
                }
                glTranslatef(0.0f,10.0f,0.0f);
                glRotatef(22.5f,0.0f,1.0f,0.0f);
            }
        glPopMatrix();

        glPushMatrix();
            RGB_Color(255.0f,255.0f,255.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            glRotatef(90.0f,1.0f,0.0f,0.0f);
            glTranslatef(0.0f,0.0f,-32.0f);
            gluCylinder(pObj,cylinder_radius*0.96,cylinder_radius*0.96,1.5f,16,1);

            glTranslatef(0.0f,0.0f,-3.0f);
            gluCylinder(pObj,cylinder_radius*0.96,cylinder_radius*0.96,1.0f,16,1);

            glTranslatef(0.0f,0.0f,-15.0f);
            gluCylinder(pObj,cylinder_radius*0.96,cylinder_radius*0.96,1.0f,16,1);

            glTranslatef(0.0f,0.0f,-2.5f);
            gluCylinder(pObj,cylinder_radius*0.96,cylinder_radius*0.96,1.0f,16,1);

            glTranslatef(0.0f,0.0f,-1.5f);
            RGB_Color(255.0f,223.0f,11.0f);
            gluCylinder(pObj,cylinder_radius*1.06,cylinder_radius*1.06,0.6f,16,1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(11.25,0,1,0);
        for(int i = 0 ; i < 8 ; i++)
        {
            glPushMatrix();
            glRotatef(45.0f*i,0.0f,1.0f,0.0f);
            glTranslatef(0.0f,35.0f,cylinder_radius*0.94);
            scaleObjects(2.0f);
            drawWhiteArcWindow();
            glPopMatrix();
        }
        glPopMatrix();
        gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);

}

void St_Basils_Cathedral::drawWall_Medium1()
{
    float cylinder_radius = 15.0f;

    glDisable(GL_CULL_FACE);
        GLUquadricObj *pObj;
        pObj = gluNewQuadric();
        gluQuadricDrawStyle(pObj, GLU_LINE);
        float A[3],B[3],C[3],D[3];

        /* Lower Part */
        glPushMatrix();
        ///Base
            glTranslatef(0.0f,40.0f,0.0f);
            glRotatef(90.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);
            RGB_Color(224.0f,65.0f,0.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, 26.0f,28.0f , 40.0f, 8, 2); //triangle till 35
        glPopMatrix();

        /* Triangle Roof Windows */
        glPushMatrix();
            for(int i = 0 ; i < 8;i++ )
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,28.0f);
                    drawTriangleBase_MediumDome();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
        glPopMatrix();

        /* Frames+WhiteStrips */
        glPushMatrix();
        for(int i = 0 ; i < 8; i++)
        {
            glRotatef(45.0f,0,1,0);
            glPushMatrix();
                RGB_Color(255,255,255);
                glRotatef(270,1,0,0);
                glTranslatef(-10.3f,26.0f,0.0f);
                gluCylinder(pObj,0.45f,0.45f,29,4,1);

                glTranslatef(+2.0f,0.0f,6.0f);
                gluCylinder(pObj,0.45f,0.45f,23,4,1);

                glTranslatef(+16.6f,0.0f,0.0f);
                gluCylinder(pObj,0.45f,0.45f,23,4,1);

                glTranslatef(+2.0f,0.0f,-6.0f);
                gluCylinder(pObj,0.45f,0.45f,29,4,1);
            glPopMatrix();
        }
        glPopMatrix();

        ///rings
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);
            glTranslatef(0.0f,0.0f,28.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj,26.43f,29.43f,1.5f,8,1);
            glTranslatef(0.0f,0.0f,1.5f);
            gluCylinder(pObj,29.43f,29.43f,1.5f,8,1);
        glPopMatrix();

        ///Connector of Top and Bot
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);

            glTranslatef(0.0f,0.0f,31.0f);
            RGB_Color(224.0f,100.0f,0.0f);
            gluCylinder(pObj,29.43f,29.43f,5.0f,8,1);

            RGB_Color(255.0f,255.0f,255.0f);
            glTranslatef(0.0f,0.0f,5.0f);
            gluCylinder(pObj,29.43f,30.0f,1.0f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,1.0f); //38
            gluCylinder(pObj,30.0f,29.5f,2.0f,8,1);

            RGB_Color(126.0f,19.0f,1.0f); //dark red
            glTranslatef(0.0f,0.0f,2.0f); //40
            gluCylinder(pObj,29.5f,31.0f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f); // red
            glTranslatef(0.0f,0.0f,0.5f); //40.5
            gluCylinder(pObj,31.0f,30.5f,2.0f,8,1);

            RGB_Color(176.0f,175.0f,171.0f); //grey
            glTranslatef(0.0f,0.0f,2.0f); //42.5
            gluCylinder(pObj,30.5f,31.0f,0.5f,8,1);

            RGB_Color(255,255,255); //white
            glTranslatef(0.0f,0.0f,0.5f); //43
            gluCylinder(pObj,31.0f,31.5f,1.0f,8,1);

            RGB_Color(1,160,132); //grey
            glTranslatef(0.0f,0.0f,1.0f); //44
            gluCylinder(pObj,31.5f,25.0f,3.0f,8,1);

            //Now reach 45.0f height of the dome
        glPopMatrix();

        /* Upper Part */
        ///SemiDisks
        glPushMatrix();
            for(int i = 0 ; i < 8 ; i++ )
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,44.0f,25.5f);
                    scaleObjects(1.1);
                    drawSemiCylinder_MediumDome1();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();

            }
        glPopMatrix();

        /// Upper Body
        glPushMatrix();
            glTranslatef(0.0f,44.0f,0.0f);
            glRotatef(270.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);

            RGB_Color(0.0f,180.0f,151.0f); //grey
            gluCylinder(pObj, 23.0f,23.0f ,15.0f, 8, 2);

            glTranslatef(0.0f,0.0f,15.0f);
            RGB_Color(1.0f,117.0f,80.0f); //brown-grey
            gluCylinder(pObj, 23.0f,23.0f ,5.0f, 8, 2);

            glTranslatef(0.0f,0.0f,5.0f);
            RGB_Color(224.0f,100.0f,0.0f);//red
            gluCylinder(pObj, 23.0f,23.0f ,21.0f, 8, 2);
        glPopMatrix();

        ///Red Triangles
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glTranslatef(0.0f,54.0f,.0f);
            for(int i = 0 ; i < 8 ; i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                glTranslatef(0.0f,0.0f,24.0f);
                scaleObjects(0.6);
                drawTriangleTop_MediumDome();
                glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
        glPopMatrix();

        ///White Windows, Red Left, Red Right Strips
        glPushMatrix();
            glTranslatef(0.0f,64.0f,0.0f);
            for(int i = 0; i < 8;i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    ///left
                    glTranslatef(-8.4f,0.0f,21.5f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcDisk
                    glRotatef(-270,1,0,0);
                    glTranslatef(+8.4f,16.5f,0.6f);
                    RGB_Color(255,255,255); //white
                    gluPartialDisk(pObj,0,3.5f,8,1,270,180);

                    ///right
                    glTranslatef(+8.4f,-16.5,-0.6f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcQuad
                    glRotatef(-270,1,0,0);
                    glTranslatef(-8.4f,0.0f,0.6f);
                    glBegin(GL_QUADS);
                        RGB_Color(255,255,255);
                        A[0] = -3.5f  , A[1] = 0.0f , A[2] = 0.0f;
                        B[0] = -3.5f  , B[1] = 16.5 , B[2] = 0.0f;
                        C[0] = 3.5f   , C[1] = 16.5f, C[2] = 0.0f;
                        ComputeNormal(C,B,A);
                        glVertex3f(-3.5f,0.0f,0.0f);
                        glVertex3f(-3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,0.0f,0.0f);
                    glEnd();

                    ///Top
                    //glTranslatef(0.0f,10.5f,0.0f);
                    glRotatef(270,1,0,0);
                    glTranslatef(-10.5f,0.0f,21.0f);
                    glRotatef(90,0,1,0);

                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,20.0,6,1);

                glPopMatrix();
            }
        glPopMatrix();

        ///Connectors & Cylinders
        glPushMatrix();
            ///white strips
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);

            RGB_Color(216.0f,214.0f,191.0f); // grey-white
            glTranslatef(0.0f,0.0f,85.5f);
            gluCylinder(pObj,24.0f,26.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.0f,25.7f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.7f,25.4f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f); //red
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.4f,25.4f,4.5f,8,1);

            RGB_Color(216.0f,214.0f,191.0f); //grey-white
            glTranslatef(0.0f,0.0f,4.5f);
            gluCylinder(pObj,25.4f,27.4f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,27.4f,27.1f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,27.1f,26.8f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.8f,27.8f,3.0f,8,1);

            RGB_Color(216.0f,214.0f,191.0f);
            glTranslatef(0.0f,0.0f,3.0f);
            gluCylinder(pObj,27.8f,26.8f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.8f,26.5f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.5f,26.2f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.2f,27.2f,3.0f,8,1);

            RGB_Color(255.0f,223.0f,11.0f);
            glTranslatef(-0.2f,0.0f,1.0f);
            gluCylinder(pObj,26.2f,27.2f,1.0f,8,1);
        glPopMatrix();

        /* Decor */
        glPushMatrix();
            ///black <> shape
            glTranslatef(0.0f,87.0f,0.0f);
            for(int i = 0; i < 8; i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,23.4f);
                    glBegin(GL_QUADS);
                        RGB_Color(138,0,0); //dark-red
                        A[0] = -7.4f  , A[1] = 2.3f , A[2] = 0.1f;
                        B[0] = -5.6f  , B[1] = 4.1f , B[2] = 0.1f;
                        C[0] = -3.8f  , C[1] = 2.3f , C[2] = 0.1f;
                        D[0] = -5.6f  , D[1] = 0.5f , D[2] = 0.1;

                        ComputeNormal(C,B,A);
                        glVertex3f(A[0],A[1],A[2]);
                        glVertex3f(B[0],B[1],B[2]);
                        glVertex3f(C[0],C[1],C[2]);
                        glVertex3f(D[0],D[1],D[2]);

                        A[0] = -1.8f  , A[1] = 2.3f , A[2] = 0.1f;
                        B[0] = -0.0f  , B[1] = 4.1f , B[2] = 0.1f;
                        C[0] = +1.8f  , C[1] = 2.3f , C[2] = 0.1f;
                        D[0] = -0.0f  , D[1] = 0.5f , D[2] = 0.1;

                        ComputeNormal(C,B,A);
                        glVertex3f(A[0],A[1],A[2]);
                        glVertex3f(B[0],B[1],B[2]);
                        glVertex3f(C[0],C[1],C[2]);
                        glVertex3f(D[0],D[1],D[2]);

                        A[0] = +7.4f  , A[1] = 2.3f , A[2] = 0.1f;
                        B[0] = +5.6f  , B[1] = 4.1f , B[2] = 0.1f;
                        C[0] = +3.8f  , C[1] = 2.3f , C[2] = 0.1f;
                        D[0] = +5.6f  , D[1] = 0.5f , D[2] = 0.1;

                        ComputeNormal(A,B,C);
                        glVertex3f(A[0],A[1],A[2]);
                        glVertex3f(B[0],B[1],B[2]);
                        glVertex3f(C[0],C[1],C[2]);
                        glVertex3f(D[0],D[1],D[2]);
                    glEnd();
                glPopMatrix();
            }
        glPopMatrix();


        glPushMatrix();
            ///white disks
            RGB_Color(255,255,255);
            for(int i = 0; i< 8;i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,93.2f,25.0f);
                    glRotatef(28.48,1,0,0);
                    glTranslatef(-6.84f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                glPopMatrix();
            }
        glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);

}

void St_Basils_Cathedral::drawWall_Medium2()
{
    float cylinder_radius = 15.0f;

    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_LINE);
	float A[3],B[3],C[3],D[3];

        /* Lower Part */
        glPushMatrix();
        ///Base
            glTranslatef(0.0f,40.0f,0.0f);
            glRotatef(90.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);
            RGB_Color(224.0f,65.0f,0.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, 26.0f,28.0f , 40.0f, 8, 2); //triangle till 35
        glPopMatrix();

        /* Triangle Roof Windows */
        glPushMatrix();
            for(int i = 0 ; i < 8;i++ )
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,28.0f);
                    drawTriangleBase_MediumDome();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
        glPopMatrix();

        /* Frames+WhiteStrips */
        glPushMatrix();
        for(int i = 0 ; i < 8; i++)
        {
            glRotatef(45.0f,0,1,0);
            glPushMatrix();
                RGB_Color(255,255,255);
                glRotatef(270,1,0,0);
                glTranslatef(-10.3f,26.0f,0.0f);
                gluCylinder(pObj,0.45f,0.45f,29,4,1);

                glTranslatef(+2.0f,0.0f,6.0f);
                gluCylinder(pObj,0.45f,0.45f,23,4,1);

                glTranslatef(+16.6f,0.0f,0.0f);
                gluCylinder(pObj,0.45f,0.45f,23,4,1);

                glTranslatef(+2.0f,0.0f,-6.0f);
                gluCylinder(pObj,0.45f,0.45f,29,4,1);
            glPopMatrix();
        }
        glPopMatrix();

        ///rings
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);
            glTranslatef(0.0f,0.0f,28.0f);
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj,26.43f,29.43f,1.5f,8,1);
            glTranslatef(0.0f,0.0f,1.5f);
            gluCylinder(pObj,29.43f,29.43f,1.5f,8,1);
        glPopMatrix();

        ///Connector of Top and Bot
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);

            glTranslatef(0.0f,0.0f,31.0f);
            RGB_Color(224.0f,100.0f,0.0f);
            gluCylinder(pObj,29.43f,29.43f,5.0f,8,1);

            RGB_Color(255.0f,255.0f,255.0f);
            glTranslatef(0.0f,0.0f,5.0f);
            gluCylinder(pObj,29.43f,32.5f,1.f,8,1);

            ///Red Arcs
            glPushMatrix();
                glRotatef(22.5,0,0,1);
                glRotatef(-270,1,0,0);
                for(int i = 0 ; i < 8; i++)
                {
                    glRotatef(45,0,1,0);
                    glPushMatrix();
                        glTranslatef(-14.5f,1.0f,28.5f);
                        for(int i = 0; i < 4 ; i++)
                        {
                            glTranslatef(+6.0f,0.0f,0.0f);
                            drawSemiCylinder_MediumDome2_b();
                        }
                    glPopMatrix();
                }
            glPopMatrix();

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,1.0f); //38
            gluCylinder(pObj,30.0f,30.5f,4.5f,8,1);

            RGB_Color(176.0f,175.0f,171.0f); //grey
            glTranslatef(0.0f,0.0f,4.5f); //42.5
            gluCylinder(pObj,30.5f,31.0f,0.5f,8,1);

            RGB_Color(255,255,255); //white
            glTranslatef(0.0f,0.0f,0.5f); //43
            gluCylinder(pObj,31.0f,31.5f,1.0f,8,1);

            RGB_Color(1,160,132); //grey
            glTranslatef(0.0f,0.0f,1.0f); //44
            gluCylinder(pObj,31.5f,25.0f,3.0f,8,1);
        glPopMatrix();

        /* Upper Part */
        ///SemiDisks
        glPushMatrix();
            for(int i = 0 ; i < 8 ; i++ )
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,44.0f,25.5f);
                    scaleObjects(1.1);
                    drawSemiCylinder_MediumDome2();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();

            }
        glPopMatrix();

        /// Upper Body
        glPushMatrix();
            glTranslatef(0.0f,44.0f,0.0f);
            glRotatef(270.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);

            RGB_Color(0.0f,180.0f,151.0f); //grey
            gluCylinder(pObj, 23.0f,23.0f ,15.0f, 8, 2);

            glTranslatef(0.0f,0.0f,15.0f);
            RGB_Color(1.0f,117.0f,80.0f); //brown-grey
            gluCylinder(pObj, 23.0f,23.0f ,5.0f, 8, 2);

            glTranslatef(0.0f,0.0f,5.0f);
            RGB_Color(224.0f,100.0f,0.0f); //red
            gluCylinder(pObj, 23.0f,23.0f ,21.0f, 8, 2);
        glPopMatrix();

        ///Red Triangles
        glPushMatrix();
            glRotatef(22.5,0,1,0);
            glTranslatef(0.0f,54.0f,.0f);
            for(int i = 0 ; i < 8 ; i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                glTranslatef(0.0f,0.0f,24.0f);
                scaleObjects(0.6);
                drawTriangleTop_MediumDome();
                glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
        glPopMatrix();

        ///White Windows, Red Left, Red Right Strips
        glPushMatrix();
            glTranslatef(0.0f,64.0f,0.0f);
            for(int i = 0; i < 8;i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    ///left
                    glTranslatef(-8.4f,0.0f,21.5f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcDisk
                    glRotatef(-270,1,0,0);
                    glTranslatef(+8.4f,16.5f,0.6f);
                    RGB_Color(255,255,255); //white
                    gluPartialDisk(pObj,0,3.5f,8,1,270,180);

                    ///right
                    glTranslatef(+8.4f,-16.5,-0.6f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcQuad
                    glRotatef(-270,1,0,0);
                    glTranslatef(-8.4f,0.0f,0.6f);
                    glBegin(GL_QUADS);
                        RGB_Color(255,255,255);
                        A[0] = -3.5f  , A[1] = 0.0f , A[2] = 0.0f;
                        B[0] = -3.5f  , B[1] = 16.5 , B[2] = 0.0f;
                        C[0] = 3.5f   , C[1] = 16.5f, C[2] = 0.0f;
                        ComputeNormal(C,B,A);
                        glVertex3f(-3.5f,0.0f,0.0f);
                        glVertex3f(-3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,0.0f,0.0f);
                    glEnd();

                    ///Top
                    //glTranslatef(0.0f,10.5f,0.0f);
                    glRotatef(270,1,0,0);
                    glTranslatef(-10.5f,0.0f,21.0f);
                    glRotatef(90,0,1,0);

                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,20.0,6,1);

                glPopMatrix();
            }
        glPopMatrix();

        ///Connectors & Cylinders
        glPushMatrix();
            ///white strips
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);

            RGB_Color(216.0f,214.0f,191.0f); // grey-white
            glTranslatef(0.0f,0.0f,85.5f);
            gluCylinder(pObj,24.0f,26.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.0f,25.7f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.7f,25.4f,0.5f,8,1);

            ///Top second surface
            ///Arcs Surface
            float ArcRadii[6] = { 25.4f ,25.4f, 25.6f, 26.0f, 27.0f, 28.0f};
            RGB_Color(224.0f,100.0f,0.0f); //red
            glTranslatef(0.0f,0.0f,0.5f);
            /* Start here */
            gluCylinder(pObj,25.4f,25.4f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.4f,25.4f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.4f,25.6f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.6f,25.8f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,25.8f,26.5f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.5f,27.4f,0.5f,8,1);
            /* End */

            RGB_Color(216.0f,214.0f,191.0f); //grey-white

            gluCylinder(pObj,25.4f+2.0f,27.4f+2.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,27.4f+2.0f,27.1f+2.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,27.1f+2.0f,26.8f+2.0f,0.5f,8,1);

            ///Top 1st surface
            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.8f+2.0f,27.8f+2.0f,5.0f,8,1);

            RGB_Color(216.0f,214.0f,191.0f);
            glTranslatef(0.0f,0.0f,5.0f);
            gluCylinder(pObj,27.8f+2.0f,26.8f+2.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.8f+2.0f,26.5f+2.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.5f+2.0f,26.2f+2.0f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,26.2f+2.0f,27.2f+2.0f,3.0f,8,1);

            RGB_Color(255.0f,223.0f,11.0f); //GOLD
            glTranslatef(-0.2f,0.0f,1.0f);
            gluCylinder(pObj,26.2f+2.0f,27.2f+2.0f,1.0f,8,1);
        glPopMatrix();

        glPushMatrix();
            ///white disks

            for(int i = 0; i< 8;i++)
            {
                RGB_Color(255,255,255);
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,91.0f,25.0f+2.0f);
                    glRotatef(17.64,1,0,0);
                    glTranslatef(-6.84f,0.0f,0.1f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.1f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.1f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.1f); gluPartialDisk(pObj,0.0f,2.0f,8,1,270,180);
                glPopMatrix();


                RGB_Color(224.0f,63.0f,0.0f);
                glPushMatrix();
                    glTranslatef(0.0f,91.0f,25.0f+2.0f);
                    glRotatef(17.64,1,0,0);
                    glTranslatef(-6.84f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,3.5f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,3.5f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,3.5f,8,1,270,180);
                    glTranslatef(+4.56f,0.0f,0.0f); gluPartialDisk(pObj,0.0f,3.5f,8,1,270,180);
                glPopMatrix();
            }
        glPopMatrix();

    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawWall_Medium3()
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_LINE);
	float cylinder_radius = 15.0f;
	float A[3],B[3],C[3],D[3];

	glPushMatrix();
		/* Lower Part */
		glPushMatrix();
			///Base
            glTranslatef(0.0f,18.0f,0.0f);
            glRotatef(90.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);
            RGB_Color(224.0f,65.0f,0.0f); //red
            gluQuadricDrawStyle(pObj,GLU_FILL);
            gluCylinder(pObj, 28.0f,30.0f , 18.0f, 8, 2); // h = 18
        glPopMatrix();

		/* Triangle Roof Windows */
        glPushMatrix();
            for(int i = 0 ; i < 8;i++ )
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,28.0f);
                    drawTriangleBase_MediumDome();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
        glPopMatrix();

        /* Lower Body Wall, Strip 1 */
        glPushMatrix();
            RGB_Color(257,248,242);
            glRotatef(-90,1,0,0);
            glRotatef(22.5f,0,0,1);
            glTranslatef(0.0f,0.0f,18.0f);
            gluCylinder(pObj,28.0f,29.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,29.0f,27.0f,0.5f,8,1);

            RGB_Color(224.0f,65.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f);
            gluCylinder(pObj,27.0f,27.0f,22.0f,8,1);
        glPopMatrix();

        /* Surface White Quad *2 */
        glPushMatrix();
            RGB_Color(223,215,214);
            for(int i = 0; i < 8; i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,1.0f,25.0f);
                    //left
                    glBegin(GL_QUAD_STRIP);
                        glVertex3f(-10.5f,18.0f,0.0f);
                        glVertex3f(-10.5f,18.0f,0.5f);
                        glVertex3f(-10.5f,33.0f,0.0f);
                        glVertex3f(-10.5f,33.0f,0.5f);
                        glVertex3f(-7.04f,33.0f,0.0f);
                        glVertex3f(-7.04f,33.0f,0.5f);
                        glVertex3f(-7.04f,18.0f,0.0f);
                        glVertex3f(-7.04f,18.0f,0.5f);
                    glEnd();

                    glBegin(GL_QUAD_STRIP);
                        A[0] = -10.5f , A[1] = 18.0f, A[2] = 0.5f;
                        B[0] = -7.04f , B[1] = 18.0f, B[2] = 0.5f;
                        C[0] = -10.5f , C[1] = 33.0f, C[2] = 0.5f;

                        ComputeNormal(A,B,C);
                        glVertex3f(-10.5f,18.0f,0.5f);
                        glVertex3f(-7.04f,18.0f,0.5f);

                        A[1] = 33.0f, A[2] = 0.0f;
                        B[1] = 33.0f, B[2] = 0.5f;
                        C[1] = 18.0f, C[2] = 0.5f;

                        ComputeNormal(C,B,A);
                        glVertex3f(-10.5f,33.0f,0.5f);
                        glVertex3f(-7.04f,33.0f,0.5f);


                        glVertex3f(-10.5f,33.0f,0.0f);
                        glVertex3f(-7.04f,33.0f,0.0f);
                        glVertex3f(-10.5f,18.0f,0.0f);
                        glVertex3f(-7.04f,18.0f,0.0f);
                    glEnd();


                    //Right
                    glBegin(GL_QUAD_STRIP);
                        glVertex3f(+7.04f,18.0f,0.0f);
                        glVertex3f(+7.04f,18.0f,0.5f);
                        glVertex3f(+7.04f,33.0f,0.0f);
                        glVertex3f(+7.04f,33.0f,0.5f);
                        glVertex3f(+10.5f,33.0f,0.0f);
                        glVertex3f(+10.5f,33.0f,0.5f);
                        glVertex3f(+10.5f,18.0f,0.0f);
                        glVertex3f(+10.5f,18.0f,0.5f);
                    glEnd();

                    glBegin(GL_QUAD_STRIP);
                        A[0] = +7.04f , A[1] = 18.0f, A[2] = 0.5f;
                        B[0] = +10.5f, B[1] = 18.0f, B[2] = 0.5f;
                        C[0] = +7.04f , C[1] = 33.0f, C[2] = 0.5f;

                        ComputeNormal(A,B,C);
                        glVertex3f(+7.04f,18.0f,0.5f);
                        glVertex3f(+10.5f,18.0f,0.5f);

                        A[1] = 33.0f, A[2] = 0.0f;
                        B[1] = 33.0f, B[2] = 0.5f;
                        C[1] = 18.0f, C[2] = 0.5f;

                        ComputeNormal(C,B,A);
                        glVertex3f(+7.04f,33.0f,0.5f);
                        glVertex3f(+10.5f,33.0f,0.5f);
                        glVertex3f(+7.04f,33.0f,0.0f);
                        glVertex3f(+10.5f,33.0f,0.0f);
                        glVertex3f(+7.04f,18.0f,0.0f);
                        glVertex3f(+10.5f,18.0f,0.0f);
                    glEnd();
                glPopMatrix();
            }
        glPopMatrix();

        /* Connectors */
        glPushMatrix();
        {
            RGB_Color(224.0f,100.0f,0.0f); //brighter red
            glRotatef(-90,1,0,0);
            glRotatef(22.5f,0,0,1);
            glTranslatef(0.0f,0.0f,33.0f); //h = 33
            gluCylinder(pObj,27.0f,28.0f,1.0f,8,1);

            RGB_Color(224.0f,65.0f,0.0f); //red
            glTranslatef(0.0f,0.0f,1.0f); // h = 34
            gluCylinder(pObj,28.0f,28.5f,1.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f); //brighter red
            glTranslatef(0.0f,0.0f,1.5f); // h = 34.5
            gluCylinder(pObj,28.5f,28.5f,1.0f,8,1);

            RGB_Color(234,230,219); //white
            glTranslatef(0.0f,0.0f,1.0f); // h = 35
            gluCylinder(pObj,28.5f,29.0f,0.5f,8,1);

            glTranslatef(0.0f,0.0f,0.5f); // h = 35.5
            gluCylinder(pObj,29.5f,28.5f,0.5f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.5f); // h = 35.5
            gluCylinder(pObj,28.5f,30.0f,9.19f,8,1);
        }
        glPopMatrix();

        /* Red Arc Surfaces */
        glPushMatrix();
            glTranslatef(0.0f,37.5f,0.0f);
            for(int i = 0 ; i < 8 ; i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                glTranslatef(0.0f,0.0f,27.5f);
                    scaleObjects(0.8);
                    drawRedArcSurface_MediumDome3();
                glPopMatrix();
            }
            glDisable(GL_CULL_FACE);
        glPopMatrix();

        /* Continue Connector */
        glPushMatrix();
            glRotatef(-90,1,0,0);
            glRotatef(22.5f,0,0,1);
            RGB_Color(234,230,219);
            glTranslatef(0.0f,0.0f,46.69f); // h = 44.69
            gluCylinder(pObj,30.0f,30.5f,1.0f,8,1);

            RGB_Color(171,172,173);
            glTranslatef(0.0f,0.0f,1.0f);
            gluCylinder(pObj,30.5f,26.5f,2.0f,8,1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f,48.69f,0.0f);
            for(int i = 0 ; i < 8 ; i++)
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,25.0f);
                    scaleObjects(1.2f);
                    drawSemiCylinder_MediumDome3();
                glPopMatrix();
            }
        glPopMatrix();

        glPushMatrix();
            glRotatef(22.5f,0,1,0);
            glTranslatef(0.0f,57.69f,0.0f);
            for(int i = 0 ; i < 8 ; i++)
            {
                glRotatef(45.0f,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,0.0f,19.0f);
                    scaleObjects(0.8f);
                    drawSemiCylinder_MediumDome2();
                glPopMatrix();
            }
        glDisable(GL_CULL_FACE);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f,40.0f,0.0f);
            gluSphere(pObj,25.0f,16,8);
        glPopMatrix();

        glPushMatrix();
            RGB_Color(224.0f,105.0f,0.0f); //red
            glRotatef(-90.0f,1.0f, 0.0f, 0.0f);
            glRotatef(22.5f,0,0,1);
            glTranslatef(0.0f,0.0f,57.69f);
            gluCylinder(pObj,18.0f,18.0f,24.0f,8,1);

            RGB_Color(171,172,173);
            glTranslatef(0.0f,0.0f,-5.69f);
            gluCylinder(pObj,18.1f,18.1f,10.0f,8,1);
        glPopMatrix();


        ///White Windows, Red Left, Red Right Strips
        glPushMatrix();
            scaleObjects(0.80f);
            glTranslatef(0.0f,80.0f,0.0f);
            for(int i = 0; i < 8;i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    ///left
                    glTranslatef(-8.4f,0.0f,21.5f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcDisk
                    glRotatef(-270,1,0,0);
                    glTranslatef(+8.4f,16.5f,0.6f);
                    RGB_Color(255,255,255); //white
                    gluPartialDisk(pObj,0,3.5f,8,1,270,180);

                    ///right
                    glTranslatef(+8.4f,-16.5,-0.6f);
                    glRotatef(270,1,0,0);
                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,21.0f,6,1);

                    ///ArcQuad
                    glRotatef(-270,1,0,0);
                    glTranslatef(-8.4f,0.0f,0.6f);
                    glBegin(GL_QUADS);
                        RGB_Color(255,255,255);
                        A[0] = -3.5f  , A[1] = 0.0f , A[2] = 0.0f;
                        B[0] = -3.5f  , B[1] = 16.5 , B[2] = 0.0f;
                        C[0] = 3.5f   , C[1] = 16.5f, C[2] = 0.0f;
                        ComputeNormal(C,B,A);
                        glVertex3f(-3.5f,0.0f,0.0f);
                        glVertex3f(-3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,16.5f,0.0f);
                        glVertex3f(3.5f,0.0f,0.0f);
                    glEnd();

                    ///Top
                    //glTranslatef(0.0f,10.5f,0.0f);
                    glRotatef(270,1,0,0);
                    glTranslatef(-10.5f,0.0f,21.0f);
                    glRotatef(90,0,1,0);

                    RGB_Color(224.0f,65.0f,0.0f); //red
                    gluCylinder(pObj,0.6f,0.6f,20.0,6,1);

                glPopMatrix();
            }
        glPopMatrix();

        ///Lazy Connectors
        glPushMatrix();
        {
            ///white strips
            glRotatef(22.5,0,1,0);
            glRotatef(270,1,0,0);

            glTranslatef(0.0f,0.0f,81.0f);

            RGB_Color(216.0f,214.0f,191.0f); // grey-white

            gluCylinder(pObj,18.0f,19.5f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,19.5f,19.275f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,19.275f,19.05f,0.375f,8,1);

            RGB_Color(224.0f,100.0f,0.0f); //red:2nd surface
            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,19.05f,19.05f,3.375f,8,1);

            RGB_Color(216.0f,214.0f,191.0f); //grey-white
            glTranslatef(0.0f,0.0f,3.375f);
            gluCylinder(pObj,19.05f,20.55f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,20.55f,20.325f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,20.325f,20.1f,0.375f,8,1);

            RGB_Color(224.0f,100.0f,0.0f); //2nd Surfaces
            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,20.1f,20.85f,4.25f,8,1);

            RGB_Color(216.0f,214.0f,191.0f);
            glTranslatef(0.0f,0.0f,4.25f);
            gluCylinder(pObj,20.85f,20.1f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,20.1f,19.875f,0.375f,8,1);

            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,19.875f,19.65f,0.375f,8,1);

            RGB_Color(224.0f,100.0f,0.0f);
            glTranslatef(0.0f,0.0f,0.375f);
            gluCylinder(pObj,19.65f,20.4f,2.25f,8,1);

            RGB_Color(255.0f,223.0f,11.0f);
            glTranslatef(-0.15f,0.0f,0.75f);
            gluCylinder(pObj,19.65f,20.4f,0.75f,8,1);
        }
        glPopMatrix();

        ///Decorations
        ///White Tile + dark Circle
        glPushMatrix();
            for(int j = 0 ; j < 8; j++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                glTranslatef(-4.56f,0.0f,0.0f);
                for(int i = 0; i < 3; i++)
                {
                    glPushMatrix();
                        glTranslatef(0.0f,82.0f,18.0f);
                        float n = +0.5f;
                        glBegin(GL_QUADS);
                        {

                            A[0] = B[0] = -1.5f + (i*n) , C[0] = 1.5f + (i*n);
                            A[1] = C[1] = 0.175f, B[1] = 3.175f;
                            A[2] = B[2] = C[2] = 0.0f;
                            RGB_Color(255,255,255);
                            ComputeNormal(C,B,A); //take point 1,2,4, CW from bottom left.

                            glVertex3f(-1.5f + (i*n) ,0.175f,0.0f);
                            glVertex3f(-1.5f + (i*n) ,3.175f,0.0f);
                            glVertex3f(+1.5f + (i*n) ,3.175f,0.0f);
                            glVertex3f(+1.5f + (i*n) ,0.175f,0.0f);
                        }
                        glEnd();

                        glRotatef(270,1,0,0);
                        RGB_Color(25,25,25);
                        glTranslatef(0.5*i,-0.1f,1.6875f);
                        simpleDisk(1.1,8);
                        glDisable(GL_CULL_FACE);
                    glPopMatrix();
                    glTranslatef(4.175f,0.0f,0.0f);
                }
                glPopMatrix();
            }
        glPopMatrix();

        ///Top Triangles
        glPushMatrix();
            for(int j = 0 ; j < 8 ;j++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0.0f,86.5f,18.7f);
                    glRotatef(9,1,0,0);
                    for(int i = 0 ; i < 3 ; i++)
                    {
                        float n = 5.0f;
                        glBegin(GL_TRIANGLES);
                        {
                            A[0] = -7.05f +(n*i), B[0] = -5.05f +(n*i) , C[0] = -3.05f +(n*i);
                            A[1] = C[1] = 0.0f, B[1] = 4.0f;
                            A[2] = B[2] = C[2] = 0.0f;
                            RGB_Color(255,255,255);
                            ComputeNormal(C,B,A); //take point 1,2,4, CW from bottom left.

                            glVertex3f(-7.05f +(n*i),0.0f,0.0f);
                            glVertex3f(-5.05f +(n*i),4.0f,0.0f);
                            glVertex3f(-3.05f +(n*i),0.0f,0.0f);
                        }
                        glEnd();
                    }
                glPopMatrix();
            }
        glPopMatrix();
	glPopMatrix();

	gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);
}

void St_Basils_Cathedral::drawWall_Center()
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);
	float A[3],B[3],C[3];

    /* Lower Body Part */
	glPushMatrix();
	{
	    ///Base Connector
        RGB_Color(225,80,0);
        glRotatef(270,1,0,0);
        glRotatef(22.5,0,0,1);
        gluCylinder(pObj,40.0f,40.0f,2.5f,8,1);

        glTranslatef(0,0,2.5);
        gluCylinder(pObj,40.0f,30.0f,0.5f,8,1);

        glTranslatef(0,0,0.5);
        glRotatef(270,1,0,0);
        simpleDisk(30.0f,8);
        glDisable(GL_CULL_FACE);

        glRotatef(-270,1,0,0);
        RGB_Color(244,244,244);
        gluCylinder(pObj,25.0f,25.0f,20.0f,8,1);

	}
	glPopMatrix();

    /* Pillar, White Arc */
    for(int i = 0; i < 8; i++)
    {
        glRotatef(45,0,1,0);
        glPushMatrix();
            glTranslatef(-14.0f,3.0f,33.0f);
            drawRedArcSurface_CenterDome();
        glPopMatrix();
    }

    /* More Connectors */
    glPushMatrix();
    {
        RGB_Color(224,80,0);
        glRotatef(270,1,0,0);
        glRotatef(22.5,0,0,1);
        glTranslatef(0.0f,0.0f,19.0f);
        gluCylinder(pObj,36.0f,36.0f,2.5f,8,1);

        RGB_Color(227,233,220);
        glTranslatef(0.0f,0.0f,2.5f);
        gluCylinder(pObj,36.0f,37.0f,0.5f,8,1);

        glTranslatef(0.0f,0.0f,0.5f);
        gluCylinder(pObj,37.0f,36.5f,0.5f,8,1);
    }
    glPopMatrix();

    /* Triangles */
    glPushMatrix();
    {
        scaleObjects(0.45);
        for(int j = 0 ; j < 8; j++)
        {
            glRotatef(45,0,1,0);
            glPushMatrix();
            glTranslatef(+34.6,0,0);
            for(int i = 0 ; i < 3 ; i++)
            {
                glTranslatef(-18.5,0,0);
                glPushMatrix();
                    glTranslatef(0.0f,48.5f,74.0f);
                    drawRedTriangle_CenterDome();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
            glPopMatrix();
        }
    }
    glPopMatrix();

    /* Connectors */
    glPushMatrix();
    {
        RGB_Color(0,183,151);
        glRotatef(270,1,0,0);
        glRotatef(22.5,0,0,1);
        glTranslatef(0.0f,0.0f,21.5);
        gluCylinder(pObj,36.0f,32.0f,6.0f,8,1);

        RGB_Color(224,50,0);
        glTranslatef(0.0f,0.0f,6.0f);
        gluCylinder(pObj,32.0f,30.0f,2.5f,8,1);

        RGB_Color(148,94,92);
        glTranslatef(0.0f,0.0f,2.5f);
        gluCylinder(pObj,30.0f,29.5f,0.5f,8,1);

        RGB_Color(224,50,0);
        glTranslatef(0.0f,0.0f,0.5f);
        gluCylinder(pObj,29.5f,29.5f,16.0f,8,1);
    }
    glPopMatrix();

    /* Red Quad *2 */
    glPushMatrix();
    {
        scaleObjects(1.1);
        RGB_Color(223,100,0);
        for(int i = 0; i < 8; i++)
        {
            glRotatef(45,0,1,0);
            glPushMatrix();
            {
                glTranslatef(0.0f,9.0f,25.0);
                //left
                glBegin(GL_QUAD_STRIP);
                {
                    glVertex3f(-10.5f,18.0f,0.0f);
                    glVertex3f(-10.5f,18.0f,0.5f);
                    glVertex3f(-10.5f,33.0f,0.0f);
                    glVertex3f(-10.5f,33.0f,0.5f);
                    glVertex3f(-7.04f,33.0f,0.0f);
                    glVertex3f(-7.04f,33.0f,0.5f);
                    glVertex3f(-7.04f,18.0f,0.0f);
                    glVertex3f(-7.04f,18.0f,0.5f);
                }
                glEnd();

                glBegin(GL_QUAD_STRIP);
                {
                    A[0] = -10.5f , A[1] = 18.0f, A[2] = 0.5f;
                    B[0] = -7.04f , B[1] = 18.0f, B[2] = 0.5f;
                    C[0] = -10.5f , C[1] = 33.0f, C[2] = 0.5f;

                    ComputeNormal(A,B,C);
                    glVertex3f(-10.5f,18.0f,0.5f);
                    glVertex3f(-7.04f,18.0f,0.5f);

                    A[1] = 33.0f, A[2] = 0.0f;
                    B[1] = 33.0f, B[2] = 0.5f;
                    C[1] = 18.0f, C[2] = 0.5f;

                    ComputeNormal(C,B,A);
                    glVertex3f(-10.5f,33.0f,0.5f);
                    glVertex3f(-7.04f,33.0f,0.5f);


                    glVertex3f(-10.5f,33.0f,0.0f);
                    glVertex3f(-7.04f,33.0f,0.0f);
                    glVertex3f(-10.5f,18.0f,0.0f);
                    glVertex3f(-7.04f,18.0f,0.0f);
                }
                glEnd();

                glBegin(GL_QUAD_STRIP);
                {
                    glVertex3f(+7.04f,18.0f,0.0f);
                    glVertex3f(+7.04f,18.0f,0.5f);
                    glVertex3f(+7.04f,33.0f,0.0f);
                    glVertex3f(+7.04f,33.0f,0.5f);
                    glVertex3f(+10.5f,33.0f,0.0f);
                    glVertex3f(+10.5f,33.0f,0.5f);
                    glVertex3f(+10.5f,18.0f,0.0f);
                    glVertex3f(+10.5f,18.0f,0.5f);
                }
                glEnd();

                glBegin(GL_QUAD_STRIP);
                {
                    A[0] = +7.04f , A[1] = 18.0f, A[2] = 0.5f;
                    B[0] = +10.5f, B[1] = 18.0f, B[2] = 0.5f;
                    C[0] = +7.04f , C[1] = 33.0f, C[2] = 0.5f;

                    ComputeNormal(A,B,C);
                    glVertex3f(+7.04f,18.0f,0.5f);
                    glVertex3f(+10.5f,18.0f,0.5f);

                    A[1] = 33.0f, A[2] = 0.0f;
                    B[1] = 33.0f, B[2] = 0.5f;
                    C[1] = 18.0f, C[2] = 0.5f;

                    ComputeNormal(C,B,A);
                    glVertex3f(+7.04f,33.0f,0.5f);
                    glVertex3f(+10.5f,33.0f,0.5f);
                    glVertex3f(+7.04f,33.0f,0.0f);
                    glVertex3f(+10.5f,33.0f,0.0f);
                    glVertex3f(+7.04f,18.0f,0.0f);
                    glVertex3f(+10.5f,18.0f,0.0f);
                }
                glEnd();
            }
            glPopMatrix();
        }

    }
    glPopMatrix();

    /* Surface */
    glPushMatrix();
    {
        for(int j = 0; j < 8;j++)
        {
            glRotatef(45,0,1,0);
            glPushMatrix();
                float r = 2.0f;
                glTranslatef(-10.0f,32.0f,0.0f);
                for(int i = 0; i < 3;i++)
                {
                    glTranslatef(5.0f,0.0f,0.0f);
                    glPushMatrix();
						glTranslatef(0.0f,0.0f,28.0f);
						glBegin(GL_QUADS);
						{
							A[0] = -r , A[1] = 0.0f, A[2] = 0.0f;
							B[0] = -r , B[1] = +2*r  , B[2] = 0.0f;
							C[1] = +r , C[1] = 0.0f, C[2] = 0.0f;
							ComputeNormal(C,B,A);
							RGB_Color(215,38,2);
							glVertex3f(-r, 0.0f , 0.0f);
							glVertex3f(-r, +2*r , 0.0f);
							glVertex3f(+r, +2*r , 0.0f);
							glVertex3f(+r, 0.0f, 0.0f);

							A[0] = -0.67*r , A[1] = 0.0f+0.33*r, A[2] = 0.1f;
							B[0] = -0.67*r , B[1] = +1.34*r+0.33*r  , B[2] = 0.1f;
							C[1] = +0.67*r , C[1] = 0.0f+0.33*r, C[2] = 0.1f;
							RGB_Color(176,172,176);
							ComputeNormal(C,B,A);
							glVertex3f(-0.67*r, 0.0f+0.33*r , 0.1f);
							glVertex3f(-0.67*r, +1.34*r+0.33*r , 0.1f);
							glVertex3f(+0.67*r, +1.34*r+0.33*r, 0.1f);
							glVertex3f(+0.67*r, 0.0f+0.33*r, 0.1f);

							A[0] = -0.33*r , A[1] = 0.0f+0.66*r, A[2] = 0.2f;
							B[0] = -0.33*r , B[1] = +0.33*r+0.66*r  , B[2] = 0.2f;
							C[1] = +0.33*r , C[1] = 0.0f+0.66*r, C[2] = 0.2f;
							RGB_Color(123,108,108);
							ComputeNormal(C,B,A);
							glVertex3f(-0.33*r, 0.0f+0.66*r , 0.2f);
							glVertex3f(-0.33*r, +0.66*r+0.66*r , 0.2f);
							glVertex3f(+0.33*r, +0.66*r+0.66*r , 0.2f);
							glVertex3f(+0.33*r, 0.0f+0.66*r, 0.2f);
						}
						glEnd();

						glBegin(GL_TRIANGLES);
						{
							A[0] = -0.67*r , A[1] = 1.67*r, A[2] = 0.1f;
							B[0] = 0.0f ,    B[1] = +0.33*r+5*r  , B[2] = 0.1f;
							C[1] = +0.67*r , C[1] = 1.67*r, C[2] = 0.1f;
							RGB_Color(215,38,2);
							ComputeNormal(C,B,A);
							glVertex3f( -0.67*r, +1.67*r ,0.1f );
							glVertex3f( 0.0f, +5*r+0.33*r ,0.1f );
							glVertex3f( +0.67*r, +1.67*r ,0.1f );

							A[0] = -r , A[1] = +2*r, A[2] = 0.0f;
							B[0] = 0  , B[1] = +5*r , B[2] = 0.0f;
							C[1] = r  , C[1] = +2*r, C[2] = 0.0f;
							RGB_Color(215,18,2);
							ComputeNormal(C,B,A);
							glVertex3f( -r, 2*r ,0.0f );
							glVertex3f( 0.0f, +5*r+1*r ,0.0f );
							glVertex3f( r, +2*r ,0.0f );
						}
						glEnd();
					glPopMatrix();
				}
            glPopMatrix();
        }
    }
    glPopMatrix();

    /*Connectors*/
    glPushMatrix();
    {
        RGB_Color(180,179,175);
        glRotatef(270,1,0,0);
        glRotatef(22.5,0,0,1);
        glTranslatef(0.0f,0.0f,46.0f);
        gluCylinder(pObj,30.5f,31.5f,1.5f,8,1);

        RGB_Color(255,255,255);
        glTranslatef(0.0f,0.0f,1.5f);
        gluCylinder(pObj,31.5f,31.0f,1.5f,8,1);

        RGB_Color(2,138,115);
        glTranslatef(0.0f,0.0f,1.5f);
        gluCylinder(pObj,31.0f,26.0f,3.0f,8,1);

        RGB_Color(225,60,0);
        glTranslatef(0.0f,0.0f,3.0f);
        gluCylinder(pObj,26.0f,26.0f,30.0f,8,1);

        RGB_Color(180,179,175);
        glTranslatef(0.0f,0.0f,30.0f);
        gluCylinder(pObj,26.0f,27.0f,0.5f,8,1);

        RGB_Color(255,255,255);
        glTranslatef(0.0f,0.0f,0.5f);
        gluCylinder(pObj,27.0f,26.0f,0.5f,8,1);

        RGB_Color(225,60,0);
        glTranslatef(0.0f,0.0f,0.5f);
        gluCylinder(pObj,26.0f,26.0f,2.0f,8,1);

        RGB_Color(180,179,175);
        glTranslatef(0.0f,0.0f,2.0f);
        gluCylinder(pObj,26.0f,27.0f,0.5f,8,1);

        RGB_Color(255,255,255);
        glTranslatef(0.0f,0.0f,0.5f);
        gluCylinder(pObj,27.0f,26.0f,0.5f,8,1); //86.5

    }
    glPopMatrix();

    /*Red Cylinders */ ///<- Dalek balls added
    glPushMatrix();
    glRotatef(22.5,0,1,0);
    for(int i = 0;i<8;i++)
    {
        glRotatef(45,0,1,0);
        glPushMatrix();
        {
            glRotatef(270,1,0,0);
            glTranslatef(0,26,50);
            RGB_Color(223,100,0);
            gluCylinder(pObj,2,2,36,6,1);

            RGB_Color(179,185,182);
            for(int i = 0 ; i < 5; i++)
            {
                gluCylinder(pObj,2,3,0.5,6,1);
                glTranslatef(0,0,0.5);
                gluCylinder(pObj,3,3,3.0,6,1);

                glTranslatef(0,0,3.0);
                gluCylinder(pObj,3,2,0.5,6,1);
                glTranslatef(0,0,4.5);
            }
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(22.5,0,1,0);
            glRotatef(180,1,0,0);
            glTranslatef(0,-50,25);
            for(int i = 0; i < 6; i++)
            {
                RGB_Color(243,229,168);
                glTranslatef(0.1,-5,0.1);
                gluSphere(pObj,2.0f,6,4);
            }
        }
        glPopMatrix();
    }
    glPopMatrix();

    /* Connectors */
    glPushMatrix();
    {

        glRotatef(270,1,0,0);
        glRotatef(22.5,0,0,1);
        glTranslatef(0,0,86);
        RGB_Color(225,50,0);
        gluCylinder(pObj,26.0f,28.0f,0.5f,8,1);

        glTranslatef(0,0,0.5f);
        gluCylinder(pObj,28.0f,30.0f,2.0f,8,1);

        RGB_Color(181,182,183);
        glTranslatef(0,0,2.0f);
        gluCylinder(pObj,30.0f,31.0f,0.5f,8,1);

        RGB_Color(220,220,220);
        glTranslatef(0,0,0.5f);
        gluCylinder(pObj,31.0f,30.0f,0.5f,8,1);

        ///Dalek Part
        RGB_Color(136,112,89);
        glTranslatef(0,0,0.5);
        gluCylinder(pObj,23.0f,21.4f,25.0f,16,1);

        ///Dalek Part
        RGB_Color(255,250,157);
        glTranslatef(0,0,-5.0f);

        for(int i = 0; i < 4; i++)
        {
           glTranslatef(0,0,6.0f);
           gluCylinder(pObj,23.5f,23.5f,2.5f,16,1);
        }


    }
    glPopMatrix();

    glPushMatrix();
    for(int i = 0; i<1; i++)
    {
        glPushMatrix();
        {
            glPushMatrix();
            glTranslatef(0,89,0);
            for(int i = 0; i < 8 ;i++)
            {
                glRotatef(45,0,1,0);
                glPushMatrix();
                    glTranslatef(0,0,27.0f);
                    drawSemiCylinder_MediumDome2();
                    glDisable(GL_CULL_FACE);
                glPopMatrix();
            }
            glPopMatrix();

            glPushMatrix();
            {
                float m = 0.5f;
                glTranslatef(0,95,0);
                glRotatef(22.5,0,1,0);
                scaleObjects(m);
                for(int i = 0; i < 8 ;i++)
                {
                    glRotatef(45,0,1,0);
                    glPushMatrix();
                        glTranslatef(0,0,27.0f*(1/m));
                        drawSemiCylinder_MediumDome2();
                        glDisable(GL_CULL_FACE);
                    glPopMatrix();
                }
            }
            glPopMatrix();



        }
        glPopMatrix();
        glTranslatef(0,20.0f,0);
        scaleObjects(0.90);

    }
    glPopMatrix();

    /*More Dalek Start Here */
    glPushMatrix();
        glTranslatef(0,115,0);
        RGB_Color(255,250,157);
        gluSphere(pObj,21.0f,16,16);

        glTranslatef(17.89,7.89,14);
        RGB_Color(173,161,109);
        gluSphere(pObj,5.0f,8,4);

        RGB_Color(117,221,219);
        glRotatef(90,0,1,1);
        gluCylinder(pObj,1,1,30,6,1);

        RGB_Color(180,156,218);
        glTranslatef(0,0,15);
        gluSphere(pObj,2.0f,8,4);

        RGB_Color(0,0,0);
        glTranslatef(0,0,15);
        gluSphere(pObj,3.0f,8,4);

        RGB_Color(115,104,208);
        glTranslatef(0,0,3);
        gluSphere(pObj,2.0f,8,4);
    glPopMatrix();



    gluDeleteQuadric(pObj);
    glEnable(GL_CULL_FACE);

}

void St_Basils_Cathedral::drawSmallDome1() //North-West Small Dome
{
    glPushMatrix();
        drawWall_Small();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,54.0f,0.0f);
        scaleObjects(14.0f);
        drawDomeTop_1();
    glPopMatrix();
}

void St_Basils_Cathedral::drawSmallDome2() //North-East Small Dome
{
    glPushMatrix();
        drawWall_Small();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,54.0f,0.0f);
        scaleObjects(14.0f);
        drawDomeTop_2();
    glPopMatrix();
}

void St_Basils_Cathedral::drawSmallDome3() //South-East Small Dome
{
    glPushMatrix();
        drawWall_Small();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,54.0f,0.0f);
        scaleObjects(14.0f);
        drawDomeTop_4();
    glPopMatrix();
}

void St_Basils_Cathedral::drawSmallDome4() //South-West Small Dome
{
    glPushMatrix();
        drawWall_Small();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0f,54.0f,0.0f);
        scaleObjects(14.0f);
        drawDomeTop_5();
    glPopMatrix();
}

void St_Basils_Cathedral::drawMediumDome1() //East Dome
{
    glPushMatrix();
        drawWall_Medium1();
    glPopMatrix();

    glPushMatrix();
        glRotatef(22.5,0,1,0);
        glTranslatef(0.0f,100.0f,0.0f);
        scaleObjects(24.5f);
        drawDomeTop_3();
    glPopMatrix();
}

void St_Basils_Cathedral::drawMediumDome2() //North Dome
{
     glPushMatrix();
        drawWall_Medium2();
    glPopMatrix();

    glPushMatrix();
        glRotatef(22.5,0,1,0);
        glTranslatef(0.0f,100.5f,0.0f);
        scaleObjects(26.5f);
        drawDomeTop_6();
    glPopMatrix();
}

void St_Basils_Cathedral::drawMediumDome3() //West Dome
{
    glPushMatrix();
        drawWall_Medium1();
    glPopMatrix();

    glPushMatrix();
        glRotatef(22.5,0,1,0);
        glTranslatef(0.0f,100.5f,0.0f);
        scaleObjects(24.8f);
        drawDomeTop_7();
    glPopMatrix();
}

void St_Basils_Cathedral::drawMediumDome4() //South Dome
{
    glPushMatrix();
        drawWall_Medium3();
    glPopMatrix();

    glPushMatrix();
        glRotatef(22.5,0,1,0);
        glTranslatef(0.0f,94.0f,0.0f);
        scaleObjects(18.5f);
        drawDomeTop_8();
    glPopMatrix();
}

void St_Basils_Cathedral::drawCenterDome() //Center
{
    glPushMatrix();
        drawWall_Center();
    glPopMatrix();
}

void St_Basils_Cathedral::drawBase()
{
    glDisable(GL_CULL_FACE);
	GLUquadricObj *pObj;
	pObj = gluNewQuadric();
	gluQuadricDrawStyle(pObj, GLU_FILL);

    glPushMatrix();
        RGB_Color(118,135,67);
        glRotatef(270,1,0,0);
        gluDisk(pObj,0,80,16,4);
        gluCylinder(pObj,80,80,5,16,1);
        glTranslatef(0.0f,00.0f,5.0f);
        gluDisk(pObj,0,80,16,4);
    glPopMatrix();
    gluDeleteQuadric(pObj);
}

void St_Basils_Cathedral::drawKremlinAndRedSquare()
{
    glPushMatrix();
    {
        scaleObjects(1.1f);
        glPushMatrix();
            drawBase();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f,5.0f,0.0f);
            scaleObjects(0.7);
            drawCenterDome();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-55.0f,5.0f,0.0f);
            scaleObjects(0.6);
            drawMediumDome1();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f,5.0f,-55.0f);
            scaleObjects(0.6);
            drawMediumDome2();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(55.0,5.0f,0.0f);
            scaleObjects(0.6);
            drawMediumDome3();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0,5.0f,55.0f);
            scaleObjects(0.7);
            drawMediumDome4();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-35.0,5.0f,-35.0f);
            scaleObjects(0.7);
            drawSmallDome2();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(+35.0,5.0f,-35.0f);
            scaleObjects(0.7);
            drawSmallDome1();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-35.0,5.0f,+35.0f);
            scaleObjects(0.7);
            drawSmallDome3();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(+35.0,5.0f,+35.0f);
            scaleObjects(0.7);
            drawSmallDome4();
        glPopMatrix();
    }
    glPopMatrix();
}
