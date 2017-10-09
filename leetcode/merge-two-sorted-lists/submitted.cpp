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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      ListNode* head, *h1, *h2, *cur;
      if (l1 == NULL) return l2;
      if (l2 == NULL) return l1;

      if (l1->val < l2->val) {
        cur = head = l1;
        h1 = l1->next;
        h2 = l2;
      } else {
        cur = head = l2;
        h1 = l1;
        h2 = l2->next;
      }

      while (h1 != NULL && h2 != NULL) {
        if (h1->val < h2->val) {
          cur->next = h1;
          cur = cur->next;
          h1 = h1->next;
        } else {
          cur->next = h2;
          cur = cur->next;
          h2 = h2->next;
        }
      }

      if (h2 == NULL) {
        cur->next = h1;
      } else {
        cur->next = h2;
      }

      return head;
    }
};