# 🔧 Troubleshooting Guide
## Fire Alarm System — Analog & Arduino Implementations

---

## 📋 Table of Contents

1. [Analog (Transistor) Issues](#1-analog-transistor-issues)
2. [Gas Sensor Issues (Arduino)](#2-gas-sensor-issues-arduino)
3. [Buzzer Issues](#3-buzzer-issues)
4. [LED Issues](#4-led-issues)
5. [LCD Display Issues](#5-lcd-display-issues)
6. [Arduino & Upload Issues](#6-arduino--upload-issues)
7. [Tinkercad Simulation Issues](#7-tinkercad-simulation-issues)
8. [General Tips](#8-general-tips)

---

## 1. Analog (Transistor) Issues

### ❌ Alarm triggers constantly even without smoke
**Cause:** Sensor is too sensitive or transistor base is always getting voltage.
**Fix:**
- Add a **variable resistor (potentiometer)** in series with the sensor to tune sensitivity
- Check that the sensor output is truly LOW when no smoke is present (measure with multimeter)
- Ensure base resistor (1kΩ) is present — without it, excessive base current keeps transistor ON

---

### ❌ Alarm never triggers even when smoke is present
**Cause:** Transistor not switching ON — base voltage too low.
**Fix:**
- Verify base-emitter voltage reaches at least **0.7V** when smoke is detected
- Test sensor output directly with a multimeter — confirm it goes HIGH on smoke exposure
- Try a lower base resistor value (e.g. 470Ω) to allow more base current

---

### ❌ LED lights up but buzzer doesn't sound (or vice versa)
**Cause:** One component is faulty or incorrectly wired.
**Fix:**
- Test buzzer and LED independently by connecting directly to 5V
- Check polarity — buzzer and LED are both polarized components
- Verify both share the same collector node on the transistor

---

### ❌ Circuit works intermittently
**Cause:** Loose breadboard connections.
**Fix:**
- Press all components firmly into the breadboard
- Re-seat all jumper wires and alligator clip leads
- Avoid bending component legs too close to the breadboard surface

---

## 2. Gas Sensor Issues (Arduino)

### ❌ MQ-2 sensor always reads 0 or maximum
**Cause:** Sensor not warmed up or incorrect wiring.
**Fix:**
- MQ-2 requires a **warm-up time of 20–30 seconds** after power-on before stable readings
- Verify wiring: VCC → 5V, GND → GND, AO (analog out) → A0
- Do NOT use DO (digital out) pin for analog reading

---

### ❌ Alarm triggers without any smoke present
**Cause:** Threshold set too low or sensor is in a dusty/humid environment.
**Fix:**
- Increase the `THRESHOLD` value in code (default 300 — try 400 or 500):
  ```cpp
  const int THRESHOLD = 400;  // Raise to reduce false alarms
  ```
- Allow the sensor 1–2 minutes to stabilize after power-on
- Keep sensor away from humidity, dust, and alcohol vapors

---

### ❌ Alarm doesn't trigger even with obvious smoke
**Cause:** Threshold set too high or sensor faulty.
**Fix:**
- Lower the `THRESHOLD` value:
  ```cpp
  const int THRESHOLD = 200;  // Lower to increase sensitivity
  ```
- Open Serial Monitor to read live sensor values and calibrate threshold accordingly

---

## 3. Buzzer Issues

### ❌ Buzzer makes no sound
**Cause:** Buzzer polarity reversed or wrong pin.
**Fix:**
- Check polarity — buzzer has a **+** marked side (connect to signal pin) and **–** (connect to GND)
- Verify `BUZZER_PIN` matches the actual Arduino pin used
- Test buzzer directly: `digitalWrite(BUZZER_PIN, HIGH)` in `setup()`

---

### ❌ Buzzer produces a very faint sound
**Cause:** Insufficient drive current or active vs passive buzzer mismatch.
**Fix:**
- Use an **active buzzer** (has internal oscillator — just needs DC power)
- If using a passive buzzer, use `tone(BUZZER_PIN, 1000)` instead of `digitalWrite`

---

### ❌ Buzzer keeps sounding after smoke clears
**Cause:** Sensor reading still above threshold, or missing reset logic.
**Fix:**
- Check that `digitalWrite(BUZZER_PIN, LOW)` is in the `else` (safe) block of the loop
- Open Serial Monitor — confirm sensor reading drops below threshold when smoke clears

---

## 4. LED Issues

### ❌ Red LED stays ON always
**Cause:** Pin always HIGH or alarm condition never exits.
**Fix:**
- Confirm `digitalWrite(RED_LED, LOW)` is in the safe state block
- Check that sensor readings actually fall below threshold when air is clear

---

### ❌ Green and Red LEDs both ON at the same time
**Cause:** Logic error — both states executing simultaneously.
**Fix:**
- Ensure your `if/else` properly separates alarm and safe states — they must be mutually exclusive:
  ```cpp
  if (smokeLevel >= THRESHOLD) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  } else {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  ```

---

### ❌ LEDs are very dim
**Cause:** Current-limiting resistor value too high.
**Fix:**
- Use **220Ω resistors** for LEDs — values above 1kΩ make LEDs noticeably dim

---

## 5. LCD Display Issues

### ❌ LCD shows nothing / completely blank
**Cause:** Contrast too low or incorrect pin wiring.
**Fix:**
- **Adjust the potentiometer** (Vo pin) — rotate slowly until characters appear
- Verify LCD pin connections match the `LiquidCrystal` constructor in code:
  ```cpp
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
  //              RS EN D4 D5 D6 D7
  ```

---

### ❌ LCD shows garbled characters
**Cause:** Pin mismatch between wiring and code.
**Fix:**
- Re-check every LCD wire against the pin order in `LiquidCrystal lcd(...)` constructor
- Call `lcd.clear()` at start of `setup()` to reset the display

---

### ❌ Emergency message doesn't scroll
**Cause:** `scrollMessage()` not being called or smoke level dropped mid-scroll.
**Fix:**
- Confirm `scrollMessage(emergencyMsg)` is inside the alarm `if` block
- The function breaks early if smoke drops below threshold — this is by design for safety

---

## 6. Arduino & Upload Issues

### ❌ "Port not found" error
**Fix:**
- Reconnect USB cable — use a data cable, not a charge-only cable
- Go to **Tools → Port** and select the correct COM port
- Install CH340/FTDI drivers if using a clone Arduino board

---

### ❌ Compile error: LiquidCrystal not found
**Fix:**
- Go to **Sketch → Include Library → Manage Libraries**
- Search **"LiquidCrystal"** and click Install

---

### ❌ Code uploads but nothing happens
**Fix:**
- Open Serial Monitor at **9600 baud** to verify the program is running
- Press the **Reset button** on Arduino after uploading

---

## 7. Tinkercad Simulation Issues

### ❌ MQ-2 sensor doesn't respond to smoke in simulation
**Fix:**
- Click on the **MQ-2 sensor** during simulation — a slider appears
- Drag the slider to simulate smoke levels and watch the LCD/LEDs/buzzer respond

---

### ❌ LCD stays blank in simulation
**Fix:**
- Click the **potentiometer** and rotate it during simulation to adjust contrast
- Verify the potentiometer wiper is connected to the LCD **Vo** pin

---

### ❌ Buzzer not sounding in Tinkercad
**Fix:**
- Make sure your browser audio is not muted
- Tinkercad buzzer sound requires the simulation to be actively running

---

### ❌ Simulation runs but LEDs don't change state
**Fix:**
- Check pin numbers in code match physical connections in the Tinkercad circuit
- Adjust the gas sensor slider above and below the threshold value to trigger state changes

---

## 8. General Tips

| Tip | Details |
|-----|---------|
| 🌡️ Warm up MQ-2 | Always wait 30 seconds after power-on for stable readings |
| 📋 Use Serial Monitor | Print `smokeLevel` every loop to calibrate your threshold |
| 🔁 Test components solo | Test buzzer, LEDs, and LCD independently before full integration |
| 🎛️ Tune threshold | Adjust `THRESHOLD` based on Serial Monitor readings in your environment |
| 🔌 Check polarity | Buzzer, LEDs, and electrolytic capacitors are all polarized |
| 💾 Save Tinkercad | Save your simulation project frequently |
| 🧪 Analog test first | For the analog circuit, confirm transistor switches with a multimeter before adding buzzer/LED |

---

## 📬 Still Having Issues?

- [Arduino Documentation](https://docs.arduino.cc/)
- [LiquidCrystal Library Reference](https://www.arduino.cc/reference/en/libraries/liquidcrystal/)
- [MQ-2 Sensor Datasheet](https://www.pololu.com/file/0J309/MQ2.pdf)
- [Tinkercad Support](https://www.tinkercad.com/learn)

---

*Troubleshooting Guide — Fire Alarm System*
*Author: Mamoon | Course: Engr. Fazeel Abbas*
