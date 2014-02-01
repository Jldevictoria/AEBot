//  ---------  Angry Engineers Robot - Winter 2013  ---------
//  --  Brendan Huber, Joseph DeVictoria, Scott Heidbrink  --
//  -  This robot will use an  ultrasonic sensor to locate  -
//  -  a 1 sq. ft. target, and launch a missile to hit it.  -
//  -   Made for angry engineers competition Feb 19, 2014   -
//  ---------------------------------------------------------

#include <Servo.h>
#include <math.h>

Servo horizontal;
Servo vertical;

// Pin Global Variables.
int echoPin = 2;
int trigPin = 4;
int firePin = 8;
int vServoPin = 17;
int hServoPin = 19;

// Scanning Variables.
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  Serial.begin(9600);
  // This is where we set up the transmit type for each pin:
  // pinMode(0, INPUT/OUTPUT); //Digital Pin / Touch / RX1
  // pinMode(1, INPUT/OUTPUT); //Digital Pin / Touch / RX1
  pinMode(echoPin, INPUT); //Digital Pin / CS
  // pinMode(3, INPUT/OUTPUT); //Digital Pin / PWM
  pinMode(trigPin, OUTPUT); //Digital Pin / PWM
  // pinMode(5, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(6, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(7, INPUT/OUTPUT); //Digital Pin / DOUT / RX3
  pinMode(firePin, OUTPUT); //Digital Pin / DIN / TX3
  // pinMode(9, INPUT/OUTPUT); //Digital Pin / PWM / RX2
  // pinMode(10, INPUT/OUTPUT); //Digital Pin / PWM / CS / TX2
  // pinMode(11, INPUT/OUTPUT); //Digital Pin / DOUT 
  // pinMode(12, INPUT/OUTPUT); //Digital Pin / DIN
  // pinMode(13, INPUT/OUTPUT); //Digital Pin / LED / SCK
  // pinMode(14/A0, INPUT/OUTPUT); //Digital Pin / Analog Pin (A0) / SCK
  // pinMode(15/A1, INPUT/OUTPUT); //Digital Pin / Analog Pin (A1) / Touch
  // pinMode(16/A2, INPUT/OUTPUT); //Digital Pin / Analog Pin (A2) / SCL0 / Touch
  // pinMode(17/A3, INPUT/OUTPUT); //Digital Pin / Analog Pin (A3) / SDA0 / Touch
  // pinMode(18/A4, INPUT/OUTPUT); //Digital Pin / Analog Pin (A4) / SDA0 / Touch
  // pinMode(19/A5, INPUT/OUTPUT); //Digital Pin / Analog Pin (A5) / SCL0 / Touch
  // pinMode(20/A6, INPUT/OUTPUT); //Digital Pin / Analog Pin (A6) / PWM
  // pinMode(22, INPUT); //Digital Pin / Analog Pin (A7) / RX1 / PWN
  // pinMode(22/A8, INPUT/OUTPUT); //Digital Pin / Analog Pin (A8) / Touch / PWM
  // pinMode(23/A9, INPUT/OUTPUT); //Digital Pin / Analog Pin (A9) / Touch / PWM
}

void loop() {
  // Here we will put our main code, to run repeatedly: 
  // I think it is a good idea for us to put our ideas about implementation here.
  //
  // Joseph - Jan 24, 2014:
  // So basically my idea is represented by this simple state machine:
  // (START) -> (SCAN) -> (TARGET) -> (AIM-H) -> (AIM-V) -> (FIRE) -> (ADJUST/FIREx5)
  // We scan left and right until we find a strong reading on the ultrasonic sensor.
  // Once we find it, we adjust our horizontal servo until we are aiming directly at
  // the strongest return signal we sensed.  We adjust the vertical aim based on the 
  // strength of the signal we get (to judge distace.) We will have to test and 
  // calibrate this based on distance.  We then aim for a spot slightly  higher than 
  // we think we will need and fire a shot, followed by five servo adjustments down 
  // and five additional shots to try and hit the target. 
  
  //slowManualControl();
  //fastManualControl();
  //tester();
  //scan();
  //aim();
  //fire();
  //delay(1000);
  //scanLoop();
}

void scan() {
  
}

void aim(int horz, int vert){
  
  delay(10);
  horizontal.write(horz);
  Serial.println(horz);
  //horizontal.detach();
  
  delay(10);
  vertical.write(vert);
  Serial.println(vert);
  //vertical.detach();
  return;
}

void fire() {
 //Serial.println("Fire");
 digitalWrite(firePin, HIGH);
 delay(1000);
 digitalWrite(firePin, LOW);
}

void slowManualControl(){
  // 5 IS OUR ZERO VERITCAL,  AND WE TOP OUT AT ABOUT 120
  // 0 IS OUR HORIZONTAL RIGHT, 
  
  static int v = 0;

  if ( Serial.available()) {
    char ch = Serial.read();

    switch(ch) {
      case '0'...'9':
        v = v * 10 + ch - '0';
        break;
      case 'q':
        horizontal.write(v);
        v = 0;
        break;
      case 'w':
        vertical.write(v);
        v = 0;
        break;
      case 's':
        vertical.detach();
        break;
      case 'a':
        vertical.attach(vServoPin);
        break;
      case 'x':
        horizontal.detach();
        break;
      case 'z':
        horizontal.attach(hServoPin);
        break;
    }
  }
}

void fastManualControl(){
   static char horz = 0;
   static char vert = 0;
   Serial.println("Choose Horizontal Value: (XXX)");
   while (Serial.available() > 0) {
     horz = Serial.read();
     Serial.println("Horz: ");
     Serial.println(horz);
   }
   
   Serial.println("Choose Vertical Value: (YYY)");
   while ( Serial.available() > 0) {
     vert = Serial.read();
     Serial.println("Vert: " + vert);
   }
   aim(horz,vert);
   return;
}

void tester(){
  horizontal.attach(hServoPin);
  spanh();
  horizontal.detach();
  vertical.attach(vServoPin);
  spanv();
  vertical.detach();
}

void spanh(){
  horizontal.write(90);
  delay(300);
  for (int i = 90; i < 180; i=i+3){
      aim(i,i);
      delay(1);
  }
  for (int i = 90; i > 0; i=i-3){
      aim(i,i);
      delay(1);
  }
  horizontal.write(90);
  delay(250);
}

void spanv(){
  for (int i = 0; i < 110; i=i+3){
      aim(i,i);
      delay(1);
  }
  vertical.write(0);
  delay(250);
}

void scanLoop(){
  /* The following trigPin/echoPin cycle is used to determine the
   distance of the nearest object by bouncing soundwaves off of it. */ 
   int avtop, avfin = 0;
   for (int i = 0; i < 500; i++){
     digitalWrite(trigPin, LOW); 
     delayMicroseconds(2); 

     digitalWrite(trigPin, HIGH);
     delayMicroseconds(10); 
 
     digitalWrite(trigPin, LOW);
     duration = pulseIn(echoPin, HIGH);
     delay(2);
     avtop += duration;
   }
   avfin = avtop/20;
 
   //Calculate the distance (in cm) based on the speed of sound.
   distance = avfin/58.2;
 
   Serial.println(distance);
}





