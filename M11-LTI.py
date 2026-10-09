# ========== VARIASI YANG DIGUNAKAN ==========
# sinyal input = sinus/sinus+noise/step

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import lfilter

# ========== FILTER FIR ==========                            # apakah harus dengan FIR?
h = [0.25, 0.5, 0.25]
n = np.arange(20)

# ========== UJI LINEARITAS ==========
x1 = np.sin(0.2 * np.pi * n)
x2 = np.cos(0.3 * np.pi * n)
x_sum = x1 + x2

y1 = lfilter(h, 1, x1**2)
y2 = lfilter(h, 1, x2**2)
y_sum = lfilter(h, 1, x_sum)

# ========== UJI TIME INVARIANCE ==========
x = np.zeros(20)
x[0] = 1
y = lfilter(h, 1, x)

delay = 5                                                      # variasikan nilai delaynya
x_shift = np.zeros(20)
x_shift[delay] = 1

y_shift = lfilter(h, 1, x_shift)
y_expected = np.zeros(20)
y_expected[delay:delay + len(y) - delay] = y[:len(y) - delay]

# ========== UJI HOMOGENITAS ==========
k = 3                                                          # variasikan nilai skalanya
x_test = np.sin(0.25 * np.pi * n)
y_test = lfilter(h, 1, x_test)

y_scaled_input = lfilter(h, 1, k * x_test)
y_scaled_output = k * y_test

# ========== PLOT DATA ==========
plt.figure(figsize=(12, 10))

# Subplot1. : Lineraritas
plt.subplot(3, 1, 1)
plt.plot(n, y_sum, 'r-', linewidth=2, label='h(x1 + x2)')
plt.plot(n, y1 + y2, 'bs', markersize=6, label='h(x1) + h(x2)')
plt.title("Uji Linearitas")
plt.xlabel("n")
plt.ylabel("Amplitudo")
plt.legend()
plt.grid(True)

# Subplot2. : Time-Invariance
plt.subplot(3, 1, 2)
plt.plot(n, y_shift, 'r-', linewidth=2, label='h(x_shift)')
plt.plot(n, y_expected, 'go', markersize=6, label='h(x) digeser')
plt.title("Uji Time-Invariance")
plt.xlabel("n")
plt.ylabel("Amplitudo")
plt.legend()
plt.grid(True)

# Subplot3. : Homogenitas
plt.subplot(3, 1, 3)
plt.plot(n, y_scaled_input, 'r-', linewidth=2, label='h(k·x)')
plt.plot(n, y_scaled_output, 'md', markersize=6, label='k·h(x)')
plt.title(f"Uji Homogenitas (k = {k})")
plt.xlabel("n")
plt.ylabel("Amplitudo")
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()
