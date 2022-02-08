import matplotlib.pyplot as plt

fb_read_file = open("rtt_feedback.txt", "r")
fb_write_file = open("feedback_times.txt", "w")

fb_time_list = []
fb_calc_time = []

for str_time in fb_read_file:
    fb_time_list.append(int(str_time))
fb_read_file.close()

for pos in range(0,len(fb_time_list)-1):
    fb_calc_time[pos] = fb_time_list[pos+1] - fb_time_list[pos]
    fb_write_file.write(str(fb_calc_time[pos]) + "\n")
fb_write_file.close()

cmd_read_file = open("rtt_command.txt", "r")
cmd_write_file = open("command_times.txt", "w")

cmd_time_list = []
cmd_calc_time = []

for str_time in cmd_read_file:
    cmd_time_list.append(int(str_time))
cmd_read_file.close()

for pos in range(0,len(cmd_time_list)-1):
    cmd_calc_time[pos] = cmd_time_list[pos+1] - cmd_time_list[pos]
    cmd_write_file.write(str(cmd_calc_time[pos]) + "\n")
cmd_write_file.close()

fig, axs = plt.subplots(1,1)
axs.hist(fb_calc_time, bins=20)
plt.show()