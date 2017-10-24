//to use this library, put it in the same folder as your main program, and add the line
//#include "library.c"
//at the start of your file. Do not attempt to compile this code as robotC code, as there is no main method.

//formula that models 2 button control scheme.
//input the name of the 2 buttons
//output is -1 if only control2 is pressed
//output is 1 if only control1 is pressed
//output is 0 if both or neither are pressed
//use this method to have a motor going in 2 directions chosen by 2 buttons
//Ex: motor[arm] = 127*between(Btn5U, Btn5D);
int between(int control1, int control2){
    if(vexRT[control1] ^ vexRT[control2]){
        return vexRT[control1] ? 1 : -1;
    }
    return 0;
}

//models tank movement with both joysticks moving four motors
//input the motors by name
void tankBase(int frontLeft, int backLeft, int frontRight, int backRight){
    motor[frontLeft] = vexRT[Ch3];
    motor[frontRight] = vexRT[Ch2];
    motor[backLeft] = vexRT[Ch3];
    motor[backRight] = vexRT[Ch2];
}

//models a proportional controller for a motor with a potentiometer
//input the motor name, potentiometer name, the target value of the potentiometer, and a constant for the rate of change
//this works well for arms that normally fall with their own weight, you can have your controller change the target instead of the motor speed
//it is suggested to not run this method on a while loop without a wait1Msec(_) included in the loop. Loops go very very fast if left to run. Motors cannot update faster than 20ms anyway.
//ensure that the target is within the range of motion of the motor and within the 0-4096 range of the potentiometer sensor
//if the motor is going in the opposite direction of the target, flip the sign of amount
void proportionalMotion(int mtr, int potentiometer, int target, int amount){
    int error = target - SensorValue[potentiometer];
    motor[mtr] = amount*error;
}
