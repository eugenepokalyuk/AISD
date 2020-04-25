
template<typename Tk, typename Td>
Node<Tk, Td>::Node() //без параметров
{
    key = 0;
    data = 0;
    left = right = parent = nullptr;
    n = 1;
    color = colors::RED;
}

template<typename Tk, typename Td>
Node<Tk, Td>::Node(Td d, Tk k) //конструктор с параметрами
{
    key = k;
    data = d;
    left = right = parent = nullptr;
    n = 1;
    color = colors::RED;
};
