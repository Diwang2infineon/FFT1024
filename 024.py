# This code snippet imports the re module for regular expression operations and the sys module for system-specific parameters and functions.
# It redirects the standard output to a file named '024output.txt'.
# The code opens the file '023output.txt' for reading and reads its contents.
# Then, it uses regular expressions to extract numbers from the contents and stores them as floats in a list.
# The code iterates over the list of numbers, formatting and printing them in the desired format.
# Finally, it closes the standard output file.

import re
import sys
sys.stdout = open('024output.txt', 'w')

# Open the file and read the contents
with open("023output.txt", "r") as f:
    contents = f.read()

# Use regex to extract the numbers and store as floats in a list
nums = re.findall(r"[-+]?\d*\.\d+|\d+", contents)
nums = [float(x) for x in nums]

# Output the numbers in the desired format

for i in range(0, len(nums)-1,2):
    if nums[i+1]>0:
        print("        {:.15f}+{:.15f}i;".format(nums[i], nums[i+1]))
    else:
        print("        {:.15f}{:.15f}i;".format(nums[i], nums[i+1]))

sys.stdout.close()
