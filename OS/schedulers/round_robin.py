				#!/usr/bin/python

in_file = open("input-rr.txt")

new_queue = []
ready_queue = []
running_process = {}
timer = 0
time_quanta = 1

new_queue = [
	{'PID': line.split()[0], 'arr_time': int(line.split()[1]), 'burst_time': int(line.split()[2])} for line in in_file.read().splitlines()
	]

for p in new_queue:
	print(p)

# RR
while len(new_queue) > 0 or len(ready_queue) > 0:
	if len(ready_queue) > 0:
		running_process = ready_queue[0]
		ready_queue.remove(running_process)
	else:
		for new in new_queue:
			if new['arr_time'] <= timer:
				ready_queue.append(new)
		for r in ready_queue:
			if r in new_queue:
				new_queue.remove(r)
		timer += 1

		continue

	timer += time_quanta
	running_process['burst_time'] -= time_quanta
	#print("{} : {}".format(running_process['PID'], running_process['burst_time']))
	if running_process['burst_time'] == 0:
		print("{} exited AT: {}, FT: {}".format(running_process['PID'], running_process['arr_time'], timer - 1))
	else:
		ready_queue.append(running_process)
