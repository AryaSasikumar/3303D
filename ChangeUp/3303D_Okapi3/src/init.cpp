#include "main.h"

Controller controller;

const double joyDeadband = .08;

alliances alliance;

void initActTasks()
{
    // Constructs and starts tasks for subsystems
    driveActTask = new pros::Task(drive::act, NULL, TASK_PRIORITY_DEFAULT,
                                  TASK_STACK_DEPTH_DEFAULT, "Act Drive");
    intakeActTask = new pros::Task(intake::act, NULL, TASK_PRIORITY_DEFAULT,
                                   TASK_STACK_DEPTH_DEFAULT, "Act Intake");
    updateTask = new pros::Task(updateFunc, NULL, TASK_PRIORITY_DEFAULT,
                                TASK_STACK_DEPTH_DEFAULT, "Update");
}

void waitUntilSettled(okapi::AbstractMotor &motor, double isAtTargetError = 50, double isAtTargetDerivative = 5, QTime isAtTargetTime = 250_ms)
{
    auto settledUtil = SettledUtilFactory::create(isAtTargetError, isAtTargetDerivative, isAtTargetTime);

    while (!settledUtil.isSettled(motor.getTargetPosition() - motor.getPosition()))
    {
        pros::delay(10);
    }
}

void updateFunc(void *)
{
    while (true)
    {

        drive::update();
        intake::update();
        // printf("isLoaded: %d | hasBall: %d\n", puncher::puncherIsLoaded, differential::intakeHasBall);

        pros::delay(5);
    }
}

void states();

void autonStates();