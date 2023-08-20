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

void DrawLeftArm (double x, double y, double scale, double AngLA, COLORREF robot);

void DrawRightArm (double ShoulderLeftPointX, double ShoulderLeftPointY, double BodyWidth, double scale, double angle, COLORREF robot);

void DrawLeftLeg (double FootLeftPointX, double FootTopPointY, double scale, double angle, COLORREF robot);

void DrawRightLeg (double x, double y, double scale, double AngRL, COLORREF robot);

void DrawEyes (double HeadCentreX, double EyeLevelY, double HeadWidth, double scale, COLORREF eyes);

void DrawSmile (double HeadCentreX, double LipsLevelY, double HeadWidth, double scale, COLORREF smile);

void DrawMan ();

void DrawCigarette();

int main()
    {
    txCreateWindow (800, 600);

    txSunset (400, 180, 30, 250, 240, 180);

    DrawGround ();

    DrawMountains (10, 205, 423, 745, RGB (255, 255, 255), TX_GRAY);

    double pi = 2 * asin (1);

    DrawHouse (540, 320, 1, 120 * pi / 180,
        RGB (185, 122, 87), RGB (103, 65, 44), TX_GRAY, TX_BLACK);

    DrawSmokeTree (0, 525, 60, 12, 1, RGB (185, 122, 87), TX_GREEN);

    DrawRobot (250, 370, 1,
        pi * 1.5, pi * 0.3,
        pi * 1.5, pi * 1.5,
        RGB (200, 191, 223), TX_BLACK, TX_BLACK);
    cout << cos (pi * 1.25);
    //DrawCigarette();

    return 0;
    }

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
    txRectangle (x,         y,
                 x + width, y + high);

    double pi = 3.141592;
    RoofAngle = RoofAngle / 2;
    POINT attic[3] = {{x,             y},
                      {x + width / 2, y - width / 2 / tan (RoofAngle)},
                      {x + width,     y}};
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
    txLine (WindowPlaceX,         WindowPlaceY + high / 2,
            WindowPlaceX + width, WindowPlaceY + high / 2);
}

void DrawSmokeTree (double RootLeftPointX, double RootLeftPointY, double rad, int density, double scale, COLORREF trunk, COLORREF crown)
{
    txSetColor     (trunk);
    txSetFillColor (trunk);

    double RootWidth = 180 * scale;
    double RootHigh = 20 * scale;

    POINT Root[3] = {{RootLeftPointX,                 RootLeftPointY},
                     {RootLeftPointX + RootWidth / 2, RootLeftPointY - RootHigh},
                     {RootLeftPointX + RootWidth,     RootLeftPointY}};
    txPolygon (Root, 3);


    double TrunkWidth = 60 * scale;
    double TrunkHigh = 325 * scale;

    double TrunkCentreX = RootLeftPointX + RootWidth / 2;

    double TrunkBottom = RootLeftPointY;
    double TrunkTop = TrunkBottom - TrunkHigh * scale;

    txRectangle (TrunkCentreX - TrunkWidth / 2, TrunkBottom,
				 TrunkCentreX + TrunkWidth / 2, TrunkTop);

    txSetColor (crown);
    txSetFillColor (crown);

    double pi = 2 * asin (1);
    double CrownAngle = 2 * pi / density;

    txCircle (TrunkCentreX, TrunkTop, rad);

    for (int i = 0; i < density; ++i)
    {
        double CrownX = TrunkCentreX + rad * cos (CrownAngle * i);
        double CrownY = TrunkTop - rad * sin (CrownAngle * i);

        txCircle (CrownX, CrownY, rad * 0.75);
    }
}

