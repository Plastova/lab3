#-*- coding: utf-8 -*-
import matplotlib.pyplot as plt
import pylab
import numpy as np
import csv
import scipy as sp
from scipy.optimize import fsolve
from scipy.interpolate import lagrange


x=[]
a=[]
month=[]
defined = []
d1=0
d2=0
d3=0
d4=0
d5=0
d6=0
d=0
def read_csv_file(filename):
	print("Выберите столбец 1-12:")
	st=int(input())
	f = open(filename)
	global a, month,defined
	for row in csv.reader(f):
		stroka=" ".join(row)
		a=stroka.split(' ')
		month.append(a[st])
	f.close()
	del month[0]
	
	print(" ")
	for i in range (len(month)):
		if month[i]!="999.9":
			defined.append(float(month[i]))
			
def make_x(r):
	global x
	for i in range (r):
		x.append(i)	
		
print("Note: в 5 задании после закрытия общего графика можно самостоятельно выбрать степень полинома")
read_csv_file("data.csv")
l=len(defined)

print("Введите индекс стартового элемента от 0 до")
print(l-12)
start=int(input())
make_x(12)
a=[]
for i in range (start, start+12):
		a.append(defined[i])
for i in range (12):
		print(a[i])		

#Lagrange
poly = lagrange(x, a)
print (poly)
dx=0.1

xlist = np.arange (0, 11.1, dx)
ylist = [poly(g) for g in xlist]
plt.plot (xlist, ylist,'g-')
plt.plot (x,a,'ro')
plt.gcf().canvas.set_window_title("Lagrange")
plt.minorticks_on()
plt.grid(color="blue", which="major", linewidth=1)
plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
pylab.show()


#Newton1
def delty1 (m0, m1,m2, m3, m4, m5,m6):
	global d1,d2,d3,d4,d5,d6
	d1=m1 - m0
	d2=m2 - 2 * m1 + m0
	d3=m3 - 3 * m2 + 3 * m1 - m0
	d4=m4 - 4 * m3 + 6 * m2 - 4 * m1 + m0
	d5=m5 - 5 * m4 + 10 * m3 - 10 * m2 + 5 * m1 - m0
	d6=m6 - 6 * m5 + 15 * m4 - 20 * m3 + 15 * m2 - 6 * m1 + m0


def New1(k):
	global a
	s=a[0]
	x0 = 0 
	h = 1
	d = [d1,d2,d3,d4,d5,d6]
	q = (k - x0) / h
	s += q * d[0]
	for i in range (1,6):
		q *= ((k - x0) / h - i) / (i + 1)
		s += q * d[i]
	return s;

delty1(a[0],a[1],a[2],a[3],a[4],a[5],a[6])
xlist = np.arange (0, 5.1, dx)
ylist = [New1(g) for g in xlist]
plt.plot (xlist, ylist,'r-')
an=[]
xn=[]
for i in range (start, start+6):
		an.append(defined[i])
for i in range (6):
		xn.append(i)	
plt.plot (xn,an,'go')
plt.gcf().canvas.set_window_title("New1")
plt.minorticks_on()
plt.grid(color="blue", which="major", linewidth=1)
plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
pylab.show()

#Newton2
def New2(k):
	global a
	s=a[6]
	x0 = 6 
	h = 1
	d = [d1,d2,d3,d4,d5,d6]
	q = (k - x0) / h
	s += q * d[0]
	for i in range (1,6):
		q *= ((k - x0) / h + i) / (i + 1)
		s += q * d[i]
	return s

def delty2 (m0, m1,m2, m3, m4, m5,m6):
	global d1,d2,d3,d4,d5,d6
	d1=m6 - m5
	d2=m6 - 2 * m5 + m4
	d3=m6 - 3 * m5 + 3 * m4 - m3
	d4=m6 - 4 * m5 + 6 * m4 - 4 * m3 + m2
	d5=m6 - 5 * m5 + 10 * m4 - 10 * m3 + 5 * m2 - m1
	d6=m6 - 6 * m5 + 15 * m4 - 20 * m3 + 15 * m2 - 6 * m1 + m0

delty2(a[0],a[1],a[2],a[3],a[4],a[5],a[6])	
dx=-0.1
xlist = np.arange (5, -0.1, dx)
ylist = [New2(g) for g in xlist]
plt.plot (xlist, ylist,'r-')
plt.plot (xn,an,'go')
plt.gcf().canvas.set_window_title("New2")
plt.minorticks_on()
plt.grid(color="blue", which="major", linewidth=1)
plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
pylab.show()

#step polinom
x=[]
a=[]
legend =[]
make_x(l)
for i in range (l):
		a.append(defined[i])
dx=0.1
fx = np.arange (0, l-1, dx)

for d in range(1, 6):    
	fp, residuals, rank, sv, rcond = sp.polyfit(x, a, d, full=True)  
	f = sp.poly1d(fp)
	plt.plot(fx, f(fx), linewidth=2)
	legend.append("deg=%i" % f.order)
	f2 = f - 1000 
	t = fsolve(f2, x[-1]) 
plt.legend(legend, loc="upper left")
plt.plot (x,a,'ro')
plt.gcf().canvas.set_window_title("Stepennoy polinom")
plt.minorticks_on()
plt.grid(color="blue", which="major", linewidth=1)
plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
plt.show()

print(" ")
print("Введите степень полинома 1-5:")
d=int(input())
legend =[]
fp, residuals, rank, sv, rcond = sp.polyfit(x, a, d, full=True)  
f = sp.poly1d(fp)
plt.plot(fx, f(fx), linewidth=2)
f2 = f - 1000 
t = fsolve(f2, x[-1]) 
print ("Полином степени")
print(d)
legend.append("deg=%i" % f.order)
plt.legend(legend, loc="upper left")
plt.plot (x,a,'ro')
plt.gcf().canvas.set_window_title("Stepennoy polinom")
plt.minorticks_on()
plt.grid(color="blue", which="major", linewidth=1)
plt.grid(color="blue", which="minor", linestyle=":", linewidth=0.5)
plt.show()

