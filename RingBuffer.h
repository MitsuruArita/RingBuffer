#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#define BUFFER_SIZE     64

template <typename T>
class RingBuffer{
public:
    RingBuffer() : is_overflow(false), index_w(0), index_r(0){};
    bool readForward(T&);
    bool containsForward(const T);
    bool containsBackward(const T);   
    bool append(const T);
    void clear(const T);

protected:
    T ring_buffer[BUFFER_SIZE];
    int index_w;
    int index_r;
    bool is_overflow;
};

#endif
