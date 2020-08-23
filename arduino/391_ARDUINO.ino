/*
 * Timer 0 (controls pin 13, 4);
 * Timer 1 (controls pin 12, 11);
 * Timer 2 (controls pin 10, 9);
 * Timer 3 (controls pin 5, 3, 2);
 * Timer 4 (controls pin 8, 7, 6);
 * Timer 5 (controls pin 46,45,44);
 * 
 * Timer3
 * -Highest frequency is 1MHz
 * -Lowest frequency is 0.12Hz
 * -for .pwm(pin,duty,period): duty is 10bit val, so from 0-1023
 * 
 */
#include "TimerOne.h"
#include "FlexiTimer2.h" 
#include "TimerThree.h"
#include "TimerFour.h"
#include "TimerFive.h"
#include <Stepper.h>
#include <stdlib.h>
#include <SoftwareSerial.h>

// ====== Constants ====== 

// define frequencies for timers
#define frequency1  200  // 5ms
#define frequency2  200 
#define frequency3  150000       
#define frequency4  10      
#define frequency5  10   // 1 = 100, so if u want 1000 Hz (1ms), do 10 etc

// ====== Global Variables ====== 

//Bluetooth
SoftwareSerial ble(10, 7); // RX, TX
// white is TX on chip
// yellow goes to rx on chip
// blue vcc
// black is ground

// define duty cycles for timer, val/1024 = duty cycle
int duty3_2 = 0;  // duty cycle for timer3, pin 2
int duty3_3 = 256; 
int duty3_5 = 103;

// calculate periods for timers
long int period1 = (1000000/frequency1);
long int period2 = (1000/frequency2);
long int period3 = (1000000/frequency3); 
long int period4 = (1000000/frequency4); 
long int period5 = (1000000/frequency5); 

//Stepper Setup Variable
Stepper myStepper(300, 47, 51, 49, 53);          // initialize the stepper library
int Step_counter = 0;
double position = 0.0;
double Step_degree = 0.0;
int dir = 0;
int Step_start = 0;
int Step_countTarget = 0.0;
int Step_ready = 1;
double Step_current_pos = 0;                         

//Boost Control Setup Variables
float Vin = 0.0;
int dutycycle = 0;

//Voltage Sensor, pin A2
int VS_inputPin = A2;
int VS_count = 0;
float VS_sum = 0.0;
float R1 = 300000.0;                           // Resistor value 1, before node
float R2 =  77000.0;                           // Resistor value 2, after node

//Current Sensor, pin A3
int CS_inputPin = A3;
float CS_sum = 0.0;

//Wind Sensor, potentiometer input pin A4
int WS_inputPin = A4;
float WS_sum = 0.0;
float WS_val = 0.0;

//Power 
int PC_count = 0;
float PC_voltage = 0.0;
float PC_current = 0.0;
float PC_power = 0.0;

//MPPT
int boostup = -1;
float oldPower = 0.0;
                    
void setup()
{
  Serial.begin(9600);                // initialize serial port
  ble.begin(9600);

  Timer3.initialize(period3);                     // Set period
  //Timer3.attachInterrupt();                     // ISR setup
  Timer3.pwm(2, duty3_2);                         // Set pwm
  
  pinMode(VS_inputPin, INPUT);
  while(((analogRead(VS_inputPin)* (5.0/1023.0))/(R2/(R1+R2))) < 9){
    Serial.println("Waiting to reach 10V !");
  }

// ====== Timer(s) ====== 
  Timer1.initialize(period1);                     // Set period
  Timer1.attachInterrupt(AnalogSensor);          // ISR setup

  FlexiTimer2::set(period2, mppt);       // Set period & ISR
  FlexiTimer2::start();
  

  Timer4.initialize(period4);                     // Set period
  Timer4.attachInterrupt(BoostControl);              // ISR setup

  Timer5.initialize(period5);                     // Set period
  Timer5.attachInterrupt(WindSensor);             // ISR Setup
 
// ====== Stepper Motor ====== 
  myStepper.setSpeed(60);                         // Speed = 60rpm

// ====== Voltage & Current Sensors ====== 
  //pinMode(VS_inputPin, INPUT);
  pinMode(CS_inputPin, INPUT);
}

void loop() 
{ 
  if(Step_start == 1){    // If stepper is finished prev instruction, move
  StepperMotorControl();
  }
  
}



  
