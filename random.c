import random

def fcfs_simulation(arrival_time, burst_time):
  n = len(arrival_time)
  completion_time = [0] * n
  turnaround_time = [0] * n
  waiting_time = [0] * n

  for i in range(n):
  if i == 0:
  completion_time[i] = arrival_time[i] + burst_time[i]
  else:
  completion_time[i] = max(arrival_time[i], completion_time[i-1]) + burst_time[i] + 2

  turnaround_time[i] = completion_time[i] - arrival_time[i]
  waiting_time[i] = turnaround_time[i] - burst_time[i]

  avg_turnaround_time = sum(turnaround_time) / n
  avg_waiting_time = sum(waiting_time) / n


  gantt_chart = ""
  for i in range(n):
  gantt_chart += f"| P{i+1} "

  
  print("Gantt Chart:")
  print(gantt_chart)
  print("\nTurnaround Time:")
  print(turnaround_time)
  print("\nWaiting Time:")
  print(waiting_time)
  print("\nAverage Turnaround Time:", avg_turnaround_time)
  print("Average Waiting Time:", avg_waiting_time)

arrival_time = [0, 2, 4]
burst_time = [5, 3, 2]
fcfs_simulation(arrival_time, burst_time)
