read_file = open("rtt.txt", "r")
write_file = open("times.txt", "w")

time_list = []

for str_time in read_file:
    time_list.append(int(str_time))
read_file.close()

for pos in range(0,len(time_list)-1):
    write_file.write(str(time_list[pos+1] - time_list[pos]))
write_file.close()