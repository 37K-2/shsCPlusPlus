// Shunting Yard Algorithm By: Aaron Guo, Period: 6
// basically takes an expression and finds the infix, prefix, and postfix of the expression

#include <iostream>
#include <cstring>

#include "queue.h"
#include "stacks.h"
#include "tree.h"

using namespace std;

// commands
const char cmdInput[] = "INPUT";
const char cmdDisplay[] = "DISPLAY";
const char optInfixDisplay[] = "INFIX";
const char optPrefixDisplay[] = "PREFIX";
const char optPostfixDisplay[] = "POSTFIX";
const char cmdClear[] = "CLEAR";
const char cmdQuit[] = "QUIT";

// funct prototypes
outputQueue *expressionInput();
void shuntingYardFunc(outputQueue *expressionQueue);
void expressionTreeFunc(outputQueue *postfixQueue, expressionTree *tree);
int getPrecedence(char op);

int main() {
    cout << "Shunting Yard Algorithm" << endl;

    expressionTree *tree = new expressionTree();

    char commandInput[8];

    while (true) {
        cout << "--------------------------------------------------" << endl;
        cout << "INPUT, DISPLAY, CLEAR or QUIT" << endl;
        cout << " >> ";
        cin >> commandInput; // get info

        if (strcmp(commandInput, cmdInput) == 0) { // to input smthg
            if (!tree->empty()) // make sure tree does not contain smthg before entering stuff into the tree
                cout << "There's an expression existing in the tree, please run \"CLEAR\" to clear it" << endl; // asks user to clear tree
            else {
                // create temp queue pointer from the expression (pointer to de-allocate pointers created by the object)
                outputQueue *queue = expressionInput();
                try {
                    shuntingYardFunc(queue);  //do shunting yard algorithm on the expression
                    expressionTreeFunc(queue, tree); // queue -> bst
                    cout << "Done." << endl;
                } catch (runtime_error &ex) { //only used if mismatched parentheses
                    cout << ex.what() << endl;
                }
                delete queue;
            }
        }
        if (strcmp(commandInput, cmdDisplay) == 0) { // display
            if (tree->empty()) // tree does not contain expression
                cout << "There's no expression to display" << endl;
            else {
                cout << "INFIX, PREFIX, or POSTFIX" << endl; // asks to do infix/prefix/postfix on the expression
                cout << " >> ";
                char optionInput[8];
                cin >> optionInput;

                if (strcmp(optionInput, optInfixDisplay) == 0)
                    tree->infixPrint(); // cmd for infix
                if (strcmp(optionInput, optPrefixDisplay) == 0)
                    tree->prefixPrint(); // cmd for prefix
                if (strcmp(optionInput, optPostfixDisplay) == 0)
                    tree->postfixPrint(); // cmd for postfix
            }
        }
        if (strcmp(commandInput, cmdClear) == 0) {
            delete tree; // delete tree and set new var
            tree = new expressionTree();
            cout << "Cleared the current expression" << endl;
        } if (strcmp(commandInput, cmdQuit) == 0) {
            delete tree;
            break;
        }

        cout << endl;
    }

    return 0;
}


// input should only be int, operators, spaces, and be <101 chars
outputQueue *expressionInput() {
    cout << "Enter in your expression.  Numbers should be single digits only.  Separate each token with a space.  Expression shouldn't exceed 100 characters in length (including spaces)." << endl;
    cout << " >> ";
    cin.ignore();
    char expression[102];
    cin.getline(expression, 101, '\n');

    outputQueue *queue = new outputQueue(); // queue pointer

    for (int i = 0; i < 102; i++) { // loop expression
        if (expression[i] == '\0')  // if at end then break
            break;
        if (expression[i] == ' ')  // if space then disregard
            continue;

        queue->enqueue(expression[i]);
    }

    return queue; // return queue pointer
}

// trasnformed to postfix notation -> used by next function to create an expression tree via the queue pointer

void shuntingYardFunc(outputQueue *expression) {
    // outputs
    outputQueue outputQueue;
    nodeStack operatorStack;

    while (!expression->empty()) { // continue until empty
        treeNode<char> *node = new treeNode<char>(expression->dequeue());

        if (node->isNum()) // if num then add to output
            outputQueue.enqueue(node->data); 
        else if (node->isOperator()) { // if operator then use PEMDAS
            while ((operatorStack.peek() != '\0' && operatorStack.peek() != '(') && (getPrecedence(operatorStack.peek()) >= getPrecedence(node->data))){ // something exists on the operator stack & top of the operator stack isn't an open parentheses + precedence of the top of the operator stack is > than the precedence of the current
                outputQueue.enqueue(operatorStack.pop()); // pop top of the operator stack, put in output queue
            }
            operatorStack.push(node->data); // put current token onto operator stack
        }
        else if (node->data == '(') // current is open parentheses
            operatorStack.push(node->data); // put on operator stack
        else if (node->data == ')') { // current is closing parentheses
            while (operatorStack.peek() != '(') { // find operators & put them in the output queue until top of the operator stack is open parentheses
                if (operatorStack.peek() == '\0') // operator stack is empty before parentheses are closed
                    throw runtime_error("Expression has 1(+) mismatched parentheses");
                else
                    outputQueue.enqueue(operatorStack.pop()); // pop off top of operator stack and put into output queue
            }
            if (operatorStack.peek() != '\0' && operatorStack.peek() == '(') // make sure top of operator stack is an open parentheses & remove from operator stack
                operatorStack.pop(); 
        }
    }
    // put all remaining operators on the operator stack into the output queue
    while (!operatorStack.empty()) {
        if (operatorStack.peek() == '(') // if there's still parentheses in the operator stack then obviously theres mismatched parentheses
            throw runtime_error("Expression has one more more mismatched parentheses"); 
        else
            outputQueue.enqueue(operatorStack.pop());
    }

    while (!expression->empty()) // check so that expression queue has nothing in it
        expression->dequeue();
    // copy the entire output queue into the expression queue from ^
    while (!outputQueue.empty())
        expression->enqueue(outputQueue.dequeue());
}

// construct expression tree from the given postfix expression
// queue pointer from above is passed in, contains a postfix expression instead of the infix 

void expressionTreeFunc(outputQueue *postfix, expressionTree *tree) {
    expressionStack stack; // stack contains pointers that will be expression tree (no dynamically allocated object so no deletion)
    
    while (!postfix->empty()) { // continue to read until empty
        treeNode<char> *node = new treeNode<char>(postfix->dequeue());
        if (!node->isOperator()) // If operand push TreeNode and into stack
            stack.push(node); 
        else { // If operator then get the top two treeNodes onto stack
            treeNode<char> *leftChild = stack.pop();
            treeNode<char> *rightChild = stack.pop();

            // set the current node's left and right children
            node->left = leftChild;
            node->right = rightChild;

            stack.push(node); // push the new node onto the stack
        }
    }
    tree->setRoot(stack.pop()); // set expression tree's root (which is treeNode) to top of stack (which is the full expression tree)
}


int getPrecedence(char op) { // precedence of operator (pemdas)
    switch (op)
    {
    case '+':
    case '-':
        // lowest priority in pemdas
        return 1;
    case '*':
    case '/':
    case '%':
        // next priority in pemdas
        return 2;
    case '^':
        // highest priority in pemdas
        return 3;
    default:
        return 0;
    }
}