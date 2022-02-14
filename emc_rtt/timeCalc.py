import matplotlib.pyplot as plt

fb_read_file = open("rtt_feedback.txt", "r")
fb_write_file = open("feedback_times.txt", "w")

fb_time_list = []
fb_calc_time = []

for str_time in fb_read_file:
    fb_time_list.append(int(str_time))
fb_read_file.close()

for pos in range(0,len(fb_time_list)-1):
    fb_calc_time.append(fb_time_list[pos+1] - fb_time_list[pos])
    fb_write_file.write(str(fb_calc_time[pos]) + "\n")
fb_write_file.close()

#fig, axs = plt.subplots(1,1)
plt.style.use('ggplot')
plt.hist(fb_calc_time, bins=100)
plt.show()