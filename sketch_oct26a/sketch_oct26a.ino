//Line Sensors
#define rightSensor 14
#define midSensor 15
#define leftSensor 16

 //HBridgeL          //dont use these unless with an hbridge
#define LAnalog 10
#define LIn1 7
#define LIn2 8

// HBridgeR     //dont use these unless with an hbridge
#define RAnalog 9
#define RIn3 5
#define RIn4 6

//LEDs
#define ledRed 12 
#define ledGreen 3
#define ledBlue 4


//Sensor Variables
int vLeftSensor;
int vRightSensor;
int vMidSensor;

// Left Motor
int L1;    //defines motion as forward
int L2;
int maxSpeedL = 252;     //adjust the speed of the wheels to match eatch other
int midSpeedL;
int speedL;
int straightL = 255;    //170

// Right Motor
int R1;   //defines motion as forward
int R2;
int maxSpeedR = 178;  //adjust the speed of the wheels to match each other
int midSpeedR;
int speedR;
int straightR = 255;  //216

int motorState1= HIGH;
int motorState0 = LOW;
int ledState0 = LOW;
int ledState1 = HIGH;

//Time Variables
int currentMillis;
int previousMillis = 0;
int delayTime = 0;

//Zeroing Variables
int nSamples = 300;
int zeroM = 0;
int zeroL = 0;
int zeroR = 0;

//PID Variables
float p = .4; //.15
float i = 0; //.15; //-.15;
float d = 0; //.2;  //.15

//Error Variables
int pErrorL = 0;
int pErrorR = 0;
int pErrorMid = 0;

unsigned long iErrorL = 0;
unsigned long iErrorR = 0;

int dErrorL = 0;
int dErrorR = 0;

int pastErrorL = 0;
int pastErrorR = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(rightSensor, INPUT);
pinMode(midSensor, INPUT);
pinMode(leftSensor, INPUT);
pinMode (ledRed, OUTPUT);
pinMode (ledGreen, OUTPUT);
pinMode (ledBlue, OUTPUT);
// Left Motor
  pinMode(LAnalog, OUTPUT);
  pinMode(LIn1, OUTPUT);
  pinMode(LIn2, OUTPUT);

  // Right Motor
  pinMode(RAnalog, OUTPUT);
  pinMode(RIn3, OUTPUT);
  pinMode(RIn4, OUTPUT);
Serial.begin(9600);

// zero
  for (int k = 0; k < 1; k++)
  {
    zeroM += analogRead(midSensor);
    zeroL += analogRead(leftSensor);
    zeroR += analogRead(rightSensor);
    
   
  }
 // zeroM = zeroM/nSamples;
  //zeroL = zeroL/nSamples;
  //zeroR = zeroR/nSamples;
}



void loop() {
  pastErrorL = vLeftSensor;
  pastErrorR = vRightSensor;
  // put your main code here, to run repeatedly:
  
  currentMillis = millis();  //update time

  if (currentMillis - delayTime >= previousMillis){
    previousMillis = currentMillis;      //update sensor values after delayTime
  
  vRightSensor= analogRead(rightSensor);
  vMidSensor= analogRead(midSensor);
  vLeftSensor = analogRead(leftSensor);
  }

 if (vLeftSensor < 600 && vRightSensor < 600){
   motorState1 = LOW;
   analogWrite(LAnalog, 0);
   analogWrite(RAnalog, 0);
   ledState0 = HIGH;
 }

  pErrorL = zeroL - vLeftSensor;
  pErrorR = zeroR - vRightSensor;
  pErrorMid = zeroM - vMidSensor;
  
  //iErrorL += pErrorL;
  //iErrorR += pErrorR;

  dErrorL = (vLeftSensor - pastErrorL)/delayTime;
  dErrorR = (vRightSensor - pastErrorR)/delayTime;

  speedL = straightL - (p*pErrorL) - (i*iErrorL) - (d*dErrorL);
  speedR = straightR - (p*pErrorR) - (i*iErrorR) - (d*dErrorR);

  //Serial.println(zeroL);
  //Serial.println(zeroR);
  //Serial.println("\n");
  Serial.println(speedL);
  Serial.println(speedR);
  //Serial.println(vMidSensor);
  Serial.println("");
  speedL = constrain(speedL,0,255);
  speedR = constrain(speedR,0,255);
  //analogWrite to motors depending on sensor values
 // Left Motor
  analogWrite(LAnalog, speedL);      //93 for now
  digitalWrite(LIn1, motorState1);   //May need to adjust the high low depending on configuration
  digitalWrite(LIn2, motorState0);

  // Right Motor
  analogWrite(RAnalog, speedR);   //100 for now
  digitalWrite(RIn3, motorState1);   //May need to adjust the high low depending on configuration
  digitalWrite(RIn4, motorState0);

  if((speedL) > speedR){
    digitalWrite(ledBlue, ledState1);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, ledState0);
  }

  if((speedL) < speedR){
    digitalWrite(ledRed, ledState1);
    digitalWrite(ledGreen,LOW);
    digitalWrite(ledBlue,ledState0);
  }
  if((speedL) == speedR){
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledBlue, LOW);
  }
}
