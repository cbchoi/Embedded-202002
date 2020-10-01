import random

dictionary = list('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ');
random.shuffle(dictionary);

'''
f = open("./large_file.bin", "w");
for i in range(500):
	random.shuffle(dictionary);
	f.write("".join(dictionary))

f.close()
'''

code_data = ['Ha', 'na', 'm ', 'Un', 'iv', 'er', 'si', 'ty'];
code_pos = [-1 for _ in code_data]
code = {}
for data, pos in zip(code_data, code_pos):
	code[data] = pos

with open("./large_file.bin", "r") as f:
	data = f.read()
	data = list(data)

	print(data[24609], data[24610])

	for i, ch in enumerate(data):
		if i < len(data)-1:
			for j in code_data:
				if j[0] == data[i] and j[1] == data[i+1]:
					code[j] = i
					print(j)


	for k, v in code.items():
		print(v)
