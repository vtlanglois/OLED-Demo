#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct Planet {
  int center_x; // x positon of the planet
  int center_y; // y positon of the planet
  int radius; // radius (half of diameter) of the planet
  float angle; // current angle of the planet
};


const int interruptPin = 2;
int slide = 0;
int previousSlide = slide;

int center_x = SCREEN_WIDTH / 2;   // X coordinate of the center
int center_y = SCREEN_HEIGHT / 2;  // Y coordinate of the center

Planet sun = {center_x, center_y, 8, 0};
Planet earth = {0, 0, 3, 0};
Planet moon = {0, 0, 1, 0};
Planet saturn = {0, 0, 4, 0};

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
  screen.clearDisplay();
  // Draw the Sun
  screen.fillCircle(sun.center_x, sun.center_y, sun.radius, WHITE);
  // Calculate the position of Earth based on it;s current angle
  earth.center_x = sun.center_x + cos(earth.angle) * ((sun.radius + earth.radius) * 1.9);
  earth.center_y = sun.center_y + sin(earth.angle) * ((sun.radius + earth.radius) * 1.9);
  // Draw Earth
  screen.fillCircle(earth.center_x, earth.center_y, earth.radius, WHITE);
  // Update Earth's angle for the next frame
  earth.angle += 0.01;

  // Calculate the position of the Moon based on the current smaller angle and the positon of Earth
  moon.center_x = earth.center_x + cos(moon.angle) * ((earth.radius + moon.radius) * 1.9);
  moon.center_y = earth.center_y + sin(moon.angle) * ((earth.radius + moon.radius) * 1.9);
  // Draw the Moon
  screen.fillCircle(moon.center_x, moon.center_y, moon.radius, WHITE);
  // Update Moons angle for the next frame
  moon.angle += 0.5;

  // Calculate the position of Saturn based on it's current angle and Sun
  saturn.center_x = sun.center_x + cos(saturn.angle) * ((sun.radius + saturn.radius) * 3.9);
  saturn.center_y = sun.center_y + sin(saturn.angle) * ((sun.radius + saturn.radius) * 3.9);
  // Draw Saturn
  screen.fillCircle(saturn.center_x, saturn.center_y, saturn.radius, WHITE);
  // Draw Saturn's rings
  screen.drawCircle(saturn.center_x, saturn.center_y, saturn.radius+3, WHITE);
  screen.drawCircle(saturn.center_x, saturn.center_y, saturn.radius+5, WHITE);
  // Update Saturn's angle for the next frame
  saturn.angle += 0.005;
  screen.display();
}


void test() {
  slide = (slide + 1) % 2;
}
