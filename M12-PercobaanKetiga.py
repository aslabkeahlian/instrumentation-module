# JGN LUPA DOWNLOAD LIBRARY CV2 DAN SKIMAGE

import cv2
import matplotlib.pyplot as plt
import numpy as np

img_bgr = cv2.imread('pulau4.jpg')
img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)
img_hsv = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2HSV)

# Deteksi Laut (Hue Biru)
lower_blue = np.array([75, 38, 0])
upper_blue = np.array([126, 255, 255])
mask_laut = cv2.inRange(img_hsv, lower_blue, upper_blue)

# Inversi
mask_daratan = cv2.bitwise_not(mask_laut)

# Pembersihan Masker 
num_labels, labels, stats, _ = cv2.connectedComponentsWithStats(mask_daratan, connectivity=8)
clean_mask = np.zeros_like(mask_daratan)
for i in range(1, num_labels):
    if stats[i, cv2.CC_STAT_AREA] >= 5:
        clean_mask[labels == i] = 255

contours, _ = cv2.findContours(clean_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
final_mask = np.zeros_like(clean_mask)
cv2.drawContours(final_mask, contours, -1, 255, thickness=cv2.FILLED)

# Ekstraksi Daratan
img_hasil = img_rgb.copy()
img_hasil[final_mask == 0] = [255, 255, 255]

# Hitung Statistik Ulang setelah pembersihan
num_labels, labels, stats, centroids = cv2.connectedComponentsWithStats(final_mask, connectivity=8)
n_pulau = num_labels - 1

plt.figure(figsize=(15, 5))
plt.subplot(1, 3, 1)
plt.imshow(img_rgb)
plt.title('1. Gambar Asli')
plt.axis('off')

plt.subplot(1, 3, 2)
plt.imshow(final_mask, cmap='gray')
plt.title(f'2. Masker Biner (N = {n_pulau})')
plt.axis('off')

plt.subplot(1, 3, 3)
plt.imshow(img_hasil)

print("\n--- Daftar Luas Pulau ---")
for i in range(1, num_labels):
    area_px = stats[i, cv2.CC_STAT_AREA]
    cx, cy = centroids[i]
    plt.text(cx, cy, str(i), color='red', fontsize=10, fontweight='bold', ha='center')
    plt.text(cx, cy + 15, f"{area_px} px", color='blue', fontsize=7, ha='center')

print(f"Pulau {i}: {area_px} piksel")

plt.title('3. Identifikasi & Luas (px)')
plt.axis('off')

plt.tight_layout()
plt.show()
