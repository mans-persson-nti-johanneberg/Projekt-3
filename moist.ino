

// Skapar variabler och konstanter
int moistureLevel = 0;
int moistPercentage = 0;
const int motorPin = 3;

//Inkluderar bibliotek och skapar displayen
#include "U8glib.h"
U8GLIB_SSD1306_128X64 oled(U8G_I2C_OPT_NONE);


void setup() {
  //Sätter bitrate till 9600
  Serial.begin(9600);

  //Sätter pinen som styr pumpen till output
  pinMode(motorPin, OUTPUT);
}

void loop() {
  //Motorn kör ej
  digitalWrite(motorPin, LOW);

  //Läser av värdet som fuktighetssensorn skickar och sätter värdet till variabeln
  moistureLevel = analogRead(A0);

  //Gör om värdet till 0-100 för att får procent
  moistPercentage = map(moistureLevel, 0, 1023, 100, 0);
  Serial.println(moistureLevel);
  draw();
  //Pausar så att det inte blir så många uppdateringar
  delay(2000);

    //När fuktigheten är under valfritt värde i detta fall 85% så körs pumpen
  while (moistPercentage <= 85){
    //Sätter på pump
    digitalWrite(motorPin, HIGH);

    //Får nytt värde för fuktighet så programmet vet när det är tillräckligt fuktigt och stänger av pumpen
    moistureLevel = analogRead(A0);
    moistPercentage = map(moistureLevel, 0, 1023, 100, 0);
    draw();
    delay(2000);
  }
  
}

//funktionen för att printa på displayen
void draw(void) {
  //Sätter fonten och font storlek
  oled.setFont(u8g_font_helvB10);
  //resettar displayen
  oled.firstPage();

  do {

    //prinat värdet för moistPercentage
    oled.drawStr(0, 13, (String(moistPercentage) + "%").c_str());
  } while (oled.nextPage());
}