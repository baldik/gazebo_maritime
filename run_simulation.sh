#!/bin/bash

echo "Starting Tethys underwater vehicle simulation with keyboard control..."
echo ""
echo "Controls:"
echo "  W/S: Move forward/backward"
echo "  A/D: Move left/right" 
echo "  Q/E: Move down/up"
echo "  Arrow keys: Rotate the vehicle"
echo "  Space: Stop movement"
echo "  C: Change speed"
echo ""
echo "Press Ctrl+C in this terminal to stop the keyboard control."
echo "Press Ctrl+C in the Gazebo window to stop the simulation."
echo ""

# Start Gazebo simulation in background
gz sim /workspace/worlds/underwater_keyboard_control.sdf &

# Wait a moment for Gazebo to start
sleep 5

# Start keyboard control
python3 /workspace/keyboard_control.py