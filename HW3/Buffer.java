import java.util.Arrays;

public class Buffer {


    private static final int MAX_SIZE = 1000;
    private double[] list = new double[MAX_SIZE];
    private int putIn = 0;
    private int takeOut = -1;
    private int elementsIn = 0;

    private boolean isFull() {
        return elementsIn == MAX_SIZE;
    }

    private boolean isEmpty() {
        return elementsIn == 0;
    }

    public synchronized void push(double bufferElement) {
        ///System.out.println(totalConsumed);

        if (isFull()) {
            try {

                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        elementsIn++;
        list[++takeOut % MAX_SIZE] = bufferElement;
        notifyAll();
    }

    public synchronized double pop() {

        if (isEmpty()) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        elementsIn--;
        notifyAll();
        return list[putIn++ % MAX_SIZE];
    }


    @Override
    public String toString() {

        return "Buffer{" +
                "{amount of Elements= " + elementsIn +
                ", bufferSize= " + MAX_SIZE +
                "\nBuffer: " + Arrays.toString(list) +
                '}' + '\n';


    }
}
