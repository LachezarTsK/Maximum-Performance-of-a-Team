
#include <queue>
#include <vector>
using namespace std;

class Solution {

    struct Engineer {
        int speed;
  	int efficiency;
	Engineer(int speed, int efficiency) :speed{ speed }, efficiency{ efficiency } {}
    };

    inline static const int MODULO = pow(10, 9) + 7;

public:
    int maxPerformance(int numberOfEngineers, vector<int>& speed, vector<int>& efficiency, int maxNumberOfDifferentEngineersToSelect) {

        vector<Engineer> engineers;
        engineers.reserve(numberOfEngineers);
        for (int i = 0; i < numberOfEngineers; ++i) {
            engineers.push_back(Engineer(speed[i], efficiency[i]));
        }

        static const auto maxEfficiencyOnTop = [](const Engineer& x, const Engineer & y) {return x.efficiency > y.efficiency;};

        //C++20: std::ranges::sort(engineers, maxEfficiencyOnTop);
        sort(engineers.begin(), engineers.end(), maxEfficiencyOnTop);


        /*
        greater<> instead of greater<int>:
        it’s recommended to always use a transparent operator for Standard Library containers 
        that accept a comparator type.
         */
        priority_queue<int, vector<int>, greater<>> minHeapSpeed;

        long long sumSpeed = 0;
        long long maxPerformanceOfTeam = 0;
        int numberOfEnginnersInTeam = 0;

        for (const auto& engineer : engineers) {

            if (numberOfEnginnersInTeam++ == maxNumberOfDifferentEngineersToSelect) {
                sumSpeed -= minHeapSpeed.top();
                minHeapSpeed.pop();
                --numberOfEnginnersInTeam;
            }

            minHeapSpeed.push(engineer.speed);
            sumSpeed += engineer.speed;
            maxPerformanceOfTeam = max(maxPerformanceOfTeam, sumSpeed * engineer.efficiency);
        }

        return maxPerformanceOfTeam % MODULO;
    }
};
