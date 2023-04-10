#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int buttonPin = 7;
int buttonState = 0;
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //set up button
  pinMode(buttonPin, INPUT);

  if(!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  screen.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  screen.clearDisplay();

  // // Draw a single pixel in white
  // screen.drawPixel(10, 10, SSD1306_WHITE);

  // // Show the display buffer on the screen. You MUST call display() after
  // // drawing commands to make them visible on screen!
  // screen.display();

  // screen.drawPixel(20, 20, SSD1306_WHITE);

  // screen.display();
  // delay(2000);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  screen.setCursor((SCREEN_WIDTH/2)-40, SCREEN_HEIGHT/2);
  screen.println("Hello, World!");
  screen.drawRoundRect(10, 10, (SCREEN_WIDTH-20), SCREEN_HEIGHT-10, 2, WHITE);
  screen.display();

  buttonState = digitalRead(buttonPin);

  screen.clearDisplay();
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
      count++;
      Serial.print("pressed!");
      Serial.println(count);
      delay(2000);
  } 
}
