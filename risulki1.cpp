#include "TXLib.h"
#include "cmath"

using namespace std;

void txSunset (double x, double y, double radius, double red, double green, double blue);

void DrawGround ();

void DrawMountains (double mount_x1, double mount_x2, double mount_x3, double mount_x4,
    COLORREF snowcol, COLORREF mountcol);

void DrawFunicular (double PeakX, double PeakY, double LowlandX, double LowlandY);

void DrawSnow (double FirstSnowX, double MountainsCoordinates[8][2], int MountainsDotNumber, COLORREF snowcol);

void DrawCabin (double RopeEndX, double RopeEndY, double CabinRatio, double FirstPillarBaseX, double FirstPillarBaseY, double PillarHigh);

void DrawHouse (double x, double y, double scale, double ang, COLORREF house, COLORREF door,
    COLORREF window, COLORREF cross);

void DrawBase (double x, double y, double scale, double ang, COLORREF house, COLORREF door);

void DrawDoor (double x, double y, double scale, COLORREF door);

void DrawWindow (double x, double y, double scale, COLORREF window, COLORREF cross, COLORREF door);

void DrawSmokeTree (double x, double y, double rad, int density, double scale, COLORREF trunk, COLORREF crown);

void DrawRobot (double x, double y, double scale, double AngLA, double AngRA,
    double AngLL, double AngRL, COLORREF robot, COLORREF eyes, COLORREF smile);

void DrawLA (double x, double y, double scale, double AngLA, COLORREF robot);

void DrawRA (double x, double y, double scale, double AngRA, COLORREF robot);

void DrawLL (double x, double y, double scale, double AngLL, COLORREF robot);

void DrawRL (double x, double y, double scale, double AngRL, COLORREF robot);

void DrawEyes (double x, double y, double scale, COLORREF eyes);

void DrawSmile (double x, double y, double scale, COLORREF smile);

void DrawMan ();

void DrawCigarette();

int main()
    {
    txCreateWindow (800, 600);

    txSunset (400, 180, 30, 250, 240, 180);

    DrawGround ();

    DrawMountains (10, 205, 423, 745, RGB (255, 255, 255), TX_GRAY);

    DrawHouse (540, 320, 1, 120 * 3.141592 / 180,
        RGB (185, 122, 87), RGB (103, 65, 44), TX_GRAY, TX_BLACK);

    //DrawSmokeTree (0, 525, 60, 12, 1, RGB (185, 122, 87), TX_GREEN);

    /*DrawRobot (250, 370, 1,
        3.141592 * 1.5, 3.141592 * 1.5,
        3.141592 * 1.5, 3.141592 * 1.5,
        RGB (200, 191, 223), TX_BLACK, TX_BLACK);*/

    //DrawCigarette();

    return 0;
    }

//                                                                        ,
//                                       ,
//          RadiusStop,
void txSunset (double x, double y, double radius, double red, double green, double blue)
    {
    int RadiusStop = 350, i = 0;
    txSetColor (RGB (red, green, blue));
    txSetFillColor (RGB (red, green, blue));
    txCircle (x, y, radius);

    txSetFillColor (TX_TRANSPARENT);
    red = 250;
    green = 90;
    blue = 80;

    while (RadiusStop > radius && blue < 91)
        {
        txSetColor (RGB (red, green, blue), 4);
        txCircle (x, y, radius);
        green += 3;
        blue += 1;
        radius += 3;
        }

    while (red > 10 && green > 49)
        {
        txSetColor (RGB (red, green, blue), 4);
        txCircle (x, y, radius);
        red -= 6;
        green -= 1;
        radius += 3;
        }

    while (i < 100)
        {
        txCircle (x, y, radius);
        radius += 3;
        ++i;
        }
    }

void DrawGround ()
    {
    txSetColor (TX_GREEN);
    txSetFillColor (TX_GREEN);

    txRectangle (0, 400, 800, 600);
    }

