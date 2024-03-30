#include <iostream>

// Node structure for BST
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Helper functions
    Node* insertUtil(Node* root, int value);
    Node* deleteUtil(Node* root, int value);
    Node* findMin(Node* node);
    Node* queryUtil(Node* root, int value);
    void inorderUtil(Node* root);
    void destroyTree(Node* root);

public:
    BST() : root(nullptr) {}
    ~BST();

    // Public functions
    void insert(int value);
    void remove(int value);
    bool query(int value);
    void inorder();
};

// Destructor to release memory
BST::~BST() {
    destroyTree(root);
}

// Helper function to destroy tree
void BST::destroyTree(Node* root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
    }
}

// Insertion operation
void BST::insert(int value) {
    root = insertUtil(root, value);
}

Node* BST::insertUtil(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }

    if (value < root->data) {
        root->left = insertUtil(root->left, value);
    } else if (value > root->data) {
        root->right = insertUtil(root->right, value);
    }

    return root;
}

// Deletion operation
void BST::remove(int value) {
    root = deleteUtil(root, value);
}

Node* BST::deleteUtil(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }

    if (value < root->data) {
        root->left = deleteUtil(root->left, value);
    } else if (value > root->data) {
        root->right = deleteUtil(root->right, value);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteUtil(root->right, temp->data);
    }

    return root;
}

Node* BST::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Query operation
bool BST::query(int value) {
    return queryUtil(root, value) != nullptr;
}

Node* BST::queryUtil(Node* root, int value) {
    if (root == nullptr || root->data == value) {
        return root;
    }

    if (value < root->data) {
        return queryUtil(root->left, value);
    }

    return queryUtil(root->right, value);
}

// Inorder traversal
void BST::inorder() {
    inorderUtil(root);
    std::cout << std::endl;
}

void BST::inorderUtil(Node* root) {
    if (root != nullptr) {
        inorderUtil(root->left);
        std::cout << root->data << " ";
        inorderUtil(root->right);
    }
}

// Testing the BST
int main() {
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);

    std::cout << "Inorder traversal of BST: ";
    bst.inorder(); // Output should be sorted: 3 5 7 10 12 15 18

    std::cout << "Query result for 7: " << (bst.query(7) ? "Found" : "Not Found") << std::endl; // Should print Found
    std::cout << "Query result for 20: " << (bst.query(20) ? "Found" : "Not Found") << std::endl; // Should print Not Found

    bst.remove(15);
    std::cout << "Inorder traversal after removing 15: ";
    bst.inorder(); // Output should be sorted: 3 5 7 10 12 18

    return 0;
}
