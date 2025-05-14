# from PIL import Image

# img = Image.open("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/fotka04.png")
# pixels = img.load()
# cols, rows = img.size

# tSize = 8
# s = tSize * tSize

# for i in range((int) (cols/tSize)):
#     for j in range ((int) (rows/tSize)):
#         r, g, b = (0,0,0)

#         for x in range(tSize):
#             for y in range(tSize):
#                 rPx, gPx, bPx = pixels[i*tSize+x, j*tSize+y]

#                 r += rPx
#                 g += gPx
#                 b += bPx

#         r = (int)(r/s)
#         g = (int)(g/s)
#         b = (int)(b/s)

#         for x in range(tSize):
#             for y in range(tSize):
#                 pixels[i*tSize+x, j*tSize+y] = (r,g,b)

# img.save(f"tile {tSize}.png")
        
# #=======================================================================================

# import os
# from PIL import Image
# import threading
# import time


# def load_photo(file_name: str, width: int = 0, height: int = 0):
#     photo = Image.open(file_name)
#     photo = photo.convert("RGB")
#     if width == 0 and height == 0:
#         size = photo.size
#         photo = photo.resize((size[0], size[1]))
#     else:
#         photo = photo.resize((width, height))
#     return photo



# def save_photo(file_name, photo):
#     photo.save(file_name)
# def make_small_photo(file_name, step_block, if_convert: bool = True):
#     photo_small = Image.open(file_name)
#     photo_small = photo_small.resize((step_block, step_block))
#     photo_small = photo_small.convert("RGB")
#     return photo_small

# def fill_og_with_small(file_name_og: str,file_out: str,step_block: int, width: int, height: int, img : str):
#     photo_small = make_small_photo(img, step_block)
#     photo = load_photo(file_name_og, width, height)
#     pixels = photo.load()
#     pixelsResult = photo.load()
#     for i in range(int(width / step_block)):
#         for j in range(int(height / step_block)):
#             r, g, b = (0,0,0)
#             for x in range(step_block):
#                 for y in range(step_block):
#                     rPpx, gPpx, bPpx = pixels[i*step_block+x, j*step_block+y]
#                     r += rPpx
#                     g += gPpx
#                     b += bPpx
#             rgb_part = (int(r/(step_block*step_block)),
#                         int(g/(step_block*step_block)),
#                         int(b/(step_block*step_block)))

#             photo_part = Image.new('RGB', (step_block, step_block), rgb_part)
#             photo_blended = Image.blend(photo_part, photo_small, alpha=0.5)
#             pixels_blended = photo_blended.load()
#             for x in range(step_block):
#                 for y in range(step_block):
#                     pixelsResult[i * step_block + x, j * step_block + y] = pixels_blended[x, y]
#     save_photo(file_out, photo)

# def fill_all_photos(dir_out):
#     path_with_photos = "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/test"
#     files = os.listdir(path_with_photos)

#     photos = []
#     c = 0
#     for file in files:
#         file_path = os.path.join(path_with_photos, file)
#         file_path_out = os.path.join(dir_out, f"nr{c}-{file}")
#         photo = threading.Thread(target = fill_og_with_small, args=(file_path, file_path_out, 20, 4000, 3000, "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/tralalala.png"))
#         photos.append(photo)
#         photo.start()
#         c += 1
#         print(f"watek {c}")

# if __name__ == '__main__':

#     begin = time.time()
#     fill_all_photos("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/hehe")
#     end = time.time()
#     print(f"Time: {end-begin}")

# #=======================================================================================================


# #=======================================================================================

# import os
# from PIL import Image
# import threading
# import time


# def load_photo(file_name: str, width: int = 0, height: int = 0):
#     photo = Image.open(file_name)
#     photo = photo.convert("RGB")
#     if width == 0 and height == 0:
#         size = photo.size
#         photo = photo.resize((size[0], size[1]))
#     else:
#         photo = photo.resize((width, height))
#     return photo



# def save_photo(file_name, photo):
#     photo.save(file_name)
# def make_small_photo(file_name, step_block, if_convert: bool = True):
#     photo_small = Image.open(file_name)
#     photo_small = photo_small.resize((step_block, step_block))
#     photo_small = photo_small.convert("RGB")
#     return photo_small

# def fill_og_with_small(file_name_og: str,file_out: str,step_block: int, width: int, height: int):
#     photo_small = make_small_photo(file_name_og, step_block)
#     photo = load_photo(file_name_og, width, height)
#     pixels = photo.load()
#     pixelsResult = photo.load()
#     for i in range(int(width / step_block)):
#         for j in range(int(height / step_block)):
#             r, g, b = (0,0,0)
#             for x in range(step_block):
#                 for y in range(step_block):
#                     rPpx, gPpx, bPpx = pixels[i*step_block+x, j*step_block+y]
#                     r += rPpx
#                     g += gPpx
#                     b += bPpx
#             rgb_part = (int(r/(step_block*step_block)),
#                         int(g/(step_block*step_block)),
#                         int(b/(step_block*step_block)))

