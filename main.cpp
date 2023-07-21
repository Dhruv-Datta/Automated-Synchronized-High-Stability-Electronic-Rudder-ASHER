#include <Arduino.h>
#include <Servo.h>

Servo rudder;

double pos = 140;

double PID_error = 0;
double _pre_error = 0;
double _integral = 0;
double output;


double error[9] = {-4, -3, -2, 4, 1, 2, 3, 4};


class PIDSys {
  public:
    PIDSys(double dt, double maxpos, double minpos, double maxout, double minout, double Kp, double Ki, double Kd);
    double _dt;
    double _maxpos;
    double _minpos;
    double _maxout;
    double _minout;
    double _Kp;
    double _Ki;
    double _Kd;
};


PIDSys::PIDSys(double dt, double maxpos, double minpos, double maxout, double minout, double Kp, double Ki, double Kd):
  _dt(dt),
  _maxpos(maxpos),
  _minpos(minpos),
  _maxout(maxout),
  _minout(minout),
  _Kp(Kp),
  _Ki(Ki),
  _Kd(Kd)
  {
  }


PIDSys myPID(0.01, 110, 0, 0.5, -0.5, 3, 1, 0);


void setup() {
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  rudder.attach(12);

  Serial.begin(9600);
}

void loop() {
  int Sensor2Value = digitalRead(4);
  int Sensor6Value = digitalRead(5);
  int Sensor7Value = digitalRead(6);
  int Sensor3Value = digitalRead(7);
  int Sensor5Value = digitalRead(8);
  int Sensor4Value = digitalRead(9);
  int Sensor8Value = digitalRead(10);
  int Sensor1Value = digitalRead(11);


  if (Sensor1Value == 0) {
    PID_error = error[0];
  } else if (Sensor2Value == 0) {
    PID_error = error[1];
  } else if (Sensor3Value == 0) {
    PID_error = error[2];
  } else if (Sensor4Value == 0) {
    PID_error = error[3];
  } else if (Sensor5Value == 0) {
    PID_error = error[4];
  } else if (Sensor6Value == 0) {
    PID_error = error[5];
  } else if (Sensor7Value == 0) {
    PID_error = error[6];
  } else if (Sensor8Value == 0) {
    PID_error = error[7];
  }

  double Pout = myPID._Kp * PID_error;

  _integral = _integral + PID_error * myPID._dt;
  double Iout = myPID._Ki * _integral;

  double derivative = (PID_error - _pre_error) / myPID._dt;
  double Dout = myPID._Kd * derivative;
 
  double output = Pout + Iout + Dout;
 
  _pre_error = PID_error;


  if( output > myPID._maxout )
    output = myPID._maxout;
  else if( output < myPID._minout )
    output = myPID._minout;
 
  if( Iout > myPID._maxout )
    Iout = myPID._maxout;
  else if( output < myPID._minout )
    Iout = myPID._minout;


  pos += output;

  if( pos > myPID._maxpos )
    pos = myPID._maxpos;
  else if( pos < myPID._minpos )
    pos = myPID._minpos;


  rudder.write(pos);

  Serial.println(pos);


  delay(10);

}
