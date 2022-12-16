
#include "kmeans.h"
#include "linear-algebra.h"
#include <iostream>

/* class KMeans: performs k-means clustering */

KMeans::KMeans(int k)
{
    this->k = k;      // number of clusters
    this->means = {}; // means of clusters
}

int KMeans::classify(std::vector<double> inputs)
{
    /* return the index of the cluster closest to the input */
    double smallest = 10000000;
    double squared_distance_input_to_mean = 10000000;
    int result = 0;
    for (int i = 0; i < this->k; i++)
    {
        squared_distance_input_to_mean = squared_distance(inputs, this->means[i]);
        if (squared_distance_input_to_mean < smallest)
        {
            smallest = squared_distance_input_to_mean;
            result = i;
        }
    }
    return result;
}

void KMeans::train(std::vector<std::vector<double>> inputs)
{
    this->means = {};
    std::vector<double> assignments = {};
    std::vector<double> new_assignments = {};
    int max_iter = 10000;
    for (int iteration = 0; iteration < max_iter; iteration++)
    {
        std::cout << "Find new assignments";
        for (int i = 0; i < inputs.size(); i++)
        {
            new_assignments[i] = this->classify(inputs[i]);
        }

        if (assignments == new_assignments)
        {
            std::cout << "no assignments have changed, we're done";
            break;
        }

        std::cout << "keep new assignments";
        assignments = new_assignments;

        for (int cluster = 0; cluster < this->k; cluster++)
        {
            std::vector<std::vector<double>> points_in_cluster = {};
            for (int j = 0; j < inputs.size(); j++)
            {
                auto p = inputs[j];
                auto a = assignments[j];
                if (a == cluster)
                {
                    points_in_cluster.push_back(p);
                }
                this->means[cluster] = vector_mean(points_in_cluster);
            }
        }
    }
}
