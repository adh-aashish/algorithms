#include "../include/node.hpp"

int Node::maxRight;
int Node::maxLeft;
int Node::goal;

std::vector<Container> Node::visitedContainer;

// check if the container state is already probed
bool Node::isUniqueContainerState(Container con) {
    for(const auto& node : Node::visitedContainer) {
        if(node.left == con.left && node.right == con.right) {
            return false;
        }
    }
    return true;
}

Container::Container(){
    left = 0;
    right = 0;
} 

Container::Container(int _left, int _right) {
    left = _left;
    right = _right;
}

Node::Node( int _left,int _right) {
    vessel.left = _left;
    vessel.right = _right;
    parent = NULL;
}

Node::Node(){
    vessel.left = 0;
    vessel.right = 0;
    parent = NULL;
}

// check if we got the goal state
bool Node::isTerminal() {
    if (this->vessel.left == goal) {
        return true;
    }
    return false;
}

// return a valid state of a container from the current state
bool Node::getValidContainer(Container& newState) {
    std::vector<Container>containerList;
    // empty action
    if(vessel.right!=0) {
        Container newState;
        newState.left = vessel.left;
        newState.right = 0;
        containerList.push_back(newState);
    }
    if(vessel.left!=0) {
        Container newState;
        newState.left = 0;
        newState.right = vessel.right;
        containerList.push_back(newState);
    }
    // transfer action
    // vessel.left -> right
    if (vessel.right < maxRight && vessel.left !=0) {
        Container newState;
        int newRight = (vessel.right + vessel.left);
        if(newRight > maxRight) {
            newRight = maxRight;
        }
        int newLeft =  vessel.left - std::abs(vessel.right - newRight);
        newState.left = newLeft;
        newState.right = newRight;
        // std::cout << newState.left << " , "<< newState.right<<std::endl;
        containerList.push_back(newState);
    }
    // right -> vessel.left
    if (vessel.left < maxLeft && vessel.right!=0) {
        Container newState;
        int newLeft = (vessel.right + vessel.left);
        if (newLeft > maxLeft) {
            newLeft = maxLeft;
        }
        int newRight =  vessel.right - std::abs(vessel.left - newLeft);
        newState.left = newLeft;
        newState.right = newRight;
        // std::cout << newState.left << " , "<< newState.right<<std::endl;
        containerList.push_back(newState);
    }
    // fill action
    if(vessel.left!=maxLeft) {
        Container newState;
        newState.left = maxLeft;
        newState.right = vessel.right;
        containerList.push_back(newState);
    }
    if(vessel.right!=maxRight) {
        Container newState;
        newState.left = vessel.left;
        newState.right = maxRight;
        containerList.push_back(newState);
    }
    for (auto& container : containerList) {
        if(Node::isUniqueContainerState(container)) {
            newState.left = container.left;
            newState.right = container.right;
            return true;
        }
    }
    return false;
}
