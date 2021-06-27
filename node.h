#ifndef NODE_H
#define NODE_H
namespace HEV
{
    template <class Thing>
    class Node
    {
        public:
        Thing D;
        Node<Thing> *next;
        Node();

        static Node<Thing>* montaNode(Thing *Dat);
        static Thing desmontaNode(Node<Thing> *P);
    };

    template <class Thing>
    Node<Thing>::Node()
    {
        next=0;
    }
    template <class Thing>
    Node<Thing>* Node<Thing>::montaNode(Thing *Dat)
    {
        Node<Thing>* P=new Node;
        if(P) P->D=*Dat;
        return P;
    }
    template <class Thing>
    Thing Node<Thing>::desmontaNode(Node<Thing> *P)
    {
        Thing x=P->D;
        delete P;
        return x;
    }
}
#endif // NODE_H
