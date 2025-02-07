import tkinter as tk 

def toggle_button(btn, x, y):
    state = button_states[(x, y)]
    new_state = not state
    button_states[(x, y)] = new_state
    if (x, y) in special_buttons:
        btn.config(bg="yellow" if new_state else "#2F2F2F")  # Very dark gray when untoggled
    else:
        btn.config(bg="white" if new_state else "black")

def generate_bitmap():
    rows, cols = 7, 26  # 7 rows x 26 columns
    binary_values = []
    
    for col in range(0, cols, 2):  # Process in chunks of 2 columns
        bits = list("00000000000000000000000000000000")  # Initialize 32-bit sequence with zeros
        
        for row in range(rows - 1, -1, -1):  # Reverse row order
            bit1 = '1' if button_states.get((col, row), False) else '0'
            bit2 = '1' if button_states.get((col+1, row), False) else '0'
            
            # Assign bits based on new specified order
            mapping = [1, 3, 4, 8, 9, 7, 13, 11, 10, 2, 6, 5, 12, 14]
            if row < len(mapping):
                bits[mapping[row]] = bit2  # Correct bit order placement
                bits[mapping[row] + 1] = bit1  # Correct bit order placement
        
        # Convert bits to 32-bit binary format
        binary_values.append("0b0000" + "".join(bits))
    
    # Ensure exactly 13 entries
    while len(binary_values) < 13:
        binary_values.append("0b00000000000000000000000000000000")
    
    # Format for Arduino
    arduino_code = "const unsigned long bitmap_testface[13] PROGMEM = {\n"
    arduino_code += "    " + ",\n    ".join(binary_values) + "\n" + "};"
    
    output_text.delete("1.0", tk.END)
    output_text.insert(tk.END, arduino_code)

root = tk.Tk()
root.title("Matrix Bitmap Generator")
root.configure(bg="gray")

button_states = {}
special_buttons = {
    (11,4), (12,4), (13,4), (14,4),
    (10,5), (11,5), (12,5), (13,5), (14,5), (15,5),
    (9,6), (10,6), (11,6), (12,6), (13,6), (14,6), (15,6), (16,6)
}

frame = tk.Frame(root, bg="gray")
frame.pack()

def create_toggle_command(btn, i, j):
    return lambda: toggle_button(btn, i, j)

for x in range(26):
    for y in range(7):
        bg_color = "#2F2F2F" if (x, y) in special_buttons else "black"  # Very dark gray for special buttons
        btn = tk.Button(frame, width=2, height=1, bg=bg_color)
        btn.config(command=create_toggle_command(btn, x, y))
        btn.grid(row=y, column=x, padx=1, pady=1)
        button_states[(x, y)] = False

generate_button = tk.Button(root, text="Generate Bitmap", command=generate_bitmap)
generate_button.pack()

output_text = tk.Text(root, height=15, width=50)
output_text.pack()

root.mainloop()
