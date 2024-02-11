# This code snippet imports the re module for regular expression operations.
# It opens an input file named '023.txt' for reading and an output file named '023output.txt' for writing.
# The code iterates through each line of the input file.
# For each line, it finds all hexadecimal numbers using a regular expression pattern.
# Then, it converts the hexadecimal numbers to decimal integers, adjusting for signed 16-bit representation.
# Next, it converts the decimal integers to floating point numbers, scaling them to the range [-1, 1].
# Finally, it writes the floating point numbers to the output file.


import re
# Open input and output files
with open('023.txt', 'r') as f_in, open('023output.txt', 'w') as f_out:
    # Iterate through each line of the input file
    for line in f_in:
        # Find all hexadecimal numbers in the line
        hex_nums = re.findall(r'0x\w+', line)
        
        # Convert hexadecimal numbers to decimal integers
        #dec_nums = [int(hex_num, 16) for hex_num in hex_nums]
        dec_nums = [int(hex_num, 16) - 65535 if int(hex_num, 16) > 32767 else int(hex_num, 16) for hex_num in hex_nums]

        # Convert decimal integers to floating point numbers
        float_nums = [round(dec_num / 32768, 15) for dec_num in dec_nums]
        
        # Write floating point numbers to output file
        f_out.write(str(float_nums) + '\n')
