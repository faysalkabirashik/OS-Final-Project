# main.py
from process import Process
from scheduler import CPUScheduler
import random

def generate_random_processes(num_processes):
    processes = []
    for i in range(num_processes):
        arrival_time = random.randint(0, 5)
        burst_time = random.randint(1, 10)
        priority = random.randint(1, 3)  # Priority levels: 1 = High, 2 = Medium, 3 = Low
        process = Process(i + 1, arrival_time, burst_time, priority)
        processes.append(process)
    return processes

def main():
    scheduler = CPUScheduler()
    processes = generate_random_processes(5)  # Generate 5 random processes

    # Add processes to scheduler
    for process in processes:
        scheduler.add_process(process)

    # Start scheduling simulation
    print("\n--- CPU Scheduling Simulation ---")
    scheduler.schedule()

    # Print final performance metrics
    scheduler.print_metrics(processes)

if __name__ == "__main__":
    main()
