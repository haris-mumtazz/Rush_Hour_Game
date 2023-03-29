//============================================================================
// Name        : Rush Hour
// Author      : Muhammad Haris Mumtaz
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
 
int axis[400][2], OccupiedArea[400], BuildingsX[100], BuildingsY[100], TreesX[5], TreesY[5];
int BoxesX[5], BoxesY[5], PassengerX[5], PassengerY[5];
int Score=0, PassengerInCar=0, PassengerDrop=0, DestinationX, DestinationY;
bool RandFlag=false, PickupFlag=false, StartMenuFlag=false, ColourFlag=false, EndGameFlag=false;
int *AIcarsX, *AIcarsY;
char *AImove; 
int CarNum=4;
float Speed=1;
char Name, TaxiColour;

 
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


void InitialDefiner()
{
	int xVal=200, yVal=765, x[20], y[20], k=0;
	
	for (int i=0; i<20; ++i)
	{
		x[i]=xVal;
		xVal += 40;
		y[i]=yVal;
		yVal -= 40;
	}
	
	for (int i=0; i<20; ++i)
	{
		for (int j=0; j<20; ++j)
		{
			axis[k][0]=x[j];
			axis[k][1]=y[i];
			++k;
		}
	}
	
	for (int i=0; i<400; ++i)
	{
		OccupiedArea[i]=0;
	}
	OccupiedArea[0]=1; OccupiedArea[20]=1; OccupiedArea[1]=1;
	
	AIcarsX = new int [CarNum];
	AIcarsY = new int [CarNum];
}


void Grid()
{
	for (int i=4; i<804; i += 40)
	{
		DrawLine(200, i+40, 1000, i+40, 1, colors[DARK_GRAY]);
		
		for (int j=200; j<=1000; j+=40)
		{
			DrawLine(j, i, j, i+40, 1, colors[DARK_GRAY]);
		}
	}
}

void Borders()
{
	DrawRectangle(0,0,200,840+1,colors[BLACK]);
	DrawRectangle(1000,0,110+1,840+1,colors[BLACK]);
	DrawRectangle(0,0,1021,10-4,colors[BLACK]);	
	DrawRectangle(0,804+1,1020+1,40,colors[BLACK]);
}



void RandomGen()
{
	int n;
	bool free=false;
	
	for (int i=0; i<100; ++i)
	{
		free=false;
		while (free==false)
		{
			n=GetRandInRange(0,399);
			if (OccupiedArea[n]==0 && OccupiedArea[n-20-1]==0 && OccupiedArea[n-20+1]==0 && OccupiedArea[n+20-1]==0 && OccupiedArea[n+20+1]==0) 
			{
				free=true;
				OccupiedArea[n]=1;
			}
		}
		BuildingsX[i]=axis[n][0];
		BuildingsY[i]=axis[n][1];
	}
	
	for (int i=0; i<5; ++i)
	{
		free=false;
		while (free==false)
		{
			n=GetRandInRange(0,399);
			if (OccupiedArea[n]==0) 
			{
				free=true;
				OccupiedArea[n]=1;
			}
		}
		TreesX[i]=axis[n][0];
		TreesY[i]=axis[n][1];
	}
	
	for (int i=0; i<5; ++i)
	{
		free=false;
		while (free==false)
		{
			n=GetRandInRange(0,399);
			if (OccupiedArea[n]==0) 
			{
				free=true;
				OccupiedArea[n]=1;
			}
		}
		BoxesX[i]=axis[n][0];
		BoxesY[i]=axis[n][1];
	}
	
	for (int i=0; i<5; ++i)
	{
		free=false;
		while (free==false)
		{
			n=GetRandInRange(0,399);
			if (OccupiedArea[n]==0) 
			{
				free=true;
			}
		}
		PassengerX[i]=axis[n][0];
		PassengerY[i]=axis[n][1];
	}
	
	AIcarsX = new int [CarNum]; AIcarsY = new int [CarNum]; 
	for (int i=0; i<4; ++i)
	{
		free=false;
		while (free==false)
		{
			n=GetRandInRange(0,399);
			if (OccupiedArea[n]==0) 
			{
				free=true;
			}
		}
		AIcarsX[i]=axis[n][0];
		AIcarsY[i]=axis[n][1];
	}
	
	AImove = new char [CarNum];
	
	
	for (int i=0; i<4; ++i)
	{
		n=GetRandInRange(1,4);
		switch(n)
		{
			case 1: AImove[i]='l';
			break;
			case 2: AImove[i]='r';
			break;
			case 3: AImove[i]='u';
			break;
			case 4: AImove[i]='d';
			break;	
		}	
		
	}	
	RandFlag=true;
}

