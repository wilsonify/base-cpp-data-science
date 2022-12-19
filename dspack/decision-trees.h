#include <cmath>
#include <vector>
#include <unordered_map>

double entropy(std::vector<double> class_probabilities);
std::vector<double> get_class_probabilities(std::vector<int> labels);
double partition_entropy(std::vector<std::vector<std::vector<double>>>);
std::unordered_map<double, std::vector<std::vector<double>>> partition_by(std::vector<std::vector<double>> inputs, int attribute);

// double data_entropy(labeled_data);
// double group_by(items, key_fn);
// double partition_entropy_by(inputs, attribute);
// double classify(tree, inputs);
// double build_tree_id3(inputs, split_candidates=None);
// double forest_classify(trees, inputs);
