int motorRightA = 8;    //Right Motor-clockwise
int motorRightB = 9;   //Right Motor-anticlockwise
int motorLeftA = 11;   //Left Motor-clockwise
int motorLeftB = 10;   //Left Motor-clockwise
int trigPin1 = 12;     // Trig Pin
int echoPin1 = 13;     // Echo Pin
long duration1;
int distance1;
int update_interval=100; // time interval in ms for updating panel indicators 
unsigned long last_time=0; // time of last update
char data_in = 0;            //Bluetooth Control
int trigPin2 = 7;       // Trig Pin
int echoPin2 = 6;       // Echo Pin
long duration2;
int distance2;
int light = 5;
int buzzer = 4;
int pushButton = 3;
void setup()
{
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(light, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP);
  Serial.println("*.kwl");
Serial.println("clear_panel()");
Serial.println("set_grid_size(14,7)");
Serial.println("add_text_box(3,6,3,L,wheel chair ,245,240,245,)");
Serial.println("add_text_box(8,4,3,L,led,245,240,245,)");
Serial.println("add_text_box(11,4,3,L,alarm ,245,240,245,)");
Serial.println("add_button(4,1,2,C,c)");
Serial.println("add_button(6,2,11,F,f)");
Serial.println("add_button(6,4,5,R,r)");
Serial.println("add_button(4,5,3,D,d)");
Serial.println("add_button(2,4,12,G,g)");
Serial.println("add_button(2,2,4,K,k)");
Serial.println("add_button(4,3,14,S,s)");
Serial.println("add_switch(8,2,4,A,a,0,0)");
Serial.println("add_switch(11,2,4,B,b,0,0)");
Serial.println("set_panel_notes(,,,)");
Serial.println("run()");
Serial.println("*");

  Serial.begin(9600);
}
void loop()
{
  //Light On Off
  lightOnOff();
  //Panic Button
  panicSound();

  //  Right
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance1);

  // Left 
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance2);
  
  if (distance1 <= 20 || distance2 <= 20) {
    //Stop Wheel Chair
    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, LOW);
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);
    control();
  }
  else {
    control(); // Call All the Control
  }
}

// All the Controls of the Wheel Chair
void control() {
  if (Serial.available() > 0)
  {
    data_in = Serial.read();
    if(data_in=='C')       //move forwards
    {
      digitalWrite(motorRightA, HIGH);
      digitalWrite(motorLeftA,  HIGH);
    }
    else if(data_in=='c')       //STOP
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorLeftA,  LOW);
    }
    if (data_in=='D')       //move backwards
    {
      digitalWrite(motorRightB, HIGH);
      digitalWrite(motorLeftB, HIGH);
    }
    else if (data_in=='d')       //STOP
    {
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftB, LOW);
    }
    
    else if (data_in=='R')    //right
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, HIGH);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='r')     //stop!
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='K')     //left
    {
      digitalWrite(motorRightA, HIGH);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='k')     //stop!
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='F')    //forward right
    {
      digitalWrite(motorRightA, HIGH);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, HIGH);
    }
    else if (data_in=='f')     //stop!
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='G')    //forward left
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, HIGH);
      digitalWrite(motorLeftA, HIGH);
      digitalWrite(motorLeftB, LOW);
    }
    else if (data_in=='g')     //stop!
    {
      digitalWrite(motorRightA, LOW);
      digitalWrite(motorRightB, LOW);
      digitalWrite(motorLeftA, LOW);
      digitalWrite(motorLeftB, LOW);
    }
  }
}
void lightOnOff() {

  if (data_in=='A') {
    digitalWrite(light, HIGH);
  }
  else if (data_in=='a') {
    digitalWrite(light, LOW);
  }
}
void panicSound() {
  int val = digitalRead(pushButton);
  if (val == LOW) {
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}