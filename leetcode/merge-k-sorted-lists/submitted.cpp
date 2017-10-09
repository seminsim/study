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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
      int size = lists.size();

      ListNode* head = new ListNode(0);
      ListNode* cur = head;
      ListNode** h = new ListNode* [size];
      int minNext;

      for (int i=0; i<size; ++i) {
        h[i] = lists[i];
      }

      bool isFinished;
      while (true) {
        // check termination condition
        isFinished = true;
        for (int i=0; i<size; ++i) {
          if (h[i] != NULL) {
            isFinished = false;
            break;
          }
        }
        if (isFinished) {
          delete[] h;
          ListNode* retHead = head->next;
          delete head;
          return retHead;
        }

        // find the min next node
        minNext = -1;
        for (int i=0; i<size; ++i) {
          if (h[i] != NULL && (minNext < 0 || h[i]->val < h[minNext]->val)) minNext = i;
        }

        cur->next = h[minNext];
        cur = cur->next;
        h[minNext] = h[minNext]->next;
      }
    }
};