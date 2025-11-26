# Usage Instructions for Tethys Keyboard Control

## Quick Start

To run the simulation with keyboard control, simply execute the run script:

```bash
./run_simulation.sh
```

## Manual Start

If you prefer to start components separately:

1. **Start the simulation:**
   ```bash
   gz sim /workspace/worlds/underwater_keyboard_control.sdf
   ```

2. **In a new terminal, start the keyboard control:**
   ```bash
   python3 /workspace/keyboard_control.py
   ```

## Controls

- `W` - Move forward (increase velocity in X direction)
- `S` - Move backward (decrease velocity in X direction) 
- `A` - Move left (increase velocity in Y direction)
- `D` - Move right (decrease velocity in Y direction)
- `Q` - Move down (decrease velocity in Z direction)
- `E` - Move up (increase velocity in Z direction)
- `↑` (Up Arrow) - Pitch up (rotate around Y axis)
- `↓` (Down Arrow) - Pitch down (rotate around Y axis)
- `←` (Left Arrow) - Yaw left (rotate around Z axis)
- `→` (Right Arrow) - Yaw right (rotate around Z axis)
- `Space` - Stop all movement
- `C` - Toggle speed between 1.0 and 2.0
- `Ctrl+C` - Quit the keyboard control program

## Troubleshooting

If you encounter issues:

1. Make sure all required dependencies are installed
2. Verify that the Gazebo simulation is running properly
3. Check that the model paths in the SDF files are correct
4. If plugins are not working, verify available plugins in your system

## System Architecture

The system consists of:
- An underwater environment with buoyancy simulation
- A Tethys underwater vehicle model with hydrodynamics
- A keyboard input handler that publishes to `/model/tethys/cmd_vel`
- Joint controllers for the vehicle's fins
- A thruster system for propulsion