import numpy as np
import matplotlib.pyplot as plt

# ===== 1. DEKLARASI SINYAL (isi sendiri) =====
n = np.arange(____, ____)          # indeks sampel
f = ____                           # frekuensi (siklus/sampel)
x = ____                           # x[n] = sin(2*pi*f*n)

# ===== 2. ELEMEN DASAR (isi sendiri) =====
def delay(signal, k=1):
    return ____

def gain(signal, k=0.5):
    return ____

def adder(*signals):
    return ____

# ===== 3. PEMROSESAN (tentukan k sendiri) =====
x_delay = delay(x, k=____)
x_gain  = gain(x, k=____)
x_sum   = adder(x, x_delay)

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
