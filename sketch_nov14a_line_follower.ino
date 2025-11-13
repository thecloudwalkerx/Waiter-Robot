#define MS 12      // Middle Sensor
#define LS 13      // Left Sensor
#define RS 11      // Right Sensor

#define LM1 2      // Left Motor Direction
#define LM2 3      // Left Motor Speed (PWM)
#define RM1 4      // Right Motor Direction
#define RM2 5      // Right Motor Speed (PWM)

int currentSpeedL = 0;
int currentSpeedR = 0;

const int baseSpeed = 120;
const int maxSpeed = 255;
const int turnBoost = 40;
const int accelStep = 8;
unsigned long lastAdjust = 0;
const int adjustInterval = 20;

// ---- Motion State Machine ----
enum Mode { FORWARD_RUN, ROTATING, RETURN_RUN, IDLE };
Mode currentMode = FORWARD_RUN;
bool returning = false;
unsigned long rotationStart = 0;
const unsigned long rotationDuration = 2500; // adjust for ~360° turn (ms)

// ---- Smooth PWM control ----
void setMotorSpeed(int targetL, int targetR) {
  if (millis() - lastAdjust >= adjustInterval) {
    if (currentSpeedL < targetL) currentSpeedL += accelStep;
    else if (currentSpeedL > targetL) currentSpeedL -= accelStep;
    if (currentSpeedR < targetR) currentSpeedR += accelStep;
    else if (currentSpeedR > targetR) currentSpeedR -= accelStep;

    currentSpeedL = constrain(currentSpeedL, 0, 255);
    currentSpeedR = constrain(currentSpeedR, 0, 255);

    analogWrite(LM2, currentSpeedL);
    analogWrite(RM2, currentSpeedR);

    lastAdjust = millis();
  }
}

// ---- Motor Behaviors ----
void moveForward() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  setMotorSpeed(maxSpeed, maxSpeed);
}

void moveSlightLeft() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  setMotorSpeed(baseSpeed - turnBoost, baseSpeed + turnBoost);
}

void moveSlightRight() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  setMotorSpeed(baseSpeed + turnBoost, baseSpeed - turnBoost);
}

void sharpLeft() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, HIGH);
  setMotorSpeed(maxSpeed, maxSpeed);
}

void sharpRight() {
  digitalWrite(LM1, HIGH);
  digitalWrite(RM1, LOW);
  setMotorSpeed(maxSpeed, maxSpeed);
}

void stopCar() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, LOW);
  setMotorSpeed(0, 0);
}

// ---- Rotation (360° spin in place) ----
void rotate360() {
  digitalWrite(LM1, LOW);
  digitalWrite(RM1, HIGH);
  setMotorSpeed(maxSpeed, maxSpeed);
}

// ---- Line Following Routine ----
void followLine() {
  int ms = digitalRead(MS);
  int ls = digitalRead(LS);
  int rs = digitalRead(RS);

  if (ms && !ls && !rs) moveForward();
  else if (ms && ls && !rs) moveSlightLeft();
  else if (ms && !ls && rs) moveSlightRight();
  else if (!ms && ls && !rs) sharpLeft();
  else if (!ms && !ls && rs) sharpRight();
  else if (!ms && !ls && !rs) stopCar();
  else if (ms && ls && rs) {
    // All sensors detect line = endpoint
    stopCar();
    if (!returning) {
      Serial.println("Reached endpoint — rotating...");
      currentMode = ROTATING;
      rotationStart = millis();
    } else {
      Serial.println("Returned to start — stopping.");
      currentMode = IDLE;
    }
  }
}

// ---- MAIN LOOP ----
void loop() {
  switch (currentMode) {

    case FORWARD_RUN:
      Serial.println("Moving forward...");
      followLine();
      break;

    case ROTATING:
      rotate360();
      if (millis() - rotationStart > rotationDuration) {
        stopCar();
        returning = true;
        currentMode = RETURN_RUN;
        delay(500);
        Serial.println("Rotation complete — returning to base.");
      }
      break;

    case RETURN_RUN:
      Serial.println("Returning...");
      followLine();
      break;

    case IDLE:
      stopCar();
      Serial.println("Waiter task complete. Standing by.");
      break;
  }
  delay(10);
}

// ---- Setup ----
void setup() {
  Serial.begin(9600);
  pinMode(MS, INPUT);
  pinMode(LS, INPUT);
  pinMode(RS, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  Serial.println("System ready — Waiter mode active.");
}
