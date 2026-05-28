# Dual-Axis Solar Tracker - 3D Printable Mini Model

## Model Specifications

**File:** `dual_axis_solar_tracker_mini.stl`

**Dimensions:**
- Total Height: ~120 mm (from base to top of panel)
- Base Width/Depth: ~100 mm × 100 mm
- Solar Panel: ~80 mm × 60 mm
- Print Time:** ~8-12 hours (depending on settings)
- Filament:** ~150-200g

---

## Print Settings Recommended

```
Layer Height:        0.2 mm
Infill:              15-20% (honeycomb or grid)
Nozzle Temp:         200-210°C (PLA) / 220-230°C (PETG)
Bed Temp:            60°C (PLA) / 80°C (PETG)
Print Speed:         50 mm/s
Support:             YES (for overhanging parts)
Orientation:         Print with base plate down
```

---

## Components in the Model

| # | Component | Qty | Size | Purpose |
|---|-----------|-----|------|---------|
| 1 | Base Plate | 1 | 100×100×4 mm | Foundation |
| 2 | Vertical Pole | 1 | Ø10 mm, 100 mm tall | Main support |
| 3 | Azimuth Base Ring | 1 | Ø26 mm | Rotates horizontally (360°) |
| 4 | Horizontal Arm | 1 | 70×4×4 mm | Elevation pivot support |
| 5 | Elevation Bearings | 2 | Ø8×10 mm | Left & right pivot points |
| 6 | Tilting Arm | 1 | 65×3×3 mm | Connects panel to elevators |
| 7 | Solar Panel Frame | 1 | 80×3×60 mm | Outer frame |
| 8 | Panel Cells | 1 | 76×1×56 mm | Cell representation layer |
| 9 | LDR Sensor Housing | 4 | Ø5×2 mm | Corner-mounted sensors |
| 10 | Divider Fins | 4 | 1.5×4×8 mm | Sun-blocking separators |
| 11 | Cable Channel | 1 | 3×80×4 mm | Wire routing |

---

## Post-Print Modifications

### 1. **Add Servo Motors**
   - Insert **MG90S servo** at azimuth base (component #3)
   - Insert **MG90S servo** at elevation bearing left side
   - Use M2 screws (6-8 mm) to secure

### 2. **Install LDR Sensors**
   - Drill Ø3 mm holes at each of 4 corner housings
   - Press-fit standard **5mm LDR resistors**
   - Glue with hot glue or epoxy (not super glue — brittle on plastic)

### 3. **Add Rotation Joints**
   - Use **M3×20 mm bolts** as axles at elevation bearings
   - Add **M3 washers** on both sides
   - Tighten with **M3 lock nuts** (not too tight — should rotate freely)

### 4. **Wiring & Electronics**
   - Route 4 LDR signal wires through **cable channel** (#11)
   - Servo wires also through channel
   - All wires exit at bottom of pole for connection to Arduino

### 5. **Optional Enhancements**
   - **Bearing upgrade:** Replace printed bearings with **brass inserts** (M3 threaded) for durability
   - **Paint:** Use spray paint to distinguish components (blue for panel, gray for frame)
   - **Sealing:** Apply **resin coating** if printing in harsh conditions

---

## Orientation Tips During Printing

**Best orientation:** Base plate flat on print bed

**Why:** Reduces supports needed, minimizes print time, and ensures structural strength where most load occurs.

**Support structure:** Enable for:
- Horizontal arm overhang
- Panel frame (middle section)
- Top portions of LDR housings

---

## Assembly Order

1. Print all parts (single print, no separate exports needed)
2. Clean excess support material with knife/sandpaper
3. Locate and install both servo motors
4. Press-fit LDR sensors into corner housings
5. Install M3 axle bolts through elevation bearings
6. Route wires through cable channel
7. Mount electronics (Arduino, motor driver) to base plate using zip ties or double-sided tape
8. Test azimuth rotation → should spin freely
9. Test elevation tilt → should tilt up/down smoothly
10. Upload Arduino code and test with LDR sensors

---

## Electrical Integration Points

**From STL model to Arduino Uno:**

```
LDR Sensor Positions:
  - Top-Left:    A0
  - Top-Right:   A1
  - Bottom-Left: A2
  - Bottom-Right:A3

Servo Motor Connections:
  - Azimuth (base):  Pin 10 (signal), 5V power
  - Elevation (tilt):Pin 9 (signal), 5V power
```

---

## Troubleshooting Print Issues

| Issue | Cause | Fix |
|-------|-------|-----|
| Supports too thick | STL sliced badly | Increase support angle to 60°+, use tree supports |
| Panel warps | High print temp | Reduce nozzle to 200°C, use brim |
| Pole bends after print | Needs reinforcement | Consider printing pole separately with higher infill (40%) |
| Bearings too tight | Tolerance issue | Drill out bearing holes to Ø4.5 mm |
| Servo doesn't fit | Geometry mismatch | Sand bearing pocket walls by 1 mm |

---

## Scaling for Larger Prints

To print at **2× scale** (for real-world prototype):
- Import STL into Cura/PrusaSlicer
- Set scale to **200%**
- Increase infill to **30%** (more structural stress)
- Double all hardware sizes (M6 bolts instead of M3, larger servos)
- Expect print time: **36-48 hours**

---

## Material Recommendations

| Material | Pros | Cons | Cost |
|----------|------|------|------|
| **PLA** | Easy, low temp, detailed | Brittle, warps in sun | ~$15/kg |
| **PETG** | Strong, UV resistant | Requires care, slower | ~$18/kg |
| **ABS** | Durable, temperature stable | Hard to print, toxic fumes | ~$20/kg |
| **Nylon** | Tough, flexible | Moisture absorption, slow | ~$30/kg |

**Recommended for this project:** **PETG** (balance of strength and ease)

---

## Weight & Performance

- **Print weight:** ~180g (PLA), ~200g (PETG)
- **Max load at panel:** ~500g (recommend small 2-5W solar panel for balance)
- **Rotation speed:** ~1 sec per degree (servo-dependent)
- **Accuracy:** ±1-2° (limited by servo resolution)

---

## File Format Notes

- **STL format:** ASCII, units in millimeters
- **Compatible slicers:** Cura, PrusaSlicer, IdeaMaker, Simplify3D
- **Pre-supports:** Not included (add in your slicer)
- **Wall thickness:** 3-4 mm throughout (adequate for 3D printing)

---

## Next Steps After Printing

1. ✓ Print & assemble the model
2. ✓ Install Arduino + electronics
3. ✓ Upload the provided `.ino` code
4. ✓ Test LDR sensors with Serial Monitor
5. ✓ Calibrate threshold values
6. ✓ Mount a real solar panel
7. ✓ Deploy outdoors!

---

**Questions?** Adjust `THRESHOLD`, `SERVO_STEP`, and `LOOP_DELAY_MS` in the Arduino code to fine-tune tracking sensitivity.
