#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem {
    struct TItem *m_Next;
    char *m_Name;
    char m_Secret[24];
} TITEM;


TITEM *newItem(const char *name, TITEM *next) {
  TITEM* tmp = (TITEM*)malloc(sizeof(TITEM));
  int len;

  len = strlen(name);
  tmp->m_Name = (char*)malloc(len*sizeof(char) + 1);
  strcpy(tmp->m_Name,name);
  tmp->m_Next = next;

  return tmp;
}

TITEM* mergeSorted(TITEM* a, TITEM* b, int ascending){
  int res;
  TITEM* result;

  if (a==NULL){
    return b;
  }
  else if (b == NULL){
    return a;
  }

  res = strcmp(a->m_Name, b->m_Name);
  if (ascending){
    if (res >= 0){
      result = b;
      result->m_Next = mergeSorted(a, b->m_Next, ascending);
    }
    else{
      result = a;
      result->m_Next = mergeSorted(a->m_Next, b, ascending);
    }
  }
  else{
    if (res <= 0){
      result = b;
      result->m_Next = mergeSorted(a, b->m_Next, ascending);
    }
    else{
      result = a;
      result->m_Next = mergeSorted(a->m_Next, b, ascending);
    }
  }

  return  result;
}
/*
void split(TITEM *head, TITEM **front, TITEM **back){

  if (head == NULL || head->m_Next){
    *front = head;
    *back = NULL;
    return;
  }

  TITEM *mid = head;
  TITEM *last = head->m_Next;

  while(last != NULL){
    last = last->m_Next;
    if (last != NULL){
      mid = mid->m_Next;
      last = last->m_Next;
    }
  }

  *front = head;
  *back = mid->m_Next;
  mid->m_Next = NULL;
}*/

TITEM *sortList(TITEM *l, int ascending) {
  if (l == NULL || l->m_Next == NULL){
    return l;
  }

  TITEM* a = l;
  TITEM* b = l->m_Next;

  while ( b != NULL){
    b = b->m_Next;
    if (b != NULL){
      l = l->m_Next;
      b = b->m_Next;
    }
  }
  b = l->m_Next;
  l->m_Next = NULL;
  //split(l, &a, &b);

  a = sortList(a, ascending);
  b = sortList(b, ascending);

  l = mergeSorted(a, b, ascending);
  return l;
}


void freeList(TITEM *src) {
  while(src){
    TITEM* nextNode = src->m_Next;
    free(src->m_Name);
    free(src);
    src = nextNode;
  }
}
