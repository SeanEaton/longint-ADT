template <class Object>
Deque<Object>::Deque( ) {                          // the constructor
  front = back = NULL;
}

template <class Object>
Deque<Object>::Deque( const Deque &rhs ) {         // the copy constructor
  front = back = NULL;
  *this = rhs;
}

template <class Object>
Deque<Object>::~Deque( ) {                         // the destructor
  clear( );
}

template <class Object>
bool Deque<Object>::isEmpty( ) const {             // check if a deque is empty
  return front == NULL;
}

template <class Object>
int Deque<Object>::size( ) const {                 // retrieves # deque nodes
  int i = 0;
  for ( DequeNode *ptr = front; ptr != NULL; ptr = ptr->next ) // traverse que
    ++i;

  return i;
}

template <class Object>
const Object &Deque<Object>::getFront( ) const {   // retrieve the front node
  if ( isEmpty( ) )
    throw "empty queue";
  return front->item;
}

template <class Object>
const Object &Deque<Object>::getBack( ) const {    // retrieve the tail node
  if ( isEmpty( ) )
    throw "empty queue";
  return back->item;
}

template <class Object>
void Deque<Object>::clear( ) {          // clean up all entries.
  while ( !isEmpty( ) )                 // dequeue till the queue gets empty.
    removeFront( );
}
// add a new node to front
template <class Object>
void Deque<Object>::addFront( const Object &obj ) {
  //implement the function body.
  DequeNode *newnode = new DequeNode();
  newnode->item = obj;
  if (front == NULL) {
    front = back = newnode;
  }
  else {
    newnode->next = front;
    front->prev = newnode;
    front = newnode;
  }
}

// add a new node to tail
template <class Object>
void Deque<Object>::addBack( const Object &obj ) { 
   //implement the function body.
  DequeNode *newnode = new DequeNode();
  newnode->item = obj;
  if (front == NULL) {
    front = back = newnode;
  }
  else {
    newnode->prev = back;
    back->next = newnode;
    back = newnode;
  }
}

template <class Object>
Object Deque<Object>::removeFront( ) {  // remove the front node
  if (isEmpty()) throw "empty queue";
  DequeNode *del = front;
  front = front->next;
  if (front != NULL) {
    front->prev = NULL;
  }
  else back = NULL;
  Object obj = del->item;
  delete del;
  del = NULL;
  return obj;
}

template <class Object>
Object Deque<Object>::removeBack( ) {   // remove the tail node
  if (isEmpty()) throw "empty queue";
  DequeNode *del = back;
  back = back->prev;
  if (back != NULL) {
    back->next = NULL;
  }
  else front = NULL;
  Object obj = del->item;
  delete del;
  del = NULL;
  return obj;
}

template <class Object>
const Deque<Object> &Deque<Object>::operator=( const Deque &rhs ) { // assign
  if ( this != &rhs ) { // avoid self assignment
    clear( );
    for ( DequeNode *rptr = rhs.front; rptr != NULL; rptr = rptr->next )
      addBack( rptr->item );
  }
  return *this;
}


