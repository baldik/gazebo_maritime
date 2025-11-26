#!/usr/bin/env python3
"""
Keyboard control script for the Tethys underwater vehicle
Use keys W/A/S/D for forward/backward/left/right movement
Use Q/E for up/down movement
Use arrows for rotation
"""

import sys
import select
import tty
import termios
from geometry_msgs.msg import Twist
import rclpy
from rclpy.node import Node
import threading
import time


class KeyboardControlNode(Node):
    def __init__(self):
        super().__init__('tethys_keyboard_control')
        self.publisher = self.create_publisher(Twist, '/model/tethys/cmd_vel', 10)
        
        self.linear_x = 0.0
        self.linear_y = 0.0
        self.linear_z = 0.0
        self.angular_x = 0.0
        self.angular_y = 0.0
        self.angular_z = 0.0
        
        self.speed = 1.0
        self.turn = 1.0
        
        print("Tethys Keyboard Control")
        print("Controls:")
        print("W/S: Move forward/backward")
        print("A/D: Move left/right")
        print("Q/E: Move down/up")
        print("Arrow keys: Rotate")
        print("Space: Stop")
        print("C: Change speed (currently {:.1f})".format(self.speed))
        print("Press 'Ctrl+C' to quit")
        
        # Start keyboard input thread
        self.keyboard_thread = threading.Thread(target=self.keyboard_input)
        self.keyboard_thread.daemon = True
        self.keyboard_thread.start()
        
        # Timer for publishing messages
        self.timer = self.create_timer(0.1, self.publish_cmd_vel)

    def publish_cmd_vel(self):
        msg = Twist()
        msg.linear.x = self.linear_x * self.speed
        msg.linear.y = self.linear_y * self.speed
        msg.linear.z = self.linear_z * self.speed
        msg.angular.x = self.angular_x * self.turn
        msg.angular.y = self.angular_y * self.turn
        msg.angular.z = self.angular_z * self.turn
        self.publisher.publish(msg)

    def keyboard_input(self):
        old_settings = termios.tcgetattr(sys.stdin)
        try:
            tty.setcbreak(sys.stdin.fileno())
            while rclpy.ok():
                if select.select([sys.stdin], [], [], 0.1)[0]:
                    key = sys.stdin.read(1)
                    
                    # Reset all values
                    self.linear_x = 0.0
                    self.linear_y = 0.0
                    self.linear_z = 0.0
                    self.angular_x = 0.0
                    self.angular_y = 0.0
                    self.angular_z = 0.0
                    
                    if key == 'w':  # Forward
                        self.linear_x = 1.0
                    elif key == 's':  # Backward
                        self.linear_x = -1.0
                    elif key == 'a':  # Left
                        self.linear_y = 1.0
                    elif key == 'd':  # Right
                        self.linear_y = -1.0
                    elif key == 'q':  # Down
                        self.linear_z = -1.0
                    elif key == 'e':  # Up
                        self.linear_z = 1.0
                    elif key == ' ':  # Stop
                        pass  # All values already reset to 0
                    elif key == 'c':  # Change speed
                        self.speed = 2.0 if self.speed == 1.0 else 1.0
                        print(f"\rSpeed changed to: {self.speed:.1f}       ")
                    elif ord(key) == 3:  # Ctrl+C
                        break
                    
                    # Check for special keys (arrow keys)
                    if key == '\x1b':  # ESC sequence
                        key += sys.stdin.read(2)
                        if key == '\x1b[A':  # Up arrow
                            self.angular_y = 1.0  # Pitch up
                        elif key == '\x1b[B':  # Down arrow
                            self.angular_y = -1.0  # Pitch down
                        elif key == '\x1b[C':  # Right arrow
                            self.angular_z = -1.0  # Yaw right
                        elif key == '\x1b[D':  # Left arrow
                            self.angular_z = 1.0  # Yaw left
        finally:
            termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_settings)


def main(args=None):
    rclpy.init(args=args)
    
    node = KeyboardControlNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()