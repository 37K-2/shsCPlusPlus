#include <cstring>
#include <iostream>
#include <iomanip>

#include "graph.h"
#include "types.h"

using namespace std;

// commands
const char commandAdd[] = "ADD";
const char commandRemove[] = "REMOVE";
const char operandNode[] = "NODE";
const char operandEdge[] = "EDGE";
const char cmdMatrix[] = "MATRIX";
const char cmdShortest[] = "SHORTEST";
const char operandAll[] = "ALL";
const char operandOne[] = "ONE";
const char commandQuit[] = "QUIT";

int main() {
    graph* graph_ = new graph();

    cout << fixed << setprecision(1); // round to decimal
    cout << "Graph Creator" << endl;

    while (true) {
        cout << "ADD, REMOVE, MATRIX, SHORTEST, or QUIT" << endl;
        cout << "--------------------------------------" << endl;
        cout << " > ";//get commands from user
        char commandInput[9]; 
        cin >> commandInput;
        
        if (strcmp(commandInput, commandAdd) == 0) { //add node to graph
            cout << "NODE or EDGE: ";
            char optionInput[5];
            cin >> optionInput; //take input
            
            if (strcmp(optionInput, operandNode) == 0) {
                if (graph_->isFull()) { // if graph is full then can't add more
                    cout << "The graph is full (20 nodes)." << endl;
                    continue;
                }
                node* node_ = new node();
                cout << "Enter a node label (2 chars max): ";
                char label[2];
                for (int i = 0; i < 2; i++)
                    label[i] = '\0';
                cin >> label;
                strncpy(node_->label, label, 2); // new node will get a label > than 2 characters if this is not here

                if (!graph_->add(node_)) {
                    cout << "A node labeled \"" << node_->label << "\" already exists." << endl; // label already exists
                    delete node_;
                } else
                    cout << "Added a node labeled \"" << node_->label << "\"" << endl; //added label
            }
            if (strcmp(optionInput, operandEdge) == 0) {
                edge* edge_ = new edge();

                cout << "Enter the first node's label (2 chars max): ";
                char firstLabel[3];
                cin >> firstLabel;

                cout << "Enter the second node's label: ";
                char secondLabel[3];
                cin >> secondLabel;

                cout << "Enter the edge's weight (decimals allowed): ";
                cin >> edge_->weight;

                if (strcmp(firstLabel, secondLabel) == 0) {
                    cout << "Both labels can't be the same." << endl << endl;
                    continue;
                }

                node* first = graph_->find(firstLabel); //attempt to find the nodes
                node* second = graph_->find(secondLabel);
                if (first == nullptr) {
                    cout << "A node labeled \"" << firstLabel << "\" wasn't found." << endl << endl; // 1 isnt found
                    continue;
                }
                if (second == nullptr) {
                    cout << "A node labeled \"" << secondLabel << "\" wasn't found." << endl << endl; // 2 isnt found
                    continue;
                }
                if (strcmp(first->label, second->label) == 0) { //probably wont ever happen lmfao
                    cout << "Both labels can't be the same." << endl << endl;
                    continue;
                }
                edge* firstToSecond = first->getConnectionTo(second); //connection
                edge* secondToFirst = second->getConnectionTo(first);
                if (firstToSecond != nullptr) { //check if 1 is already connected to 2
                    cout << "The node \"" << first->label << "\" (a) is already connected to  \"" << second->label << "\" (b), delete that edge first.   (a->b)." << endl << endl;
                    continue;
                }
                if (secondToFirst != nullptr) { //vice versa from ^
                    cout << "The node \"" << second->label << "\" (a) is already connected to  \"" << first->label << "\" (b), delete that edge first.   (b->a)." << endl << endl;
                    continue;
                }

                edge_->start = first;
                edge_->end = second;

                first->connections.push_back(edge_); //edge
                cout << "Added an edge with weight " << edge_->weight << " between nodes \"" << first->label << "\" and \"" << second->label << "\"." << endl;
            }
        }
        if (strcmp(commandInput, commandRemove) == 0) { //remove node
            cout << "NODE or EDGE: ";
            char optionInput[5];
            cin >> optionInput;

            if (strcmp(optionInput, operandNode) == 0) {
                cout << "Enter a node label to remove (2 chars max): ";
                char lb[2];
                cin >> lb;
                if (!graph_->remove(lb))
                    cout << "A node labeled \"" << lb << "\" could not be found." << endl; // cannot find node in graph
                else
                    cout << "Removed the node \"" << lb << "\" from the graph." << endl; //removed node
            }
            if (strcmp(optionInput, operandEdge) == 0) { // edge
                cout << "Enter the first node's label (2 chars max): ";
                char firstLabel[2];
                cin >> firstLabel;

                cout << "Enter the second node's label (2 chars max): ";
                char secondLabel[2];
                cin >> secondLabel;

                if (strcmp(firstLabel, secondLabel) == 0) {
                    cout << "Both labels can't be the same." << endl
                         << endl;
                    continue;
                }

                node* first = graph_->find(firstLabel);
                node* second = graph_->find(secondLabel);
                if (first == nullptr) {
                    cout << "A node labeled \"" << firstLabel << "\" wasn't found." << endl
                         << endl;
                    continue;
                }
                if (second == nullptr) {
                    cout << "A node labeled \"" << secondLabel << "\" wasn't found." << endl
                         << endl;
                    continue;
                }
                if (strcmp(first->label, second->label) == 0) { // probably shouldnt happen
                    cout << "Both labels can't be the same." << endl
                         << endl;
                    continue;
                }
                edge* firstToSecond = first->getConnectionTo(second);
                edge* secondToFirst = second->getConnectionTo(first);
                if (firstToSecond == nullptr) {
                    if (secondToFirst == nullptr) {
                        if (firstToSecond == nullptr) {
                            cout << "The node \"" << first->label << "\" isn't connected to \"" << second->label << "\"." << endl
                                 << endl;
                            continue;
                        } else {
                            cout << "The node \"" << second->label << "\" isn't connected to \"" << first->label << "\"." << endl
                                 << endl;
                            continue;
                        }
                    }
                }

                if (!graph_->removeConnection(first, second)) // probably wont ever happen
                    cout << "Failed to remove the edge." << endl;
                else
                    cout << "The edge between " << first->label << " and " << second->label << " has been deleted." << endl;
            }
        }
        if (strcmp(commandInput, cmdMatrix) == 0)
            graph_->printAdjacencyMatrix();
        if (strcmp(commandInput, cmdShortest) == 0) {
            cout << "ALL or ONE: ";
            char optionInput[7];
            cin >> optionInput;
            
            if (strcmp(optionInput, operandAll) == 0) {
                cout << "Enter the first node's label (2 chars max): ";
                char firstLabel[2];
                cin >> firstLabel;

                node* first = graph_->find(firstLabel);
                if (first == nullptr) {
                    cout << "A node labeled \"" << firstLabel << "\" wasn't found." << endl
                         << endl;
                    continue;
                }
                graph_->printAllPaths(first);
            }
            if (strcmp(optionInput, operandOne) == 0) {
                cout << "Enter the first node's label (2 chars max): ";
                char firstLabel[2];
                cin >> firstLabel;

                cout << "Enter the second node's label (2 chars max): ";
                char secondLabel[2];
                cin >> secondLabel;

                if (strcmp(firstLabel, secondLabel) == 0) {
                    cout << "Both labels can't be the same." << endl
                         << endl;
                    continue;
                }

                node* first = graph_->find(firstLabel);
                node* second = graph_->find(secondLabel);
                if (first == nullptr) {
                    cout << "A node labeled \"" << firstLabel << "\" wasn't found." << endl
                         << endl;
                    continue;
                }
                if (second == nullptr) {
                    cout << "A node labeled \"" << secondLabel << "\" wasn't found." << endl
                         << endl;
                    continue;
                }
                if (strcmp(first->label, second->label) == 0) { //probably shouldnt happen
                    cout << "Both labels can't be the same." << endl
                         << endl;
                    continue;
                }

                graph_->printShortestPath(first, second);
            }
        }
        if (strcmp(commandInput, commandQuit) == 0)
            break;
        cout << endl;
    }

    delete graph_;

    return 0;
}