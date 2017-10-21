/************************************************************* 
/* 6 DOF Robotic Arm inverse kinematics code for Arduino
/* By: Dhrumil Parikh
/* Date: 20-Oct-2017
*************************************************************/

#include <Servo.h>


#define BASE_SERVO				0
#define SHOULDER_SERVO			1
#define ELBOW_SERVO				2
#define WRIST_SERVO				3
#define WRIST_ROTATE_SERVO	 	4
#define GRIPPER_SERVO			5

#define GRIPPER_CLOSED			100
#define GRIPPER_OPENED			45
#define TIME					5000

//Dimensions in mm
#define GRIPPER					130.00 
#define BASE_HGT				60.00
#define HUMERUS					146.05      //shoulder-to-elbow "bone" 5.75"
#define ULNA					100.00        //elbow-to-wrist "bone" 7.375"

float hum_sq = HUMERUS*HUMERUS;
float uln_sq = ULNA*ULNA;

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
	servo[SHOULDER_SERVO].write(90);
	servo[ELBOW_SERVO].write(90);
	servo[WRIST_SERVO].write(0);
	servo[WRIST_ROTATE_SERVO].write(90);
	servo[GRIPPER_SERVO].write(GRIPPER_CLOSED);
}

void ControlWithKeyBoard()
{
	int poser = 0; // initial position of servero

	int val; // initial value of input

	if (Serial.available()) // if serial value is available 
	{
		val = Serial.read();// then read the serial value
		if (val == 'd') //if value input is equals to d
		{
			poser += 10; //than position of servo motor increases by 1 ( anti clockwise)
			servo[BASE_SERVO].write(poser);// the servo will move according to position
			delay(15);//delay for the servo to get to the position
		}
		if (val == 'a') //if value input is equals to a
		{
			poser -= 10; //than position of servo motor decreases by 1 (clockwise)
			servo[BASE_SERVO].write(poser);// the servo will move according to position
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
	//servo[WRIST_SERVO].writeMicroseconds(1000);
	GoToPos(0, 0, 150, 90);
	//delay(1000);
	//servo[BASE_SERVO].write(180);
	//delay(1000);
}

void GoToPos(float x, float y, float z, float grip_angle_d)
{
	float grip_angle_r = radians(grip_angle_d);
	float bas_angle_r = atan2(x, y);

	y = sqrt((x * x) + (y * y)); 

	float grip_off_z = (sin(grip_angle_r)) * GRIPPER;
	float grip_off_y = (cos(grip_angle_r)) * GRIPPER;

	float wrist_z = (z - grip_off_z) - BASE_HGT;
	float wrist_y = y - grip_off_y;

	/* Shoulder to wrist distance ( AKA sw ) */
	float s_w = (wrist_z * wrist_z) + (wrist_y * wrist_y);
	float s_w_sqrt = sqrt(s_w);

	/* s_w angle to ground */
	//float a1 = atan2( wrist_y, wrist_z );
	float a1 = atan2(wrist_z, wrist_y);
	/* s_w angle to humerus */
	float a2 = acos(((hum_sq - uln_sq) + s_w) / (2 * HUMERUS * s_w_sqrt));
	/* shoulder angle */
	float shl_angle_r = a1 + a2;
	float shl_angle_d = degrees(shl_angle_r);
	/* elbow angle */
	float elb_angle_r = acos((hum_sq + uln_sq - s_w) / (2 * HUMERUS * ULNA));
	float elb_angle_d = degrees(elb_angle_r);
	float elb_angle_dn = -(180.0 - elb_angle_d);
	/* wrist angle */
	float wri_angle_d = (grip_angle_d - elb_angle_dn) - shl_angle_d;




	float bas_servopulse = 1500.0 - ((degrees(bas_angle_r)) * 11.11);
	float shl_servopulse = 1500.0 + ((shl_angle_d - 90.0) * 6.6);
	float elb_servopulse = 1500.0 - ((elb_angle_d - 90.0) * 6.6);
	float wri_servopulse = 1500 + (wri_angle_d  * 11.1);


	servo[BASE_SERVO].writeMicroseconds(bas_servopulse);
	servo[SHOULDER_SERVO].writeMicroseconds(shl_servopulse);
	servo[ELBOW_SERVO].writeMicroseconds(elb_servopulse);
	servo[WRIST_SERVO].writeMicroseconds(wri_servopulse);

	Serial.println(elb_servopulse);
}
