
#include "kmeans.h"
#include "linear-algebra.h"

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

double KMeans::train(std::vector<std::vector<double>> inputs)
{
    this->means = random.sample(inputs, this->k);
    std::vector<double> assignments = {};
    std::vector<double> new_assignments = {};
    while (1)
    {
        // Find new assignments
        for (int i = 0; i < inputs.size(); i++)
        {
            new_assignments[i] = this->classify(inputs[i])
        }

        // If no assignments have changed, we're done.
        if (assignments == new_assignments)
        {
            break;
        }

        // Otherwise keep the new assignments,
        assignments = new_assignments;

        for (int i = 0; i < this->k; i++)
        {

            // i_points = [p for p, a in zip(inputs, assignments) if a == i]
            // this->means[i] = vector_mean(i_points)
        }
    }
}
