from PIL import Image


def getImageCodes(image_path):
    image = Image.open(image_path)

    colorValues = []
    color1 = []
    color2 = []
    color3 = []

    width, height = image.size

    i = 0
    n1 = 0
    n2 = 0
    n3 = 0
    first = True
    for y in range(height):
        for x in range(width):

            rgb = image.getpixel((x, y))
            rgb = (rgb[0], rgb[1], rgb[2])

            if rgb != (255,255,255) and rgb not in colorValues:
                colorValues.append(rgb)

            if i % 16 == 0:
                i = 0
                if first:
                    first = False
                else:
                    color1.append(n1)
                    color2.append(n2)
                    color3.append(n3)
                    n1 = 0
                    n2 = 0
                    n3 = 0
            i += 1

            try:
                if rgb == colorValues[0]:
                    n1 = n1 + (1 << i)
                elif rgb == colorValues[1]:
                    n2 = n2 + (1 << i)
                elif rgb == colorValues[2]:
                    n3 = n3 + (1 << i)
            except IndexError:
                pass

    color1.append(n1)
    color2.append(n2)
    color3.append(n3)
    output = str([color1, color2, color3]).replace("]", "}").replace("[", "{")
    print(output)


getImageCodes("mario.png")
