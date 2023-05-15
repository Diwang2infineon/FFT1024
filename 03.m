X1Q15_fft16 = [
    -0.35379 + 0.53381i;
    -0.56195 + 0.82718i;
    -0.55511 + 0.04089i;
    0.32993 + 0.68829i;
    -0.35715 - 0.59216i;
    0.07544 + 0.86865i;
    -0.63217 - 0.41385i;
    0.35831 - 0.44846i;
    -0.22025 + 0.68033i;
    0.65186 + 0.42966i;
    0.64032 - 0.65814i;
    0.16940 - 0.88406i;
    -0.00626 + 0.71320i;
    0.72382 - 0.54477i;
    0.58234 - 0.36447i;
    0.26236 + 0.29230i
];


scaled_values = round(fft(X1Q15_fft16)*32768/16); % Scale the values
disp(scaled_values)
scaled_values_real_hex = dec2hex(real(scaled_values)); % Convert real components to hexadecimal
scaled_values_imag_hex = dec2hex(imag(scaled_values)); % Convert imaginary components to hexadecimal

% Display the result
for i = 1:length(scaled_values)
    disp(['Real: ', scaled_values_real_hex(i, :), ' Imaginary: ', scaled_values_imag_hex(i, :)]);
end