void DrawMountains (double mount_x1, double mount_x2, double mount_x3, double mount_x4,
    COLORREF snowcol, COLORREF mountcol)
    {
    txSetColor (mountcol);
    txSetFillColor (mountcol);

    double peak_x[4] = {50,  275, 550, 800},
           peak_y[4] = {150, 170, 120, 120};

    POINT MountainsCoordinatesPoints[10] = {{-50, 320}, {peak_x[0], peak_y[0]}, {150, 240}, {peak_x[1], peak_y[1]},
                                            {400, 270}, {peak_x[2], peak_y[2]}, {675, 270}, {peak_x[3], peak_y[3]},
                                            {800, 400}, {0, 400}};
    txPolygon (MountainsCoordinatesPoints, 10);

    double MountainsCoordinates[9][2];
    MountainsCoordinates[0][0] = 320;
    MountainsCoordinates[0][1] = -50;
    MountainsCoordinates[1][0] = peak_y[0];
    MountainsCoordinates[1][1] = peak_x[0];
    MountainsCoordinates[2][0] = 240;
    MountainsCoordinates[2][1] = 150;
    MountainsCoordinates[3][0] = peak_y[1];
    MountainsCoordinates[3][1] = peak_x[1];
    MountainsCoordinates[4][0] = 270;
    MountainsCoordinates[4][1] = 400;
    MountainsCoordinates[5][0] = peak_y[2];
    MountainsCoordinates[5][1] = peak_x[2];
    MountainsCoordinates[6][0] = 270;
    MountainsCoordinates[6][1] = 675;
    MountainsCoordinates[7][0] = peak_y[3];
    MountainsCoordinates[7][1] = peak_x[3];
    MountainsCoordinates[8][0] = 270;
    MountainsCoordinates[8][1] = 950;

    DrawSnow (mount_x1, MountainsCoordinates, 1, snowcol);

    DrawSnow (mount_x2, MountainsCoordinates, 3, snowcol);

    DrawSnow (mount_x3, MountainsCoordinates, 5, snowcol);
    DrawFunicular (peak_x[2], peak_y[2], MountainsCoordinates[4][1], MountainsCoordinates[4][0]);

    DrawSnow (mount_x4, MountainsCoordinates, 7, snowcol);
    }

void DrawFunicular (double PeakX, double PeakY, double LowlandX, double LowlandY)
    {
    txSetColor (TX_BLACK, 1);
    txSetFillColor (TX_BLACK);

    double MountainDeltaX = PeakX - LowlandX;
    double MountainDeltaY = LowlandY - PeakY;
	double RopeRatio = 0.75;
    double RopeLength = RopeRatio * sqrt (pow (MountainDeltaX, 2) + pow (MountainDeltaY, 2));

    double FunicularAngle = atan (MountainDeltaY / MountainDeltaX);
    double RopeEndX = RopeLength * cos (FunicularAngle);
    double RopeEndY = RopeLength * sin (FunicularAngle);
	double FirstPillarBaseX = LowlandX + 5;
	double FirstPillarBaseY = LowlandY - 5 * tan (FunicularAngle);
	double PillarHigh = 25;

    txLine (FirstPillarBaseX, 			 FirstPillarBaseY - PillarHigh,
			FirstPillarBaseX + RopeEndX, FirstPillarBaseY - PillarHigh - RopeEndY);


    for (double PillarRatio = 0; PillarRatio < 1; PillarRatio += 0.3)
        {
        double PillarX = FirstPillarBaseX + RopeEndX * PillarRatio;
        double PillarY = FirstPillarBaseY - RopeEndY * PillarRatio;

        txLine (PillarX, PillarY, PillarX, PillarY - PillarHigh);
        }

    for (double CabinRatio = 0.1; CabinRatio < 0.9; CabinRatio += 0.1)
        {
        if ((CabinRatio <= 0.28 || 0.32 <= CabinRatio) &&
            (CabinRatio <= 0.58 || 0.62 <= CabinRatio) &&
            (CabinRatio <= 0.88 || 0.92 <= CabinRatio))
            {
            DrawCabin (RopeEndX, RopeEndY, CabinRatio, FirstPillarBaseX, FirstPillarBaseY, PillarHigh);
            }
        }

	double PlatformHigh = 10;
	txLine (FirstPillarBaseX + RopeEndX, FirstPillarBaseY - RopeEndY,
			FirstPillarBaseX + RopeEndX, FirstPillarBaseY - RopeEndY - PlatformHigh);

	double PlatformWidth = PlatformHigh / tan (FunicularAngle);
    txLine (FirstPillarBaseX + RopeEndX, 	 		   	 FirstPillarBaseY - RopeEndY - PlatformHigh,
			FirstPillarBaseX + RopeEndX + PlatformWidth, FirstPillarBaseY - RopeEndY - PlatformHigh);

    double CabinRatio = 1;
    DrawCabin (RopeEndX, RopeEndY, CabinRatio, FirstPillarBaseX, FirstPillarBaseY, PillarHigh);

    txLine (FirstPillarBaseX + RopeEndX,                FirstPillarBaseY - RopeEndY - PillarHigh,
			FirstPillarBaseX + RopeEndX + PlatformWidth, FirstPillarBaseY - RopeEndY - PillarHigh);

    }

