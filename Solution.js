
/**
 * @param {number} numberOfEngineers
 * @param {number[]} speed
 * @param {number[]} efficiency
 * @param {number} maxNumberOfDifferentEngineersToSelect
 * @return {number}
 */
var maxPerformance = function (numberOfEngineers, speed, efficiency, maxNumberOfDifferentEngineersToSelect) {
    const {PriorityQueue} = require('@datastructures-js/priority-queue');
    const MODULO = Math.pow(10, 9) + 7;

    const engineers = new Array(numberOfEngineers);
    for (let i = 0; i < numberOfEngineers; ++i) {
        engineers[i] = new Engineer(speed[i], efficiency[i]);
    }

    engineers.sort((x, y) => y.efficiency - x.efficiency);
    const minHeapSpeed = new MinPriorityQueue({compare: (x, y) => x - y});

    let sumSpeed = BigInt(0);
    let maxPerformanceOfTeam = BigInt(0);
    let numberOfEnginnersInTeam = 0;


    for (let engineer of engineers) {

        if (numberOfEnginnersInTeam++ === maxNumberOfDifferentEngineersToSelect) {
            sumSpeed -= BigInt(minHeapSpeed.dequeue());
            --numberOfEnginnersInTeam;
        }

        minHeapSpeed.enqueue(engineer.speed);
        sumSpeed += BigInt(engineer.speed);
        let currentPerformanceOfTeam = sumSpeed * BigInt(engineer.efficiency);

        if (maxPerformanceOfTeam < currentPerformanceOfTeam) {
            maxPerformanceOfTeam = currentPerformanceOfTeam;
        }
    }

    return maxPerformanceOfTeam % BigInt(MODULO);
};

/**
 * @param {number} speed
 * @param {number} efficiency
 */
function Engineer(speed, efficiency) {
    this.speed = speed;
    this.efficiency = efficiency;
}
