# ========== VARIASI YANG DIGUNAKAN ==========
# filter = pake lowpass/highpass

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import firwin, lfilter, butter, freqz

# ==========  DEKLARASI SINYAL ==========
fs = 1000                                                      # sampling frequency
n = np.arange(0, 1, 1/fs)
x = np.sin(2 * np.pi * 5 * n) + 0.5 * np.sin(2 * np.pi * 100 * n)

# ========== FIR FILTER ==========
numtaps = 51                                                   # variasi nilai numtaps
cutoff = 50                                                    # variasi nilai cutoff
h_fir = firwin(numtaps, cutoff, fs=fs)                         # coba ganti dengan metode selain firwin
y_fir = lfilter(h_fir, 1.0, x)

# ========== IIR FILTER ==========
order = 4                                                      # variasi nilai order
cutoff_iir = 50                                                # variasi nilai cutoff
b, a = butter(order, cutoff_iir / (fs / 2), btype='low')       # coba ganti dengan metode selain butter
y_iir = lfilter(b, a, x)

# ========== FREQUENCY RESPONSE ==========
w_fir, H_fir = freqz(h_fir, worN=8000, fs=fs)
w_iir, H_iir = freqz(b, a, worN=8000, fs=fs)

# ========== PLOT DATA ==========
plt.figure(figsize=(12, 8))

# Subplot1. : Time Domain
plt.subplot(2, 2, 1)
plt.plot(n, x, label="Input x[n]", alpha=0.7)
plt.plot(n, y_fir, label="FIR output")
plt.plot(n, y_iir, label="IIR output")
plt.xlim(0, 0.2)
plt.legend()
plt.title("Input & Output (Time Domain)")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.grid(True)

# Subplot2. : FIR Frequency Response
plt.subplot(2, 2, 2)
plt.plot(w_fir, 20 * np.log10(abs(H_fir)), label="FIR LPF")
plt.title("FIR Frequency Response")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.grid(True)

# Subplot3. : IIR Frequency Response
plt.subplot(2, 2, 4)
plt.plot(w_iir, 20 * np.log10(abs(H_iir)), label="IIR LPF", color='orange')
plt.title("IIR Frequency Response")
plt.xlabel("Frequency (Hz)")
plt.ylabel("Magnitude (dB)")
plt.grid(True)

plt.tight_layout()
plt.show()
