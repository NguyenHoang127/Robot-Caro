#include <math.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#define pi 3.14159265
int theta_1;
int theta_2;
int Steps_X;
int Steps_Y;
float X,Y;
float X1,Y1;
float X2,Y2;
float X0,Y0;
float r;
char Ki_tu;


//Khai bao cac chan tin hieu dong co
AccelStepper stepperX(1, 2, 5);  //Chuyen dong t1
AccelStepper stepperY(1, 3, 6);  //Chuyen dong t2
AccelStepper stepperZ(1, 4, 7);  //Chuyen dong len xuong
#define Enable 8

void setup()
{
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(Enable,OUTPUT);
  
  stepperX.setMaxSpeed(1500); // Đặt tốc độ tối đa là 1000
  stepperX.setSpeed(750);   //950
  stepperX.setAcceleration(400);
  
  stepperY.setMaxSpeed(1500);
  stepperY.setSpeed(750);
  stepperY.setAcceleration(400);
  
  stepperZ.setMaxSpeed(4000);
  stepperZ.setSpeed(3000);
  stepperZ.setAcceleration(800);
}

void calculator1(float x, float y)
{
  float A;
  float B;
  double c2,s2,t2,c1,s1,t1,t_2,t_1;   
  float l2 = 245;
  float l3 = 180;
  float l01 = 125;
  float l02 = 150;

  //Tim toa do
  A = x + l01;
  B = y - l02;

  //Tinh toan goc quay huong (+)
  c2 = (pow(A,2) + pow(B,2) - pow(l2,2) - pow(l3,2))/(2*l2*l3);
  s2 = sqrt(abs(1 - pow(c2,2)));
  t2 = -(atan2(s2,c2)*180/pi);
  t_2 = -atan2(s2,c2);
  
  s1 = B*(l3*cos(t_2) + l2) - A*(l3*sin(t_2));
  c1 = A*(l3*cos(t_2) + l2) + B*(l3*sin(t_2));
  t1 = (atan2(s1,c1)*180/pi)+57;

  // Tinh toan goc buoc (+)
  Steps_X = (t1/0.1125)*3.9155;  //1 bước là 0.1125 độ
  Steps_Y = (t2/0.1125)*3.9155;
  delayMicroseconds(1);
  stepperX.moveTo(Steps_X);
  stepperY.moveTo(Steps_Y);
  if (Steps_X >0)
    {
      stepperX.setSpeed(750);
    }
   if (Steps_X <0)
    {
      stepperX.setSpeed(-750);
    }
    if (Steps_Y >0)
    {
      stepperY.setSpeed(750);
    }
   if (Steps_Y <0)
    {
      stepperY.setSpeed(-750);
    }
   
  while((stepperX.distanceToGo()!=0) || (stepperY.distanceToGo()!=0))
  {
    stepperX.runSpeedToPosition();
    stepperY.runSpeedToPosition();
  }
}

void calculator2(float x, float y)
{
  float A;
  float B;
  double c2,s2,t2,c1,s1,t1,t_2,t_1;   
  float l2 = 245;
  float l3 = 180;
  float l01 = 125;
  float l02 = 150;
  
  //Tim toa do
  A = x + l01;
  B = y - l02;

  //Tinh toan goc quay huong (-)
  c2 = (pow(A,2) + pow(B,2) - pow(l2,2) - pow(l3,2))/(2*l2*l3);
  s2 = sqrt(abs(1 - pow(c2,2)));
  t2 = (atan2(s2,c2)*180/pi);
  t_2 = atan2(s2,c2);
  
  s1 = B*(l3*cos(t_2) + l2) - A*(l3*sin(t_2));
  c1 = A*(l3*cos(t_2) + l2) + B*(l3*sin(t_2));
  t1 = (atan2(s1,c1)*180/pi)+57;

  //Tinh toan goc buoc (-)
  Steps_X = (t1/0.1125)*3.9155;  //1 bước là 0.1125 độ
  Steps_Y = (t2/0.1125)*3.9155;
  delayMicroseconds(1);
  stepperX.moveTo(Steps_X);
  stepperY.moveTo(Steps_Y);
  if (Steps_X >0)
    {
      stepperX.setSpeed(750);
    }
   if (Steps_X <0)
    {
      stepperX.setSpeed(-750);
    }
    if (Steps_Y >0)
    {
      stepperY.setSpeed(750);
    }
   if (Steps_Y <0)
    {
      stepperY.setSpeed(-750);
    }
   
  while((stepperX.distanceToGo()!=0) || (stepperY.distanceToGo()!=0))
  {
    stepperX.runSpeedToPosition();
    stepperY.runSpeedToPosition();
  }
}

//Quay hinh tron theo huong (+) 
void circle_1(float x0, float y0,float r) 
{
    for (float t = 0; t < pi/2; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator1(X,Y);
        delayMicroseconds(1);
     }
    for (float t = pi/2; t < pi; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator1(X,Y);
        delayMicroseconds(1);
     }
    for (float t = pi; t < 3*pi/2; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator1(X,Y);
        delayMicroseconds(1);
     }
    for (float t = 3*pi/2; t < 2.5*pi; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator1(X,Y);
        delayMicroseconds(1);
     }
}

