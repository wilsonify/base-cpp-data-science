#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <map>

class Table
{
public:
	std::vector<std::string> attrName;
	std::vector<std::vector<std::string>> data;

	std::vector<std::vector<std::string>> attrValueList;
	void extractAttrValue()
	{
		attrValueList.resize(attrName.size());
		for (int j = 0; j < attrName.size(); j++)
		{
			std::map<std::string, int> value;
			for (int i = 0; i < data.size(); i++)
			{
				value[data[i][j]] = 1;
			}

			for (auto iter = value.begin(); iter != value.end(); iter++)
			{
				attrValueList[j].push_back(iter->first);
			}
		}
	}
};

class Node
{
public:
	int criteriaAttrIndex;
	std::string attrValue;

	int treeIndex;
	bool isLeaf = false;
	std::string label;

	std::vector<int> children;

	Node() = default;
};

class DecisionTree
{
public:
	Table initialTable;
	std::vector<Node> tree;

	explicit DecisionTree(Table const& table)
	{
		initialTable = table;
		initialTable.extractAttrValue();

		Node root;
		root.treeIndex = 0;
		tree.push_back(root);
		run(initialTable, 0);
		printTree(0, "");

		std::cout << "<-- finish generating decision tree -->" << std::endl
				  << std::endl;
	}

	std::string guess(std::vector<std::string> row)
	{
		std::string label = "";
		int leafNode = dfs(row, 0);
		if (leafNode == -1)
		{
			return "dfs failed";
		}
		label = tree[leafNode].label;
		return label;
	}

	int dfs(std::vector<std::string> &row, int here)
	{
		if (tree[here].isLeaf)
		{
			return here;
		}

		int criteriaAttrIndex = tree[here].criteriaAttrIndex;

		for (int i = 0; i < tree[here].children.size(); i++)
		{
			int next = tree[here].children[i];

			if (row[criteriaAttrIndex] == tree[next].attrValue)
			{
				return dfs(row, next);
			}
		}
		return -1;
	}

	void run(Table table, int nodeIndex)
	{
		if (isLeafNode(table) == true)
		{
			tree[nodeIndex].isLeaf = true;
			tree[nodeIndex].label = table.data.back().back();
			return;
		}

		int selectedAttrIndex = getSelectedAttribute(table);

		std::map<std::string, std::vector<int>> attrValueMap;
		for (int i = 0; i < table.data.size(); i++)
		{
			attrValueMap[table.data[i][selectedAttrIndex]].push_back(i);
		}

		tree[nodeIndex].criteriaAttrIndex = selectedAttrIndex;

		std::pair<std::string, int> majority = getMajorityLabel(table);
		if (double(majority.second) / double(table.data.size()) > 0.8)
		{
			tree[nodeIndex].isLeaf = true;
			tree[nodeIndex].label = majority.first;
			return;
		}

		for (std::string attrValue : initialTable.attrValueList[selectedAttrIndex])
		{
			Table nextTable;
			std::vector<int> candi = attrValueMap[attrValue];
			for (int candi_j : candi)
			{
				nextTable.data.push_back(table.data[candi_j]);
			}

			Node nextNode;
			nextNode.attrValue = attrValue;
			nextNode.treeIndex = (int)tree.size();
			tree[nodeIndex].children.push_back(nextNode.treeIndex);
			tree.push_back(nextNode);

			// for empty table
			if (nextTable.data.empty())
			{
				nextNode.isLeaf = true;
				nextNode.label = getMajorityLabel(table).first;
				tree[nextNode.treeIndex] = nextNode;
			}
			else
			{
				run(nextTable, nextNode.treeIndex);
			}
		}
	}

	double getEstimatedError(double f, int N) const
	{
		double z = 0.69;
		if (N == 0)
		{
			std::cout << ":: getEstimatedError :: N is zero" << std::endl;
			exit(0);
		}
		return (f + z * z / (2 * N) + z * sqrt(f / N - f * f / N + z * z / (4 * N * N))) / (1 + z * z / N);
	}

