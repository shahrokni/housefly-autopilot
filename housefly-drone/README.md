**_This ARTICLE MAY INCLUDE SOME BASIC ELECTRONIC TECHNICAL TERMS!_**

# Housefly Drone

To test the **Autopilot** software, a test environment or an actual flying vehicle is required. This flying vehicle is called the **Housefly Drone**. The **Housefly Drone** is a cost-efficient, lightweight, and compact quadcopter designed to perform basic maneuvers, including takeoff, landing, stable hovering, and transitions.

## Housefly Drone Design Requirements

- Cost-efficient, lightweight, and compact
- Capable of performing basic maneuvers, including:
  - Takeoff
  - Landing
  - Stable hovering
  - Transitions
- Capable of continuous flight for 10 to 15 minutes
- Supports autopilot software updates
- Designed for easy replacement of electronic components
- Optimized for indoor environments
- Designed to receive emergency commands from **ATC**

## Bill of Material

- ESP8266 Wireless Module 1X
- MPU6050 1X
- HC SR04 1X
- Arduino 2560 1X
- Racerstar BR2205 2300KV Brush-less Motor 4X
- Racerstar RS20A 20A ESC 4X
- Gemfan 5030 (5x3) 2-blades propellers 4X
- Turnigy 3S 1500mAh 30C 1X
- Matek PDB-XT60 with 5V/12V BEC 1X

### ESP8266 Wireless Module

The ESP8266 is a low-cost Wi-Fi micro-controller, with built-in TCP/IP networking software, and micro-controller capability

### MPU6050

The MPU6050 is a 6-axis motion tracking device that integrates a 3-axis gyroscope and a 3-axis accelerometer in a single chip.

### HC SR04

The HC-SR04 is a popular ultrasonic sensor used for non-contact distance measurements

### Arduino 2560

The Arduino Mega 2560 is a micro-controller board based on the ATmega2560. It has 54 digital input/output pins (of which 15 can be used as PWM outputs), 16 analog inputs, 4 UARTs (hardware serial ports), a 16 MHz crystal oscillator, a USB connection, a power jack, an ICSP header, and a reset button.

### Racerstar BR2205 2300KV Brush-less Motor

A high-performance brush-less DC (BLDC) motor commonly used in racing drones and DIY quadcopters. It is known for its high RPM, durability, and efficiency, making it ideal for lightweight aerial applications

- **Type**: 3-phase brush-less motor
- **KV Rating**: 2300KV (rotates at 2300 RPM per volt applied)
- **Voltage Range**: Typically supports 2S–4S LiPo batteries (7.4V–14.8V)
- **Maximum Current**: ~27A
- **Stator Size**: 22mm diameter, 5mm height
- **Shaft Diameter**: 5mm
- **Mounting Pattern**: Standard quadcopter motor mounting

#### Thrust per Motor

Refers to the amount of force (usually measured in grams (g) or Newtons (N)) that a single motor and propeller combination can generate to lift an aircraft (e.g., a drone). It determines how much weight a drone can carry and how fast it can accelerate. For example, if a drone weighs 1,000g (1kg), and each of its four motors generates 800g of thrust, the total thrust is 3,200g. **_A good rule of thumb for drones is to have at least a 2:1 thrust-to-weight ratio, meaning the drone can generate twice the thrust needed for hovering_**, allowing for maneuverability. While having higher thrust than weight improves maneuverability, acceleration, and responsiveness, there should be a practical limit to how much thrust a drone has. **_If the thrust-to-weight ratio is too high, it can cause issues_**.

- **2:1** → Enough thrust for stable flight & basic maneuvers (good for autonomous drones).
- **3:1** → More responsive, allowing sharper movements.
- **4:1** → Very agile, suitable for racing or high-speed acrobatics.

**_Since Housefly Drone is designed for stability, controlled movement, and indoor testing, a 2:1 to 3:1 ratio should be ideal._**

**The thrust per motor depends on several factors, including**:

- Battery voltage (e.g., 2S, 3S, or 4S LiPo)
- Propeller size and pitch (e.g., 5045, 6045)
- ESC & motor efficiency
- Air density and environmental conditions

### Racerstar RS20A 20A ESC

The Racerstar RS20A 20A ESC is an Electronic Speed Controller (ESC) designed for small to medium-sized quadcopters and drones. It regulates the power sent from the LiPo battery to the brush-less motors, ensuring smooth and precise control over motor speed.

### Gemfan 5030 (5x3) 2-blades propellers

The Gemfan 5030 (5x3) are lightweight, efficient, and well-balanced propellers designed for small drones and quadcopters

### Turnigy 3S 1500mAh 30C

LiPo battery

### Matek PDB-XT60 with 5V/12V BEC

The Matek PDB-XT60 is a Power Distribution Board (PDB) designed for quadcopters and drones, providing stable power distribution to ESCs, flight controllers, and other electronic components.
