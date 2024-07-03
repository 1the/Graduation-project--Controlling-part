//motor1
#define potentiometer  A0  //10k Variable Resistor-speed control "actual used 4.6 k-ohm only"
//pi signals
#define clk A1 // Clockwise Button "represents right/up"  
#define stop A2 // Stop Button "camera is off"
#define anti A3 // Anticlockwise Button "represents left/down"
//
#define dirPin  2  //8Pin  of Arduino--Direction of stepper motor driver 
#define stepPin 3  //9Pin  of Arduino--Step of stepper motor driver 
#define enPin   4 //10Pin of Arduino--Enabled of stepper motor driver  

int read_ADC;
int Speed_LCD, Speed_Delay;
int Mode=1, flag=0;

//motor2
#define potentiometer2  A4  //10k Variable Resistor-speed control "actual used 4.6 k-ohm only"
//pi signals
#define clk2 A5 // Clockwise Button "represents right/up"
#define stop2 A6 // Stop Button "camera is off"
#define anti2 A7 // Anticlockwise Button "represents left/down"
//
#define dirPin2  5  //8Pin  of Arduino--Direction of stepper motor driver 
#define stepPin2 6  //9Pin  of Arduino--Step of stepper motor driver 
#define enPin2   7 //10Pin of Arduino--Enabled of stepper motor driver  

int read_ADC2;
int Speed_LCD2, Speed_Delay2;
int Mode2=1, flag2=0;

//buzzer
#define buzzer 8
//pi signal
#define fire A8       //common between: buzzer , exit door, fan
//

//door
#define power 9
#define ENA 10    // Enable pin for motor A
#define IN1 11   // Input 1 pin for motor A
#define IN2 12   // Input 2 pin for motor A
//its signal is up there "fire"
    
const int motorSpeed = 15;   // Motor speed (0-255)
int motorDirection = 0;   // Motor direction (0 or 1)
bool buttonState = false; // Button state (pressed or released)
int count1 = 0;
int count2 = 0;

//fan
#define fan 13
bool isFireDetected= false;
//its signal is up there "fire"

//pump
#define pumpPin 22 // Relay controlling the pump

//valve
//its supposed to work after the 2motors stop moving,then it uses fire on, stop on,stop2 on
#define valvePin 23 // Relay controlling the valve





void setup() { // put your setup code here, to run once
//motor1
pinMode(potentiometer, INPUT); // declare potentiometer as input 
pinMode(clk, INPUT_PULLUP); // declare bt_F as input
pinMode(stop, INPUT_PULLUP); // declare bt_S as input
pinMode(anti, INPUT_PULLUP); // declare bt_B as input
pinMode(dirPin,  OUTPUT); // declare as output for Direction of stepper motor driver 
pinMode(stepPin, OUTPUT); // declare as output for Step of stepper motor driver 
pinMode(enPin,   OUTPUT); // declare as output for Enabled of stepper motor driver 
//motor2
pinMode(potentiometer2, INPUT); // declare potentiometer as input 
pinMode(clk2, INPUT_PULLUP); // declare bt_F as input
pinMode(stop2, INPUT_PULLUP); // declare bt_S as input
pinMode(anti2, INPUT_PULLUP); // declare bt_B as input
pinMode(dirPin2,  OUTPUT); // declare as output for Direction of stepper motor driver 
pinMode(stepPin2, OUTPUT); // declare as output for Step of stepper motor driver 
pinMode(enPin2,   OUTPUT); // declare as output for Enabled of stepper motor driver 
//buzzer
pinMode(buzzer, OUTPUT);
//door
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(power, HIGH);
digitalWrite(ENA, LOW);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
//fan
pinMode(fan, OUTPUT);
//pump
pinMode(pumpPin, OUTPUT);
digitalWrite(pumpPin, LOW);
//valve
pinMode(valvePin, OUTPUT);
digitalWrite(valvePin, LOW);

//signal for door,buzzer,valve,fan
pinMode(fire, INPUT_PULLUP);
  
}

