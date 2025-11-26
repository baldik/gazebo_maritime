# Tethys Underwater Vehicle Keyboard Control

This project implements keyboard control for the Tethys underwater vehicle in a simulated underwater environment using Gazebo.

## Overview

The project includes:
- A modified Tethys model with underwater dynamics
- An underwater world simulation
- Keyboard control interface for navigation
- Proper hydrodynamic modeling using damping instead of unavailable fluid drag systems

## Components

### Model: `tethys_keyboard_control`
- Based on the original Tethys ROV model
- Includes thruster systems for movement
- Uses linear and angular damping to simulate underwater resistance
- Includes fins for directional control

### World: `underwater_keyboard_control.sdf`
- Underwater environment with proper physics
- Buoyancy system for realistic underwater behavior
- Appropriate visual settings for underwater scene

### Control: `keyboard_control.py`
- Keyboard interface for controlling the vehicle
- W/S: Move forward/backward
- A/D: Move left/right
- Q/E: Move up/down
- Arrow keys: Rotate (pitch/yaw)
- Space: Stop movement
- C: Change speed

## Installation Requirements

To run this project, you need to have Gazebo Garden installed:

```bash
# Install Gazebo Garden
curl -sSf https://get.gazebosim.org | sh

# Install additional dependencies
sudo apt update
sudo apt install python3-ros-foxy-geometry-msgs python3-ros-foxy-rclpy
```

## Usage

1. Clone or copy this project to your workspace
2. Set up environment variables:
   ```bash
   export GZ_SIM_RESOURCE_PATH="${GZ_SIM_RESOURCE_PATH}:/path/to/workspace/models:/path/to/workspace/worlds"
   ```
3. Launch the simulation:
   ```bash
   gz sim worlds/underwater_keyboard_control.sdf
   ```
4. In another terminal, run the keyboard control:
   ```bash
   python3 keyboard_control.py
   ```

Alternatively, use the provided script:
```bash
./run_simulation.sh
```

## Controls

- `W` / `S`: Move forward / backward
- `A` / `D`: Move left / right  
- `Q` / `E`: Move down / up
- Arrow Up / Down: Pitch up / down
- Arrow Left / Right: Yaw left / right
- `Space`: Stop all movement
- `C`: Toggle speed (1.0x / 2.0x)
- `Ctrl+C`: Quit the control program

## Implementation Details

The model uses:
- Linear damping (10.0) and angular damping (5.0) to simulate underwater resistance
- Thruster system for propulsion
- Buoyancy system for realistic underwater physics
- Joint position controllers for fin control
- Velocity control system for receiving commands

The system was designed to work without the `gz-sim-fluid-drag-system` plugin that might not be available in all installations, using simpler damping parameters instead.

## Troubleshooting

- If you get "plugin not found" errors, make sure Gazebo Garden is properly installed
- Ensure all environment variables are set correctly
- Check that the model and world files are in the correct directories
- Make sure the Python script has the required dependencies

## Files Structure

```
/workspace/
├── models/
│   └── tethys_keyboard_control/
│       ├── model.config
│       └── model.sdf
├── worlds/
│   └── underwater_keyboard_control.sdf
├── keyboard_control.py
├── run_simulation.sh
└── README.md
```

# Gazebo Maritime

This repository contains various models, worlds, and plugins for simulating maritime vehicles in Gazebo.