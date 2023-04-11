#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// data struct represents a Planet's position, radius, and angle in the solar system demo
struct Planet {
  int center_x;  // x positon of the planet
  int center_y;  // y positon of the planet
  int radius;    // radius (half of diameter) of the planet
  float angle;   // current angle of the planet
};

// data struct represents a star's position in the solar system demo
struct Position {
  int x;
  int y;
};


const int interruptPin = 2;
int demo = 0;
const int MAX_DEMOS = 3;
int previousDemo = demo;

int center_x = SCREEN_WIDTH / 2;   // X coordinate of the center
int center_y = SCREEN_HEIGHT / 2;  // Y coordinate of the center

Planet sun = { center_x, center_y, 8, 0 };
Planet earth = { 0, 0, 3, 0 };
Planet moon = { 0, 0, 1, 0 };
Planet saturn = { 0, 0, 4, 0 };

//for pyramid demo
Planet py_sun = {center_x, 0, 8, 0};
Planet py_moon = {center_x, SCREEN_HEIGHT, 7, 0};

const int MAX_STARS = 60;

Position starPositions[MAX_STARS];

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
  attachInterrupt(digitalPinToInterrupt(interruptPin), goToNextDemo, RISING);

  // set up star positons
  for (int i = 0; i < MAX_STARS; i++) {
    int x = random(SCREEN_WIDTH);
    int y = random(SCREEN_HEIGHT);
    Position pos = { x, y };
    starPositions[i] = pos;
  }

  screen.display();
  delay(2000);  // Pause for 2 seconds

  // Clear the buffer
  screen.clearDisplay();
}

void loop() {
  if (demo == 0) {
    previousDemo = demo;
    drawSolarSystem();
  } else if (demo == 1) {
    previousDemo = demo;
    drawMountain();
    //drawSolarSystemInfo();
  } else {
    previousDemo = demo;
    drawCircleAnimation();
  }

  Serial.println(demo);
}

void drawCircleAnimation() {
  drawCircleFrame(10, 10, 117, 10, 150);
  drawCircleFrame(12, 9, 115, 11, 125);
  drawCircleFrame(18, 8, 109, 12, 75);
  drawCircleFrame(31, 7, 96, 13, 75);
  drawCircleFrame(64, 5, 64, 15, 25);
  drawCircleFrame(96, 7, 31, 13, 75);
  drawCircleFrame(109, 8, 18, 12, 75);
  drawCircleFrame(115, 9, 12, 11, 125);
  drawCircleFrame(117, 10, 10, 10, 150);
  drawCircleFrame(115, 11, 12, 9, 125);
  drawCircleFrame(109, 12, 18, 8, 75);
  drawCircleFrame(96, 13, 31, 7, 75);
  drawCircleFrame(64, 15, 64, 5, 25);
  drawCircleFrame(31, 13, 96, 7, 75);
  drawCircleFrame(18, 12, 109, 8, 75);
  drawCircleFrame(12, 11, 115, 9, 125);
}

void drawCircleFrame(int x, int r, int x2, int r2, int pauseLength) {
  //do this for pauseLength/30 amount of time
  for (int i = 0; i < pauseLength / 30; i++) {
    if (previousDemo != demo) {
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

void drawSolarSystem() {
  screen.clearDisplay();

  // Draw stars
  for (int i = 0; i < MAX_STARS/2; i++) {
    screen.drawPixel(starPositions[i].x, starPositions[i].y, WHITE);
  }


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
  screen.drawCircle(saturn.center_x, saturn.center_y, saturn.radius + 3, WHITE);
  screen.drawCircle(saturn.center_x, saturn.center_y, saturn.radius + 5, WHITE);
  // Update Saturn's angle for the next frame
  saturn.angle += 0.005;
  screen.display();
}

void drawSolarSystemInfo() {
  screen.clearDisplay();
  screen.setCursor(0, 0);
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  printPlanetInfo(earth, "Earth");
  printPlanetInfo(moon, "Moon");
  printPlanetInfo(saturn, "Saturn");
  screen.display();
}

void printPlanetInfo(Planet planet, String name) {
  screen.print(name + "'s pos: ");
  screen.print(planet.center_x);
  screen.print(", ");
  screen.print(planet.center_y);
  screen.println();
  screen.print(name + "'s angle: ");
  screen.print(normalizeAngle(planet.angle));
  screen.println();
}

float normalizeAngle(float angle) {
  angle = fmod(angle, 360.0);
  if (angle < 0) {
    angle += 360.0;
  }
  return angle;
}
void drawMountain() {
  screen.clearDisplay();

  // Draw ALL stars
  for (Position pos : starPositions) {
    screen.drawPixel(pos.x, pos.y, WHITE);
  }

  screen.fillCircle(py_sun.center_x-30, py_sun.center_y+7, py_sun.radius, WHITE);
  screen.fillCircle(py_sun.center_x-28, py_sun.center_y+5, py_sun.radius, BLACK);

  //define the points for the pyramid triangle
  int x1 = 0;
  int y1 = SCREEN_HEIGHT;
  int x2 = SCREEN_WIDTH / 2;
  int y2 = SCREEN_HEIGHT / 4;
  int x3 = SCREEN_WIDTH;
  int y3 = SCREEN_HEIGHT;

  // Draw the filled triangle for the pyramid
  screen.fillTriangle(x1, y1, x2, y2, x3, y3, WHITE);

  // Draw the lines on the triangle to mimic pyramid bricks
  screen.drawLine(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2, BLACK);
  screen.drawLine(0, (SCREEN_HEIGHT/2)+10, SCREEN_WIDTH, (SCREEN_HEIGHT/2)+10, BLACK);
  screen.drawLine(0, (SCREEN_HEIGHT/2)+20, SCREEN_WIDTH, (SCREEN_HEIGHT/2)+20, BLACK);
  // Update the screen

  screen.display();
}


void goToNextDemo() {
  demo = (demo + 1) % MAX_DEMOS;
}
