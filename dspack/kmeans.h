#include <vector>

class KMeans
{
    /* performs k-means clustering */
    KMeans(int k);
    int k;
    std::vector<std::vector<double>> means;
    int classify(std::vector<double> inputs);
    double train(std::vector<std::vector<double>> inputs);
}