#
#This Python code converts signed bytes to int16 and outputs the real and imaginary parts of the twiddle values.
#

data = "\n" \
       "\t.byte -1, 127, 0, 0, -1, 127, 0, 0, -1, 127, 0, 0,\n" \
       "\t.byte 65, 118, 5, -49, -126, 90, 126, -91, -5, 48, -65, -119,\n" \
       "\t.byte -126, 90, 126, -91, 0, 0, 1, -128, 126, -91, 126, -91,\n" \
       "\t.byte -5, 48, -65, -119, 126, -91, 126, -91, -65, -119, -5, 48"

# Remove unwanted characters and split into bytes
bytes_list =[int(x) for x in  data.replace("\n", "").replace("\t.byte", "").replace(" ", "").split(",")]

# Convert negative bytes to positive by adding 256
positive_byte_list = [x if x >= 0 else x + 256 for x in bytes_list]

# Convert each byte to a 2-digit hex string and concatenate them
hex_str = ' '.join([f'{x:02x}' for x in positive_byte_list])

# Print the result
print(hex_str)

# Combine each pair of bytes into a 16-bit integer and output its decimal value
decimal_values = [positive_byte_list[i+1] * 256 + positive_byte_list[i] for i in range(0, len(positive_byte_list), 2)]

# Print the decimal values
for value in decimal_values:
    if (value >32767):
        value=value-65536;
    print(value/32767)

