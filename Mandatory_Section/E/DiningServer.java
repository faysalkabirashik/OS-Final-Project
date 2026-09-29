public interface DiningServer {
    /* Called by a philosopher when they wish to eat */
    public void takeForks(int philosopherNumber);
    
    /* Called by a philosopher when they finish eating */
    public void returnForks(int philosopherNumber);
}
