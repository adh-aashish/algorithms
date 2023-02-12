#pragma once
#include <iostream>
#include <queue>

// represents the left vessel and right vessel of the problem
struct Container {
    int left;
    int right;
    Container();
    Container(int _left, int _right);
};

class Node {
    public:
    Container vessel;
    Node(int _left,int _right);
    Node();
    Node* parent;
    static std::vector<Container> visitedContainer;
    static bool isUniqueContainerState(Container con);
    static int maxLeft;
    static int maxRight;
    static int goal;
    bool isTerminal();
    bool getValidContainer(Container& newState);
};
