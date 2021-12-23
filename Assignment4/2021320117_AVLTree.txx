//
// Implementation
//
template <typename E>					// constructor
  AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
  int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
  void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
  }

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
  }

template <typename E>					// get tallest grandchild
  typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
      if (height(zl.left()) >= height(zl.right()))
        return zl.left();
      else
        return zl.right();
    else 						// right child taller
      if (height(zr.right()) >= height(zr.left()))
        return zr.right();
      else
        return zr.left();
  }


//
// ToDo
//

template <typename E>					// remove key k entry
  void AVLTree<E>::erase(const K& k) {
    
    TPos v = ST::finder(k, ST::root());
    if(Iterator(v) == ST::end()){
      throw "Erase of nonexistent";
    }    
    TPos w = ST::eraser(v);
    rebalance(w);
  }

template <typename E>					// insert (k,x)
  typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
    TPos v = ST::inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
    
  }
  
template <typename E>					// rebalancing utility
  void AVLTree<E>::rebalance(const TPos& v) {
    
    TPos z = v;
    while(!(z == ST::root())){
      z = z.parent();
      setHeight(z);
      if (!isBalanced(z)){
        TPos x = tallGrandchild(z);
        z = restructure(x);
        setHeight(z.left());
        setHeight(z.right());
        setHeight(z);
      }
    }
    
  }

template <typename E>				// Binary Search Tree Rotation
  typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {

    TPos x = v; TPos y = x.parent(); TPos z = y.parent();
    TPos a, b, c;

    if(((*z).key() <= (*x).key()) && ((*x).key() <= (*y).key())){
      a = z; b = x; c = y;
    }
    if(((*y).key() <= (*x).key()) && ((*x).key() <= (*z).key())){
      a = y; b = x; c = z;
    }
    if(((*z).key() <= (*y).key()) && ((*y).key() <= (*x).key())){
      a = z; b = y; c = x;
    }
    if(((*x).key() <= (*y).key()) && ((*y).key() <= (*z).key())){
      a = x; b = y; c = z;
    }

    if(z.parent().left() == z){
      (z.parent().v)->left = b.v;
      (b.v)->par = z.parent().v;
    }
    else{
      (z.parent().v)->right = b.v;
      (b.v)->par = z.parent().v;
    }

    if(b.left() != x && b.left() != y && b.left() != z){
      (a.v)->right = b.left().v;
      (b.left().v)->par = a.v;
    }
    if(b.right() != x && b.right() != y && b.right() != z){
      (c.v)->left = b.right().v;
      (b.right().v)->par = c.v;
    }

    (b.v)->left = a.v;
    (a.v)->par = b.v;

    (b.v)->right = c.v;
    (c.v)->par = b.v;

    return b;

  }

