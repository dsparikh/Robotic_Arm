/*************************************************************
/* 6 DOF Robotic Arm inverse kinematics code for Arduino
/* By: Dhrumil Parikh
/* Date Created: 20-Oct-2017
*************************************************************/

#include <Servo.h>

#define L1                          235.0
#define L2                          130.0
#define L3                          130

#define BASE_SERVO                  0
#define SHOULDER_SERVO              1
#define ELBOW_SERVO                 2
#define WRIST_SERVO                 3
#define WRIST_ROTATE_SERVO          4
#define GRIPPER_SERVO               5
#define RIGHT_PLATFORM              6
#define LEFT_PLATFORM               7


#define RIGHT_PLATFORM_MOTOR_STOP   78
#define LEFT_PLATFORM_MOTOR_STOP    88

#define GRIPPER_CLOSED              100
#define GRIPPER_OPENED              45

/*Servos are numbered bottom to top (on arm)*/
Servo servo[8];         // Create 8 servos

						//servo[0]              // BASE     Servo 0 Bottom most 
						//servo[1]              // SHOULDER   Servo 1  
						//servo[2]              // ELBOW      Servo 2
						//servo[3]              // WRIST      Servo 3
						//servo[4]              // WRIST ROTATE Servo 4
						//servo[5]              // GRIPPER    Servo 5 Top Most
						//servo[6]              // Right Platform Servo
						//servo[7]              // Left Platfrom Servo

#define PLATFORM_DIRECTION_RIGHT	0
#define PLATFORM_DIRECTION_LEFT		1


void setup()
{
	Serial.begin(9600);
	Serial.println("Arduino Running...");
	servo[BASE_SERVO].attach(2);
	servo[SHOULDER_SERVO].attach(3);
	servo[ELBOW_SERVO].attach(4);
	servo[WRIST_SERVO].attach(5);
	servo[WRIST_ROTATE_SERVO].attach(6);
	servo[GRIPPER_SERVO].attach(7);
	servo[RIGHT_PLATFORM].attach(8);
	servo[LEFT_PLATFORM].attach(9);
}

int PlatfromCounter = 0;

void arm_home()
{
	servo[BASE_SERVO].write(90);
	servo[SHOULDER_SERVO].write(100);
	servo[ELBOW_SERVO].write(100);
	servo[WRIST_SERVO].write(85);
	servo[WRIST_ROTATE_SERVO].write(93);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
	servo[RIGHT_PLATFORM].write(93);
	servo[LEFT_PLATFORM].write(92);
	//delay(1000);
}

