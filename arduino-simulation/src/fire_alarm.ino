#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ── Pin Definitions ───────────────────────────────────────────
const int GAS_SENSOR_PIN = A0;
const int BUZZER_PIN     = 8;
const int RED_LED        = 12;
const int GREEN_LED      = 11;

// ── Detection Threshold (0–1023) ──────────────────────────────
const int THRESHOLD = 300;   

// ── Emergency Message ─────────────────────────────────────────
String emergencyMsg = "Emergency exit is right to the elevator Fire and Rescue Dial 101 immediately ";

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
    lcd.setCursor(0, 0);
    lcd.print("!! FIRE ALARM !!");
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
void scrollMessage(String msg) {
  int msgLen = msg.length();
  for (int pos = 0; pos < msgLen - 15; pos++) {
    lcd.setCursor(0, 1);
    lcd.print(msg.substring(pos, pos + 16));
    delay(300);
    if (analogRead(GAS_SENSOR_PIN) < THRESHOLD) break;
  }
}
