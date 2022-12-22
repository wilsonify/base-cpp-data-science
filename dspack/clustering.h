#include <cassert>
#include "linear-algebra.h"
#include "kmeans.h"

double squared_clustering_errors(std::vector<std::vector<double>> inputs, int k);
bool is_leaf(std::vector<std::vector<double>> cluster_);
std::vector<std::vector<double>> get_children(std::vector<std::vector<double>> cluster_);
// std::vector<std::vector<double>> get_values(std::vector<std::vector<double>> cluster_);
// double cluster_distance(cluster1, cluster2, distance_agg = min);
// double bottom_up_cluster(inputs, distance_agg = min);
// double generate_clusters(base_cluster, num_clusters);