%{
  
  In this code, we start by defining the necessary parameters such as numPoints (total number of points), sampleFrequency (sample frequency in Hz), signalFrequency (signal frequency in Hz), and pointsPerCycle (number of points per cycle).

A signal is then generated using a sine wave with a frequency of signalFrequency. The time vector t is created using the linspace function, spanning the duration of the signal based on the numPoints and sampleFrequency.

Next, the FFT of the signal is computed using the fft function, yielding fftResult, which represents the complex-valued FFT coefficients. The magnitude spectrum is obtained by calculating the absolute values of fftResult, stored in fftMagnitude. This spectrum is then normalized by dividing it by numPoints to obtain fftMagnitudeNormalized.

The frequency axis is determined using the formula frequencyAxis = (0:numPoints-1) * sampleFrequency / numPoints, representing the frequency values corresponding to each FFT coefficient.

Finally, the code plots the waveform of the signal in the first subplot, and the FFT magnitude spectrum in the second subplot. Appropriate labels and titles are provided to enhance the interpretation of the plots.

By executing this code in MATLAB, you will visualize the waveform and the FFT magnitude spectrum of the generated signal with a frequency of 256 Hz.
%}


% Parameters
numPoints = 1024;            % Total number of points
sampleFrequency = 1024;      % Sample frequency in Hz
signalFrequency = 256;        % Signal frequency in Hz
pointsPerCycle = sampleFrequency / signalFrequency;  % Number of points per cycle

% Generate signal
t = linspace(0, numPoints/sampleFrequency, numPoints+1);  % Time vector
signal = sin(2*pi*signalFrequency*t);  % Generate signal (sine wave)

% Perform FFT
fftResult = fft(signal, numPoints);
fftMagnitude = abs(fftResult);
fftMagnitudeNormalized = fftMagnitude / numPoints;

% Frequency axis
frequencyAxis = (0:numPoints-1) * sampleFrequency / numPoints;


% Plot the waveform
subplot(2,1,1)
plot(signal)
xlabel('Sample')
ylabel('Amplitude')
title('Waveform with  256Hz (1024 points total)')
subplot(2,1,2)

% Plot the FFT magnitude
plot(frequencyAxis, fftMagnitudeNormalized)
xlabel('Frequency (Hz)')
ylabel('Magnitude')
title('FFT of the Signal')
