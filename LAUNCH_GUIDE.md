# Launch Guide for Tethys Underwater Vehicle Keyboard Control

## Prerequisites

Before launching the simulation, ensure you have:

1. Gazebo Garden installed on your system
2. Python 3 with ROS 2 Foxy libraries (geometry_msgs, rclpy)

## Installation

If Gazebo Garden is not installed:

```bash
curl -sSf https://get.gazebosim.org | sh
sudo apt update
sudo apt install python3-ros-foxy-geometry-msgs python3-ros-foxy-rclpy
```

## Quick Launch

The easiest way to run the simulation is using the provided script:

```bash
cd /workspace
./run_simulation.sh
```

This script will:
1. Set up the required environment variables
2. Launch the underwater world in Gazebo
3. Start the keyboard control interface

## Manual Launch

If you prefer to launch components manually:

1. **Set environment variables:**
   ```bash
   export GZ_SIM_RESOURCE_PATH="${GZ_SIM_RESOURCE_PATH}:/workspace/models:/workspace/worlds"
   ```

2. **Launch the simulation:**
   ```bash
   gz sim /workspace/worlds/underwater_keyboard_control.sdf
   ```

3. **In another terminal, start keyboard control:**
   ```bash
   python3 /workspace/keyboard_control.py
   ```

## Controls

Once the simulation is running:

- `W` / `S`: Move forward / backward
- `A` / `D`: Move left / right  
- `Q` / `E`: Move down / up
- Arrow Up / Down: Pitch up / down
- Arrow Left / Right: Yaw left / right
- `Space`: Stop all movement
- `C`: Toggle speed (1.0x / 2.0x)
- `Ctrl+C`: Quit the control program

## Troubleshooting

If you encounter issues:

1. **Plugin not found errors**: Make sure Gazebo Garden is properly installed
2. **Model not loading**: Verify that the GZ_SIM_RESOURCE_PATH includes the models directory
3. **No response to keyboard**: Check that the Python script is running and has focus
4. **Vehicle not moving**: Verify that the thruster system and velocity control plugins are working

## Components Overview

- **Model**: `/workspace/models/tethys_keyboard_control/` - Enhanced Tethys model with underwater dynamics
- **World**: `/workspace/worlds/underwater_keyboard_control.sdf` - Underwater environment with physics
- **Control**: `/workspace/keyboard_control.py` - Keyboard interface script
- **Script**: `/workspace/run_simulation.sh` - Automated launch script