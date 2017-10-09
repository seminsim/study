#include <iostream>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

ListNode* mergeTwoLists (ListNode* l1, ListNode* l2)
{
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

ListNode* generateInput1()
{
  ListNode* head = new ListNode(1);
  ListNode* cur = head;
  cur->next = new ListNode(4); cur = cur->next;
  cur->next = new ListNode(8); cur = cur->next;
  cur->next = new ListNode(9); cur = cur->next;

  return head;
}

ListNode* generateInput2()
{
  ListNode* head = new ListNode(2);
  ListNode* cur = head;
  cur->next = new ListNode(3); cur = cur->next;
  cur->next = new ListNode(5); cur = cur->next;
  cur->next = new ListNode(10); cur = cur->next;
  cur->next = new ListNode(11); cur = cur->next;
  cur->next = new ListNode(12); cur = cur->next;
  cur->next = new ListNode(13); cur = cur->next;

  return head;
}

void printLinkedList (ListNode* head)
{
  while (head != NULL) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

int main (int argc, char* argv[])
{
  printLinkedList(generateInput1());
  printLinkedList(generateInput2());
  printLinkedList(
    mergeTwoLists(generateInput1(), generateInput2())
  );
  printLinkedList(
    mergeTwoLists(generateInput1(), NULL)
  );
  printLinkedList(
    mergeTwoLists(NULL, generateInput2())
  );

  return 0;
}
