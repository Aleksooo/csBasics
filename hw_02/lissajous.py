from re import A
import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation

a = 1
b = 2
delta = np.pi / 2
print(np.gcd(a, b))
t = np.linspace(0, 2*np.gcd(a, b) * np.pi, 100)

x_data, y_data = [], []

# x = np.sin(a * t + delta)
# y = np.sin(b * t)

fig, ax = plt.subplots()
ln, = plt.plot([], [])

def init():
    ax.set_xlim(-1, 1)
    ax.set_ylim(-1, 1)

    return ln,

def update(frame):
    x_data.append(np.sin(a * frame + delta))
    y_data.append(np.sin(b * frame))
    ln.set_data(x_data, y_data)

    return ln,

ani = FuncAnimation(fig, update, frames=t, init_func=init, blit=True)
plt.show()
