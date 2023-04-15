//
// Created by Jorge Enriquez on 3/17/23.
// Updated by Renzo Pereyra on 04/14/23.
//

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your motors and other devices here
// controller configuration
controller Controller1 = controller(primary);
// motor configurations
// motor(port#, cartridge, reverse true or false)
// blue motor ratio6_1, red motor ratio36_1, green motor ratio18_1
motor LeftFront = motor(PORT1, ratio6_1, false);
motor LeftRear = motor(PORT2, ratio36_1, false);
motor RightFront = motor(PORT3, ratio18_1, true);
motor RightRear = motor(PORT4, ratio18_1, true);
motor arm = motor(PORT5, ratio18_1, true);
float WheelCircumference = (4.0 * 3.14159265); //Diameter of wheel * Pi
float RevToAngle = (1/93); // 1 revolution turns 93 degrees
int TurningSpeed = 45;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

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
void goFwd(float distance, int speed){
    float MotorDegrees = (distance /WheelCircumference)* 360;
    leftFront.spin(fwd,MotorDegrees,deg,speed,pct,false);
    leftRear.spin(fwd,MotorDegrees,deg,speed,pct,false);
    rightFront.spin(fwd,MotorDegrees,deg,speed,pct,false);
    rightRear.spin(fwd,MotorDegrees,deg,speed,pct);
}
void goBack(float distance, int speed){
    float MotorDegrees = (distance /WheelCircumference)* 360;
    leftFront.spin(rev,MotorDegrees,deg,speed,pct,false);
    leftRear.spin(rev,MotorDegrees,deg,speed,pct,false);
    rightFront.spin(rev,MotorDegrees,deg,speed,pct,false);
    rightRear.spin(rev,MotorDegrees,deg,speed,pct);
}
void turnLeft(float degrees){
    //turn MotorDegrees into RobotDegrees by testing
    float NumberOfDegrees = degrees * RevToAngle * 360;
    leftFront.spin(rev,NumberOfDegrees,def,TurningSpeed,pct, false);
    leftRear.spin(rev,NumberOfDegrees,def,TurningSpeed,pct, false);
    rightFront.spin(fwd,NumberOfDegrees,def,TurningSpeed,pct, false);
    rightRear.spin(fwd,NumberOfDegrees,def,TurningSpeed,pct);
}
void turnRight(float degrees){
    //turn MotorDegrees into RobotDegrees by testing
    float NumberOfDegrees = degrees * RevToAngle * 360;
    leftFront.spin(fwd,NumberOfDegrees,def,TurningSpeed,pct, false);
    leftRear.spin(fwd,NumberOfDegrees,def,TurningSpeed,pct, false);
    rightFront.spin(rev,NumberOfDegrees,def,TurningSpeed,pct, false);
    rightRear.spin(rev,NumberOfDegrees,def,TurningSpeed,pct);
}

void autonomous(void) {
    //int counter = 1;
    //int power = 11200;

    //robot1.fly1.move_voltage(power);
    goBack(10,50); //Go back 10 inches at a speed of 50

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

void usercontrol(void) {
    // User control code here, inside the loop
    while (1) {
        //To move the drivetrain in tank mode
        /*
        LeftRear.spin(fwd, Controller1.Axis3.value(),velocityUnits::pct);
        LeftFront.spin(fwd, Controller1.Axis3.value(), velocityUnits::pct);
        RightRear.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
        RightFront.spin(fwd, Controller1.Axis2.value(), velocityUnits::pct);
        */

        //To move robot is arcade control
        LeftRear.spin(fwd, Controller1.Axis3.value()+Controller1.Axis1.value(),velocityUnits::pct);
        LeftFront.spin(fwd, Controller1.Axis3.value()+Controller1.Axis1.value(), velocityUnits::pct);
        RightRear.spin(fwd, Controller1.Axis3.value()-Controller1.Axis1.value(), velocityUnits::pct);
        RightFront.spin(fwd, Controller1.Axis3.value()-Controller1.Axis1.value(), velocityUnits::pct);


        /*
        //To move a motor using a button
        if(Controller1.ButtonLeft.pressing()){
            arm.spin(fwd, 100,velocityUnits::pct);
        }else if(Controller1.ButtonRight.pressing()){
            arm.spin(reverse, 100,velocityUnits::pct);
        }else{
            arm.spin(reverse, 0,velocityUnits::pct);
            arm.setBrake(brake);
        }
        */

        wait(20, msec); // Sleep the task for a short amount of time to
        // prevent wasted resources.
    }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
    // Set up callbacks for autonomous and driver control periods.
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);

    // Run the pre-autonomous function.
    pre_auton();

    // Prevent main from exiting with an infinite loop.
    while (true) {
        wait(100, msec);
    }
}