#pragma once
#include "element.h"
#include <iostream>

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
    buffer(int sz, int cap, int rt);
    int const get_size();
    int get_prev_size();
    void update_state(const int time) override;
    int get_items_buffered();
    bool get_buffer_empty();
    void dec_size();
    void print_results() override;
};
