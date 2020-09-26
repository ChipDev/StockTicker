int pin2state = LOW;
int led0 [8] = {1, 0, 0, 0, 0, 0, 0, 1};
int led1 [8] = {1, 1, 1, 0, 1, 1, 0, 1};
int led2 [8] = {0, 1, 0, 0, 0, 0, 1, 1};
int led3 [8] = {0, 1, 0, 0, 1, 0, 0, 1};
int led4 [8] = {0, 0, 1, 0, 1, 1, 0, 1};
int led5 [8] = {0, 0, 0, 1, 1, 0, 0, 1};
int led6 [8] = {0, 0, 0, 1, 0, 0, 0, 1};
int led7 [8] = {1, 1, 0, 0, 1, 1, 0, 1};
int led8 [8] = {0, 0, 0, 0, 0, 0, 0, 1};
int led9 [8] = {0, 0, 0, 0, 1, 1, 0, 1};
int all [8] = {0, 0, 0, 0, 0, 0, 0, 0};
int currentsecond = -1; 
int digit1led = 1;
int digit2led = 0;
int currentdigit = 2;

void setup() {
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  

  digitalWrite(4, LOW); //4 WAS DATA
  digitalWrite(5, LOW); 
  digitalWrite(6, LOW); 
  digitalWrite(7, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(10, digit1led); //1st digit NPN
  digitalWrite(11, digit2led);
  clearLEDs();

  int* led = all;
    for(int i = 0; i < 8; i++){
      digitalWrite(4, led[7-i]);
      digitalWrite(5, HIGH);
      digitalWrite(5, LOW); 
    }
    digitalWrite(6, HIGH);
    digitalWrite(6, LOW);

}

void clearLEDs() {
  digitalWrite(7, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(6, LOW);
}

void loop() {

                                                                                      
  long seconds = millis() / 1000;
            //if(seconds != currentsecond){
  currentsecond = (int) seconds;
  int digit1s = (int)seconds % 10;
  int digit10s = (((int)seconds % 100) - digit1s) / 10;
  int* led1s = ledkey(digit1s);
  int* led10s = ledkey(digit10s);
  
                                                          
  for(int i = 0; i < 8; i++){
    if(currentdigit == 2){
      digitalWrite(4, led10s[7-i]);
    }else if(currentdigit == 1){
      digitalWrite(4, led1s[7-i]);
    }
    digitalWrite(5, HIGH);
    digitalWrite(5, LOW); 
  }
  digitalWrite(10, 0);
  digitalWrite(11, 0);  //PREVENTS OVERLAPPING BETWEEN LEDS BY TURNING THEM OFF FOR THE UPDATE PROCESS

  digitalWrite(6, HIGH);
  digitalWrite(6, LOW);

  switchLEDposition();
            //}
                                                                

}


int * ledkey(int digit) {
  if(digit == 1){
    return led1;
  }
  if(digit == 2){
    return led2;
  }
  if(digit == 3){
    return led3;
  }
  if(digit == 4){
    return led4;
  }
  if(digit == 5){
    return led5;
  }
  if(digit == 6){
    return led6;
  }
  if(digit == 7){
    return led7;
  }
  if(digit == 8){
    return led8;
  }
  if(digit == 9){
    return led9;
  }
  if(digit == 0){
    return led0;
  }
}

void switchLEDposition(){
  
  if(digit1led == 1){
    digit1led = 0;
    digit2led = 1;
    currentdigit = 2;
  }else if(digit2led == 1){
    digit2led = 0;
    digit1led = 1;
    currentdigit = 1;
  }

  digitalWrite(10, digit1led);
  digitalWrite(11, digit2led);
  //delay(5);

}
