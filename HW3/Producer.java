import java.util.Random;

public class Producer extends Thread {

    private final Buffer buffer;
    private double count = 0;



    public Producer(Buffer buffer) {
        this.buffer = buffer;
    }

    @Override
    public void run() {
        for (int i = 1; i <= 1_000_000; ++i) {
            Random random = new Random();
            double el = random.nextDouble() * 100.0;
            buffer.push(el);
            count += el;
            if (i % 100_000 == 0) {
                System.out.printf("Producer: Generated %,d items, Cumulative value of generated  items=%.3f%n", i, count);

            }
        }
        System.out.println("Producer: Finished generating 1000000 items");

    }
}
