int IN1=2;
int IN2=3;
int IN3=4;
int IN4=7;
int ENA=5;
int ENB=6;

int trig = 9;
int echo = 8;
int inter_time = 1000;
float duration, distance;

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

void moveBackward(){
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  delay(1000);    
  }

void moveFoward(){
  digitalWrite(IN3,LOW);  
  digitalWrite(IN4,HIGH); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  delay(1000);
  
  }
void trunRight(){
  digitalWrite(IN1,HIGH);  
  digitalWrite(IN2,LOW); 
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(1000);
    
  
  }

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
//  delayMicroseconds(10000);
  digitalWrite(trig, LOW);
  duration = pulseIn (echo, HIGH);
  distance = (duration/2)/29; 
  Serial.print("d = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);  
  return distance;
  }

void detect(){
//  myservo.write(35);
  delay(100);
  if(Distance()>50){
    Serial.println("RIGHT");
    trunRight();    
//    myservo.write(85);
    }
  else if(Distance()<50){
//    myservo.write(135);
    delay(100);
      if(Distance()>50){
        Serial.println("LEFT");
        turnLeft(); 
//        myservo.write(85);
      }
      else{
        moveBackward();
//        myservo.write(85);
        }
    }
  

  }

void setup(){
//  myservo.attach(10);
  
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


void loop(){
  
  //Ultrasonic
  if(Distance()>=40){
    stopMotor(false);
    moveFoward();      
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

    Serial.println("DETECT");
    stopMotor(false);
    detect();
    delay(20);
    stopMotor(true);
  }

}

