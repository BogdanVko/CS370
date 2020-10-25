public class Consumer extends Thread {


    private final Buffer buffer;
    private double count = 0.0;

    public Consumer(Buffer buffer) {
        this.buffer = buffer;
    }


    @Override
    public void run() {

        for (int i = 1; i <= 1_000_000; i++) {
            double el = buffer.pop();
            count += el;
            if (i % 100_000 == 0) {
                System.out.printf("Consumer: Consumed %,d items, Cumulative value of generated items=%.3f%n", i, count);

            }


        }
        System.out.println("Consumed: Finished generating 1000000 items");
    }
}