
template <typename Tk, typename Td>
colors RBTree<Tk, Td>::red(Node<Tk, Td> *node)
{
    return node ? node->color : colors::BLACK;
} 

template <typename Tk, typename Td>
Node<Tk, Td> *RBTree<Tk, Td>::leftOf(Node<Tk, Td> *node)
{
    return node ? node->left : nullptr;
} 

template <typename Tk, typename Td>
Node<Tk, Td> *RBTree<Tk, Td>::rightOf(Node<Tk, Td> *node)
{
    return node ? node->right : nullptr;
} 

template <typename Tk, typename Td>
Node<Tk, Td> *RBTree<Tk, Td>::parentOf(Node<Tk, Td> *node)
{
    return node ? node->parent : nullptr;
} 

template <typename Tk, typename Td>
void RBTree<Tk, Td>::setColor(Node<Tk, Td> *node, colors color)
{
    if (node)
        node->color = color;
} 

template <typename Tk, typename Td>
RBTree<Tk, Td>::RBTree() : Tree<Tk, Td>()
{
} 

template <typename Tk, typename Td>
RBTree<Tk, Td>::RBTree(const Tree<Tk, Td> &anotherTree) : Tree<Tk, Td>(anotherTree)
{
} 

template <typename Tk, typename Td>
RBTree<Tk, Td>::~RBTree<Tk, Td>()
{
    Tree<Tk, Td>::Clear();
} 

template <typename Tk, typename Td>
Node<Tk, Td> *RBTree<Tk, Td>::Rotate(Node<Tk, Td> *p, Side side)
{
    if (!p)
        return nullptr;
    if (side == LEFT)
    {
        Node<Tk, Td> *r = p->right;
        p->right = r->left;
        if (r->left)
            r->left->parent = p;
        r->parent = p->parent;
        if (!p->parent)
        {
            Tree<Tk, Td>::root = r;
        }
        else if (p->parent->left == p)
        {
            p->parent->left = r;
        }
        else
        {
            p->parent->right = r;
        }
        r->left = p;
        p->parent = r;
        return r;
    }
    else
    {
        Node<Tk, Td> *l = p->left;
        p->left = l->right;
        if (l->right)
            l->right->parent = p;
        l->parent = p->parent;
        if (!p->parent)
        {
            Tree<Tk, Td>::root = l;
        }
        else if (p->parent->right == p)
        {
            p->parent->right = l;
        }
        else
        {
            p->parent->left = l;
        }
        l->right = p;
        p->parent = l;
        return l;
    }
} 

template <typename Tk, typename Td>
bool RBTree<Tk, Td>::Insert(Node<Tk, Td> *&node, Tk key, Td value, Side sw)
{
    Tree<Tk, Td>::cnt++;
    if (!node)
    {
        node = new Node<Tk, Td>(value, key);
        Tree<Tk, Td>::cnt++;
        return true;
    }
    if (red(node->left) && red(node->right))
    {
        node->color = colors::RED;
        node->left->color = colors::BLACK;
        node->right->color = colors::BLACK;
    }
    bool success;
    if (node->key == key)
    {
        return false;
    }
    else if (key < node->key)
    {
        success = Insert(node->left, key, value, LEFT);
        node->left->parent = node;
        if (red(node) && red(node->left) && (sw == RIGHT))
        {
            node = Rotate(node, RIGHT);
        }
        if (red(node->left) && red(node->left->left))
        {
            node = Rotate(node, RIGHT);
            node->color = colors::BLACK;
            node->right->color = colors::RED;
        }
    }
    else
    {
        success = Insert(node->right, key, value, RIGHT);
        node->right->parent = node;
        if (red(node) && red(node->right) && (sw == LEFT))
        {
            node = Rotate(node, LEFT);
        }
        if (red(node->right) && red(node->right->right))
        {
            node = Rotate(node, LEFT);
            node->color = colors::BLACK;
            node->left->color = colors::RED;
        }
    }
    return success;
} 

