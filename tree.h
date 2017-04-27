#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

using namespace std;

enum colors { red, black };

template <class T> class node
{
    public:
    T key;
    node *father;
    node *left;
    node *right;
    int color;

    node(T input)
    {
        key = input;
        left = NULL;
        right = NULL;
        father = NULL;
        color = red;
    }
};



template <class T> class Tree
{
        int Size(node<T>*);
        void Display(node<T>*,int);
        void Rotate_left (node<T>*);
        void Rotate_right(node<T>*);
        void Insert_fix (node<T>*);
        Tree(node<T>*);
        void Merge(node<T>*);
        void Split(node<T>*);
        node<T> *root;
        node<T>* Successor(node<T>*);
        void Delete_fix(node<T>*);
    public:
        Tree():root(NULL){};
        Tree(const Tree<T> &);
        void Insert(T input);
        bool T_find(T);
        node<T>* T_node_find(T);
        void Display();
        void operator+(const Tree<T>&);
        void operator-(const Tree<T>&);
        int Black_hight();
        int Size();
        void Delete(T);
};


template <class T>
Tree<T>::Tree(const Tree<T> &tree)
{
    if(tree.root == NULL) root = NULL;
    else
    {
     root = new node<T>(tree.root->key);
     root->color = tree.root->color;
     root->left = Tree(Tree(tree.root->left)).root;
     root->right = Tree(Tree(tree.root->right)).root;
    }
}

template<class T>
Tree<T>::Tree(node<T> * in)
{
    root = in;
}

template <class T>
void Tree<T>::Insert(T input){
    node<T> *p, *q;
     node<T> *create = new node<T>(input);
    p = root;
    q = NULL;
    if (root == NULL )
    {
        root = create;
        create->father = NULL;
    }
    else
    {
        while ( p != NULL)
        {
            q=p;
            if(p->key > create->key) p = p->left;
            else if(p->key < create->key) p = p->right;
            else return;
        }
        create->father = q;
        if(q->key < create->key) q->right=create;
        else if(q->key > create->key)q->left=create;
        else return;
    }
    Insert_fix(create);
}


