#include <climits>
#include <iostream>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
};
typedef struct Node *NodePtr;

NodePtr createNode(int x) {
    NodePtr node = new Node();
    node->info = x;
    node->left = NULL;
    node->right = NULL;
    return node;
}

NodePtr insertNode(NodePtr p, int value) {
    if (p == NULL) {
        return createNode(value);
    } else {
        if (value < p->info) {
            p->left = insertNode(p->left, value);
        } else {
            p->right = insertNode(p->right, value);
        }
        return p;
    }
}

void preOrder(NodePtr root) {
    if (root != NULL) {
        cout << root->info << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void FreeNode(NodePtr p) {
    if (p == NULL)
        return;
    FreeNode(p->left);
    FreeNode(p->right);
    delete p;
}

NodePtr findMinValueNode(NodePtr root) {
    NodePtr current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

NodePtr deleteNode(NodePtr root, int key) {
    if (root == NULL)
        return root;

    if (key < root->info) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->info) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            NodePtr temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            NodePtr temp = root->left;
            delete root;
            return temp;
        }

        NodePtr temp = findMinValueNode(root->right);
        root->info = temp->info;
        root->right = deleteNode(root->right, temp->info);
    }
    return root;
}

int countNodesWithOneChild(NodePtr root) {
    if (root == NULL)
        return 0;

    int count = 0;
    if ((root->left != NULL && root->right == NULL) ||
        (root->left == NULL && root->right != NULL)) {
        count = 1;
    }

    count += countNodesWithOneChild(root->left);
    count += countNodesWithOneChild(root->right);

    return count;
}

void Menu() {
    cout << "\n____________________MENU____________________\n";
    cout << endl;
    cout << "    [+] 1. Them 1 Nut 10 vao cay nhi phan tim kiem\n";
    cout << "    [+] 2. Dem so Nut co dung 1 cay con\n";
    cout << "    [+] 3. Xoa Nut co gia tri 27\n";
    cout << "    [+] 4. DUYET CAY NLR\n";
    cout << "    [+] 0. EXIT.\n";
    cout << "\n____________________________________________\n";
    cout << endl;
    cout << "Nhap lua chon cua ban: ";
    cout << "Hello world";
}

int main() {
    NodePtr p = createNode(32);
    p->left = createNode(12);
    p->left->left = createNode(7);
    p->left->left->left = createNode(1);
    p->left->right = createNode(27);
    p->left->right->left = createNode(22);
    p->left->right->right = createNode(28);
    p->left->right->left->right = createNode(24);
    p->left->right->right = createNode(48);
    p->right = createNode(53);
    p->right->left = createNode(45);
    p->right->right = createNode(80);
    p->right->right->left = createNode(75);
    int choice, value;

    do {
        Menu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap gia tri can them (vi du: 10): ";
                cin >> value;
                p = insertNode(p, value);
                break;
            case 2:
                cout << "So nut co dung 1 cay con la: " << countNodesWithOneChild(p) << endl;
                break;
            case 3:
                cout << "Nhap gia tri nut can xoa (vi du: 27): ";
                p = deleteNode(p, 27);
                break;
            case 4:
                cout << "\nDUYET CAY NLR : ";
                preOrder(p);
                break;
            case 0:
                cout << "Thoat chuong trinh.";
                break;
            default:
                cout << "Lua chon khong hop le.";
                break;
        }
        cout << endl;
    } while (choice != 0);

    FreeNode(p);

    return 0;
}
