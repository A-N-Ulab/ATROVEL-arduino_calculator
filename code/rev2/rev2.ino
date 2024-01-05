/*
Copyright C 2023 "to od"
Arduino calculator by ANUlab & Glinek

Calculator's layout:
7  8  9  +
4  5  6  -
1  2  3  /
,  0  R  *
eq -> =
clr -> Clear
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Button pins
#define eq 10
#define clr 11

//OLED init
Adafruit_SSD1306 display(128, 32, &Wire, -1);

//Variables
int HIGH_state, COL_pressed;
long lastBTNpress = 0, t1, t2;
int col,row, INTnumber2, whichNUM = 1, floatPoints1, floatPoints2;
double FLOATnumber1, FLOATnumber2, calculatedNum, displayedNum1, displayedNum2, ph1, ph2;
String STRnumber1, STRnumber2, STRoperator1, STRoperator2;
bool per1 = false, per2 = false;
const char* matrix[][4]={ {"+", "-", "/", "*"},
                          {"9", "6", "3", "R"},
                          {"8", "5", "2", "0"},
                          {"7", "4", "1", "."}, };

void setup(){
  //ROW's from R1 to R4 -> 2-5 as outputs
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  //COLUMN's from C1 to C4 -> 9-6 as inputs
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  //two extra buttons
  pinMode(eq, INPUT_PULLUP);
  pinMode(clr, INPUT_PULLUP);

  //Serial 
  Serial.begin(9600);

  //Display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE); 
  display.setCursor(0, 0);
}

void loop(){
  //loop for reading 8x8 button matrix
  for(HIGH_state = 2; HIGH_state < 6; HIGH_state++){
    digitalWrite(HIGH_state, LOW);
    for(COL_pressed = 6; COL_pressed < 10; COL_pressed++){
      if(digitalRead(COL_pressed) == LOW){
        if(millis()-lastBTNpress > 50){
          //Fix rows and cols to be from 0 to 3
          row = COL_pressed-6;
          col = HIGH_state-2;

          //------Setting number1-------
          if(whichNUM == 1 && matrix[row][col] == "0" || whichNUM == 1 && matrix[row][col] == "1" || whichNUM == 1 && matrix[row][col] == "2" || whichNUM == 1 && matrix[row][col] == "3" || whichNUM == 1 && matrix[row][col] == "4" || whichNUM == 1 && matrix[row][col] == "5" || whichNUM == 1 && matrix[row][col] == "6" || whichNUM == 1 && matrix[row][col] == "7" || whichNUM == 1 && matrix[row][col] == "8" || whichNUM == 1 && matrix[row][col] == "9" || whichNUM == 1 && matrix[row][col] == "."){
            //inserting and displaying floting number
            if(matrix[row][col] == ".") per1 = true; //set per1 to true if "." pressed
            if(per1) if(floatPoints1 < 5) floatPoints1++; //add 1 to floatPoints1 so floating number displayed

            //"make" number1
            if(String(FLOATnumber1).length() < 10){
              STRnumber1 = STRnumber1 + matrix[row][col]; //put new number to a string1
              FLOATnumber1 = STRnumber1.toFloat(); //convert string1 to float (number1)
              displayedNum1 = FLOATnumber1; //set displayed number as number1
            }
          }

          //------Setting operator number1------
          if(whichNUM == 1 && matrix[row][col] == "+" || whichNUM == 1 && matrix[row][col] == "-" || whichNUM == 1 && matrix[row][col] == "/" || whichNUM == 1 && matrix[row][col] == "*" || whichNUM == 1 && matrix[row][col] == "R"){
            STRoperator1 = matrix[row][col]; //set operator number 1
            whichNUM = 2; //go to set number 2
          }

          //------Setting number2------
          if(whichNUM == 2 && matrix[row][col] == "0" || whichNUM == 2 && matrix[row][col] == "1" || whichNUM == 2 && matrix[row][col] == "2" || whichNUM == 2 && matrix[row][col] == "3" || whichNUM == 2 && matrix[row][col] == "4" || whichNUM == 2 && matrix[row][col] == "5" || whichNUM == 2 && matrix[row][col] == "6" || whichNUM == 2 && matrix[row][col] == "7" || whichNUM == 2 && matrix[row][col] == "8" || whichNUM == 2 && matrix[row][col] == "9" || whichNUM == 2 && matrix[row][col] == "."){
            //inserting and displaying floting number
            if(matrix[row][col] == ".") per2 = true; //set per1 to true if "." pressed
            if(per2) if(floatPoints2 < 5) floatPoints2++; //add 1 to floatPoints1 so floating number displayed

            //"make" number2
            if(String(FLOATnumber2).length() < 10){
              STRnumber2 = STRnumber2 + matrix[row][col]; //put new number to string2
              FLOATnumber2 = STRnumber2.toFloat(); //convert string2 to float (number2)
              displayedNum2 = FLOATnumber2; //set displayed number as number2
            }
          }

          //------Setting operator number2 and making all the calculations------
          if(whichNUM == 2 && matrix[row][col] == "+" || whichNUM == 2 && matrix[row][col] == "-" || whichNUM == 2 && matrix[row][col] == "/" || whichNUM == 2 && matrix[row][col] == "*"  || whichNUM == 2 && matrix[row][col] == "R"){     
            //calculate square root of number1
            if(STRoperator1 == "R"){
              ph1 = FLOATnumber1; //put FLOATnumber1 to ph1 (placeholder1)
              FLOATnumber1 = sqrt(ph1); //calculate square root
              displayedNum1 = FLOATnumber1; //set displayedNum as square root of number1

              //set operators to empty strings to avoid errors
              STRoperator1 = "";
              STRoperator2 = "";
            }

            //make calculations when "+", "-", "*", "/" operators and set calculated number as number1
            else if(STRoperator2 == "+" || STRoperator2 == "-" || STRoperator2 == "*" || STRoperator2 == "/"){
              //subtraction, addition, itd.
              if(STRoperator1 == "+") calculatedNum = FLOATnumber1 + FLOATnumber2; //addition
              else if(STRoperator1 == "-") calculatedNum = FLOATnumber1 - FLOATnumber2; //subtraction
              else if(STRoperator1 == "/"){
                  calculatedNum = FLOATnumber1 / FLOATnumber2; 
                  floatPoints1 = 5;
                }
              else if(STRoperator1 == "*") calculatedNum = FLOATnumber1 * FLOATnumber2; //multiplication

              //clear for new calculations
              FLOATnumber1 = calculatedNum;
              FLOATnumber2 = 0;
              floatPoints2 = 0;
              STRoperator1 = STRoperator2;
              STRnumber2 = "";
              displayedNum1 = calculatedNum;
              displayedNum2 = 0;
              per1 = false;
              per2 = false;
            }

            //square root
            else if(STRoperator2 == "R"){
              if(STRoperator1 == "+") calculatedNum = FLOATnumber1 + FLOATnumber2; //addition
              else if(STRoperator1 == "-") calculatedNum = FLOATnumber1 - FLOATnumber2; //subtraction
              else if(STRoperator1 == "/"){
                calculatedNum = FLOATnumber1 / FLOATnumber2; 
                floatPoints1 = 5;
              }
              else if(STRoperator1 == "*") calculatedNum = FLOATnumber1 * FLOATnumber2; //multiplication
              
              ph2 = calculatedNum; //put calculatedNum to ph2 (placeholder2)
              calculatedNum = sqrt(ph2); //calculate square root
            }
            
            STRoperator2 = matrix[row][col]; //set oprator number 2
            STRoperator1 = matrix[row][col]; //set oprator number 1
          }
          //------DEBUG------
          if(true){  
            Serial.print(matrix[row][col]);
            Serial.print("\t");
            Serial.print(STRnumber1);
            Serial.print(" | ");
            Serial.print(STRnumber2);
            Serial.print("\t");
            Serial.print(FLOATnumber1, 5);
            Serial.print(" | ");
            Serial.print(FLOATnumber2, 5);
            Serial.print("\t");
            Serial.print(STRoperator1);
            Serial.print(" | ");
            Serial.print(STRoperator2);
            Serial.print("\t");
            Serial.print(calculatedNum, 5);
            Serial.print(" | ");
            Serial.print(displayedNum1, 5);
            Serial.print(" | ");
            Serial.print(displayedNum2, 5);
            Serial.print("\t");
            Serial.println(whichNUM);             
          }
        }
        lastBTNpress = millis();
      }
    }
    digitalWrite(HIGH_state, HIGH);
  }

  //------make calculations when operator is "="------
  if(digitalRead(eq) == LOW){
    if(millis()-lastBTNpress > 50){
      if(STRoperator1 == "+") calculatedNum = FLOATnumber1 + FLOATnumber2; //addition
      else if(STRoperator1 == "-") calculatedNum = FLOATnumber1 - FLOATnumber2; //subtraction
      else if(STRoperator1 == "/"){
        calculatedNum = FLOATnumber1 / FLOATnumber2; 
        floatPoints1 = 5;
      }
      else if(STRoperator1 == "*") calculatedNum = FLOATnumber1 * FLOATnumber2; //multiplication
            
      //set all variables to default
      displayedNum1 = calculatedNum; //set displayedNum1 to 0
      FLOATnumber1 = calculatedNum; //set number1 as calculatedNum
      displayedNum2 = 0; //set displayedNum2 to 0
      calculatedNum = 0; //set calculatedNum to 0 
      floatPoints2 = 0; //reset floatPoints2
      //reset number2 and operators
      STRnumber2 = "";
      STRoperator1 = "=";
      STRoperator2 = "=";
      per1 = false;
      per2 = false;
    }
    lastBTNpress = millis();
  }

  //------clear all numbers/set all variables to default------
  if(digitalRead(clr) == LOW){
    if(millis()-lastBTNpress > 50){
      whichNUM = 1; //set back to number1
      displayedNum1 = 0; //set displayedNum1 to 0
      displayedNum2 = 0; //set displayedNum2 to 0
      calculatedNum = 0; //set calculatedNum to 0
      //reset numbers and operators
      STRnumber1 = ""; 
      STRnumber2 = "";
      STRoperator1 = " ";
      STRoperator2 = "";
      FLOATnumber1 = 0;
      FLOATnumber2 = 0;
      //reset floatPoints
      floatPoints1 = 0;
      floatPoints2 = 0;
      per1 = false;
      per2 = false;
    }
    lastBTNpress = millis();
  }

  //------Display to OLED-----
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(displayedNum1, floatPoints1);
  display.setCursor(0,16);
  display.print(displayedNum2, floatPoints2);
  display.setCursor(110,16);
  display.print(STRoperator1);
  display.display();
}