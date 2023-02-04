import json
import numpy as np
import matplotlib.pylab as plt
from matplotlib.animation import FuncAnimation
import os

def read_config(file_id):
    config = dict()
    with open('configs/'+'config'+file_id+'.json', 'r') as inp:
        config = json.load(inp)

    return config

def read_data(file_id):
    data = np.loadtxt('data/'+'data'+file_id+'.txt')

    return data

def run_sim(ids):
    for config_id in ids:
        os.system("./main config"+config_id+".json > "+"data/data"+config_id+'.txt')

def AFC(data, N_tau, epsilon=0.05):
    max = data[:, 0].max()
    print(max)
    return max
