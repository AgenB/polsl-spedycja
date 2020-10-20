#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
using namespace std;

struct node {
    string name;
    vector<array<int, 2>> connections; //first element is distance, second is destination node
};

int findNode(vector<node> &nodeVec, string &name) {
    int nodeVecSize = nodeVec.size();
    for (int i = 0; i < nodeVecSize; i++) {
        if (nodeVec[i].name == name) return i;
    }
    return nodeVecSize;
}

int main(int argc, char **argv) {
    vector<node> nodeVec;
    ifstream inputFile("input.txt");
    string line;
    while (getline(inputFile, line)) {
        int currPos = 0, breakPos, dist, node1Pos, node2Pos;
        string name1, name2;

        breakPos = line.find(' ', currPos);
        name1 = line.substr(currPos, breakPos - currPos);
        currPos = breakPos + 1;
        breakPos = line.find(' ', currPos);
        name2 = line.substr(currPos, breakPos - currPos);
        currPos = breakPos + 1;
        dist = stoi(line.substr(currPos));

        node1Pos = findNode(nodeVec, name1);
        if (node1Pos == nodeVec.size()) {
            vector<array<int, 2>> conn;
            node node = {name1, conn};
            nodeVec.push_back(node);
        }
        node2Pos = findNode(nodeVec, name2);
        if (node2Pos == nodeVec.size()) {
            vector<array<int, 2>> conn;
            node node = {name2, conn};
            nodeVec.push_back(node);
        }
        nodeVec[node1Pos].connections.push_back({dist, node2Pos});
        nodeVec[node2Pos].connections.push_back({dist, node1Pos});
    }
    inputFile.close();
    return 0;
}