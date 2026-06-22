#include <iostream>
#include <vector>

class element
{
public:
    virtual void update_state();
};

class buffer : element {
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

    void update_state override
    {
        action_ready = true;
    }
    

};

class machine : element {
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
};

class discrete_event_sim
{
    private:
    int time{0};
    std::vector<element> elements;

    void update_sim(){
        for (auto &e : elements)
        {
            e.update_state();
        }
        ++time;
    }

};

int main(){

    machine a{1,1};
    buffer b{5, 3, 1};

    a.add_input(b);

    return 0;
}
