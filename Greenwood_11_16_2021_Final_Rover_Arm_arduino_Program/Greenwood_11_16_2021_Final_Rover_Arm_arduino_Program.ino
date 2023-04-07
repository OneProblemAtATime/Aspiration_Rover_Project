//Arduino Code to run the ARM from the Raspberry Pi GUI
//Will Sayers & Joshua Merrit
// 5/21/2021 - 8/7/2021

// This code receives serial input from the Raspberry Pi and then takes that input and moves the ARM
// This code moves the ARM in up and down motions, as well as spins the stepper motor around so that the Stepper Motor can spin

bool Blink10, Blink20, Blink50, Blink100, Blink250, Blink500, Blink1000, Blink2000;  // square waves in msec.
bool Pulse10, Pulse20, Pulse50, Pulse100, Pulse250, Pulse500, Pulse1000, Pulse2000;  // one-shots in msec.

//These variables are used to keep track of run times
char Data_from_raspberry_pi;

//These are the pins from the stepper motor driver that are connected to the microcontroller
const uint8_t DirPin = 2;
const uint8_t StepPin = 3;
const uint8_t CSPin = 4;

//The 6 variables below are the pins that are connected to the arduino to control the motor driver
int Base_enable = 7;
int Speed_of_Base = 8;
int Base_direction = 9;
int Speed_of_actuator_Top = 10;
int Top_enable = 11;
int Top_direction = 12;

//***********************************************************************************************
// T I M E R  R O U T I N E S
//***********************************************************************************************
// ServiceTimers()
// General-purpose square waves are available as Blinkxxx at millisecond intervals shown below.
// General-purpose one-shots are available as Pulsexxx at millisecond intervals shown below.
//***************************************************
void ServiceTimers() {
  static uint32_t tNow, tRef10, tRef20, tRef50, tRef100, tRef250, tRef500, tRef1000, tRef2000;
  tNow = millis();
  Pulse10 = Pulse20 = Pulse50 = Pulse100 = Pulse250 = Pulse500 = Pulse1000 = Pulse2000 = 0;
  if ((tNow - tRef10) > 10) {
    Pulse10 = 1;
    Blink10 = !Blink10;
    tRef10 = tNow;
  }
  if ((tNow - tRef20) > 20) {
    Pulse20 = 1;
    Blink20 = !Blink20;
    tRef20 = tNow;
  }
  if ((tNow - tRef50) > 50) {
    Pulse50 = 1;
    Blink50 = !Blink50;
    tRef50 = tNow;
  }
  if ((tNow - tRef100) > 100) {
    Pulse100 = 1;
    Blink100 = !Blink100;
    tRef100 = tNow;
  }
  if ((tNow - tRef250) > 250) {
    Pulse250 = 1;
    Blink250 = !Blink250;
    tRef250 = tNow;
  }
  if ((tNow - tRef500) > 500) {
    Pulse500 = 1;
    Blink500 = !Blink500;
    tRef500 = tNow;
    Serial.print("Blink500: ");
    Serial.println(Blink500);
  }
  if ((tNow - tRef1000) > 1000) {
    Pulse1000 = 1;
    Blink1000 = !Blink1000;
    tRef1000 = tNow;
    Serial.print("Blink1000: ");
    Serial.println(Blink1000);
  }
  if ((tNow - tRef2000) > 2000) {
    Pulse2000 = 1;
    Blink2000 = !Blink2000;
    tRef2000 = tNow;
    Serial.print("Blink2000: ");
    Serial.println(Blink2000);
  }
}

//Setup runs once on startup of the microcontroller
void setup() {
  Serial.begin(9600);
  /* Used for verication of data transfer during testing
  Serial.begin(9600);
  Serial.print("Arduino is ready");
  */

  //All output pins are changed from a number to a physical conection to a arduino pin
  pinMode(Base_enable, OUTPUT);
  pinMode(Speed_of_Base, OUTPUT);
  pinMode(Base_direction, OUTPUT);
  pinMode(Top_enable, OUTPUT);
  pinMode(Speed_of_actuator_Top, OUTPUT);
  pinMode(Top_direction, OUTPUT);

  //Enables both actuators and sets the speed of both to 0
  digitalWrite(Base_enable, HIGH);
  analogWrite(Speed_of_Base, 0);
  digitalWrite(Top_enable, HIGH);
  analogWrite(Speed_of_actuator_Top, 0);

  //Used for testing //Serial.print("Initialization Complete");

}

