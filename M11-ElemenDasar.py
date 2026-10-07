# ========== VARIASI YANG DIGUNAKAN ==========
# sinyal input = sinus/sinus+noise/step/deret pulsa

import numpy as np
import matplotlib.pyplot as plt

# ========== DEKLARASI SINYAL ==========
n = np.arange(0, 100)             
f = 0.05                          
x = np.sin(2 * np.pi * f * n)                         # ini sinus, coba ubah ke step atau deret pulsa (salah satunya)

# ========== FUNGSI OPERASI DASAR SINYAL ==========
def delay(signal, k=1):
    """Elemen Delay (pergeseran waktu sejauh k sampel)"""
    return np.concatenate([np.zeros(k), signal[:-k]])

def gain(signal, k=0.5):
    """Elemen Gain (pengali amplitudo)"""
    return k * signal

def adder(*signals):
    """Elemen Penjumlah (menjumlahkan beberapa sinyal)"""
    return np.sum(np.array(signals), axis=0)

# ========== PEMROSESAN (tentukan k) ==========
x_delay = delay(x, k=____)                             # nilai delay bisa sebebasnya
x_gain  = gain(x, k=____)                              # nilai gain bisa sebebasnya
x_sum   = adder(x, x_delay)                            # otomatis ditambah dari nilai delay dan gain

# ========== VISUALISASI HASIL ==========
plt.figure(figsize=(12, 8))

# Subplot 1: Elemen Delay
plt.subplot(3, 1, 1)
plt.plot(n, x, 'b-', linewidth=2, label='Sinus Asli x[n]')
plt.plot(n, x_delay, 'r--', linewidth=2, label='Delay x[n-10]')
plt.title("Elemen Delay (Gelombang Sinus)")
plt.xlabel("n (sampel)")
plt.ylabel("Amplitudo")
plt.legend(loc='upper right')
plt.grid(True)

# Subplot 2: Elemen Gain
plt.subplot(3, 1, 2)
plt.plot(n, x, 'b-', linewidth=2, label='Sinus Asli x[n]')
plt.plot(n, x_gain, 'g-.', linewidth=2, label='1.5 · x[n]')
plt.title("Elemen Gain (Pengali 1.5)")
plt.xlabel("n (sampel)")
plt.ylabel("Amplitudo")
plt.legend(loc='upper right')
plt.grid(True)

# Subplot 3: Elemen Penjumlah (Adder)
plt.subplot(3, 1, 3)
plt.plot(n, x, 'b:', linewidth=1.5, alpha=0.7, label='Sinus Asli x[n]')
plt.plot(n, x_delay, 'r:', linewidth=1.5, alpha=0.7, label='Delay x[n-10]')
plt.plot(n, x_sum, 'm-', linewidth=2, label='Hasil Penjumlahan (x[n] + x[n-10])')
plt.title("Elemen Penjumlah (Adder)")
plt.xlabel("n (sampel)")
plt.ylabel("Amplitudo")
plt.legend(loc='upper right')
plt.grid(True)

plt.tight_layout()
plt.show()
