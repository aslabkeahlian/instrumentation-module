# JGN LUPA DOWNLOAD LIBRARY CV2 DAN SKIMAGE

import cv2
import matplotlib.pyplot as plt
import numpy as np
from skimage import color, measure, morphology

img = cv2.imread('ubinwarna.jpg')
img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

if img.ndim == 3:
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
else:
    img_gray = img.copy()

# Binerisasi (Thresholding)
_, bw_nat = cv2.threshold(img_gray, 140, 255, cv2.THRESH_BINARY)

# Pertebal Garis Nat (Dilasi pada Nat)
se = morphology.disk(3)
bw_nat_thick = cv2.dilate(bw_nat, se)

# Inversi 
ubin_objek = cv2.bitwise_not(bw_nat_thick)

# Pembersihan Noise
ubin_objek_bool = ubin_objek > 0
ubin_objek_clean = morphology.remove_small_objects(
    ubin_objek_bool, min_size=100
)

# Analisis dan Labeling
L = measure.label(ubin_objek_clean, connectivity=2)
N = L.max()
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
plt.subplot(1, 3, 3)
plt.imshow(img_rgb)
for i, prop in enumerate(stats):
    y, x = prop.centroid  # Centroid di skimage berurutan (baris/y, kolom/x)
    plt.text(x, y, str(i + 1), color='red', fontsize=12, fontweight='bold', ha='center', va='center')

plt.title('Identifikasi & Penomoran Ubin')
plt.axis('off')
plt.title('Identifikasi Ubin')
plt.axis('off')

plt.tight_layout()
plt.show()
