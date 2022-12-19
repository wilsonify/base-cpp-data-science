#include <cassert>
#include "linear-algebra.h"
#include "kmeans.h"

double squared_clustering_errors(std::vector<std::vector<double>> inputs, int k)
{
    /* finds the total squared error from k-means clustering the inputs */
    auto clusterer = KMeans(k);
    clusterer.train(inputs);
    std::vector<double> assignments = {};
    for (int i = 0; i < inputs.size(); i++)
    {
        assignments[i] = clusterer.classify(inputs[i]);
    }

    double result = 0.0;
    for (int i = 0; i < inputs.size(); i++)
    {
        auto assigned_cluster = int(assignments[i]);
        result = result + squared_distance(inputs[i], clusterer.means[assigned_cluster]);
    }
    return result;
}

bool is_leaf(std::vector<std::vector<double>> cluster_)
{
    /* a cluster is a leaf if it has length 1 */
    return cluster_.size() == 1;
}

// std::vector<std::vector<double>> get_children(std::vector<std::vector<double>> cluster_)
// {
//     /*
//     returns the two children of this cluster if it's a merged cluster;
//     raises an exception if this is a leaf cluster
//     */
//     assert(!is_leaf(cluster_));
//     return {cluster_[1]};
// }

// std::vector<double> get_values(std::vector<double> cluster_)
// {
//     /*
//     returns the value in this cluster (if it's a leaf cluster)
//     or all the values in the leaf clusters below it (if it's not)
//     */
//     std::vector<std::vector<double>> result;
//     if (is_leaf({cluster_}))
//     {
//         return cluster_; // is already a 1-tuple containing value
//     }

//     for (std::vector<double> child : get_children({cluster_}))
//     {
//         auto values = get_values(child);
//         for (auto value : values)
//         {
//             result.push_back(value);
//         }
//     }

//     return result;
// }

// double cluster_distance(cluster1, cluster2, distance_agg = min)
// {
//     /*finds the aggregate distance between elements of cluster1
//     and elements of cluster2*/
//     return distance_agg(
//         [
//             distance(input1, input2)
//             for input1 in get_values(cluster1)
//             for input2 in get_values(cluster2)
//         ]
//     )
// }

// double get_merge_order(cluster_)
// {
//     if is_leaf (cluster_):
//         return float("inf")
//     else:
//         return cluster_[0]  // merge_order is first element of 2-tuple
// }

// double bottom_up_cluster(inputs, distance_agg = min)
// {
//     // start with every in_put a leaf cluster / 1-tuple
//     clusters = [(in_put,) for in_put in inputs]

//     // as long as we have more than one cluster left...
//     while len(clusters) > 1:
//         // find the two closest clusters
//         c1, c2 = min(
//             [
//                 (cluster1, cluster2)
//                 for i, cluster1 in enumerate(clusters)
//                 for cluster2 in clusters[:i]
//             ],
//             key=lambda p: cluster_distance(p[0], p[1], distance_agg),
//         )

//         // remove them from the list of clusters
//         clusters = [c for c in clusters if c != c1 and c != c2]

//         // merge them, using merge_order = // of clusters left
//         merged_cluster = (len(clusters), [c1, c2])

//         // and add their merge
//         clusters.append(merged_cluster)

//     // when there's only one cluster left, return it
//     return clusters[0]
// }

// double generate_clusters(base_cluster, num_clusters)
// {
//     // start with a list with just the base cluster
//     clusters = [base_cluster]

//     // as long as we don't have enough clusters yet...
//     while len(clusters) < num_clusters:
//         // choose the last-merged of our clusters
//         next_cluster = min(clusters, key=get_merge_order)
//         // remove it from the list
//         clusters = [c for c in clusters if c != next_cluster]
//         // and add its children to the list (i.e., unmerge it)
//         clusters.extend(get_children(next_cluster))

//     // once we have enough clusters...
//     return clusters
// }