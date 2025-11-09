
const int buttonPin = 2;  // the number of the pushbutton pin
const int red = 9;
const int green = 10;
const int blue = 11;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status
bool buttonPressed = false;
unsigned long pressingTime = 0;
const int longPressInterval = 2000;

int currentMode = 0;
unsigned long blinkTimer = 0;
const int blinkInterval = 500;
bool blinkOn = true;

const int fadeAmount = 2;
int fadeDirection = 1;

int lightNum = 0;
int redlight=0;
int greenlight = 0; 
int bluelight = 0 ;

int RCurrentColor=0;
int GCurrentColor=0;
int BCurrentColor=0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(red, OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  checkButton();
  setRGBLEDColor(RCurrentColor,GCurrentColor,BCurrentColor);
  updateLEDColor();
}
void checkButton(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW && !buttonPressed) {
    pressingTime = millis();
    buttonPressed = true;
  }
  if(buttonState == HIGH && buttonPressed) 
  {
    unsigned long currentTime = millis();
    if(currentTime - pressingTime < longPressInterval){
      //short click
      changeLEDColor();
    }
    else{
      //long press
      changeMode();
    }
    buttonPressed = false;
  }
}

void changeLEDColor(){
  lightNum = lightNum +1;
  if(lightNum>=5)
    lightNum = 0;
  if(lightNum==0){
    redlight = 0;
    greenlight = 0;
    bluelight = 0;
  }
  if(lightNum==1){
    redlight = 0;
    greenlight = 255;
    bluelight = 255;
  }
  if(lightNum==2){
    redlight = 255;
    greenlight = 0;
    bluelight = 255;
  }
  if(lightNum==3){
    redlight = 255;
    greenlight = 255;
    bluelight = 0;
  }
  if(lightNum==4){
    redlight = 0;
    greenlight = 255;
    bluelight = 0;
  }
  RCurrentColor = redlight;
  GCurrentColor = greenlight;
  BCurrentColor = bluelight;
}
void changeMode(){
  currentMode = currentMode +1;
  if(currentMode>=3){
    currentMode = 0;
  }
  if(currentMode==1){
    blinkTimer = 0;
    blinkOn = true;
  }
  if(currentMode ==2){
    fadeDirection = 1;
  }
}
void updateLEDColor(){
  if(currentMode ==0){
    RCurrentColor = redlight;
    GCurrentColor = greenlight;
    BCurrentColor = bluelight;
  }
  else if(currentMode == 1){
    unsigned long currentTime = millis();
    if(currentTime - blinkTimer > blinkInterval){
      blinkOn = !blinkOn;
      blinkTimer = currentTime;
    }
    if(blinkOn){
      RCurrentColor = redlight;
      GCurrentColor = greenlight;
      BCurrentColor = bluelight;
    }
    else{
      RCurrentColor = 255;
      GCurrentColor = 255;
      BCurrentColor = 255;
    }
  }
  else if(currentMode == 2){
    bool negativeDir = false;

    if(redlight==0){
      RCurrentColor = RCurrentColor + fadeDirection * fadeAmount;
      if(RCurrentColor > (255 - redlight)||(RCurrentColor<0)){
        negativeDir = true;
      }
      if(RCurrentColor<0) RCurrentColor = 0;
      if(RCurrentColor > 255) RCurrentColor = 255;
    }
    if(greenlight==0){
      GCurrentColor = GCurrentColor + fadeDirection * fadeAmount;
      if(GCurrentColor > (255 - greenlight)||(GCurrentColor<0)){
        negativeDir = true;
      }
      if(GCurrentColor<0) GCurrentColor = 0;
      if(GCurrentColor > 255) GCurrentColor = 255;
    }
    if(bluelight==0){
      BCurrentColor = BCurrentColor + fadeDirection * fadeAmount;
      if(BCurrentColor > (255 - bluelight)||(BCurrentColor<0)){
        negativeDir = true;
      }
      if(BCurrentColor<0) BCurrentColor = 0;
      if(BCurrentColor > 255) BCurrentColor = 255;
    }
    if(negativeDir)
      fadeDirection = -fadeDirection;
    delay(10);
  } 
}

void setRGBLEDColor(int r, int g, int b){
  analogWrite(red,r);
  analogWrite(blue,b);
  analogWrite(green,g);
}