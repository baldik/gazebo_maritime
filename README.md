# Tethys Underwater Vehicle with Keyboard Control

This project provides keyboard control for the Tethys underwater vehicle in a simulated underwater environment.

## Components

1. **Model**: `/workspace/models/tethys_keyboard_control/`
   - Enhanced Tethys model with hydrodynamics, thruster, and control systems
   - Includes joint controllers for horizontal and vertical fins
   - Ready for velocity command input

2. **World**: `/workspace/worlds/underwater_keyboard_control.sdf`
   - Underwater environment with buoyancy simulation
   - Lighting setup for underwater visibility
   - Includes the tethys model positioned at start location

3. **Keyboard Control Script**: `/workspace/keyboard_control.py`
   - Python script for keyboard input handling
   - Maps keyboard keys to velocity commands
   - Publishes commands to `/model/tethys/cmd_vel` topic

## Usage

1. Start the Gazebo simulation with the underwater world:
   ```bash
   gz sim /workspace/worlds/underwater_keyboard_control.sdf
   ```

2. In another terminal, run the keyboard control script:
   ```bash
   python3 /workspace/keyboard_control.py
   ```

## Controls

- `W/S`: Move forward/backward
- `A/D`: Move left/right
- `Q/E`: Move down/up
- Arrow keys: Rotate the vehicle
- `Space`: Stop movement
- `C`: Change speed

## Notes

The model uses ROS 2 topics for communication:
- Command topic: `/model/tethys/cmd_vel`
- Odometry topic: `/model/tethys/odometry`

The actual plugin names in the SDF file may need to be adjusted based on the available Gazebo plugins in your system. Common alternatives to `gz-sim-velocity-control-system` include:
- `gz-sim-velocity-controller-system`
- `gz-sim-ackermann-steering-system`
- Custom-built control plugins

If the simulation doesn't work, check available plugins with:
```bash
find /usr -name "*.so" -path "*/lib/*" | grep -i gz
```