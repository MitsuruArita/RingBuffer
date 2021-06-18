#include "RingBuffer.h"

//readがwriteにおいついたらとまる
template<typename T>
bool RingBuffer<T>::readForward(T& record)
{
    if(index_r == index_w){
        return true;
    }
    record = ring_buffer[index_r]; 
    index_r = (index_r+1)%BUFFER_SIZE;
    return false;
}

template<typename T>
bool RingBuffer<T>::containsForward(const T record)
{
    int record_num = is_overflow ? BUFFER_SIZE : index_w;
    int index_c = is_overflow ? (index_w+1)%BUFFER_SIZE : 0;
    T compare;

    for(int i = 0;i < record_num;i++){
        compare = ring_buffer[(index_c+i)%BUFFER_SIZE];
        if(record == compare)
            return true;
    }
    return false;
}

template<typename T>
bool RingBuffer<T>::containsBackward(const T record)
{
    int record_num = is_overflow ? BUFFER_SIZE : index_w;
    int index_c;
    T compare;
    if(is_overflow){
        index_c = (BUFFER_SIZE+(index_w-1))%BUFFER_SIZE;
    }
    else if(index_w == 0){
        return false;
    }
    else{
        index_c = index_w - 1;
    }
    for(int i = 0;i < record_num;i++){
        compare = ring_buffer[(BUFFER_SIZE+(index_c-i))%BUFFER_SIZE];
        if(record == compare)
            return true;
    }
    return false;
}

//readを気にせず追加
template<typename T>
bool RingBuffer<T>::append(const T record)
{
    ring_buffer[index_w] = record;
    if(index_w == BUFFER_SIZE-1)
        is_overflow = true;
    index_w = (index_w+1)%BUFFER_SIZE;
    return is_overflow;
}

template<typename T>
void RingBuffer<T>::clear(const T init_value)
{
    for(int i=0;i < BUFFER_SIZE;i++){
        ring_buffer[i] = init_value;
    }
    index_w = 0;
    index_r = 0;
}
