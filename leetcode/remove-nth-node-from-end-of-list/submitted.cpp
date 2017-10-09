/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (n == 1) {
            if (head->next == NULL) return NULL;
            ListNode* cur = head;
            while (cur->next->next != NULL) cur = cur->next;
            delete cur->next;
            cur->next = NULL;
            return head;
        }

        ListNode* fast = head;
        for (int i=0; i<n; ++i){
            if (fast == NULL) return head;
            fast = fast->next;
        }

        ListNode* slow = head;
        while (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode* nextOfNext = slow->next->next;
        slow->val = slow->next->val;
        delete slow->next;
        slow->next = nextOfNext;

        return head;
    }
};