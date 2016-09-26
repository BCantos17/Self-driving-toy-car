/*
 * Changes the speed of the motors based on the signals recieved from the bluetooth
 */

struct Signal {
    int left;   
    int right;  
    bool selfDrive;
            
    Signal() : left(0), right(0), selfDrive(false) {}
    void goForward(){
      left = 255;
      right = 255;
    }
    
    void goBack(){
      left = -255;
      right = -255;
    }
    
    void turnLeft(){
        left = -255;
        right = 255;
    }
    
    void turnRight(){
      left = 255;
      right = -255;
    }
    
    void stop(){
      left = 0;
      right = 0;
    }
};
