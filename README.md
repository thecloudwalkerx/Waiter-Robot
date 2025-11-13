# EZBot: Basic Line Following Robot 🤖

EZBot is an Arduino-based line-following robot designed to follow a predefined path using three Infrared (IR) line sensors and motor control. It implements basic movement functions to navigate straight, curved, and steep lines, while demonstrating precise step-based line-following behavior.

---

## ✨ Project Idea & Implementation

The goal of this project is to create a simple yet functional line-following robot. The robot uses three IR sensors — Left (LS), Middle (MS), and Right (RS) — to detect the line and determine the appropriate movement.

Implemented movement functions:

- **moveForward()** — moves straight when only the middle sensor detects the line.  
- **turnLeft() / turnRight()** — adjusts the path when the line deviates to the sides.  
- **sharpLeft() / sharpRight()** — handles steep curves detected by two sensors.  
- **stopBot()** — stops the robot when all sensors detect the line or no sensors detect it.

The robot’s behavior is managed in the `loop()` function, which continuously reads sensor inputs and executes the corresponding movement function. Each movement function sets motor directions and PWM speeds for a short duration and then stops, providing step-based control for basic line following.

---

## 💻 Code Overview

- **Sensor Logic:**  
  - **Forward:** Only the Middle Sensor is active (`MS` ON, `LS` and `RS` OFF).  
  - **Turn Left:** Left sensor ON, Right sensor OFF (MS may vary).  
  - **Turn Right:** Right sensor ON, Left sensor OFF (MS may vary).  
  - **Sharp Left:** Middle and Left sensors ON, Right sensor OFF.  
  - **Sharp Right:** Middle and Right sensors ON, Left sensor OFF.  
  - **Stop:** All sensors ON, or no sensors ON.

- **Movement Functions:**  
  - Each function sets the motor driver pins for a brief duration and then stops using `stopBot()`.  
  - This step-based control allows the robot to adjust direction based on the line detected by the sensors.

- **Acceleration & Motor Control (Enhanced Version):**  
  - Optional PWM-based speed ramping can be used to provide smooth acceleration and deceleration.  
  - Differential motor speeds improve precision when navigating curves.  
  - Functions like `moveForward()`, `moveSlightLeft()`, `moveSlightRight()`, `sharpLeft()`, and `sharpRight()` can be tuned with speed parameters for smoother motion.

---

## ⚙️ Hardware Requirements

- Arduino Uno or compatible board  
- L298N or L293D Motor Driver  
- 2 DC motors (left and right drive wheels)  
- 3 IR line sensors (Left, Middle, Right)  
- Chassis with wheels  
- Battery pack or external power supply  
- Jumper wires

---

## 🔧 Future Enhancements

- Implement continuous motion by removing `stopBot()` and `delay()` calls inside movement functions for smoother line following.  
- Separate functions for straight, curved, and steep lines to optimize path tracking.  
- Incorporate PID control for high-accuracy line-centering and turning.  
- Add advanced features such as endpoint rotation and automatic return-to-start behavior.
