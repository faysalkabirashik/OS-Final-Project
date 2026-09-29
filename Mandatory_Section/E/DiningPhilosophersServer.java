import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class DiningPhilosophersServer implements DiningServer {
    private final Lock[] chopsticks;
    
    public DiningPhilosophersServer(int numPhilosophers) {
        chopsticks = new Lock[numPhilosophers];
        for (int i = 0; i < numPhilosophers; i++) {
            chopsticks[i] = new ReentrantLock();
        }
    }

    @Override
    public void takeForks(int philosopherNumber) {
        int left = philosopherNumber;
        int right = (philosopherNumber + 1) % chopsticks.length;

        // To avoid deadlock, one philosopher will always pick up the left fork first
        if (left < right) {
            chopsticks[left].lock();
            chopsticks[right].lock();
        } else {
            chopsticks[right].lock();
            chopsticks[left].lock();
        }
    }

    @Override
    public void returnForks(int philosopherNumber) {
        int left = philosopherNumber;
        int right = (philosopherNumber + 1) % chopsticks.length;
        
        chopsticks[left].unlock();
        chopsticks[right].unlock();
    }
}
