class Motor{
public:
  Motor(int number):  motor(number), currentSpeed(0){}
    /* Removes the need to set "run" as Forward and Backward */
  void setSpeed(int speed){
    currentSpeed = speed;
    if (speed >= 0) {
      motor.setSpeed(speed);
      motor.run(FORWARD);
    }
    else {
      motor.setSpeed(-speed);
      motor.run(BACKWARD);
    }
  }

  int getSpeed() const{ return currentSpeed; }
        
private:
    AF_DCMotor motor;
    int currentSpeed;
};
