## Vehicle

## Flight Flags

| Flag Bit  | Flag Symbol  | Description         | 1     | 0       | Activation    |
| --------- | ------------ | ------------------- | ----- | ------- | ------------- |
| ----0---- | `SFTYTSTFLG` | Initial safety test | Valid | Invalid | OR 0b00000001 |

## Housefly Autopilot - State machine

The autopilot maintains an internal state machine that determines whether an instruction received from the ATC should be executed or not. Due to safety measures, **_received instructions are never queued!_** This means they are either executed immediately or rejected. For instance, a drone should not be able to change its destination if it is already in the `Transition` state.

### Ground state

The Ground state or `GND` refers to a stable state in which the drone is on the ground with all four rotors turned off. This should be the drone's initial state. Additionally, a successful landing operation should eventually set the state to `GND`.

### Take off state

The Takeoff state or `TO` refers to a temporary state in which the drone is lifting off the ground. This state should only be set if the drone's current state is `GND`. A successful takeoff operation eventually sets the state to `IDLE`.
Takeoff takes place, if the `SFTYTSTFLG` is set to true. This means an initial safety test is mandatory.

### Landing state

The Landing state or `LND` refers to a temporary state in which the drone is descending to land on the ground. A successful landing operation eventually sets the state to `GND`.

### Transition state

The Transition state or `TRN` refers to a temporary state in which the drone moves from one coordinate in space to another. This state should only be set if the drone's current state is `IDLE`.

### Idle state

The Idle state or `IDLE` refers to a stable state in which the drone hovers in place.

### Test state

The Test state or `TST` refers to a temporary state in which the drone takes precautionary measures. This state should only be set if the drone's current state is `GND`.

### Halt state

The Halt state or `HLT` refers to an immediate emergency state in which all four rotors are turned off at once. Due to safety reasons, a drone may enter this state at any time.

| State | State Symbol | Type      | From               | Flags        | To     |
| ----- | ------------ | --------- | ------------------ | ------------ | ------ |
| 0     | `GND`        | Stable    | `INITIAL, LND`     |              |        |
| 1     | `TO`         | Temporary | `GND`              | `SFTYTSTFLG` | `IDLE` |
| 2     | `LND`        | Temporary | `IDLE`             |              | `GND`  |
| 3     | `TRN`        | Temporary | `IDLE`             |              | `IDLE` |
| 4     | `IDLE`       | Stable    | `TO, TRN`          |              |        |
| 5     | `TST`        | Temporary | `GND`              |              | `GND`  |
| 6     | `HLT`        | Stable    | `ALL_OTHER_STATES` |              |        |
