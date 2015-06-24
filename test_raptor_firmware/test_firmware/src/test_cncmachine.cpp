/////////////////////////////////////////////////////////////////////////////
/// @file   test_cncmachine.cpp
///
/// @date	26 avr. 2015 20:23:58
///
/// @author	Michael House
///
/// @brief	[see corresponding .hpp file]
///
/// @par Copyright (c) 2014 All rights reserved.
/////////////////////////////////////////////////////////////////////////////
#include "cute.h"
#include "test_cncmachine.h"

#include <list>
#include "types.hpp"
#include "cncmachine.hpp"

using namespace std;

extern "C"
{
#include "stdio.h"
}
typedef struct
{
	alt_u32 x;
	alt_u32 y;
} COORDINATE;


COORDINATE xy(alt_u32 x, alt_u32 y)
{
	COORDINATE pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

void DisplayStepCoordinate(list<CncMachine::TRAVERSALXY> route_data)
{
    printf("started routing\n");
    //DisplayRoutes(route_data);
    CncMachine::TRAVERSALXY movement;
    list<CncMachine::TRAVERSALXY>::iterator it;

   alt_32 xpos = 0;
   alt_32 ypos= 0;
   for(it = route_data.begin(); it != route_data.end(); it++)
   {
       movement = *it;
       if (movement.X.StepDir)
       {
    	   xpos = xpos + movement.X.StepNum;
       }
       else
       {
    	   xpos = xpos - movement.X.StepNum;
       }
       if (movement.Y.StepDir)
       {
    	   ypos = ypos + movement.Y.StepNum;
       }
       else
       {
    	   ypos = ypos - movement.Y.StepNum;
       }
       printf("G3 X%ld Y%ld\n",xpos, ypos);

   }

    printf("completed routing\n");
}

/////////////////////////////////////////////////////////////////////////////
///@brief verify cncmachine sets the correct direction
///@details creates a list of coordinates then send it into cncmachine object
///			compare old coordinate with new coordinate to verify direction
/////////////////////////////////////////////////////////////////////////////
void InputCoordinateTest() {
	list<COORDINATE> triangle;
	triangle.push_back(xy(294366,84801));
	triangle.push_back(xy(175520,307195));
	triangle.push_back(xy(64840,380000));
	triangle.push_back(xy(0,0));

	list<COORDINATE>::iterator it;
	CncMachine raptor;
	COORDINATE pos;
	//COORDINATE old;
	CncMachine::TRAVERSALXY data;
	//CncMachine::Direction dir;
//	alt_32 val;
	//old.x = 0;
	//old.y = 0;
	for(it = triangle.begin(); it != triangle.end(); it++)
	{
		pos = *it;
		raptor.SetNextPosition(pos.x,pos.y);
		data = raptor.GetXYMovement();
		//compare with previous position to new direction is
		//set correctly with respect to old position
		//verify X direction
//		val = (alt_32)data.X.Position - (alt_32)old.x;
//		cout << "value position change = "<<val<<endl;
		//dir = ((alt_32)data.X.Position - (alt_32)old.x)>0?
		//		CncMachine::up: CncMachine::down;
		//ASSERT_EQUAL(dir,data.X.StepDir);
		//verify Y direction
		//dir = ((alt_32)data.Y.Position - (alt_32)old.y)>0?
		//		CncMachine::up: CncMachine::down;
		//ASSERT_EQUAL(dir,data.Y.StepDir);

		//old.x = data.X.Position;
		//old.y = data.Y.Position;

	}
}

void outOfRangeTest()
{
	//ASSERTM("start writing tests", false);
	CncMachine machine;
	//send triangle coordinates , triangle.nc
	machine.SetNextPosition(380001,84801);
	ASSERT_EQUAL(1,(int)machine.SetNextPosition(380001,84801));


}



void routeTest()
{
	CncMachine machine;
	//send triangle coordinates , triangle.nc
	machine.SetNextPosition(294366,84801);
	machine.SetNextPosition(175520,307195);
	machine.SetNextPosition(64840,84800);

	machine.StartRouting();
}

void routeTestSmallNumbers()
{
	CncMachine machine;
	//send coordinates from rd_bm1.nc
	machine.SetNextPosition(28773, 5806);
	machine.SetNextPosition(28828, 4828);
	machine.SetNextPosition(28974, 4049);
	machine.SetNextPosition(29236, 3307);
	machine.SetNextPosition(29573, 2720);
	machine.SetNextPosition(30027, 2228);
	machine.SetNextPosition(30527, 1893);
	machine.SetNextPosition(31095, 1692);
	machine.SetNextPosition(31780, 1618);
	machine.SetNextPosition(32464, 1692);
	machine.SetNextPosition(33032, 1893);
	machine.SetNextPosition(33532, 2228);
	machine.SetNextPosition(33985, 2720);
	machine.SetNextPosition(34328, 3308);
	machine.SetNextPosition(34592, 4049);
	machine.SetNextPosition(34739, 4828);
	machine.SetNextPosition(34796, 5806);
	machine.SetNextPosition(34739, 6784);
	machine.SetNextPosition(34592, 7561);
	machine.SetNextPosition(34327, 8299);
	machine.SetNextPosition(33985, 8882);
	machine.SetNextPosition(33531, 9380);
	machine.SetNextPosition(33031, 9717);
	machine.SetNextPosition(32463, 9919);
	machine.SetNextPosition(31780, 9994);
	machine.SetNextPosition(31096, 9919);
	machine.SetNextPosition(30528, 9717);
	machine.SetNextPosition(30028, 9380);
	machine.SetNextPosition(29573, 8882);
	machine.SetNextPosition(29236, 8300);
	machine.SetNextPosition(28974, 7561);
	machine.SetNextPosition(28828, 6785);
	machine.SetNextPosition(28773, 5806);
	machine.SetNextPosition(28773, 5806);
	machine.SetNextPosition(28773, 5806);
	machine.StartRouting();

}

void routeTestReturnStepCoordinates()
{
	CncMachine machine;
	list<CncMachine::TRAVERSALXY> route_data;
	//send coordinates from rd_bm1.nc
	//note: these coordinates are generated from running parse_gcode.py
	machine.SetNextPosition( 0 , 0 );
	machine.SetNextPosition( 28773 , 5806 );
	machine.SetNextPosition( 28828 , 4828 );
	machine.SetNextPosition( 28974 , 4049 );
	machine.SetNextPosition( 29236 , 3307 );
	machine.SetNextPosition( 29573 , 2720 );
	machine.SetNextPosition( 30027 , 2228 );
	machine.SetNextPosition( 30527 , 1893 );
	machine.SetNextPosition( 31095 , 1692 );
	machine.SetNextPosition( 31780 , 1618 );
	machine.SetNextPosition( 32464 , 1692 );
	machine.SetNextPosition( 33032 , 1893 );
	machine.SetNextPosition( 33532 , 2228 );
	machine.SetNextPosition( 33985 , 2720 );
	machine.SetNextPosition( 34328 , 3308 );
	machine.SetNextPosition( 34592 , 4049 );
	machine.SetNextPosition( 34739 , 4828 );
	machine.SetNextPosition( 34796 , 5806 );
	machine.SetNextPosition( 34739 , 6784 );
	machine.SetNextPosition( 34592 , 7561 );
	machine.SetNextPosition( 34327 , 8299 );
	machine.SetNextPosition( 33985 , 8882 );
	machine.SetNextPosition( 33531 , 9380 );
	machine.SetNextPosition( 33031 , 9717 );
	machine.SetNextPosition( 32463 , 9919 );
	machine.SetNextPosition( 31780 , 9994 );
	machine.SetNextPosition( 31096 , 9919 );
	machine.SetNextPosition( 30528 , 9717 );
	machine.SetNextPosition( 30028 , 9380 );
	machine.SetNextPosition( 29573 , 8882 );
	machine.SetNextPosition( 29236 , 8300 );
	machine.SetNextPosition( 28974 , 7561 );
	machine.SetNextPosition( 28828 , 6785 );
	machine.SetNextPosition( 28773 , 5806 );
	machine.SetNextPosition( 28773 , 5806 );
	machine.SetNextPosition( 28773 , 5806 );
	machine.SetNextPosition( 36593 , 397 );
	machine.SetNextPosition( 36593 , 15492 );
	machine.SetNextPosition( 34896 , 15492 );
	machine.SetNextPosition( 34896 , 9625 );
	machine.SetNextPosition( 34803 , 9599 );
	machine.SetNextPosition( 34496 , 10062 );
	machine.SetNextPosition( 34168 , 10439 );
	machine.SetNextPosition( 33793 , 10766 );
	machine.SetNextPosition( 33386 , 11026 );
	machine.SetNextPosition( 32950 , 11229 );
	machine.SetNextPosition( 32452 , 11379 );
	machine.SetNextPosition( 31937 , 11467 );
	machine.SetNextPosition( 31340 , 11498 );
	machine.SetNextPosition( 30384 , 11395 );
	machine.SetNextPosition( 29563 , 11108 );
	machine.SetNextPosition( 28831 , 10636 );
	machine.SetNextPosition( 28147 , 9936 );
	machine.SetNextPosition( 27618 , 9108 );
	machine.SetNextPosition( 27225 , 8121 );
	machine.SetNextPosition( 27002 , 7076 );
	machine.SetNextPosition( 26917 , 5806 );
	machine.SetNextPosition( 27002 , 4536 );
	machine.SetNextPosition( 27225 , 3491 );
	machine.SetNextPosition( 27618 , 2505 );
	machine.SetNextPosition( 28147 , 1676 );
	machine.SetNextPosition( 28831 , 977 );
	machine.SetNextPosition( 29563 , 504 );
	machine.SetNextPosition( 30384 , 218 );
	machine.SetNextPosition( 31340 , 114 );
	machine.SetNextPosition( 31937 , 145 );
	machine.SetNextPosition( 32452 , 230 );
	machine.SetNextPosition( 32951 , 378 );
	machine.SetNextPosition( 33386 , 577 );
	machine.SetNextPosition( 33793 , 840 );
	machine.SetNextPosition( 34168 , 1171 );
	machine.SetNextPosition( 34496 , 1550 );
	machine.SetNextPosition( 34803 , 2013 );
	machine.SetNextPosition( 34896 , 1988 );
	machine.SetNextPosition( 34896 , 397 );
	machine.SetNextPosition( 36593 , 397 );
	machine.SetNextPosition( 101507 , 5806 );
	machine.SetNextPosition( 101563 , 4828 );
	machine.SetNextPosition( 101708 , 4049 );
	machine.SetNextPosition( 101969 , 3307 );
	machine.SetNextPosition( 102308 , 2720 );
	machine.SetNextPosition( 102762 , 2228 );
	machine.SetNextPosition( 103262 , 1893 );
	machine.SetNextPosition( 103829 , 1692 );
	machine.SetNextPosition( 104514 , 1618 );
	machine.SetNextPosition( 105198 , 1692 );
	machine.SetNextPosition( 105765 , 1893 );
	machine.SetNextPosition( 106266 , 2228 );
	machine.SetNextPosition( 106719 , 2720 );
	machine.SetNextPosition( 107062 , 3308 );
	machine.SetNextPosition( 107327 , 4049 );
	machine.SetNextPosition( 107474 , 4828 );
	machine.SetNextPosition( 107530 , 5806 );
	machine.SetNextPosition( 107474 , 6784 );
	machine.SetNextPosition( 107327 , 7561 );
	machine.SetNextPosition( 107062 , 8299 );
	machine.SetNextPosition( 106719 , 8882 );
	machine.SetNextPosition( 106265 , 9380 );
	machine.SetNextPosition( 105765 , 9717 );
	machine.SetNextPosition( 105198 , 9919 );
	machine.SetNextPosition( 104514 , 9994 );
	machine.SetNextPosition( 103829 , 9919 );
	machine.SetNextPosition( 103262 , 9717 );
	machine.SetNextPosition( 102762 , 9380 );
	machine.SetNextPosition( 102308 , 8882 );
	machine.SetNextPosition( 101969 , 8300 );
	machine.SetNextPosition( 101708 , 7561 );
	machine.SetNextPosition( 101563 , 6785 );
	machine.SetNextPosition( 101507 , 5806 );
	machine.SetNextPosition( 101507 , 5806 );
	machine.SetNextPosition( 101507 , 5806 );
	machine.SetNextPosition( 109327 , 397 );
	machine.SetNextPosition( 109327 , 15492 );
	machine.SetNextPosition( 107630 , 15492 );
	machine.SetNextPosition( 107630 , 9625 );
	machine.SetNextPosition( 107537 , 9599 );
	machine.SetNextPosition( 107230 , 10062 );
	machine.SetNextPosition( 106903 , 10439 );
	machine.SetNextPosition( 106527 , 10766 );
	machine.SetNextPosition( 106120 , 11026 );
	machine.SetNextPosition( 105684 , 11229 );
	machine.SetNextPosition( 105186 , 11379 );
	machine.SetNextPosition( 104671 , 11467 );
	machine.SetNextPosition( 104074 , 11498 );
	machine.SetNextPosition( 103118 , 11395 );
	machine.SetNextPosition( 102297 , 11108 );
	machine.SetNextPosition( 101565 , 10636 );
	machine.SetNextPosition( 100881 , 9936 );
	machine.SetNextPosition( 100353 , 9108 );
	machine.SetNextPosition( 99960 , 8121 );
	machine.SetNextPosition( 99736 , 7076 );
	machine.SetNextPosition( 99652 , 5806 );
	machine.SetNextPosition( 99736 , 4536 );
	machine.SetNextPosition( 99960 , 3491 );
	machine.SetNextPosition( 100353 , 2505 );
	machine.SetNextPosition( 100881 , 1676 );
	machine.SetNextPosition( 101565 , 977 );
	machine.SetNextPosition( 102297 , 504 );
	machine.SetNextPosition( 103118 , 218 );
	machine.SetNextPosition( 104074 , 114 );
	machine.SetNextPosition( 104671 , 145 );
	machine.SetNextPosition( 105186 , 230 );
	machine.SetNextPosition( 105685 , 378 );
	machine.SetNextPosition( 106121 , 577 );
	machine.SetNextPosition( 106527 , 840 );
	machine.SetNextPosition( 106903 , 1171 );
	machine.SetNextPosition( 107230 , 1550 );
	machine.SetNextPosition( 107537 , 2013 );
	machine.SetNextPosition( 107630 , 1988 );
	machine.SetNextPosition( 107630 , 397 );
	machine.SetNextPosition( 109327 , 397 );
	machine.SetNextPosition( 2149 , 1968 );
	machine.SetNextPosition( 2199 , 1918 );
	machine.SetNextPosition( 5363 , 1918 );
	machine.SetNextPosition( 6159 , 1965 );
	machine.SetNextPosition( 6761 , 2084 );
	machine.SetNextPosition( 7330 , 2304 );
	machine.SetNextPosition( 7750 , 2585 );
	machine.SetNextPosition( 8090 , 2964 );
	machine.SetNextPosition( 8342 , 3442 );
	machine.SetNextPosition( 8484 , 3967 );
	machine.SetNextPosition( 8538 , 4644 );
	machine.SetNextPosition( 8483 , 5326 );
	machine.SetNextPosition( 8342 , 5849 );
	machine.SetNextPosition( 8090 , 6324 );
	machine.SetNextPosition( 7749 , 6694 );
	machine.SetNextPosition( 7330 , 6974 );
	machine.SetNextPosition( 6761 , 7195 );
	machine.SetNextPosition( 6159 , 7312 );
	machine.SetNextPosition( 5363 , 7360 );
	machine.SetNextPosition( 2199 , 7360 );
	machine.SetNextPosition( 2149 , 7310 );
	machine.SetNextPosition( 2149 , 1968 );
	machine.SetNextPosition( 2149 , 8912 );
	machine.SetNextPosition( 2199 , 8862 );
	machine.SetNextPosition( 5119 , 8862 );
	machine.SetNextPosition( 5843 , 8900 );
	machine.SetNextPosition( 6391 , 8997 );
	machine.SetNextPosition( 6915 , 9180 );
	machine.SetNextPosition( 7298 , 9409 );
	machine.SetNextPosition( 7618 , 9727 );
	machine.SetNextPosition( 7848 , 10118 );
	machine.SetNextPosition( 7980 , 10552 );
	machine.SetNextPosition( 8031 , 11109 );
	machine.SetNextPosition( 7980 , 11660 );
	machine.SetNextPosition( 7848 , 12093 );
	machine.SetNextPosition( 7618 , 12481 );
	machine.SetNextPosition( 7298 , 12799 );
	machine.SetNextPosition( 6915 , 13032 );
	machine.SetNextPosition( 6391 , 13218 );
	machine.SetNextPosition( 5843 , 13317 );
	machine.SetNextPosition( 5119 , 13355 );
	machine.SetNextPosition( 2199 , 13355 );
	machine.SetNextPosition( 2149 , 13306 );
	machine.SetNextPosition( 2149 , 8912 );
	machine.SetNextPosition( 277 , 14877 );
	machine.SetNextPosition( 277 , 397 );
	machine.SetNextPosition( 5461 , 397 );
	machine.SetNextPosition( 6670 , 471 );
	machine.SetNextPosition( 7618 , 661 );
	machine.SetNextPosition( 8512 , 1006 );
	machine.SetNextPosition( 9209 , 1451 );
	machine.SetNextPosition( 9785 , 2036 );
	machine.SetNextPosition( 10190 , 2718 );
	machine.SetNextPosition( 10428 , 3481 );
	machine.SetNextPosition( 10519 , 4429 );
	machine.SetNextPosition( 10465 , 5155 );
	machine.SetNextPosition( 10318 , 5774 );
	machine.SetNextPosition( 10067 , 6354 );
	machine.SetNextPosition( 9719 , 6869 );
	machine.SetNextPosition( 9286 , 7315 );
	machine.SetNextPosition( 8769 , 7682 );
	machine.SetNextPosition( 8192 , 7954 );
	machine.SetNextPosition( 7492 , 8159 );
	machine.SetNextPosition( 7452 , 8209 );
	machine.SetNextPosition( 7494 , 8258 );
	machine.SetNextPosition( 8077 , 8398 );
	machine.SetNextPosition( 8543 , 8597 );
	machine.SetNextPosition( 8960 , 8878 );
	machine.SetNextPosition( 9299 , 9226 );
	machine.SetNextPosition( 9561 , 9636 );
	machine.SetNextPosition( 9759 , 10137 );
	machine.SetNextPosition( 9871 , 10667 );
	machine.SetNextPosition( 9913 , 11324 );
	machine.SetNextPosition( 9831 , 12160 );
	machine.SetNextPosition( 9612 , 12834 );
	machine.SetNextPosition( 9242 , 13432 );
	machine.SetNextPosition( 8712 , 13950 );
	machine.SetNextPosition( 8074 , 14340 );
	machine.SetNextPosition( 7250 , 14645 );
	machine.SetNextPosition( 6379 , 14812 );
	machine.SetNextPosition( 5266 , 14877 );
	machine.SetNextPosition( 277 , 14877 );
	machine.SetNextPosition( 96583 , 397 );
	machine.SetNextPosition( 96583 , 11235 );
	machine.SetNextPosition( 94886 , 11235 );
	machine.SetNextPosition( 94886 , 397 );
	machine.SetNextPosition( 96583 , 397 );
	machine.SetNextPosition( 22152 , 11235 );
	machine.SetNextPosition( 22152 , 397 );
	machine.SetNextPosition( 23849 , 397 );
	machine.SetNextPosition( 23849 , 11235 );
	machine.SetNextPosition( 22152 , 11235 );
	machine.SetNextPosition( 13841 , 11235 );
	machine.SetNextPosition( 13841 , 397 );
	machine.SetNextPosition( 15548 , 397 );
	machine.SetNextPosition( 15548 , 6109 );
	machine.SetNextPosition( 15548 , 6109 );
	machine.SetNextPosition( 15605 , 7035 );
	machine.SetNextPosition( 15752 , 7761 );
	machine.SetNextPosition( 16021 , 8447 );
	machine.SetNextPosition( 16370 , 8983 );
	machine.SetNextPosition( 16835 , 9427 );
	machine.SetNextPosition( 17385 , 9744 );
	machine.SetNextPosition( 17995 , 9927 );
	machine.SetNextPosition( 18752 , 9997 );
	machine.SetNextPosition( 18969 , 9991 );
	machine.SetNextPosition( 19168 , 9975 );
	machine.SetNextPosition( 19365 , 9946 );
	machine.SetNextPosition( 19544 , 9908 );
	machine.SetNextPosition( 19726 , 9861 );
	machine.SetNextPosition( 19898 , 9803 );
	machine.SetNextPosition( 20065 , 9732 );
	machine.SetNextPosition( 20147 , 9690 );
	machine.SetNextPosition( 20137 , 11409 );
	machine.SetNextPosition( 20043 , 11424 );
	machine.SetNextPosition( 19920 , 11443 );
	machine.SetNextPosition( 19796 , 11458 );
	machine.SetNextPosition( 19683 , 11470 );
	machine.SetNextPosition( 19572 , 11482 );
	machine.SetNextPosition( 19471 , 11491 );
	machine.SetNextPosition( 19370 , 11497 );
	machine.SetNextPosition( 19280 , 11498 );
	machine.SetNextPosition( 18639 , 11466 );
	machine.SetNextPosition( 18089 , 11377 );
	machine.SetNextPosition( 17557 , 11222 );
	machine.SetNextPosition( 17096 , 11016 );
	machine.SetNextPosition( 16671 , 10749 );
	machine.SetNextPosition( 16285 , 10417 );
	machine.SetNextPosition( 15950 , 10031 );
	machine.SetNextPosition( 15641 , 9561 );
	machine.SetNextPosition( 15548 , 9586 );
	machine.SetNextPosition( 15548 , 11235 );
	machine.SetNextPosition( 13841 , 11235 );
	machine.SetNextPosition( 63060 , 11235 );
	machine.SetNextPosition( 63060 , 397 );
	machine.SetNextPosition( 64767 , 397 );
	machine.SetNextPosition( 64767 , 6529 );
	machine.SetNextPosition( 64767 , 6529 );
	machine.SetNextPosition( 64823 , 7322 );
	machine.SetNextPosition( 64972 , 7970 );
	machine.SetNextPosition( 65235 , 8577 );
	machine.SetNextPosition( 65589 , 9081 );
	machine.SetNextPosition( 66043 , 9502 );
	machine.SetNextPosition( 66560 , 9797 );
	machine.SetNextPosition( 67130 , 9972 );
	machine.SetNextPosition( 67815 , 10036 );
	machine.SetNextPosition( 68394 , 9982 );
	machine.SetNextPosition( 68846 , 9841 );
	machine.SetNextPosition( 69248 , 9596 );
	machine.SetNextPosition( 69574 , 9254 );
	machine.SetNextPosition( 69809 , 8846 );
	machine.SetNextPosition( 70000 , 8276 );
	machine.SetNextPosition( 70100 , 7682 );
	machine.SetNextPosition( 70140 , 6889 );
	machine.SetNextPosition( 70140 , 397 );
	machine.SetNextPosition( 71847 , 397 );
	machine.SetNextPosition( 71847 , 6529 );
	machine.SetNextPosition( 71847 , 6529 );
	machine.SetNextPosition( 71903 , 7328 );
	machine.SetNextPosition( 72052 , 7977 );
	machine.SetNextPosition( 72315 , 8586 );
	machine.SetNextPosition( 72670 , 9091 );
	machine.SetNextPosition( 73124 , 9506 );
	machine.SetNextPosition( 73645 , 9800 );
	machine.SetNextPosition( 74220 , 9972 );
	machine.SetNextPosition( 74914 , 10036 );
	machine.SetNextPosition( 75484 , 9982 );
	machine.SetNextPosition( 75931 , 9841 );
	machine.SetNextPosition( 76328 , 9596 );
	machine.SetNextPosition( 76654 , 9254 );
	machine.SetNextPosition( 76890 , 8841 );
	machine.SetNextPosition( 77080 , 8271 );
	machine.SetNextPosition( 77180 , 7677 );
	machine.SetNextPosition( 77220 , 6889 );
	machine.SetNextPosition( 77220 , 397 );
	machine.SetNextPosition( 78927 , 397 );
	machine.SetNextPosition( 78927 , 6949 );
	machine.SetNextPosition( 78862 , 8038 );
	machine.SetNextPosition( 78697 , 8889 );
	machine.SetNextPosition( 78396 , 9694 );
	machine.SetNextPosition( 78009 , 10317 );
	machine.SetNextPosition( 77498 , 10838 );
	machine.SetNextPosition( 76905 , 11203 );
	machine.SetNextPosition( 76239 , 11417 );
	machine.SetNextPosition( 75412 , 11498 );
	machine.SetNextPosition( 74788 , 11460 );
	machine.SetNextPosition( 74238 , 11356 );
	machine.SetNextPosition( 73710 , 11176 );
	machine.SetNextPosition( 73231 , 10930 );
	machine.SetNextPosition( 72795 , 10613 );
	machine.SetNextPosition( 72371 , 10204 );
	machine.SetNextPosition( 72001 , 9741 );
	machine.SetNextPosition( 71638 , 9161 );
	machine.SetNextPosition( 71547 , 9169 );
	machine.SetNextPosition( 71313 , 9721 );
	machine.SetNextPosition( 71043 , 10172 );
	machine.SetNextPosition( 70707 , 10573 );
	machine.SetNextPosition( 70324 , 10903 );
	machine.SetNextPosition( 69897 , 11161 );
	machine.SetNextPosition( 69419 , 11349 );
	machine.SetNextPosition( 68915 , 11459 );
	machine.SetNextPosition( 68332 , 11498 );
	machine.SetNextPosition( 67751 , 11467 );
	machine.SetNextPosition( 67243 , 11379 );
	machine.SetNextPosition( 66751 , 11230 );
	machine.SetNextPosition( 66316 , 11026 );
	machine.SetNextPosition( 65913 , 10762 );
	machine.SetNextPosition( 65528 , 10424 );
	machine.SetNextPosition( 65189 , 10038 );
	machine.SetNextPosition( 64859 , 9559 );
	machine.SetNextPosition( 64767 , 9586 );
	machine.SetNextPosition( 64767 , 11235 );
	machine.SetNextPosition( 63060 , 11235 );
	machine.SetNextPosition( 47903 , 6742 );
	machine.SetNextPosition( 47953 , 6792 );
	machine.SetNextPosition( 47953 , 6793 );
	machine.SetNextPosition( 47888 , 7528 );
	machine.SetNextPosition( 47732 , 8135 );
	machine.SetNextPosition( 47467 , 8700 );
	machine.SetNextPosition( 47109 , 9180 );
	machine.SetNextPosition( 46664 , 9573 );
	machine.SetNextPosition( 46159 , 9851 );
	machine.SetNextPosition( 45605 , 10015 );
	machine.SetNextPosition( 44944 , 10075 );
	machine.SetNextPosition( 44194 , 10017 );
	machine.SetNextPosition( 43572 , 9860 );
	machine.SetNextPosition( 42994 , 9587 );
	machine.SetNextPosition( 42497 , 9212 );
	machine.SetNextPosition( 42093 , 8742 );
	machine.SetNextPosition( 41778 , 8172 );
	machine.SetNextPosition( 41571 , 7552 );
	machine.SetNextPosition( 41447 , 6787 );
	machine.SetNextPosition( 41445 , 6783 );
	machine.SetNextPosition( 41496 , 6733 );
	machine.SetNextPosition( 47903 , 6742 );
	machine.SetNextPosition( 41438 , 5436 );
	machine.SetNextPosition( 49649 , 5436 );
	machine.SetNextPosition( 49649 , 6264 );
	machine.SetNextPosition( 49561 , 7463 );
	machine.SetNextPosition( 49330 , 8434 );
	machine.SetNextPosition( 48923 , 9337 );
	machine.SetNextPosition( 48373 , 10088 );
	machine.SetNextPosition( 47680 , 10707 );
	machine.SetNextPosition( 46880 , 11146 );
	machine.SetNextPosition( 46000 , 11402 );
	machine.SetNextPosition( 44924 , 11498 );
	machine.SetNextPosition( 43723 , 11392 );
	machine.SetNextPosition( 42733 , 11107 );
	machine.SetNextPosition( 41832 , 10619 );
	machine.SetNextPosition( 41045 , 9933 );
	machine.SetNextPosition( 40427 , 9097 );
	machine.SetNextPosition( 39971 , 8100 );
	machine.SetNextPosition( 39711 , 7028 );
	machine.SetNextPosition( 39613 , 5709 );
	machine.SetNextPosition( 39716 , 4436 );
	machine.SetNextPosition( 39990 , 3397 );
	machine.SetNextPosition( 40466 , 2440 );
	machine.SetNextPosition( 41121 , 1623 );
	machine.SetNextPosition( 41943 , 968 );
	machine.SetNextPosition( 42908 , 492 );
	machine.SetNextPosition( 43954 , 217 );
	machine.SetNextPosition( 45237 , 114 );
	machine.SetNextPosition( 45756 , 127 );
	machine.SetNextPosition( 46269 , 167 );
	machine.SetNextPosition( 46779 , 234 );
	machine.SetNextPosition( 47287 , 328 );
	machine.SetNextPosition( 47789 , 446 );
	machine.SetNextPosition( 48285 , 590 );
	machine.SetNextPosition( 48774 , 757 );
	machine.SetNextPosition( 49230 , 937 );
	machine.SetNextPosition( 49230 , 2520 );
	machine.SetNextPosition( 48816 , 2317 );
	machine.SetNextPosition( 48336 , 2112 );
	machine.SetNextPosition( 47845 , 1936 );
	machine.SetNextPosition( 47359 , 1792 );
	machine.SetNextPosition( 46868 , 1681 );
	machine.SetNextPosition( 46368 , 1601 );
	machine.SetNextPosition( 45864 , 1554 );
	machine.SetNextPosition( 45344 , 1537 );
	machine.SetNextPosition( 44454 , 1605 );
	machine.SetNextPosition( 43736 , 1782 );
	machine.SetNextPosition( 43069 , 2094 );
	machine.SetNextPosition( 42516 , 2519 );
	machine.SetNextPosition( 42074 , 3058 );
	machine.SetNextPosition( 41727 , 3731 );
	machine.SetNextPosition( 41510 , 4463 );
	machine.SetNextPosition( 41388 , 5383 );
	machine.SetNextPosition( 41388 , 5386 );
	machine.SetNextPosition( 41438 , 5436 );
	machine.SetNextPosition( 87541 , 5895 );
	machine.SetNextPosition( 86452 , 5859 );
	machine.SetNextPosition( 85690 , 5770 );
	machine.SetNextPosition( 84947 , 5592 );
	machine.SetNextPosition( 84498 , 5390 );
	machine.SetNextPosition( 84118 , 5084 );
	machine.SetNextPosition( 83849 , 4696 );
	machine.SetNextPosition( 83694 , 4245 );
	machine.SetNextPosition( 83634 , 3648 );
	machine.SetNextPosition( 83634 , 3648 );
	machine.SetNextPosition( 83634 , 3648 );
	machine.SetNextPosition( 83676 , 3169 );
	machine.SetNextPosition( 83794 , 2770 );
	machine.SetNextPosition( 83994 , 2406 );
	machine.SetNextPosition( 84275 , 2088 );
	machine.SetNextPosition( 84624 , 1841 );
	machine.SetNextPosition( 85040 , 1660 );
	machine.SetNextPosition( 85485 , 1557 );
	machine.SetNextPosition( 86028 , 1518 );
	machine.SetNextPosition( 86769 , 1590 );
	machine.SetNextPosition( 87393 , 1786 );
	machine.SetNextPosition( 87956 , 2116 );
	machine.SetNextPosition( 88458 , 2590 );
	machine.SetNextPosition( 88856 , 3165 );
	machine.SetNextPosition( 89149 , 3845 );
	machine.SetNextPosition( 89316 , 4569 );
	machine.SetNextPosition( 89378 , 5445 );
	machine.SetNextPosition( 89378 , 5845 );
	machine.SetNextPosition( 89328 , 5895 );
	machine.SetNextPosition( 87541 , 5895 );
	machine.SetNextPosition( 91075 , 397 );
	machine.SetNextPosition( 91075 , 6586 );
	machine.SetNextPosition( 90993 , 7818 );
	machine.SetNextPosition( 90785 , 8755 );
	machine.SetNextPosition( 90406 , 9625 );
	machine.SetNextPosition( 89917 , 10283 );
	machine.SetNextPosition( 89283 , 10801 );
	machine.SetNextPosition( 88465 , 11194 );
	machine.SetNextPosition( 87573 , 11412 );
	machine.SetNextPosition( 86408 , 11498 );
	machine.SetNextPosition( 85972 , 11486 );
	machine.SetNextPosition( 85523 , 11450 );
	machine.SetNextPosition( 85075 , 11390 );
	machine.SetNextPosition( 84612 , 11304 );
	machine.SetNextPosition( 84153 , 11201 );
	machine.SetNextPosition( 83674 , 11071 );
	machine.SetNextPosition( 83200 , 10920 );
	machine.SetNextPosition( 82738 , 10752 );
	machine.SetNextPosition( 82738 , 9210 );
	machine.SetNextPosition( 83082 , 9383 );
	machine.SetNextPosition( 83507 , 9566 );
	machine.SetNextPosition( 83942 , 9722 );
	machine.SetNextPosition( 84384 , 9849 );
	machine.SetNextPosition( 84834 , 9948 );
	machine.SetNextPosition( 85291 , 10018 );
	machine.SetNextPosition( 85752 , 10061 );
	machine.SetNextPosition( 86222 , 10075 );
	machine.SetNextPosition( 86960 , 10027 );
	machine.SetNextPosition( 87546 , 9902 );
	machine.SetNextPosition( 88099 , 9677 );
	machine.SetNextPosition( 88539 , 9380 );
	machine.SetNextPosition( 88908 , 8997 );
	machine.SetNextPosition( 89169 , 8546 );
	machine.SetNextPosition( 89321 , 8045 );
	machine.SetNextPosition( 89378 , 7427 );
	machine.SetNextPosition( 89378 , 7252 );
	machine.SetNextPosition( 89328 , 7201 );
	machine.SetNextPosition( 86809 , 7201 );
	machine.SetNextPosition( 85597 , 7136 );
	machine.SetNextPosition( 84673 , 6969 );
	machine.SetNextPosition( 83795 , 6660 );
	machine.SetNextPosition( 83148 , 6274 );
	machine.SetNextPosition( 82617 , 5754 );
	machine.SetNextPosition( 82240 , 5129 );
	machine.SetNextPosition( 82021 , 4426 );
	machine.SetNextPosition( 81937 , 3531 );
	machine.SetNextPosition( 81937 , 3531 );
	machine.SetNextPosition( 81937 , 3531 );
	machine.SetNextPosition( 82003 , 2761 );
	machine.SetNextPosition( 82180 , 2126 );
	machine.SetNextPosition( 82483 , 1544 );
	machine.SetNextPosition( 82908 , 1038 );
	machine.SetNextPosition( 83435 , 638 );
	machine.SetNextPosition( 84057 , 346 );
	machine.SetNextPosition( 84728 , 177 );
	machine.SetNextPosition( 85549 , 114 );
	machine.SetNextPosition( 86205 , 145 );
	machine.SetNextPosition( 86763 , 230 );
	machine.SetNextPosition( 87308 , 380 );
	machine.SetNextPosition( 87772 , 577 );
	machine.SetNextPosition( 88203 , 843 );
	machine.SetNextPosition( 88603 , 1177 );
	machine.SetNextPosition( 88954 , 1563 );
	machine.SetNextPosition( 89286 , 2034 );
	machine.SetNextPosition( 89378 , 2007 );
	machine.SetNextPosition( 89378 , 397 );
	machine.SetNextPosition( 91075 , 397 );
	machine.SetNextPosition( 22152 , 15492 );
	machine.SetNextPosition( 22152 , 13317 );
	machine.SetNextPosition( 23849 , 13317 );
	machine.SetNextPosition( 23849 , 15492 );
	machine.SetNextPosition( 22152 , 15492 );
	machine.SetNextPosition( 94886 , 15492 );
	machine.SetNextPosition( 94886 , 13317 );
	machine.SetNextPosition( 96583 , 13317 );
	machine.SetNextPosition( 96583 , 15492 );
	machine.SetNextPosition( 94886 , 15492 );
	machine.SetNextPosition( 51898 , 2521 );
	machine.SetNextPosition( 51898 , 784 );
	machine.SetNextPosition( 52392 , 633 );
	machine.SetNextPosition( 52888 , 497 );
	machine.SetNextPosition( 53389 , 381 );
	machine.SetNextPosition( 53859 , 289 );
	machine.SetNextPosition( 54337 , 212 );
	machine.SetNextPosition( 54791 , 158 );
	machine.SetNextPosition( 55249 , 125 );
	machine.SetNextPosition( 55686 , 114 );
	machine.SetNextPosition( 56726 , 175 );
	machine.SetNextPosition( 57554 , 334 );
	machine.SetNextPosition( 58342 , 621 );
	machine.SetNextPosition( 58967 , 993 );
	machine.SetNextPosition( 59500 , 1484 );
	machine.SetNextPosition( 59860 , 2022 );
	machine.SetNextPosition( 60077 , 2633 );
	machine.SetNextPosition( 60157 , 3365 );
	machine.SetNextPosition( 60102 , 4015 );
	machine.SetNextPosition( 59958 , 4536 );
	machine.SetNextPosition( 59708 , 5010 );
	machine.SetNextPosition( 59362 , 5407 );
	machine.SetNextPosition( 58940 , 5732 );
	machine.SetNextPosition( 58298 , 6065 );
	machine.SetNextPosition( 57612 , 6314 );
	machine.SetNextPosition( 56670 , 6558 );
	machine.SetNextPosition( 56056 , 6695 );
	machine.SetNextPosition( 55336 , 6874 );
	machine.SetNextPosition( 54846 , 7026 );
	machine.SetNextPosition( 54372 , 7221 );
	machine.SetNextPosition( 54113 , 7378 );
	machine.SetNextPosition( 53891 , 7588 );
	machine.SetNextPosition( 53739 , 7823 );
	machine.SetNextPosition( 53648 , 8088 );
	machine.SetNextPosition( 53614 , 8404 );
	machine.SetNextPosition( 53614 , 8404 );
	machine.SetNextPosition( 53614 , 8404 );
	machine.SetNextPosition( 53661 , 8814 );
	machine.SetNextPosition( 53785 , 9145 );
	machine.SetNextPosition( 53996 , 9431 );
	machine.SetNextPosition( 54302 , 9677 );
	machine.SetNextPosition( 54662 , 9850 );
	machine.SetNextPosition( 55157 , 9991 );
	machine.SetNextPosition( 55670 , 10065 );
	machine.SetNextPosition( 56340 , 10094 );
	machine.SetNextPosition( 56782 , 10082 );
	machine.SetNextPosition( 57210 , 10045 );
	machine.SetNextPosition( 57636 , 9984 );
	machine.SetNextPosition( 58051 , 9898 );
	machine.SetNextPosition( 58460 , 9787 );
	machine.SetNextPosition( 58862 , 9652 );
	machine.SetNextPosition( 59255 , 9493 );
	machine.SetNextPosition( 59570 , 9345 );
	machine.SetNextPosition( 59570 , 10928 );
	machine.SetNextPosition( 59231 , 11051 );
	machine.SetNextPosition( 58832 , 11171 );
	machine.SetNextPosition( 58427 , 11269 );
	machine.SetNextPosition( 57992 , 11353 );
	machine.SetNextPosition( 57554 , 11416 );
	machine.SetNextPosition( 57088 , 11462 );
	machine.SetNextPosition( 56621 , 11489 );
	machine.SetNextPosition( 56125 , 11498 );
	machine.SetNextPosition( 55133 , 11439 );
	machine.SetNextPosition( 54356 , 11290 );
	machine.SetNextPosition( 53620 , 11017 );
	machine.SetNextPosition( 53050 , 10669 );
	machine.SetNextPosition( 52576 , 10206 );
	machine.SetNextPosition( 52245 , 9672 );
	machine.SetNextPosition( 52050 , 9071 );
	machine.SetNextPosition( 51976 , 8326 );
	machine.SetNextPosition( 51976 , 8326 );
	machine.SetNextPosition( 51976 , 8326 );
	machine.SetNextPosition( 52026 , 7708 );
	machine.SetNextPosition( 52158 , 7208 );
	machine.SetNextPosition( 52388 , 6748 );
	machine.SetNextPosition( 52703 , 6360 );
	machine.SetNextPosition( 53095 , 6047 );
	machine.SetNextPosition( 53663 , 5740 );
	machine.SetNextPosition( 54272 , 5511 );
	machine.SetNextPosition( 55092 , 5298 );
	machine.SetNextPosition( 55716 , 5152 );
	machine.SetNextPosition( 56548 , 4951 );
	machine.SetNextPosition( 57096 , 4782 );
	machine.SetNextPosition( 57625 , 4561 );
	machine.SetNextPosition( 57894 , 4390 );
	machine.SetNextPosition( 58122 , 4163 );
	machine.SetNextPosition( 58282 , 3895 );
	machine.SetNextPosition( 58376 , 3595 );
	machine.SetNextPosition( 58412 , 3227 );
	machine.SetNextPosition( 58364 , 2833 );
	machine.SetNextPosition( 58234 , 2501 );
	machine.SetNextPosition( 58022 , 2214 );
	machine.SetNextPosition( 57705 , 1955 );
	machine.SetNextPosition( 57340 , 1772 );
	machine.SetNextPosition( 56859 , 1627 );
	machine.SetNextPosition( 56361 , 1548 );
	machine.SetNextPosition( 55725 , 1518 );
	machine.SetNextPosition( 55249 , 1534 );
	machine.SetNextPosition( 54766 , 1582 );
	machine.SetNextPosition( 54287 , 1661 );
	machine.SetNextPosition( 53798 , 1774 );
	machine.SetNextPosition( 53316 , 1920 );
	machine.SetNextPosition( 52817 , 2103 );
	machine.SetNextPosition( 52331 , 2311 );
	machine.SetNextPosition( 51898 , 2521 );
	machine.SetNextPosition( 36593 , 397 );
	machine.SetNextPosition( 36593 , 15492 );
	machine.SetNextPosition( 34896 , 15492 );
	machine.SetNextPosition( 34896 , 9625 );
	machine.SetNextPosition( 34803 , 9599 );
	machine.SetNextPosition( 34496 , 10062 );
	machine.SetNextPosition( 34168 , 10439 );
	machine.SetNextPosition( 33793 , 10766 );
	machine.SetNextPosition( 33386 , 11026 );
	machine.SetNextPosition( 32950 , 11229 );
	machine.SetNextPosition( 32452 , 11379 );
	machine.SetNextPosition( 31937 , 11467 );
	machine.SetNextPosition( 31340 , 11498 );
	machine.SetNextPosition( 30384 , 11395 );
	machine.SetNextPosition( 29563 , 11108 );
	machine.SetNextPosition( 28831 , 10636 );
	machine.SetNextPosition( 28147 , 9936 );
	machine.SetNextPosition( 27618 , 9108 );
	machine.SetNextPosition( 27225 , 8121 );
	machine.SetNextPosition( 27002 , 7076 );
	machine.SetNextPosition( 26917 , 5806 );
	machine.SetNextPosition( 27002 , 4536 );
	machine.SetNextPosition( 27225 , 3491 );
	machine.SetNextPosition( 27618 , 2505 );
	machine.SetNextPosition( 28147 , 1676 );
	machine.SetNextPosition( 28831 , 977 );
	machine.SetNextPosition( 29563 , 504 );
	machine.SetNextPosition( 30384 , 218 );
	machine.SetNextPosition( 31340 , 114 );
	machine.SetNextPosition( 31937 , 145 );
	machine.SetNextPosition( 32452 , 230 );
	machine.SetNextPosition( 32951 , 378 );
	machine.SetNextPosition( 33386 , 577 );
	machine.SetNextPosition( 33793 , 840 );
	machine.SetNextPosition( 34168 , 1171 );
	machine.SetNextPosition( 34496 , 1550 );
	machine.SetNextPosition( 34803 , 2013 );
	machine.SetNextPosition( 34896 , 1988 );
	machine.SetNextPosition( 34896 , 397 );
	machine.SetNextPosition( 36593 , 397 );
	machine.SetNextPosition( 109327 , 397 );
	machine.SetNextPosition( 109327 , 15492 );
	machine.SetNextPosition( 107630 , 15492 );
	machine.SetNextPosition( 107630 , 9625 );
	machine.SetNextPosition( 107537 , 9599 );
	machine.SetNextPosition( 107230 , 10062 );
	machine.SetNextPosition( 106903 , 10439 );
	machine.SetNextPosition( 106527 , 10766 );
	machine.SetNextPosition( 106120 , 11026 );
	machine.SetNextPosition( 105684 , 11229 );
	machine.SetNextPosition( 105186 , 11379 );
	machine.SetNextPosition( 104671 , 11467 );
	machine.SetNextPosition( 104074 , 11498 );
	machine.SetNextPosition( 103118 , 11395 );
	machine.SetNextPosition( 102297 , 11108 );
	machine.SetNextPosition( 101565 , 10636 );
	machine.SetNextPosition( 100881 , 9936 );
	machine.SetNextPosition( 100353 , 9108 );
	machine.SetNextPosition( 99960 , 8121 );
	machine.SetNextPosition( 99736 , 7076 );
	machine.SetNextPosition( 99652 , 5806 );
	machine.SetNextPosition( 99736 , 4536 );
	machine.SetNextPosition( 99960 , 3491 );
	machine.SetNextPosition( 100353 , 2505 );
	machine.SetNextPosition( 100881 , 1676 );
	machine.SetNextPosition( 101565 , 977 );
	machine.SetNextPosition( 102297 , 504 );
	machine.SetNextPosition( 103118 , 218 );
	machine.SetNextPosition( 104074 , 114 );
	machine.SetNextPosition( 104671 , 145 );
	machine.SetNextPosition( 105186 , 230 );
	machine.SetNextPosition( 105685 , 378 );
	machine.SetNextPosition( 106121 , 577 );
	machine.SetNextPosition( 106527 , 840 );
	machine.SetNextPosition( 106903 , 1171 );
	machine.SetNextPosition( 107230 , 1550 );
	machine.SetNextPosition( 107537 , 2013 );
	machine.SetNextPosition( 107630 , 1988 );
	machine.SetNextPosition( 107630 , 397 );
	machine.SetNextPosition( 109327 , 397 );
	route_data = machine.routes;
	DisplayStepCoordinate(route_data);
}

cute::suite make_suite_test_cncmachine(){
	cute::suite s;

	//push_back tests to s
//	s.push_back(CUTE(outOfRangeTest));
//	s.push_back(CUTE(InputCoordinateTest));
//	s.push_back(CUTE(thisIsATest));
	//s.push_back(CUTE(routeTest));
	//s.push_back(CUTE(routeTestSmallNumbers));
	s.push_back(CUTE(routeTestReturnStepCoordinates));
	return s;
}



