from PIL import Image


def assign_color_values(path):
    image = Image.open(path)
    width, height = image.size
    color_values = {}
    color_values = {
        (255, 0, 255, 255): 0,
        (255, 255, 255, 255): 1,
        (0, 0, 0, 255): 2,
        (135, 80, 153, 255): 3,
        (255, 255, 128, 255): 4,
        (107, 179, 93, 255): 5,
        62: 6,
        134: 7,
        (51, 102, 153, 255): 8,
        (102, 204, 204, 255): 9,
        185: 0,
        215: 1,
        167: 10,
        118: 3,
        0: 2,
        213: 4,
        151: 11,
        98: 5,
        51: 8,
        100: 9,
        49: 12,
        (51, 204, 102, 255): 6,
        (153, 204, 102, 255): 7,
        79: 14,
        208: 15,
    }
    value = 0
    formattedString = ""

    output = "{"
    for y in range(height):
        for x in range(width):
            pixel = image.getpixel((x, y))
            if pixel not in color_values:
                color_values[pixel] = value
                print(pixel)
                value += 1

            binary_value = format(color_values[pixel], "04b")
            formattedString = binary_value + formattedString
            if len(formattedString) == 64:
                output += f"{int(formattedString, 2)},"
                formattedString = ""

    output += "}"
    print(output.replace(",}", "}"))


assign_color_values(f"{input()}.png")
