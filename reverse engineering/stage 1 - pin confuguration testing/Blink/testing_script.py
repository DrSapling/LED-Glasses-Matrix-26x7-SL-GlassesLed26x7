import tkinter as tk
from tkinter import messagebox
import serial
import time

# Define the pins and their states
pins = [27, 14, 26, 25, 12, 13, 21, 23, 22, 17, 18, 5, 19, 4, 16, 15]
button_states = {}  # To track the last state of each pin

# Initialize serial connection to the Arduino
try:
    arduino = serial.Serial(port="COM3", baudrate=9600, timeout=1)  # Replace COM3 with your port
    time.sleep(2)  # Give some time for the connection to establish
except Exception as e:
    messagebox.showerror("Connection Error", f"Could not connect to Arduino: {e}")
    exit()


def send_command(pin, state):
    """Send the command to the Arduino and update button colors."""
    global button_states
    command = f"{pin}.{state}\n"  # Format the command
    try:
        arduino.write(command.encode())  # Send the command to Arduino
        time.sleep(0.1)  # Small delay for stability
        button_states[pin] = state  # Update the button state
        update_button_colors(pin)  # Update the colors of the buttons
    except Exception as e:
        messagebox.showerror("Communication Error", f"Failed to send command: {e}")


def update_button_colors(pin):
    """Update button colors based on the last sent state."""
    for state, button in buttons[pin].items():
        if state == button_states.get(pin):  # Highlight the active button
            button.config(bg="green", fg="white")
        else:
            button.config(bg="lightgray", fg="black")


def create_gui():
    """Create the main GUI window."""
    global buttons
    buttons = {}  # Dictionary to store button widgets
    root = tk.Tk()
    root.title("Arduino Pin Controller")

    # Create buttons for each pin
    for row, pin in enumerate(pins):
        tk.Label(root, text=f"Pin {pin}", font=("Arial", 12)).grid(row=row, column=0, padx=10, pady=5)

        # Create HIGH, LOW, and INPUT buttons for each pin
        buttons[pin] = {}
        for col, (state, label) in enumerate([("h", "HIGH"), ("l", "LOW"), ("d", "INPUT")]):
            button = tk.Button(root, text=label, width=10,
                               command=lambda p=pin, s=state: send_command(p, s))
            button.grid(row=row, column=col + 1, padx=5, pady=5)
            buttons[pin][state] = button  # Store the button in the dictionary

        # Initialize button states
        button_states[pin] = None
        update_button_colors(pin)

    root.mainloop()


if __name__ == "__main__":
    create_gui()

    # Close the serial connection when the program exits
    if arduino.is_open:
        arduino.close()
