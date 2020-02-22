import numpy as np
from scipy.signal import spectrogram, hanning

M = 4096
NFFT = M
win = hanning(M)
overlap = 0.5
overlap_samples = int(round(M*overlap)) # overlap in samples
t, f, S = spectrogram(x,window=win,nperseg=M,noverlap=overlap_samples,nfft=NFFT)

# Compute average spectrum
avg_S = np.mean(S,axis=1)