#             photo_part = Image.new('RGB', (step_block, step_block), rgb_part)
#             photo_blended = Image.blend(photo_part, photo_small, alpha=0.5)
#             pixels_blended = photo_blended.load()
#             for x in range(step_block):
#                 for y in range(step_block):
#                     pixelsResult[i * step_block + x, j * step_block + y] = pixels_blended[x, y]
#     save_photo(file_out, photo)

# def fill_all_photos(dir_out):
#     path_with_photos = "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/sea"
#     files = os.listdir(path_with_photos)

#     photos = []
#     c = 0
#     for file in files:
#         file_path = os.path.join(path_with_photos, file)
#         file_path_out = os.path.join(dir_out, f"nr{c}-{file}")
#         photo = threading.Thread(target = fill_og_with_small, args=(file_path, file_path_out, 5, 150, 150 ))
#         photos.append(photo)
#         photo.start()
#         c += 1
#         print(f"watek {c}")

# if __name__ == '__main__':

#     begin = time.time()
#     fill_all_photos("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/result")
#     end = time.time()
#     print(f"Time: {end-begin}")

# #=======================================================================================================

import os
import time
from PIL import Image
from multiprocessing import Pool, cpu_count

base_dir = "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos"
source_image_path = os.path.join(base_dir, "bulbul.jpg") 
tiles_dir = os.path.join(base_dir, "zdjecia")
output_path = os.path.join(base_dir, "result", "result.jpg")

# image = Image.open(source_image_path)
# output_width , output_hegiht = image.size
tile_size = 20 
output_width = 3000
output_height = 1500


def average_color(image):
    pixels = list(image.getdata())
    n = len(pixels)
    r = sum(p[0] for p in pixels) // n
    g = sum(p[1] for p in pixels) // n
    b = sum(p[2] for p in pixels) // n
    return (r, g, b)


def load_tile_images(tile_dir, tile_size):
    tiles = [] #pusta lista do przechowywania miniatur z ich srednim kolorem
    for root,_, files in os.walk(tile_dir): #mozna by uzyc listdir ale walk idzie po podfolderach, _ ignoruje nazwy folderow
        for file in files:
            if file.lower().endswith((".jpg", ".png")):
                file_path = os.path.join(root, file)
                try:
                    img = Image.open(file_path).resize((tile_size, tile_size)).convert("RGB")
                    tiles.append((average_color(img), img)) #sredni kolor miniatury, ta miniatura
                except Exception as e:
                    print(f"Błąd podczas ładowania obrazu {file_path}: {e}")
                    continue
    return tiles



def closest_tile_color(avg_color, tiles):
    def distance(c1, c2):
        return sum((a - b) ** 2 for a, b in zip(c1, c2))
    def helpFunc(tile):
        return distance(avg_color, tile[0])
    return min(tiles, key=helpFunc)[1] #zwraca najbardziej zblizony obrazek



def process_tile(args):
    x, y, block, tile_size, tiles = args
    avg_color = average_color(block)
    best_tile = closest_tile_color(avg_color, tiles) #szuka najbardziej zblizonego kafelka do sredniego rgb bloku z obrazu
    return x, y, best_tile #gdzie ma umiescic znaleziony kafelek


def create_mosaic(source_image_path, output_path, tile_size, out_width, out_height, tiles_dir):

    source = Image.open(source_image_path).resize((out_width, out_height)).convert("RGB")


    tiles = load_tile_images(tiles_dir, tile_size)
    if not tiles:
        print("Brak miniatur w folderze:", tiles_dir)
        return

    mosaic = Image.new('RGB', (out_width, out_height))
    args_list = []

    for i in range(0, out_width, tile_size):
        for j in range(0, out_height, tile_size):
            block = source.crop((i, j, i + tile_size, j + tile_size))
            args_list.append((i, j, block, tile_size, tiles)) #wspolrzedne i dane dla kazdego procesu potrzebne do znalezienia najlepszego kafelka


    with Pool(cpu_count()) as pool:
        results = pool.map(process_tile, args_list) #lista gdzie wkleic dany kafelek(multiprocessing)


    for x, y, tile in results:
        mosaic.paste(tile, (x, y))


    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    mosaic.save(output_path)
    print("Mozaika zapisana:", output_path)


if __name__ == '__main__':
    start = time.time()

    files = os.listdir(base_dir)
    for f in files:
        if f.lower().endswith(('.jpg', '.png')) and not f.startswith("result"):
            source_image_path = os.path.join(base_dir, f)
            break

    create_mosaic(source_image_path, output_path, tile_size, output_width, output_height, tiles_dir)

    end = time.time()
    print(f"Zrobione w {end - start:.2f} s")