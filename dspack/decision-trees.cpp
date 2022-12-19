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

// double partition_entropy_by(inputs, attribute)
// {
//     /* computes the entropy corresponding to the given partition */
//     partitions = partition_by(inputs, attribute) return partition_entropy(partitions.values())
// }

// double classify(tree, inputs)
// {
//     /* classify the input using the given decision tree */

//     // if this is a leaf node, return its value
//     if tree
//         in[True, False] : return tree

//                               // otherwise find the correct subtree
//                               attribute,
//                           subtree_dict = tree

//                               subtree_key = inputs.get(attribute) // None if input is missing attribute

//                                             if subtree_key not in subtree_dict :                    // if no subtree for key,
//                                                                                  subtree_key = None // we'll use the None subtree

//                                   subtree = subtree_dict[subtree_key] // choose the appropriate subtree
//                           return classify(subtree, inputs)            // and use it to classify the input
// }

// double build_tree_id3(inputs, split_candidates = None)
// {
//     // if this is our first pass,
//     // all keys of the first input are split candidates
//     if split_candidates is None:
//         split_candidates = inputs[0][0].keys()

//     // count Trues and Falses in the inputs
//     num_inputs = len(inputs)
//     num_trues = len([label for item, label in inputs if label])
//     num_falses = num_inputs - num_trues

//     if num_trues == 0:  // if only Falses are left
//         return False  // return a "False" leaf

//     if num_falses == 0:  // if only Trues are left
//         return True  // return a "True" leaf

//     if not split_candidates:  // if no split candidates left
//         return num_trues >= num_falses  // return the majority leaf

//     // otherwise, split on the best attribute
//     best_attribute = min(split_candidates, key=partial(partition_entropy_by, inputs))

//     partitions = partition_by(inputs, best_attribute)
//     new_candidates = [a for a in split_candidates if a != best_attribute]

//     // recursively build the subtrees
//     subtrees = {
//         attribute: build_tree_id3(subset, new_candidates)
//         for attribute, subset in partitions.items()
//     }

//     subtrees[None] = num_trues > num_falses  // default case

//     return best_attribute, subtrees
// }
// double forest_classify(trees, inputs)
// {
//     votes = [classify(tree, inputs) for tree in trees]
//     vote_counts = Counter(votes)
//     return vote_counts.most_common(1)[0][0]
// }
