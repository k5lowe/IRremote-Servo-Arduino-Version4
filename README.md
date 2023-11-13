# IR-Remote Controlling Servo #

This Arduino project demonstrates how to turn a servo clockwise(CW) or counterclockwise(CCW) at the click of an IR Remote button.

## Overview ##
- [Hardware](#hardware-required)
- [Wiring](#wiring)
- [Programming](#programming)
    - [Decoding IR-Remote Serial Numbers (Code 1)](#code-1)
    - [IR-Remote Controlling Servo (Code 2)](#code-2)
- [Attributions](#attributions)

## Hardware Required ##
- Arduino Board
- Servo Motor
- IR Receiver Module
- Breadboard
- 9V battery
- Hook-up wires
- Battery snap connector (optional)

## Wiring ##

 ![IRServo Schematic](https://github.com/k5lowe/IR-Controlling-Servo-Arduino-/assets/115502398/ec69d876-da9b-4744-b29d-4a460caae6f2)

## Programming ##
This document comes with two sets of code; one for decoding the IR remote and one for using the decoded remote to control the servo.
- <b> Code 1 </b> <br>
You will need to find the serial numbers (hex codes) of your IR Remote. This is done so your IR module can read the infrared light. You can do this by running the first block of code below (<b>Code 1</b>). After running the code, open the serial monitor and select two serial numbers to use in the second code (<b>Code 2</b>).

- <b> Code 2 </b> <br>
Insert the two serial numbers found in the previous code where I have defined my serial numbers (<b>up</b> and <b>down</b>).
    - To make this circuit work, the servo was powered by a 9V battery while the Arduino was powered by a laptop. When wiring both the servo and IR module to the 
      5V pin, the circuit did not work. Instead, some wires were clipped to the battery's terminals using a battery snap connector. 


### Code 1 ###
<b>Decoding IR-Remote Serial Numbers</b>

```c++
#include <IRremote.hpp>
#define IR_RECEIVE_PIN 2

void setup()
{
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      //IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      IrReceiver.resume(); // Enable receiving of the next value
  }
}

```


### Code 2 ###
<b>IR-Remote Controlling Servo</b>
```c++
#include <IRremote.hpp>        // New IRremote library; download from libraries
#include <Servo.h>
#define up 0xF609FF00          // CCW button
#define down 0xF807FF00        // CW button. You'll need to find the serial numbers of your buttons
#define IR_RECEIVE_PIN 2       // IRModule pin


Servo myservo;
int ival;                      // Rotation angle
bool bcwRotation, bccwRotation;// The states of rotation


void setup()
{
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    myservo.attach(9);         // Servo pin
}

void loop() {

    if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.resume();

      if (IrReceiver.decodedIRData.decodedRawData == up) {
        bcwRotation = !bcwRotation;   // Toggle the rotation value
        bccwRotation = false;         // No rotation in this direction
      }

      if (IrReceiver.decodedIRData.decodedRawData == down) {
        bccwRotation = !bccwRotation; // Toggle the rotation value
        bcwRotation = false;          // No rotation in this direction
      }
    }
    if (bcwRotation && (ival != 180)) {
      ival++;  // For clockwise button

    }
    if (bccwRotation && (ival != 0)) {
      ival--;  // For counterclockwise button

    }
    myservo.write(ival);
    delay(5);  // General speed. Increase value for a slower speed
}
```

## Attributions ##

The entirety of the first code was taken from this page:

- https://github.com/Arduino-IRremote/Arduino-IRremote#using-the-new-hpp-files

The second code was largely inspired by Mohamed Soliman as I took his code and wrote it
using the IRremote.hpp library (version 4) instead of IRremote.h (version 2).

- https://www.instructables.com/member/mohamed+soliman/ <br>
- https://www.instructables.com/Controlling-servo-motor-using-IR-remote-control/


The entire reason for this Arduino project and my knowledge of Arduinos is because of Paul. To him I owe much of my gratitude and credit. Thanks boss
