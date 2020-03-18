import numpy as np
import matplotlib.pyplot as plt
try:	
	data=np.loadtxt ("cubic.txt")
	plt.plot(data[:,0], data[:,1])
	plt.gcf().canvas.set_window_title("Cubic")
	data=np.loadtxt ("uzly.txt")
	plt.plot(data[:,0], data[:,1], 'go')
	plt.minorticks_on()
	plt.grid(color="blue", which="major", linewidth=1)
	plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
	plt.show()
	
except BaseException:
	print("faila nema")
