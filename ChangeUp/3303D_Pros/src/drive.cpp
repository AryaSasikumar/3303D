#include "main.h"
#include "okapi/api.hpp"

using namespace okapi;

namespace drive
{

    driveStates currState;
    Motor driveL1(DRIVE_L1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor driveL2(DRIVE_L2, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor driveL3(DRIVE_L3, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor driveR1(DRIVE_R1, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor driveR2(DRIVE_R2, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor driveR3(DRIVE_R3, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

    ADIEncoder leftTrackingEncoder(SPORT_LTOP, SPORT_LBOT, true);
    ADIEncoder rightTrackingEncoder(SPORT_RTOP, SPORT_RBOT);

    TimeUtil chassisUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);
    TimeUtil profiledUtil = TimeUtilFactory::withSettledUtilParams(50, 5, 100_ms);

    okapi::MotorGroup leftMotorGroup(
        {driveL1, driveL2, driveL3});
    okapi::MotorGroup rightMotorGroup(
        {driveR1, driveR2, driveR3});

    AbstractMotor::GearsetRatioPair GearsetRatioPair(AbstractMotor::gearset::blue);

    AsyncPosIntegratedController leftController(std::shared_ptr<MotorGroup>(&leftMotorGroup), GearsetRatioPair, 400, chassisUtil);
    AsyncPosIntegratedController rightController(std::shared_ptr<MotorGroup>(&rightMotorGroup), GearsetRatioPair, 400, chassisUtil);

    // ChassisScales integratedScale = std_initializer_list<ChassisScales>(4.125_in, 13.273906_in);
    // ChassisScales discreteScale = std_initializer_list<ChassisScales>(2.75_in, 7.402083_in);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SkidSteerModel ChassisModel(std::shared_ptr<MotorGroup>(&leftMotorGroup), std::shared_ptr<MotorGroup>(&rightMotorGroup), leftTrackingEncoder, rightTrackingEncoder, 600, 1200);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ChassisScales drivenWheelScales({3.25_in, 11.5_in}, imev5BlueTPR);

    ChassisControllerIntegrated chassisController(
        chassisUtil,
        std::shared_ptr<SkidSteerModel>(&ChassisModel),
        std::unique_ptr<AsyncPosIntegratedController>(&leftController),
        std::unique_ptr<AsyncPosIntegratedController>(&rightController),
        AbstractMotor::gearset::blue, drivenWheelScales);

    AsyncMotionProfileController profileController(
        chassisUtil, {1.05, 1.5, 5.0}, std::shared_ptr<SkidSteerModel>(&ChassisModel), drivenWheelScales, GearsetRatioPair
        //AsyncControllerFactory::motionProfile(
        //     // 1.05, // Maximum linear velocity of the Chassis in m/s
        //     // 1.5, // Maximum linear acceleration of the Chassis in m/s/s
        //     // 5.0, // Maximum linear jerk of the Chassis in m/s/s/s
        //     1,
        //     2,
        //     10.0,
        // Chassis Controller
    );

    void update()
    {
        // currState = notRunning;
        if (abs(controller.getAnalog(ControllerAnalog::leftY)) > joyDeadband ||
            abs(controller.getAnalog(ControllerAnalog::rightY)) > joyDeadband)
        {
            currState = running; // begin running drive once small threshold on joystick is reached
        }
        // currState = autoAim;
    }

    void act(void *)
    {

        // pros::delay(500);
        // vision::vis.set_exposure(150);

        while (true)
        {
            // largestObjX = visionFilter.filter(vision::reader.get(0).x);

            // pros::lcd::print(0, "%f", drive::driveL1.getPosition());
            // pros::lcd::print(1, "%c", drive::currState);
            // printf("x: %i\n", largestObjX);

            switch (currState)
            {
            case notRunning: // the drive should not be moving; brake
                ChassisModel.setBrakeMode(AbstractMotor::brakeMode::coast);
                chassisController.stop();
                break;

            case running: // the drive moves according to joysticks
                ChassisModel.tank(
                    controller.getAnalog(ControllerAnalog::leftY) * 1.0,
                    controller.getAnalog(ControllerAnalog::rightY) * 1.0,
                    joyDeadband * 1.0);
                currState = notRunning;
                break;

            case yield: // for macro in order to take direct control of drive
                break;
            }
            pros::delay(10);
        }
    }

    // Helper function to facilitate turning during auton
} // namespace drive

// Remove path to clear up memory
void removePaths(std::string path1)
{
    drive::profileController.removePath(path1);
}

// Remove 2 paths at once to clear up memory
void removePaths(std::string path1, std::string path2)
{
    drive::profileController.removePath(path1);
    drive::profileController.removePath(path2);
}