	std::pair<std::string, int> getMajorityLabel(Table table) const
	{
		std::string majorLabel = "";
		int majorCount = 0;

		std::map<std::string, int> labelCount;
		for (int i = 0; i < table.data.size(); i++)
		{
			labelCount[table.data[i].back()]++;

			if (labelCount[table.data[i].back()] > majorCount)
			{
				majorCount = labelCount[table.data[i].back()];
				majorLabel = table.data[i].back();
			}
		}

		return {majorLabel, majorCount};
	}

	bool isLeafNode(Table table) const
	{
		for (int i = 1; i < table.data.size(); i++)
		{
			if (table.data[0].back() != table.data[i].back())
			{
				return false;
			}
		}
		return true;
	}

	int getSelectedAttribute(Table const& table) const
	{
		int maxAttrIndex = -1;
		double maxAttrValue = 0.0;

		// except label
		for (int i = 0; i < initialTable.attrName.size() - 1; i++)
		{
			if (maxAttrValue < getGainRatio(table, i))
			{
				maxAttrValue = getGainRatio(table, i);
				maxAttrIndex = i;
			}
		}

		return maxAttrIndex;
	}

	double getGainRatio(Table const& table, int attrIndex) const
	{
		return getGain(table, attrIndex) / getSplitInfoAttrD(table, attrIndex);
	}

	double getInfoD(Table table) const
	{
		double ret = 0.0;

		auto itemCount = (int)table.data.size();
		std::map<std::string, int> labelCount;

		for (int i = 0; i < table.data.size(); i++)
		{
			labelCount[table.data[i].back()]++;
		}

		for (auto iter = labelCount.begin(); iter != labelCount.end(); iter++)
		{
			double p = (double)iter->second / itemCount;

			ret += -1.0 * p * log(p) / log(2);
		}

		return ret;
	}

	double getInfoAttrD(Table table, int attrIndex) const
	{
		double ret = 0.0;
		auto itemCount = (int)table.data.size();

		std::map<std::string, std::vector<int>> attrValueMap;
		for (int i = 0; i < table.data.size(); i++)
		{
			attrValueMap[table.data[i][attrIndex]].push_back(i);
		}

		for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++)
		{
			Table nextTable;
			for (int i = 0; i < iter->second.size(); i++)
			{
				nextTable.data.push_back(table.data[iter->second[i]]);
			}
			auto nextItemCount = (int)nextTable.data.size();

			ret += (double)nextItemCount / itemCount * getInfoD(nextTable);
		}

		return ret;
	}

	double getGain(Table const& table, int attrIndex) const
	{
		return getInfoD(table) - getInfoAttrD(table, attrIndex);
	}

	double getSplitInfoAttrD(Table table, int attrIndex) const
	{
		double ret = 0.0;

		auto itemCount = (int)table.data.size();

		std::map<std::string, std::vector<int>> attrValueMap;
		for (int i = 0; i < table.data.size(); i++)
		{
			attrValueMap[table.data[i][attrIndex]].push_back(i);
		}

		for (auto iter = attrValueMap.begin(); iter != attrValueMap.end(); iter++)
		{
			Table nextTable;
			for (int i = 0; i < iter->second.size(); i++)
			{
				nextTable.data.push_back(table.data[iter->second[i]]);
			}
			auto nextItemCount = (int)nextTable.data.size();

			double d = (double)nextItemCount / itemCount;
			ret += -1.0 * d * log(d) / log(2);
		}

		return ret;
	}

	/*
	 * Enumerates through all the nodes of the tree and prints all the branches
	 */
	void printTree(int nodeIndex, std::string const& branch)
	{
		if (tree[nodeIndex].isLeaf == true)
			std::cout << branch << "Label: " << tree[nodeIndex].label << "\n";

		for (int childIndex : tree[nodeIndex].children)
		{
			std::string attributeName = initialTable.attrName[tree[nodeIndex].criteriaAttrIndex];
			std::string attributeValue = tree[childIndex].attrValue;
			printTree(childIndex, branch + attributeName + " = " + attributeValue + ", ");
		}
	}
};
