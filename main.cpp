#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <variant>

#define year 31536000

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

public:
    buffer(int sz = 0, int cap = 0, int rt = 0)
    {
        std::cout << "buffer init: " << cap << " " << capacity << " " << rate << std::endl;
        capacity = cap;
        rate = rt;
        size = sz;
    }

    int const get_size(){
        return size;
    }

    void update_state(const int time) override
    {
        action_ready = true;
    }
    

};

class machine : public element {
    int rate{0};
    int capacity{3};
    int output_count{0};

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
        if ((time % rate) == 0){
            //std::cout << "time: " << time << ". machine action has occured." << std::endl;
        }
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
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    machine* a = new machine(100,1);
    buffer* b = new buffer; //(5, 3, 1);

    a->add_input(b);

    discrete_event_sim sim;
    sim.add_element(a);
    sim.add_element(b);

    int time_steps = year;

    for (int i{0}; i < time_steps; ++i)
    {
        //std::cout << "step: " << i << std::endl;
        sim.update_sim();
        
    }

    std::clock_t c_end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();

    std::cout << "CPU time: "
    << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n";
    std::cout << "Wall time: "
    << std::chrono::duration<double, std::milli>(t_end - t_start).count()
    << " ms\n";
    
    return 0;
}
