#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Servo myservo1;
Servo myservo2;

#define Password_Length 4

int ir_s1 = 2;
int ir_s2 = 4;

int ir_s3 = 1;
int ir_s4 = 0;

int Total = 3;
int Space ;

int flag1 = 0;
int flag2 = 0;

int Gas = 5;

char Data[Password_Length];
char Master[Password_Length] = "123";
byte data_count = 0, master_count = 0;

bool Pass_is_good;
bool door = false;
char customKey;

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {13, 12, 11};

Keypad customKeypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);

  pinMode(ir_s3, INPUT);
  pinMode(ir_s4, INPUT);

  pinMode(Gas, INPUT);

  myservo1.attach(3);
  myservo1.write(100);

  myservo2.attach(6);
  myservo2.write(100);

  lcd.begin(16, 2);
  lcd.print("Protected Door");
  loading("Loading");
  lcd.clear();

  Space=Total;
}

void loop()
{
  if (digitalRead (Gas) == HIGH)
  {
    lcd.setCursor (0, 0);
    lcd.print("  Gas Detected  ");
    lcd.setCursor (0, 1);
    lcd.print("    Stay Out    ");
  }
  else
  {
    if (door == true)
    {
      customKey = customKeypad.getKey();
      EntryExit();
      EmergencyExit();

      if (customKey == '#')
      {
        lcd.clear();
        lcd.print("Door is closed");
        delay(3000);
        door = false;
      }
    }
    else
      Open();
  }
}

void EntryExit()
{
  if (digitalRead (ir_s1) == LOW && flag1 == 0)
  {
    if (Space > 0)
    {
      flag1 = 1;
      if (flag2 == 0)
      {
        myservo1.write(0);
        Space = Space - 1;
      }
    }
    else
    {
      lcd.setCursor (0, 0);
      lcd.print(" Sorry Space not ");
      lcd.setCursor (0, 1);
      lcd.print("    Available    ");
      delay (1000);
      lcd.clear();
    }
  }

  if (digitalRead (ir_s2) == LOW && flag2 == 0 && Space < Total)
  {
    flag2 = 1;
    if (flag1 == 0 )
    {
      myservo1.write(0);
      Space = Space + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1)
  {
    delay (1000);
    myservo1.write(100);
    flag1 = 0, flag2 = 0;
    door = false;
  }

  lcd.setCursor (0, 0);
  lcd.print("Total Space: ");
  lcd.print(Total);

  lcd.setCursor (0, 1);
  lcd.print("Available: ");
  lcd.print(Space);
}

void EmergencyExit()
{
  if (digitalRead (ir_s3) == LOW && flag1 == 0)
  {
    flag1 = 1;
    if (flag2 == 0)
    {
      lcd.setCursor (0, 0);
      lcd.print("      Sorry     ");
      lcd.setCursor (0, 1);
      lcd.print("You cannot Enter");
      delay (1000);
      lcd.clear();
      flag1 = 0;
    }
  }

  if (digitalRead (ir_s4) == LOW && flag2 == 0 && Space < Total)
  {
    flag2 = 1;
    if (flag1 == 0)
    {
      myservo2.write(0);
      Space = Space + 1;
    }
  }

  if (flag1 == 1 && flag2 == 1)
  {
    delay (1000);
    myservo2.write(100);
    flag1 = 0, flag2 = 0;
    door = false;
  }

  lcd.setCursor (0, 0);
  lcd.print("Total Space: ");
  lcd.print(Total);

  lcd.setCursor (0, 1);
  lcd.print("Available: ");
  lcd.print(Space);
}

void loading (char msg[])
{
  lcd.setCursor(0, 1);
  lcd.print(msg);

  for (int i = 0; i < 9; i++)
  {
    delay(200);
    lcd.print(".");
  }
}

void clearData()
{
  while (data_count != 0)
    Data[data_count--] = 0;
  return;
}

void Open()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password");

  customKey = customKeypad.getKey();
  if (customKey)
  {
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }

  if (data_count == Password_Length - 1)
  {
    if (!strcmp(Data, Master))
    {
      lcd.clear();
      lcd.print(" Door is Open ");
      door = true;
      delay(500);
      loading("Waiting");
      lcd.clear();

      lcd.setCursor (0, 0);
      lcd.print("  Car  Parking  ");
      lcd.setCursor (0, 1);
      lcd.print("     System     ");
      delay (500);
    }
    else
    {
      lcd.clear();
      lcd.print(" Wrong Password ");
      door = false;
    }

    delay(1000);
    lcd.clear();
    clearData();
  }
}
