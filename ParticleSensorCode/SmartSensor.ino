#include "rgb_lcd.h"

rgb_lcd lcd;

int inBulb = D5;
int outBulb = D4;
int sensor1 = A0;
int sensor2 = A1;
int light1 = D2;
int light2 = D3;

int savedTime;
const int TimeOut = 1500;

bool walkingIn, walkingOut;
bool storeIn, storeOut;

//This is the variable we are interested in: Number of people in the room
int peopleIn = 0;

//Runs once upon setup
void setup() {
    //Activate input and output
    pinMode(inBulb, OUTPUT);
    pinMode(outBulb, OUTPUT);
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(light1,OUTPUT);
    pinMode(light2,OUTPUT);
    roomLights("off");
    
    //Track variable and turn on display
    Particle.variable("people",peopleIn);
    Particle.function("light",roomLights);
    lcd.begin(16, 2);
    //Set screen
    resetScreen();
}

//Continues to loop throughout the duration of the program
void loop() {
    //Lights off if no one's in the room!
    if(peopleIn > 0){
        lightsOn();
    } else {
        lightsOff();
    }
    //Implement time out system
    if(millis() - savedTime > TimeOut){
        resetVars();
    }
    //Someone walked in
    if(in() != storeIn && in()){
        savedTime = millis();
        walkingIn = !walkingIn;
        if(walkingOut){
            digitalWrite(outBulb, HIGH);
            //Do not allow a negative number of people in the room
            if(peopleIn > 0){
                peopleIn--;
                Particle.publish("decrement");
                lcd.setRGB(0, 128, 255);
                leftArrow();
            } else {
                errorNeg();
            }
            resetVars();
            resetScreen();
        }
    }
    //Someone walked out
    if(out() != storeOut && out()){
        savedTime = millis();
        walkingOut = !walkingOut;
        if(walkingIn){
            digitalWrite(inBulb, HIGH);
            peopleIn++;
            Particle.publish("increment");
            lcd.setRGB(0, 204, 0);
            rightArrow();
            resetVars();
            resetScreen();
        }
    }
    //Store whether it's in or out to compare in the next iteration of the loop
    storeIn = in();
    storeOut = out();
}

//Turns lights on and off locally and online
int roomLights(String command){
    if(command == "off"){
        digitalWrite(light1,LOW);
        digitalWrite(light2,LOW);
        return 1;
    }
    else if(command == "on"){
        digitalWrite(light1,HIGH);
        digitalWrite(light2,HIGH);
        return 1;
    }
    return -1;
}

void lightsOn(){
    int light = roomLights("on");
}

void lightsOff(){
    int light = roomLights("off");
}

//Arrow and greeting animations
void rightArrow(){
    lcd.clear();
    lcd.setCursor(0,0);
    for(int s = 0; s < 16; s++){
        lcd.setCursor(s, 0);
        lcd.print(">");
        for(int i = 0; i < s; i++){
            lcd.setCursor(i, 0);
            lcd.print("-");
            delay(7);
        }
        lcd.setCursor(0,1);
        lcd.print(peopleIn);
        if(peopleIn == 1){
            lcd.setCursor(6, 1);
            lcd.print("Lights On!");
        } else {
            lcd.setCursor(8,1);
            lcd.print("Welcome!");  
        }
    }
    resetScreen();
}

void leftArrow(){
    lcd.clear();
    lcd.setCursor(0,0);
    for(int s = 15; s >= 0; s--){
        lcd.setCursor(s, 0);
        lcd.print("<");
        for(int i = 15; i > s; i--){
            lcd.setCursor(i, 0);
            lcd.print("-");
            delay(7);
        }
        lcd.setCursor(0,1);
        lcd.print(peopleIn);
        if(peopleIn == 0){
            lcd.setCursor(5, 1);
            lcd.print("Lights Off!");
        } else {
            lcd.setCursor(8,1);
            lcd.print("Goodbye!");
        }
    }
    resetScreen();
}

//Error displayed when a negative number of people are in the room
void errorNeg(){
    lcd.setRGB(255, 0 ,0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Error!");
    lcd.setCursor(0,1);
    lcd.print("Negative People.");
    delay(2000);
    resetScreen();
}

//Reset to default white screen that displays the number of people in the room
void resetScreen(){
    lcd.setRGB(255, 255, 255);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("People in Room: ");
    lcd.setCursor(0,1);
    lcd.print(peopleIn);
}

//Reset variables and turn off lights 
void resetVars(){
    walkingIn = false;
    walkingOut = false;
    digitalWrite(inBulb, LOW);
    digitalWrite(outBulb, LOW);
}

//First sensor activated because someone starts walking in
bool in(){
    if(digitalRead(sensor1) == HIGH){
        digitalWrite(inBulb,HIGH);   
    } else {
        digitalWrite(inBulb,LOW); 
    }     
    return digitalRead(sensor1) == HIGH && digitalRead(sensor2) == LOW;
}

//Second sensor activated because someone starts leaving
bool out(){
    if(digitalRead(sensor2) == HIGH){
        digitalWrite(outBulb, HIGH);      
    } else {
        digitalWrite(outBulb, LOW); 
    }
    return digitalRead(sensor2) == HIGH && digitalRead(sensor1) == LOW;
}
