# Housefly Autopilot

In a simple drone, a pilot only controls the speed of the motors. By adjusting the motors' speed individually, they can maneuver the flying vehicle. In the real world, pilots make each action based on the perceived result of their previous actions until the goal is achieved. An autopilot’s perception is based on sensor data, such as angle, position, altitude, etc.

![housefly autopilot](./public/image/logo.webp)

# What is Housefly Drone?

The Housefly Drone is a prototype drone designed specifically for research and development of autopilot systems. It focuses on providing a stable, lightweight, and cost-effective platform for testing autonomous flight capabilities indoors. The Housefly Drone emphasizes simplicity, functionality, and safety, making it an ideal choice for prototyping and developing cutting-edge autopilot systems. Below is a concise overview of its design and features:

## Purpose

- To serve as a platform for developing and testing autopilot algorithms.
- Operates exclusively indoors, such as in a lab or a large room, under stable environmental conditions.

## Key Features

- Basic maneuvers: Takeoff, landing, stable hovering, 4-direction movement.
- Simultaneous movement and altitude adjustments (if feasible).
- Real-time, bidirectional communication with a Ground Control Unit (GCU)

## Payload and Build:

- No additional payload or equipment beyond the base configuration.
- Lightweight, DIY chassis crafted from flexible and strong materials.

# What is GCU?

A Ground Control Unit (GCU) receives the drone's condition data and controls it by sending a set of commands through wireless communication.
This approach aligns well with the goals of achieving **stable maneuverability** while providing a **safer** testing environment. The ability to monitor and intervene in real-time makes it ideal for early-stage development, where issues and edge cases are more likely to arise. Additionally, the insights gained from this setup can help refine the onboard systems if we decide to pivot to a fully autonomous onboard solution in the future.

## Pros:

- Uses a more powerful and flexible computer, like a Raspberry Pi
- No need to update the drone's software directly
- Enables longer flights by saving battery (reduces energy consumption for computation)
- Allows better online and offline flight monitoring and analysis
- Supports intervention and manual control when necessary

## Cons

- Requires longer development time
- More expensive due to the GCU
- Limited by the wireless coverage area
