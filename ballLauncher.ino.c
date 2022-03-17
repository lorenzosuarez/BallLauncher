// Right engine  
const int EN_A = 9;
const int IN_1 = 8;  
const int IN_2 = 7;

//Left engine
const int EN_B = 3;
const int IN_3 = 5;  
const int IN_4 = 4;

const int PIN_BUZZER = 10;
const int TRIG = 12;
const int ECO = 11;
const int RELAY = 2;

int speedControl = A0;
int motorSpeed = 0;
           
boolean enable = false;
boolean inAction = false;

void setup ()
{
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);
  pinMode(RELAY, OUTPUT);
 
  // Right engine
  pinMode(IN_1, OUTPUT);    
  pinMode(IN_2, OUTPUT);
  pinMode(EN_A, OUTPUT);

  // Left engine
  pinMode(IN_3, OUTPUT);    
  pinMode(IN_4, OUTPUT);
  pinMode(EN_B, OUTPUT);

  Serial.begin(9600);
}
void loop()
{
  digitalWrite(RELAY, HIGH);
  int cm = ping();
  Serial.print("Distance: ");
  Serial.println(cm);
  delay(500);

  if(inAction == false){
    if (cm <= 5 || cm >= 16){
      inAction = true;
      startLaunch();
    }
  }
}

int ping() {
   long duration, distanceCm;
   
   digitalWrite(TRIG, LOW);
   delayMicroseconds(4);
   digitalWrite(TRIG, HIGH); 
   delayMicroseconds(10);
   digitalWrite(TRIG, LOW);
   
   duration = pulseIn(ECO, HIGH);
   
   distanceCm = duration * 10 / 292/ 2;   //convert distance, in cm
   return distanceCm;
}

void startLaunch(){
    tone(PIN_BUZZER, 500, 399);
    turnEngines();
    delay(1000);
    openSolenoid();
    delay(2500);
    closeSolenoid();
    stopEngines();
    inAction = false;
}

void turnEngines(){
  digitalWrite(IN_1, HIGH);  // Right turn
  digitalWrite(IN_2, LOW);
   
  analogWrite(EN_A, 100);

  digitalWrite(IN_3, LOW);  // Left turn
  digitalWrite(IN_4, HIGH);

  analogWrite(EN_B, 100);
 
  motorSpeed = analogRead(speedControl);

  motorSpeed = map(motorSpeed, 0, 1023, 0, 255);

  if (motorSpeed < 8) motorSpeed = 0;

  analogWrite(EN_A, motorSpeed);
  analogWrite(EN_B, motorSpeed);
}

void stopEngines(){
  digitalWrite(IN_1, LOW);  
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);  
  digitalWrite(IN_4, LOW);
}

void openSolenoid(){
  digitalWrite(RELAY, LOW);
}

void closeSolenoid(){
  digitalWrite(RELAY, HIGH);
}