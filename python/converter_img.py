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


#=======================================================================================

import os
from PIL import Image
import threading
import time


def load_photo(file_name: str, width: int = 0, height: int = 0):
    photo = Image.open(file_name)
    photo = photo.convert("RGB")
    if width == 0 and height == 0:
        size = photo.size
        photo = photo.resize((size[0], size[1]))
    else:
        photo = photo.resize((width, height))
    return photo



def save_photo(file_name, photo):
    photo.save(file_name)
def make_small_photo(file_name, step_block, if_convert: bool = True):
    photo_small = Image.open(file_name)
    photo_small = photo_small.resize((step_block, step_block))
    photo_small = photo_small.convert("RGB")
    return photo_small

def fill_og_with_small(file_name_og: str,file_out: str,step_block: int, width: int, height: int):
    photo_small = make_small_photo(file_name_og, step_block)
    photo = load_photo(file_name_og, width, height)
    pixels = photo.load()
    pixelsResult = photo.load()
    for i in range(int(width / step_block)):
        for j in range(int(height / step_block)):
            r, g, b = (0,0,0)
            for x in range(step_block):
                for y in range(step_block):
                    rPpx, gPpx, bPpx = pixels[i*step_block+x, j*step_block+y]
                    r += rPpx
                    g += gPpx
                    b += bPpx
            rgb_part = (int(r/(step_block*step_block)),
                        int(g/(step_block*step_block)),
                        int(b/(step_block*step_block)))

            photo_part = Image.new('RGB', (step_block, step_block), rgb_part)
            photo_blended = Image.blend(photo_part, photo_small, alpha=0.5)
            pixels_blended = photo_blended.load()
            for x in range(step_block):
                for y in range(step_block):
                    pixelsResult[i * step_block + x, j * step_block + y] = pixels_blended[x, y]
    save_photo(file_out, photo)

def fill_all_photos(dir_out):
    path_with_photos = "/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/sea"
    files = os.listdir(path_with_photos)

    photos = []
    c = 0
    for file in files:
        file_path = os.path.join(path_with_photos, file)
        file_path_out = os.path.join(dir_out, f"nr{c}-{file}")
        photo = threading.Thread(target = fill_og_with_small, args=(file_path, file_path_out, 5, 150, 150 ))
        photos.append(photo)
        photo.start()
        c += 1
        print(f"watek {c}")

if __name__ == '__main__':

    begin = time.time()
    fill_all_photos("/home/u335775/Pulpit/Łukasz Kolczyński/pw-spi/python/convert_photos/result")
    end = time.time()
    print(f"Time: {end-begin}")

#=======================================================================================================