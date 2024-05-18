from matplotlib import pyplot as plt

filename = "./data/average_time.data"

t = [] # time
x = [] # amount


with open(filename, "r") as file:
	for line in file:
		data = line.split(",")
		amount = float(data[0])
		time = float(data[1])

		t.append(time)
		x.append(amount)

plt.plot(x,t)
plt.show()

