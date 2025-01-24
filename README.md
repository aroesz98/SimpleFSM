# SimpleFSM Library

## Table of Contents
1. [Functionality Description](#functionality-description)
2. [Algorithm Description](#algorithm-description)
3. [Detailed Description](#detailed-description)
    - [State Structure](#state-structure)
    - [FSM Class Methods](#fsm-class-methods)
    - [Adding State Transitions](#adding-state-transitions)
    - [Event Triggering and Transitions](#event-triggering-and-transitions)
    - [Control Flow](#control-flow)
4. [Additional Information](#additional-information)
5. [Example Usage](#example-usage)

## Functionality Description

The `FSM` (Finite State Machine) class implements a finite state machine. It allows defining states and transitions between them based on events. Each state can have functions assigned to handle entering the state (`onEnter`), being in the state (`onState`), and exiting the state (`onExit`).

## Algorithm Description

The algorithm for the `FSM` class operates as follows:

1. **State Machine Initialization**: Create an `FSM` object with an initial state.
2. **Defining States**: States are created as `State` structure objects with assigned event handler functions.
3. **Adding Transitions**: Use the `addTransition()` method to add transitions between states, specifying the event, from-state, and to-state.
4. **Initialization**: The `init()` method initializes the state machine by calling the `onEnter` function of the initial state and the `onState` function.
5. **Triggering Events**: The `trigger()` method checks if a transition is defined for the current state and event. If so, it performs the transition to the new state.
6. **State Transition**: During a transition, the `onExit` function of the from-state and the `onEnter` function of the to-state are called. The current state of the machine is then updated.

## Detailed Description

### State Structure

The state is represented by the `State` structure, which contains:

- `void (*onEnter)()`: Function called when entering the state.
- `void (*onState)()`: Function called while in the state.
- `void (*onExit)()`: Function called when exiting the state.

**Creating a State:**

```cpp
FSM::State state(onEnterFunction, onStateFunction, onExitFunction);
```

### FSM Class Methods

- **Constructor `FSM(State *initial_state)`**: Initializes the state machine, setting the initial state.
- **Destructor `~FSM()`**: Frees resources used by the state machine.
- **`void addTransition(int event, State *fromState, State *toState)`**: Adds a transition between states based on an event.
- **`void trigger(int event)`**: Triggers an event, potentially causing a state transition.
- **`void init()`**: Initializes the state machine, calling the `onEnter` and `onState` functions of the initial state.

### Adding State Transitions

Transitions are defined by the `Transition` structure, which contains:

- `int event`: Event identifier.
- `State *fromState`: Starting state of the transition.
- `State *toState`: Target state of the transition.

**Adding a Transition:**

```cpp
fsm.addTransition(eventID, &fromState, &toState);
```

### Event Triggering and Transitions

The `trigger()` method checks the list of transitions defined in the state machine. If a transition is found for the current state and event, it performs the transition to the new state using the `doTransition()` method.

**Triggering an Event:**

```cpp
fsm.trigger(eventID);
```

### Control Flow

1. **Initialization (`init()`)**:
   - If the state machine was not previously initialized, sets the `mInitialized` flag to `true`.
   - Calls the `onEnter` function of the current state.
   - Calls the `onState` function of the current state.

2. **Triggering an Event (`trigger()`)**:
   - Checks if the state machine has been initialized.
   - Searches the list of transitions for a match with the current state and event.
   - If a match is found, calls `doTransition()`.

3. **Performing a Transition (`doTransition()`)**:
   - Calls the `onExit` function of the from-state.
   - Updates `mCurrentState` to the to-state.
   - Calls the `onEnter` function of the new state.

## Additional Information

- **Handling Multiple Transitions**: Multiple transitions between states can be added, allowing for complex state machine modeling.
- **Memory Safety**: Ensure that state objects and event handler functions remain in memory as long as they are used by the state machine.
- **Extensions**: The `FSM` class can be extended with additional features such as post-transition actions or conditional transitions based on additional criteria.

## Example Usage

The following example demonstrates how to use the `FSM` class to model a simple state machine:

```cpp
#include <iostream>
#include "FSM.h" // Assuming the FSM class is defined in this file

// State A handler functions
void onEnterA() { std::cout << "Entering State A\n"; }
void onStateA() { std::cout << "In State A\n"; }
void onExitA()  { std::cout << "Exiting State A\n"; }

// State B handler functions
void onEnterB() { std::cout << "Entering State B\n"; }
void onStateB() { std::cout << "In State B\n"; }
void onExitB()  { std::cout << "Exiting State B\n"; }

int main()
{
    // Creating states
    FSM::State stateA(onEnterA, onStateA, onExitA);
    FSM::State stateB(onEnterB, onStateB, onExitB);

    // Initializing the state machine with initial state A
    FSM fsm(&stateA);

    // Adding a transition from State A to State B on event 1
    fsm.addTransition(1, &stateA, &stateB);

    // Initializing the state machine
    fsm.init();

    // Triggering event 1, causing transition to State B
    fsm.trigger(1);

    return 0;
}
```

**Program Output:**

```
Entering State A
In State A
Exiting State A
Entering State B
```

### Example Visualization

Graphical representation of state transitions:

```
[State A] --(event 1)--> [State B]
```

- **State A**: Initial state.
- **Event 1**: Triggers transition to State B.
- **State B**: Target state after the event occurs.
