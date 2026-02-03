#define IR_SENSOR_PIN  D5      // Eye blink IR sensor
#define RELAY_PIN     D1      // Relay module

unsigned long blinkStartTime = 0;
bool blinkDetected = false;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); // Appliance OFF initially

  Serial.begin(9600);
  Serial.println("IoT Eye Tracking Assistive System Started");
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR_PIN);

  // Eye blink detected
  if (sensorValue == LOW && !blinkDetected) {
    blinkStartTime = millis();
    blinkDetected = true;
    Serial.println("Blink detected");
  }

  // Blink released
  if (sensorValue == HIGH && blinkDetected) {
    unsigned long blinkDuration = millis() - blinkStartTime;
    blinkDetected = false;

    // Valid blink duration (intentional blink)
    if (blinkDuration > 200 && blinkDuration < 1500) {
      toggleAppliance();
    }
  }
}

void toggleAppliance() {
  digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));

  if (digitalRead(RELAY_PIN) == HIGH) {
    Serial.println("Appliance ON");
  } else {
    Serial.println("Appliance OFF");
  }

  delay(1000); // Prevent multiple triggers
}
