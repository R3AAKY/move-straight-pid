#include "base.h"


// +ve degrees clockwise turn
// -ve counter clockwise
int inchToTicks (float inch)
 	{
 		int ticks;
 		ticks = inch*99.82198;
 		return ticks;
 	}

void turn(int targetDegrees){

}

void moveStraight(float inches){
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
  error = inchToTicks(inches)-(rightEnc.get_value()+leftEnc.get_value());

	while(true){
 		error = inchToTicks(inches)-(rightEnc.get_value()+leftEnc.get_value());
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
 		rightMotor.set_value(finalpower);
    leftMotor.set_value(finalpower);
		pros::delay(25);
}

}
