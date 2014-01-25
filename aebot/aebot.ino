//  ---------  Angry Engineers Robot - Winter 2013  ---------
//  --  Brendan Huber, Joseph DeVictoria, Scott Heidbrink  --
//  -  This robot will use an  ultrasonic sensor to locate  -
//  -  a 1 sq. ft. target, and launch a missile to hit it.  -
//  -   Made for angry engineers competition Feb 19, 2014   -
//  ---------------------------------------------------------
//int a = 0;

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
  
  //for (int i = 1; i < 50; i++){
  //  digitalWrite(3, 1);
  //  delay(5);
  //  digitalWrite(3, 0);
  //  delay(1000);
  //}
  //a = analogRead(22);
  //Serial.println(a);
  //delay(100);
}
