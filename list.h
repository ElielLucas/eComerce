#ifndef LIST_H
#define LIST_H
#include<node.h>
namespace HEV
{
    template <class Objeto>
    class List
    {
    private:
        Node<Objeto>* head;
        Node<Objeto>* it;
        int N;

    public:
        List();
        bool isEmpty(){ return !N;}
        int size(){ return N;}
        bool insert(Objeto* Dat);
        bool search(Objeto k, Objeto* Dat);
        bool remove(Objeto k, Objeto* Dat);
        Objeto pegarPrimeiro();
        Objeto mostrarIT();
        void definirIT() {it = head;}
        void clear();//ainda nao sei se vou utilizar
    };
    template <class Objeto>
    List<Objeto>::List()
    {
        head=0;
        N=0;
    }
    template <class Objeto>
    Objeto List<Objeto>::pegarPrimeiro()
    {   
         Node<Objeto>* P=head;
         head=head->next;
         N--;
         return Node<Objeto>::desmontaNode(P);
    }

    template<class Objeto>
    Objeto List<Objeto>::mostrarIT()
    {
        Objeto x = it->D;
        it = it->next;
        return x;

    }
    template <class Objeto>
    bool List<Objeto>::insert(Objeto *Dat)
    {
        Node<Objeto>* P = Node<Objeto>::montaNode(Dat);
        if (!P)  return false;

        Node<Objeto>**aux=&head;
        for(;(*aux) && (*Dat) >= (*aux)->D; aux=&((*aux)->next));

        P->next=*aux;
        *aux=P;
        N++;
        it = P;
        return true;
    }
    template <class Objeto>
    bool List<Objeto>::remove(Objeto k, Objeto* Dat)
    {
        Node<Objeto>** P = &head;
        for(;*P && ((*P)->D)!=k;P=&((*P)->next));

        if(!(*P))return false;

        Node<Objeto>*aux=*P;
        *P=aux->next;
        N--;
        it = head;
        *Dat=Node<Objeto>::desmontaNode(aux);
        return true;
    }
    template <class Objeto>
    bool List<Objeto>::search(Objeto k, Objeto *Dat)
    {
        Node<Objeto>* P=head;
        for(;(P->D)!=k;P=P->next);

        if(!P)return false;
        *Dat=P->D;
        return true;
    }
    template <class Objeto>
    void List<Objeto>::clear()
    {
        N=0;
        while(head)
        {
            Node<Objeto>*aux=head;
            head=head->next;
            Node<Objeto>::desmontaNode(aux);
        }
    }
}
#endif // LIST_H