void DrawCabin (double RopeEndX, double RopeEndY, double CabinRatio, double FirstPillarBaseX, double FirstPillarBaseY, double PillarHigh)
    {
    double CableLength = 10;
	double CabinHigh = 3;
	double CabinWidth = 6;
    double CabinX = FirstPillarBaseX + RopeEndX * CabinRatio;
	double CabinY = FirstPillarBaseY - RopeEndY * CabinRatio - PillarHigh;

    txLine (CabinX, CabinY,
			CabinX, CabinY + CableLength);

    txRectangle (CabinX - CabinWidth / 2, CabinY + CableLength,
				 CabinX + CabinWidth / 2, CabinY + CableLength + CabinHigh);
    }

void DrawSnow (double FirstSnowX, double MountainsCoordinates[8][2], int MountainsDotNumber, COLORREF snowcol)
    {
    txSetColor (snowcol);
    txSetFillColor (snowcol);

    double LeftAngle  = atan ((MountainsCoordinates[MountainsDotNumber - 1][0] - MountainsCoordinates[MountainsDotNumber]	 [0]) /
							  (MountainsCoordinates[MountainsDotNumber]	   [1] - MountainsCoordinates[MountainsDotNumber - 1][1]));
    double RightAngle = atan ((MountainsCoordinates[MountainsDotNumber + 1][0] - MountainsCoordinates[MountainsDotNumber]    [0]) /
							  (MountainsCoordinates[MountainsDotNumber + 1][1] - MountainsCoordinates[MountainsDotNumber]    [1]));
	double pi = 3.141592;
	double PeakAngle = pi - LeftAngle - RightAngle;

	double SnowVertexCoordinates[8][2];
    SnowVertexCoordinates[0][1] = FirstSnowX;
    SnowVertexCoordinates[0][0] = MountainsCoordinates[MountainsDotNumber - 1][0] -
                    (FirstSnowX - MountainsCoordinates[MountainsDotNumber - 1][1]) * tan (LeftAngle);

    double SnowLineLength = sqrt (pow(SnowVertexCoordinates[0][1] - MountainsCoordinates[MountainsDotNumber][1], 2) +
                                  pow(SnowVertexCoordinates[0][0] - MountainsCoordinates[MountainsDotNumber][0], 2));

	int SnowVertexes = 7;
	double AngleRatio[6] = {0.19, 0.14, 0.16, 0.15, 0.16, 0.2};
    for (int i = 1; i < SnowVertexes; ++i)
    {
        LeftAngle += PeakAngle * AngleRatio[i - 1];

        SnowVertexCoordinates[i][1] = MountainsCoordinates[MountainsDotNumber][1] - SnowLineLength * cos (LeftAngle);
        SnowVertexCoordinates[i][0] = MountainsCoordinates[MountainsDotNumber][0] + SnowLineLength * sin (LeftAngle);
    }

	int SnowVertexesAndPeak = SnowVertexes + 1;
    POINT snow[SnowVertexesAndPeak];
    for (int i = 0; i <= SnowVertexesAndPeak - 2; ++i)
        {
        snow[i] = {SnowVertexCoordinates[i][1], SnowVertexCoordinates[i][0]};
        }

    snow[SnowVertexesAndPeak - 1] = {MountainsCoordinates[MountainsDotNumber][1], MountainsCoordinates[MountainsDotNumber][0]};

    txPolygon (snow, 8);
    }

void DrawHouse (double x, double y, double scale, double RoofAngle,
    COLORREF house, COLORREF door, COLORREF window, COLORREF cross)
    {
    DrawBase (x, y, scale, RoofAngle, house, door);

    DrawDoor (x, y, scale, door);

    DrawWindow (x, y, scale, window, cross, door);
    }

