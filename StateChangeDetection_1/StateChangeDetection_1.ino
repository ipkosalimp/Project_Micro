/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground through 220 ohm resistor (or use the
    built-in LED on most Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/StateChangeDetection
*/

// this constant won't change:
const int buttonPin_1 = 22;  // the pin that the pushbutton is attached to
const int buttonPin_2 = 23;  // the pin that the pushbutton is attached to
const int buttonPin_3 = 24;  // the pin that the pushbutton is attached to
const int buttonPin_4 = 25;  // the pin that the pushbutton is attached to
const int buttonPin_5 = 26;  // the pin that the pushbutton is attached to
const int buttonPin_6 = 27;  // the pin that the pushbutton is attached to
const int buttonPin_7 = 28;  // the pin that the pushbutton is attached to
const int buttonPin_8 = 29;  // the pin that the pushbutton is attached to
const int buttonPin_9 = 30;  // the pin that the pushbutton is attached to
const int buttonPin_10 = 31;  // the pin that the pushbutton is attached to
const int buttonPin_11 = 32;  // the pin that the pushbutton is attached to
const int buttonPin_12 = 33;  // the pin that the pushbutton is attached to
const int buttonPin_13 = 34;  // the pin that the pushbutton is attached to
const int buttonPin_14 = 35;  // the pin that the pushbutton is attached to
const int buttonPin_15 = 36;  // the pin that the pushbutton is attached to
const int buttonPin_16 = 37;  // the pin that the pushbutton is attached to
const int buttonPin_17 = 38;  // the pin that the pushbutton is attached to
const int buttonPin_18 = 39;  // the pin that the pushbutton is attached to
const int buttonPin_19 = 40;  // the pin that the pushbutton is attached to
const int buttonPin_20 = 41;  // the pin that the pushbutton is attached to
const int buttonPin_21 = 42;  // the pin that the pushbutton is attached to
const int buttonPin_22 = 43;  // the pin that the pushbutton is attached to
const int buttonPin_23 = 44;  // the pin that the pushbutton is attached to
const int buttonPin_24 = 45;  // the pin that the pushbutton is attached to
const int buttonPin_25 = 46;  // the pin that the pushbutton is attached to
const int buttonPin_26 = 47;  // the pin that the pushbutton is attached to
const int buttonPin_27 = 48;  // the pin that the pushbutton is attached to
const int buttonPin_28 = 49;  // the pin that the pushbutton is attached to
const int buttonPin_29 = 50;  // the pin that the pushbutton is attached to
const int buttonPin_30 = 51;  // the pin that the pushbutton is attached to
const int buttonPin_31 = 52;  // the pin that the pushbutton is attached to
const int buttonPin_32 = 53;  // the pin that the pushbutton is attached to


// Variables will change:
int buttonState_1 = 0;        // current state of the button
int lastButtonState_1 = 0;    // previous state of the button

int buttonState_2 = 0;        // current state of the button
int lastButtonState_2 = 0;    // previous state of the button

int buttonState_3 = 0;        // current state of the button
int lastButtonState_3 = 0;    // previous state of the button

int buttonState_4 = 0;        // current state of the button
int lastButtonState_4 = 0;    // previous state of the button

int buttonState_5 = 0;        // current state of the button
int lastButtonState_5 = 0;    // previous state of the button

int buttonState_6 = 0;        // current state of the button
int lastButtonState_6 = 0;    // previous state of the button

int buttonState_7 = 0;        // current state of the button
int lastButtonState_7 = 0;    // previous state of the button

int buttonState_8 = 0;        // current state of the button
int lastButtonState_8 = 0;    // previous state of the button

int buttonState_9 = 0;        // current state of the button
int lastButtonState_9 = 0;    // previous state of the button

int buttonState_10 = 0;        // current state of the button
int lastButtonState_10 = 0;    // previous state of the button

int buttonState_11 = 0;        // current state of the button
int lastButtonState_11 = 0;    // previous state of the button

int buttonState_12 = 0;        // current state of the button
int lastButtonState_12 = 0;    // previous state of the button

int buttonState_13 = 0;        // current state of the button
int lastButtonState_13 = 0;    // previous state of the button

int buttonState_14 = 0;        // current state of the button
int lastButtonState_14 = 0;    // previous state of the button

int buttonState_15 = 0;        // current state of the button
int lastButtonState_15 = 0;    // previous state of the button

int buttonState_16 = 0;        // current state of the button
int lastButtonState_16 = 0;    // previous state of the button

int buttonState_17 = 0;        // current state of the button
int lastButtonState_17 = 0;    // previous state of the button

int buttonState_18 = 0;        // current state of the button
int lastButtonState_18 = 0;    // previous state of the button

int buttonState_19 = 0;        // current state of the button
int lastButtonState_19 = 0;    // previous state of the button

int buttonState_20 = 0;        // current state of the button
int lastButtonState_20 = 0;    // previous state of the button

int buttonState_21 = 0;        // current state of the button
int lastButtonState_21 = 0;    // previous state of the button

int buttonState_22 = 0;        // current state of the button
int lastButtonState_22 = 0;    // previous state of the button

int buttonState_23 = 0;        // current state of the button
int lastButtonState_23 = 0;    // previous state of the button

int buttonState_24 = 0;        // current state of the button
int lastButtonState_24 = 0;    // previous state of the button

int buttonState_25 = 0;        // current state of the button
int lastButtonState_25 = 0;    // previous state of the button

int buttonState_26 = 0;        // current state of the button
int lastButtonState_26 = 0;    // previous state of the button

int buttonState_27 = 0;        // current state of the button
int lastButtonState_27 = 0;    // previous state of the button

int buttonState_28 = 0;        // current state of the button
int lastButtonState_28 = 0;    // previous state of the button

int buttonState_29 = 0;        // current state of the button
int lastButtonState_29 = 0;    // previous state of the button

int buttonState_30 = 0;        // current state of the button
int lastButtonState_30 = 0;    // previous state of the button

int buttonState_31 = 0;        // current state of the button
int lastButtonState_31 = 0;    // previous state of the button

int buttonState_32 = 0;        // current state of the button
int lastButtonState_32 = 0;    // previous state of the button


void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin_1, INPUT);
  pinMode(buttonPin_2, INPUT);
  pinMode(buttonPin_3, INPUT);
  pinMode(buttonPin_4, INPUT);
  pinMode(buttonPin_5, INPUT);
  pinMode(buttonPin_6, INPUT);
  pinMode(buttonPin_7, INPUT);
  pinMode(buttonPin_8, INPUT);
  pinMode(buttonPin_9, INPUT);
  pinMode(buttonPin_10, INPUT);
  
  pinMode(buttonPin_11, INPUT);
  pinMode(buttonPin_12, INPUT);
  pinMode(buttonPin_13, INPUT);
  pinMode(buttonPin_14, INPUT);
  pinMode(buttonPin_15, INPUT);
  pinMode(buttonPin_16, INPUT);
  pinMode(buttonPin_17, INPUT);
  pinMode(buttonPin_18, INPUT);
  pinMode(buttonPin_19, INPUT);
  pinMode(buttonPin_20, INPUT);

  pinMode(buttonPin_21, INPUT);
  pinMode(buttonPin_22, INPUT);
  pinMode(buttonPin_23, INPUT);
  pinMode(buttonPin_24, INPUT);
  pinMode(buttonPin_25, INPUT);
  pinMode(buttonPin_26, INPUT);
  pinMode(buttonPin_27, INPUT);
  pinMode(buttonPin_28, INPUT);
  pinMode(buttonPin_29, INPUT);
  pinMode(buttonPin_30, INPUT);

  pinMode(buttonPin_31, INPUT);
  pinMode(buttonPin_32, INPUT);
  
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState_1 = digitalRead(buttonPin_1);
  buttonState_2 = digitalRead(buttonPin_2);
  buttonState_3 = digitalRead(buttonPin_3);
  buttonState_4 = digitalRead(buttonPin_4);
  buttonState_5 = digitalRead(buttonPin_5);
  buttonState_6 = digitalRead(buttonPin_6);
  buttonState_7 = digitalRead(buttonPin_7);
  buttonState_8 = digitalRead(buttonPin_8);
  buttonState_9 = digitalRead(buttonPin_9);
  buttonState_10 = digitalRead(buttonPin_10);
  buttonState_11 = digitalRead(buttonPin_11);
  buttonState_12 = digitalRead(buttonPin_12);
  buttonState_13 = digitalRead(buttonPin_13);
  buttonState_14 = digitalRead(buttonPin_14);
  buttonState_15 = digitalRead(buttonPin_15);
  buttonState_16 = digitalRead(buttonPin_16);
  buttonState_17 = digitalRead(buttonPin_17);
  buttonState_18 = digitalRead(buttonPin_18);
  buttonState_19 = digitalRead(buttonPin_19);
  buttonState_20 = digitalRead(buttonPin_20);
  buttonState_21 = digitalRead(buttonPin_21);
  buttonState_22 = digitalRead(buttonPin_22);
  buttonState_23 = digitalRead(buttonPin_23);
  buttonState_24 = digitalRead(buttonPin_24);
  buttonState_25 = digitalRead(buttonPin_25);
  buttonState_26 = digitalRead(buttonPin_26);
  buttonState_27 = digitalRead(buttonPin_27);
  buttonState_28 = digitalRead(buttonPin_28);
  buttonState_29 = digitalRead(buttonPin_29);
  buttonState_30 = digitalRead(buttonPin_30);
  buttonState_31 = digitalRead(buttonPin_31);
  buttonState_32 = digitalRead(buttonPin_32);
