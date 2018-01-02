import pandas as pd
import numpy as np
import random

TIME, GYRO_X, GYRO_Y, GYRO_Z, ACC_X, ACC_Y, ACC_Z, ALT, STATE = range(9)
ALWAYS_PROCESS = 11111111111
TRUNCATE_LOW = 7428000.0
TRUNCATE_HIGH = 8500000.0
SIGMA = 1.5

# Use either a defined seed or a random seed
# SEED = 2017
SEED = random.randint(0, 1000000)
random.seed(SEED)

columns_ = ['Time', 'Gyro_x', 'Gyro_y', 'Gyro_z', 'Acc_x', 'Acc_y', 'Acc_z', 'Alt', 'State']
df_dict = {
    'Time': [],
    'Gyro_x': [],
    'Gyro_y': [],
    'Gyro_z': [],
    'Acc_x': [],
    'Acc_y': [],
    'Acc_z': [],
    'Alt': [],
    'State': []
}

def randomchoice():
    """Pseudo-randomly choose a piece of data to write as output"""
    result = None
    choice = random.randint(1, 7)
    if choice == 1:
        result = 'Gyro_x'
    elif choice == 2:
        result = 'Gyro_y'
    elif choice == 3:
        result = 'Gyro_z'
    elif choice == 4:
        result = 'Acc_x'
    elif choice == 5:
        result = 'Acc_y'
    elif choice == 6:
        result = 'Acc_z'
    elif choice == 7:
        result = 'Alt'

    return result


filename = r'./SRAD Raw Data.txt'
with open(filename, 'r') as raw_data:
    content = raw_data.readlines()
    flag = True
    for line in content:
        if(flag):
            line = line[:-3]
            line = line.replace(';', ',')
            words = line.split(',')
            flag = False
        else:
            line = line[:-3]
            words.append(line)
            df_dict['Time'].append(float(words[TIME]))
            df_dict['Gyro_x'].append(float(words[GYRO_X]))
            df_dict['Gyro_y'].append(float(words[GYRO_Y]))
            df_dict['Gyro_z'].append(float(words[GYRO_Z]))
            df_dict['Acc_x'].append(float(words[ACC_X]))
            df_dict['Acc_y'].append(float(words[ACC_Y]))
            df_dict['Acc_z'].append(float(words[ACC_Z]))
            df_dict['Alt'].append(float(words[ALT]))
            df_dict['State'].append((words[STATE]))
            flag = True

df = pd.DataFrame(df_dict)
df = df.set_index(['Time'])
df = df[df.index >= TRUNCATE_LOW]
df = df[df.index <= TRUNCATE_HIGH]

# Generate csv file, edit for more functionality
filename_mock_test = './mock_data_' + str(SEED)
with open(filename_mock_test + '.csv', 'w') as write_file:
    for index, row in df.iterrows():
        datapoint = randomchoice()
        write_file.write(datapoint.upper())
        write_file.write(', ')
        data = (random.gauss(row[datapoint], SIGMA))
        write_file.write(str(data))
        write_file.write('\n')