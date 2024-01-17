#include <Keyboard.h>
#include <Keyboard_fr_FR.h>

const int pins[] = {2, 6, 7, 8, 9};
const int numPins = 5;

void typeKey(int key){
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

// Windows CMD
void run_payload1(){
  delay(500);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(200);
  Keyboard.print(F("cmd.exe"));
  Keyboard.write(KEY_RETURN);
}

void setup() {
  Keyboard.begin(KeyboardLayout_fr_FR);
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], INPUT);
  }
  delay(2000);
}

void loop() {
  for (int i = 0; i < numPins; i++) {
    int state = digitalRead(pins[i]);
    Serial.print(state);
    Serial.print(" ");
  }
  Serial.println();

  bool allHigh = true;
  for (int i = 0; i < numPins; i++) {
    if (digitalRead(pins[i]) != HIGH) {
      allHigh = false;
      break;
    }
  }

  if (allHigh) {
    run_payload1();
    delay(2000);
  }

  delay(100);
}
