#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        if (head->next == nullptr) return new TreeNode(head->val);
        ListNode* slow = head, *fast = head, *slow_prev = nullptr;
        while (fast != nullptr && fast->next != nullptr) {
            slow_prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        TreeNode *ans = new TreeNode(slow->val);
        if (slow_prev) slow_prev->next = nullptr;
        ans->left = sortedListToBST((slow == head) ? nullptr : head);
        ans->right = sortedListToBST(slow->next);
        return ans;
    }
};

// Helper to parse input string like "[-10,-3,0,5,9]" into linked list
ListNode* parseInput(const string& s) {
    string t = s;
    t.erase(remove(t.begin(), t.end(), '['), t.end());
    t.erase(remove(t.begin(), t.end(), ']'), t.end());
    stringstream ss(t);
    string item;
    ListNode dummy, *tail = &dummy;
    while (getline(ss, item, ',')) {
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        if (!item.empty())
            tail = tail->next = new ListNode(stoi(item));
    }
    return dummy.next;
}

// Helper function to print tree in level order (as per example output)
void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    vector<string> res;
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node) {
            res.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        } else {
            res.push_back("null");
        }
    }
    // Remove trailing "null"s
    while (!res.empty() && res.back() == "null") res.pop_back();
    cout << "[";
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ",";
        cout << res[i];
    }
    cout << "]" << endl;
}

// Helper to free the memory of a tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// Helper to free the memory of a linked list
void deleteList(ListNode* head) {
    while (head) {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    vector<string> inputs = {
        "[-10,-3,0,5,9]",
        "[]"
    };

    Solution solution;

    for (const auto& input : inputs) {
        cout << "Input: head = " << input << endl;
        ListNode* head = parseInput(input);
        TreeNode* root = solution.sortedListToBST(head);
        cout << "Output: ";
        printTree(root);
        deleteTree(root);
        deleteList(head);
    }

    return 0;
}
