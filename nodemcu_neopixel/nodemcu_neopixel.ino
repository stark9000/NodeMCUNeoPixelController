#include <Adafruit_NeoPixel.h>
#include  <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);

#define PIN D8
Adafruit_NeoPixel PIXELS = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

#include <FirebaseESP8266.h>

#define WIFI_SSID  ""
#define WIFI_PASSWORD  ""
#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""

int LED;
FirebaseData FIREBASE;
int R, G, B = 0;

void setup()
{
  Serial.begin(9600);
  PIXELS.begin();
  Wire.begin(2, 0);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Innovator Park");
  lcd.setCursor(0, 1);
  lcd.print("    Quadrant");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting ...");
  }
  Serial.print("Connected !");
  delay(100);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  initx();
}

void loop()
{
  readData();
  setColorA(R, G, B);
}

void setColor(int LED, int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE, int delayValue)
{
  PIXELS.setPixelColor(LED, PIXELS.Color(RED_VALUE, GREEN_VALUE, BLUE_VALUE));
  PIXELS.show();
  delay(delayValue);
}

void setColorA(int RED_VALUE, int GREEN_VALUE, int BLUE_VALUE)
{
  for (int i = 0; i < 8; i++) {
    PIXELS.setPixelColor(i, PIXELS.Color(RED_VALUE, GREEN_VALUE, BLUE_VALUE));
    PIXELS.show();
  }
}

void writeData() {
  if (Firebase.ready()) {
    Firebase.setInt(FIREBASE, "R", 50);
    Firebase.setInt(FIREBASE, "G", 60);
    Firebase.setInt(FIREBASE, "B", 70);
  } else {
    // Serial.println("firebase error !");
  }
}
void readData() {
  if (Firebase.ready()) {
    if (Firebase.getInt(FIREBASE, "R" )) {
      if (FIREBASE.dataType() == "int")
        R = (FIREBASE.intData());
      //Serial.println(R);
    }

    if (Firebase.getInt(FIREBASE, "G" )) {
      if (FIREBASE.dataType() == "int")
        G = (FIREBASE.intData());
      //Serial.println(G);
    }

    if (Firebase.getInt(FIREBASE, "B" )) {
      if (FIREBASE.dataType() == "int")
        B = (FIREBASE.intData());
      //Serial.println(B);
    }
  } else {
    //Serial.println("firebase error !");
  }
}


void initx() {
  PIXELS.clear();
  for (LED = 0; LED <= 8; LED++)
  {
    setColor(LED, 255, 0, 0, 100);
  }
  for (LED = 0; LED <= 8; LED++)
  {
    setColor(LED, 0, 255, 255, 100);
  }
  for (LED = 0; LED <= 8; LED++)
  {
    setColor(LED, 255, 0, 255, 100);
  }
}