void DrawBase (double x, double y, double scale, double RoofAngle, COLORREF house, COLORREF door)
{
    txSetColor (door);
    txSetFillColor (house);

	double width = 250 * scale;
	double high = 220 * scale;
    txRectangle (x, y, x + width, y + high);

    double pi = 3.141592;
    RoofAngle = RoofAngle / 2;
    POINT attic[3] = {{x, y}, {x + width / 2, y - width / 2 / tan (RoofAngle)}, {x + width, y}};
    txPolygon (attic, 3);
}

void DrawDoor (double x, double y, double scale, COLORREF door)
{
    txSetColor (door);
    txSetFillColor (door);

	double DoorPlaceX = x + 110 * scale;
	double DoorPlaceY = y + 80 * scale;

	double width = 70 * scale;
	double high = 130 * scale;
    txRectangle (DoorPlaceX, 		 DoorPlaceY,
				 DoorPlaceX + width, DoorPlaceY + high);
}

void DrawWindow (double x, double y, double scale,
	COLORREF window, COLORREF cross, COLORREF door)
{
    txSetFillColor (window);
    txSetColor (door);
	double WindowPlaceX = x + 20 * scale;
	double WindowPlaceY = y + 70 * scale;
	double width = 70 * scale;
	double high = 110 * scale;
    txRectangle (WindowPlaceX, 		   WindowPlaceY,
				 WindowPlaceX + width, WindowPlaceY + high);

    txSetColor (cross);
    txLine (WindowPlaceX + width / 2, WindowPlaceY,
            WindowPlaceX + width / 2, WindowPlaceY + high);
    txLine (WindowPlaceX,        WindowPlaceY + high / 2,
            WindowPlaceX + width, WindowPlaceY + high / 2);
}

void DrawSmokeTree (double x, double y, double rad, int density, double scale, COLORREF trunk, COLORREF crown)
{
    txSetColor     (trunk);
    txSetFillColor (trunk);

    POINT TreeLeftSide[7] = {{x, y},
							 {x + 45 * scale, y - 5 * scale},  {x + 50 * scale, y - 7 * scale},
							 {x + 55 * scale, y - 10 * scale}, {x + 60 * scale, y - 20 * scale},
							 {x + 65 * scale, y - 35 * scale}, {x + 65 * scale, y}};
    txPolygon (TreeLeftSide, 7);

    POINT TreeRightSide[7] = {{x + 185 * scale, y},             {x + 140 * scale, y - 5 * scale},
							  {x + 135 * scale, y - 7 * scale}, {x + 130 * scale, y - 10 * scale},
							  {x + 125 * scale, y - 20 * scale},{x + 120 * scale, y - 35 * scale},
							  {x + 120 * scale, y}};
    txPolygon (TreeRightSide, 7);

    txRectangle (x + 65 * scale, y,
				 x + 120 * scale, y - 325 * scale);

    txSetColor (crown);
    txSetFillColor (crown);

    txCircle (x + 92.5 * scale, y - 385 * scale, rad);

    double ang = 2 * 3.131592 / density, crown_x, crown_y;
    x += 92.5 * scale;
    y -= 385 * scale;

    for (int i = 0; i < density; ++i)
    {
        crown_x = x + rad * cos (ang * i);
        crown_y = y - rad * sin (ang * i);

        txCircle (crown_x, crown_y, rad * 0.75);
    }
}

void DrawMan ()
{
    txSetColor (TX_BLACK, 3);
    txSetFillColor (TX_WHITE);

    txLine (420, 390, 420, 480);

    txLine (460, 520, 420, 480);
    txLine (380, 520, 420, 480);

    txLine (420, 390, 380, 430);
    txLine (420, 390, 460, 430);

    txCircle (420, 370, 20);
}

void DrawRobot (double x, double y, double scale, double AngLA, double AngRA, double AngLL, double AngRL,
    COLORREF robot, COLORREF eyes, COLORREF smile)
{
    DrawLL (x, y, scale, AngLL, robot);

    DrawRL (x, y, scale, AngRL, robot);

    txRectangle (x + 20 * scale, y + 100 * scale, x + 80  * scale, y); //

    DrawLA (x, y, scale, AngLA, robot);

    DrawRA (x, y, scale, AngRA, robot);

    txRectangle (x + 30 * scale, y, x + 70 * scale, y - 40 * scale); //

    DrawEyes (x, y, scale, eyes);

    DrawSmile (x, y, scale, smile);
}