void loop()
{
	int home_pos[3] = { 0, 155, 190 };

	arm_home();
	delay(500);

/*****************************************Slider*******************************************************/

	int slider_pos[3] = {-20, 190, 75};

	servo[GRIPPER_SERVO].write(GRIPPER_OPENED);
	Smooth(home_pos[0], home_pos[1], home_pos[2] , slider_pos[0], slider_pos[1], slider_pos[2]);
	delay(500);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
	Smooth(slider_pos[0], slider_pos[1], slider_pos[2], 180, slider_pos[1], slider_pos[2]);
	delay(2000);
	Smooth(180, slider_pos[1], slider_pos[2], -50, slider_pos[1], slider_pos[2]);
	servo[GRIPPER_SERVO].write(GRIPPER_OPENED);
	delay(500);
	Smooth(-50, slider_pos[1], slider_pos[2], -50, home_pos[1], home_pos[2]);
	Smooth(-50, home_pos[1], home_pos[2], home_pos[0], home_pos[1], home_pos[2]);

/****************************************Pipet 1*******************************************************/

	int pipet1_pos[3] = {-250, 190, 40};
	int cup_pos[3] = {150, 170, 250};

	servo[GRIPPER_SERVO].write(65);
	Smooth(home_pos[0], home_pos[1], home_pos[2], pipet1_pos[0], pipet1_pos[1], pipet1_pos[2]);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
	Smooth(pipet1_pos[0], pipet1_pos[1], pipet1_pos[2], pipet1_pos[0], pipet1_pos[1], 200);
	Smooth(pipet1_pos[0], pipet1_pos[1], 200, cup_pos[0], cup_pos[1], cup_pos[2]);
	 
	Smooth(cup_pos[0], cup_pos[1], cup_pos[2], cup_pos[0], cup_pos[1], 150);
	servo[GRIPPER_SERVO].write(85);
	delay(1000);
	Smooth(cup_pos[0], cup_pos[1], 150, cup_pos[0], cup_pos[1], cup_pos[2]);
	Smooth(cup_pos[0], cup_pos[1], cup_pos[2], home_pos[0], home_pos[1], home_pos[2]);

/****************************************Test Tube*******************************************************/
	//MovePlatform(PLATFORM_DIRECTION_RIGHT, 5000);


	//  Smooth(200,170,200,0,155,190);
	//  delay(1000);
	//  servo[RIGHT_PLATFORM].write(77+10);
	//  servo[LEFT_PLATFORM].write(88+10);
	//  delay(6000);
	//  servo[RIGHT_PLATFORM].write(77);
	//  servo[LEFT_PLATFORM].write(88);
	//  Smooth(0,155,190,-165,0,100);
	//  servo[GRIPPER_SERVO].write(100);
	//  delay(5000);
	//  Smooth(-165,0,100,-165,0,200);
	//  
	//  servo[RIGHT_PLATFORM].write(77-10);
	//  servo[LEFT_PLATFORM].write(88-10);
	//  delay(5800);
	//  servo[RIGHT_PLATFORM].write(77);
	//  servo[LEFT_PLATFORM].write(88);
	//  //garbage
	//  Smooth(-165,0,200,200,80,50);
	//  servo[GRIPPER_SERVO].write(65);

/****************************************Cap Closing*******************************************************/
	//servo[GRIPPER_SERVO].write(60);
	//delay(500);
	//Smooth(0,155,190,-120,150,5);
	//servo[GRIPPER_SERVO].write(80);
	//Smooth(-120,150,5,-120,150,100);
	//Smooth(-120,150,100,0,155,190);

	//servo[RIGHT_PLATFORM].write(77+10);
	//servo[LEFT_PLATFORM].write(88+10);
	//delay(6000);
	//servo[RIGHT_PLATFORM].write(77);
	//servo[LEFT_PLATFORM].write(88);
	//Smooth(0,155,190,-130,20,60);
	//delay(5000);
	////Close Cap
	//Smooth(-130,20,60,-130,20,100);
	//servo[RIGHT_PLATFORM].write(77-10);
	//servo[LEFT_PLATFORM].write(88-10);
	//delay(5000);
	//servo[RIGHT_PLATFORM].write(77);
	//servo[LEFT_PLATFORM].write(88);

/****************************************End*******************************************************/
	delay(2000000);
}

//From -> To
#define TIME  5
void Smooth(int x, int y, int z, int x2, int y2, int z2)
{
	delay(1000);
	//x
	if (x < x2)
	{
		for (x; x < x2; x++)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	else
	{
		for (x; x > x2; x--)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	//y
	if (y < y2)
	{
		for (y; y < y2; y++)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	else
	{
		for (y; y > y2; y--)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	//z
	if (z < z2)
	{
		for (z; z < z2; z++)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	else
	{
		for (z; z > z2; z--)
		{
			Goto(x, y, z); delay(TIME);
		}
	}
	delay(1000);
}

void Grab()
{
	servo[GRIPPER_SERVO].write(GRIPPER_OPENED);
	delay(500);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
}

void MovePlatform(int direction, int time)
{
	switch (direction)
	{
	case PLATFORM_DIRECTION_RIGHT:
		servo[RIGHT_PLATFORM].write(93 + 10);
		servo[LEFT_PLATFORM].write(92 + 10);
		delay(time);
		servo[RIGHT_PLATFORM].write(93);
		servo[LEFT_PLATFORM].write(92);
		break;
	case PLATFORM_DIRECTION_LEFT:
		servo[RIGHT_PLATFORM].write(93 - 10);
		servo[LEFT_PLATFORM].write(92 - 10);
		delay(time);
		servo[RIGHT_PLATFORM].write(93);
		servo[LEFT_PLATFORM].write(92);
		break;
	default:
		break;
	}
}

/*Two link Inverse kinametics*/
void Goto(float x, float y, float z)
{
	float theta_1 = atan2(y, x);//Base Servo

	float r_squared = (x*x) + (y*y);


	float theta_3 = -acos(((r_squared)+(z*z) - (L1*L1) - (L2*L2)) / (2 * L1*L2));

	float k1 = L1 + L2*cos(theta_3);
	float k2 = L2*sin(theta_3);

	float theta_2 = atan2(z, sqrt(r_squared)) - atan2(k2, k1);

	float t1 = degrees(theta_1);
	float t2 = degrees(theta_2);
	float t3 = degrees(theta_3);

	if (t3 < 0) { t3 = abs(t3); }

	servo[BASE_SERVO].write(t1);
	servo[SHOULDER_SERVO].write(180 - t2);
	servo[ELBOW_SERVO].write(97);//Always constent
	servo[WRIST_SERVO].write(190 - t3);

}