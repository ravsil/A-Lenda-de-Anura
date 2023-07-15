from PIL import Image


def assign_color_values(path):
    image = Image.open(path)
    width, height = image.size
    color_values = {}
    value = 0
    formattedString = ""

    output = "{"
    for y in range(height):
        for x in range(width):
            pixel = image.getpixel((x, y))
            if pixel not in color_values:
                color_values[pixel] = value
                value += 1

            binary_value = format(color_values[pixel], "04b")
            formattedString = binary_value + formattedString
            if len(formattedString) == 64:
                output += f"{int(formattedString, 2)},"
                formattedString = ""

    output += "}"
    print(output.replace(",}", "}"))


assign_color_values(f"{input()}.png")
