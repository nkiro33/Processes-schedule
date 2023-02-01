# Processes-schedule
schedule the processes by different algorthims
1. FCFS (First Come First Serve)
2. RR (Round Robin)
3. SPN (Shortest Process Next)
4. SRT (Shortest Remaining Time)
5. HRRN (Highest Response Ratio Next)
6. FB-1, (Feedback where all queues have q=1)
7. FB-2i, (Feedback where q= 2i)
8. Aging

Line1. “trace” or “stats”.
“trace” is used to ask the program to visualize the processes switching over the CPU .  You can see 01a-output.txt
as an example.
“stats” is used to ask the program to write some statistics on the scheduled processes . You can see 01b-output.txt
as an example.

Line2. a comma-separated list telling which CPU scheduling policies to be analyzed/visualized along with
their parameters, if applicable. Each algorithm is represented by a number as listed in the
introduction section .
Round Robin and Aging have a parameter specifying the quantum q to be used. Therefore, a policy
entered as 2-4 means Round Robin with q=4. Also, policy 8-1 means Aging with q=1.

Line3. An integer specifying the last instant to be used in your simulation and to be shown on the timeline.

Line4. An integer specifying the number of processes to be simulated. None of the processes is making a
blocking call.

Line5. Start of description of processes. Each process is to be described on a separate line. For algorithms
1 through 7, each process is described using a comma-separated list specifying:
- One character specifying a process name
- Arrival Time
- Service Time


some input and output examples are given.