void CarGenerator(int i)
{
	cout << CarNum <<endl;
	/*int n;
	bool free=false;
	while (free==false)
	{
		n=GetRandInRange(0,399);
		if (OccupiedArea[n]==0) 
		{
			free=true;
		}
	}
	AIcarsX[i]=axis[n][0];
	AIcarsY[i]=axis[n][1];
	
	n=GetRandInRange(1,4);
	switch(n)
	{
		case 1: AImove[i]='l';
		break;
		case 2: AImove[i]='r';
		break;
		case 3: AImove[i]='u';
		break;
		case 4: AImove[i]='d';
		break;
			
	} */
	
	AIcarsX[i]=1000-30;
	AIcarsY[i]=765;
	AImove[i]='l';
}

void Buildings()
{
	
	for (int j=0; j<100; ++j)
	{
		DrawSquare(BuildingsX[j], BuildingsY[j], 40, colors[BLACK]);
	}
}

void Obstacles()
{
	for (int i=0; i<5; ++i)
	{
		DrawLine(TreesX[i]+20, TreesY[i], TreesX[i]+20, TreesY[i]+10, 4, colors[BROWN]);
		DrawTriangle(TreesX[i]+20-20+10, TreesY[i]+10, TreesX[i]+20, TreesY[i]+30, TreesX[i]+20+20-10, TreesY[i]+10, colors[DARK_GREEN]);
	}
	
	for (int i=0; i<5; ++i)
	{
		DrawSquare(BoxesX[i]+10, BoxesY[i]+10, 20, colors[BROWN]);
	}
}

void Maze()
{
	Grid();
	Borders();
	if (RandFlag==false) RandomGen();
	Buildings();
	Obstacles();
	
}

void PassengerGenerator(int x)
{
	int num;
	bool free=false;
	while (free==false)
	{
		num=GetRandInRange(0,399);
		if (OccupiedArea[num]==0) 
		{
			free=true;
		}
	}
	PassengerX[x]=axis[num][0];
	PassengerY[x]=axis[num][1];
}

void Destination()
{
	DrawSquare(DestinationX, DestinationY, 40, colors[LAWN_GREEN]);
}

void Passengers()
{
	for (int i=0; i<5; ++i)
	{
		DrawCircle(PassengerX[i]+20, PassengerY[i]+25, 5, colors[BLACK]);
		DrawLine(PassengerX[i]+20, PassengerY[i]+20, PassengerX[i]+20, PassengerY[i]+10, 2, colors[BLACK]);
		DrawLine(PassengerX[i]+20, PassengerY[i]+10, PassengerX[i]+20-5, PassengerY[i], 2, colors[BLACK]);
		DrawLine(PassengerX[i]+20, PassengerY[i]+10, PassengerX[i]+20+5, PassengerY[i], 2, colors[BLACK]);
		DrawLine(PassengerX[i]+20-5, PassengerY[i]+17-5, PassengerX[i]+20, PassengerY[i]+17, 1.5, colors[BLACK]);
		DrawLine(PassengerX[i]+20+5, PassengerY[i]+17-5, PassengerX[i]+20, PassengerY[i]+17, 1.5, colors[BLACK]);
	}
}


