# Wiring Diagram & Schematic

Complete electrical connections for the dual-axis solar tracker.

## System Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    Arduino Uno (ATmega328)                  │
│  ┌───────────────────────────────────────────────────────┐  │
│  │  A0 ◄─── LDR Top-Left        PWM Pin 9  ──► Servo 2  │  │
│  │  A1 ◄─── LDR Top-Right       PWM Pin 10 ──► Servo 1  │  │
│  │  A2 ◄─── LDR Bottom-Left     GND ────────────────┐   │  │
│  │  A3 ◄─── LDR Bottom-Right    5V ─────────────────┼───┼─┬┘  │
│  │                                                  │   │ │
│  └───────────────────────────────────────────────────────┘ │
│                         ↓                                   │
└──────────────────────────┼───────────────────────────────────┘
                           │
                    USB Power Supply
                      (5V / 2A min)
                           │
        ┌──────────────────┼──────────────────┐
        │                  │                  │
     ┌──▼────┐         ┌──▼────┐         ┌──▼────┐
     │Servo 1│         │Servo 2│         │ LDRs  │
     │Azimuth│         │Elevation       │Circuit│
     └───────┘         └───────┘         └───────┘
```

---

## Pin Assignments

### Analog Input (A0-A3)

| Pin | Component | Signal | Purpose |
|-----|-----------|--------|---------|
| A0 | LDR 1 | Top-Left light level | Upper-left quadrant sensing |
| A1 | LDR 2 | Top-Right light level | Upper-right quadrant sensing |
| A2 | LDR 3 | Bottom-Left light level | Lower-left quadrant sensing |
| A3 | LDR 4 | Bottom-Right light level | Lower-right quadrant sensing |

### Digital PWM Output (3,5,6,9,10,11)

| Pin | Component | Signal | Frequency | Duty Cycle |
|-----|-----------|--------|-----------|------------|
| 9 | Servo 2 (Elevation) | Control signal | 50 Hz | 1-2 ms pulse |
| 10 | Servo 1 (Azimuth) | Control signal | 50 Hz | 1-2 ms pulse |

### Power Pins

| Pin | Use | Voltage | Max Current |
|-----|-----|---------|------------|
| 5V | Logic supply, servo signal | 5V | 400 mA |
| GND | Ground reference | 0V | - |

---

## LDR Sensor Circuit

Each LDR uses a **voltage divider** with a 10kΩ pull-down resistor:

```
        5V
        │
        │
      ┌─┴─┐
      │LDR│  (GL5506 or similar)
      └─┬─┘
        │
        ├─────► Analog Pin (A0-A3)
        │
        ├─┐
        │ │ 10kΩ resistor (1/4W)
        │ │ (carbon or metal film)
        │ │
        │ GND
        │
       GND
```

### LDR Readings (Voltage Divider Output)

```
Light Level     Resistance (Ω)    Voltage (V)    ADC Value (0-1023)
─────────────────────────────────────────────────────────────────
Full sunlight   100-200 Ω         0.2-0.5 V      40-100
Bright indoor   1 kΩ              0.8 V          160
Dim indoor      10 kΩ             2.4 V          500
Very dark       100 kΩ+           4.5-5.0 V      900+
```

### Physical Placement

```
          Panel (top view)
    ┌─────────────────────┐
    │  TL ◄──► TR         │
    │  ↑         ↑        │
    │  │    Panel    │        │
    │  │   Cells   │        │
    │  ↓         ↓        │
    │  BL ◄──► BR         │
    └─────────────────────┘

TL = A0 (Top-Left)
TR = A1 (Top-Right)
BL = A2 (Bottom-Left)
BR = A3 (Bottom-Right)

Divider: ┌─┐ shaped shadow blocker
         │ │ between each pair prevents
         └─┘ cross-talk between LDRs
```

---

## Servo Motor Connections

### MG90S Servo Pinout

```
┌─────────────┐
│  Servo     │
│   MG90S    │
│            │
│ Wire Color │ Signal
│ ────────── │ ───────────
│ Red        │ 5V Power
│ Brown      │ Ground (GND)
│ Yellow     │ Control Signal (PWM)
│            │
└─────────────┘
```

### Servo 1 (Azimuth — Horizontal Rotation)

**Location:** Base of tracker (azimuth bearing ring)

```
Servo 1 (MG90S)
├─ Red wire (5V)     ──► Arduino 5V
├─ Brown wire (GND)  ──► Arduino GND
└─ Yellow wire (PWM) ──► Arduino Pin 10
```

**Rotation Range:** -80° to +80° (160° total)
- 0° = pointing forward
- Positive = rotate right
- Negative = rotate left

### Servo 2 (Elevation — Vertical Tilt)

**Location:** Left elevation bearing (on horizontal arm)

```
Servo 2 (MG90S)
├─ Red wire (5V)     ──► Arduino 5V
├─ Brown wire (GND)  ──► Arduino GND
└─ Yellow wire (PWM) ──► Arduino Pin 9
```

**Rotation Range:** -80° to +80° (160° total)
- 0° = horizontal (level)
- Positive = tilt upward
- Negative = tilt downward

---

## Complete Breadboard Wiring

```
Arduino Uno Breadboard Layout (top view)

