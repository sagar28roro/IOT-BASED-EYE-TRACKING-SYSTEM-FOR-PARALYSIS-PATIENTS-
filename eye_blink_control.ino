#define IR_SENSOR_PIN  D5
#define RELAY_PIN      D1

unsigned long blinkStartTime = 0;
bool blinkInProgress = false;

const unsigned long MIN_BLINK_TIME = 200;
const unsigned long MAX_BLINK_TIME = 1500;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  int sensorState = digitalRead(IR_SENSOR_PIN);

  if (sensorState == LOW && !blinkInProgress) {
    blinkStartTime = millis();
    blinkInProgress = true;
  }

  if (sensorState == HIGH && blinkInProgress) {
    unsigned long blinkDuration = millis() - blinkStartTime;
    blinkInProgress = false;

    if (blinkDuration >= MIN_BLINK_TIME && blinkDuration <= MAX_BLINK_TIME) {
      toggleRelay();
    }
  }
}

void toggleRelay() {
  bool currentState = digitalRead(RELAY_PIN);
  digitalWrite(RELAY_PIN, !currentState);
  delay(1000);
}