void loop() { 
//motor1
read_ADC = analogRead(potentiometer); // read analogue to digital value 0 to 1023 
Speed_Delay = map(read_ADC, 0, 1023, 5000, 10); //value map for Microstep resolution Delay
Speed_LCD = map(read_ADC, 0, 1023, 0, 100); //value map to Display on the LCD

if(digitalRead (clk) == 1){Mode = 2; digitalWrite(enPin, LOW);} //For Clockwise

if(digitalRead (stop) == 1){ //For Stop
if(flag==0){flag=1;
 if(Mode>1)Mode=1; 
 else{Mode=!Mode; 
    if(Mode==0)digitalWrite(enPin, HIGH);
      else digitalWrite(enPin, LOW);
  }
delay(100);
 }
}else{flag=0;} 

if(digitalRead (anti) == 1){Mode = 3; digitalWrite(enPin, LOW);} //For Anticlockwise

if(Speed_LCD>0 && Mode>1){ 
   
  if(Mode==2)digitalWrite(dirPin, LOW);// Stepper motor rotates CW (Clockwise)
        else digitalWrite(dirPin, HIGH);// Stepper motor rotates CCW (Anticlockwise)

digitalWrite(stepPin, HIGH);
delayMicroseconds(Speed_Delay);
digitalWrite(stepPin, LOW);
delayMicroseconds(Speed_Delay);
}  

//motor2
read_ADC2 = analogRead(potentiometer2); // read analogue to digital value 0 to 1023 
Speed_Delay2 = map(read_ADC2, 0, 1023, 5000, 10); //value map for Microstep resolution Delay
Speed_LCD2 = map(read_ADC2, 0, 1023, 0, 100); //value map to Display on the LCD

if(digitalRead (clk2) == 1){Mode2 = 2; digitalWrite(enPin2, LOW);} //For Clockwise

if(digitalRead (stop2) == 1){ //For Stop
  if(flag2==0){flag2=1;
    if(Mode2>1)Mode2=1; 
        else{Mode2=!Mode2; 
        if(Mode2==0)digitalWrite(enPin2, HIGH);
              else digitalWrite(enPin2, LOW);
        }
    delay(100);
    }
}else{
  flag2=0;
} 

if(digitalRead (anti2) == 1){Mode2 = 3; digitalWrite(enPin2, LOW);} //For Anticlockwise

if(Speed_LCD2 >0 && Mode2 >1){ 
   
  if(Mode2==2)digitalWrite(dirPin2, LOW);// Stepper motor rotates CW (Clockwise)
        else digitalWrite(dirPin2, HIGH);// Stepper motor rotates CCW (Anticlockwise)

digitalWrite(stepPin2, HIGH);
delayMicroseconds(Speed_Delay2);
digitalWrite(stepPin2, LOW);
delayMicroseconds(Speed_Delay2);
}  

//buzzer
int status = digitalRead(fire);
if(status == HIGH){
  digitalWrite(buzzer, HIGH);
}else{
  digitalWrite(buzzer, LOW);
}


//door
buttonState = digitalRead(fire);
// Move motor if button is pressed and motor is not already moving
if (fire == LOW) {
  // Motor moves in one direction
  motorDirection = 0;
  count2 = 0;
  if(count1 == 0)
    digitalWrite(power, HIGH);
  digitalWrite(IN1, motorDirection);
  digitalWrite(IN2, !motorDirection);
  // Set motor speed
  analogWrite(ENA, motorSpeed);
  delay(120); // Move for 20 milliseconds
  analogWrite(ENA, 0); // Stop the motor
  digitalWrite(IN1, 0);
  digitalWrite(IN2, motorDirection);
  digitalWrite(power, LOW);
  count1 ++;    
}
// Move motor in the other direction if button is released and motor is not already moving
if (fire == HIGH) {
  // Motor moves in the other direction
  motorDirection = 1;
  count1 = 0;
  if(count2 == 0)
    digitalWrite(power, HIGH);
  digitalWrite(IN1, motorDirection);
  digitalWrite(IN2, !motorDirection);
  // Set motor speed
  analogWrite(ENA, motorSpeed);
  delay(120); // Move for 20 milliseconds
  analogWrite(ENA, 0); // Stop the motor
  digitalWrite(IN1, !motorDirection);
  digitalWrite(IN2, !motorDirection);
  digitalWrite(power, LOW);
  count2 ++;
}

//fan
isFireDetected = digitalRead(fire);
  
if (isFireDetected == LOW) {
  // Turn on the fan
  digitalWrite(fan, HIGH);
} else {
  // Turn off the fan
  digitalWrite(fan, LOW);
}

//pump is always on
digitalWrite(pumpPin, LOW);
delay(2000);
digitalWrite(pumpPin, HIGH);
delay(2000);

//valve is on in case of fire only
if(stop == 1 && stop2 == 1 && fire == 0) {
  digitalWrite(valvePin, LOW);
}else {
  digitalWrite(valvePin,HIGH);
 }
}