/*
A decision tree uses a tree structure to represent a number of possible decision paths and an outcome for each path.
*/

#include <cmath>
#include <vector>
#include <unordered_map>
#include "linear-algebra.h"

double entropy(std::vector<double> class_probabilities)
{
    /* given a list of class probabilities, compute the entropy */
    double result = 0.0;
    double logp = 0.0;
    for (double p : class_probabilities)
    {
        logp = -std::log2(p);
        result = result + (p * logp);
    }

    return result;
}

std::vector<double> get_class_probabilities(std::vector<int> labels)
{
    auto total_count = double(labels.size());
    std::unordered_map<int, int> label_counter;
    for (int i = 0; i < total_count; i++)
    {
        label_counter[labels[i]]++;
    }

    std::vector<double> result;
    result.resize(label_counter.size());
    int i = 0;
    for (std::pair<const int, int> it : label_counter)
    {
        int count = it.second;
        result[i] = count / total_count;
        i++;
    }
    return result;
}

double data_entropy(std::vector<std::vector<double>> labeled_data)
{
    unsigned long label_index_ul = labeled_data.size() - 1;
    auto label_index_double = double(label_index_ul);
    std::vector<double> labels_double = get_column(labeled_data, label_index_double);
    std::vector<int> labels_int = double_to_int_vector(labels_double);
    std::vector<double> probabilities = get_class_probabilities(labels_int);
    double result = entropy(probabilities);
    return result;
}

double partition_entropy(std::vector<std::vector<std::vector<double>>> subsets)
{
    /* find the entropy from this partition of data into subsets */

    double total_count = 0.0;
    for (std::vector<std::vector<double>> subset : subsets)
    {
        total_count = total_count + double(subset.size());
    }
    double result = 0.0;
    for (std::vector<std::vector<double>> subset : subsets)
    {
        result = result + (data_entropy(subset) * double(subset.size()) / total_count);
    }

    return result;
}

std::unordered_map<double, std::vector<std::vector<double>>> partition_by(std::vector<std::vector<double>> inputs, int attribute)
{
    /*returns a dict of inputs partitioned by the attribute
    each input is a pair (attribute_dict, label)*/
    std::unordered_map<double, std::vector<std::vector<double>>> groups;
    double key;
    for (std::vector<double> item : inputs)
    {
        key = item[attribute];
        groups[key].push_back(item);
    }
    return groups;
}

double partition_entropy_by(std::vector<std::vector<double>> inputs, int attribute)
{
    /* computes the entropy corresponding to the given partition */
    std::unordered_map<double, std::vector<std::vector<double>>> partitions = partition_by(inputs, attribute);
    double result = 0.0;
    for (auto const &part : partitions)
    {
        result = result + data_entropy(part.second);
    }
    return result;
}
