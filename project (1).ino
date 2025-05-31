
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int sensor_pin = A0;       //Sensor Pin
int relay_pin = 2;         //Relay Pin
int ldrPin = A1;         // LDR Pin
int led = 3;
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setBacklight(HIGH);
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop()
{
  int moisture_data = analogRead(sensor_pin);
  
  if(moisture_data > 950)
  {
    Serial.println("No moisture, Soil is dry");
    digitalWrite(relay_pin, LOW);
    lcd.setCursor(0,0);
    lcd.print("Motor ON ");
    lcd.print(moisture_data);
  }
  else if(moisture_data >= 500 && moisture_data <= 950)
  {
    Serial.println("There is some moisture, Soil is medium");
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Motor OFF  ");
    lcd.print(moisture_data);
  }
  else if(moisture_data < 500)
  {
    Serial.println("Soil is wet");
    digitalWrite(relay_pin, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Motor OFF  ");
    lcd.print(moisture_data);
  }

  int ldr_data = analogRead(ldrPin);
  Serial.println("");
  Serial.print("Light Sensor ");
  Serial.print("Value = ");
  Serial.print(ldr_data);
  if(ldr_data <= 70)
  {
    Serial.println("Insufficient Light: ");
    Serial.println(ldr_data);
    digitalWrite(led, HIGH);
  }
  else
  {
    Serial.println("Sufficient Light: ");
    Serial.println(ldr_data);
    digitalWrite(led, LOW);
  }

  delay(100);
}

