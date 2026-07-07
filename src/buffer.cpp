#include "../include/buffer.h"

buffer::buffer(int sz = 0, int cap = 0, int rt = 0)
{
    if (sz > cap){
        std::cout << "SIZE CANNOT BE GREATER THAN CAPACITY. EXITING.\n";
        exit(1);
    }
    std::cout << "buffer init: " << sz << " " << cap << " " << rt << std::endl;
    capacity = cap;
    rate = rt;
    size = sz;
    items_buffered = size;
    if (sz > 0) {buffer_empty = false;}
}

int const buffer::get_size(){
    return size;
}

int buffer::get_prev_size(){
    return prev_size;
}

void buffer::update_state(const int time)
{
    if (size == 0){buffer_empty = true;} // if buffer holds nothing, set flag so that if item is produced this time step, it will not be used.
    else {buffer_empty = false;}
    if (size +1 > capacity)
    {
        //std::cout << "buffer full.\n";
    }
    else if ((time % rate) == (rate -1)){
        ++size;
        ++items_buffered;
    }
}
    
int buffer::get_items_buffered(){
    return items_buffered;
}

bool buffer::get_buffer_empty(){
    return buffer_empty;
}
void buffer::dec_size()
{
    if (size == 0)
    {
        std::cout << "ERROR decrementing buffer beyond empty. Exiting.";
        exit(1);
    }
    --size;
}
