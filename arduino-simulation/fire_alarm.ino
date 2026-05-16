/*
 * ============================================================
 * Fire Alarm System — Arduino + MQ-2 Gas Sensor
 * ============================================================
 * Platform  : Arduino UNO
 * Simulation: Autodesk Tinkercad
 * Author    : Mamoon
 * Course    : Engr. Fazeel Abbas
 * ============================================================
 *
 * Description:
 * Detects smoke/gas using MQ-2 sensor. On detection:
 *   - Buzzer sounds
 *   - Red LED turns ON, Green LED turns OFF
 *   - LCD scrolls an emergency message
 * In safe state:
 *   - Green LED ON, Red LED OFF, Buzzer OFF
 *   - LCD shows "Air Quality: OK"
 *
 * Pin Map:
 *   MQ-2 Sensor (AO) → A0
 *   Buzzer            → Pin 8
 *   Red LED           → Pin 2
 *   Green LED         → Pin 3
 *   LCD RS            → Pin 7
 *   LCD EN            → Pin 6
 *   LCD D4–D7         → Pins 5, 4, 3... (see LiquidCrystal init)
 * ============================================================
 */

#include <LiquidCrystal.h>

// ── LCD Pin Configuration ─────────────────────────────────────
// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ── Pin Definitions ───────────────────────────────────────────
const int GAS_SENSOR_PIN = A0;
const int BUZZER_PIN     = 8;
const int RED_LED        = 12;
const int GREEN_LED      = 11;

// ── Detection Threshold (0–1023) ──────────────────────────────
const int THRESHOLD = 300;   // Adjust based on sensor sensitivity

// ── Emergency Message ─────────────────────────────────────────
String emergencyMsg = "Emergency exit is right   And Rescue Dial 1   ";

// ── Setup ─────────────────────────────────────────────────────
void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED,    OUTPUT);
  pinMode(GREEN_LED,  OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Fire  Alarm   ");
  lcd.setCursor(0, 1);
  lcd.print("   System Ready ");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("=== Fire Alarm System ===");
  Serial.println("Monitoring started...\n");
}

// ── Main Loop ─────────────────────────────────────────────────
void loop() {
  int smokeLevel = analogRead(GAS_SENSOR_PIN);

  Serial.print("Smoke Level: ");
  Serial.print(smokeLevel);

  if (smokeLevel >= THRESHOLD) {
    // ── ALARM STATE ─────────────────────────────────────────
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(RED_LED,    HIGH);
    digitalWrite(GREEN_LED,  LOW);

    Serial.println("  ⚠ ALARM TRIGGERED!");

    // Row 1: Alarm header
    lcd.setCursor(0, 0);
    lcd.print("!! FIRE ALARM !!");

    // Row 2: Scroll emergency message
    scrollMessage(emergencyMsg);

  } else {
    // ── SAFE STATE ──────────────────────────────────────────
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(RED_LED,    LOW);
    digitalWrite(GREEN_LED,  HIGH);

    Serial.println("  ✓ Safe");

    lcd.setCursor(0, 0);
    lcd.print("Air Quality: OK ");
    lcd.setCursor(0, 1);
    lcd.print("No Smoke Detected");

    delay(1000);
  }
}

// ── Helper: Scroll a message across LCD row 2 ────────────────
void scrollMessage(String msg) {
  int msgLen = msg.length();
  for (int pos = 0; pos < msgLen - 15; pos++) {
    lcd.setCursor(0, 1);
    lcd.print(msg.substring(pos, pos + 16));
    delay(300);

    // Re-check sensor mid-scroll to stay responsive
    if (analogRead(GAS_SENSOR_PIN) < THRESHOLD) break;
  }
}
