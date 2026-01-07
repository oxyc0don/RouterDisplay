#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String serialBuffer = "";

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22); // SDA, SCL

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 nicht gefunden");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Bereit...");
  display.display();

  Serial.println("ESP32 bereit. Text senden!");
}

void loop() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      showText(serialBuffer);
      serialBuffer = "";
    } else {
      serialBuffer += c;
    }
  }
}

void showText(String text) {
  display.clearDisplay();
  display.setCursor(0, 0);

  int lineHeight = 8;
  int maxLines = SCREEN_HEIGHT / lineHeight;
  int line = 0;

  while (text.length() > 0 && line < maxLines) {
    String lineText = text.substring(0, 21);
    text.remove(0, 21);

    display.println(lineText);
    line++;
  }

  display.display();
}
