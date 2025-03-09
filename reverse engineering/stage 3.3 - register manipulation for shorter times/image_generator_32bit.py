import tkinter as tk
from tkinter import scrolledtext

def toggle_button(x, y):
    current_color = button_colors[(x, y)]
    new_color = "white" if current_color in ["black", "#222"] else ("black" if (x, y) not in special_buttons else "#222")
    button_colors[(x, y)] = new_color
    buttons[(x, y)].config(bg=new_color)
    update_bitmap()

def update_bitmap():
    chunks = ["0b00000000000000000000000000000000" for _ in range(13)]
    for chunk_index in range(13):
        x_start = chunk_index * 2
        bit_sequence = [
            (x_start, 0), (x_start+1, 0), (x_start, 1), (x_start+1, 1),
            (x_start, 2), (x_start+1, 2), (x_start, 3), (x_start+1, 3),
            (x_start, 4), (x_start+1, 4), (x_start, 5), (x_start+1, 5),
            (x_start, 6), (x_start+1, 6)
        ]
        #bit_values = ["1" if button_colors.get(pos, "black") in ["white", "yellow"] else "0" for pos in bit_sequence]
        bit_values = []  # Store 1s and 0s
        bit_even = "0"
        bit_odd = "0"
        for pos in range(14):
            if button_colors.get(bit_sequence[pos], "black") in ["white", "yellow"]:
                if chunk_index!=pos:
                    bit_values.append("1")
                else:
                    bit_values.append("0")
                    if chunk_index%2==0:
                        bit_even = "1"
                        bit_odd = "0"
                    else:
                        bit_even = "0"
                        bit_odd = "1"
            else:
                bit_values.append("0")

        chunk_bits = f"0b0000{bit_values[0]}{bit_values[2]}{bit_values[3]}0{bit_values[7]}{bit_values[8]}{bit_values[6]}0{bit_values[12]}{bit_values[10]}{bit_values[9]}{bit_even}{bit_odd}{bit_values[1]}{bit_values[5]}{bit_values[4]}000000{bit_values[11]}{bit_values[13]}0000"
        if "1" in bit_values or bit_odd == "1" or bit_even == "1":
            chunks[chunk_index] = chunk_bits
    
    bitmap_text = "const unsigned short bitmap_NAME[13] PROGMEM = {\n" + ",\n".join(chunks) + "\n};"
    output_text.config(state=tk.NORMAL)
    output_text.delete("1.0", tk.END)
    output_text.insert(tk.END, bitmap_text)
    output_text.config(state=tk.DISABLED)

root = tk.Tk()
root.title("Matrix GUI")
root.configure(bg="gray")

buttons = {}
button_colors = {}
special_buttons = {(11,4), (12,4), (13,4), (14,4), (10,5), (11,5), (12,5), (13,5), (14,5), (15,5), (9,6), (10,6), (11,6), (12,6), (13,6), (14,6), (15,6), (16,6)}

for y in range(7):
    for x in range(26):
        color = "#222" if (x, y) in special_buttons else "black"
        button = tk.Button(root, bg=color, width=2, height=1, command=lambda x=x, y=y: toggle_button(x, y))
        button.grid(row=y, column=x, padx=1, pady=1)
        buttons[(x, y)] = button
        button_colors[(x, y)] = color

output_text = scrolledtext.ScrolledText(root, width=70, height=15, state=tk.DISABLED)
output_text.grid(row=8, column=0, columnspan=26, pady=10)
update_bitmap()

root.mainloop()
