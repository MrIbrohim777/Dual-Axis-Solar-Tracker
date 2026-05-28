# Calibration & Tuning Guide

Step-by-step instructions to optimize your dual-axis solar tracker for accurate, smooth sun tracking.

## Pre-Calibration Checklist

Before starting, ensure:

- [ ] Arduino is programmed with `dual_axis_solar_tracker.ino`
- [ ] All 4 LDR sensors are connected to A0-A3
- [ ] Both servo motors are connected to pins 9 and 10
- [ ] USB power supply is connected (5V, 2A minimum)
- [ ] Servos move freely without mechanical binding
- [ ] All wiring is secure and no solder bridges present

---

## Stage 1: Hardware Verification

### 1.1 Servo Range Test

Upload this test code to verify servos move across their full range:

```cpp
#include <Servo.h>

Servo s1, s2;

void setup() {
  Serial.begin(9600);
  s1.attach(10);  // Azimuth
  s2.attach(9);   // Elevation
  
  Serial.println("Testing full range...");
  for (int angle = 10; angle <= 170; angle += 10) {
    s1.write(angle);
    s2.write(angle);
    Serial.print("Angle: ");
    Serial.println(angle);
    delay(500);
  }
  Serial.println("Done!");
}

void loop() {}
```

**Expected behavior:**
- Servo 1 (azimuth) rotates smoothly left → right
- Servo 2 (elevation) tilts smoothly up → down
- Both stop at ~10° and ~170° (mechanical limits)

**If servo doesn't move:**
- Check power supply (5V, 2A)
- Try swapping servo to different pin (9 vs 10)
- Test servo independently with standard Arduino servo example

### 1.2 LDR Reading Test

Upload this to verify all 4 LDRs are responding:

```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  int tl = analogRead(A0);
  int tr = analogRead(A1);
  int bl = analogRead(A2);
  int br = analogRead(A3);
  
  Serial.print("TL: ");
  Serial.print(tl);
  Serial.print("  TR: ");
  Serial.print(tr);
  Serial.print("  BL: ");
  Serial.print(bl);
  Serial.print("  BR: ");
  Serial.println(br);
  
  delay(200);
}
```

**Expected behavior (indoors under normal lighting):**
- All 4 values range between 200-600
- Values change when you block light with your hand
- No sensor reads 0 or 1023 constantly

**If sensor reading is stuck at 0:**
- Check 10kΩ resistor is installed
- Verify LDR legs are not bent/broken
- Check for solder bridges

**If sensor reading is stuck at 1023:**
- Check if LDR is open circuit (leg not soldered)
- Verify 5V is reaching the LDR

---

## Stage 2: Servo Calibration

### 2.1 Azimuth Servo Center Point

The azimuth servo should point "straight ahead" at 90°.

1. In `dual_axis_solar_tracker.ino`, temporarily set:
   ```cpp
   servoAzim.write(90);
   ```

2. Upload and observe servo position

3. **Visually align** the servo horn to point straight forward

4. If not centered:
   - Mechanical fix: Loosen servo horn screw, rotate horn to 90° position, re-tighten
   - Code fix: Adjust `AZIM_START = 90` (default) to a different value (e.g., 88-92)

### 2.2 Elevation Servo Center Point

The elevation servo should be level (horizontal) at 90°.

1. Set:
   ```cpp
   servoElev.write(90);
   ```

2. Verify panel is perfectly horizontal (use spirit level)

3. If tilted:
   - Mechanical: Loosen servo horn, rotate to 90°, re-tighten
   - Code: Adjust `ELEV_START = 90` if needed

### 2.3 Servo Direction Verification

**For Azimuth:** Moving the panel to the right should increase the angle value

```cpp
// Test script
servoAzim.write(80);   // Move left
delay(500);
servoAzim.write(100);  // Move right
```

If direction is reversed, add this to the main code:
```cpp
// Reverse azimuth direction
int adjustedAzim = 180 - posAzim;  // Flip 0-180 range
servoAzim.write(adjustedAzim);
```

**For Elevation:** Tilting upward should increase the angle value

Similar fix if needed:
```cpp
int adjustedElev = 180 - posElev;
servoElev.write(adjustedElev);
```

---

## Stage 3: LDR Sensitivity Tuning

### 3.1 Threshold Adjustment

The `THRESHOLD` value (default: 15) determines how much light difference is needed to move the servo.

**Test in different lighting conditions:**

**Bright sunlight indoors (window):**
```cpp
const int THRESHOLD = 10;  // Sensitive (quick tracking)
```

