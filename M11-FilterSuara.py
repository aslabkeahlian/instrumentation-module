# ========== LANGKAH - LANGKAH ==========
# Pertama kalian cari/rekam suara dengan tipe file ".wav" dan diupload di folder yang sama seperti kodingan
# Kedua dari file yang ada analisa grafik FFT dari audionya
# Ketiga bisa lgsg pilih mau pakai filter apa
# Keempat file yang ada bisa di filter lagi jika dirasa krg bagus
# NOTES : kodingan bisa disesuaikan sendiri, ini bisa jadi acuan pertama kalian

import numpy as np
import scipy.io.wavfile as wav
import matplotlib.pyplot as plt
from scipy.signal import butter, firwin, lfilter, filtfilt

# ========== BACA AUDIO ==========
sample_rate, data = wav.read("DataAudio.wav")                                # tolong diisi dengan nama file rekamannya

if len(data.shape) > 1:
    data = np.mean(data, axis=1)

times = np.arange(len(data)) / sample_rate

# ========== ANALISA FFT ==========
fft_data = np.fft.fft(data)
frequencies = np.fft.fftfreq(len(data), 1 / sample_rate)

plt.figure(figsize=(10, 4))
plt.plot(
    frequencies[:len(frequencies) // 2],
    np.abs(fft_data[:len(fft_data) // 2]),
    color="red"
)
plt.title("FFT Magnitude Spectrum (Original Audio)")
plt.xlabel("Frequency [Hz]")
plt.ylabel("Magnitude")
plt.grid(True)
plt.show()

print("=== LIHAT SPEKTRUM DI ATAS ===")
print("Gunakan grafik FFT untuk menentukan cutoff frequency yang sesuai.\n")

# ========== MENU FILTER ==========
print("=== DESAIN FILTER AUDIO ===")
print("1. FIR Low-Pass")
print("2. FIR High-Pass")
print("3. FIR Band-Pass")
print("4. IIR Butterworth Low-Pass")
print("5. IIR Butterworth High-Pass")
print("6. IIR Butterworth Band-Pass")
print("7. FIR Band-Reject (Notch)")
print("8. IIR Butterworth Band-Reject (Notch)")

choice = int(input("Pilih jenis filter (1–8): "))

# Input cutoff
if choice in [1, 2, 4, 5]:
    cutoff = float(input("Masukkan frekuensi cutoff (Hz): "))
    cutoff_norm = cutoff / (0.5 * sample_rate)

elif choice in [3, 6, 7, 8]:
    lowcut = float(input("Masukkan frekuensi lowcut (Hz): "))
    highcut = float(input("Masukkan frekuensi highcut (Hz): "))
    cutoff_norm = [
        lowcut / (0.5 * sample_rate),
        highcut / (0.5 * sample_rate)
    ]

# Parameter filter                    # ini tidak perlu diganti, tapi bisa dicari tau kenapa nilainya segini
order = 101      # FIR
iir_order = 6    # IIR

# ========== PROSES FILTER ==========
if choice == 1:  # FIR Low-pass
    h = firwin(order, cutoff_norm, window="hamming", pass_zero=True)
    filtered = lfilter(h, 1.0, data)
    jenis = f"FIR Low-Pass {cutoff} Hz"

elif choice == 2:  # FIR High-pass
    h = firwin(order, cutoff_norm, window="hamming", pass_zero=False)
    filtered = lfilter(h, 1.0, data)
    jenis = f"FIR High-Pass {cutoff} Hz"

elif choice == 3:  # FIR Band-pass
    h = firwin(order, cutoff_norm, window="hamming", pass_zero=False)
    filtered = lfilter(h, 1.0, data)
    jenis = f"FIR Band-Pass {lowcut}-{highcut} Hz"

elif choice == 4:  # IIR Low-pass
    b, a = butter(iir_order, cutoff_norm, btype="low")
    filtered = filtfilt(b, a, data)
    jenis = f"IIR Butterworth Low-Pass {cutoff} Hz"

elif choice == 5:  # IIR High-pass
    b, a = butter(iir_order, cutoff_norm, btype="high")
    filtered = filtfilt(b, a, data)
    jenis = f"IIR Butterworth High-Pass {cutoff} Hz"

elif choice == 6:  # IIR Band-pass
    b, a = butter(iir_order, cutoff_norm, btype="band")
    filtered = filtfilt(b, a, data)
    jenis = f"IIR Butterworth Band-Pass {lowcut}-{highcut} Hz"

elif choice == 7:  # FIR Band-Reject (Notch)
    h = firwin(order, cutoff_norm, window="hamming", pass_zero=True)
    filtered = lfilter(h, 1.0, data)
    jenis = f"FIR Band-Reject (Notch) {lowcut}-{highcut} Hz"

elif choice == 8:  # IIR Band-Reject (Notch)
    b, a = butter(iir_order, cutoff_norm, btype="bandstop")
    filtered = filtfilt(b, a, data)
    jenis = f"IIR Butterworth Band-Reject (Notch) {lowcut}-{highcut} Hz"

# ========== PROSES MENYIMPAN FILE ==========
wav.write("DataAudioOut.wav", sample_rate, filtered.astype(np.int16))               # ini nama filenya juga diganti sesuai preferensi kalian
print(f"Filtered audio berhasil disimpan sebagai 'DataAudioOut.wav' ({jenis})")

# ========== PLOT TIME DOMAIN ==========
plt.figure(figsize=(12, 6))
plt.subplot(2, 1, 1)
plt.plot(times, data, color="gray")
plt.title("Original Audio Signal")
plt.xlabel("Time [s]")
plt.ylabel("Amplitude")
plt.grid(True)
plt.subplot(2, 1, 2)
plt.plot(times, filtered, color="blue")
plt.title(f"Filtered Signal ({jenis})")
plt.xlabel("Time [s]")
plt.ylabel("Amplitude")
plt.grid(True)
plt.tight_layout()
plt.show()

# ========== PLOT FFT ORIGINAL vs FILTERED ==========
fft_filtered = np.fft.fft(filtered)
plt.figure(figsize=(12, 5))
plt.plot(
    frequencies[:len(frequencies) // 2],
    np.abs(fft_data[:len(fft_data) // 2]),
    color="gray",
    label="Original FFT"
)
plt.plot(
    frequencies[:len(frequencies) // 2],
    np.abs(fft_filtered[:len(fft_filtered) // 2]),
    color="blue",
    label="Filtered FFT"
)
plt.title(f"FFT Comparison (Original vs Filtered) - {jenis}")
plt.xlabel("Frequency [Hz]")
plt.ylabel("Magnitude")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
