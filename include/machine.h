#pragma once
#include <vector>
#include <memory>
#include "element.h"
#include "buffer.h"

class machine : public element {
    int rate{0};
    int capacity{3};
    int output_count{0};
    bool processing{false};

    std::vector<std::shared_ptr<buffer>> inputs;
    
public:
    machine(int rt, int cap);
    machine();
    void add_input(std::shared_ptr<buffer> buf);
    void update_state(const int time) override;
    int get_output_count();
};