void AIcars()
{
	for (int i=0; i<CarNum; ++i)
	{
		DrawSquare(AIcarsX[i], AIcarsY[i], 30, colors[AQUA]);	
	}
}


int xI = 200, yI = 775;

void drawCar() 
{
	if (TaxiColour=='y') DrawSquare(xI, yI, 30, colors[YELLOW]);
	else DrawSquare(xI, yI, 30, colors[RED]);
	glutPostRedisplay();
}

string name;
void NameGen()
{	
	name += Name;
}



void DisplayName()
{

	DrawRectangle(0,0,1021,841,colors[BLACK]);
	DrawRectangle(190 , 205 , 320+240, 160+240, colors[WHITE]);	
	DrawString(300,500,name,colors[GREEN]);
	DrawString(300,400,"Press space to start the game",colors[GREEN]);
}

void ColourMenu()
{
	DrawRectangle(0,0,1300,900,colors[BLACK]);
	DrawRectangle(180,205,320+250,160+250,colors[WHITE]);
	DrawString(390,450,"Choose your taxi:",colors[BLACK]);
	DrawString(370,350,"Press r for red taxi",colors[RED]);
	DrawString(370,390,"Press y for yellow taxi",colors[YELLOW]);
	DrawString(370,320,"Press a for any",colors[BLACK]);		
}

void DisplayScore()
{
	string score = to_string(Score);
	
	DrawRectangle(10,605,100,80,colors[WHITE]);
	DrawString(15,655,"SCORE",colors[RED]);
	DrawString(40,620,score,colors[RED]);	
	
}

float GameTimer=9000;
void DisplayTimer()
{
	int gametimer= GameTimer / (10*5);
	
	string timer = to_string(gametimer);
	
	DrawRectangle(10,405,100,80,colors[WHITE]);
	DrawString(15,455,"TIMER",colors[RED]);
	DrawString(40,420,timer,colors[RED]);
}

void FinalScore()
{
	string score = to_string(Score);
	
	DrawRectangle(0,0,1300,900,colors[BLACK]);
	DrawRectangle(310,325,330,160,colors[WHITE]);
	DrawString(410,430,"Your Score",colors[BLACK]);
	DrawString(450,365,score,colors[BLACK]);	
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 1 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	
	
	{
		Maze();
		Passengers();
		if (PickupFlag == true)	Destination();	
		AIcars();
		drawCar();
	}
	DisplayScore();
	DisplayTimer();
	if (StartMenuFlag==false)
	{
		DisplayName();
	}
	if(ColourFlag==false && StartMenuFlag==true)
	{
		ColourMenu();
	}
	if(EndGameFlag==true)
	{
		FinalScore();
	}
	
	
	
	glutSwapBuffers(); // do not modify this line..
}


void Lboundary()
{
	if (xI <= 200)	xI += 10;
}

void Rboundary()
{
	if (xI >= 1000-30)	xI -= 10;
}

void Uboundary()
{
	if (yI >= 804-30)	yI -= 10;
}

void Dboundary()
{
	if (yI <= 5)	yI += 10;
}


void Lbuilding()
{
	for (int i=0; i<100; ++i)
	{
		if ((xI > BuildingsX[i] && xI <= BuildingsX[i]+40) && (yI > BuildingsY[i]-30 && yI < BuildingsY[i]+40)) xI += 10;	
	}
}

void Rbuilding()
{
	for (int i=0; i<100; ++i)
	{
		if ((xI >= BuildingsX[i]-30 && xI < BuildingsX[i]+40) && (yI > BuildingsY[i]-30 && yI < BuildingsY[i]+40)) xI -= 10;	
	}
}

void Ubuilding()
{
	for (int i=0; i<100; ++i)
	{
		if ((xI > BuildingsX[i]-30 && xI < BuildingsX[i]+40) && (yI >= BuildingsY[i]-30 && yI < BuildingsY[i]+40)) yI -= 10;	
	}
}

