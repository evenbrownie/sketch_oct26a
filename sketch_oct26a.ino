//Line Sensors
#define rightSensor 14
#define midSensor 15
#define leftSensor 16

// HBridgeL          //dont use these unless with an hbridge
//#define LAnalog 10
//#define LIn1 7
//#define LIn2 8

// HBridgeR     //dont use these unless with an hbridge
//#define RAnalog 9
//#define RIn3 5
//#define RIn4 6

//LEDs
#define ledRed 12 
#define ledGreen 3
#define ledBlue 4


//Sensor Variables
int vLeftSensor;
int vRightSensor;
int vMidSensor;

// Left Motor
int L1 = HIGH;   //defines motion as forward
int L2 = LOW;
int maxSpeedL = 252;     //adjust the speed of the wheels to match eatch other
int midSpeedL;
int SpeedL;

// Right Motor
int R1 = HIGH;    //defines motion as forward
int R2 = LOW;
int maxSpeedR = 255;  //adjust the speed of the wheels to match each other
int midSpeedR;
int SpeedR;

//Time Variables
int currentMillis;
int previousMillis = 0;
int delayTime = 25;

//Zeroing Variables
int nSamples = 100;
int zeroM = 0;
int zeroL = 0;
int zeroR = 0;

//PID Variables
float p;
float i;
float d; 

//Error Variables
int pErrorL = 0;
int pErrorR = 0;
int pErrorMid = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(rightSensor, INPUT);
pinMode(midSensor, INPUT);
pinMode(leftSensor, INPUT);
pinMode (ledRed, OUTPUT);
pinMode (ledGreen, OUTPUT);
pinMode (ledBlue, OUTPUT);
Serial.begin(9600);

// zero
  for (int k = 0; k < nSamples; k++)
  {
    zeroM += analogRead(midSensor);
    zeroL += analogRead(leftSensor);
    zeroR += analogRead(rightSensor);
    delay(7);
  }
  zeroM /= nSamples;
  zeroL /= nSamples;
  zeroR /= nSamples;
}



void loop() {
  
  // put your main code here, to run repeatedly:
  
  currentMillis = millis();  //update time

  if (currentMillis - delayTime >= previousMillis){
    previousMillis = currentMillis;      //update sensor values after delayTime
  
  vRightSensor= analogRead(rightSensor);
  vMidSensor= analogRead(midSensor);
  vLeftSensor = analogRead(leftSensor);
  }
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledBlue, HIGH);
  digitalWrite(ledGreen, HIGH);
Serial.println(vRightSensor);
  //if(maxSpeedL > maxSpeedR){
    //digitalWrite(ledBlue, HIGH);
  //}

  //if(maxSpeedL < maxSpeedR){
    //digitalWrite(ledRed, HIGH);
  //}

  //if(
  
  
  //analogWrite to motors depending on sensor values
 // Left Motor
  //analogWrite(LAnalog, maxSpeedL);
  //digitalWrite(LIn1, HIGH);   //May need to adjust the high low depending on configuration
  //digitalWrite(LIn2, LOW);

  // Right Motor
  //analogWrite(RAnalog, maxSpeedR);
  //digitalWrite(RIn3, HIGH);   //May need to adjust the high low depending on configuration
  //digitalWrite(RIn4, LOW);
}
