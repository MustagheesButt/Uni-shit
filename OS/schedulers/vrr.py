#!/usr/bin/python

in_file = open("input-rr.txt")

new_queue = []
ready_queue = []
waiting_queue = []
aux_queue = []
running_process = {}
timer = 0
time_quanta = 1

new_queue = [
	{'PID': line.split()[0], 'arr_time': int(line.split()[1]), 'burst_time': int(line.split()[2])} for line in in_file.read().splitlines()
	]

for p in new_queue:
	print(p)

# VRR
even = False
while len(new_queue) > 0 or len(ready_queue) > 0 or len(waiting_queue) > 0 or len(aux_queue) > 0:	
	# process auxillary queue
	for a in aux_queue:
		a['burst_time'] -= time_quanta # uses its remaining time quanta (which in this case is 100% of the time quanta)
		timer += time_quanta

		if a['burst_time'] == 0:
			print("{} exited from Aux queue. AT: {}, FT: {}".format(a['PID'], a['arr_time'], timer - 1))	
		else:
			ready_queue.append(a)
	
	# removing from aux queue
	aux_queue.clear()
		
	# ready queue
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

		# process waiting queue
		for w in waiting_queue:
			w['waiting_time'] -= 1
			if w['waiting_time'] <= 0:
				aux_queue.append(w)

		# remove processes from waiting_queue which were added to aux queue
		for a in aux_queue:
			if a in waiting_queue:
				waiting_queue.remove(a)

		continue

	# if even process, send into waiting for 2s
	if even:
		running_process['waiting_time'] = 2
		waiting_queue.append(running_process)
		even = False
		continue
	else:
		even = True

	timer += time_quanta
	running_process['burst_time'] -= time_quanta
	#print("{} : {}".format(running_process['PID'], running_process['burst_time']))
	if running_process['burst_time'] == 0:
		print("{} exited. AT: {}, FT: {}".format(running_process['PID'], running_process['arr_time'], timer - 1))
	else:
		ready_queue.append(running_process)
