#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int interruptPin = 2;
int slide = 0;
int previousSlide = slide;

int center_x = SCREEN_WIDTH / 2;   // X coordinate of the center
int center_y = SCREEN_HEIGHT / 2;  // Y coordinate of the center
float angle = 0;                   // Current angle of the smaller circle for Planet Demo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //set up button


  if (!screen.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), test, RISING);

  screen.display();
  delay(2000);  // Pause for 2 seconds

  // Clear the buffer
  screen.clearDisplay();
}

void loop() {
  // screen.setTextSize(1);
  // screen.setTextColor(WHITE);
  // screen.setCursor((SCREEN_WIDTH/2)-40, SCREEN_HEIGHT/2);
  // screen.println("Hello, World!");
  // screen.drawRoundRect(10, 10, (SCREEN_WIDTH-20), SCREEN_HEIGHT-10, 2, WHITE);
  if (slide == 0) {
    previousSlide = slide;
    drawCircleFrame(10, 10, 117, 10, 150);
    drawCircleFrame(12, 9, 115, 11, 125);
    drawCircleFrame(18, 8, 109, 12, 75);
    drawCircleFrame(64, 5, 64, 15, 25);
    drawCircleFrame(109, 8, 18, 12, 75);
    drawCircleFrame(115, 9, 12, 11, 125);
    drawCircleFrame(117, 10, 10, 10, 150);
    drawCircleFrame(115, 11, 12, 9, 125);
    drawCircleFrame(109, 12, 18, 8, 75);
    drawCircleFrame(64, 15, 64, 5, 25);
    drawCircleFrame(18, 12, 109, 8, 75);
    drawCircleFrame(12, 11, 115, 9, 125);
  } else {
    drawPlanets();
  }

  Serial.println(slide);
}

void drawCircleFrame(int x, int r, int x2, int r2, int pauseLength) {
  for (int i = 0; i < pauseLength / 30; i++) {
    if (previousSlide != slide) {
      Serial.println("JEY!");
      return;
    }
    screen.clearDisplay();
    screen.drawCircle(x, 16, r, WHITE);
    screen.drawCircle(x2, 48, r2, WHITE);
    screen.display();
  }
}

void drawPlanets() {
  screen.clearDisplay();
  // Draw the bigger circle
  screen.fillCircle(center_x, center_y, big_radius, WHITE);

  // Calculate the position of the smaller circle based on the current angle
  int x = center_x + cos(angle) * ((big_radius + small_radius) * 1.5);
  int y = center_y + sin(angle) * ((big_radius + small_radius) * 1.5);

  // Draw the smaller circle
  screen.fillCircle(x, y, small_radius, WHITE);

  // Update the angle for the next frame
  angle += 0.1;

  // Show the updated display
  screen.display();
}


void test() {
  slide = (slide + 1) % 2;
  screen.println("AAA");
}