//This loop constantly reads the serial input, and if a character was received, it runs through some switch cases
//The serial data is determined by the GUI on the Raspberry Pi. Depending on what button was pressed, a character is sent (they're numbers but considered characters)
void loop() {
  //ReadSerial();
  ServiceTimers();
}

void ReadSerial() {
  //Check to see if data was recieved and if true, store that data as "Data_from_raspberry_pi"
  if (Serial.available() > 0) {
    Data_from_raspberry_pi = Serial.read();
    //Serial.print("Message has been read"); This is commented out because it will print a ton of times and make the GUI crash
  }
  
  //Switch(variable)-case works just like an if-else statement
  switch (Data_from_raspberry_pi) { //Switch case checks the value of c and if the serial port reads a 1,2,... or 6, then it will do the case of that number.
    case '1':
      
      break;//Required at the end of any case in order to allow the program to continue running

    case '2':
      
      break;//Required at the end of any case in order to allow the program to continue running

    case '3': //Moves ARM Base Down
        digitalWrite(Base_enable, HIGH);
        digitalWrite(Base_direction, LOW); //You would think it's high to move the base up
        analogWrite(Speed_of_Base, 175);   //but when the motor goes down, it forces the ARM Up
        delay(500);    // Change this delay to make the ARM movements shorter or longer when a button was pressed
        digitalWrite(Speed_of_Base, 0); //The speed is turned off and then the pin is disabled. For some reason, there were issues when only the speed was turned off
        digitalWrite(Base_enable, LOW);   //The pin was disabled as well for good measure so that the ARM definitely stops after 0.5 seconds
        break;//Required at the end of any case in order to allow the program to continue running

    case '4': //Moves ARM Base Up
      digitalWrite(Base_enable, HIGH);
      digitalWrite(Base_direction, HIGH);
      analogWrite(Speed_of_Base, 175);
      delay(500);
      digitalWrite(Speed_of_Base, 0);
      digitalWrite(Base_enable, HIGH);
      break;//Required at the end of any case in order to allow the program to continue running

    case '5': //Moves the upper actuator of the ARM Down
        digitalWrite(Top_enable, HIGH);
        digitalWrite(Top_direction, LOW);
        analogWrite(Speed_of_actuator_Top, 175);
        delay(500);
        digitalWrite(Speed_of_actuator_Top, 0);
        digitalWrite(Top_enable, LOW);
        break;//Required at the end of any case in order to allow the program to continue running

    case '6': //Moves the upper actuator of the ARM Up
      digitalWrite(Top_enable, HIGH);
      digitalWrite(Top_direction, HIGH);
      analogWrite(Speed_of_actuator_Top, 175);
      delay(500);
      digitalWrite(Speed_of_actuator_Top, 0);
      digitalWrite(Top_enable, LOW);
      break;//Required at the end of any case in order to allow the program to continue running

    case '7':  //Stepper motor moves based on case 7 and 8.
      
      break;//Required at the end of any case in order to allow the program to continue running

    case '8':
      
      break;//Required at the end of any case in order to allow the program to continue running

    case '9':
      digitalWrite(Base_enable, HIGH);
      digitalWrite(Base_direction, HIGH);
      analogWrite(Speed_of_Base, 175);
      delay(11000); //Make sure the Base is all the way in the reset position before the top moves
      digitalWrite(Top_enable, HIGH);
      digitalWrite(Top_direction, HIGH);
      analogWrite(Speed_of_actuator_Top, 175);
      digitalWrite(Top_enable, HIGH);
      digitalWrite(Top_direction, LOW); //You would think it's high to tilt up
      analogWrite(Speed_of_actuator_Top, 175);
      break;//Required at the end of any case in order to allow the program to continue running
}}
