#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>

#define SOUND_VELOCITY 0.034

const int SERVO_PIN = 2;

const int trigPinIn = 3;
const int echoPinIn = 4;

const int trigPinOut = 5;
const int echoPinOut = 21;

bool detectedIn = false;
bool detectedOut = false;

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

Servo gateServo;

int emptySpaces = 5;


enum motion {closed, gate_open};
motion GateState = closed;

void setup() {
  Serial.begin(115200);

  gateServo.attach(SERVO_PIN);

  pinMode(trigPinIn, OUTPUT);
  pinMode(echoPinIn, INPUT);

  pinMode(trigPinOut, OUTPUT);
  pinMode(echoPinOut, INPUT);

  lcd.init();                  
  lcd.backlight();

  GateState=closed; 
}

void loop() {

  detectedIn = checkUltrasonic(trigPinIn, echoPinIn);
  detectedOut = checkUltrasonic(trigPinOut, echoPinOut);
  
  lcd.setCursor(0, 1);
  lcd.print("Empty spaces: " + String(emptySpaces) + " ");

  switch (GateState)
  {
    case closed:
      lcd.setCursor(0, 0);
      lcd.print("Gate is closed");
      gateServo.write(90);
      
      if(detectedIn || detectedOut)
      {
        if(detectedIn)
        {
          if(emptySpaces<=0)
          {
            GateState = closed;
          }
          else
          {
            GateState = gate_open;
            emptySpaces--;
          }
        }
        else if(detectedOut)
        {
          if(emptySpaces>=5)
          {
            emptySpaces = 5;
            GateState=gate_open;
          }
          else
          {
            GateState=gate_open;
            emptySpaces++;
          }
        }
      }
    break;

    case gate_open:
      lcd.setCursor(0, 0);
      lcd.print("Gate is open  ");
      gateServo.write(0);
      if(!detectedIn && !detectedOut) {
        GateState = closed;
      }
      delay(1000);
    break;

    default:
    break;
  }

}

bool checkUltrasonic(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distanceCm = duration * SOUND_VELOCITY / 2;

  if(distanceCm > 0 && distanceCm <= 10) {
    return true;
  }
  return false;
}



