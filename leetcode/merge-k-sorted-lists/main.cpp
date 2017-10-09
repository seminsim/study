#include <vector>

#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeKLists (vector<ListNode*>& lists)
{
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

void printList (ListNode* head);
void generateInput(vector<ListNode*>& lists)
{
  lists.clear();

  ListNode* head;
  ListNode* cur;

  head = new ListNode(1);
  cur = head;
  cur->next = new ListNode(4); cur = cur->next;
  cur->next = new ListNode(8); cur = cur->next;
  cur->next = new ListNode(12); cur = cur->next;
  cur->next = new ListNode(13); cur = cur->next;
  printList(head);
  lists.push_back(head);
  lists.push_back(NULL);
  lists.push_back(new ListNode(20));

  head = new ListNode(2);
  cur = head;
  cur->next = new ListNode(3); cur = cur->next;
  cur->next = new ListNode(5); cur = cur->next;
  cur->next = new ListNode(6); cur = cur->next;
  cur->next = new ListNode(18); cur = cur->next;
  printList(head);
  lists.push_back(head);
}

void printList (ListNode* head)
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
  vector<ListNode*> input;
  generateInput(input);

  printList (
    mergeKLists(
      input
    )
  );
  return 0;
}
