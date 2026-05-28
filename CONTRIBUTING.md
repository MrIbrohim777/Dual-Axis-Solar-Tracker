# Contributing to Dual-Axis Solar Tracker

Thank you for your interest in contributing! This project welcomes improvements, bug fixes, optimizations, and new features.

## How to Contribute

### Reporting Bugs

Found an issue? Please create a GitHub Issue with:

1. **Title:** Clear, concise description (e.g., "Servo oscillates in bright sunlight")
2. **Description:** What happened?
3. **Steps to Reproduce:** How to trigger the bug
4. **Expected Behavior:** What should happen
5. **Actual Behavior:** What actually happened
6. **Environment:**
   - Arduino board (Uno, Nano, etc.)
   - Servo type (MG90S, SG90, etc.)
   - Location / lighting conditions
   - Arduino IDE version
   - Firmware version (commit hash)

### Suggesting Enhancements

Have an idea? Open an Issue with:

1. **Title:** Feature request title
2. **Description:** What problem does it solve?
3. **Why:** Why is this useful?
4. **Alternatives:** How do users work around it now?
5. **Implementation ideas:** (optional) How might this be done?

### Submitting Code Changes

1. **Fork** the repository
2. **Create a branch** for your feature:
   ```bash
   git checkout -b feature/your-feature-name
   ```

3. **Make changes** following the code style guidelines below
4. **Test thoroughly:**
   - Verify hardware still responds correctly
   - Check Serial Monitor output for expected values
   - Test calibration procedure from CALIBRATION_GUIDE.md

5. **Commit with clear messages:**
   ```bash
   git commit -m "Add cloud detection algorithm"
   git commit -m "Fix servo direction reversal bug"
   ```

6. **Push to your fork:**
   ```bash
   git push origin feature/your-feature-name
   ```

7. **Open a Pull Request** with:
   - Clear title and description
   - Reference any related issues (#123)
   - Explanation of changes
   - Testing performed

## Code Style Guidelines

### Arduino (C++)

- **Indentation:** 2 spaces (not tabs)
- **Line length:** Max 100 characters
- **Comments:** Use `//` for single-line, `/* */` for blocks
- **Naming:**
  - Constants: `UPPER_CASE_WITH_UNDERSCORES`
  - Variables: `camelCase`
  - Functions: `camelCase`
  - Private members: `_leadingUnderscore`

**Example:**

```cpp
// Reading and comparing LDR values
const int LDR_THRESHOLD = 15;
int topBrightness = (ldrTL + ldrTR) / 2;

void adjustElevation(int difference) {
  if (abs(difference) > LDR_THRESHOLD) {
    moveServo(ELEVATION_PIN, difference > 0 ? UP : DOWN);
  }
}
```

### Markdown Documentation

- **Headers:** Use `#`, `##`, `###` (no single `#` in middle of file)
- **Code blocks:** Use triple backticks with language (```cpp, ```bash)
- **Links:** Use descriptive text: `[link text](url)` not bare URLs
- **Lists:** Use `-` for unordered, `1.` for ordered
- **Emphasis:** Use `**bold**` and `*italic*`, not `__bold__` or `_italic_`

## Areas for Contribution

### High Priority

- [ ] Cloud detection algorithm (prevent tracking shadows)
- [ ] GPS-based sun prediction (alternative to light sensing)
- [ ] Data logging to SD card
- [ ] Outdoor weatherproofing (epoxy coating, seals)
- [ ] Efficiency calculator (actual power output measurements)

### Medium Priority

- [ ] Web dashboard for remote monitoring (ESP32 version)
- [ ] Seasonal latitude adjustments
- [ ] Dual-panel support (larger arrays)
- [ ] Temperature compensation for servo drift
- [ ] Battery backup circuit

### Nice-to-Have

- [ ] KiCad schematic file
- [ ] Fusion 360 CAD model (editable)
- [ ] Multi-language documentation (español, 中文, etc.)
- [ ] PID controller tuning options
- [ ] Machine learning for weather prediction

## Testing Checklist

Before submitting a PR, verify:

- [ ] Code compiles without warnings
- [ ] Hardware responds as expected
- [ ] Serial Monitor shows expected output
- [ ] No new magic numbers (use named constants)
- [ ] Changes don't break existing calibration
- [ ] Documented with comments where unclear
- [ ] All new code follows style guidelines

## Documentation Changes

When you update code, please also update:

1. **Inline comments** — Explain the "why" not the "what"
2. **README.md** — If feature is user-facing
3. **CALIBRATION_GUIDE.md** — If tuning parameters changed
4. **WIRING_DIAGRAM.md** — If hardware connections changed

## Review Process

A maintainer will:

1. Review your code for correctness
2. Check alignment with project goals
3. Request changes if needed
4. Merge once approved

Response time: typically 3-7 days.

## Community Standards

This project adheres to the Contributor Covenant Code of Conduct. Be respectful, inclusive, and constructive.

## Questions?

- **General:** Open a Discussion in the repo
- **Technical:** Create an Issue with detailed steps
- **Ideas:** Start a Discussion before beginning major work

---

## Thank You!

Every contribution — bug reports, ideas, code, docs — helps make this project better. We appreciate your time and effort! 🌞
