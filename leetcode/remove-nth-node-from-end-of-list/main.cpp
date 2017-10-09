#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

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

void printOutput (ListNode* head)
{
  ListNode* cur = head;
  while (cur != NULL) {
    cout << cur->val << " ";
    cur = cur->next;
  }
  cout << endl;
}

int main (int argc, char* argv[])
{
  ListNode* head = new ListNode(1);
  ListNode* cur = head;
  cur->next = new ListNode(2); cur = cur->next;
  cur->next = new ListNode(3); cur = cur->next;
  cur->next = new ListNode(4); cur = cur->next;
  cur->next = new ListNode(5); cur = cur->next;

  int n = 2;

  printOutput(head);
  printOutput( removeNthFromEnd(head, n) );
  return 0;
}
