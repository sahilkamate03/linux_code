import tkinter as tk

# Create the main application window
root = tk.Tk()
root.title("GUI with Navbar")

# Function to handle navbar item clicks
def on_navbar_click(item_name):
    # Handle the click event for the selected item
    print(f"Clicked on {item_name}")

# Navbar Frame
navbar_frame = tk.Frame(root)
navbar_frame.pack(side=tk.TOP, fill=tk.X, padx=10, pady=10)

# Logo (You can replace 'logo.png' with your actual logo)
logo_label = tk.Label(navbar_frame, text="Your Logo", font=("Helvetica", 16))
logo_label.grid(row=0, column=0, padx=(10, 20))  # Place the logo on the left

# Navbar Items
navbar_items = ["Item 1", "Item 2", "Item 3", "Item 4"]
for i, item_name in enumerate(navbar_items):
    item_button = tk.Button(navbar_frame, text=item_name, command=lambda name=item_name: on_navbar_click(name))
    item_button.grid(row=0, column=i + 1, padx=10)  # Place items to the right

# Card Frame
card_frame = tk.Frame(root)
card_frame.pack(side=tk.LEFT, padx=10, pady=10)

# Card Heading
card_heading = tk.Label(card_frame, text="Card Heading", font=("Helvetica", 14))
card_heading.pack()

# Card Description
card_description = tk.Label(card_frame, text="This is a short description of the card content.")
card_description.pack()

# Right Side Image (You can replace 'image.png' with your actual image)
image = tk.PhotoImage(file="image.png")
image_label = tk.Label(card_frame, image=image)
# image_label.pack()

# Start the main loop
root.mainloop()
