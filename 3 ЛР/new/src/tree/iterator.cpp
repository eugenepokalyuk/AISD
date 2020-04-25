
template <typename Tk, typename Td>
Tree<Tk, Td>::Iterator::Iterator(Tree<Tk, Td> *thistree)
{
	tree = thistree;
	cur = nullptr;
}

template <typename Tk, typename Td>
void Tree<Tk, Td>::Iterator::begin()
{
	cur = tree->root;
	while (cur != nullptr && cur->left != nullptr)
		cur = cur->left;
}


template <typename Tk, typename Td>
void Tree<Tk, Td>::Iterator::end()
{
	cur = tree->root;
	while (cur != nullptr && cur->right != nullptr)
		cur = cur->right;
}


template <typename Tk, typename Td>
bool Tree<Tk, Td>::Iterator::is_off()
{
	return (cur == nullptr);
}


template <typename Tk, typename Td>
int &Tree<Tk, Td>::Iterator::operator*()
{
	if (is_off())
		throw - 1;
	return cur->data;
}


template <typename Tk, typename Td>
void Tree<Tk, Td>::Iterator::next()
{
	cur = tree->Successor(cur);
}


template <typename Tk, typename Td>
void Tree<Tk, Td>::Iterator::prev()
{
	cur = tree->Predecessor(cur);
}
