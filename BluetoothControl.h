#include "Signal.h"

class BluetoothControl{
public:
  BluetoothControl() : lastButton(false){}

  bool getSignal(Signal& button){
    button.stop();
    button.selfDrive = false;
            
    if (bluetooth.available() <= 0)
      return false;
      
    char ch = bluetooth.read();

    /* Calls functions in Signal.h base on the values read from the bluetooth */
    if( ch == '8' )
      button.goForward();
              
    else if( ch == '2' )
      button.goBack();
              
    else if ( ch == '4' )
      button.turnLeft();

    else if ( ch == '6' )
      button.turnRight();
              
    else if ( ch == 'C' )
      button.selfDrive = true;

    if (button.selfDrive != false && button.selfDrive == lastButton) 
      return false; 

    lastButton = button.selfDrive;
    return true;
  }
    
private:
  bool lastButton;
};
