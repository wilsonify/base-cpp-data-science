#include <vector>

class KMeans
{
    /* performs k-means clustering */

private:
    int k;

public:
    KMeans(int k);
    std::vector<std::vector<double>> means;
    int classify(std::vector<double> inputs);
    void train(std::vector<std::vector<double>> inputs);
};