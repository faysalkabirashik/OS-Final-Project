public class DiningPhilosophers {
    public static void main(String[] args) {
        int numPhilosophers = 5; // Number of philosophers
        DiningServer server = new DiningPhilosophersServer(numPhilosophers);

        // Create philosopher threads
        Thread[] philosophers = new Thread[numPhilosophers];
        for (int i = 0; i < numPhilosophers; i++) {
            philosophers[i] = new Philosopher(i, server);
        }

        // Start philosopher threads
        for (int i = 0; i < numPhilosophers; i++) {
            philosophers[i].start();
        }

        // Wait for all philosophers to finish (optional)
        for (int i = 0; i < numPhilosophers; i++) {
            try {
                philosophers[i].join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}
