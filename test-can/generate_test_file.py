import pandas as pd
import numpy as np
import re
import random

TIME = 0
GYRO_X = 1
GYRO_Y = 2
GYRO_Z = 3
ACC_X = 4
ACC_Y = 5
ACC_Z = 6
ALT = 7
STATE = 8
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

filename = r'./SRAD Raw Data.txt'
with open(filename, 'r') as raw_file:
    content = raw_file.readlines()
    flag = True
    for line in content:
        if(flag):
            line = line[:-3]
            line = line.replace(';', ',')
            words = re.split(',', line)
            flag = not flag
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
            flag = not flag

df = pd.DataFrame(df_dict)
df = df.set_index('Time')
df = df[df.index >= TRUNCATE_LOW]
df = df[df.index <= TRUNCATE_HIGH]

# Generate csv file, edit for more functionality
filename_mock_test = './mock_data_' + str(SEED)
with open(filename_mock_test + '.csv', 'w') as write_file:
    for index, row in df.iterrows():
        write_file.write(str(ALT))
        write_file.write(', ')
        data = (random.gauss(row['Alt'], SIGMA))
        write_file.write(str(data))
        write_file.write('\n')

filename_args = './can_test_args.txt'
with open(filename_args, 'w') as write_file:
    write_file.write(filename_mock_test + '\n')