template <typename Tk, typename Td>
bool RBTree<Tk, Td>::Insert(Td value, Tk key)
{
    Tree<Tk, Td>::cnt = 0;
    bool success = Insert(Tree<Tk, Td>::root, key, value, LEFT);
    if (!success)
        return false;
    Tree<Tk, Td>::root->color = colors::BLACK;
    Tree<Tk, Td>::size++;
    return true;
} 

template <typename Tk, typename Td>
bool RBTree<Tk, Td>::Delete(Tk key)
{
    Tree<Tk, Td>::cnt = 0;
    Node<Tk, Td> *t = Tree<Tk, Td>::root, *x = nullptr;
    while (t != nullptr && t->key != key)
    {
        if (key < t->key)
            t = t->left;
        else
            t = t->right;
        Tree<Tk, Td>::cnt++;
    }
    if (t == nullptr)
        return false;
    Tree<Tk, Td>::cnt++;
    if (t->left && t->right)
    {
        x = Tree<Tk, Td>::Successor(t);
        t->key = x->key;
        t->data = t->data;
        t = x;
    }
    Node<Tk, Td> *replacement = (t->left ? t->left : t->right); 

    if (replacement)
    {
        t->key = replacement->key;
        t->data = replacement->data;
        t->left = t->right = nullptr;
        t = replacement;
    }
    else if (!t->parent)
    {
        Tree<Tk, Td>::root = nullptr;
    }
    else
    {
        if (t->color == colors::BLACK)
            Fixup(t); 

        if (t->parent)
        {
            if (t == t->parent->left)
                t->parent->left = nullptr;
            else if (t == t->parent->right)
                t->parent->right = nullptr;
            t->parent = nullptr;
        }
    }
    delete t;
    Tree<Tk, Td>::size--;
    return true;
} 

template <typename Tk, typename Td>
void RBTree<Tk, Td>::Fixup(Node<Tk, Td> *x)
{
    while (x != Tree<Tk, Td>::root && red(x) == colors::BLACK)
    {
        if (x == leftOf(parentOf(x)))
        {
            Node<Tk, Td> *sib = rightOf(parentOf(x)); 

            if (red(sib) == colors::RED)
            {
                setColor(sib, colors::BLACK);
                setColor(parentOf(x), colors::RED);
                Rotate(parentOf(x), LEFT);
                sib = rightOf(parentOf(x));
            } 

            if (!red(leftOf(sib)) && !red(rightOf(sib)))
            {
                setColor(sib, colors::RED);
                x = parentOf(x);
            }
            else
            {
                if (red(rightOf(sib)) == colors::BLACK)
                {
                    setColor(leftOf(sib), colors::BLACK);
                    setColor(sib, colors::RED);
                    Rotate(sib, RIGHT);
                    sib = rightOf(parentOf(x));
                }
                setColor(sib, red(parentOf(x))); //цвет sib  становится цветом отца x
                setColor(parentOf(x), colors::BLACK);
                setColor(rightOf(sib), colors::BLACK);
                Rotate(parentOf(x), LEFT);
                x = Tree<Tk, Td>::root;
            }
        }
        else
        { // симметрично
            Node<Tk, Td> *sib = leftOf(parentOf(x)); 

            if (red(sib) == colors::RED)
            {
                setColor(sib, colors::BLACK);
                setColor(parentOf(x), colors::RED);
                Rotate(parentOf(x), RIGHT);
                sib = leftOf(parentOf(x));
            } 

            if (red(rightOf(sib)) == colors::BLACK &&
                red(leftOf(sib)) == colors::BLACK)
            {
                setColor(sib, colors::RED);
                x = parentOf(x);
            }
            else
            {
                if (red(leftOf(sib)) == colors::BLACK)
                {
                    setColor(rightOf(sib), colors::BLACK);
                    setColor(sib, colors::RED);
                    Rotate(sib, LEFT);
                    sib = leftOf(parentOf(x));
                }
                setColor(sib, red(parentOf(x)));
                setColor(parentOf(x), colors::BLACK);
                setColor(leftOf(sib), colors::BLACK);
                Rotate(parentOf(x), RIGHT);
                x = Tree<Tk, Td>::root;
            }
        }
    } 

    setColor(x, colors::BLACK);
}
