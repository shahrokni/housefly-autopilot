## How does autopilot work?

As mentioned earlier, instructions are sent by the ATC and received by the drone. Based on the drone’s current state, the autopilot either executes or rejects the instructions.

It is important to understand that, due to safety measures, no instructions are queued for later execution. The only exception is the `HALT` emergency instruction. Since instructions may change the drone's state, their feasibility is assessed first. If they do not comply with the `State Transition Table`, they are rejected.

Whenever the state changes, the `Control Unit` is notified. The `CU` is responsible for executing instructions by calculating the RPM for individual motors based on sensor data. Finally, once the instruction has been fully executed, the CU sends a request to State Management to update the state.

## Flying Vehicle Configuration 🪰

This read-only configuration helps the autopilot system make the right decisions during flight. It is strongly recommended that developers set up the configuration and build the library according to their flying vehicle's capacity and limitations.

## service_ceiling

This property, as its name suggests, determines the service ceiling of the `Flying Vehicle`. The property's type is `unsigned char`, meaning it can range from 0 to 255. When divided by 10, the result represents the `service_ceiling` in `meters`. The configured value should be at least 10 (equivalent to 1 meter); otherwise, the initial safety test will fail. For safety reasons, the default value is set to 20. However, be aware that `reaction_latency` may affect the accuracy of the service_ceiling.

> [!WARNING]
> For more information review `reaction_latency`

## reaction_latency

As mentioned earlier, the autopilot perceives its environment through sensors and acts accordingly. The `reaction_latency` property introduces an `intentional delay`, measured in `milliseconds`, between these two critical steps. Since some actions take time to influence the flight dynamics, both short and long delays can lead to instability or even incidents. The property's type is `unsigned char`, meaning it can range from 0 to 255. However, values below 150 are ignored by the autopilot. Although a higher `reaction_latency` may reduce instability, it can introduce (tolerable) inaccuracies. With a well-designed drone, a lower `reaction_latency` may enable smoother execution of acrobatic maneuvers.

## Flight Flags

| Flag Bit | Flag Symbol  | Description         | 1     | 0       | Activation    |
| -------- | ------------ | ------------------- | ----- | ------- | ------------- |
| `0`      | `SFTYTSTFLG` | Initial safety test | Valid | Invalid | OR 0b00000001 |

## Housefly Autopilot - State machine

The autopilot maintains an internal state machine that determines whether an instruction received from the ATC should be executed or not. Due to safety measures, **_received instructions are never queued!_** This means they are either executed immediately or rejected. For instance, a drone should not be able to change its destination if it is already in the `Transition` state.

### Ground state

The Ground state or `GND` refers to a stable state in which the drone is on the ground with all four rotors turned off. This should be the drone's initial state. Additionally, a successful landing operation should eventually set the state to `GND`.

The `GND` state cannot be requested by an external actor (such as ATC). It can only be set by the autopilot.

### Take off state

The Takeoff state or `TO` refers to a temporary state in which the drone is lifting off the ground. This state should only be set if the drone's current state is `GND`. A successful takeoff operation eventually sets the state to `IDLE`.
Takeoff takes place, if the `SFTYTSTFLG` is set to true. This means an initial safety test is mandatory.

### Landing state

The Landing state or `LND` refers to a temporary state in which the drone is descending to land on the ground. A successful landing operation eventually sets the state to `GND`.

### Transition state

The Transition state or `TRN` refers to a temporary state in which the drone moves from one coordinate in space to another. This state should only be set if the drone's current state is `IDLE`. A successful transition operation eventually sets the state to `IDLE`.

### Idle state

The Idle state, or IDLE, refers to a stable condition in which the drone hovers in place. The request to transition to the `IDLE` state can **only** be made internally by the autopilot.

### Test state

The Test state or `TST` refers to a temporary state in which the drone takes precautionary measures. This state should only be set if the drone's current state is `GND`.

### Halt state

The Halt state or `HLT` refers to an immediate emergency state in which all four rotors are turned off at once. Due to safety reasons, a drone may enter this state at any time.

### State Transition Table

| State | State Symbol | Type      | From                | Actors            | Flags        | To     |
| ----- | ------------ | --------- | ------------------- | ----------------- | ------------ | ------ |
| 0     | `GND`        | Stable    | `INITIAL, LND, TST` | Internal          |              |
| 1     | `TO`         | Temporary | `GND`               | External          | `SFTYTSTFLG` | `IDLE` |
| 2     | `LND`        | Temporary | `IDLE`              | External          |              | `GND`  |
| 3     | `TRN`        | Temporary | `IDLE`              | External          |              | `IDLE` |
| 4     | `IDLE`       | Stable    | `TO, TRN`           | Internal          |              |
| 5     | `TST`        | Temporary | `GND`               | External          |              | `GND`  |
| 6     | `HLT`        | Stable    | `ALL_OTHER_STATES`  | External\Internal |              |
