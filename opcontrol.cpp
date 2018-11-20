#include "main.h"
#define RQUAD_TOP_PORT 1
#define RQUAD_BOTTOM_PORT 2
#define LQUAD_TOP_PORT 3
#define LQUAD_BOTTOM_PORT 5

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void move(int speed){
 	pros::ADIMotor mtr('A');
 	mtr.set_value(speed);
 	pros::ADIMotor mtr1('A');
 	mtr1.set_value(speed);

 }
 int inchToTicks (float inch)
 	{
 		int ticks;
 		ticks = inch*99.82198;
 		return ticks;
 	}
 void pidControl(float target){
 	float kp=0.2;
 	float ki=0.05;
 	float kd=0.5;
 	int error;
 	int proportion;
 	int finalpower;
	int derivative;
	int lastError=0;
	int integral =0;
	int integralPower;

 	pros::ADIEncoder Rightencoder (RQUAD_TOP_PORT, RQUAD_BOTTOM_PORT, false);
 	pros::ADIEncoder Leftencoder (LQUAD_TOP_PORT,LQUAD_BOTTOM_PORT, false);
 	Rightencoder.reset();
 	Leftencoder.reset();
 	error = inchToTicks(target)-(Rightencoder.get_value()+Leftencoder.get_value());

	while(true){
 		error = inchToTicks(target)-(Rightencoder.get_value()+Leftencoder.get_value());
 		proportion=kp*error;
		derivative = kd*(error-lastError);
		lastError = error;
		if (error == 0)
		{
			derivative = 0;
		}

		integral+=error;
		integralPower=integral*ki;

 		finalpower = proportion + derivative + integralPower;
 		move(finalpower);
		pros::delay(25);

	}
}
void opcontrol() {
		 pidControl(12);

		 while (true) {
				 pros::delay(20);
		 }
}
