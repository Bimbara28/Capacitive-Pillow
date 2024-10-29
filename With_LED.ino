#include <CapPin.h>
#include <Keyboard.h>

// Capacitive pins for arrow keys
CapPin cPin_6 = CapPin(3);   // Pin for left arrow key
CapPin cPin_7 = CapPin(10);  // Pin for right arrow key
CapPin cPin_8 = CapPin(9);  // Pin for up arrow key
CapPin cPin_9 = CapPin(2);   // Pin for down arrow key

// The keys that should be sent when the pins are touched
char leftKey = KEY_LEFT_ARROW;
char rightKey = KEY_RIGHT_ARROW;
char upKey = KEY_UP_ARROW;
char downKey = KEY_DOWN_ARROW;

// LED pin configuration
const int ledPin =12; 

// Variables to track if the keys are currently pressed
boolean leftPressed = false;
boolean rightPressed = false;
boolean upPressed = false;
boolean downPressed = false;

// Dynamic threshold adjustment variables for each button
long baselineLeft = 0;
long baselineRight = 0;
long baselineUp = 0;
long baselineDown = 0;
long dynamicThresholdLeft = 0;
long dynamicThresholdRight = 0;
long dynamicThresholdUp = 0;
long dynamicThresholdDown = 0;

// Auto-calibration settings
int recalibrationTime = 5000;  // Recalibrate after 5 seconds of idle time
unsigned long lastInteractionTime = 0;  // Time of last sensor interaction
unsigned long idleTimeout = 10000;  // If idle for 10 seconds, recalibrate baseline

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.println("Start");

  // Calibrate the baseline for each sensor
  baselineLeft = calibrateSensor(cPin_6);
  baselineRight = calibrateSensor(cPin_7);
  baselineUp = calibrateSensor(cPin_8);
  baselineDown = calibrateSensor(cPin_9);

  // Set initial dynamic thresholds
  dynamicThresholdLeft = baselineLeft + 10;
  dynamicThresholdRight = baselineRight + 10;
  dynamicThresholdUp = baselineUp + 10;
  dynamicThresholdDown = baselineDown + 10;

  Serial.println("Baseline calibrated:");
  Serial.print("Left: "); Serial.println(baselineLeft);
  Serial.print("Right: "); Serial.println(baselineRight);
  Serial.print("Up: "); Serial.println(baselineUp);
  Serial.print("Down: "); Serial.println(baselineDown);
}

void loop() {
  delay(1);

  // Check for idle time and recalibrate if necessary
  if (millis() - lastInteractionTime > idleTimeout) {
    recalibrateSensors();
    lastInteractionTime = millis();
  }

  // Read the current sensor values
  long totalLeft = cPin_6.readPin(500);
  long totalRight = cPin_7.readPin(500);
  long totalUp = cPin_8.readPin(500);
  long totalDown = cPin_9.readPin(500);

  // Adjust thresholds for each button separately based on user interaction
  dynamicThresholdLeft = adjustThreshold(totalLeft, dynamicThresholdLeft, baselineLeft, leftPressed);
  dynamicThresholdRight = adjustThreshold(totalRight, dynamicThresholdRight, baselineRight, rightPressed);
  dynamicThresholdUp = adjustThreshold(totalUp, dynamicThresholdUp, baselineUp, upPressed);
  dynamicThresholdDown = adjustThreshold(totalDown, dynamicThresholdDown, baselineDown, downPressed);

  // Print sensor values and thresholds
  Serial.print("Left: "); Serial.print(totalLeft); Serial.print(" Threshold: "); Serial.println(dynamicThresholdLeft);
  Serial.print("Right: "); Serial.print(totalRight); Serial.print(" Threshold: "); Serial.println(dynamicThresholdRight);
  Serial.print("Up: "); Serial.print(totalUp); Serial.print(" Threshold: "); Serial.println(dynamicThresholdUp);
  Serial.print("Down: "); Serial.print(totalDown); Serial.print(" Threshold: "); Serial.println(dynamicThresholdDown);

  // Check if the current readings exceed the threshold for each button
  handleKeyPress(totalLeft, dynamicThresholdLeft, leftPressed, leftKey, "Left");
  handleKeyPress(totalRight, dynamicThresholdRight, rightPressed, rightKey, "Right");
  handleKeyPress(totalUp, dynamicThresholdUp, upPressed, upKey, "Up");
  handleKeyPress(totalDown, dynamicThresholdDown, downPressed, downKey, "Down");

  // Control the LED based on connection status
  if (isConnectedToComputer()) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED
  }

  delay(50);
}

void handleKeyPress(long sensorValue, long threshold, boolean &keyPressed, char key, const char* keyName) {
  if ((sensorValue > threshold) && (!keyPressed)) {
    Serial.println(String(keyName) + " Key Pressed");
    keyPressed = true;
    lastInteractionTime = millis();
    Keyboard.press(key); 
  } else if ((sensorValue <= threshold) && (keyPressed)) {
    Serial.println(String(keyName) + " Key Released");
    keyPressed = false;
    lastInteractionTime = millis();
    Keyboard.release(key);
  }
}

void recalibrateSensors() {
  baselineLeft = calibrateSensor(cPin_6);
  baselineRight = calibrateSensor(cPin_7);
  baselineUp = calibrateSensor(cPin_8);
  baselineDown = calibrateSensor(cPin_9);

  // Reset dynamic thresholds based on new baselines
  dynamicThresholdLeft = baselineLeft + 10;
  dynamicThresholdRight = baselineRight + 10;
  dynamicThresholdUp = baselineUp + 10;
  dynamicThresholdDown = baselineDown + 10;

  Serial.println("Sensors recalibrated after idle:");
  Serial.print("New Left Baseline: "); Serial.println(baselineLeft);
  Serial.print("New Right Baseline: "); Serial.println(baselineRight);
  Serial.print("New Up Baseline: "); Serial.println(baselineUp);
  Serial.print("New Down Baseline: "); Serial.println(baselineDown);
}

long calibrateSensor(CapPin &sensorPin) {
  long total = 0;
  int samples = 10;

  for (int i = 0; i < samples; i++) {
    total += sensorPin.readPin(500);
    delay(50);
  }

  return total / samples; // Return the average value
}

long adjustThreshold(long sensorValue, long currentThreshold, long baseline, boolean keyPressed) {
  long newThreshold = currentThreshold;

  if (sensorValue > currentThreshold) {
    // Adjust threshold if the sensor is pressed
    newThreshold = baseline + (sensorValue - baseline) / 2;
  } else {
    // Gradually decay the threshold if no activity
    newThreshold -= (newThreshold - baseline) / 50;
  }

  return newThreshold;
}

// Function to determine if the pillow is connected to the computer (pseudo-function)
bool isConnectedToComputer() {
  return true; 
}