void Dbuilding()
{
	for (int i=0; i<100; ++i)
	{
		if ((xI > BuildingsX[i]-30 && xI < BuildingsX[i]+40) && (yI > BuildingsY[i] && yI <= BuildingsY[i]+40)) yI += 10;	
	}
}


void Lbox()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > BoxesX[i]+10 && xI <= BoxesX[i]-10+40) && (yI > BoxesY[i]+10-30 && yI < BoxesY[i]-10+40)) 
		{
			xI += 20;
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}		
	}
}

void Rbox()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI >= BoxesX[i]+10-30 && xI < BoxesX[i]-10+40) && (yI > BoxesY[i]+10-30 && yI < BoxesY[i]-10+40)) 
		{
			xI -= 20;	
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}
	}
}

void Ubox()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > BoxesX[i]+10-30 && xI < BoxesX[i]-10+40) && (yI >= BoxesY[i]+10-30 && yI < BoxesY[i]-10+40)) 
		{
			yI -= 20;
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;	
		}
	}
}

void Dbox()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > BoxesX[i]+10-30 && xI < BoxesX[i]-10+40) && (yI > BoxesY[i]+10 && yI <= BoxesY[i]-10+40)) 
		{
			yI += 20;	
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}
	}
}


void Ltree()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > TreesX[i]+10 && xI <= TreesX[i]-10+40) && (yI > TreesY[i]-30 && yI < TreesY[i]-10+40)) 
		{
			xI += 20;
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}		
	}
}

void Rtree()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI >= TreesX[i]+10-30 && xI < TreesX[i]-10+40) && (yI > TreesY[i]-30 && yI < TreesY[i]-10+40)) 
		{
			xI -= 20;	
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}
	}
}

void Utree()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > TreesX[i]+10-30 && xI < TreesX[i]-10+40) && (yI >= TreesY[i]-30 && yI < TreesY[i]-10+40)) 
		{
			yI -= 20;
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}
	}
}

void Dtree()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > TreesX[i]+10-30 && xI < TreesX[i]-10+40) && (yI > TreesY[i]+10 && yI <= TreesY[i]-10+40)) 
		{
			yI += 20;	
			if (TaxiColour=='y') Score -= 4;
			else Score -= 2;
		}
	}
}


void Lpassenger()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > PassengerX[i]+10 && xI <= PassengerX[i]-10+40) && (yI > PassengerY[i]-30 && yI < PassengerY[i]-10+40)) 
		{
			xI += 20;
			Score -= 5;
		}		
	}
}

void Rpassenger()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI >= PassengerX[i]+10-30 && xI < PassengerX[i]-10+40) && (yI > PassengerY[i]-30 && yI < PassengerY[i]-10+40)) 
		{
			xI -= 20;	
			Score -= 5;
		}
	}
}

void Upassenger()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > PassengerX[i]+10-30 && xI < PassengerX[i]-10+40) && (yI >= PassengerY[i]-30 && yI < PassengerY[i]-10+40)) 
		{
			yI -= 20;
			Score -= 5;	
		}
	}
}

void Dpassenger()
{
	for (int i=0; i<5; ++i)
	{
		if ((xI > PassengerX[i]+10-30 && xI < PassengerX[i]-10+40) && (yI > PassengerY[i]+10 && yI <= PassengerY[i]-10+40)) 
		{
			yI += 20;	
			Score -= 5;
		}
	}
}