void DrawRobot (double LeftShoulderTopLeftX, double LeftShoulderTopLeftY, double scale,
    double AngleLeftArm, double AngleRightArm, double AngleLeftLeg, double AngleRightLeg,
    COLORREF robot, COLORREF eyes, COLORREF smile)
{
    double ShoulderWidth = 20 * scale;
    double LegHigh = 90 * scale;
    double BodyHigh = 100 * scale;
    double LegWidth = 10 * scale;
    double FootWidth = 20 * scale;

    DrawLeftLeg (LeftShoulderTopLeftX + ShoulderWidth + FootWidth - LegWidth,
                 LeftShoulderTopLeftY + BodyHigh,
                 scale, AngleLeftLeg, robot);

    double BodyWidth = 60 * scale;

    DrawRightLeg (LeftShoulderTopLeftX + ShoulderWidth + BodyWidth - FootWidth,
                  LeftShoulderTopLeftY + BodyHigh,
                  scale, AngleRightLeg, robot);

    txRectangle (LeftShoulderTopLeftX + ShoulderWidth,             LeftShoulderTopLeftY,
                 LeftShoulderTopLeftX + ShoulderWidth + BodyWidth, LeftShoulderTopLeftY + BodyHigh); //

    DrawLeftArm (LeftShoulderTopLeftX, LeftShoulderTopLeftY, scale, AngleLeftArm, robot);

    DrawRightArm (LeftShoulderTopLeftX + ShoulderWidth + BodyWidth,
                  LeftShoulderTopLeftY,
                  BodyWidth, scale, AngleRightArm, robot);

    double HeadWidth = 40 * scale;
    double HeadHigh = 40 * scale;

    txRectangle (LeftShoulderTopLeftX + ShoulderWidth + BodyWidth / 2 - HeadWidth / 2, LeftShoulderTopLeftY,
                 LeftShoulderTopLeftX + ShoulderWidth + BodyWidth / 2 + HeadWidth / 2, LeftShoulderTopLeftY - HeadHigh); //

    DrawEyes (LeftShoulderTopLeftX + ShoulderWidth + BodyWidth / 2,
              LeftShoulderTopLeftY - HeadHigh * 0.75,
              HeadWidth, scale, eyes);

    DrawSmile (LeftShoulderTopLeftX + ShoulderWidth + BodyWidth / 2,
               LeftShoulderTopLeftY - HeadHigh * 0.35,
               HeadWidth, scale, smile);
}

void DrawLeftArm (double ShoulderLeftPointX, double ShoulderLeftPointY, double scale, double angle, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double ShoulderWidth = 20 * scale;
    double ShoulderHigh = 5 * scale;
    double ArmWidth = 10 * scale;
    double ArmHigh = 90 * scale;

    double pi = 2 * asin (1);

    double ShoulderCentreX = ShoulderLeftPointX + ShoulderWidth / 2;
    double ShoulderCentreY = ShoulderLeftPointY + ShoulderHigh / 2;

    txRectangle (ShoulderCentreX,                     ShoulderLeftPointY,
                 ShoulderCentreX + ShoulderWidth / 2, ShoulderLeftPointY +  ShoulderWidth);

    txCircle (ShoulderCentreX,
              ShoulderLeftPointY + ShoulderWidth / 2,
              ShoulderWidth / 2);

    double ShoulderAngle = angle;

    ShoulderCentreY = ShoulderLeftPointY + ShoulderWidth / 2;

    double TopLeftX = ShoulderCentreX - ArmWidth / 2 * cos (ShoulderAngle + 0.5 * pi);
    double TopLeftY = ShoulderCentreY + ArmWidth / 2 * sin (ShoulderAngle + 0.5 * pi);
    double TopRightX = ShoulderCentreX - ArmWidth / 2 * cos (ShoulderAngle - 0.5 * pi);
    double TopRightY = ShoulderCentreY + ArmWidth / 2 * sin (ShoulderAngle - 0.5 * pi);

    POINT arm[4] = {{TopLeftX,  TopLeftY},
                        {TopRightX, TopRightY},
                        {TopRightX + ArmHigh * cos (angle), TopRightY - ArmHigh * sin (angle)},
                        {TopLeftX  + ArmHigh * cos (angle), TopLeftY  - ArmHigh * sin (angle)}};
    txPolygon (arm, 4);
}

void DrawRightArm (double ShoulderLeftPointX, double ShoulderLeftPointY, double BodyWidth, double scale, double angle, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double ShoulderWidth = 20 * scale;
    double ShoulderHigh = 5 * scale;
    double ArmWidth = 10 * scale;
    double ArmHigh = 90 * scale;

    double pi = 2 * asin (1);

    double ShoulderCentreX = ShoulderLeftPointX + ShoulderWidth / 2;
    double ShoulderCentreY = ShoulderLeftPointY + ShoulderHigh / 2;

    txRectangle (ShoulderCentreX,                     ShoulderLeftPointY,
                 ShoulderCentreX - ShoulderWidth / 2, ShoulderLeftPointY +  ShoulderWidth);

    txCircle (ShoulderCentreX,
              ShoulderLeftPointY + ShoulderWidth / 2,
              ShoulderWidth / 2);

    double ShoulderAngle = angle;

    ShoulderCentreY = ShoulderLeftPointY + ShoulderWidth / 2;

    double TopLeftX = ShoulderCentreX - ArmWidth / 2 * cos (ShoulderAngle + 0.5 * pi);
    double TopLeftY = ShoulderCentreY + ArmWidth / 2 * sin (ShoulderAngle + 0.5 * pi);
    double TopRightX = ShoulderCentreX - ArmWidth / 2 * cos (ShoulderAngle - 0.5 * pi);
    double TopRightY = ShoulderCentreY + ArmWidth / 2 * sin (ShoulderAngle - 0.5 * pi);

    POINT arm[4] = {{TopLeftX,  TopLeftY},
                    {TopRightX, TopRightY},
                    {TopRightX + ArmHigh * cos (angle), TopRightY - ArmHigh * sin (angle)},
                    {TopLeftX  + ArmHigh * cos (angle), TopLeftY  - ArmHigh * sin (angle)}};
    txPolygon (arm, 4);
}

