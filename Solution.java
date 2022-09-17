
import java.util.Arrays;
import java.util.PriorityQueue;

public class Solution {

    private record Engineer(int speed, int efficiency) {}
    private static final int MODULO = (int) Math.pow(10, 9) + 7;

    public int maxPerformance(int numberOfEngineers, int[] speed, int[] efficiency, int maxNumberOfDifferentEngineersToSelect) {

        Engineer[] engineers = new Engineer[numberOfEngineers];
        for (int i = 0; i < numberOfEngineers; ++i) {
            engineers[i] = new Engineer(speed[i], efficiency[i]);
        }

        Arrays.sort(engineers, (x, y) -> y.efficiency - x.efficiency);
        PriorityQueue<Integer> minHeapSpeed = new PriorityQueue<>();

        long sumSpeed = 0;
        long maxPerformanceOfTeam = 0;
        int numberOfEnginnersInTeam = 0;

        for (Engineer engineer : engineers) {

            if (numberOfEnginnersInTeam++ == maxNumberOfDifferentEngineersToSelect) {
                sumSpeed -= minHeapSpeed.poll();
                --numberOfEnginnersInTeam;
            }

            minHeapSpeed.add(engineer.speed);
            sumSpeed += engineer.speed;
            maxPerformanceOfTeam = Math.max(maxPerformanceOfTeam, sumSpeed * engineer.efficiency);
        }

        return (int) (maxPerformanceOfTeam % MODULO);
    }
}
