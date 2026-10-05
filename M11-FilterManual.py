# ========== VARIASI YANG DIGUNAKAN ==========
# sinyal input = sinus/sinus+noise
# filter = pake lowpass/highpass
# opsional = bisa dibandingin antara lowpass dan highpass

import numpy as np
import matplotlib.pyplot as plt

# ========== DEKLARASI SINYAL ==========
n = np.arange(0, 100)
x = np.sin(2 * np.pi * 0.05 * n)

# ========== FUNGSI FIR & IIR MANUAL ==========
def manual_fir(x, h):
    y = np.zeros_like(x, dtype=float)
    for n in range(len(x)):
        for k in range(len(h)):
            if n - k >= 0:
                y[n] += h[k] * x[n - k]        #rumus FIR
    return y

def manual_iir(x, b, a):
    y = np.zeros_like(x, dtype=float)
    for n in range(len(x)):
        for k in range(len(b)):
            if n - k >= 0:
                y[n] += b[k] * x[n - k]        #rumus IIR

        for k in range(1, len(a)):
            if n - k >= 0:
                y[n] -= a[k] * y[n - k]        #rumus IIR

        y[n] /= a[0]
    return y

# ========== FILTER FIR & IIR ==========       #ini nilai h, b, a nya diganti
h_fir = [1/3, 1/3, 1/3]                        #nilai sum(h_fir) = 1
b = [0.2]                                      #nilai koefisien feedback lebih kuat/lemah
a = [1.0, -0.8]                  

y_fir = manual_fir(x, h_fir)
y_iir = manual_iir(x, b, a)

# ========== ANALISIS FREKUENSI ==========
fs = 100
freqs = np.linspace(0, fs/2, 50)

amp_fir = []
amp_iir = []

for f in freqs:
    t = np.arange(0, 200) / fs
    x_test = np.sin(2 * np.pi * f * t)
    y_test_fir = manual_fir(x_test, h_fir)
    y_test_iir = manual_iir(x_test, b, a)
    amp_in = np.sqrt(np.mean(x_test[-50:]**2))
    amp_out_fir = np.sqrt(np.mean(y_test_fir[-50:]**2))
    amp_out_iir = np.sqrt(np.mean(y_test_iir[-50:]**2))
    amp_fir.append(amp_out_fir / amp_in)
    amp_iir.append(amp_out_iir / amp_in)

# ========== PLOT TIME DOMAIN OUTPUT ==========
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.plot(n, x, label="Input x[n]", alpha=0.7)
plt.plot(n, y_fir, label="FIR output", linewidth=2)
plt.plot(n, y_iir, label="IIR output", linewidth=2)
plt.legend()
plt.xlabel("n (sample)")
plt.ylabel("Amplitude")
plt.title("Output Filter (Time Domain)")
plt.grid(True)

# ========== PLOT FREQUENCY RESPONSE ==========
plt.subplot(1, 2, 2)
plt.plot(freqs, amp_fir, 'o-', label="FIR (LPF)")
plt.plot(freqs, amp_iir, 's-', label="IIR (LPF)")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Gain (output/input)")
plt.title("Frequency Response (Magnitude)")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
