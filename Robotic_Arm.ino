/*************************************************************
/* 6 DOF Robotic Arm inverse kinematics code for Arduino
/* By: Dhrumil Parikh
/* Date Created: 20-Oct-2017
*************************************************************/

#include <Servo.h>

#define L1                      235.0
#define L2                      130.0
#define L3                      130

#define BASE_SERVO				0
#define SHOULDER_SERVO			1
#define ELBOW_SERVO				2
#define WRIST_SERVO				3
#define WRIST_ROTATE_SERVO	 	4
#define GRIPPER_SERVO			5

#define GRIPPER_CLOSED			100
#define GRIPPER_OPENED			45

/*Servos are numbered bottom to top (on arm)*/
Servo servo[6];			  // Create 6 servos

//servo[0]			      // BASE			Servo 0 Bottom most 
//servo[1]		          // SHOULDER		Servo 1  
//servo[2]		          // ELBOW			Servo 2
//servo[3]		          // WRIST			Servo 3
//servo[4]		          // WRIST ROTATE	Servo 4
//servo[5]		          // GRIPPER		Servo 5 Top Most

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
}

void arm_home()
{
	servo[BASE_SERVO].write(90);
	servo[SHOULDER_SERVO].write(100);
	servo[ELBOW_SERVO].write(100);
	servo[WRIST_SERVO].write(85);
	servo[WRIST_ROTATE_SERVO].write(90);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
	delay(1000);
}

int poser = 0; // initial position of servero
void ControlWithKeyBoard()
{
	int val; // initial value of input

	if (Serial.available()) // if serial value is available 
	{
		val = Serial.read();// then read the serial value
		if (val == 'd') //if value input is equals to d
		{
			poser += 10; //than position of servo motor increases by 1 ( anti clockwise)
			servo[WRIST_SERVO].write(poser);// the servo will move according to position
			delay(15);//delay for the servo to get to the position
		}
		if (val == 'a') //if value input is equals to a
		{
			poser -= 10; //than position of servo motor decreases by 1 (clockwise)
			servo[WRIST_SERVO].write(poser);// the servo will move according to position
			delay(15);//delay for the servo to get to the position
		}

	}
	Serial.println(poser);
	if (poser >= 180)
	{
		poser = 180;
	}
	if (poser <= 0)
	{
		poser = 0;
	}
}


void loop()
{
	////arm_home();
	//Smooth(0, 100, 200,  200, 100, 200);// Step 1 -> Step 2
	////Goto(0, 100, 200); // Step 1
	////delay(2000);
	////Goto(200, 100, 200);// Step 2
	////delay(2000);
	//Smooth(200, 100, 200,  200, 200, 200);// Step 2 -> Step 3
	////Goto(200, 200, 200);// Step 3
	//Grab();
	//Smooth(200, 200, 200,  200, 100, 200);// Step 3 -> Step 4
	////delay(2000);
	////Goto(200, 100, 200);// Step 4
	////delay(2000);
	//Smooth(200, 100, 200,  -50, 100, 200);// Step 4 -> Step 5
	////Goto(-50, 100, 200);// Step 5
	////delay(2000);
	//Smooth(-50, 100, 200,  -100, 100, 200);// Step 5 -> Step 6
	////Goto(-100, 100, 200); //(0,0,0) Step 6
	////delay(2000);
	//Smooth(-100, 100, 200,  -150, 100, 0);// Step 6 -> Step 7
	////Goto(-150, 100, 0);// Step 7
	////delay(2000);
	//Smooth(-150, 100, 0,  -100, 100, 0);// Step 7 -> Step 8
	////Goto(-100, 100, 0);// Step 8
	////delay(2000);
	//Smooth(-100, 100, 0,  -100, 100,150); //Step 8 -> Step 9
	//delay(10000);
	//Smooth(-100, 100, 150,  -100, 100, 0);//Step 10 -> Step 11
	//
	//Smooth(-100, 100, 0,  -150, 100, 0);//Step 11 -> Step 12
	////Goto(-150, 100, 0);// Step 12
	////delay(2000);
	//Smooth(-150, 100, 0,  -50, 100, 200);//Step 12 -> Step 13
	////Goto(-50, 100, 200);// Step 13
	////delay(2000);
	//Smooth(-50, 100, 200,  -100, 100, 200);//Step 13 -> Step 14
	////Goto(-100, 100, 200); //(0,0,0) Step 14
	////delay(2000);
	//Smooth(-100, 100, 200,  -50, 100, 200);//Step 14 -> Step 15
	////Goto(-50, 100, 200); //Step 15
	////delay(2000);
	//Smooth(-50, 100, 200,  200, 100, 200);//Step 15 -> Step 19
	////Goto(200, 100, 200); // Step 19
	////delay(2000);
	//Smooth(200, 100, 200,  0, 100, 200);//Step 10 -> Step 20
	//
	////Goto(0, 100, 200); // Step 20
	////delay(5000);
	//servo[GRIPPER_SERVO].write(95);
    //delay(5000);
    //servo[GRIPPER_SERVO].write(180);
    //delay(5000);
	Goto(0, 100, 62);// Step 8
  servo[WRIST_ROTATE_SERVO].write(180);
  servo[GRIPPER_SERVO].write(60);
  delay(1000);
  servo[GRIPPER_SERVO].write(85);
  delay(1000);
  servo[WRIST_ROTATE_SERVO].write(45);
  delay(1000);
  servo[GRIPPER_SERVO].write(60);
  delay(1000);
  servo[WRIST_ROTATE_SERVO].write(180);
  delay(1000);



}

//From -> To
#define TIME	10
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
		for (x; x > x2 ; x--)
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





	//for (int i = 0; i <= 150; i += 1)
	//{
	//	Goto(-100, 100, i);// Step 9
	//	delay(50);
	//}
	//delay(10000);//Step 10
	//for (int i = 150; i >= 0; i -= 1)
	//{
	//	Goto(-100, 100, i);// Step 11
	//	delay(50);
	//}
}

void Grab()
{
	servo[GRIPPER_SERVO].write(GRIPPER_OPENED);
	delay(500);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
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
	servo[SHOULDER_SERVO].write(180-t2);
	servo[ELBOW_SERVO].write(97);//Always constent
	servo[WRIST_SERVO].write(190-t3);

}
