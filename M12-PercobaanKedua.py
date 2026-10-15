import cv2
import matplotlib.pyplot as plt
import numpy as np
from skimage import color, feature, measure, morphology

img = cv2.imread('ubin.jpg')
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

if img.ndim == 3:
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
else:
    img_gray = img.copy()

# Deteksi Tepi (Canny)
tepi = feature.canny(img_gray, sigma=1)

# Dilasi
se = morphology.disk(2)
garis_pembatas = morphology.dilation(tepi, se)

# Inversi
ubin_objek = ~garis_pembatas

# Bersihkan Noise
ubin_objek_clean = morphology.remove_small_objects(
    ubin_objek, min_size=200
)

# Labeling
L = measure.label(ubin_objek_clean, connectivity=2)
N = L.max()

# Analisis Properti (Area dan Centroid)
stats = measure.regionprops(L)
all_areas = [prop.area for prop in stats]

print(f"Jumlah ubin yang terdeteksi (N): {N}")
print("Luas tiap ubin:", all_areas)

plt.figure(figsize=(15, 5))
plt.subplot(1, 3, 1)
plt.imshow(ubin_objek_clean, cmap='gray')
plt.title('Masker Ubin (Terpisah)')
plt.axis('off')

plt.subplot(1, 3, 2)
img_label_rgb = color.label2rgb(L, bg_label=0)
plt.imshow(img_label_rgb)
plt.title(f'N = {N}')
plt.axis('off')

plt.subplot(1, 3, 3)
plt.imshow(img_rgb)

for i, prop in enumerate(stats):
    y, x = prop.centroid
    plt.text(x, y, str(i + 1), color='red', fontsize=10, fontweight='bold', ha='center', va='center')

plt.title('Identifikasi Ubin Marmer')
plt.axis('off')

plt.tight_layout()
plt.show()