//Quay hinh tron theo huong (-) 
void circle_2(float x0, float y0, float r)
{
  for (float t = 0; t < pi/2; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator2(X,Y);
        delayMicroseconds(1);
     }
    for (float t = pi/2; t < pi; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator2(X,Y);
        delayMicroseconds(1);
     }
    for (float t = pi; t < 3*pi/2; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator2(X,Y);
        delayMicroseconds(1);
     }
    for (float t = 3*pi/2; t < 2.5*pi; t = t+0.01)
     { 
        X = x0 +r*cos(t) ;
        Y = y0 +r*sin(t);
        calculator2(X,Y);
        delayMicroseconds(1);
     }
}

//Ve dau X
void cross1(float x0, float y0,float r)
{
  for (float t = 0; t < r*sqrt(2); t = t+0.1)
      { 
         X = x0 +r/sqrt(2)-t ;
         Y = y0 +r/sqrt(2)-t ;
         calculator1(X,Y);
         delayMicroseconds(1);
      }
}


void cross2(float x0, float y0,float r)
{
  for (float t = 0; t < r*sqrt(2); t = t+0.1)
      { 
         X = x0 -r/sqrt(2)+t ;
         Y = y0 +r/sqrt(2)-t ;
         calculator1(X,Y);
         delayMicroseconds(1);
      }
}

void cross3(float x0, float y0,float r)
{
  for (float t = 0; t < r*sqrt(2); t = t+0.1)
      { 
         X = x0 +r/sqrt(2)-t ;
         Y = y0 +r/sqrt(2)-t ;
         calculator2(X,Y);
         delayMicroseconds(1);
      }
}

void cross4(float x0, float y0,float r)
{
  for (float t = 0; t < r*sqrt(2); t = t+0.1)
      { 
         X = x0 -r/sqrt(2)+t ;
         Y = y0 +r/sqrt(2)-t ;
         calculator2(X,Y);
         delayMicroseconds(1);
      }
}


//Ve duong thang giua hai diem
void line(float x0,float y0,float x1, float y1)
{
  for (float t = 0; t<1; t=t+0.008)
  {
    X = x0 + (x1-x0)*t;
    Y = y0 + (y1-y0)*t;
    calculator1(X,Y);
    delayMicroseconds(1);
  }
}

//Quay xuong theo truc z
void godown()
{
  stepperZ.setCurrentPosition(0);
  while(stepperZ.currentPosition() != 4600) //buoc ren 8mm
        {
           stepperZ.setSpeed(3000); 
           stepperZ.runSpeed();
        }
}

//Quay len theo truc z
void goup()
{
  stepperZ.setCurrentPosition(0);
  while(stepperZ.currentPosition() != -4600) 
         {
            stepperZ.setSpeed(-3000); 
            stepperZ.runSpeed();
         }
}

//Quay goc truc x
void gocquayx(float gocx)
{
  Steps_X = (gocx/0.1125)*3.92;
  stepperX.moveTo(Steps_X);
  if (Steps_X >0)
    {
      stepperX.setSpeed(1400);
    }
   if (Steps_X <0)
    {
      stepperX.setSpeed(-1400);
    }
   while((stepperX.distanceToGo()!=0))
   {
    stepperX.runSpeedToPosition();
   }  
}

//Quay goc truc y
void gocquayy(float gocy)
{
  Steps_Y = (gocy/0.1125)*3.92;
  stepperY.moveTo(Steps_Y);
  if (Steps_Y >0)
    {
      stepperY.setSpeed(1400);
    }
   if (Steps_Y <0)
    {
      stepperY.setSpeed(-1400);
    }
   while((stepperY.distanceToGo()!=0))
   {
    stepperY.runSpeedToPosition();
   }  
}

//Set vi tri tro ve
void backhome()
{
  stepperX.moveTo(0);
  stepperY.moveTo(0);
  stepperX.setSpeed(2500);
  stepperY.setSpeed(2500);
  while((stepperX.distanceToGo()!=0) || (stepperY.distanceToGo()!=0))
         {
             stepperX.runSpeedToPosition();
             stepperY.runSpeedToPosition();
         }
}

//Set vi tri ban dau
void statehome()
{
  stepperX.setCurrentPosition(0); 
  stepperY.setCurrentPosition(0); 
  stepperZ.setCurrentPosition(0); 
}


