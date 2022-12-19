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
	void extractAttrValue();
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

	explicit DecisionTree(Table const& table);

	std::string guess(std::vector<std::string> row);

	int dfs(std::vector<std::string> &row, int here);

	void run(Table table, int nodeIndex);

	double getEstimatedError(double f, int N) const;

	std::pair<std::string, int> getMajorityLabel(Table table) const;

	bool isLeafNode(Table table) const;

	int getSelectedAttribute(Table const& table) const;

	double getGainRatio(Table const& table, int attrIndex) const;

	double getInfoD(Table table) const;

	double getInfoAttrD(Table table, int attrIndex) const;

	double getGain(Table const& table, int attrIndex) const;

	double getSplitInfoAttrD(Table table, int attrIndex) const;

	void printTree(int nodeIndex, std::string const& branch);
};
