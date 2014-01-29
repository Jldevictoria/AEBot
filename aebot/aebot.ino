//  ---------  Angry Engineers Robot - Winter 2013  ---------
//  --  Brendan Huber, Joseph DeVictoria, Scott Heidbrink  --
//  -  This robot will use an  ultrasonic sensor to locate  -
//  -  a 1 sq. ft. target, and launch a missile to hit it.  -
//  -   Made for angry engineers competition Feb 19, 2014   -
//  ---------------------------------------------------------
//int a = 0;
#include <Servo.h>
#include <math.h>

Servo horizontal;
int hServoPin = 14;
Servo vertical;
int vServoPin = 15;
int _pingPin = 16;

long halfBaseEdgeInches = 5*12;

void setup() {
  //Serial.begin(9600);
  // This is where we set up the transmit type for each pin:
  // pinMode(0, INPUT/OUTPUT); //Digital Pin / Touch / RX1
  // pinMode(1, INPUT/OUTPUT); //Digital Pin / Touch / RX1
  // pinMode(2, INPUT/OUTPUT); //Digital Pin / CS
  // pinMode(4, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(4, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(5, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(6, INPUT/OUTPUT); //Digital Pin / PWM
  // pinMode(7, INPUT/OUTPUT); //Digital Pin / DOUT / RX3
  // pinMode(8, INPUT/OUTPUT); //Digital Pin / DIN / TX3
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
  
  //horizontal.attach(_hServoPin);
  //vertical.attach(_vServoPin);
}

long GetSensorReading() {
  long duration;
  pinMode(_pingPin, OUTPUT);
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(_pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pingPin, LOW);
  /* 
  The same pin is used to read the signal from the PING))): a HIGH
  pulse whose duration is the time (in microseconds) from the sending
  of the ping to the reception of its echo off of an object.
  */
  pinMode(_pingPin, INPUT);
  duration = pulseIn(_pingPin, HIGH);
  return duration;
}   
  
long microsecondsToInches(long microseconds) {
  /*
  According to Parallax's datasheet for the PING))), there are
  73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  second).  This gives the distance travelled by the ping, outbound
  and return, so we divide by 2 to get the distance of the obstacle.
  See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  */
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  /* 
  The speed of sound is 340 m/s or 29 microseconds per centimeter.
  The ping travels out and back, so to find the distance of the
  object we take half of the distance travelled.
  */
  return microseconds / 29 / 2;
}

boolean FoundTarget(long distance, int hAngle)
{
  //DOESNT WORK!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int realAngle;
    if (hAngle > 90)
    {
       realAngle = 180 - hAngle;
    }
    else
    {
       realAngle = hAngle; 
    }
    int testAngle = 90 -realAngle;
    long edgeDistance = halfBaseEdgeInches/sin(testAngle);
    if (distance < edgeDistance)
    {
       return true; 
    }
    else
    {
       return false; 
    }
    
}

void Fire() {
 //Serial.println("Fire");
}

void Scan() {
  
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

void spanh(){
  for (int i = 0; i < 180; i++){
      aim(i,i);
      delay(10);
  }
}

void spanv(){
  for (int i = 0; i < 100; i++){
      aim(i,i);
      delay(10);
  }
}

void tester(){
  horizontal.attach(hServoPin);
  spanh();
  horizontal.write(0);
  delay(200);
  horizontal.detach();
  vertical.attach(vServoPin);
  spanv();
  vertical.write(0);
  delay(300);
  vertical.detach();
}

void loop() {
  /*long duration, inches;//, cm;
  duration = GetSensorReading();
  
  inches = microsecondsToInches(duration);
  //cm = microsecondsToCentimeters(duration);
  
  if (FoundTarget(inches, horizontal.read()))
  {
    Fire();
  }
  else
  {
    Scan();
  }  */
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
  
  //for (int i = 1; i < 50; i++){
  //  digitalWrite(3, 1);
  //  delay(5);
  //  digitalWrite(3, 0);
  //  delay(1000);
  //}
  //a = analogRead(22);
  //Serial.println(a);
  //delay(100);
  
  //slowManualControl();
  //fastManualControl();
  //tester();
  delay(1000);
}

