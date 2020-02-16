#include <stdio.h>
#include <stdlib.h>

//Definition for singly-linked list.
struct ListNode {
   int val;
   struct ListNode *next;
};

void printList(struct ListNode* list)
{
    printf("list:");
    while (list != NULL) {
        printf(" %d", list->val);
        list = list->next;
    }
    printf("\n");
}

struct ListNode* reverseList(struct ListNode* list)
{
    struct ListNode* pre = list;
    struct ListNode* cur = list->next;
    struct ListNode* tmp;

    while (cur != NULL) {
        tmp = cur->next;
        cur->next = pre;

        pre = cur;
        cur = tmp;
    }

    list->next = NULL;
    return pre;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    if (l1 == NULL) {
        return l2;
    }

    if (l2 == NULL) {
        return l1;
    }

    struct ListNode* r1 = reverseList(l1);
    struct ListNode* r2 = reverseList(l2);
    struct ListNode* ans = NULL;
    struct ListNode* remain;
    struct ListNode* tmp = NULL;
    int carry = 0;
    int sum;

    while (r1 != NULL && r2 != NULL) {
        ans = (struct ListNode*)malloc(sizeof(struct ListNode));
        ans->next = tmp;
        tmp = ans;

        sum = r1->val + r2->val + carry;
        carry = sum > 9 ? 1 : 0;
        ans->val = sum % 10;

        r1 = r1->next;
        r2 = r2->next;
    }

    remain = r1 == NULL ? r2 : r1;
    while (remain != NULL) {
        ans = (struct ListNode*)malloc(sizeof(struct ListNode));
        ans->next = tmp;
        tmp = ans;

        sum = remain->val + carry;
        carry = sum > 9 ? 1 : 0;
        ans->val = sum % 10;

        remain = remain->next;
    }

    if (carry) {
        ans = (struct ListNode*)malloc(sizeof(struct ListNode));
        ans->next = tmp;
        ans->val = carry;
    }

    return ans;
}

int test2()
{
	struct ListNode l1;

	struct ListNode r1;
	struct ListNode r2;

	l1.val = 1;

	l1.next = NULL;

	r1.val = 9;
	r2.val = 9;

	r1.next = &r2;
	r2.next = NULL;

	struct ListNode* ans = addTwoNumbers(&l1, &r1);

    printList(ans);
	return 0;
}

int test1()
{
	struct ListNode l1;
	struct ListNode l2;
	struct ListNode l3;
	struct ListNode l4;

	struct ListNode r1;
	struct ListNode r2;
	struct ListNode r3;

	l1.val = 7;
	l2.val = 2;
	l3.val = 4;
	l4.val = 3;

	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = NULL;

	r1.val = 5;
	r2.val = 6;
	r3.val = 4;

	r1.next = &r2;
	r2.next = &r3;
	r3.next = NULL;

	struct ListNode* ans = addTwoNumbers(&l1, &r1);
    printList(ans);

	return 0;
}

int main()
{
    test2();
	return 0;
}
