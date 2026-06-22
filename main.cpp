#include <iostream>
#include <vector>

class element
{
public:
    void update_state();
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

    void update_state()
    {
        action_ready = true;
    }
    

};

class machine : public element {
    int rate{0};
    int capacity{3};
    int output_count{0};

    std::vector<buffer> inputs; //{0};
    //std::vector<

public:
    machine(int rt, int cap)
    {
        rate = rt;
        cap = cap;
    }

    void add_input(buffer &buf)
    {   std::cout << "adding buffer of size: " << buf.get_size() << std::endl;
        this->inputs.emplace_back(buf);
    } 
    void update_state()
    {
        
    }
};

class discrete_event_sim
{
private:
    int time{0};
    std::vector<element> elements;

public:
    void update_sim(){
        for (auto &e : elements)
        {
            e.update_state();
        }
        ++time;
    }

    void add_element(element& e)
    {
        elements.emplace_back(e);
    }

};

int main(){

    machine a{1,1};
    buffer b{5, 3, 1};

    a.add_input(b);

    discrete_event_sim sim;
    sim.add_element(a);
    sim.add_element(b);

    int time_steps = 1000;

    for (int i{0}; i < time_steps; ++time_steps)
    {
        sim.update_sim();
    }
    

    return 0;
}
