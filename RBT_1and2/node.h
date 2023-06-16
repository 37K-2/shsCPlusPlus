#ifndef NODE_H
#define NODE_H
struct vertex {
    vertex();
    vertex(vertex*, int);

    bool isRed();

    int value;

    vertex* parentVertex;
    vertex* leftVertex;
    vertex* rightVertex;

    char color; // r -> red, b -> black
};

#endif

// contains left child, right child, parent node, a data value, and a color (red or black in this case).