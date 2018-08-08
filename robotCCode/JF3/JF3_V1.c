#pragma config(Sensor, in3,    ballDetectorBottom, sensorLineFollower)
#pragma config(Sensor, in4,    turnerSensor,   sensorPotentiometer)
#pragma config(Sensor, in5,    clawPot,        sensorPotentiometer)
#pragma config(Sensor, in6,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in7,    ballDetectorTop, sensorLineFollower)
#pragma config(Sensor, dgtl1,  leftBaseEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  turnerTop,      sensorTouch)
#pragma config(Sensor, dgtl9,  flyWheelEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, rightBaseEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           capClaw,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           flyWheel,      tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           ballIntake,    tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           leftFrontBase, tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port5,           rightFrontBase, tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port6,           rightMiddleBase, tmotorVex393TurboSpeed_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port7,           leftMiddleBase, tmotorVex393TurboSpeed_MC29, openLoop, driveLeft)
#pragma config(Motor,  port8,           lift,          tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           capTurner,     tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          ballElevator,  tmotorVex393TurboSpeed_HBridge, openLoop)
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

#include "functions/buttonDefinitions.h"
#include "functions/sensorDefinitions.h"
#include "functions/motorControlFunctions.h"
#include "functions/driverControl.h"
#include "functions/autonomusFunctions.h"

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks
	// running between Autonomous and Driver controlled modes. You will need to
	// manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// Set bDisplayCompetitionStatusOnLcd to false if you don't want the LCD
	// used by the competition include file, for example, you might want
	// to display your team name on the LCD in this function.
	// bDisplayCompetitionStatusOnLcd = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
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
	flyWheelRev(on,48);
	drivePID(forwards, 48);// (Direction:"forwards, backwards", Distance: inches)
	driveTurnPID(right, 90);
	autoBallIntake(1, 0);
	autoBallIntake(0, 0);
	autoBallIntake(1, 1);
	flyWheelRev(off,0);
	while(true)
	{

	}
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
	clearTimer(T2);
	while (true)
	{
		directionController(changeDirectionBtn);
		baseController(Y_rightJoy, Y_leftJoy);
		liftControl(liftUpBtn, liftDownBtn, liftSensor);
		ballIntakeController(currentIntake(1), currentOuttake(1));
		capIntakeController(currentIntake(0), currentOuttake(0), clawSensor);
		capRotateController(capRotateBtn,clawTurnerSensor); //clawTurnerSensor
		flyWheelController(flyWheelToggleBtn, 48);
		//Cross Cort -- 53
		//Aginst Back Tile -- Top Flag -- 48
		//One Tile Up -- Top Flag -- 46.5
		//Front colored tile -- Top Flag -- 40
		//Front colored tile -- Top Flag -- 33

	}
}
