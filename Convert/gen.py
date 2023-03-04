import numpy as np
import cv2
import joyo
import chardet
from PIL import Image, ImageFont, ImageDraw

#常用漢字を取得し,白黒 16px * 16px の一文字ずつのbmp画像をjoyo_/ディレクトリ内に生成するスクリプト


# 入力画像の読み込み
input_image = cv2.imread("plane.bmp", cv2.IMREAD_COLOR)

# フォントファイルを読み込み(Googleのフリーフォントを使用)
font = ImageFont.truetype('/home/kasagon/Documents/sazanami-20040629/sazanami-gothic.ttf', 16)

# 入力画像をPIL形式に変更してテキストを書き込み
image_pil = Image.fromarray(input_image)
draw = ImageDraw.Draw(image_pil)
a = '漢'
draw.text((0, -2), a, font = font, fill = (0,0,0))
output_image = np.array(image_pil)
result = cv2.imwrite("joyo_/jp_font_text.bmp", output_image)

# textlist = joyo.load()
#hiragana = [chr(i) for i in range(ord("ぁ"), ord("ゖ")+1)]
katakana = [chr(i) for i in range(ord("ァ"), ord("ヺ")+1)]
for s in katakana:
    image_pil = Image.fromarray(input_image)
    draw = ImageDraw.Draw(image_pil)
    draw.text((0, -2), s, font = font, fill = (0,0,0))
    output_image = np.array(image_pil)
    filename = "katakana/" + s + ".bmp"
    result = cv2.imwrite(filename, output_image)
    print(filename)
