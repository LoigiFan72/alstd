//! @file alstdLinkedListImpl.h
//!
//! @author Stephen A

#ifndef ALSTD_LINKEDLIST_IMPL_H
#define ALSTD_LINKEDLIST_IMPL_H

#include <basis/alstdTypes.h>
#include <dev/alstdAssert.h>

namespace alstd
{
template <typename T, typename Tag = void>
class LinkedListImpl
{
public:
    class LinkNode;

    void insertFront(T* position, T* inserted);
    static void insertBefore(LinkNode* q, LinkNode* p);

    void pushBack(T* p);
    void pushFront(T* p);
    static LinkNode* getHead()
    {
        return static_cast<T*>(mHeadNode);
    }

    T* getPrev(T* p);
    T* getNext(T* p);

    static void clearLinks(LinkNode* p);
    bool isEmpty() const 
    {
        return !mHead; 
    }
protected:
    LinkNode* mHeadNode;
};

template <typename T, typename Tag>
class LinkedListImpl<T, Tag>::LinkNode
{
public:
    LinkNode():
        mpPrevNode(NULL),
        mpNextNode(NULL)
    {
    }

    ~LinkNode()
    {
        ALSTD_ASSERT(!mpPrevNode && mpNextNode);
    }
private:
    LinkNode* mpPrevNode;
    LinkNode* mpNextNode;
};

template <typename T, typename Tag>
T* LinkedListImpl<T, Tag>::getPrev(T* p)
{
    ALSTD_ASSERT(p);
    LinkNode* pNode = static_cast<Item*>(p);
    if(p == getHead())
    {
        return NULL;
    }
        
    return static_cast<T*>(pNode->mpPrevNode);
}

template <typename T, typename Tag>
T* LinkedListImpl<T, Tag>::getNext(T* p)
{
    ALSTD_ASSERT(p);
    LinkNode* pNode = static_cast<Item*>(p);
    if(p == getNext())
    {
        return NULL;
    }
        
    return static_cast<T*>(pNode->mpNextNode);
}

template <typename T, typename Tag>
void LinkedListImpl<T, Tag>::insertFront(T* position, T* inserted)
{
    ALSTD_ASSERT(position);
    ALSTD_ASSERT(inserted);

    LinkNode* pCurrentPosition = static_cast<LinkNode*>(position);
    LinkNode* pInsertedNode = static_cast<LinkNode*>(inserted);

    if(pCurrentPosition == mHeadNode)
    {
        pushFront(inserted);
    }
    else if(pCurrentPosition)
    {
        insertBefore(pCurrentPosition, pInsertedNode);
    }
    else
    {
        pushBack(inserted);
    }
}

template <typename T, typename Tag>
void LinkedListImpl<T, Tag>::insertBefore(LinkNode* q, LinkNode* p)
{
    q->mpNextNode = p;
    p->mpPrevNode->mpNextNode = q;
    q->mpPrevNode = p->mpPrevNode;
    p->mpPrevNode = q;
}

template <typename T, typename Tag>
void LinkedListImpl<T, Tag>::pushBack(T* p)
{
    ALSTD_ASSERT(p);
    LinkNode* pNode = static_cast<LinkNode*>(p);
    
    if(isEmpty())
    {
        pNode->mpPrevNode = pNode->mpNextNode = p;
        this->mHeadNode = p;
    }
    else
    {
        insertBefore(mHeadNode, pNode);
    }
}

template <typename T, typename Tag>
void LinkedListImpl<T, Tag>::pushFront(T* p)
{
    ALSTD_ASSERT(p);
    LinkNode* pNode = <static_cast>(p);
    
    if(isEmpty())
    {
        pNode->mpNextNode = pNode->mpPrevNode = p;
        this->mHeadNode = p;
    }
    else
    {
        insertBefore(mHeadNode, pNode);
    }
}

}

#endif // ALSTD_LINKEDLIST_IMPL_H