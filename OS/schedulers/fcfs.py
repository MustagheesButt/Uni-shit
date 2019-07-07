#!/usr/bin/python

# input format: PID, Arrival time, Burst time
in_file = open("input-fcfs.txt")

new_queue = []
ready_queue = []
running_process = {}
timer = 0

# Note:
# `in_file.read().splitline()` will return a list of lines without \n
# using in_file object directly will include \n in the last value
new_queue = [
    {'PID': line.split(' ')[0], 'arr_time': int(line.split(' ')[1]), 'burst_time': int(line.split(' ')[2])}
    for line in in_file.read().splitlines()
    ]

for process in new_queue:
    print(process)

# FCFS
while len(new_queue) > 0 or len(ready_queue) > 0:
    # select process to run, if any
    if len(ready_queue) > 0:
        running_process = ready_queue[0]
    else:
        # check if any new processes have arrived
        for new in new_queue:
            if new['arr_time'] <= timer:
                ready_queue.append(new)
        
        # remove from new_queue those which were added to ready
        for r in ready_queue:
            if r in new_queue:
                new_queue.remove(r)

        timer += 1

        continue

    i = 0
    while i < running_process['burst_time']:
        timer += 1

        # update ready queue
        for new in new_queue:
            if new['arr_time'] <= timer:
                ready_queue.append(new)
        
        # remove from new_queue those which were added to ready
        for r in ready_queue:
            if r in new_queue:
                new_queue.remove(r)
        i += 1

    print("PID: {}, AT: {}, FT: {}".format(running_process['PID'], running_process['arr_time'], timer - 1))
    ready_queue.remove(running_process)
