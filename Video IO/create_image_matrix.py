from matplotlib.image import imread
import numpy as np

def extract_matrix(img):
    image = imread(img, 'png')
    print(image.shape)
    image = np.transpose(image, (2, 0, 1))
    print(image.shape)
    with open("main.cpp", "w") as f:
        f.write("{")
        for channel in image:
            f.write("{")
            for row in channel:
                f.write("{")
                row_str = ','.join(map(str, row))
                f.write(row_str + '},\n')
            f.write("},")
        f.write("};\n")


extract_matrix(r"input.png")