/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT)  
	{
		Lboundary();
		Lbuilding();
		Lbox();
		Ltree();
		Lpassenger();
		
		if (TaxiColour=='y') xI -= 10;
		else xI -= 5;
	}
	
	else if (key == GLUT_KEY_RIGHT) 
	{
		Rboundary();
		Rbuilding();
		Rbox();
		Rtree();
		Rpassenger();
		
		if (TaxiColour=='y') xI += 10;
		else xI += 5;
	}
	
	else if (key == GLUT_KEY_UP)
	{
		Uboundary();
		Ubuilding();
		Ubox();
		Utree();
		Upassenger();
		
		if (TaxiColour=='y') yI += 10;
		else yI +=5;
	}

	else if (key == GLUT_KEY_DOWN)
	{
		Dboundary();
		Dbuilding();
		Dbox();
		Dtree();
		Dpassenger();
		
		if (TaxiColour=='y') yI -= 10;
		else yI -= 5;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}


void Pickup()
{	
	int n;
	int free=false;
	for (int i=0; i<5; ++i)
	{
		if ( (xI >= PassengerX[i]-30 && yI >= PassengerY[i]-30) && (xI <= PassengerX[i]+40 && yI <= PassengerY[i]+40) )
		{
			PickupFlag=true;
			PassengerX[i]=1;
			PassengerY[i]=1;
			PassengerInCar=i;
			while (free==false)
			{
				n=GetRandInRange(0,399);
				if (OccupiedArea[n]==0) 
				{
					free=true;
				}
			}
			DestinationX=axis[n][0];
			DestinationY=axis[n][1];
			break;
		}
			
	}
}