**Dim indoor lighting:**
```cpp
const int THRESHOLD = 25;  // Less sensitive (reduce jitter)
```

**Very bright outdoors (direct sun):**
```cpp
const int THRESHOLD = 15;  // Balanced
```

**How to find the right value:**

1. Place your hand slowly moving around the panel edge
2. Observe when servo first responds
3. If servo responds too eagerly (jitters), **increase THRESHOLD**
4. If servo doesn't respond until light difference is large, **decrease THRESHOLD**

### 3.2 Checking for Sensor Imbalance

Some LDRs may be more sensitive than others. Monitor readings:

```cpp
Serial.print("TL-TR: ");
Serial.print(tl - tr);
Serial.print("  TL+TR-BL-BR: ");
Serial.println(tl + tr - bl - br);
```

If one corner reads consistently 100+ points higher:
- Ensure the divider plates are equal height
- Check that all LDRs are the same type (GL5506)
- Verify none are bent or damaged

---

## Stage 4: Movement Tuning

### 4.1 Servo Step Size

The `SERVO_STEP` value (default: 1°) controls how many degrees the servo moves per loop iteration.

```cpp
const int SERVO_STEP = 1;   // Smooth, slow (50ms × 1° = 0.5°/sec)
const int SERVO_STEP = 2;   // Faster (1°/sec)
const int SERVO_STEP = 3;   // Very responsive (1.5°/sec)
```

**Trade-offs:**
- **SERVO_STEP = 1:** Smooth, gentle, but slow to catch up with fast sun movement
- **SERVO_STEP = 2:** Balanced for most applications
- **SERVO_STEP = 3+:** Fast but may overshoot and hunt

**Recommended:** Start with `SERVO_STEP = 1`, increase only if tracking lags noticeably

### 4.2 Loop Delay

The `LOOP_DELAY_MS` value (default: 50 ms) is the pause between sensor reads.

```cpp
const int LOOP_DELAY_MS = 30;   // Fast updates (33 Hz)
const int LOOP_DELAY_MS = 50;   // Balanced (20 Hz)
const int LOOP_DELAY_MS = 100;  // Slow updates (10 Hz)
```

**Effect on tracking speed:**
```
Speed (°/sec) = SERVO_STEP / (LOOP_DELAY_MS / 1000)

Examples:
SERVO_STEP=1, LOOP_DELAY=50   → 1 ÷ 0.05 = 20°/sec max
SERVO_STEP=1, LOOP_DELAY=100  → 1 ÷ 0.1  = 10°/sec max
SERVO_STEP=2, LOOP_DELAY=50   → 2 ÷ 0.05 = 40°/sec max
```

The sun moves at approximately **0.25°/sec**, so 20°/sec is more than sufficient.

---

## Stage 5: Full System Calibration

### 5.1 Outdoor Testing (Clear Day)

1. **Set panel facing east** at sunrise
2. **Observe for 5 minutes:**
   - Does panel follow the sun smoothly?
   - Any oscillation (jittering)?
   - Any delayed response?

3. **Adjust parameters if needed:**
   - **Too much jitter** → Increase THRESHOLD by 5
   - **Delayed response** → Decrease LOOP_DELAY_MS by 10 ms
   - **Overshooting** → Decrease SERVO_STEP or increase LOOP_DELAY_MS

### 5.2 Cloud Movement Test

Clouds move much faster than the sun. Your tracker should NOT follow fast-moving clouds.

1. Watch Serial Monitor output
2. If panel jumps around with clouds:
   - Increase THRESHOLD (e.g., 20 → 25)
   - This filters out brief light fluctuations

### 5.3 Shading Test

Run the tracker in partial shade to verify it doesn't chase shadows.

Expected behavior:
- Panel stays pointed at brightest area (usually the actual sun)
- Doesn't move rapidly between light patches

---

## Stage 6: Fine-Tuning Parameters

### Suggested Starting Point

For most locations and lighting conditions:

```cpp
const int THRESHOLD = 15;
const int SERVO_STEP = 1;
const int LOOP_DELAY_MS = 50;
const int ELEV_MIN = 10;
const int ELEV_MAX = 170;
const int AZIM_MIN = 10;
const int AZIM_MAX = 170;
const int ELEV_START = 90;
const int AZIM_START = 90;
```

### Parameter Matrix (for reference)

| Scenario | THRESHOLD | SERVO_STEP | LOOP_DELAY | Result |
|----------|-----------|------------|-----------|--------|
| Bright sun | 15 | 1 | 50 | Smooth tracking |
| Cloudy/dim | 20-25 | 1-2 | 50-100 | Stable, less jitter |
| Fast tracking needed | 10 | 2-3 | 30 | Responsive (may overshoot) |
| Ultra-stable (no clouds) | 25 | 1 | 100 | Slow but very stable |

