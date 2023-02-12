#include "../include/node.hpp"

int Node::maxRight;
int Node::maxLeft;
int Node::goal;

void BFS() {
    // pointer to current Node
    Node* currNode;
    // queue maintained of Breadth First Search
    std::queue<Node> nodeList; 

    // Create root node, push to the nodeList, update visitedContainer
    Node root(0,0);
    nodeList.push(root);
    Node::visitedContainer.push_back(root.vessel);
    
    // to count number of visited Nodes
    int counter=1;

    // variable that is passed to getValidContainer by reference to a valid state
    Container container;
    std::vector<Container> pathToGoalState;

    // flag to check if we stopped after getting answer or not
    bool gotAns=false;

    //--------------------------- 
    //   Implementation of BSF
    //---------------------------
    while(!nodeList.empty()) {
        // get first element of nodeList
        currNode = &nodeList.front();
        // remove the currNode from nodelist queue
        nodeList.pop();
        counter++;
        // while there are Valid Container state, check if the state is goal state, else push to nodeList
        while(currNode->getValidContainer(container)) {
            // container is pass by refrence and now container a valid state
            // create newNode from that valid state
            Node newNode(container.left,container.right); 
            newNode.parent = currNode;

            // check if we reached the goal Node
            if(newNode.isTerminal()) {
                gotAns = true;
                currNode = &newNode;
                // backpropagation to store result in pathToGoalState
                while(currNode != NULL) {
                    pathToGoalState.push_back(Container(currNode->vessel.left,currNode->vessel.right));
                    currNode = currNode->parent;
                }
                break;
            }

            // push the node to nodelist queue and update the visitedContainer
            nodeList.push(newNode);
            Node::visitedContainer.push_back(container);
        }
        if(gotAns) {
            break;
        }
    }

    //------------------------------- 
    //  Printing of the path obtained 
    //-------------------------------

    if(gotAns) {
        std::cout << "\nBreadth First Search:" << std::endl;
        while(pathToGoalState.size() !=0) {
            Container container = pathToGoalState.back();
            pathToGoalState.pop_back();
            std::cout << "( "<<container.left << " , " << container.right << " )";
            if(pathToGoalState.size()==0) {
                std::cout << std::endl;
            }
            else {
                std::cout << " -> ";
            }
        }
        std::cout << "No. of visited Nodes : "<<counter<<std::endl;
    }
    else {
        std::cout << "No solution found"<<std::endl;
    }
}

void getInput() {
    int left, right, goal;
    std::cout << "\nEnter max capacity of left water jug:\n"<<">> ";
    std::cin >> left;
    std::cout << "\nEnter max capacity of left water jug:\n"<<">> ";
    std::cin >> right;
    std::cout << "\nEnter goal state of water jug of left vessel:\n"<<">> ";
    std::cin >> goal;
    Node::maxLeft = left;
    Node::maxRight = right;
    Node::goal = goal;
    BFS();
}

int main() {
    getInput();
    return 0;
}
