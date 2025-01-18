# Housefly Autopilot

In a simple drone, a pilot only controls the speed of the motors. By adjusting the motors' speed individually, they can maneuver the flying vehicle. In the real world, pilots make each action based on the perceived result of their previous actions until the goal is achieved. An autopilot’s perception is based on sensor data, such as angle, position, altitude, etc. This approach aligns well with the goals of achieving **stable maneuverability** while providing a **safer** testing environment. The ability to monitor and intervene in real-time makes it ideal for early-stage development, where issues and edge cases are more likely to arise. Additionally, the insights gained from this setup can help refine the onboard systems if we decide to pivot to a fully autonomous onboard solution in the future.

![housefly autopilot](./public/image/logo.webp)

# What is GCU?

A Ground Control Unit (GCU) receives the drone's condition data and controls it by sending a set of commands through wireless communication.

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
