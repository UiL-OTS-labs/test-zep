
#ifndef CYCLIC_QUEUE_H
#define CYCLIC_QUEUE_H

#include <memory>
#include <cstdlib>

template <typename T>
class CyclicQueue {

    public:

        typedef T           value_type;
        typedef T&          reference_type;
        typedef const T&    const_reference_type;

        enum {
            OK,
            FULL,
            EMPTY
        };

        CyclicQueue(size_t size);
        virtual ~CyclicQueue();

        int enqueue(const_reference_type element);
        int dequeue(reference_type element);

        size_t size() const;
        size_t capacity() const;

        bool full() const;
        bool empty() const;
        //bool haveEvent() const;

        void clear();

    private:

        const size_t mcapacity;
        T* melements;

        const T* const mpbegin;
        const T* const mpend;

        T* mpread;
        T* mpwrite;
};



#endif //define CYCLIC_QUEUE_H