---

## Serial Monitor Interpretation

Open Serial Monitor (9600 baud) and watch the output:

```
Elev | Azim | TL   | TR   | BL   | BR
90°  | 90°  | 450  | 480  | 440  | 470
89°  | 91°  | 420  | 510  | 450  | 460
88°  | 92°  | 380  | 540  | 440  | 450
```

**What to look for:**

1. **Gradual changes in angles** (smooth tracking) ✓
2. **Balanced TL/TR values** (panel level) ✓
3. **Balanced BL/BR values** (panel centered) ✓
4. **Values in 200-800 range** (good sensor operation) ✓

**Red flags:**

- **One LDR stuck at 0 or 1023** → Wiring issue
- **Angles jumping 5-10° per update** → SERVO_STEP too high
- **Rapid oscillation** (89 → 91 → 89 → 91) → THRESHOLD too low
- **Values all 1023 or all 0** → No light on panel

---

## Performance Targets

After calibration, your tracker should achieve:

| Metric | Target | How to Verify |
|--------|--------|--------------|
| **Tracking accuracy** | ±2-3° | Compare panel angle to actual sun position |
| **Response time** | <5 seconds to respond to sun movement | Move light source, observe servo |
| **Stability** | No oscillation under steady light | Observe angle values in Serial Monitor |
| **Cloud robustness** | Ignores brief shadows | Test with moving hand over panel |

---

## Maintenance & Re-Calibration

### Monthly
- Clean LDR lenses (dust reduces sensitivity)
- Check servo horns haven't loosened
- Verify mechanical bearings spin freely

### Seasonal
- Recalibrate if location latitude changes significantly
- Check for gear wear in servo
- Test full range (ELEV_MIN to ELEV_MAX)

### Annual
- Replace servo if range of motion becomes stiff or erratic
- Consider replacing LDRs if readings become inconsistent
- Inspect for corrosion (if outdoors)

---

## Troubleshooting Calibration Issues

| Issue | Likely Cause | Fix |
|-------|--------------|-----|
| Panel stays motionless | THRESHOLD too high or no sunlight | Reduce THRESHOLD or test indoors |
| Panel oscillates rapidly | THRESHOLD too low | Increase to 20-25 |
| Panel overshoots sun | SERVO_STEP too high or LOOP_DELAY too small | Reduce SERVO_STEP or increase LOOP_DELAY |
| Panel slow to track | SERVO_STEP too low or LOOP_DELAY too high | Increase SERVO_STEP or reduce LOOP_DELAY |
| Servo twitches at limit | Mechanical binding | Check for bent servo horn, loosen pivot bolts slightly |
| Unbalanced tracking (favors one side) | LDR sensitivity mismatch | Verify dividers are symmetric, check LDR values match |

---

## Field Testing Checklist

Once fully calibrated, run through this checklist:

- [ ] Sunrise: Panel correctly faces east
- [ ] Mid-morning: Panel tilts upward as sun rises
- [ ] Noon: Panel facing nearly straight up
- [ ] Afternoon: Panel tilts downward and rotates west
- [ ] Sunset: Panel faces west, low in sky
- [ ] Continuous operation: No failures for 2+ hours
- [ ] Response to clouds: Ignores brief shadows
- [ ] Power consumption: Stable, no spikes
- [ ] Temperature: Servos and panel not overheating

---

## Optimization Tips

### For Maximum Power Output
- Focus on elevation accuracy (more impact on power)
- Allow azimuth to be ±2-3° off (less critical)
- Increase SERVO_STEP slightly for faster tracking

### For Maximum Stability
- Increase THRESHOLD to 25-30
- Reduce SERVO_STEP to 0.5 (requires code change to float)
- Increase LOOP_DELAY to 100 ms
- Useful for very cloudy climates

### For Extreme Conditions
- **Very hot:** Use PETG servos (higher temp rating)
- **Very cold:** Reduce LOOP_DELAY (thicker grease)
- **High altitude/thin air:** LDRs less affected; normal calibration works
- **Tropical humid:** Add conformal coating to LDR circuit

---

## Next Steps

Once calibration is complete:

1. Log performance data (angles, power output) for 1 week
2. Calculate average power improvement vs. fixed panel
3. Adjust seasonal tilt angles if not moving north/south
4. Consider adding automated cloud-detection algorithm
5. Plan for winter solstice / summer solstice adjustments

**Expected power improvement:** 30-45% more energy than a fixed panel at your latitude.
