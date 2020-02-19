#include <Servo.h>
#include <SPI.h>
#include<stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include<avr/interrupt.h>

//PIN MAPPINGS
//132465

/*
 * Serpentine lateral plane:
 * a=0.6*pi
 * b=2*pi
 * c=0
 * 
 *  a=0.75*pi;
    b=3.5*pi;
    c=-0.2*pi;
    num_segments = 5;

          a=1.5*pi;
          b=3*pi;
          c=0*pi;
 */
 /*
  * Rolling gait:
  * a=0.9*pi
  * b=1*pi
  * c=0
  * n=8
  * phase diff += 0.1
  * add pi to switch direction
  */
 
// Define servo objects for the snake segments
Servo s1; 
Servo s2;
Servo s3;
Servo s4; 
Servo s5;
Servo s6;

int gait=1;
int direc=2;
const float pi = 3.141593;
int counter = 0; 
int frequency = 1; 
int startPause = 2000; 
int data[2];
int flag=0;

char tx='1';

float a = 0.5*pi;                                   //Ampli Coeff
float b = 1*pi;                                     //Curve Coeff      
float c = 0;                                        //Turn Coeff
float num_segments = 8;
float gamma=-c/num_segments;
float beta=b/num_segments;
float alpha=a*abs(sin(beta/2));
unsigned long previousMillis = 0;
long interval = 4;

void setup() 
{
  // Attach segments to pins  
   s1.attach(2); //blue left - 1st servo
   s2.attach(3); //black right - 2nd servo
   s3.attach(4); //violet right - 3rd servo 
   s4.attach(5); //black left - 4th servo 
   s5.attach(6); //white left - 5th servo 
   s6.attach(7); //blue right - 6th servo 
 
//Put snake in starting position
   s1.write(90);
   s2.write(90);
   s3.write(90);
   s4.write(90);
   s5.write(90);
   s6.write(90-13); 
 
   delay(startPause);
   previousMillis = millis();
}
void loop() 
{
        //Serpentine gait
          a=0.9*pi;
          b=3*pi;
          c=0*pi;
          num_segments = 8;2
          gamma=-c/num_segments;
          beta=b/num_segments;
          alpha=a*abs(sin(beta/2));
          interval = 3;

          for(counter = 0; counter < 360;) 
          {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= interval)
            {
              previousMillis = currentMillis;
              s1.write(90 + (alpha*sin(frequency*counter*pi/180+1*beta)+gamma)*180/pi);
              s2.write(90 + (alpha*sin(frequency*counter*pi/180+2*beta+pi/2)+gamma)*180/pi);
              s3.write(90 + (alpha*sin(frequency*counter*pi/180+3*beta)+gamma)*180/pi);
              s4.write(90 + (alpha*sin(frequency*counter*pi/180+4*beta+pi/2)+gamma)*180/pi);
              s5.write(90 + (alpha*sin(frequency*counter*pi/180+5*beta)+gamma)*180/pi);
              s6.write(90 + (alpha*sin(frequency*counter*pi/180+6*beta+pi/2)+gamma)*180/pi);
              counter += 1;
            }       
          }       
}
