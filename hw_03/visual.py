from itertools import count
from turtle import width
import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation

def read_data(file):
    data = np.zeros((1, 1))
    params = {}
    with open(file) as inp:
        key, value = [], []
        line = inp.readline()
        for i in range(3):
            line = line.split(": ")
            key.append(line[0])
            value.append(float(line[1]))
            line = inp.readline()

        params = dict(zip(key, value))
        data = np.zeros((int(params["N"]), 2), dtype=float)

        count = 0
        while (line != ""):
            data[count] = np.array(list(map(float, line.split())))
            line = inp.readline()
            count += 1

    return params, data

file = "data100E.txt"
paramsE, dataE = read_data(file)

tE = np.linspace(paramsE["t_left"], paramsE["t_right"] , int(paramsE["N"]))
xE = dataE[:, 0]

file = "data100H.txt"
paramsH, dataH = read_data(file)

tH = np.linspace(paramsH["t_left"], paramsH["t_right"] , int(paramsH["N"]))
xH = dataH[:, 0]

plt.plot(tE, np.sin(tE), "--", color='orange', lw=1)
plt.plot(tE, xE, ".",  color='blue', ms=1.5)
plt.plot(tH, xH, ".",  color='green', ms=1.5)

plt.show()
