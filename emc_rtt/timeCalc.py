fb_read_file = open("rtt_feedback.txt", "r")
fb_write_file = open("feedback_times.txt", "w")

fb_time_list = []

for str_time in fb_read_file:
    fb_time_list.append(int(str_time))
fb_read_file.close()

for pos in range(0,len(fb_time_list)-1):
    fb_write_file.write(str(fb_time_list[pos+1] - fb_time_list[pos]) + "\n")
fb_write_file.close()

cmd_read_file = open("rtt_command.txt", "r")
cmd_write_file = open("command_times.txt", "w")

cmd_time_list = []

for str_time in cmd_read_file:
    cmd_time_list.append(int(str_time))
cmd_read_file.close()

for pos in range(0,len(cmd_time_list)-1):
    cmd_write_file.write(str(cmd_time_list[pos+1] - cmd_time_list[pos]) + "\n")
cmd_write_file.close()