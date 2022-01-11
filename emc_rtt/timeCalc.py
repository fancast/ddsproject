read_file = open("rtt.txt", "r")
write_file = open("SimTimes.txt", "w")

time_list = []

for str_time in read_file:
    time_list.append(int(str_time))
read_file.close()

for pos in range(0,len(time_list)):
    write_file.write(time_list[time+1] - time_list[time])
write_file.close()