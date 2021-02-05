#include <Servo.h>

 

#define WHITE_VAL  700
#define BLACK_VAL  600

 

Servo MyservoLeft;  // create servo object for Left Motor
Servo MyservoRight; // create servo object for Right Motor

 

int Analog1 = A0;
int Analog2 = A1;
int Analog3 = A2;
int Analog4 = A3;
int Analog5 = A4;

 

int middle_sensor      = 0;
int left_sensor        = 0;
int most_left_sensor   = 0;
int right_sensor       = 0;
int most_right_sensor  = 0;

 

int node_count = 0;
boolean node_count_flag = false;
boolean node_oper_flag = false;

 

unsigned int node_counter = 0;

 

//1 - Right, 2 - Left, 3 - Stop
//unsigned int grid_track[5] = [

 

void setup()
{
  Serial.begin(9600);
  MyservoLeft.attach(12);  // attaches the servo on pin 9 to the servo object
  MyservoRight.attach(13);
}

 

void loop() 
{  
  most_left_sensor  = analogRead(Analog1);
  
  left_sensor       = analogRead(Analog2);

 

  middle_sensor     = analogRead(Analog3);

 

  right_sensor      = analogRead(Analog4);

 

  most_right_sensor = analogRead(Analog5);

 

//  Serial.print("Sensor 1:");
//  Serial.println(most_left_sensor);
//  Serial.print("Sensor 2:");
//  Serial.println(left_sensor);
//  Serial.print("Sensor 3:");
//  Serial.println(middle_sensor);
//  Serial.print("Sensor 4:");
//  Serial.println(right_sensor);  
//  Serial.print("Sensor 5:");
//  Serial.println(most_right_sensor);

 

 if(((most_left_sensor < BLACK_VAL)&&(left_sensor < BLACK_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor < BLACK_VAL) && (most_right_sensor < BLACK_VAL))||
    ((most_left_sensor < BLACK_VAL)&&(left_sensor < BLACK_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL))||
    ((most_left_sensor > WHITE_VAL)&&(left_sensor > WHITE_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor < BLACK_VAL) && (most_right_sensor < BLACK_VAL))||
    ((most_left_sensor > WHITE_VAL)&&(left_sensor > WHITE_VAL)&&(middle_sensor > WHITE_VAL) && (right_sensor < BLACK_VAL) && (most_right_sensor < BLACK_VAL))||
    ((most_left_sensor < BLACK_VAL)&&(left_sensor < BLACK_VAL)&&(middle_sensor > WHITE_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL)))
  {
    if(node_count_flag == false)
    {
      node_count++;
      node_count_flag = true;
      node_oper_flag = false;
    }
  }
  else
  {
    node_count_flag = false;
  }
  Serial.print("Node :");
  Serial.println(node_count);

 

  if(((node_count == 2)||
      (node_count == 5))&&
      (node_oper_flag == false))
  {
    //Right Turn on Grid
    //Serial.println("Turning");
    move_forward();
    delay(200);
    turn_right();
    stop_robot();
    delay(100);
    node_oper_flag = true;
  }
  else if(((node_count == 3)||
           (node_count == 4))&&
           (node_oper_flag == false))
  {
    //Left Turn on Grid
    move_forward();
    delay(200);
    turn_left();
    stop_robot();
    delay(100);;
    node_oper_flag = true;
  }
  else if((node_count == 7) && (node_oper_flag == false))
  {
    //Stop Robot
    stop_motor();
    node_oper_flag = true;
  }  
  else
  {
    
  }
  line_trace();
 

 

}

 

void line_trace()
{
  if((most_left_sensor > WHITE_VAL)&&(left_sensor > WHITE_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL))
  {
    Serial.println("F");
    move_forward();
  }
  else if((most_left_sensor > WHITE_VAL) && (left_sensor > WHITE_VAL)&&(middle_sensor > WHITE_VAL) && ((right_sensor < BLACK_VAL) || (most_right_sensor < BLACK_VAL)))
  {
   Serial.println("L");
    move_left();
  }
  else if((most_left_sensor > WHITE_VAL)&&(left_sensor > WHITE_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor < BLACK_VAL) && (most_right_sensor < BLACK_VAL))
  {
    Serial.println("SL");
    move_left();
  }
  else if(((most_left_sensor < BLACK_VAL)||(left_sensor < BLACK_VAL))&&(middle_sensor > WHITE_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL))
  {
    Serial.println("R");
    move_right();
  }
  else if((most_left_sensor < BLACK_VAL)&&(left_sensor < BLACK_VAL)&&(middle_sensor < BLACK_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL))
  {
    Serial.println("SR");
    move_right();
  }
//  else if((most_left_sensor > WHITE_VAL)&&(left_sensor > WHITE_VAL)&&(middle_sensor > WHITE_VAL) && (right_sensor > WHITE_VAL) && (most_right_sensor > WHITE_VAL))
//  {
//    Serial.println("rev");
//    move_reverse();
//  }
  else
  {
    Serial.println("Def");
    move_forward();
  }
  delay(20);
}

 

void move_forward()
{
  MyservoRight.writeMicroseconds(1700);
  MyservoLeft.writeMicroseconds(1300);
  delay(10);
}

 

void move_left()
{
  MyservoRight.writeMicroseconds(1700);
  MyservoLeft.writeMicroseconds(1500);
  delay(10);
}

 

void move_right()
{
  MyservoRight.writeMicroseconds(1500);
  MyservoLeft.writeMicroseconds(1300);
  delay(10);
}

 

void move_reverse()
{
  MyservoRight.writeMicroseconds(1300);
  MyservoLeft.writeMicroseconds(1700);
  delay(10);
}

 

void turn_right()
{
  MyservoRight.writeMicroseconds(1700);
  MyservoLeft.writeMicroseconds(1700);
  delay(600);
}

 

void turn_left()
{
  MyservoRight.writeMicroseconds(1300);
  MyservoLeft.writeMicroseconds(1300);
  delay(600);
}

 

void stop_robot()
{
  MyservoRight.writeMicroseconds(1483);
  MyservoLeft.writeMicroseconds(1500);
}
void stop_motor()
{
  MyservoRight.detach();
  MyservoLeft.detach();
}
 
