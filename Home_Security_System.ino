#include <Keypad.h>
#include <Servo.h> 

String room1 = "0001";
String room2 = "0002";
String room_all = "0";
String close_all = "0000";

String tempPassword;

int i;

const int gasPin1 = A4;
const int gasPin2 = A5;
const int threshold1 = 90;
const int threshold2 = 280;

int count[2] = {0,0};

char keypressed;

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {11, 10, 9, 8}; //Rows 0 to 3
byte colPins[numCols]= {7, 6, 5, 4}; //Columns 0 to 3

int servoPin1 = 12;
int servoPin2 = 13;

int ledPin1 = 2;
int ledPin2 = 3;

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);
Servo servo1; 
Servo servo2;

int angle = 0;   // servo position in degrees 

void setup()
{
  Serial.begin(9600);
  servo1.attach(servoPin1); 
  servo1.write(0);
  servo2.attach(servoPin2);
  servo2.write(0);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}
void loop()
{
  if((analogRead(gasPin1) > threshold1) && (analogRead(gasPin2) > threshold2) && (count[0] == 0 && count[1] == 0))
  {
    Serial.println("Fire alert in all rooms. Please enter the master code followed by * to open all the doors");
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    enterPassword();  
    delay(1000);
  }
  if((analogRead(gasPin1) > threshold1) && count[0] == 0)
  {
    Serial.println("Fire alert in room number 1. Please enter the code followed by *");
    digitalWrite(ledPin1, HIGH);
    enterPassword1();
    delay(1000);  
  }
  if((analogRead(gasPin2) > threshold2) && count[1] == 0)
  {
    Serial.println("Fire alert in room number 2. Please enter the code followed by *");
    digitalWrite(ledPin2, HIGH);
    enterPassword2();
    delay(1000);  
  }
  if(analogRead(gasPin1) <= threshold1 && analogRead(gasPin2) <= threshold2)
  {
    Serial.println("All systems stable");
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    delay(5000);  
  }
  if(count[0] == 1 && count[1] == 1)
  {
    Serial.println("Enter code to close a doors");
    closeAllDoors();
    delay(1000);
  }
}

void enterPassword1() {
  tempPassword = "";
  while(1)
  {
    keypressed = myKeypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;   }
          if(keypressed == '*'){
            break;
          }
          }
  }
          
        
      if(tempPassword == room1)
      {
        //Serial.print("Entered room code is - ");
        Serial.println(tempPassword);
        servo1.write(180);
        Serial.println("Room 1 opened"); 
        tempPassword=""; 
        count[0] = 1;
        loop();
      }
      else if(tempPassword == "")
      {
        Serial.println("False Alarm detected, returning systems to normal condition");
        delay(1000);
        tempPassword = "";
        loop();  
      }
      /*else if(tempPassword == "1000")
      {
        servo1.write(0);
        Serial.println("Room 1 door closed");  
        tempPassword = "";
        count[0] = 0;
        loop();
      }*/
      else
      {
        Serial.println("Entered code doesn't match. Please re-enter the correct code followed by a *"); 
        //servo1.write(0);
        //servo2.write(0);
        enterPassword1(); 
      }
}
void enterPassword2() {
  tempPassword = "";
  while(1)
  {
    keypressed = myKeypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;   }
          if(keypressed == '*'){
            break;
          }
          }
  }
          
        
      if(tempPassword == room2)
      {
        Serial.print("Entered room code is - ");
        Serial.println(tempPassword);
        servo2.write(180);
        Serial.println("Room 2 opened"); 
        tempPassword=""; 
        count[1] = 1;
        loop();
      }
      else if(tempPassword == "")
      {
        Serial.println("False alarm detected, returning systems to normal condition");
        delay(1000);
        tempPassword = "";
        loop();  
      }
      /*else if(tempPassword == "1000")
      {
        servo2.write(0);
        Serial.println("Room 2 door closed");  
        tempPassword = "";
        count[1] = 0;
        loop();
      }*/
      else
      {
        Serial.println("Entered code doesn't match. Please re-enter the room code followed by a  *"); 
        //servo2.write(0);
        //servo2.write(0);
        enterPassword2(); 
      }
}

void enterPassword() {
  tempPassword = "";
  while(1)
   {
    keypressed = myKeypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;   }
          if(keypressed == '*'){
            break;
          }
          }
  }
          
        
      if(tempPassword == room_all)
      {
        //Serial.print("Entered room code is - ");
        //Serial.println(tempPassword);
        servo1.write(180);
        Serial.println("Room 1 opened");
        servo2.write(180);
        Serial.println("Room 2 opened");
        tempPassword=""; 
        count[0] = 1;
        count[1] = 1;
        loop();
      }
      else if(tempPassword == "")
      {
        Serial.println("False alarm detected, returning systems to normal condition");
        delay(5000);
        tempPassword = "";
        loop();  
      }
      else
      {
        Serial.println("Entered code doesn't match. Please re-enter the correct code followed by a *"); 
        //servo1.write(0);
        //servo2.write(0);
        enterPassword(); 
      }
}

void closeAllDoors() {
  tempPassword = "";
  while(1)
  {
    keypressed = myKeypad.getKey();
          if (keypressed != NO_KEY){
            if (keypressed == '0' || keypressed == '1' || keypressed == '2' || keypressed == '3' ||
                keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' ||
                keypressed == '8' || keypressed == '9' ) {
          tempPassword += keypressed;   }
          if(keypressed == '*'){
            break;
          }
          }
  }
          
        
      if(tempPassword == close_all)
      {
          servo1.write(0);
          servo2.write(0);
          count[0] = 0;
          count[1] = 0;
          Serial.println("All doors closed");
          loop();
      }
      else if(tempPassword == "1000")
      {
        servo1.write(0);
        Serial.println("Door 1 closed");  
        count[0] = 0;
        delay(1000);
        loop();
      }
      else if(tempPassword == "2000")
      {
        servo2.write(0);
        Serial.println("Door 2 closed");
        count[1] = 0; 
        delay(1000); 
        loop();
      }
      else if(tempPassword == "")
      {
        Serial.println("Returning to normal conditions");
        tempPassword == "";
        delay(1000);
        loop();  
      }
      else
      {
        Serial.println("Entered code doesn't match. Please re-enter the correct code followed by a *"); 
        //servo1.write(0);
        //servo2.write(0);
        closeAllDoors(); 
      }
}
