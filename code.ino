# include <Servo.h> 
#define in1  9 //left side positive
#define in2  8 //left side negative
#define enA  10 //left side speed
#define in3  13 //right side positive
#define in4  12 //right side negative
#define enB  11 //right side speed
#define trigerPin 2  //ultrasonic trig pin
#define echoPin 3  // ultrasonic echo pin


#define irr  A4 //ir right
#define irl  A5 //ir left
int timen = 50;
int timet = 345 ;
int m = 0 ;
int time90 = 370 ;
//int speed1 ;
//int speed2  ;
int time1 = 10 ;
int time2 = 300 ;
float distance ;
//Servo myservo;
String voice;
int t,d;
char c ;
int i=0;

int Rirr  ;
int Rirl ;
//int x[500] ;
 
void setup()

{
  Serial.begin(9600);
  pinMode(trigerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enA,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(enB,OUTPUT);
  //myservo.attach(4);          // if you mean that by  servo in the pns pic
  pinMode(irr,INPUT);
  pinMode(irl,INPUT);
}

void forward() //move forward
{

  
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}
  void forward(int speed55) //move forward
{
  
  digitalWrite(enA,speed55);
  digitalWrite(enB,speed55);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("Forward");
}

void left() //rotate left
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
 digitalWrite(enA,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 analogWrite(enB,200);
 Serial.println("Left"); 
  
}
void right() //rotate right
{
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
  analogWrite(enA,200);
 digitalWrite(enB,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,LOW);
 Serial.println("Right");
 
}
void back() //move reverse
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 analogWrite(enA,255);
 digitalWrite(in4,LOW);
 digitalWrite(in3,HIGH);
 analogWrite(enB,255);
 Serial.println("back");
}

void stop() //stop
{
 digitalWrite(in1,LOW);
 digitalWrite(in2,LOW);
 digitalWrite(enA,LOW);
 digitalWrite(in3,LOW);
 digitalWrite(in4,LOW);
 digitalWrite(enB,LOW);
 Serial.println("Stop");
}

void back_left() //rotate left
{
  
 digitalWrite(in1,LOW);
 digitalWrite(in2,HIGH);
 analogWrite(enA,255);
 digitalWrite(in3,LOW);
 digitalWrite(in4,HIGH);
 analogWrite(enB,255);
 Serial.println("Left"); 
}
void back_right() //rotate right
{
  
 digitalWrite(in1,HIGH);
 digitalWrite(in2,LOW);
 analogWrite(enA,255);
 digitalWrite(in3,HIGH);
 digitalWrite(in4,LOW);
 analogWrite(enB,255);
 Serial.println("Right");
 
}


float measure( ){
  float dis, dur ;
 /* delay(500);*/
  digitalWrite(trigerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigerPin,LOW);
  
  dur = pulseIn (echoPin,HIGH);
  dis = (dur /2)* 0.0343 ;
  Serial.println(dis);
  /*delay(100);*/
  return dis ;   
}



void obsticale() { 
   distance = measure() ;
   if(distance < 30)
   {
     stop();
 //    myservo.write(0);
    back_right();
    delay(time90);
     distance = measure() ;
     if(distance < 30)
      {
        //myservo.write(180);

        back_right();
        delay(time90);
        delay(time90);

        distance = measure() ;
        if(distance < 30)  
        {stop();}
      }
      }     
      
      //myservo.write(90);
 }
 
/*
        
void xx()
{
  for(int f =0;f<500;f++)
  {
    x[f] =f;
    }
  
}

*/

void track() 
{
  //xx();
  while (1)
  {
 /* i = i + (1/100)  ;
  for(int f=0;f<500;f++)
  {
  if  (i ==x[f])
  {
    distance = measure();
    break;
  } 
   if(i<x[f]&& i>x[f-1])
   {break;}
  }

   */

   i++;
  if(i%5==0)
  {
    stop();
     distance = measure();
  }
     
    if(distance> 15)
    {


      
        Rirr = analogRead(irr) ;
        Rirl = analogRead(irl) ;
        Serial.println(Rirr);
        Serial.println(Rirl);
       
      
         if(Rirr > 100 &&Rirl < 100) 
           {
    
             left();
    
             while(1)
              {
               Rirr = analogRead(irr) ;
    
               Rirl = analogRead(irl) ;
               Serial.println(Rirr);
               Serial.println(Rirl);

//delay(5);
              if(Rirr < 100 )
                {break;}
              }

            }
            
else if(Rirr < 100 &&Rirl > 100 ) 
  {
    
        right();

  while(1)
{
  Rirr = analogRead(irr) ;
    Rirl = analogRead(irl) ;
    Serial.println(Rirr);
    Serial.println(Rirl);


//delay(5);
if(Rirl < 100)
{break;}
}   


    
  }
       else
        { forward();} 
    }
if(distance < 15)
  {
    stop();
    delay(2000);
   back_left();
   delay(timet);
   stop();
   delay(2000);
   distance =measure();
    if(distance > 60)
      {
      forward();
      delay(50);
      }
      if(distance < 60)
      {
        back_right();
        delay(timet);
        delay(timet);
        stop();
        delay(2000);
      }



   
  }
  
  }
}




  /*
void track(){
       int left_sensor_state = digitalRead(irl);
     int right_sensor_state = digitalRead(irr);
      
      if(right_sensor_state == LOW && left_sensor_state == HIGH)
      {
        Serial.println("fast_right");
        fast_right();
        delay(10);
      }
        if(right_sensor_state == HIGH && left_sensor_state == LOW)
      {
        Serial.println("turning left");
       fast_left();
        delay(10);
      }
        if(right_sensor_state == HIGH && left_sensor_state == HIGH)
      {
        Serial.println("going forward");
        forward(5);
        delay(10);
      }
     
      

} 
  
*/


void loop()
{
    
 track();
/*forward(5);
    delay(3000);

  right() ;
  delay(3000);
  left();
  delay(3000);
  Rirr= analogRead(irr);
 Rirl= analogRead(irl); 
  Serial.println("irr ");
  Serial.println( Rirr);
  delay(1000);
   Serial.println("irl ");
   Serial.println(  Rirl);
 
 

 
c = Serial.read();
  switch(c){
    case 'f': forward(); break;
    case 'b': back();   break;
    case 'l': left();   break;
    case 'r': right();  break;
    case 's': stop();   break;
    case 't': track(); break;
    Serial.println(c); 
    default:  break;}
 */
/*
   while(Serial.available())
  {
    delay(10);
    c=Serial.read();
    //voice +=c;
  }
  /*if(voice.length()>0)
  {
    Serial.println(voice); 
  } 
/*
switch(c){
  case 'f' :
  forward();
  obsticale();        
  Serial.println("forward");
  break;
  case 'b' :
  back();
   Serial.println("back");
  break; 
  }}
  case 'r' :
  right();
   Serial.println("right");
  break;
  case 'l' :
  left();
   Serial.println("left");
break;
  case 's' :
  stop();
   Serial.println("stop");
  break ;
  case 't' :
  track();
   Serial.println("track");
  break;
  } 
*/
  }

