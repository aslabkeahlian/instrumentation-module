import numpy as np
import matplotlib.pyplot as plt
from skimage.transform import radon, iradon

# =======================================
# TAHAP 1: MEMBUAT CITRA ASLI (PHANTOM)
# =======================================
sz = 256 # Divariasikan
f = np.zeros((sz, sz))
y, x = np.ogrid[0:sz, 0:sz]
center = sz/2

# Membuat dinding organ (Densitas 0.3)
dinding_organ = ((x - center)**2 / 100**2 + (y - center)**2 / 120**2) <= 1
f[dinding_organ] = 0.3 # Divariasikan

ddo = round(sum(f[dinding_organ])/len(f[dinding_organ]),1)

# organ_satu (Densitas Rendah/Udara 0.1)
organ_satu_kanan = ((x - (center-45))**2 / 35**2 + (y - center)**2 / 70**2) <= 1
f[organ_satu_kanan] = 0.1 # Divariasikan

organ_satu_kiri = ((x - (center+45))**2 / 35**2 + (y - center)**2 / 70**2) <= 1
f[organ_satu_kiri] = 0.1 # Divariasikan

dos = round((sum(f[organ_satu_kanan])/len(f[organ_satu_kanan]) + sum(f[organ_satu_kiri])/len(f[organ_satu_kiri]))/2, 1)

# organ_dua (Densitas 0.6)
organ_dua = ((x - center)**2 / 20**2 + (y - (center+20))**2 / 25**2) <= 1
f[organ_dua] = 0.6 # Divariasikan

dod = round(sum(f[organ_dua])/len(f[organ_dua]), 1)

# Nodul/Tumor (Objek Kecil Padat 0.9)
nodul = ((x - (center-50))**2 + (y - (center-30))**2) <= 5**2
f[nodul] = 0.9 # Divariasikan

don = round(sum(f[nodul])/len(f[nodul]), 1)

# =======================================
# TAHAP 2: MEMBUAT SINOGRAM
# =======================================
theta = np.linspace(0., 180., max(f.shape), endpoint=False)
sinogram = radon(f, theta=theta)

# =======================================
# TAHAP 3: BACK PROJECTION MURNI
# =======================================

# filter_name=None mensimulasikan efek kabur 1/r
bp_murni = iradon(sinogram, theta=theta, filter_name=None)

# =======================================
# TAHAP 4: FILTERED BACK PROJECTION MURNI
# =======================================

# filter_name='ramp' adalah standar untuk ketajaman
fbp_hasil = iradon(sinogram, theta=theta, filter_name='ramp')

# =======================================
# TAHAP 5: PERHITUNGAN SNR
# =======================================

# --- PERHITUNGAN SNR ---
def hitung_snr(asli, rekonstruksi):
    """
    SNR = 10 * log10( sum(Asli^2) / sum((Asli - Rekonstruksi)^2) )
    """
    sinyal = np.sum(asli**2)
    # Menghitung noise/error (selisih antara asli dan rekonstruksi)
    noise = np.sum((asli - rekonstruksi)**2)
    # Mencegah pembagian dengan nol
    if noise == 0:
        return float('inf')
    snr_val = 10 * np.log10(sinyal / noise)
    return snr_val

# Hitung SNR untuk kedua metode
snr_murni = hitung_snr(f, bp_murni)
snr_fbp = hitung_snr(f, fbp_hasil)


# ==========================================
# VISUALISASI BERURUTAN
# ==========================================
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(10, 10))
judulWindow = f'Hasil CT Scan_Resolusi {sz}_Densitas [{str(ddo).replace('.',',')}, {str(dos).replace('.',',')}, {str(dod).replace('.',',')}, {str(don).replace('.',',')}]'
fig.canvas.manager.set_window_title(judulWindow)
fig.canvas.get_default_filename = lambda: judulWindow.replace(" ", "")

# 1. Citra Asli
ax1.set_title('1. Citra Asli (Phantom Organ)')
ax1.imshow(f, cmap='bone')
ax1.axis('off')

# 2. Sinogram
ax2.set_title('2. Sinogram (Data Mentah)')
ax2.imshow(sinogram, cmap='hot', aspect='auto')
ax2.set_xlabel(r'$\theta$ (sudut)')
ax2.set_ylabel('r (posisi)')

# 3. Back-Projection Murni
ax3.set_title(f"3. BP Murni (SNR: {snr_murni:.2f} dB)")
ax3.imshow(bp_murni, cmap='bone')
ax3.set_xlabel('Hasil: Kabur/Blur')
ax3.axis('off')

# 4. Filtered Back-Projection
ax4.set_title(f"4. Filtered BP (SNR: {snr_fbp:.2f} dB)")
ax4.imshow(fbp_hasil, cmap='bone')
ax4.set_xlabel('Hasil: Tajam & Akurat')
ax4.axis('off')
plt.tight_layout()
plt.show()

# Menampilkan hasil di Konsol
print(f"SNR Back-Projection Murni: {snr_murni:.2f} dB")
print(f"SNR Filtered Back-Projection: {snr_fbp:.2f} dB")