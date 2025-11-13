## Autonomous Waiter Line-Following Robot

An Arduino-based intelligent line-following robot with a built-in “Waiter System” — capable of moving to a destination point, performing a 360° rotation, and automatically returning to its starting position.  
This system combines precision motor control, adaptive speed, and state-driven automation for realistic and smooth motion.

---

### 🚀 Features
- Intelligent line tracking using three IR sensors (Left, Middle, Right)
- Smooth acceleration and deceleration via PWM-based speed ramping
- Adaptive differential steering for high-accuracy line following
- 360° rotation system at destination point
- Automatic return-to-base behavior
- Modular and customizable control parameters (speed, rotation time, sensitivity)

---

### ⚙️ Hardware Requirements
Arduino Uno or Nano  
L298N / L293D motor driver module  
2 DC motors (left and right drive wheels)  
3 IR line sensors (Left, Middle, Right)  
7–12V battery pack  
Chassis and wheels (two-wheel drive base)

---

### 🧠 Working Principle
1. The robot follows a black line using three infrared sensors.  
2. When all sensors detect the line simultaneously, it recognizes the target point.  
3. It then performs a 360° rotation, simulating a delivery turnaround.  
4. After rotation, it switches to return mode, retracing the same path to its starting point.  
5. Upon detecting all sensors on the line again, it stops in idle mode, completing the cycle.

---

### 💻 Code Overview
The logic operates as a finite state machine with four operational modes:
1. **FORWARD_RUN** → Normal line-following motion  
2. **ROTATING** → Performs the 360° spin  
3. **RETURN_RUN** → Follows line in reverse direction back to start  
4. **IDLE** → System stop after return

All motion behaviors (forward, turn, rotation) use PWM-based speed control with adaptive acceleration to ensure stability.

---

### 📂 Repository Contents
waiter_bot.ino — Main Arduino code  
/media — Demo videos and photos  
README.md — Project documentation

---

### 📹 Demonstration
After uploading, include your videos here or embed YouTube links.  
Example:  
[![Watch the video](https://img.youtube.com/vi/VIDEO_ID/0.jpg)](https://youtube.com/watch?v=VIDEO_ID)

---

### 🧩 Customization
- Adjust `rotationDuration` for a precise 360° spin (2000–3000 ms range).  
- Modify `baseSpeed`, `maxSpeed`, and `turnBoost` to match motor power and track sharpness.  
- Tune `accelStep` and `adjustInterval` to control responsiveness and smoothness.

---

### 🔧 Future Enhancements
- PID-controlled steering for advanced precision  
- Auto-calibration for rotation duration based on sensor feedback  
- Bluetooth or IoT remote command integration

---

### 📜 License
This project is released under the MIT License.  
You are free to use, modify, and distribute with attribution.
