// UTFT Library
// web: http://www.henningkarlsen.com/electronics

#include <UTFT.h>

#define X_Scale 0.7666 
#define Y_Scale 0.96

// Declare which fonts we will be using
extern uint8_t SmallFont[];

//Init LCD Variable
UTFT myGLCD(31,A2,A1,A3,A4);

void dot(int, int);
void line(int, int, int, int);
void clr();
void drawGrid();
void drawProfiles();

void drawProfiles() {
  //Profile Lines
  //Fastest
  myGLCD.setColor(0,255,0);
  line(0,25,34,100);
  line(34,100,94,150);
  line(94,150,123,235);
  line(123,235,146,235);
  line(146,235,169,100);
  
  //Slowest
  myGLCD.setColor(0,255,0);
  line(0,25,125,100);
  line(125,100,245,150);
  line(245,150,386,235);
  line(386,235,431,100);
}

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT_PULLUP);
  
  // Setup the LCD
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  drawGrid();
  drawProfiles();

  
}

   bool data = false;
void loop()
{
  myGLCD.setColor(255, 0, 0);

  String content = "";
  String content2 = "";
  char character;

  if (Serial.available()>0 && Serial.peek() == '$') {
    //We have a new data point get it
    delay(50);
    Serial.read();
    while(Serial.available()>0) {
      character = Serial.read();
      content.concat(character);
    }
    //Check if we got a clear screen command ie. New reflow
    if (content.indexOf('$') != -1) {
      clr();
      drawGrid(); 
    } else {
      String x = "";
      String y = "";
      for (int j=0; j<content.indexOf(',');j++) {
        x.concat(content[j]);
      }
      for (int j=content.indexOf(',')+1;j<content.length();j++) {
        y.concat(content[j]);
      }
      dot(x.toInt(), y.toInt());
      content = "";
    }
  }
                        

 
}

void clr() {
  myGLCD.clrScr();
}

void dot(int x, int y) {
  //input seconds and degrees. 12px/12.5C 
  // 23px/30s
  // Y=226 - float(12/12.5)*y
  // X=(float(23/30))*x + 26
  int Y = 226 - float(Y_Scale*(y-25));
  int X = float(X_Scale*x) + 26;
  myGLCD.drawPixel(X,Y);
}

void line(int x1, int y1, int x2, int y2) {
  int X1, X2, Y1, Y2;
  X1 = float(X_Scale*x1) + 26;
  X2 = float(X_Scale*x2) + 26;
  Y1 = 226 - float(Y_Scale*(y1-25));
  Y2 = 226 - float(Y_Scale*(y2-25));
  myGLCD.drawLine(X1,Y1,X2,Y2);
}

void drawGrid() {
  clr();
  
  //  myGLCD.print("Temperature C", 12, 70,90);

  
  // Set color White
  myGLCD.setColor(255, 255, 255);

  
  // Y-Axis Labels
  myGLCD.print("25",8,221);
  myGLCD.print("50",8,197);
  myGLCD.print("75",8,173);
  myGLCD.print("100",0,149);
  myGLCD.print("125",0,125);
  myGLCD.print("150",0,101);
  myGLCD.print("175",0,77);
  myGLCD.print("200",0,53);
  myGLCD.print("225",0,29);
  myGLCD.print("250", 0,4);
  
  // X-Axis Labels
  myGLCD.print("0",24,228);
  myGLCD.print("1",69,228);
  myGLCD.print("2",115,228);
  myGLCD.print("3",160,228);
  myGLCD.print("4",207,228);
  myGLCD.print("5",252,228);
  myGLCD.print("6",299,228);
  myGLCD.print("7",344,228);
  myGLCD.print("8",391,228);
  
  //Set color Blue
  myGLCD.setColor(0, 0, 255);
  
  //draw Y axis
  myGLCD.drawLine(25, 0, 25, 226);
  // draw X axis
   myGLCD.drawLine(25, 226, 398, 226);
   
  //Set color Blue
  myGLCD.setColor(0, 255, 255);   

  //draw Y ticks
  for (int i=214; i>=0; i-=24) {
    myGLCD.drawLine(26, i, 27, i);
    myGLCD.drawLine(26, i-12, 28, i-12);
    
  }
 

  
  //draw X Ticks
  for (int i=48; i<=399; i+=46) {
    myGLCD.drawLine(i, 225, i, 224);
    myGLCD.drawLine(i+23, 225, i+23, 223);
    
  }
}

