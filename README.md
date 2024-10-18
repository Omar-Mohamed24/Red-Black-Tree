# Red-Black-Tree
  A Red-Black Tree (RBT) is a type of self-balancing binary search tree that ensures operations like insertion, deletion, and lookups are performed efficiently in       O(log n) time. It's widely used in computer science for maintaining sorted data in dynamic sets. The key idea behind a Red-Black Tree is that it imposes additional    properties on the standard binary search tree, which helps to keep the tree balanced.

##Key Properties of Red-Black Trees:
  1.Every node is either red or black.
  2.The root of the tree is always black.
  3.All leaves (NULL pointers) are considered black.
  4.If a node is red, both of its children must be black (no two consecutive red nodes on a path).
  5.Every path from a node to its descendant leaves has the same number of black nodes.

  These properties guarantee that the longest path from the root to any leaf is no more than twice as long as the shortest path, ensuring the tree remains balanced.    This balance allows efficient insertion, deletion, and search operations.

In my implementation, I've adhered to the standard Red-Black Tree properties, focusing on efficient balancing during insertions and deletions to maintain the logarithmic time complexity. You can explore the code in this repository for a deeper understanding of how Red-Black Trees function in practice.