┌─────────────────────────────────────────┐
│ POWER RAIL                              │
│ ┌─────┬─────────────┬─────┬─────────┐   │
│ │ +5V │    GND      │ +5V │   GND   │   │
│ └─────┴─────────────┴─────┴─────────┘   │
│                                         │
│ ┌─ USB ─┐                               │
│ │ Power │ ────► 5V (+) ─────────────┐   │
│ │Supply │ ────► GND (─) ─────────┬──┴───┼───┐
│ └───────┘                        │      │   │
│                                  ▼      ▼   ▼
│         LDR Circuits (×4)
│ ┌─────────────────────────┐
│ │ 5V ──[LDR_TL]──┬──► A0  │
│ │               │         │
│ │              [10kΩ]    │
│ │               │         │
│ │              GND        │
│ └─────────────────────────┘
│
│ (Repeat for A1, A2, A3 with LDR_TR, LDR_BL, LDR_BR)
│
│         Servo Connections
│ ┌──────────────────────────┐
│ │ Servo 1 (Azimuth)        │
│ │ Red   ──► +5V            │
│ │ Brown ──► GND            │
│ │ Yellow──► Pin 10 (PWM)   │
│ └──────────────────────────┘
│
│ ┌──────────────────────────┐
│ │ Servo 2 (Elevation)      │
│ │ Red   ──► +5V            │
│ │ Brown ──► GND            │
│ │ Yellow──► Pin 9 (PWM)    │
│ └──────────────────────────┘
│
└─────────────────────────────────────────┘
```

---

## Wiring Checklist

- [ ] **LDR A0 (Top-Left)**
  - [ ] 5V to LDR anode
  - [ ] LDR cathode to 10kΩ resistor
  - [ ] 10kΩ resistor to GND
  - [ ] Junction (between LDR & resistor) to Arduino A0

- [ ] **LDR A1 (Top-Right)**
  - [ ] 5V to LDR anode
  - [ ] LDR cathode to 10kΩ resistor
  - [ ] 10kΩ resistor to GND
  - [ ] Junction to Arduino A1

- [ ] **LDR A2 (Bottom-Left)**
  - [ ] 5V to LDR anode
  - [ ] LDR cathode to 10kΩ resistor
  - [ ] 10kΩ resistor to GND
  - [ ] Junction to Arduino A2

- [ ] **LDR A3 (Bottom-Right)**
  - [ ] 5V to LDR anode
  - [ ] LDR cathode to 10kΩ resistor
  - [ ] 10kΩ resistor to GND
  - [ ] Junction to Arduino A3

- [ ] **Servo 1 (Azimuth)**
  - [ ] Red wire to 5V
  - [ ] Brown wire to GND
  - [ ] Yellow wire to Pin 10

- [ ] **Servo 2 (Elevation)**
  - [ ] Red wire to 5V
  - [ ] Brown wire to GND
  - [ ] Yellow wire to Pin 9

- [ ] **Power Supply**
  - [ ] USB cable connected to Arduino
  - [ ] Power supply rated 5V, minimum 2A

---

## Voltage Reference & ADC

### Arduino Analog-to-Digital Conversion

```
Analog Input Range: 0V to 5V
ADC Resolution: 10-bit (0-1023)
Conversion: ADC_value = (Vin / 5V) × 1023

Example:
- Vin = 0V  → ADC = 0
- Vin = 2.5V → ADC = 512
- Vin = 5V  → ADC = 1023
```

### Recommended ADC Thresholds

```
Bright sunlight zone (optimal for tracking):
  ADC range: 150-600 (0.7V - 2.9V)
  
Dim/cloudy:
  ADC range: 50-150

Darkness:
  ADC range: 0-50
```

---

## Troubleshooting Connections

| Symptom | Possible Cause | Check |
|---------|----------------|-------|
| Servo not moving | Wrong pin or no signal | Pin 9/10 connected? PWM output? |
| Servo twitching | Power issue | Supply 5V / 2A minimum |
| LDR readings constant (1023) | Open circuit | Check LDR soldering, resistor value |
| LDR readings constant (0) | Short circuit | Check for solder bridges, correct polarity |
| Noisy LDR readings | Long cables, EMI | Use shielded cable, keep away from motors |
| Servo moves wrong direction | Reversed signal | Swap pins or invert in code |

---

## Cable Recommendations

- **Signal wires** (LDR analog, servo control): 22 AWG or 24 AWG stranded
- **Power wires** (5V to servos): 20 AWG or 18 AWG (lower resistance)
- **Ground wires** (common return): 20 AWG minimum
- **Cable length**: Keep under 1 meter for noise immunity
- **Shielding**: Use twisted pair or shielded cable for long analog runs

---

## Notes

- All GND connections must be common (star connection to USB supply GND)
- Use a separate USB power supply rated for 2A minimum (servos draw ~1.5A peak)
- LDR values (GL5506) are typical; adjust resistor if different LDR type used
- Servo signal wires should not run parallel to high-current power lines
