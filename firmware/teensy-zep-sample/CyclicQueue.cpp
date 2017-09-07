
#include "CyclicQueue.h"
#include "Events.h"

template <typename T>
CyclicQueue<T>::CyclicQueue(size_t size)
    :
        mcapacity(size - 1),
        melements(new CyclicQueue::value_type[size]),
        mpbegin(&melements[0]),
        mpend(&melements[0] + size),
        mpread(const_cast<T*>(mpbegin)),
        mpwrite(const_cast<T*>(mpbegin))
{
}

template <typename T>
CyclicQueue<T>::~CyclicQueue()
{
    delete melements;
}

template <typename T>
size_t CyclicQueue<T>::size() const
{
    if (mpwrite >= mpread)
        return mpwrite - mpread;
    else
        return (mpend - mpread) + (mpwrite - mpbegin);
}

template <typename T>
size_t CyclicQueue<T>::capacity() const
{
    return mcapacity;
}

template <typename T>
bool CyclicQueue<T>::full() const
{
    return size() == capacity();
}

template <typename T>
bool CyclicQueue<T>::empty() const
{
    return size() == 0;
}

template <typename T>
void CyclicQueue<T>::clear()
{
    mpread = const_cast<T*>(mpbegin);
    mpwrite= const_cast<T*>(mpbegin);
}

template <typename T>
int CyclicQueue<T>::enqueue(const_reference_type element)
{
    if(full())
        return CyclicQueue<T>::FULL;

    *mpwrite    = element;
    mpwrite     = mpwrite + 1 < mpend ? mpwrite + 1 : (T*)mpbegin;

    return CyclicQueue<T>::OK;
}

template <typename T>
int CyclicQueue<T>::dequeue(reference_type element)
{
    if(empty())
        return CyclicQueue::EMPTY;

    element = *mpread;
    mpread  = mpread + 1 < mpend ? mpread + 1 : (T*)mpbegin;

    return CyclicQueue::OK;
}


template class CyclicQueue<std::shared_ptr<Event>>;
