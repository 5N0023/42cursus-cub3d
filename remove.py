from PIL import Image
from pytmatting import estimate_alpha

def remove_green_screen(input_path, output_path, green_range=((0, 128, 0), (50, 255, 50))):
    # Load the image
    image = Image.open(input_path)

    # Convert the image to RGBA (with alpha channel) to support transparency
    image = image.convert("RGBA")

    # Get the image data as a list of pixels
    data = list(image.getdata())

    # Define the green color range to remove
    lower_green, upper_green = green_range

    # Loop through each pixel and remove green pixels
    new_data = []
    for pixel in data:
        r, g, b, a = pixel

        if lower_green[0] <= r <= upper_green[0] and \
           lower_green[1] <= g <= upper_green[1] and \
           lower_green[2] <= b <= upper_green[2]:
            # Set the alpha channel to 0 to make the pixel transparent
            a = 0

        new_data.append((r, g, b, a))

    # Update the image data
    image.putdata(new_data)

    # Estimate alpha matting to clean up edges
    alpha = estimate_alpha(image, estimate_foreground=False)

    # Apply the estimated alpha to the image
    image.putalpha(alpha)

    # Save the modified image
    image.save(output_path)

if __name__ == "__main__":
    input_path = "jett/frame-001.png"
    output_path = "jett/frame-001___.png"

    # You can adjust the green_range if needed
    # Format: ((lower_red, lower_green, lower_blue), (upper_red, upper_green, upper_blue))
    # For example: ((0, 128, 0), (50, 255, 50))
    green_range = ((0, 128, 0), (50, 255, 50))

    remove_green_screen(input_path, output_path, green_range)
