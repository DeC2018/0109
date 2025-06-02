#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 20000

// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Find the middle node and split the list
struct ListNode* findMiddle(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast != NULL && fast->next != NULL) {
        prev = slow;
        fast = fast->next->next;
        slow = slow->next;
    }
    if (prev) {
        prev->next = NULL;
    }
    return slow;
}

// Convert sorted list to height-balanced BST
struct TreeNode* sortedListToBST(struct ListNode* head) {
    if (!head)
        return NULL;
    struct ListNode* mid = findMiddle(head);
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = mid->val;
    root->left = NULL;
    root->right = NULL;
    if (mid != head) {
        root->left = sortedListToBST(head);
    }
    root->right = sortedListToBST(mid->next);
    return root;
}

// Helper to parse input string like "[-10,-3,0,5,9]" into linked list
struct ListNode* parseInput(const char* s) {
    int i = 0, sign = 1, num = 0, inNum = 0;
    struct ListNode dummy, *tail = &dummy;
    dummy.next = NULL;
    while (s[i]) {
        if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
            sign = 1;
            if (s[i] == '-') {
                sign = -1;
                ++i;
            }
            num = 0;
            inNum = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                ++i;
                inNum = 1;
            }
            if (inNum) {
                struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
                node->val = num * sign;
                node->next = NULL;
                tail->next = node;
                tail = node;
            }
        } else {
            ++i;
        }
    }
    return dummy.next;
}

// Helper to print tree in level order (as per example output)
void printTree(struct TreeNode* root) {
    if (!root) {
        printf("[]\n");
        return;
    }
    struct TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;
    char* res[MAX_NODES];
    int res_len = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct TreeNode* node = queue[front++];
        if (node) {
            char* buf = (char*)malloc(24);
            sprintf(buf, "%d", node->val);
            res[res_len++] = buf;
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        } else {
            res[res_len++] = strdup("null");
        }
    }
    // Remove trailing "null"s
    while (res_len > 0 && strcmp(res[res_len-1], "null") == 0)
        res_len--;
    printf("[");
    for (int i = 0; i < res_len; ++i) {
        if (i) printf(",");
        printf("%s", res[i]);
        free(res[i]);
    }
    printf("]\n");
}

// Helper to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// Helper to free the memory of a linked list
void deleteList(struct ListNode* head) {
    while (head) {
        struct ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    const char* inputs[] = {
        "[-10,-3,0,5,9]",
        "[]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: head = %s\n", inputs[i]);
        struct ListNode* head = parseInput(inputs[i]);
        struct TreeNode* root = sortedListToBST(head);
        printf("Output: ");
        printTree(root);
        deleteTree(root);
        deleteList(head);
    }
    return 0;
}
