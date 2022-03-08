import matplotlib.pyplot as plt
import numpy as np

cmd_read_file = open("rtt_command.txt", "r")
cmd_write_file = open("command_times.txt", "w")

cmd_time_list = []
cmd_calc_time = []

for str_time in cmd_read_file:
    cmd_time_list.append(int(str_time))
cmd_read_file.close()

for pos in range(0,len(cmd_time_list)-1):
    cmd_calc_time.append(((cmd_time_list[pos+1] - cmd_time_list[pos])/1000))
    #cmd_write_file.write(str(cmd_calc_time[pos]) + "\n")

# Get 99 percent of values
cmd_calc_time.sort()
for pos in range(0,int(0.01*len(cmd_calc_time))-1):
    cmd_calc_time.pop()

for pos in range(0,len(cmd_calc_time)-1):
    cmd_write_file.write(str(cmd_calc_time[pos]) + "\n")
cmd_write_file.close()

avg_time = np.mean(cmd_calc_time)
sd_times = np.std(cmd_calc_time)
print("Total Trips: " + str(len(cmd_calc_time)))
print("Average round trip time: " + str(avg_time) + " ms")
print("Standard Deviation: " + str(sd_times))

plt.style.use('ggplot')
#plt.hist(cmd_calc_time, bins=np.logspace(start=np.log10(10), stop=np.log10(15), num=10))
plt.hist(cmd_calc_time, bins=20)
#plt.gca().set_xscale("log")
plt.xlabel("Round Trip Time (ms)")
plt.ylabel("Trip Count")
plt.title("Round Trip Time Histogram for DDS")
plt.show()