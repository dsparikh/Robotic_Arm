#include <Servo.h>

#define SERVO_NUM		0
#define GRIPPER_CLOSED	100
#define GRIPPER_OPENED	45
#define TIME			5000
/*Servos are numbered bottom to top (on arm)*/
Servo servo[6];			  // Create 6 servos
//servo[0]			      // servo_xy_rotate	Servo 0 Bottom most 
//servo[1]		          // servo_axis_lower   Servo 1  
//servo[2]		          // servo_axis_middle	Servo 2
//servo[3]		          // servo_axis_upper	Servo 3
//servo[4]		          // servo_axis_gripper Servo 4
//servo[5]		          // servo_gripper		Servo 5 Top Most

void arm_home()
{
	servo[0].write(90);
	servo[1].write(90);
	servo[2].write(90);
	servo[3].write(0);
	servo[4].write(90);
	servo[5].write(95);//closed
}
void setup() 
{
	Serial.begin(9600);
	Serial.println("Arduino Running...");
	servo[SERVO_NUM].attach(9);	
	//servo[1].attach(1);
	//servo[2].attach(2);
	//servo[3].attach(3);
	//servo[4].attach(4);
	//servo[5].attach(5);
}
int poser = 0; // initial position of server

int val; // initial value of input
void loop()
{
	if (Serial.available()) // if serial value is available 
	{
		val = Serial.read();// then read the serial value
		if (val == 'd') //if value input is equals to d
		{
			poser += 10; //than position of servo motor increases by 1 ( anti clockwise)
			servo[SERVO_NUM].write(poser);// the servo will move according to position
			delay(15);//delay for the servo to get to the position
		}
		if (val == 'a') //if value input is equals to a
		{
			poser -= 10; //than position of servo motor decreases by 1 (clockwise)
			servo[SERVO_NUM].write(poser);// the servo will move according to position
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
