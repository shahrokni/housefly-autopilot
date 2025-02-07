# Housefly Autopilot

In a simple drone (quadcopter), a pilot only controls the speed of the motors. By adjusting the motors' speed individually, they can maneuver the flying vehicle. In the real world, pilots make each action based on the perceived result of their previous actions until the goal is achieved. An autopilot’s perception is based on sensor data, such as angle, position, altitude, etc.

## Housefly Autopilot - State machine

The autopilot maintains an internal state machine that determines whether an instruction received from the ATC should be executed or not. Due to safety measures, **_received instructions are never queued!_** This means they are either executed immediately or rejected. For instance, a drone should not be able to change its destination if it is already in the `Transition` state.

### Ground state

The Ground state or `GND` refers to a stable state in which the drone is on the ground with all four rotors turned off. This should be the drone's initial state. Additionally, a successful landing operation should eventually set the state to `GND`.

### Take off state

The Takeoff state or `TO` refers to a temporary state in which the drone is lifting off the ground. This state should only be set if the drone's current state is `GND`. A successful takeoff operation eventually sets the state to `IDLE`.

### Landing state

The Landing state or `LND` refers to a temporary state in which the drone is descending to land on the ground. A successful landing operation eventually sets the state to `GND`.

### Transition state

The Transition state or `TRN` refers to a temporary state in which the drone moves from one coordinate in space to another. This state should only be set if the drone's current state is `IDLE`.

### Idle state

The Idle state or `IDLE` refers to a stable state in which the drone hovers in place.

### Halt state

The Halt state or `HLT` refers to an immediate emergency state in which all four rotors are turned off at once. Due to safety reasons, a drone may enter this state at any time.

# What is Housefly Drone?

The Housefly Drone is a prototype drone designed specifically for research and development of autopilot systems. It focuses on providing a stable, lightweight, and cost-effective platform for testing autonomous flight capabilities indoors. The Housefly Drone emphasizes simplicity, functionality, and safety, making it an ideal choice for prototyping and developing cutting-edge autopilot systems.

# What is ATC?

In the context of the `Housefly Lab`, the ATC refers to any form of electromagnetic transmission control used to send signals and instructions to the `Housefly Drone`. Unlike traditional aviation definitions, communication between the so-called tower and the flying vehicle in this setup is unilateral, flowing only from the ATC to the drone.

## ATC Commands

![housefly autopilot](./public/image/logo.webp)
