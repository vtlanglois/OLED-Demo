# Arduino OLED Screen Demo

This repository provides code and instructions for building an Arduino-based device that showcases the capabilities of an OLED screen. The device consists of an OLED screen, a button, a breadboard, wires, and an Arduino UNO, and it displays four demonstrations that illustrate various aspects of OLED screen usage.

This project was created for INFO-341 **Prototyping with Arduino Tools**, a class taught at Indiana University in Spring 2023.

## Hardware Setup

To assemble the device, you will need:

- OLED screen
- Button
- Breadboard
- Jumper wires
- Arduino UNO

Follow these steps to set up the hardware:

1. Connect **5V** and **Ground* from the Arduino UNO to the breadboard in their appropriate buses.
2. Connect the OLED screen to the breadboard.
3. Connect the OLED screen to **5V** and **Ground** from the breadboard bus.
4. Connect a jumper wire from **Analog Input A4** to **SDA** on the OLED screen.
5. Connect a jumper wire from **Analog Input A5** to **SCL** on the OLED screen.
6. Connect the button to the breadboard.
7. Connect a jumper wire to the top-left corner of the button, and connect a ground wire to the top-right corner.
8. Connect the jumper wire to **Digital Input 2** on the Arduino UNO

## Software Setup

To run the code, you will need to install the Arduino Integrated Development Environment (IDE) from the official [Arduino website](https://www.arduino.cc/en/software/) and follow these steps:

1. Clone this repository to your computer or download the ZIP file and extract its contents.
2. Open the `OLED-demo.ino` file in the Arduino IDE.
3. Connect the Arduino UNO to your computer via USB cable.
4. Select the appropriate board and port from the "Tools" menu.
5. Click "Upload" to upload the code to the Arduino UNO.

## Usage

Once the code has been uploaded to the device, the button can be used to switch between the four demos:

1. **Solar System Animation**: This demo showcases a 2D animation of Earth, the Moon, Mars, and Saturn orbiting the Sun. Simple shapes and math are used to create the animation, with stars in the background as pixels.
2. **Earth Data**: This demo displays the position and angle of Earth in the solar system. This serves to demonstrate printing text and variables to the OLED screen.
3. **Pyramid in the Night**: This demo depicts a pyramid in the night with a crescent moon above it. The aim is to demonstrate the creation of complex images using simple shapes such as lines, triangles, and circles.
4. **Moving Circles**: This demo features two circles moving rapidly across the screen, with the appearance of moving into and out of the foreground. This animation serves to demonstrate how OLED screens and Arduinos can generate more sophisticated animations using squash-and-stretch and variable frame lengths.

The device is designed to loop back to the first demo once the user clicks the button on the last demo.

## Credits

This demo was created by Vincent Langlois and relies on the Adafruit SSD1306 library for OLED screens. 
