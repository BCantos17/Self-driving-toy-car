// constants
const int runTime = 30;
const int close = 10;

#include <SoftwareSerial.h>
/* Set the pins for the bluetooth slave */
SoftwareSerial bluetooth(16, 17);
/* Downloaded from http://playground.arduino.cc/Code/NewPing */
#include <NewPing.h> 
/* Downloaded from https://github.com/adafruit/Adafruit-Motor-Shield-library */
#include <AFMotor.h>
#include "Motor.h"
#include "BluetoothControl.h"

class Car{
public:
  /* Setting the pins for the left, right, distance sensor( Trig and Echo) and the maximum distance */
  Car()
    : left( 1 ), right( 3 ), sensor( 14, 15, 200 ){
        setCar();
  }
  
  void setCar(){
    remote();
  }
  
  /* The car starts in the remote control phase and if the grab button is release, goes to auto drive */
  void start(){
    long time = millis();
    int distance = 0;

    // Not all signals are returned and thus a 0 value is given which confuses the vehicle, so if the sensor gets a 0, assume no signal was bounced back
    if (sensor.ping_cm() <= 0)
      distance = 200;
    else
      distance = sensor.ping_cm();
    Signal BTSignal;
    bool haveBTSignal = blueStick.getSignal(BTSignal);  // Get signal from bluetooth

    /* If mode is in control mode, set motor speed base on signal inputs */
    if ( mode == control ) {
      if ( haveBTSignal ) {
        if ( BTSignal.selfDrive == true )
            move();
        else {
          left.setSpeed(BTSignal.left);
          right.setSpeed(BTSignal.right);
        }
      }
    }

    /* Self driving vehicle */
    else {
      /* Set back to control mode */
      if (haveBTSignal && BTSignal.selfDrive == true){
        remote();
        BTSignal.selfDrive = false;
      }
      /* statments for the vehicle to move on its own */
      else {
        if ( mode == stopped )
          return;

        else if ( mode == moving ) 
          if ( distance <= close )
            turn(time);

        else if ( mode == turning )
          if (finishTurning(time, distance))
           move();
      }
    }
  }

  protected:

    void remote(){
      left.setSpeed(0);
      right.setSpeed(0);
      mode = control;
    }
    /* Move forward on by itself */
    void move(){
      left.setSpeed(255);
      right.setSpeed(255);
      mode = moving;
    }

    void stop(){
      left.setSpeed(0);
      right.setSpeed(0);
      mode = stopped;
  }
  
  bool turn(unsigned long time){
    /* Base on Random values, turn left or right when sensor picks up something too close */
    if (random(2) == 0) {
      left.setSpeed(-255);
      right.setSpeed(255);
    }
    else {
      left.setSpeed(255);
      right.setSpeed(-255);
    }
    mode = turning;
    endmodeTime = time + random(500, 1000);
  }
        
  bool finishTurning(unsigned long time, unsigned int distance){
    if (time >= endmodeTime)
      return (distance > close);
  return false;
  }

private:
  Motor left;
  Motor right;
  NewPing sensor;
  enum carMode { stopped, moving, turning, control };
  carMode mode;
  unsigned long endmodeTime;
  BluetoothControl blueStick;
};

Car myCar;
void setup(){
    Serial.begin(9600);
    bluetooth.begin(9600);
}

void loop(){
    myCar.start();
}
