# scheduler.py
import random
from collections import deque
from process import Process
import time

class CPUScheduler:
    def __init__(self):
        # Initialize multilevel queues (High, Low priority)
        self.queues = {1: deque(), 2: deque(), 3: deque()}  # Priority levels (1 = high, 3 = low)
        self.time_quantum = 4  # Time slice for Round Robin
        self.current_time = 0  # Simulation time

    def add_process(self, process):
        # Add process to the appropriate queue based on priority
        self.queues[process.priority].append(process)
        print(f"Time {self.current_time}: Process {process.process_id} arrived in Priority {process.priority} Queue.")

    def round_robin(self, queue):
        if queue:
            process = queue.popleft()
            if process.remaining_time > self.time_quantum:
                process.remaining_time -= self.time_quantum
                queue.append(process)  # Add process back to the queue
                print(f"Time {self.current_time}: Executing Process {process.process_id} from Priority {process.priority} Queue.")
            else:
                self.current_time += process.remaining_time
                process.remaining_time = 0
                print(f"Time {self.current_time}: Process {process.process_id} finished from Priority {process.priority} Queue.")
            return process
        return None

    def priority_scheduling(self, queue):
        if queue:
            process = min(queue, key=lambda p: p.priority)  # Process with highest priority
            queue.remove(process)
            self.current_time += process.burst_time
            print(f"Time {self.current_time}: Executing Process {process.process_id} from Priority {process.priority} Queue.")
            return process
        return None

    def fifo(self, queue):
        if queue:
            process = queue.popleft()
            self.current_time += process.burst_time
            print(f"Time {self.current_time}: Executing Process {process.process_id} from Priority {process.priority} Queue.")
            return process
        return None

    def schedule(self):
        # Scheduling processes from each queue based on the algorithm
        while any(self.queues.values()):  # Continue until all queues are empty
            for priority in sorted(self.queues.keys()):
                queue = self.queues[priority]
                if priority == 1:  # High priority queue - using Round Robin
                    process = self.round_robin(queue)
                elif priority == 2:  # Medium priority queue - using Priority Scheduling
                    process = self.priority_scheduling(queue)
                elif priority == 3:  # Low priority queue - using FIFO
                    process = self.fifo(queue)

                if process:
                    self.calculate_metrics(process)
                    if process.remaining_time == 0:
                        print(f"Time {self.current_time}: Process {process.process_id} finished.")
                    time.sleep(1)  # Simulate CPU time taken for process

    def calculate_metrics(self, process):
        # Calculate waiting time, turnaround time, and response time
        process.turnaround_time = self.current_time - process.arrival_time
        process.waiting_time = process.turnaround_time - process.burst_time
        if process.response_time is None:
            process.response_time = self.current_time - process.arrival_time

    def print_metrics(self, processes):
        # Output the performance metrics
        print("\n--- Performance Metrics ---")
        total_waiting_time = total_turnaround_time = total_response_time = 0
        for p in processes:
            print(f"PID: {p.process_id}, Arrival: {p.arrival_time}, Burst: {p.burst_time}, Wait: {p.waiting_time}, Turnaround: {p.turnaround_time}, Response: {p.response_time}")
            total_waiting_time += p.waiting_time
            total_turnaround_time += p.turnaround_time
            total_response_time += p.response_time

        n = len(processes)
        avg_waiting_time = total_waiting_time / n
        avg_turnaround_time = total_turnaround_time / n
        avg_response_time = total_response_time / n
        cpu_utilization = 100  # Assuming CPU is always utilized in the simulation
        throughput = n / self.current_time  # processes completed per unit time

        print(f"\nAverage Waiting Time: {avg_waiting_time:.2f}")
        print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
        print(f"Average Response Time: {avg_response_time:.2f}")
        print(f"CPU Utilization: {cpu_utilization:.2f}%")
        print(f"Throughput: {throughput:.2f} processes/unit time")
