#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <variant>

#define year 31536000
#define day 24*60*60

class element
{

public:
    element(){};
    virtual void update_state(const int time){};
    virtual ~element(){};
};

class buffer : public element {
private:
    int capacity{0};
    int rate{0};
    int size{0};
    bool action_ready{false};
    int items_buffered{0};
    int prev_size{0};
    bool buffer_empty{true};

public:
    buffer(int sz = 0, int cap = 0, int rt = 0)
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

    int const get_size(){
        return size;
    }

    int get_prev_size(){
        return prev_size;
    }

    void update_state(const int time) override
    {
        if (size == 0){buffer_empty = true;}
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
    int get_items_buffered(){
        return items_buffered;
    }

    bool get_buffer_empty(){
        return buffer_empty;
    }
    void dec_size()
    {
        if (size == 0)
        {
            std::cout << "ERROR decrementing buffer beyond empty. Exiting.";
            exit(1);
        }
        --size;
    }
    

};

class machine : public element {
    int rate{0};
    int capacity{3};
    int output_count{0};
    bool processing{false};

    std::vector<buffer*> inputs;
    

public:
    machine(int rt, int cap)
    {
        rate = rt;
        cap = cap;
    }
    machine(){}

    void add_input(buffer* buf)
    {   std::cout << "adding buffer of size: " << buf->get_size() << std::endl;
        this->inputs.push_back(buf);
    } 
    void update_state(const int time) override
    {   
        //if (processing) {std::cout << "processing.";}
        //else {std::cout << "not processing.\n";}
        if (processing && (time % rate == (rate - 1)))
        {   
            //std::cout << "finished processing.\n";
            processing = false;
            ++output_count;
            return;
        }

        bool pulled_input = false;
        
        for (auto & i : inputs)
        {
            //std::cout << "looping through inputs.\n";
            
            if (!(i->get_buffer_empty())) // make sure the part wasn't generated this time step
            {
                //std::cout << "input buffer size: " << i->get_size() << std::endl;
                //std::cout << "processing now true;\n";
                processing = true;
                pulled_input = true;
                i->dec_size();
                break;
            }
        }
    }

    int get_output_count()
    {
        return output_count;
    }
};

class discrete_event_sim
{
private:
    int time{0};
    std::vector<element*> elements;

public:
    void update_sim(){
        //std::cout << "update_sim() called." << std::endl;
        for (auto &e : elements)
        {
           e->update_state(time);
        }
        ++time;
    }

    void add_element(element* e)
    {
        elements.push_back(e);
    }

};

int main(){
    // std::clock_t c_start = std::clock();
    // auto t_start = std::chrono::high_resolution_clock::now();

    machine* a = new machine(1,1);
    buffer* b = new buffer(0, 1, 100);

    a->add_input(b);

    discrete_event_sim sim;
    sim.add_element(b);
    sim.add_element(a);

    int time_steps = day;

    for (int i{0}; i < time_steps; ++i)
    {
        //std::cout << "step: " << i << std::endl;
        sim.update_sim();
        
    }

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    // std::cout << "CPU time: "
    // << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n";
    // std::cout << "Wall time: "
    // << std::chrono::duration<double, std::milli>(t_end - t_start).count()
    // << " ms\n";


    std::cout << "items machined: " << a->get_output_count() << std::endl; 
    std::cout << "items buffered: " << b->get_items_buffered() << std::endl;
    return 0;
}
