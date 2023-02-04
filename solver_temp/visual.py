import json
import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation
import os

from algorithm import *

def visual(ids, mode):
    for file_id in ids:
        config = read_config(file_id)
        t = np.linspace(config['left'], config['right'], config['N'])

        data = read_data(file_id)

    if mode == 'xt':
        plt.plot(t, data[:, 0])
    elif mode == 'vt':
        plt.plot(t, data[:, 1])
    elif mode == 'vx':
        plt.plot(data[:, 0], data[:, 1])
    elif mode == 'at':
        plt.plot(t, data[:, 0])
    elif mode == 'bt':
        plt.plot(t, data[:, 2])
    elif mode == 'abt':
        plt.plot(t, data[:, 0], t, data[:, 2])

    plt.show()

def visual_x(ids): visual(ids, 'xt')
def visual_v(ids): visual(ids, 'vt')
def visual_phase(ids): visual(ids, 'vx')
def visual_a(ids): visual(ids, 'at')
def visual_b(ids): visual(ids, 'bt')
def visual_ab(ids): visual(ids, 'abt')

def visual_double_pendulum(ids):
    for file_id in ids:
        config = read_config(file_id)
        t = np.linspace(config['left'], config['right'], config['N'])
        data = read_data(file_id)

    L1 = config['L1']
    L2 = config['L2']
    L = L1 + L2 + 0.5
    dt = 2 * np.pi * (config['right'] - config['left']) / (config['N'] - 1)

    fig = plt.figure(figsize=(5, 4))
    ax = fig.add_subplot(autoscale_on=False, xlim=(-L, L), ylim=(-L, L))
    ax.set_aspect('equal')
    ax.grid()

    line, = ax.plot([], [], 'o-', lw=1)
    trace, = ax.plot([], [], '.-', lw=1, ms=2)
    time_template = 'time = %.1fs'
    time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)
    history_x, history_y = [], []


    def animate(i):
        thisx = [0, L1 * np.sin(data[i, 0]), L1 * np.sin(data[i, 0]) + L2 * np.sin(data[i, 2])]
        thisy = [0, -L1 * np.cos(data[i, 0]), - L1 * np.cos(data[i, 0]) - L2 * np.cos(data[i, 2])]

        if i == 0:
            history_x.clear()
            history_y.clear()

        history_x.append(thisx[2])
        history_y.append(thisy[2])

        line.set_data(thisx, thisy)
        trace.set_data(history_x, history_y)
        time_text.set_text(time_template % (i * dt))
        return line, trace, time_text


    ani = FuncAnimation(
        fig, animate, len(t), interval=dt * 1000, blit=True)
    plt.show()

def visual_Kapitza_pendulum(ids):
    for file_id in ids:
        config = read_config(file_id)
        t = np.linspace(config['left'], config['right'], config['N'])
        data = read_data(file_id)

    L = config['L']
    A = config['A']
    nu = config['nu']
    dt = 2 * np.pi * (config['right'] - config['left']) / (config['N'] - 1)

    fig = plt.figure(figsize=(5, 4))
    ax = fig.add_subplot(autoscale_on=False, xlim=(-1.5*(L+A), 1.5*(L+A)), ylim=(-1.5*(L+A), 1.5*(L+A)))
    ax.set_aspect('equal')
    ax.grid()

    line, = ax.plot([], [], 'o-', lw=1)
    trace, = ax.plot([], [], '.-', lw=1, ms=2)
    time_template = 'time = %.1fs'
    time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)
    history_x, history_y = [], []


    def animate(i):
        thisx = [0, L * np.sin(data[i, 0])]
        thisy = [A * np.cos(nu * i * dt), A * np.cos(nu * i * dt) - L * np.cos(data[i, 0])]

        if i == 0:
            history_x.clear()
            history_y.clear()

        # history_x.append(thisx[2])
        # history_y.append(thisy[2])

        line.set_data(thisx, thisy)
        # trace.set_data(history_x, history_y)
        time_text.set_text(time_template % (i * dt))
        return line, trace, time_text


    ani = FuncAnimation(
        fig, animate, len(t), interval=dt * 1000, blit=True)
    plt.show()


def visual_AFC(ids):
    omega, A = [], []
    for file_id in ids:
        config = read_config(file_id)
        # first column should be - 'omega', second - 'amplitude'
        data = read_data(file_id)
        dt = 2 * np.pi * (config['right'] - config['left']) / (config['N'] - 1);
        N_tau = int(np.ceil(1 / config['GAMMA'] / dt))
        omega.append(config['BIG_OMEGA'])
        A.append(AFC(data, N_tau))

    plt.plot(omega, A)
    plt.show()
