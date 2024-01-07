//set up sonar
#include <NewPing.h> 
#define TRIGGER_PIN 4
#define ECHO_PIN 3
#define MAX_DISTANCE 40 //maximum distance 40cm
NewPing sonar(TRIGGER_PIN,ECHO_PIN,MAX_DISTANCE); //construct
int pin2 = 2; //output to switch
int pin5 = 5; //output to mosfet
int dis,fs; //distance detected by sonar and the frequency of the fan
int state = LOW;

//set up keypad
#include <Key.h>
#include <Keypad.h>
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};
byte pin_rows[ROW_NUM] = {13,12,11,10};
byte pin_column[COLUMN_NUM] = {9,8,7,6};
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
const String password = "8675309"; // change your password here
String input_password;
boolean correct = false;

void setup() {
  Serial.begin(115200);
  pinMode(pin2,OUTPUT);
  pinMode(pin5,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pin2),changeState,RISING);
}

void loop() {
  if(correct == false){ //input password first
    char key = keypad.getKey();
    if (key){
      Serial.print(key);
      if(key == '#') {          
          if(input_password.indexOf(password)>=0) { //check if input password contains the password
            Serial.println("password is correct");
            correct = true;
          } else {
            Serial.println("password is incorrect, try again");
          }
          input_password = ""; // clear input password
        } else {
          input_password += key; // append new character to input password string
        }
    }
  } else {  //after inputing correct password, run the program
    unsigned int uS = sonar.ping();
    dis = sonar.convert_cm(uS);
    fs = dis*5+55;
    if(state==LOW){
      digitalWrite(5,LOW);
    } else {
      analogWrite(5,fs);
    }
  }
}

void changeState(){
  state = !state;
}
