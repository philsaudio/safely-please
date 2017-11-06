//These are the global variables. You must have these!!

int IN1=2;  //Input to control Motor A
int IN2=3;  //Input to control Motor A
int IN3=4;  //Input to control Motor B
int IN4=7;  //Input to control Motor B
int ENA=5;  //Input to enable Motor A
int ENB=6;  //Input to enable Motor B

int trig = 9;  //This group is the input for the ultrasonic sensor.
int echo = 8;
int inter_time = 1000;
float duration, distance;

//Below are a series of call-by functions to move the car forward, backward, turn left and turn right.

//The following code block is to stop the motor.  This is to reset the motor so that it works each time we command a new function.
void stopMotor(boolean r){
  if (r){ 
    analogWrite(ENA,0);
    analogWrite(ENB,0);
  }
  else{
    analogWrite(ENA,255);
    analogWrite(ENB,255);
  }
}

//This code block means the car will move backwards for 1000ms (or 1 second)

void moveBackward(){
  digitalWrite(IN3,HIGH);  //HIGH means that input is on.
  digitalWrite(IN4,LOW);   //LOW means that input is off.
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  delay(1000);    
  }

//This code block means the car will move forwards for 1000ms (or 1 second)

void moveForward(){
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,HIGH); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(1000);
  }

//This will turn the car right.

void turnRight(){
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW); 
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(1000);
  }

//this will turn the car left.

void turnLeft(){
  digitalWrite(IN3,HIGH);  
  digitalWrite(IN4,LOW); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(1000);
  }

//Ultrasonic Sensor
int Distance(){
  digitalWrite(trig, HIGH);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH); //Ultrasonic function to detect the echo from sending the sound out and reciving the echo back in. Like a dolphin or submarine.
  distance = (duration/2)/29; //the following is used to turn the data into distances.
  Serial.print("d = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);  
  return distance;
  }


//This block is used to setup the arduino so that it knows which pins do what function.
void setup(){
  
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);

  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
    
  Serial.begin(9600);
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
}

//How to write a call-by function for moving forward a certain distance.

void moveOnemeter(){ //the function is called 'moveOnemeter'
 stopMotor(false);
 moveForward();
 delay(4500);           //this is the time the car will move forward for, 
                        //you need to calculate this.
 Serial.println("ONE"); //use this to ensure that the ultrasonic sensor is activated
}


void loop(){
  
  //Ultrasonic sensor - If the distance is more than 40cm the stopMotor 
  //function is not triggered and we then use the call-by function to move
  //the car foward.
  if(Distance()>=40){
    stopMotor(false);
    moveForward();      
    }
  else if(Distance()<50){
    Serial.println("STOP");
    stopMotor(true);
    delay(20);
    
    stopMotor(false);
    Serial.println("BACK");
    moveBackward();
    delay(20);
    stopMotor(true);

    stopMotor(false);
    Serial.println("RIGHT");
    turnRight();
    delay(20);
    stopMotor(true);
  }

//  If we just place moveOnemeter() only, then it'll make keep forward, 
//  because loop(). That's why we need to add stopMotor & delay
//  void loop(){
//  moveOnemeter();
//  stopMotor(true);
//  delay(100000000);  

}