template<class T>
void Tree<T>::Insert_fix(node<T> *create)
{
    node<T> *x = create;
    while( x!= root && x->father->color == red)
    {
        if(x->father == x->father->father->left) //father jest lewym synem dziadka
        {
            node<T> *y = x->father->father->right;
            if((y  != NULL ) && (y->color == red)) //stryj jest czerwony
            {
                x->father->color = black;
                y->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else  //stryj czarny
            {
                if(x->father->right == x)
                {
                    x  = x->father;
                    Rotate_left(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                Rotate_right(x->father->father);
            }
        }
        else
        {
            node<T> *y = x->father->father->left;
            if((y != NULL) && (y->color == red)) //stryj jest czerwony
            {
                x->father->color = black;
                y->color = black;
                x->father->father->color = red;
                x = x->father->father;
            }
            else  //stryj czarny
            {
                if(x->father->left == x)
                {
                    x = x->father;
                    Rotate_right(x);
                }
                x->father->color = black;
                x->father->father->color = red;
                Rotate_left(x->father->father);
            }
        }
    }
    root->color = black;
}

template<class T>
void Tree<T>::Rotate_right(node<T>* in)
{

     if(in->left == NULL)
           return ;
     else
     {
        node<T> *y = in;
        node<T> *x = y->left;
        node<T> *b = x->right;
        node<T> *f = y->father;
        if(f == NULL)
        {
            x->father = NULL;
            root = x;
        }
        else
        {
            x->father = f;
            if(f->left == y)
                f->left = x;
            if(f->right == y)
                f->right = x;
        }
        x->right = y;
        y->father = x;
        y->left = b;
        if( b != NULL)
            b->father =y;
     }
}

template <class T>
void Tree<T>::Rotate_left(node<T>* x)
{
     if(x->right == NULL)
           return ;
     else
     {
        node<T> *y = x->right;
        node<T> *b = y->left;
        node<T> *f = x->father;
        if(f == NULL)
        {
            y->father = NULL;
            root = y;
        }
        else
        {
            y->father = f;
            if(f->left == x)
                f->left = y;
            if(f->right == x)
                f->right = y;
        }
        y->left = x;
        x->father = y;
        x->right = b;
        if( b != NULL)
            b->father = x;
     }
}

template <class T>
bool Tree<T>::T_find(T in)
{
   node<T> *t;
   t = root;
   while(t != NULL)
   {
      if(t->key == in)   break;
      if(in > t->key)    t = t->right;
      else if(in < t->key)    t = t->left;
   }
   if(t == NULL) return false;
   else if(t->key == in) return true;
   return true;
}

template<class T>
node<T>* Tree<T>::T_node_find(T in)
{
 node<T> *t;
   t = root;
   while(t != NULL)
   {
      if(t->key == in)   break;
      if(in > t->key)    t = t->right;
      else if(in < t->key)    t = t->left;
   }
   if(t == NULL)
    return NULL;
   else if(t->key == in)
    return t;
   return NULL;
}


template<class T>
 void Tree<T>::Merge(node<T> *p ) {
    if(p != NULL){
    if(p->left) Merge(p->left);
    if(p->right) Merge(p->right);
    Insert(p->key);
    }
}

template<class T>
 void Tree<T>::Split(node<T> *p ) {
    if(p != NULL){
    if(p->left) Split(p->left);
    if(p->right) Split(p->right);
    cout <<p->key;
    Delete(p->key);
    }
}

template<class T>
void Tree<T>::operator+(const Tree<T> & in){
    cout <<"\n\n Dodajemy do siebie drzewa \n";
    Merge(in.root);
}

template<class T>
void Tree<T>::operator-(const Tree<T> & in){
    cout <<"\n\n Odejmujemy od siebie drzewa \n";
    Split(in.root);
}

template<class T>
int Tree<T>::Black_hight(){
    node<T> *p;
    p=root;
    int num=0;
    while(p != NULL){
        if(p->color == black) num++;
        p = p->left;
    }
    return num;
}

template<class T>
int Tree<T>::Size()
{
    return Size(root);
}

template<class T>
int Tree<T>::Size(node<T> * in)
{
    if( in == NULL) return 0;
    else
    {
        int ls,rs;
        ls = Size(in->left);
        rs = Size(in->right);
        return ls+rs+1;
    }
}

template<class T>
void Tree<T>::Display()
{
    Display(root,0);
}

template<class T>
void Tree<T>::Display(node<T>* in, int level)
{
    int i;
    if(in == NULL)
    {
        for(i=0;i<level;i++) cout<<".";
        cout <<"NULL\n";
        return;
    }
    for(i=0;i<level;i++) cout<<".";
    cout <<in->key<<" "<<in->color<<"\n";
    Display(in->left,level+1);
    Display(in->right,level+1);
}

template<class T>
node<T>* Tree<T>::Successor(node<T> *p)
{
      node<T> *y=NULL;
     if(p->left!=NULL)
     {
         y=p->left;
         while(y->right!=NULL)
              y=y->right;
     }
     else
     {
         y=p->right;
         while(y->left!=NULL)
              y=y->left;
     }
     return y;
}

template <class T>
void Tree<T>::Delete(T x)
{
    if(root==NULL)
    {
        cout<<"\nEmpty Tree." ;
        return ;
    }
    node<T> *p;
    p = root;
    node<T> *y=NULL;
    node<T> *q=NULL;
    int found=0;
    while(p!= NULL && found == 0)
    {
        if(p->key == x)
            found = 1;
        if(found == 0)
        {
                if(p->key < x)
                    p = p->right;
                 else
                    p = p->left;
           }
     }
     if(found == 0)
        return ;
     else
     {
         cout<<"\nDeleted Element: "<<p->key;
         cout<<"\nColour: ";
         if(p->color == black)
            cout<<"Black\n";
        else
            cout<<"Red\n";
         if(p->left == NULL || p->right == NULL)
              y=p;
         else
              y=  Successor(p);
         if(y->left!=NULL)
              q = y->left;
         else
         {
              if(y->right!=NULL)
                   q=y->right;
              else
                   q = NULL;
         }
         if(q!=NULL)
              q->father=y->father;
         if(y->father == NULL)
              root = q;
         else
         {
             if(y==y->father->left)
                y->father->left=q;
             else
                y->father->right=q;
         }
         if(y!=p)
         {
             p->color=y->color;
             p->key=y->key;
         }
         if(y->color == black)
             Delete_fix(q);
     }
}

template <class T>
void Tree<T>::Delete_fix(node<T> *p)
{
    if(p!=NULL)
    {
    node<T> *s;
    while(p!=root&&p->color==black)
    {
        if(p->father->left==p)
        {
            s=p->father->right;
            if(s->color == red)
            {
                s->color=black;
                p->father->color=red;
                Rotate_left(p->father);
                s = p->father->right;
            }
            if(s->right->color==black && s->left->color==black)
            {
                s->color = red;
                p=p->father;
            }
            else
            {
                if(s->right->color==black)
                {
                    s->left->color = black;
                    s->color=red;
                    Rotate_right(s);
                    s=p->father->right;
                }
            s->color=p->father->color;
            p->father->color=black;
            s->right->color=black;
            Rotate_left(p->father);
            p = root;
            }
          }
          else
          {
            s=p->father->left;
            if(s->color==red)
            {
                s->color=red;
                p->father->color=red;
                Rotate_right(p->father);
                s=p->father->left;
            }
            if(s->left->color==black && s->right->color==black)
            {
                s->color=red;
                p=p->father;
            }
            else
            {
                if(s->left->color == black)
                {
                    s->right->color=black;
                    s->color=red;
                    Rotate_left(s);
                    s=p->father->left;
                }
                s->color=p->father->color;
                p->father->color=black;
                s->left->color=black;
                Rotate_right(p->father);
                p=root;
            }
          }
       p->color = black;
       root->color=black;
    }
    }
}



/*
template<class T>
void Tree<T>::Delete(node<T>* z)
{
    cout <<" Wejscie: "<<z;
    node<T> *y,*x;

    if(z->left == NULL || z->right == NULL)
        y=z;
    else y = Successor(z);

    if(y->left != NULL)
        x = y->left;
    else x = y->right;

    x->father = y->father;
    if(y->father == NULL)
        root = x;
    else
    {
        if(y == y->father->left)
            y->father->left = x;
        else y->father->right = x;
    }
    if ( y != z)
        z->key = y->key;
    if(y->color == black)
            Delete_fix(x);
}

template<class T>
void Tree<T>::Delete_fix(node<T>* x)
{
    node<T> *w;
    while( x != root && x->color == black)
    {
        if( x == x->father->left)
        {
            w = x->father->right;
            if(w->color == red)
            {
                w->color = black;
                x->father->color = red;
                Rotate_left(x->father);
                w = x->father->right;
            }
            if(w->left->color == black && w->right->color ==black)
            {
                w->color = red;
                x = x->father;
            }
            else if(w->right->color == black)
            {
                w->left->color = black;
                w->color = red;
                Rotate_right(w);
                w = x->father->right;
            }
            w->color = x->father->color;
            x->father->color = black;
            w->right->color = black;
            Rotate_left(x->father);
            x = root;
        }
        else
        {
            w = x->father->left;
            if(w->color == red)
            {
                w->color = black;
                x->father->color = red;
                Rotate_right(x->father);
                w = x->father->left;
            }
            if(w->right->color == black && w->left->color ==black)
            {
                w->color = red;
                x = x->father;
            }
            else if(w->left->color == black)
            {
                w->right->color = black;
                w->color = red;
                Rotate_left(w);
                w = x->father->left;
            }
            w->color = x->father->color;
            x->father->color = black;
            w->left->color = black;
            Rotate_right(x->father);
            x = root;
        }
    }
}
*/
#endif // TREE_H_INCLUDED
