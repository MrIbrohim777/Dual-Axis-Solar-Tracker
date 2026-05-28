/*
  Dual-Axis Solar Tracker
  ========================
  Hardware:
    - Arduino Uno
    - 4x LDR sensors (with 10kΩ pull-down resistors)
        TL → A0  (Top-Left)
        TR → A1  (Top-Right)
        BL → A2  (Bottom-Left)
        BR → A3  (Bottom-Right)
    - Elevation servo  → Pin 9
    - Azimuth servo    → Pin 10
  
  Wiring each LDR:
    5V ── [LDR] ──┬── Analog Pin
                  └── [10kΩ] ── GND
*/

#include <Servo.h>

// ── Pin assignments ────────────────────────────────────────────────────────────
const int PIN_LDR_TL = A0;   // Top-Left
const int PIN_LDR_TR = A1;   // Top-Right
const int PIN_LDR_BL = A2;   // Bottom-Left
const int PIN_LDR_BR = A3;   // Bottom-Right

const int PIN_SERVO_ELEV = 9;    // Elevation (up / down)
const int PIN_SERVO_AZIM = 10;   // Azimuth   (left / right)

// ── Tuning parameters ─────────────────────────────────────────────────────────
const int   THRESHOLD       = 15;   // Light difference to trigger movement (0-1023 scale)
const int   SERVO_STEP      = 1;    // Degrees to move per loop iteration
const int   LOOP_DELAY_MS   = 50;   // Milliseconds between readings

// Elevation limits (degrees) — protect your mechanism
const int   ELEV_MIN        = 10;   // Minimum tilt (near horizontal)
const int   ELEV_MAX        = 170;  // Maximum tilt (near vertical)
const int   ELEV_START      = 90;   // Starting position

// Azimuth limits (degrees)
const int   AZIM_MIN        = 10;
const int   AZIM_MAX        = 170;
const int   AZIM_START      = 90;

// ── Servo objects ─────────────────────────────────────────────────────────────
Servo servoElev;
Servo servoAzim;

// Current positions
int posElev = ELEV_START;
int posAzim = AZIM_START;

// ── Setup ─────────────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  servoElev.attach(PIN_SERVO_ELEV);
  servoAzim.attach(PIN_SERVO_AZIM);

  // Move to start position
  servoElev.write(posElev);
  servoAzim.write(posAzim);

  Serial.println("Dual-Axis Solar Tracker started.");
  Serial.println("Elev | Azim | TL   | TR   | BL   | BR");
  delay(1000);
}

// ── Main loop ─────────────────────────────────────────────────────────────────
void loop() {
  // 1. Read all four LDR sensors
  int tl = analogRead(PIN_LDR_TL);
  int tr = analogRead(PIN_LDR_TR);
  int bl = analogRead(PIN_LDR_BL);
  int br = analogRead(PIN_LDR_BR);

  // 2. Calculate averages for each direction
  int avgTop    = (tl + tr) / 2;
  int avgBottom = (bl + br) / 2;
  int avgLeft   = (tl + bl) / 2;
  int avgRight  = (tr + br) / 2;

  int diffVertical   = avgTop - avgBottom;
  int diffHorizontal = avgLeft - avgRight;

  // 3. Elevation axis (up / down)
  if (abs(diffVertical) > THRESHOLD) {
    if (diffVertical > 0) {
      // Top brighter → tilt up
      posElev = constrain(posElev + SERVO_STEP, ELEV_MIN, ELEV_MAX);
    } else {
      // Bottom brighter → tilt down
      posElev = constrain(posElev - SERVO_STEP, ELEV_MIN, ELEV_MAX);
    }
    servoElev.write(posElev);
  }

  // 4. Azimuth axis (left / right)
  if (abs(diffHorizontal) > THRESHOLD) {
    if (diffHorizontal > 0) {
      // Left brighter → rotate left
      posAzim = constrain(posAzim - SERVO_STEP, AZIM_MIN, AZIM_MAX);
    } else {
      // Right brighter → rotate right
      posAzim = constrain(posAzim + SERVO_STEP, AZIM_MIN, AZIM_MAX);
    }
    servoAzim.write(posAzim);
  }

  // 5. Serial monitor output (open at 9600 baud to watch)
  Serial.print(posElev);   Serial.print("°   | ");
  Serial.print(posAzim);   Serial.print("°   | ");
  Serial.print(tl);         Serial.print(" | ");
  Serial.print(tr);         Serial.print(" | ");
  Serial.print(bl);         Serial.print(" | ");
  Serial.println(br);

  delay(LOOP_DELAY_MS);
}
