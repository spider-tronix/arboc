#include <Servo.h>
Servo myservo;  
void setup()
{
  myservo.attach(9);  
}

void loop() 
{

    myservo.write(0);              
    delay(1500);                      
 
    myservo.write(180);             
    delay(1500);                       
}