void loop()
{

  Serial.println(" Chọn kích thước mà bạn muốn đánh "); //3x3,4x4,5x5,6x6,7x7,8x8,9x9 Vd3x3: 3
  while(Serial.available()==0) {};       
  int mode = Serial.parseInt();
  Serial.println(mode);

  while(mode == 3)
    {
      while(Serial.available()==0) {}; 
      r = sqrt(pow(300,2)/pow(3,2))*0.7/2;
      Serial.println(r);
      Serial.println(" Nhập kí tự mà bạn muốn đánh ");
      Ki_tu = Serial.read();
      while(Ki_tu == 'o')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/3;
            int i = (u-1)%3;
            X0 = 100*(i+0.5);
            Y0 = 100*(j+0.5);
            X = X0+r;
            Y = Y0;
            if(u<6)
              {
                statehome();
                calculator1(X,Y);
                godown();
                circle_1(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                calculator2(X,Y);
                godown();
                circle_2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
            while(Ki_tu == 'x')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/3;
            int i = (u-1)%3;
            X0 = 100*(i+0.5);
            Y0 = 100*(j+0.5);
            if(u<6)
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator1(X1,Y1);
                godown();
                cross1(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator1(X2,Y2);
                godown();
                cross2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator2(X1,Y1);
                godown();
                cross3(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator2(X2,Y2);
                godown();
                cross4(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
      
      
  }

  while(mode == 5)
    {
      while(Serial.available()==0) {}; 
      r = sqrt(pow(300,2)/pow(5,2))*0.6/2;
      Serial.println(r);
      Serial.println(" Nhập kí tự mà bạn muốn đánh ");
      Ki_tu = Serial.read();
      while(Ki_tu == 'o')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/5;
            int i = (u-1)%5;
            X0 = 60*(i+0.5);
            Y0 = 60*(j+0.5);
            X = X0+r;
            Y = Y0;
            if(u<15)
              {
                statehome();
                calculator1(X,Y);
                godown();
                circle_1(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                calculator2(X,Y);
                godown();
                circle_2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
            while(Ki_tu == 'x')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/5;
            int i = (u-1)%5;
            X0 = 60*(i+0.5);
            Y0 = 60*(j+0.5);
            if(u<15)
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator1(X1,Y1);
                godown();
                cross1(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator1(X2,Y2);
                godown();
                cross2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator2(X1,Y1);
                godown();
                cross3(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator2(X2,Y2);
                godown();
                cross4(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
      
      
  }

  while(mode == 7)
    {
      while(Serial.available()==0) {}; 
      r = sqrt(pow(300,2)/pow(7,2))*0.65/2;
      Serial.println(r);
      Serial.println(" Nhập kí tự mà bạn muốn đánh ");
      Ki_tu = Serial.read();
      while(Ki_tu == 'o')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/7;
            int i = (u-1)%7;
            X0 = 300/7*(i+0.5);
            Serial.println(X0);
            Y0 = 300/7*(j+0.5);
            Serial.println(Y0);
            X = X0+r;
            Y = Y0;
            if(u<29)
              {
                statehome();
                calculator1(X,Y);
                godown();
                circle_1(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                calculator2(X,Y);
                godown();
                circle_2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
            while(Ki_tu == 'x')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/7;
            int i = (u-1)%7;
            X0 = 300/7*(i+0.5);
            Y0 = 300/7*(j+0.5);
            if(u<29)
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator1(X1,Y1);
                godown();
                cross1(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator1(X2,Y2);
                godown();
                cross2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator2(X1,Y1);
                godown();
                cross3(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator2(X2,Y2);
                godown();
                cross4(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
        
  }

 while(mode == 9)
    {
      while(Serial.available()==0) {}; 
      r = sqrt(pow(300,2)/pow(9,2))*0.6/2;
      Serial.println(r);
      Serial.println(" Nhập kí tự mà bạn muốn đánh ");
      Ki_tu = Serial.read();
      while(Ki_tu == 'o')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/9;
            int i = (u-1)%9;
            X0 = 300/9*(i+0.5);
            Serial.println(X0);
            Y0 = 300/9*(j+0.5);
            Serial.println(Y0);
            X = X0+r;
            Y = Y0;
            if(u<40)
              {
                statehome();
                calculator1(X,Y);
                godown();
                circle_1(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                calculator2(X,Y);
                godown();
                circle_2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
            while(Ki_tu == 'x')
      {
          Serial.println(" Nhập ô mà bạn muốn đánh ");
          int u = Serial.parseInt();
          if(u==0){}
          else
          {
            int j = (u-1)/9;
            int i = (u-1)%9;
            X0 = 300/9*(i+0.5);
            Y0 = 300/9*(j+0.5);
            if(u<40)
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator1(X1,Y1);
                godown();
                cross1(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator1(X2,Y2);
                godown();
                cross2(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
            else
              {
                statehome();
                X1 = X0 +r/sqrt(2) ;
                Y1 = Y0 +r/sqrt(2);
                calculator2(X1,Y1);
                godown();
                cross3(X0,Y0,r);
                goup();
                X2 = X0 -r/sqrt(2) ;
                Y2 = Y0 +r/sqrt(2);
                calculator2(X2,Y2);
                godown();
                cross4(X0,Y0,r);
                goup();
                backhome();
                delay(1000);
              }
          }   
      }
        
  }
}  
