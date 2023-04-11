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
float smallerAngle = 0;
float saturnAngle = 0;

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
  //do this for pauseLength/30 amount of time
  for (int i = 0; i < pauseLength / 30; i++) {
    if (previousSlide != slide) {
      Serial.println("JEY!");
      return;
    }
    screen.clearDisplay();
    //draw circle frame on the left
    screen.drawCircle(x, 16, r, WHITE);
    //draw circle frame on the right
    screen.drawCircle(x2, 48, r2, WHITE);
    screen.display();
  }
}

void drawPlanets() {
  int big_radius = 8;   // Radius of the bigger circle
  int small_radius = 3;  // Radius of the smaller circle
  int tiny_radius = 1;
  int saturn_radius = 4;
  screen.clearDisplay();
  // Draw the bigger circle
  screen.fillCircle(center_x, center_y, big_radius, WHITE);
  // Calculate the position of the smaller circle (EARTH) based on the current angle
  int x1 = center_x + cos(angle) * ((big_radius + small_radius) * 1.9);
  int y1 = center_y + sin(angle) * ((big_radius + small_radius) * 1.9);
  // Draw the smaller circle
  screen.fillCircle(x1, y1, small_radius, WHITE);
  // Update the angle for the next frame
  angle += 0.1;

  // Calculate the position of the tiny circle (MOON) based on the current smaller angle and the positon of the smaller circle (EARTH)
  int x2 = x1 + cos(smallerAngle) * ((small_radius + tiny_radius) * 1.9);
  int y2 = y1 + sin(smallerAngle) * ((small_radius + tiny_radius) * 1.9);
  // Draw the tiny circle
  screen.fillCircle(x2, y2, tiny_radius, WHITE);

  smallerAngle += 0.5;

    // Calculate the position of the smaller circle (EARTH) based on the current angle
  x1 = center_x + cos(saturnAngle) * ((big_radius + saturn_radius) * 3.9);
  y1 = center_y + sin(saturnAngle) * ((big_radius + saturn_radius) * 3.9);
  // Draw the smaller circle
  screen.fillCircle(x1, y1, saturn_radius, WHITE);
  screen.drawCircle(x1, y1, saturn_radius+5, WHITE);

  saturnAngle += 0.005;
  screen.display();
}


void test() {
  slide = (slide + 1) % 2;
}
