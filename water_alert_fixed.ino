// water_alert_fixed.ino

#include <SomeLibraries.h>

const int waterSensorPin = A0;
const int ultrasonicSensorPin = A1;

int waterLevelThresholds[] = {7, 5, 2}; // Water levels in cm
unsigned long lastAlertTime = 0;
const unsigned long alertInterval = 40000; // 40 seconds

void setup() {
    // Initial setup
    Serial.begin(9600);
}

void loop() {
    int waterLevel = readWaterLevel();
    if (isCriticalLevel(waterLevel)) {
        sendSMSAlert(waterLevel);
    }
    delay(1000); // Delay for next reading
}

int readWaterLevel() {
    // Code to read water level
    return analogRead(waterSensorPin); // Replace with actual reading logic
}

bool isCriticalLevel(int level) {
    for (int i = 0; i < sizeof(waterLevelThresholds) / sizeof(waterLevelThresholds[0]); i++) {
        if (level <= waterLevelThresholds[i]) {
            return true;
        }
    }
    return false;
}

void sendSMSAlert(int level) {
    unsigned long currentTime = millis();
    if (currentTime - lastAlertTime > alertInterval) {
        // Code to send SMS
        Serial.println("Alert! Water level at " + String(level) + " cm");
        lastAlertTime = currentTime;
    }
}