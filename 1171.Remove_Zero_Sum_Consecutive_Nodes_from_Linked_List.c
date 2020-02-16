#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* removeZeroSumSublists(struct ListNode* head){
    struct ListNode ans;
    ans.next = head;
    struct ListNode* pre = &ans;
    struct ListNode* cur;
    struct ListNode* tmp;
    int sum = 0;
    int deleted = 0;

    while (pre->next != NULL) {
        cur = pre->next;
        sum = 0;
        deleted = 0;

        while (cur != NULL) {
            sum += cur->val;

            cur = cur->next;
            if (sum == 0) {
                while (pre->next != cur) {
                    tmp = pre->next;
                    pre->next = pre->next->next;
                    free(tmp);
                }

                deleted = 1;
                break;
            }
        }

        if (deleted == 0) {
            pre = pre->next;
        }
    }

    return ans.next;
}

void printList(struct ListNode* head)
{
    printf("List:");
    while(head) {
        printf(" %d", head->val);
        head = head->next;
    }
    printf("\n");
}

void test1()
{
    struct ListNode* node1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* node2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* node3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* node4 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* node5 = (struct ListNode*)malloc(sizeof(struct ListNode));

    node1->val = 1;
    node2->val = 2;
    node3->val = -3;
    node4->val = 3;
    node5->val = 1;

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = NULL;

    printList(node1);
    struct ListNode* head = removeZeroSumSublists(node1);
    printList(head);
}

void test2()
{
    struct ListNode* head = NULL;
    int data[] = {1,2,3,-3,4};

    struct ListNode* node;
    struct ListNode* pre;
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
        node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = data[i];
        if (head == NULL) {
            head = node;
            pre = node;
        } else {
            pre->next = node;
            pre = pre->next;
        }
    }
    node->next = NULL;

    printList(head);
    head = removeZeroSumSublists(head);
    printList(head);
}

int main()
{
    test1();
    test2();
    return 0;
}