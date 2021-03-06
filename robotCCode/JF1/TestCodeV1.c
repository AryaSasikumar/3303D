#pragma config(Sensor, in4,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in5,    turnerSensor,   sensorLineFollower)
#pragma config(Sensor, in6,    navPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,  green1,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  green2,         sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  red1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  red2,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, flyWheelEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           ballIntake,    tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightShot,     tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           rightExtreme,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           rightMid,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightLift,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           leftExtreme,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftMid,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftShot,      tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          turner,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

int direction = 1;
int ACTIVATE = 300;
int LS = 100;
int LSA = LS;
float Kp = 1;
#define PID_INTEGRAL_LIMIT  50
static float velocity = 16;
float  CurrentVelocity;
float Error;
bool revvedup = false;
bool on = false;

bool liftHoldToggle = true;

const unsigned int TrueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};



/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
//********************************************************************************************************//
//********************************************DRIVER_FUNCTIONS*********************************************//
//********************************************************************************************************//

void ledControl()
{
	if(direction == 1)
	{
		SensorValue[green1] = 1;
		SensorValue[green2] = 1;
		SensorValue[red1] = 0;
		SensorValue[red2] = 0;
	}
	else if(direction == -1)
	{
		SensorValue[green1] = 0;
		SensorValue[green2] = 0;
		SensorValue[red1] = 1;
		SensorValue[red2] = 1;
	}
}

//-----MOTOR_CONNECTION_FUNCTIONS-----//
void leftBase(int power)//Function used to control all the motors on the left side of the base at once.
{
	motor[leftExtreme] = power;
	motor[leftMid] = power;
}

void rightBase(int power)//Function used to control all the motors on the right side of the base at once.
{
	motor[rightExtreme] = power;
	motor[rightMid] = power;
}

//-----MOTOR_CONNECTION_FUNCTIONS-----//


void baseDriver(int RT2, int RT1)//Function to control base during driver control
{
		if(RT2 > 0)
		{
			leftBase(-TrueSpeed[RT2]);
		}
		else if(RT2 < 0)
		{
			RT2 = RT2 * -1;
			leftBase(TrueSpeed[RT2]);
		}

		if(RT1 > 0)
		{
			rightBase(-TrueSpeed[RT1]);
		}
		else if(RT1 < 0)
		{
			RT1 = RT1 * -1;
			rightBase(TrueSpeed[RT1]);
		}
}

void base(int rSpeed, int lSpeed)
{
	rightBase(rSpeed);
	leftBase(lSpeed);
}
/*
task vroomvroom()
{
clearTimer(T1);
SensorValue[flyWheelEncoder] = 0;
while( true )
{

CurrentVelocity = (SensorValue[flyWheelEncoder] / (time1[T1] + 0.000001));
Error = CurrentVelocity - velocity;
if(revvedup)
{
// calculate error
if(Error < -0.2)
{
LSA = 127;
wait1Msec(1);
}
else
{
LSA = (LS - (LS * Error * Kp));
}
}
else
{
LSA = LS;
if(Error > 0)
{
revvedup = true;
}
}
clearTimer(T1);
SensorValue[flyWheelEncoder] = 0;
wait1Msec(10);
}
}

task fwdecel()
{
motor[rightShot] = 80;
motor[leftShot] = 80;
wait1Msec(300);
motor[rightShot] = 40;
motor[leftShot] = 40;
wait1Msec(100);
motor[rightShot] = 0;
motor[leftShot] = 0;
revvedup = false;
}
*/

void pre_auton()
{

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
	// ..........................................................................
	// Insert user code here.
	// ..........................................................................

	// Remove this function call once you have "real" code.
	AutonomousCodePlaceholderForTesting();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task usercontrol()
{

	// User control code here, inside the loop

	//startTask(vroomvroom);
	SensorValue[flyWheelEncoder] = 0;

	while (true)
	{
		ledControl();
		if(vexRT[Btn6U] == 1)
		{
			motor[ballIntake] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[ballIntake] = -127;

		}
		else
		{
			motor[ballIntake] = 0;
		}



		if(vexRT[Btn8R] == 1)
		{
			direction = direction * (-1);
			wait1Msec(250);
		}
		if(direction == -1)
		{
			baseDriver((vexRT[Ch2]),(vexRT[Ch3]));
		}
		else
		{
			baseDriver((-vexRT[Ch3]),(-vexRT[Ch2]));
		}









		if(vexRT[Btn8U] == 1)
		{
			motor[rightShot] = 127;
			motor[leftShot] = 127;
		}
		else
		{
			motor[rightShot] = 0;
			motor[leftShot] = 0;
		}
		/*
		if(vexRT[Btn6U] == 1)
		{
		on = true;
		}
		else if(vexRT[Btn6D] == 1)
		{
		startTask(fwdecel);
		on = false;
		}
		if(on)
		{
		motor[rightShot] = LSA;
		motor[leftShot] = LSA;
		}
		*/


		if(vexRT[Btn5U] == 1)
		{
			motor[rightLift] = -127;
			motor[leftLift] = -127;
		}
		else if(vexRT[Btn5D] == 1)
		{
			motor[rightLift] = 127;
			motor[leftLift] = 127;

		}
		else
		{
			if(SensorValue[liftPot] <= 2300)
			{
				motor[rightLift] = 10;
				motor[leftLift] = 10;
			}
			else
			{
				if(liftHoldToggle == false)
				{
					motor[rightLift] = -10;
					motor[leftLift] = -10;
				}
				else
				{
					motor[rightLift] = -20;
					motor[leftLift] = -20;
				}
			}

		}
		if(vexRT[Btn7L] == 1)
		{
			liftHoldToggle = !liftHoldToggle;
			wait1Msec(250);
		}


		if(vexRT[Btn7U] == 1)
		{
			motor[turner] = -127;
		}
		else if(vexRT[Btn7D] == 1)
		{
			motor[turner] = 127;
		}
		else
		{
			motor[turner] = 0;
		}


	}





















}
