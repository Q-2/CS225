/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* curr = head_;
  while (curr != NULL){
    ListNode* future = curr->next;
    delete curr;
    curr = future;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  


  if (head_ != NULL) {
    head_ -> prev = newNode;
    head_ = head_->prev;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  length_++;
  //stringstream s;
  //print(s);
  //std::cout << s.str() << std::endl;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = tail_;
  newNode -> next = NULL;
  

  if (tail_ != NULL) {
    tail_ -> next = newNode;
    tail_ = tail_->next;
  }
  
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  length_++;
  
  //stringstream s;
  //print(s);
  //std::cout << s.str() << std::endl;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start == NULL) {return start;}
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
    if (curr->prev != NULL) {
      curr->prev->next = NULL;
      }
    curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  auto cur = head_;
  int i = 0;
  while( cur != tail_){
    if(cur == NULL) {return;}
    if(cur->next != NULL) {
      if(cur->next->next != NULL){
        auto zero = cur->prev;
        auto one = cur;
        auto two = cur->next;
        auto three = cur->next->next;
        auto four = cur->next->next->next;
        if(i == 0) {head_ = two;}
        i++;
        one->next = four;
        one->prev = three;
        two->prev = zero;
        two->next = three;
        three->prev = two;
        three->next = one;
        if(four != NULL) {
          four->prev = one;
          cur = four;
        }
        if(zero != NULL) {
          zero->next = two;
        }

      }
    }
  if (cur->next == NULL) {return;}
  if (cur->next->next == NULL) {return;}
  }
  // @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  auto startTemp = startPoint;
  auto endTemp = endPoint;
  ListNode* Right = endPoint->next;
  ListNode* Left = startPoint->prev;
  ListNode* curr = startPoint;
  Penguin(curr, endPoint);
  startPoint->next = endPoint->next;
  endPoint->next = endPoint->prev;
  endPoint->prev = Left;
  
  if(startTemp == head_) {head_ = endPoint;}
  if(endTemp == tail_) {tail_ = startPoint;}
  ListNode* temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
  if(Left != NULL) {
  Left->next = startPoint;
  }
  if(Right != NULL) {
  Right->prev = endPoint;
  }
 }


 template <typename T>
void List<T>::Penguin( ListNode *&curr,  ListNode *& endPoint) {
  auto anexxed = curr->next;
  while(curr != endPoint && curr != NULL){
    anexxed = curr->next;
    curr->next = curr->prev;
      curr->prev = anexxed;
      curr = anexxed;
    }
}
/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  auto curr = head_;
  auto historian = curr;
  auto lister = head_;
  auto ceiling = getLength() / n;
  auto storedceil = ceiling;
    std::cout << ceiling <<"<-ceiling    " << getLength() << "<- length    " << n  << "<- N    " << std::endl;
  while (ceiling > 0){
    for (int i = 1; (i < getLength()) && (i < n) && (curr != tail_); i++ ){
     curr = curr->next;  // sets curr to the endpoint
    }

 
    reverse(lister,curr);
    
    lister = curr->next; // sets curr and lister to the first point in the next block;
    curr = curr->next;
    ceiling--; // decrements ceiling
  } // it's not properly finishing the last loop; why?
  if((storedceil * n) != getLength()) {
    historian = curr;
    while (curr != tail_){
      curr = curr->next;
    }
    if(historian != NULL) {
      reverse(historian,curr);
    }
  }
}



/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2 INFINITE LOOP IS WITHIN THIS FUNCTION
 if (second->data < first->data) {
        auto temp = second;
        second = first;
        first = temp;
 }
auto j = first;
auto i = second;
int y  = 0;
auto trailer = j;
for(; j !=nullptr;){
  auto tempj = j->next;
  auto tempi = i->next;
 trailer = j;
  if(i->data < j->data) {
    pointerMergePrev(j,i);
    i = tempi; 
    continue;
  }
  //update j
  j = tempj;
  }
    if(j == NULL && i != NULL) {
    trailer->next = i;
    i->prev = j;
}
  return first;
}



template <typename T>
void List<T>::pointerMergeNext(ListNode *& first, ListNode *&inserted) {
// MERGES THE INSERTED INTO THE NEXT OF FIRST
  auto fnext = first->next;
  first->next = inserted;
  inserted->next = fnext;
  inserted->prev = first;
  if(fnext != NULL) {fnext->prev = inserted;}
  if(first == tail_) {tail_ = inserted;}
}
template <typename T>
void List<T>::pointerMergePrev(ListNode *& first, ListNode *&inserted) {
  auto fprev = first->prev;
  first->prev = inserted;
  inserted->prev = fprev;
  inserted->next = first;
  if(fprev != NULL) {fprev->next = inserted;}
  if(first == head_) {head_ = inserted;}
}
/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(head_ == tail_) {return head_;}
  auto temp = split(start,chainLength/2);
 
  return merge(mergesort(start,chainLength/2),mergesort(temp, (chainLength % 2) + (chainLength / 2)) );

}
