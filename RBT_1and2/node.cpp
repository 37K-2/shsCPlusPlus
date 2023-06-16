#include "node.h"

vertex::vertex() {
    this->value = 0;
    this->parentVertex = nullptr;
    this->leftVertex = nullptr;
    this->rightVertex = nullptr;
    this->color = 'b';
}

vertex::vertex(vertex* nullVertex, int value) {
    this->value = value;
    this->parentVertex = nullptr;
    this->leftVertex = nullVertex;
    this->rightVertex = nullVertex;
    this->color = 'r'; // r -> red, b -> black
}

bool vertex::isRed() { return this->color == 'r'; }