int pin2 = 2;
int pin3 = 3;
int SWpin = 10;
int LEDpins[] = {6,5,4,3,2};
int X;
int Y;
int Left;
int Right;
int button = 0;
int pos;

void setup() {
  Serial.begin(9600);
  pinMode(SWpin,INPUT_PULLUP);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  button = digitalRead(10);
  if(button==LOW){
    allOn(LEDpins);
  } else {
    X = analogRead(pin2);
    if (X == 0){
      turn1On(0,LEDpins);
    }else if (X < 400){
      turn1On(1,LEDpins);
    }else if (X < 600){
      turn1On(2,LEDpins);
    }else if (X < 1022){
      turn1On(3,LEDpins);
    }else {
      turn1On(4,LEDpins);
    }
  }
  Left = analogRead(0);
  Right = analogRead(4);
  delay(100);
  Serial.print(Left);
  Serial.print(" ");
  Serial.println(Right);
  pos = getLightPosition(Left,Right);
  Serial.print("The current LED is ");
  Serial.println(pos);
}

void turn1On(int onLED,int LEDlist[]){
  allOff(LEDlist);
  digitalWrite(LEDlist[onLED],HIGH);
}

void allOff(int LEDlist[]){
  for (int i=0; i<5; i++){
    digitalWrite(LEDlist[i],LOW);
  }
}

void allOn(int LEDlist[]){
  for (int i=0; i<5; i++){
    digitalWrite(LEDlist[i],HIGH);
  }
}

int getLightPosition(int leftPhotoresist, int rightPhtotoresist){
  if(leftPhotoresist>50 && rightPhtotoresist>50){
    return 6;
  } else if (leftPhotoresist>50) {
    return 1;
  } else if (leftPhotoresist>15) {
    return 2;
  } else if (rightPhtotoresist>40) {
    return 5;
  } else if (rightPhtotoresist>5) {
    return 4;
  } else {
    return 3;
  } 
}
