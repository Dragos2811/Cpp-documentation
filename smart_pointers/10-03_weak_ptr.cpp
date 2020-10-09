#include <iostream>
#include <string>
#include <memory>

using namespace std;


void f(weak_ptr<int> &wk)
{
    if (auto shared_copy = wk.lock()) {
        cout << "Cloned shared_ptr: use count = " << shared_copy.use_count() << endl;
        cout << *shared_copy << endl;
    } else {
        cout << "Object has been destroyed" << endl;
    }
}

void test_basic_usage()
{
    shared_ptr<int> si{new int{100}};
    cout << *si << endl;
    
    weak_ptr<int> wk{si};
    cout << "original shared_ptr use count = " << si.use_count() << endl;
    // si.reset();  // if reset, weak_ptr won't be used
    f(wk);
}

void test_circular_ref()
{
    struct Node
    {
        Node() { cout << "Node()" << endl; }
        int m_val{};
        shared_ptr<Node> m_next{};
        ~Node() { cout << "~Node" << endl; }
    };
    auto n1{make_shared<Node>()};
    auto n2{make_shared<Node>()};
    n1->m_next = n2;
    n2->m_next = n1;
}

void test_circular_ref_solution()
{
    struct Node
    {
        Node() { cout << "Node()" << endl; }
        int m_val{};
        weak_ptr<Node> m_next{};
        ~Node() { cout << "~Node" << endl; }
        
        void operation() {
            cout << "Do something" << endl;
            if (auto sh = m_next.lock()) {
                cout << sh->m_val << endl;
            } else {
                cout << "This is the last node" << endl;
            }
        }
    };

    Node *n1{new Node{}};
    Node *n2{new Node{}};
    shared_ptr<Node> pn1{n1};
    shared_ptr<Node> pn2{n2};
    pn1->m_next = pn2;
    pn2->m_next = pn1;
}

int main()
{
    test_basic_usage();
    test_circular_ref();
    test_circular_ref_solution();
        
    return 0;
}