void DrawLA (double x, double y, double scale, double AngLA, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double l = 87.5 * scale;
    txRectangle (x, y, x + 20 * scale, y +  5 * scale);

    POINT LA[4] = {{x,              y +  2.5 * scale},
                   {x + 10 * scale, y +  2.5 * scale},
                   {x + 10 * scale + l * cos (AngLA), y + 2.5 * scale - l * sin (AngLA)},
                   {x +              l * cos (AngLA), y + 2.5 * scale - l * sin (AngLA)}};
    txPolygon (LA, 4);
}

void DrawRA (double x, double y, double scale, double AngRA, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double l = 87.5 * scale;
    txRectangle (x + 80 * scale, y, x + 100 * scale, y + 5 * scale);

    POINT RA[4] = {{x +  90 * scale, y + 2.5 * scale},
                   {x + 100 * scale, y + 2.5 * scale},
                   {x + 100 * scale + l * cos (AngRA), y + 2.5 * scale - l * sin (AngRA)},
                   {x +  90 * scale + l * cos (AngRA), y + 2.5 * scale - l * sin (AngRA)}};
    txPolygon (RA, 4);
}

void DrawLL (double x, double y, double scale, double AngLL, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double l = 55 * scale;
    txRectangle (x + 40 * scale + l * cos (AngLL), y + 100 * scale - l * sin (AngLL),
                 x + 10 * scale + l * cos (AngLL), y + 105 * scale - l * sin (AngLL));

    POINT LL[4] = {{x + 40 * scale,                   y + 100 * scale},
                   {x + 40 * scale + l * cos (AngLL), y + 100 * scale - l * sin (AngLL)},
                   {x + 30 * scale + l * cos (AngLL), y + 100 * scale - l * sin (AngLL)},
                   {x + 30 * scale,                   y + 100 * scale}};
    txPolygon (LL, 4);
}

void DrawRL (double x, double y, double scale, double AngRL, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double l = 55 * scale;
    txRectangle (x + 90 * scale + l * cos (AngRL), y + 100 * scale - l * sin (AngRL),
                 x + 60 * scale + l * cos (AngRL), y + 105 * scale - l * sin (AngRL)); //

    POINT RL[4] = {{x + 70 * scale,                   y + 100 * scale},
                   {x + 70 * scale + l * cos (AngRL), y + 100 * scale - l * sin (AngRL)},
                   {x + 60 * scale + l * cos (AngRL), y + 100 * scale - l * sin (AngRL)},
                   {x + 60 * scale,                   y + 100 * scale}};
    txPolygon (RL, 4);
}

void DrawEyes (double x, double y, double scale, COLORREF eyes)
{
    txSetColor     (eyes);
    txSetFillColor (eyes);

    txRectangle (x + 40 * scale, y - 30 * scale, x + 45 * scale, y - 25 * scale);
    txRectangle (x + 60 * scale, y - 30 * scale, x + 55 * scale, y - 25 * scale);
}

void DrawSmile (double x, double y, double scale, COLORREF smile)
{
    txSetColor     (smile);
    txSetFillColor (smile);

    txLine (x + 45 * scale, y - 14 * scale, x + 45 * scale, y - 10 * scale);
    txLine (x + 45 * scale, y - 10 * scale, x + 55 * scale, y - 10 * scale);
    txLine (x + 55 * scale, y - 10 * scale, x + 55 * scale, y - 15 * scale);
}

void DrawCigarette()
{
    txSetColor (RGB (222, 114, 5));
    txSetFillColor (RGB (222, 114, 5));

    txPie (380, 510, 460, 530, 180, 180);
    txRectangle (380, 520, 460, 470);

    txSetColor (RGB (243, 247, 250));
    txSetFillColor (RGB (243, 247, 250));

    txRectangle (380, 480, 460, 330);
    txEllipse (380, 470, 460, 490);
    txEllipse (380, 320, 460, 340);

    txSetColor (RGB (219, 176, 134));
    txSetFillColor (RGB (219, 176, 134));

    txEllipse (385, 325, 455, 335);

    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txRectangle (395, 370, 405, 375);
    txRectangle (445, 370, 435, 375);

    txLine (410, 390, 420, 400);
    txLine (420, 400, 431, 389);
}




