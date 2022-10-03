from re import A
import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation

a = 7
b = 10
delta = np.pi / 2
print(np.gcd(a, b))
t_max = 2 * np.pi / np.gcd(a, b)
dt = 0.01
frames = np.arange(0, t_max, dt)
N = frames.size
print(N)

t, x_data, y_data = [], [], []

fig, (ax1, ax2, ax3) = plt.subplots(3, 1)
ln1, = ax1.plot([], [])
ln2, = ax2.plot([], [])
ln3, = ax3.plot([], [])

def init():
    ax1.set_xlim(-1, 1)
    ax1.set_ylim(-1, 1)

    ax2.set_xlim(0, t_max)
    ax2.set_ylim(-1, 1)

    ax3.set_xlim(0, t_max)
    ax3.set_ylim(-1, 1)
    return ln1, ln2, ln3,

def update(frame):
    x_data.append(np.sin(a * frame + delta))
    y_data.append(np.sin(b * frame))
    t.append(frame)

    ln1.set_data(x_data, y_data)
    ln2.set_data(t, x_data)
    ln3.set_data(t, y_data)

    return ln1, ln1, ln2, ln3,

ani = FuncAnimation(fig, update, frames=frames,
    init_func=init, blit=True, interval=100, repeat=False)
plt.show()
