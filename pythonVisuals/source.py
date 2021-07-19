import matplotlib.pyplot as plt
import numpy as np

#manually fill out
runs = 25
xinter = 30
yinter = 30
  
# copy and paste the array output from the write() function in the cpp source
print("Enter the entries in a single line (separated by space): ")
  
entries = list(map(int, input().split()))

matrix = np.array(entries).reshape(200, 100)
  
plt.imshow(matrix, cmap='Greys', interpolation='nearest')
# filename format = "(xintercept-yintercept)runs-porosity.png, e.g. (30-30)25por2100.png"
plt.savefig('({}-{}){}-por{}.png'.format(xinter, yinter, runs, yinter*(100 - xinter)), dpi=300)
plt.show()