//==================== MK-1 ====================
  if (buttonState_1 != lastButtonState_1) {
    if (buttonState_1 == HIGH) {
    Serial.println("MK_1-NO_1 Closed");
    } 
    else {
    Serial.println("MK_1-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_1 = buttonState_1;
  }


  if (buttonState_2 != lastButtonState_2) {
    if (buttonState_2 == HIGH) {
    Serial.println("MK_1-NC_1 Closed");
    } 
    else {
    Serial.println("MK_1-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_2 = buttonState_2;
  }

//==================== MK-2 ====================
  if (buttonState_3 != lastButtonState_3) {
    if (buttonState_3 == HIGH) {
    Serial.println("MK_2-NO_1 Closed");
    } 
    else {
    Serial.println("MK_2-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_3 = buttonState_3;
  }


  if (buttonState_4 != lastButtonState_4) {
    if (buttonState_4 == HIGH) {
    Serial.println("MK_2-NC_1 Closed");
    } 
    else {
    Serial.println("MK_2-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_4 = buttonState_4;
  }

//==================== MK-3 ====================
  if (buttonState_5 != lastButtonState_5) {
    if (buttonState_5 == HIGH) {
    Serial.println("MK_3-NO_1 Closed");
    } 
    else {
    Serial.println("MK_3-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_5 = buttonState_5;
  }


  if (buttonState_6 != lastButtonState_6) {
    if (buttonState_6 == HIGH) {
    Serial.println("MK_3-NC_1 Closed");
    } 
    else {
    Serial.println("MK_3-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_6 = buttonState_6;
  }

//==================== MK-4 ====================
  if (buttonState_7 != lastButtonState_7) {
    if (buttonState_7 == HIGH) {
    Serial.println("MK_4-NO_1 Closed");
    } 
    else {
    Serial.println("MK_4-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_7 = buttonState_7;
  }


  if (buttonState_8 != lastButtonState_8) {
    if (buttonState_8 == HIGH) {
    Serial.println("MK_4-NC_1 Closed");
    } 
    else {
    Serial.println("MK_4-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_8 = buttonState_8;
  }

//==================== MK-5 ====================
  if (buttonState_9 != lastButtonState_9) {
    if (buttonState_9 == HIGH) {
    Serial.println("MK_5-NO_1 Closed");
    } 
    else {
    Serial.println("MK_5-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_9 = buttonState_9;
  }


  if (buttonState_10 != lastButtonState_10) {
    if (buttonState_10 == HIGH) {
    Serial.println("MK_5-NC_1 Closed");
    } 
    else {
    Serial.println("MK_5-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_10 = buttonState_10;
  }

//==================== MK-6 ====================
  if (buttonState_11 != lastButtonState_11) {
    if (buttonState_11 == HIGH) {
    Serial.println("MK_6-NO_1 Closed");
    } 
    else {
    Serial.println("MK_6-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_11 = buttonState_11;
  }


  if (buttonState_12 != lastButtonState_12) {
    if (buttonState_12 == HIGH) {
    Serial.println("MK_6-NC_1 Closed");
    } 
    else {
    Serial.println("MK_6-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_12 = buttonState_12;
  }

//==================== MK-7 ====================
  if (buttonState_13 != lastButtonState_13) {
    if (buttonState_13 == HIGH) {
    Serial.println("MK_7-NO_1 Closed");
    } 
    else {
    Serial.println("MK_7-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_13 = buttonState_13;
  }


  if (buttonState_14 != lastButtonState_14) {
    if (buttonState_14 == HIGH) {
    Serial.println("MK_7-NC_1 Closed");
    } 
    else {
    Serial.println("MK_7-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_14 = buttonState_14;
  }
//==================== MK-8 ====================
  if (buttonState_15 != lastButtonState_15) {
    if (buttonState_15 == HIGH) {
    Serial.println("MK_8-NO_1 Closed");
    } 
    else {
    Serial.println("MK_8-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_15 = buttonState_15;
  }


  if (buttonState_16 != lastButtonState_16) {
    if (buttonState_16 == HIGH) {
    Serial.println("MK_8-NC_1 Closed");
    } 
    else {
    Serial.println("MK_8-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_16 = buttonState_16;
  }
//==================== MK-9 ====================
  if (buttonState_17 != lastButtonState_17) {
    if (buttonState_17 == HIGH) {
    Serial.println("MK_9-NO_1 Closed");
    } 
    else {
    Serial.println("MK_9-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_17 = buttonState_17;
  }


  if (buttonState_18 != lastButtonState_18) {
    if (buttonState_18 == HIGH) {
    Serial.println("MK_9-NC_1 Closed");
    } 
    else {
    Serial.println("MK_9-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_18 = buttonState_18;
  }
//==================== MK-10 ====================
  if (buttonState_19 != lastButtonState_19) {
    if (buttonState_19 == HIGH) {
    Serial.println("MK_10-NO_1 Closed");
    } 
    else {
    Serial.println("MK_10-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_19 = buttonState_19;
  }


  if (buttonState_20 != lastButtonState_20) {
    if (buttonState_20 == HIGH) {
    Serial.println("MK_10-NC_1 Closed");
    } 
    else {
    Serial.println("MK_10-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_20 = buttonState_20;
  }

//==================== MK-11 ====================
  if (buttonState_21 != lastButtonState_21) {
    if (buttonState_21 == HIGH) {
    Serial.println("MK_11-NO_1 Closed");
    } 
    else {
    Serial.println("MK_11-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_21 = buttonState_21;
  }


  if (buttonState_22 != lastButtonState_22) {
    if (buttonState_22 == HIGH) {
    Serial.println("MK_11-NC_1 Closed");
    } 
    else {
    Serial.println("MK_11-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_22 = buttonState_22;
  }

//==================== MK-12 ====================
  if (buttonState_23 != lastButtonState_23) {
    if (buttonState_23 == HIGH) {
    Serial.println("MK_12-NO_1 Closed");
    } 
    else {
    Serial.println("MK_12-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_23 = buttonState_23;
  }


  if (buttonState_24 != lastButtonState_24) {
    if (buttonState_24 == HIGH) {
    Serial.println("MK_12-NC_1 Closed");
    } 
    else {
    Serial.println("MK_12-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_24 = buttonState_24;
  }

//==================== MK-13 ====================
  if (buttonState_25 != lastButtonState_25) {
    if (buttonState_25 == HIGH) {
    Serial.println("MK_13-NO_1 Closed");
    } 
    else {
    Serial.println("MK_13-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_25 = buttonState_25;
  }


  if (buttonState_26 != lastButtonState_26) {
    if (buttonState_26 == HIGH) {
    Serial.println("MK_13-NC_1 Closed");
    } 
    else {
    Serial.println("MK_13-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_26 = buttonState_26;
  }

//==================== MK-14 ====================
  if (buttonState_27 != lastButtonState_27) {
    if (buttonState_27 == HIGH) {
    Serial.println("MK_14-NO_1 Closed");
    } 
    else {
    Serial.println("MK_14-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_27 = buttonState_27;
  }


  if (buttonState_28 != lastButtonState_28) {
    if (buttonState_28 == HIGH) {
    Serial.println("MK_14-NC_1 Closed");
    } 
    else {
    Serial.println("MK_14-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_28 = buttonState_28;
  }

//==================== MK-15 ====================
  if (buttonState_29 != lastButtonState_29) {
    if (buttonState_29 == HIGH) {
    Serial.println("MK_15-NO_1 Closed");
    } 
    else {
    Serial.println("MK_15-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_29 = buttonState_29;
  }


  if (buttonState_30 != lastButtonState_30) {
    if (buttonState_30 == HIGH) {
    Serial.println("MK_15-NC_1 Closed");
    } 
    else {
    Serial.println("MK_15-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_30 = buttonState_30;
  }

//==================== MK-16 ====================
  if (buttonState_31 != lastButtonState_31) {
    if (buttonState_31 == HIGH) {
    Serial.println("MK_16-NO_1 Closed");
    } 
    else {
    Serial.println("MK_16-NO_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_31 = buttonState_31;
  }


  if (buttonState_32 != lastButtonState_32) {
    if (buttonState_32 == HIGH) {
    Serial.println("MK_16-NC_1 Closed");
    } 
    else {
    Serial.println("MK_16-NC_1 Opened");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
    lastButtonState_32 = buttonState_32;
  }

}
