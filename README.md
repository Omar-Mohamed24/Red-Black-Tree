# Red-Black Tree

A **Red-Black Tree (RBT)** is a self-balancing binary search tree that ensures operations like insertion, deletion, and lookups are performed efficiently in **O(log n)** time. This tree is widely used in computer science for maintaining sorted data within dynamic sets. By imposing additional properties on the standard binary search tree, a Red-Black Tree maintains balance, which optimizes its performance.

## Key Properties of Red-Black Trees

1. **Node Color**: Each node is either **red** or **black**.
2. **Root Property**: The root node is always **black**.
3. **Leaf Nodes**: All leaves (represented by `NULL` pointers) are considered **black**.
4. **Red-Red Conflict**: If a node is **red**, both of its children must be **black** (i.e., no two consecutive red nodes on any path).
5. **Black Height**: Every path from a node to its descendant leaves must have the same number of **black** nodes.

These properties ensure that the longest path from the root to any leaf is no more than twice the length of the shortest path, keeping the tree balanced and ensuring logarithmic time complexity for critical operations like insertion, deletion, and search.

## Implementation

This repository contains an implementation of the Red-Black Tree, where I've strictly adhered to its balancing rules. Special attention is given to maintaining logarithmic time complexity, especially during insertion and deletion operations.

### Key Features:
- **Insertion**: Automatically adjusts the tree after each insertion to preserve balance.
- **Deletion**: Ensures that the Red-Black properties remain intact after removing a node.
- **Balancing**: Rotations and recoloring operations ensure that the tree remains balanced.

You can explore the source code in this repository for a deeper understanding of how Red-Black Trees work and how the balancing mechanisms.
