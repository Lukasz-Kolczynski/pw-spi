from PIL import Image

def convert_to_pixel_art(input_path, output_path, size=(32, 32), num_colors=32):
    img = Image.open(input_path)

    img_small = img.resize(size, Image.NEAREST)

    img_quantized = img_small.convert("P", palette=Image.ADAPTIVE, colors=num_colors).convert("RGB")

    img_quantized.save(output_path)
    print(f"Zapisano obraz pixel art: {output_path}")


convert_to_pixel_art("C:\\Users\\takty\\Desktop\\test.jpg", "pixel_art.png")
