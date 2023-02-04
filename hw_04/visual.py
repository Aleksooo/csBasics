import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation


def read_data(file, pwd):
    data = np.zeros((1, 1))
    params = {}
    with open('/'.join([pwd,file]), 'r') as inp:
        key, value = [], []
        line = inp.readline()
        for i in range(4):
            line = line.split(": ")
            key.append(line[0])
            value.append(float(line[1]))
            line = inp.readline()

        params = dict(zip(key, value))
        data = np.zeros((int(params["N"]), 2), dtype=float)

        count = 0
        while (line != ""):
            # print(line)
            data[count] = np.array(list(map(float, line.split())))
            line = inp.readline()
            count += 1

    return params, data

def draw(files):
    for file in files:
        params, data = read_data(file, 'data')
        t = np.linspace(params["t_left"], params["t_right"] , int(params["N"]))
        x = data[:, 0]

        # plt.plot(tE, np.sin(tE), "--", color='orange', lw=1)
        plt.plot(t, x, lw=1.5)

    plt.gcf().set_dpi(20)
    plt.show()