void Drop()
{
	if( (xI >= DestinationX && xI <= DestinationX+10) && (yI >= DestinationY && yI <= DestinationY+10) )
	{
		PickupFlag=false;
		Score += 10;
		if (PassengerDrop == 0) PassengerDrop += 1;
		else 
		{
			PassengerDrop=0;
			CarNum += 1;
			CarGenerator(CarNum-1);
			Speed += 1;
		}
		cout << PassengerDrop <<endl;
		
		PassengerGenerator(PassengerInCar);
	}	
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	char alpha;
	if (StartMenuFlag==false)
	{
		if ( (key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z') )
		{
			//alpha=key;
			//Name(to_string(alpha)); 
			Name=key;
			NameGen();
		}
		if ( key == ' ' )
		{
			StartMenuFlag=true;
		}
	}
	if (key == 27/* Escape key ASCII*/) 
	{
		delete [] AIcarsX;
		delete []AIcarsY;
		delete [] AImove; 
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == ' ')
	{
		if (PickupFlag == false) Pickup();
		else Drop();
	}
	
	if (ColourFlag==false && StartMenuFlag==true)
	{
		if (key == 'y')
		{
			if (ColourFlag == false)
			{
				TaxiColour='y';
				ColourFlag=true;
				GameTimer=9000;
			}
		}
		
		if (key == 'r')
		{
			if (ColourFlag == false)
			{
				TaxiColour='r';
				ColourFlag=true;
				GameTimer=9000;
			}
		}
		
		if (key == 'a')
		{
			if (ColourFlag==false)
			{
				if (GetRandInRange(1,1000) > 500)	TaxiColour='y';
				else TaxiColour='r';
				ColourFlag=true;
				GameTimer=9000;
			}
		}
	}	
	glutPostRedisplay();
}


void LcollisionAI(int i)
{
	int n=GetRandInRange(1,300);
	switch(n)
	{
		case 1 ... 100: AImove[i] = 'r';
		break;
		case 101 ... 200: AImove[i] = 'd';
		break;
		case 201 ... 300: AImove[i] = 'u';
		break;
	}
}

void RcollisionAI(int i)
{
	int n=GetRandInRange(1,300);
	switch(n)
	{
		case 1 ... 100: AImove[i] = 'l';
		break;
		case 101 ... 200: AImove[i] = 'u';
		break;
		case 201 ... 300: AImove[i] = 'd';
		break;
	}
}

void UcollisionAI(int i)
{
	int n=GetRandInRange(1,300);
	switch(n)
	{
		case 1 ... 100: AImove[i] = 'r';
		break;
		case 101 ... 200: AImove[i] = 'l';
		break;
		case 201 ... 300: AImove[i] = 'd';
		break;
	}
}

void DcollisionAI(int i)
{
	int n=GetRandInRange(1,3);
	switch(n)
	{
		case 1 : AImove[i] = 'r';
		break;
		case 2: AImove[i] = 'l';
		break;
		case 3: AImove[i] = 'u';
		break;
		default: AImove[i] = 'u';
	}
}

void LboundaryAI(int x)
{
	if (AIcarsX[x] <= 200)	
	{
		LcollisionAI(x);
		AIcarsX[x] += 5;

	}
}

void RboundaryAI(int x)
{
	if (AIcarsX[x] >= 1000-30)	
	{
		RcollisionAI(x);
		AIcarsX[x] -= 5;

	}
	
}

void UboundaryAI(int x)
{
	if (AIcarsY[x] >= 804-30)	
	{
		UcollisionAI(x);
		AIcarsY[x] -= 5;

	}
}

void DboundaryAI(int x)
{
	if (AIcarsY[x] <= 5)
	{

		AIcarsY[x] += 10;
		// DcollisionAI(x);
		AImove[x] = 'u';
	}
	
}


void LbuildingAI(int x)
{
	for (int i=0; i<100; ++i)
	{
		if ((AIcarsX[x] > BuildingsX[i] && AIcarsX[x] <= BuildingsX[i]+40) && (AIcarsY[x] > BuildingsY[i]-30 && AIcarsY[x] < BuildingsY[i]+40)) 
		{
			LcollisionAI(x);
			AIcarsX[x] += 5;

		}		
	}
}

void RbuildingAI(int x)
{
	for (int i=0; i<100; ++i)
	{
		if ((AIcarsX[x] >= BuildingsX[i]-30 && AIcarsX[x] < BuildingsX[i]+40) && (AIcarsY[x] > BuildingsY[i]-30 && AIcarsY[x] < BuildingsY[i]+40)) 
		{
			RcollisionAI(x);
			AIcarsX[x] -= 5;

		}
	}
}

void UbuildingAI(int x)
{
	for (int i=0; i<100; ++i)
	{
		if ((AIcarsX[x] > BuildingsX[i]-30 && AIcarsX[x] < BuildingsX[i]+40) && (yI >= BuildingsY[i]-30 && AIcarsY[x] < BuildingsY[i]+40)) 
		{
			UcollisionAI(x);
			AIcarsY[x] -= 5;

		}		
	}
}

void DbuildingAI(int x)
{
	for (int i=0; i<100; ++i)
	{
		if ((AIcarsX[x] > BuildingsX[i]-30 && AIcarsX[x] < BuildingsX[i]+40) && (AIcarsY[x] > BuildingsY[i] && AIcarsY[x] < BuildingsY[i]+40+5)) 
		{
			DcollisionAI(x);
			AIcarsY[x] += 5;
		}	
	}
}


 
void MoveCars()
{

	
	for(int i=0; i<CarNum; ++i)
	{
		if (AIcarsY[i] <= 4) 
		{	
			AIcarsY[i] += 15;
			AImove[i] = 'u';
		}
		switch(AImove[i])
		{
			case 'd': 
			{
				DboundaryAI(i);
				DbuildingAI(i);
				
				AIcarsY[i] -= Speed;
			}
			break;
			case 'u': 
			{
				UboundaryAI(i);
				UbuildingAI(i);
				
				AIcarsY[i] += Speed;
			}
			break;
			case 'r': 
			{
				RboundaryAI(i);
				RbuildingAI(i);
				
				AIcarsX[i] += Speed;
			}	
			break;
			case 'l': 
			{
				LbuildingAI(i);
				LboundaryAI(i);
				AIcarsX[i] -= Speed;
			}
			break;
			
		
		}
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) 
{

	MoveCars();
	GameTimer -= 1;
	if (GameTimer <= 0) EndGameFlag=true; 

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(20, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) 
{

	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	
	InitialDefiner();

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Mohib"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
