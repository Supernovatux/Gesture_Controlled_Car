#include <SoftwareSerial.h>

#define rxPin 13
#define txPin 12
char previous_state = 'S';
char current_state = 'S';
// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 4;
int in3 = 6;
int in4 = 5;
SoftwareSerial BT_Serial(rxPin, txPin); // RX, TX

void setup() {
  BT_Serial.begin(9600);
  //For debugging
  Serial.begin(9600);
  Serial.println(BT_Serial.available());
  	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
  pinMode(10, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
  analogWrite(10, 255);W
}

void loop(){
  while(BT_Serial.available()){
    current_state = BT_Serial.read();    
    if (previous_state == current_state) {
      continue;
    }
    previous_state = current_state;
    switch (current_state) {
      case 'S' :      
        STOP();
        break;
      case 'F' :
        M1Forward();
        break;
      case 'B' :
        M1Back();
        break;
      case 'L' :
        M2Left();
        break;
      case 'R':
        M2Right();
        break;       
    }
    Serial.println(current_state);
  }
}
// This function lets you control spinning direction of motors
void M1Forward() {
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(enA, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
}
void M1Back() {
	analogWrite(enA, 255);
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	
}
void M2Left() {
  analogWrite(enA, 255);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	analogWrite(enB, 255);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
}
void M2Right() {
  STOP();
  analogWrite(enA, 255);
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	analogWrite(enB, 255);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
}
void STOP() {  
	analogWrite(enA, 0);
  analogWrite(enB, 0);
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}