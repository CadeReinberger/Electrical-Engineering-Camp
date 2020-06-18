/////////////////////////////////////////////////////////////
///////////////   PROGRAM CONSTANTS ////////////////////////
///////////////////////////////////////////////////////////

/* START OF REGION OF CONSTANTS YOU SHOULD EDIT */

const double speedFactor = .65; //A multiplier between 0 and 1 indicating how fast the robot should go

//If true the robot will run code to fix that one wheel is faster than the other.
const bool isWheelImbalance = true; 

//If isWheelImbalance is false these next two constants won't matter. 
//If the robot going straight veers left, the right wheel is faster and this is true. If it veers right, this is false
const bool isRightWheelFaster = false;
//Should always be at least one. Roughly how many times faster the faster wheel is than the slower one. You can guess and check to tune this. 
const double fasterWheelSpeedRatio = 1.3; 

/* END OF REGION OF CONSTANTS YOU SHOULD EDIT */

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;           //speed control pin on the motor driver for the left motor
const int BIN2 = 9;           //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;           //control pin 1 on the motor driver for the left motor

const int switchPin = 7;             //switch to turn the robot on and off

//defined later, but these are the globabl absolute speeds of the wheels. 
int leftSpeed, rightSpeed;


/////////////////////////////////////////////////////////////
///////////////   SETUP AND LOOP ///////////////////////////
///////////////////////////////////////////////////////////


void setup() {
  //configure the switch pin
  pinMode(switchPin, INPUT_PULLUP);

  //configure the right motor
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  //configure the right motor
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //these constants use the speed factor and speed imbalance constants to compute the size of the power to each motor.
  //You don't have to worry about this math and logic. 
  
  double bigger = 255 * speedFactor;
  double smaller = bigger / fasterWheelSpeedRatio;
  if (isWheelImbalance){
    leftSpeed = isRightWheelFaster ? (int) bigger : (int) smaller;
    rightSpeed = isRightWheelFaster ? (int) smaller : (int) bigger;
  } else {
    leftSpeed = (int) bigger;
    rightSpeed = (int) bigger;
  }
}

void loop() {
  
  /* THIS IS WHERE YOU PUT YOUR CODE TO PROGRAM THE ROBOT's ACTION */

  driveForward(1.5);
  turnLeft(2);
  driveBackward(1.5);
  turnRight(3);
  driveForward(1);
  
  /* END OF WHERE YOU PUT YOUR CODE TO PROGRAM THE ROBOT's ACTION */

  //this line is just to stop the program from repeating once it's run once. 
  while (true) {}
}


/////////////////////////////////////////////////////////////
///////////////   SWITCH READING FUNCTION  /////////////////
///////////////////////////////////////////////////////////


bool getSwitchOn(){
  return (digitalRead(switchPin) == LOW);
}


/////////////////////////////////////////////////////////////
///////////////   MOTOR RUNNING FUNCTIONS  /////////////////
///////////////////////////////////////////////////////////

//function for driving the right motor
void rightMotor(int motorSpeed){                       
  if (motorSpeed > 0){                                //if the motor should drive forward (positive speed)
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  } else if (motorSpeed < 0){                         //if the motor should drive backward (negative speed)
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  } else {                                            //if the motor should stop
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

//function for driving the left motor
void leftMotor(int motorSpeed){
  if (motorSpeed > 0){                                //if the motor should drive forward (positive speed)
    digitalWrite(BIN1, HIGH);                         //set pin 1 to high
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  } else if (motorSpeed < 0){                         //if the motor should drive backward (negative speed)
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, HIGH);                         //set pin 2 to high
  } else {                                             //if the motor should stop
    digitalWrite(BIN1, LOW);                          //set pin 1 to low
    digitalWrite(BIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}

//function to write to left and right at the same time
void leftRightCommand(int leftSpd, int rightSpd){
  leftMotor(leftSpd);
  rightMotor(rightSpd);
}


/////////////////////////////////////////////////////////////
///////////////   DRIVING FUNCTIONS   //////////////////////
///////////////////////////////////////////////////////////


void stopMoving(){
  leftRightCommand(0, 0);
}

void driveForward(double timeInSeconds){
  int startTime = millis();
  int maxTime = (int) (1000 * timeInSeconds);
  bool isFirstCycle = true;
  while ( (millis() - startTime <= maxTime) && getSwitchOn()){
    if (isFirstCycle){
      leftRightCommand(leftSpeed, rightSpeed);
      isFirstCycle = false;
    }
  }
  stopMoving();
}

void driveBackward(double timeInSeconds){
  int startTime = millis();
  int maxTime = (int) (1000 * timeInSeconds);
  bool isFirstCycle = true;
  while ( (millis() - startTime <= maxTime) && getSwitchOn()){
    if (isFirstCycle){
      leftRightCommand(-leftSpeed, -rightSpeed);
      isFirstCycle = false;
    }
  }
  stopMoving();
}

void turnLeft(double timeInSeconds){
  int startTime = millis();
  int maxTime = (int) (1000 * timeInSeconds);
  bool isFirstCycle = true;
  while ( (millis() - startTime <= maxTime) && getSwitchOn()){
    if (isFirstCycle){
      leftRightCommand(-leftSpeed, rightSpeed);
      isFirstCycle = false;
    }
  }
  stopMoving();
}

void turnRight(double timeInSeconds){
  int startTime = millis();
  int maxTime = (int) (1000 * timeInSeconds);
  bool isFirstCycle = true;
  while ( (millis() - startTime <= maxTime) && getSwitchOn()){
    if (isFirstCycle){
      leftRightCommand(leftSpeed, -rightSpeed);
      isFirstCycle = false;
    }
  }
  stopMoving();
}
