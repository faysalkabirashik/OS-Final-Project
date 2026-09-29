// Thread Representation


import java.util.Random;

public class Philosopher extends Thread {
    private int philosopherNumber;
    private DiningServer diningServer;
    private Random random;

    public Philosopher(int philosopherNumber, DiningServer diningServer) {
        this.philosopherNumber = philosopherNumber;
        this.diningServer = diningServer;
        this.random = new Random();
    }

    @Override
    public void run() {
        try {
            while (true) {
                think();
                eat();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void think() throws InterruptedException {
        System.out.println("Philosopher " + philosopherNumber + " is thinking.");
        Thread.sleep(random.nextInt(1000));
    }

    private void eat() throws InterruptedException {
        System.out.println("Philosopher " + philosopherNumber + " is hungry.");
        
        // Wait for chopsticks (mutex)
        diningServer.takeForks(philosopherNumber);
        System.out.println("Philosopher " + philosopherNumber + " is eating.");

        // Simulate eating time
        Thread.sleep(random.nextInt(1000));
        
        diningServer.returnForks(philosopherNumber);
        System.out.println("Philosopher " + philosopherNumber + " has finished eating.");
    }
}
