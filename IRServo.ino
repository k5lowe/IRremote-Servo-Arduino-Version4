/*
  IR Remote Controlling Servo

  The servo will turn clockwise(CW) or counterclockwise(CCW) at the click of a button.
  To make this circuit work, the servo was powered by a 9V battery while the Arduino 
  was powered from a laptop. When wiring both the servo and IR module to the 5V pin, 
  the circuit did not work. Instead, some wires were clipped to the battery's terminals 
  using a battery snap connector. 


  *This code was largely inspired by Mohamed Soliman as I took his code and wrote it
  using the IRremote.hpp library (version 4) instead of IRremote.h (version 2). 
  https://www.instructables.com/member/mohamed+soliman/
  https://www.instructables.com/Controlling-servo-motor-using-IR-remote-control/


  modified 10 Nov, 2023
  by Paul and Kushini
*/

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
