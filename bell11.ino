#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <RTClib.h>

char t1[32];
char t2[32];
RTC_DS1307 rtc;
LiquidCrystal lcd(15, 16, 10, 11, 12, 13); // (rs, en, d4, d5, d6, d7)
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const int r = 14;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int h1;
int h2;
int h3;
int h4;
int h5;
int h6;
int h7;
int h8;
int h9;

int h11;
int h12;
int h13;
int h14;
int h15;
int h16;
int h17;
int h18;
int h19;

int m1;
int m2;
int m3;
int m4;
int m5;
int m6;
int m7;
int m8;
int m9;

int m11;
int m12;
int m13;
int m14;
int m15;
int m16;
int m17;
int m18;
int m19;


void setup()
{
  pinMode(r, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Wire.begin();
  rtc.begin();

  //rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  rtc.adjust(DateTime(2023, 6, 29, 12, 8, 0)); // Set the time manually
  if (!rtc.begin())
  {
    lcd.print("Couldn't find RTC");
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning())
  {
    lcd.print("RTC is NOT running!");
    Serial.println("RTC is NOT running!");
  }
  //rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  //rtc.adjust(DateTime(2023, 6, 9, 12, 27, 50)); // Set the time manually

  EEPROM.write(0x0100, 9);
  EEPROM.write(0x0101, 10);
  EEPROM.write(0x0102, 10);
  EEPROM.write(0x0103, 11);
  EEPROM.write(0x0104, 12);
  EEPROM.write(0x0105, 13);
  EEPROM.write(0x0106, 14);
  EEPROM.write(0x0107, 15);
  EEPROM.write(0x0108, 16);
  
  EEPROM.write(0x0109, 00);
  EEPROM.write(0x010A, 00);
  EEPROM.write(0x010B, 10);
  EEPROM.write(0x010C, 10);
  EEPROM.write(0x010D, 10);
  EEPROM.write(0x010E, 00);
  EEPROM.write(0x010F, 00);
  EEPROM.write(0x0110, 00);
  EEPROM.write(0x0111, 00);


  EEPROM.write(0x0112, 9);
  EEPROM.write(0x0113, 9);
  EEPROM.write(0x0114, 10);
  EEPROM.write(0x0115, 10);
  EEPROM.write(0x0116, 11);
  EEPROM.write(0x0117, 12);
  EEPROM.write(0x0118, 14);
  EEPROM.write(0x0119, 15);
  EEPROM.write(0x011A, 16);
  
  EEPROM.write(0x011B, 00);
  EEPROM.write(0x011C, 50);
  EEPROM.write(0x011D, 40);
  EEPROM.write(0x011E, 50);
  EEPROM.write(0x011F, 40);
  EEPROM.write(0x1110, 30);
  EEPROM.write(0x1111, 20);
  EEPROM.write(0x1112, 10);
  EEPROM.write(0x1113, 00);
}


int readNumericInput() 
{
  int num ;
  char key;
  while(1)
  {
    char key = keypad.getKey();
    if (isdigit(key)) 
    {
      num = key - '0'; // Convert the character to integer
      while (1) 
      {
        char nextKey = keypad.getKey();
        if (isdigit(nextKey)) 
        {
          num = num * 10 + (nextKey - '0'); // Combine the digits into a 2-digit number
          return num;
          break;
        }
      }
    }
  }
}

int chooseTimeFormat() 
{
  Serial.println("Choose time format");
  Serial.println("Hr:1 , Min:2");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Choose time format");
  lcd.setCursor(0, 1);
  lcd.print("Hr:1 , Min:2");
  while (1) {
    char key = keypad.getKey();
    
    if (key == '1') 
    {
      Serial.println("Enter new value");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter new value");
      int h = readNumericInput();
      Serial.print("Value entered: ");
      Serial.println(h);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Value entered: ");
      lcd.setCursor(0, 1);
      lcd.print(h);
      return(h);
      delay(1000);
      break;
    } else if (key == '2') 
    {
      Serial.println("Enter new value");
      lcd.println("Enter new value");
      int m = readNumericInput();
      Serial.print("Value entered: ");
      Serial.println(m);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Value entered: ");
      lcd.setCursor(0, 1);
      lcd.print(m);
      return(m);
      delay(1000);
      break;
    }
    else if (key == '#')
    {
      lcd.clear();
      break;
    }
  }
}


void loop()
{
  digitalWrite(r, HIGH);

  h1 = EEPROM.read(0x0100);
  h2 = EEPROM.read(0x0101);
  h3 = EEPROM.read(0x0102);
  h4 = EEPROM.read(0x0103);
  h5 = EEPROM.read(0x0104);
  h6 = EEPROM.read(0x0105);
  h7 = EEPROM.read(0x0106);
  h8 = EEPROM.read(0x0107);
  h9 = EEPROM.read(0x0108);
  m1 = EEPROM.read(0x0109);
  m2 = EEPROM.read(0x010A);
  m3 = EEPROM.read(0x010B);
  m4 = EEPROM.read(0x010C);
  m5 = EEPROM.read(0x010D);
  m6 = EEPROM.read(0x010E);
  m7 = EEPROM.read(0x010F);
  m8 = EEPROM.read(0x0110);
  m9 = EEPROM.read(0x0111);
  
  h11 = EEPROM.read(0x0112);
  h12 = EEPROM.read(0x0113);
  h13 = EEPROM.read(0x0114);
  h14 = EEPROM.read(0x0115);
  h15 = EEPROM.read(0x0116);
  h16 = EEPROM.read(0x0117);
  h17 = EEPROM.read(0x0118);
  h18 = EEPROM.read(0x0119);
  h19 = EEPROM.read(0x011A);
  m11 = EEPROM.read(0x011B);
  m12 = EEPROM.read(0x011C);
  m13 = EEPROM.read(0x011D);
  m14 = EEPROM.read(0x011E);
  m15 = EEPROM.read(0x011F);
  m16 = EEPROM.read(0x1110);
  m17 = EEPROM.read(0x1111);
  m18 = EEPROM.read(0x1112);
  m19 = EEPROM.read(0x1113);

  DateTime now = rtc.now();
  
  sprintf(t1,"%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  sprintf(t2, "%02d/%02d/%02d ", now.day(), now.month(), now.year());  
  Serial.print(F("Date/Time: "));
  Serial.println(t2);
  Serial.println(t1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(t2);
  lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
  lcd.setCursor(0, 1);
  lcd.print(t1);
  if (now.second() == 0)
  {
    if (strcmp(daysOfTheWeek[now.dayOfTheWeek()], "Mon") == 0 ||
        strcmp(daysOfTheWeek[now.dayOfTheWeek()], "Tue") == 0 ||
        strcmp(daysOfTheWeek[now.dayOfTheWeek()], "Wed") == 0 ||
        strcmp(daysOfTheWeek[now.dayOfTheWeek()], "Thu") == 0)
    {
      if ((now.minute() == m1) && (now.hour() == h1))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m2) && (now.hour() == h2))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m3) && (now.hour() == h3))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m4) && (now.hour() == h4))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m5) && (now.hour() == h5))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m6) && (now.hour() == h6))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m7) && (now.hour() == h7))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m8) && (now.hour() == h8))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m9) && (now.hour() == h9))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
    }
    if (strcmp(daysOfTheWeek[now.dayOfTheWeek()], "Fri") == 0)
    {
      if ((now.minute() == m11) && (now.hour() == h11))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m12) && (now.hour() == h12))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m13) && (now.hour() == h13))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m14) && (now.hour() == h14))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m15) && (now.hour() == h15))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m16) && (now.hour() == h16))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m17) && (now.hour() == h17))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m18) && (now.hour() == h18))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
      else if ((now.minute() == m19) && (now.hour() == h19))
      {
        digitalWrite(r, LOW);
        delay(1000);
        digitalWrite(r, HIGH);
        return;
      }
    }
  }
  char key = keypad.getKey();
  if(key=='*') 
  {
    Serial.println("Choose day");
    Serial.println("1.Mon-Thu  2.Fri");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Choose day:");
    lcd.setCursor(0, 1);
    lcd.print("1.Mon-Thu  2.Fri");
    while (1) 
    {
      char key = keypad.getKey();
      if(key=='1')
      {
        Serial.println("Choose Period");
        Serial.println("1,B=7,2,3,L=8,4,5,6,E=9");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Period:1,B=7,2,");
        lcd.setCursor(0, 1);
        lcd.print("3,L=8,4,5,6,E=9");
        delay(100);
        while (1) 
        {
          char key = keypad.getKey();     
          if(key=='1') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");
            while (1) 
            {
              char key = keypad.getKey();
  
              if((key=='1')||(key=='2')) 
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0100 : 0x0109, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0100 : 0x0109);    
                Serial.println(readValue);                
                lcd.print(readValue);           
              } 
              if (key == '#') 
              { 
                lcd.clear();
                return ;
              }         
            } 
          }
          else if(key=='2') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if((key=='1')||(key=='2')) 
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
    
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0101 : 0x010A, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0101 : 0x010A);    
                Serial.println(readValue);
                lcd.print(readValue); 
              } 
              if (key=='#') 
              {
                lcd.clear();
                return ;
              }  
            }
          }
          else if(key == '3') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2')) 
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0102 : 0x010B, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0102 : 0x010B);
                Serial.println(readValue);
                lcd.print(readValue);
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }  
            }
          }
          else if (key == '4') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);

                EEPROM.write(key == '1' ? 0x0103 : 0x010C, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0103 : 0x010C);
                Serial.println(readValue);
                lcd.print(readValue);
              } 
              if (key == '#') 
              {          
                lcd.clear();
                return ;
              }
            }
          }
          else if (key == '5') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0104 : 0x010D, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0104 : 0x010D);
                Serial.println(readValue);
                lcd.print(readValue);   
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
            } 
          }
          else if (key == '6') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0105 : 0x010E, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0105 : 0x010E);
                Serial.println(readValue);
                lcd.print(readValue);   
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }  
            }
          }
          else if (key == '7') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0106 : 0x010F, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0106 : 0x010F);
                Serial.println(readValue);
                lcd.print(readValue);
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '8') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0107 : 0x0110, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0107 : 0x0110);
                Serial.println(readValue);
                lcd.print(readValue);
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '9') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();

              if (key == '1' || key == '2') 
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0108 : 0x0111, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0108 : 0x0111);
                Serial.println(readValue);
                lcd.print(readValue); 
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }              
            }   
          }
          
        }
      }
      if (key=='2')
      {
        Serial.println("Choose Period");
        Serial.println("1,2,B=7,3,4,L=8,5,6,E=9");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Period:1,2,B=7,");
        lcd.setCursor(0, 1);
        lcd.print("3,L=8,4,5,6,E=9");
        while (1) 
        {
          char key = keypad.getKey();
      
          if (key == '1') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if (key == '1' || key == '2') 
              { 
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0112 : 0x011B, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0112 : 0x011B);
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;    
              }  
            }
          } 
          else if (key == '2') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0113 : 0x011C, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0113 : 0x011C);
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '3') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2')) 
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);

                EEPROM.write(key == '1' ? 0x0114 : 0x011D, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0114 : 0x011D);
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '4') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0115 : 0x011E, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0115 : 0x011E);
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '5') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
    
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0116 : 0x011F, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0116 : 0x011F);
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '6') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0117 : 0x1000, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0117 : 0x1000);    
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '7') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            { 
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              { 
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();    
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0118 : 0x1001, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0118 : 0x1001);    
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }
              
            }
          }
          else if (key == '8') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
             char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
    
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x0119 : 0x1002, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x0119 : 0x1002); 
                Serial.println(readValue);
                lcd.print(readValue);
                
                
              } 
              if (key == '#') 
              {
                lcd.clear();
                return;
              }  
            }
          }
          else if (key == '9') 
          {
            Serial.println("Choose time format\nHr:1 , Min:2");
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Choose time format");
            lcd.setCursor(0, 1);
            lcd.print("Hr:1 , Min:2");

            while (1) 
            {
              char key = keypad.getKey();
  
              if ((key == '1')||(key == '2'))  
              {
                Serial.println("Enter new value");
                lcd.clear();
                lcd.print("Enter new value");
                int value = readNumericInput();
    
                Serial.print("Value entered: ");
                Serial.println(value);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Value entered:");
                lcd.print(value);
    
                EEPROM.write(key == '1' ? 0x011A : 0x1003, value);
                Serial.print("Value written: ");
                lcd.setCursor(0, 1);
                lcd.print("Value written:");
                int readValue = EEPROM.read(key == '1' ? 0x011A : 0x1003);    
                Serial.println(readValue);
                lcd.print(readValue);                
              } 
              else if (key == '#') 
              {
                lcd.clear();
                return;
              }               
            }
          }
          else if (key == '#')
          {
            lcd.clear();
            return;
          }
        }
      }          
    }
  }
  delay(1000);
}