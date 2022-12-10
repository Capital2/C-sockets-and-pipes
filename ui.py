import tkinter as tk

root = tk.Tk()

input_field1 = tk.Entry(root)
input_field1.pack()

input_field2 = tk.Entry(root)
input_field2.pack()

output_field1 = tk.Label(root, text="Output Field 1")
output_field1.pack()

output_field2 = tk.Label(root, text="Output Field 2")
output_field2.pack()

radio_button = tk.Radiobutton(root, text="Option 1")
radio_button.pack()

button = tk.Button(root, text="Submit")
button.pack()

root.mainloop()
