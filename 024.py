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
