
#define aPin 2  //        
#define bPin 3  //      _____
#define cPin 4  //     |  A  |
#define dPin 5  //   F |_____| B
#define ePin 6  //     |  G  |
#define fPin 7  //   E |_____| C
#define gPin 8  //        D     O dot

#define c1Pin 9  // CommLOW pin for digit 1
#define c2Pin 10 // Common pin for digit 2
#define c3Pin 11 // Common pin for digit 3
#define c4Pin 12 // Common pin for digit 4

#define bt_up     A0

long Counter=0;
byte current_digit;
int flag1=0, flag2=0, timer=0;

int Gas = 1;
int redLed = 0;
int Buzz = 13;

int Common = 1; //<Common=1; for Common anode> <Common=0; for Common cathode>
int On, Off, Off_C; 
int DTime = 15; // Display timer

void setup() {
 pinMode(bt_up,INPUT);
 pinMode(aPin, OUTPUT);
 pinMode(bPin, OUTPUT);
 pinMode(cPin, OUTPUT);
 pinMode(dPin, OUTPUT);
 pinMode(ePin, OUTPUT); 
 pinMode(fPin, OUTPUT);
 pinMode(gPin, OUTPUT);

 pinMode(c1Pin, OUTPUT);
 pinMode(c2Pin, OUTPUT);
 pinMode(c3Pin, OUTPUT);
 pinMode(c4Pin, OUTPUT);
  disp_off();
  TCCR1A = 0;
  TCCR1B = 1;  // enable Timer1 with prescaler = 1 ( 16 ticks each 1 µs)
  TCNT1  = 0;  // set Timer1 preload value to 0 (reset)
  TIMSK1 = 1;  // enable Timer1 overflow interrupt
 pinMode(Gas, INPUT);
 pinMode (13 , OUTPUT);
}
ISR(TIMER1_OVF_vect)   // Timer1 interrupt service routine (ISR)
{
  disp_off();  // turn off the display

  switch (current_digit)
  {
    case 1:
      showNumber((Counter/1000)%10);

digitalWrite(c1Pin, LOW);
      break;

    case 2:
     showNumber((Counter/100)%10);
/*digitalWrite(c2Pin, Common);
delay(DTime);*/
digitalWrite(c2Pin, LOW);
      break;

    case 3:
      showNumber((Counter/10)%10);
/*digitalWrite(c3Pin, Common);
delay(DTime);*/
digitalWrite(c3Pin, LOW);
      break;

    case 4:
      showNumber(Counter%10);

digitalWrite(c4Pin, LOW);
  }

  current_digit = (current_digit % 4) + 1;
}

void loop() {
  
  if(digitalRead(Gas) == HIGH){
   
    //" Gas Detected "
    digitalWrite(13, HIGH);
    digitalWrite(0 , HIGH);
    delay(80);
    digitalWrite(0 , LOW);
    delay(80);
    
   
  }
else{
 
  digitalWrite(13 , LOW);
  digitalWrite(0 ,HIGH);
  delay(500);
}

  if (flag1 == 1 && flag2 == 1)
  {
  
    flag1 = 0, flag2 = 0;
   
  }
if(digitalRead (bt_up) == 0){ 
 Counter++;  // increment 'count' by 1
    if(Counter>=9999)
      Counter = 0;
    delay(200);  // wait 200 milliseconds
}
}


void showNumber(int x){
  
   switch(x){
     case 1: one();   break;
     case 2: two();   break;
     case 3: three(); break;
     case 4: four();  break;
     case 5: five();  break;
     case 6: six();   break;
     case 7: seven(); break;
     case 8: eight(); break;
     case 9: nine();  break;
     default: zero(); break;
   }
}

void one(){
  digitalWrite( aPin, HIGH); //      
  digitalWrite( bPin,LOW);  //      |
  digitalWrite( cPin,LOW);  //      |
  digitalWrite( dPin,HIGH); //      |
  digitalWrite( ePin,HIGH); //      |
  digitalWrite( fPin, HIGH);
  digitalWrite( gPin, HIGH);
  
}

void two(){
  digitalWrite( aPin,LOW);  //  ____
  digitalWrite( bPin,LOW);  //      | 
  digitalWrite( cPin,HIGH); //  ____|
  digitalWrite( dPin,LOW);  // |     
  digitalWrite( ePin,LOW);  // |____
  digitalWrite( fPin, HIGH);
  digitalWrite( gPin, On);

}

void three(){
  digitalWrite( aPin,LOW);  //  ____
  digitalWrite( bPin,LOW);  //      |
  digitalWrite( cPin,LOW);  //  ____|
  digitalWrite( dPin,LOW);  //      |
  digitalWrite( ePin,HIGH); //  ____|
  digitalWrite( fPin,HIGH); 
  digitalWrite( gPin,LOW);

}

void four(){
  digitalWrite( aPin, HIGH); //  
  digitalWrite( bPin, LOW);  // |    |
  digitalWrite( cPin, LOW);  // |____|
  digitalWrite( dPin, HIGH); //      |
  digitalWrite( ePin, HIGH); //      |
  digitalWrite( fPin, LOW);
  digitalWrite( gPin, LOW);

}

void five(){
  digitalWrite( aPin,LOW);  //  ____
  digitalWrite( bPin,HIGH); // |
  digitalWrite( cPin,LOW);  // |____
  digitalWrite( dPin,LOW);  //      |
  digitalWrite( ePin,HIGH); //  ____|
  digitalWrite( fPin, LOW);  
  digitalWrite( gPin,LOW);
  
}

void six(){
  digitalWrite( aPin,LOW);  //  ____
  digitalWrite( bPin,HIGH); // |
  digitalWrite( cPin,LOW);  // |____
  digitalWrite( dPin,LOW);  // |    |
  digitalWrite( ePin,LOW);  // |____|
  digitalWrite( fPin,LOW);
  digitalWrite( gPin,LOW);
 
}

void seven(){
  digitalWrite( aPin,LOW);   //  ____
  digitalWrite( bPin,LOW);   //      |
  digitalWrite( cPin,LOW);   //      |
  digitalWrite( dPin, HIGH); //      |
  digitalWrite( ePin, HIGH); //      |
  digitalWrite( fPin, HIGH);
  digitalWrite( gPin, HIGH);
  
}

void eight(){
  digitalWrite( aPin, LOW); //  ____
  digitalWrite( bPin, LOW); // |    |
  digitalWrite( cPin, LOW); // |____|
  digitalWrite( dPin, LOW); // |    |
  digitalWrite( ePin, LOW); // |____|
  digitalWrite( fPin, LOW); 
  digitalWrite( gPin, LOW); 
  
}

void nine(){
  digitalWrite( aPin, LOW);  //  ____
  digitalWrite( bPin, LOW);  // |    |
  digitalWrite( cPin, LOW);  // |____|
  digitalWrite( dPin, LOW);  //      |
  digitalWrite( ePin, HIGH); // ____|
  digitalWrite( fPin, LOW); 
  digitalWrite( gPin, LOW);
 
}

void zero(){                 
  digitalWrite( aPin, LOW); //  ____
  digitalWrite( bPin, LOW); // |    |
  digitalWrite( cPin, LOW); // |    |
  digitalWrite( dPin, LOW); // |    |
  digitalWrite( ePin, LOW); // |____|
  digitalWrite( fPin, LOW); 
  digitalWrite( gPin, HIGH);  
  
}

void disp_off()
{
   digitalWrite(c1Pin, HIGH);
   digitalWrite(c2Pin, HIGH);
   digitalWrite(c3Pin, HIGH);
   digitalWrite(c4Pin, HIGH);
}