void DrawLeftLeg (double LegLeftPointX, double LegTopPointY, double scale, double angle, COLORREF robot)
{
    txSetColor     (robot);
    txSetFillColor (robot);

    double LegWidth = 10 * scale;
    double LegHigh = 60 * scale;

    double pi = 2 * asin (1);

    double LegCentreX = LegLeftPointX + LegWidth / 2;
    double LegCentreY = LegTopPointY + LegWidth / 2;


    txCircle (LegCentreX,
              LegTopPointY,
              LegWidth);

    double TopLeftX = LegCentreX - LegWidth / 2 * cos (angle + 0.5 * pi);
    double TopLeftY = LegCentreY + LegWidth / 2 * sin (angle + 0.5 * pi);
    double TopRightX = LegCentreX - LegWidth / 2 * cos (angle - 0.5 * pi);
    double TopRightY = LegCentreY + LegWidth / 2 * sin (angle - 0.5 * pi);

    POINT Leg[4] = {{TopLeftX,  TopLeftY},
                    {TopRightX, TopRightY},
                    {TopRightX + LegHigh * cos (angle), TopRightY - LegHigh * sin (angle)},
                    {TopLeftX  + LegHigh * cos (angle), TopLeftY  - LegHigh * sin (angle)}};
    txPolygon (Leg, 4);
}

void DrawRightLeg (double LegLeftPointX, double LegTopPointY, double scale, double angle, COLORREF robot)
{
   txSetColor     (robot);
    txSetFillColor (robot);

    double LegWidth = 10 * scale;
    double LegHigh = 60 * scale;

    double pi = 2 * asin (1);

    double LegCentreX = LegLeftPointX + LegWidth / 2;
    double LegCentreY = LegTopPointY + LegWidth / 2;


    txCircle (LegCentreX,
              LegTopPointY,
              LegWidth);

    double TopLeftX = LegCentreX - LegWidth / 2 * cos (angle + 0.5 * pi);
    double TopLeftY = LegCentreY + LegWidth / 2 * sin (angle + 0.5 * pi);
    double TopRightX = LegCentreX - LegWidth / 2 * cos (angle - 0.5 * pi);
    double TopRightY = LegCentreY + LegWidth / 2 * sin (angle - 0.5 * pi);

    POINT Leg[4] = {{TopLeftX,  TopLeftY},
                    {TopRightX, TopRightY},
                    {TopRightX + LegHigh * cos (angle), TopRightY - LegHigh * sin (angle)},
                    {TopLeftX  + LegHigh * cos (angle), TopLeftY  - LegHigh * sin (angle)}};
    txPolygon (Leg, 4);
}

void DrawEyes (double HeadCentreX, double EyeLevelY, double HeadWidth, double scale, COLORREF eyes)
{
    txSetColor     (eyes);
    txSetFillColor (eyes);

    double EyeSize = 5 * scale;

    txRectangle (HeadCentreX - HeadWidth * 0.33,           EyeLevelY,
                 HeadCentreX - HeadWidth * 0.33 + EyeSize, EyeLevelY + EyeSize);

    txRectangle (HeadCentreX + HeadWidth * 0.33,           EyeLevelY,
                 HeadCentreX + HeadWidth * 0.33 - EyeSize, EyeLevelY + EyeSize);
}

void DrawSmile (double HeadCentreX, double LipsLevelY, double HeadWidth, double scale, COLORREF smile)
{
    txSetColor     (smile);
    txSetFillColor (smile);

    double SmileHigh = 5 * scale;

    txLine (HeadCentreX - HeadWidth * 0.25, LipsLevelY,
            HeadCentreX + HeadWidth * 0.25, LipsLevelY);

    txLine (HeadCentreX - HeadWidth * 0.25, LipsLevelY,
            HeadCentreX - HeadWidth * 0.25, LipsLevelY - SmileHigh);

    txLine (HeadCentreX + HeadWidth * 0.25, LipsLevelY,
            HeadCentreX + HeadWidth * 0.25, LipsLevelY - SmileHigh);
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





