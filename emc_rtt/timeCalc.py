import matplotlib.pyplot as plt
import numpy as np

fb_read_file = open("rtt_feedback.txt", "r")
fb_write_file = open("feedback_times.txt", "w")
write_file_numbered = open("numbered_times.txt", "w")

fb_time_list = []
fb_calc_time = []
bins = []

for str_time in fb_read_file:
    fb_time_list.append(int(str_time))
fb_read_file.close()

for pos in range(0,len(fb_time_list)-1):
    fb_calc_time.append(((fb_time_list[pos+1] - fb_time_list[pos])/1000))
    write_file_numbered.write(str(pos) + ": " + str(fb_calc_time[pos]) + "\n")
    if fb_calc_time[pos] > 50:
        print(str(pos) + " " + str(fb_calc_time[pos]))
    #fb_write_file.write(str(fb_calc_time[pos]) + "\n")

# Get 99 percent of values
fb_calc_time.sort()
for pos in range(0,int(0.01*len(fb_calc_time))-1):
    fb_calc_time.pop()

for pos in range(0,len(fb_calc_time)-1):
    fb_write_file.write(str(fb_calc_time[pos]) + "\n")
fb_write_file.close()

avg_time = np.mean(fb_calc_time)
sd_times = np.std(fb_calc_time)
print("Total Trips: " + str(len(fb_calc_time)))
print("Average round trip time: " + str(avg_time) + " ms")
print("Standard Deviation: " + str(sd_times))

for x in np.arange(0,0.75, 0.025):
    bins.append(x)

plt.style.use('ggplot')
#plt.hist(fb_calc_time, bins=np.logspace(start=np.log10(10), stop=np.log10(15), num=10))
plt.hist(fb_calc_time, bins=bins)
#plt.gca().set_xscale("log")
plt.xlabel("Round Trip Time (ms)")
plt.ylabel("Trip Count")
plt.title("Round Trip Time Histogram for DDS")
plt.show()