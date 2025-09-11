#include <AccelStepper.h>

// Define stepper interface type
#define DRIVER AccelStepper::DRIVER

// CNC shield pin mapping
#define X_STEP 2
#define X_DIR 5
#define Y_STEP 3
#define Y_DIR 6
#define Z_STEP 4
#define Z_DIR 7

#define ENABLE_PIN 8   // Enable pin for all motors

// Create stepper objects
AccelStepper stepperX(DRIVER, X_STEP, X_DIR);
AccelStepper stepperY(DRIVER, Y_STEP, Y_DIR);
AccelStepper stepperZ(DRIVER, Z_STEP, Z_DIR);

// ====== USER PARAMETERS ======
float speedX = 400.0;
float speedY = 400.0;
float speedZ = 400.0;

// Store last speeds for START command
float lastSpeedX = speedX;
float lastSpeedY = speedY;
float lastSpeedZ = speedZ;

String inputString = ""; 

void setup() {
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, LOW); // LOW = enable drivers

  Serial.begin(115200);
  Serial.println("Enter speeds like: X500 Y-300 Z100");
  Serial.println("STOP stops motors, START resumes last speeds.");

  // Set max speed + acceleration
  stepperX.setMaxSpeed(2000);
  stepperY.setMaxSpeed(2000);
  stepperZ.setMaxSpeed(2000);

  stepperX.setAcceleration(800);
  stepperY.setAcceleration(800);
  stepperZ.setAcceleration(800);

  // Apply initial speeds
  stepperX.setSpeed(speedX);
  stepperY.setSpeed(speedY);
  stepperZ.setSpeed(speedZ);
}

void loop() {
  // Run motors at current speeds
  stepperX.runSpeed();
  stepperY.runSpeed();
  stepperZ.runSpeed();

  // Handle serial input
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {  // End of command
      parseCommand(inputString);
      inputString = "";
    } else {
      inputString += c;
    }
  }
}

void parseCommand(String cmd) {
  cmd.trim();      
  cmd.toUpperCase();

  // STOP command
  if (cmd.startsWith("STOP")) {
    // Save current speeds
    lastSpeedX = speedX;
    lastSpeedY = speedY;
    lastSpeedZ = speedZ;

    // Stop motors
    speedX = 0;
    speedY = 0;
    speedZ = 0;
    stepperX.setSpeed(0);
    stepperY.setSpeed(0);
    stepperZ.setSpeed(0);
    Serial.println("⚠️ All motors stopped.");
    return;
  }

  // START command
  if (cmd.startsWith("START")) {
    speedX = lastSpeedX;
    speedY = lastSpeedY;
    speedZ = lastSpeedZ;
    stepperX.setSpeed(speedX);
    stepperY.setSpeed(speedY);
    stepperZ.setSpeed(speedZ);
    Serial.println("▶️ Motors resumed last speeds.");
    return;
  }

  // X-axis
  int xIndex = cmd.indexOf('X');
  if (xIndex != -1) {
    speedX = cmd.substring(xIndex + 1).toFloat();
    stepperX.setSpeed(speedX);   // negative values = reverse
    Serial.print("X speed set to: ");
    Serial.println(speedX);
  }

  // Y-axis
  int yIndex = cmd.indexOf('Y');
  if (yIndex != -1) {
    speedY = cmd.substring(yIndex + 1).toFloat();
    stepperY.setSpeed(speedY);
    Serial.print("Y speed set to: ");
    Serial.println(speedY);
  }

  // Z-axis
  int zIndex = cmd.indexOf('Z');
  if (zIndex != -1) {
    speedZ = cmd.substring(zIndex + 1).toFloat();
    stepperZ.setSpeed(speedZ);
    Serial.print("Z speed set to: ");
    Serial.println(speedZ);
  }
}

