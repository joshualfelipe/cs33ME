class Node:
    def __init__(self, val=None):
        self.val = val
        self.left = None
        self.right = None
        self.parent = None
        self.height = 1

class Tree:
    def __init__(self):
        # Initializes the tree
        self.root = None
    
    def checkIfHead(self, val):
        # Check if parent is head
        if self.root is None:
            # make current as head
            self.root = Node(val)
        else:
            # traverse tree then insert
            self.insert(val, self.root)
    
    def insert(self, val, current):
        # Method that adds the new node to the AVL Tree
        if val < current.val:   # Insert on left child 
            if current.left is None:
                # If parent has no left child, make current the new left child
                current.left = Node(val)
                current.left.parent = current
                self.inspect(current.left)
            
            else:
                # Traverse left child
                self.insert(val, current.left)

        if val > current.val:   # Insert on right child 
            if current.right is None:
                # If parent has no right child, make current the new right child
                current.right = Node(val)
                current.right.parent = current
                self.inspect(current.right)
            
            else:
                # Traverse right child
                self.insert(val, current.right)

    def inspect(self, current, path=[]):
        # Path serves as a list of nodes; this makes it easier to keep track of all the nodes being added and traversed

        if current.parent is None:
            # Base case: reached the root node
            return
        
        path = [current] + path         # update the value of the list of nodes

        leftHeight = self.height(current.parent.left)       # get height of left subtree
        rightHeight = self.height(current.parent.right)     # get height of right subtree

        if abs(leftHeight - rightHeight) > 1:
            path = [current.parent] + path
            self.balance(path[0], path[1], path[2])
            return
        
        new_height = 1 + current.height

        if new_height > current.parent.height:
            current.parent.height = new_height

        self.inspect(current.parent, path)

    def balance(self, node1, node2, node3):
        # Method checks which node(s) to rotate.
        if node2 == node1.left and node3 == node2.left:
            self.rotateRight(node1)

        elif node2 == node1.left and node3 == node2.right:
            self.rotateLeft(node2)
            self.rotateRight(node1)
        
        elif node2 == node1.right and node3 == node2.right:
            self.rotateLeft(node1)
        
        elif node2 == node1.right and node3 == node2.left:
            self.rotateRight(node2)
            self.rotateLeft(node1)

    def height(self, current):
        # Get the height of the tree
        if current is None:
            return 0
        return current.height

    def rotateRight(self, node):
        # Perform right rotation
        root = node.parent
        leftSubNode = node.left
        rightSubNode = leftSubNode.right
        leftSubNode.right = node
        node.parent = leftSubNode
        node.left = rightSubNode
        if rightSubNode is not None:
            rightSubNode.parent = node
        leftSubNode.parent = root
        if leftSubNode.parent is None:
            self.root = leftSubNode
        else:
            if leftSubNode.parent.left == node:
                leftSubNode.parent.left = leftSubNode
            else:
                leftSubNode.parent.right = leftSubNode

        node.height = 1 + max(self.height(node.left), self.height(node.right))

        leftSubNode.height = 1 + max(self.height(leftSubNode.left), self.height(leftSubNode.right))
    
    def rotateLeft(self, node):
        # Perform left rotation
        root = node.parent
        rightSubNode = node.right
        leftSubNode = rightSubNode.left
        rightSubNode.left = node
        node.parent = rightSubNode
        node.right = leftSubNode
        if leftSubNode is not None:
            leftSubNode.parent = node
        rightSubNode.parent = root
        if rightSubNode.parent is None:
            self.root = rightSubNode
        else:
            if rightSubNode.parent.left == node:
                rightSubNode.parent.left = rightSubNode
            else:
                rightSubNode.parent.right = rightSubNode

        node.height = 1 + max(self.height(node.left), self.height(node.right))

        rightSubNode.height = 1 + max(self.height(rightSubNode.left), self.height(rightSubNode.right))


def printPreorder(root):
    # Print tree values in preorder traversal
    if root:
        print(f"-{root.val}-", end="")

        # Then recur on the left child
        printPreorder(root.left)

        # Finally recur on the right child
        printPreorder(root.right)

a = Tree()
arr = []
while True:
    num = int(input())
    if num == 0:
        break

    arr.append(num)

for num in arr:
    a.checkIfHead(num)
    printPreorder(a.root)
    print()

"""
References:

https://www.youtube.com/watch?v=lxHF-mVdwK8
https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
"""