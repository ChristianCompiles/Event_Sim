#pragma once
#include <vector>
#include <memory>
#include <memory>
#include <chrono>
#include <ctime>
#include "element.h"

class discrete_event_sim
{
private:
    int time{0};
    std::vector<std::shared_ptr<element>> elements;
    std::clock_t c_start; 
    std::chrono::time_point<std::chrono::high_resolution_clock> t_start;
    std::clock_t c_end = std::clock();
    std::chrono::time_point<std::chrono::high_resolution_clock> t_end;

    void update_sim();

public:
    discrete_event_sim(std::initializer_list<std::shared_ptr<element>> e);

    void add_element(std::shared_ptr<element> e);

    void run(int duration);
    void print_results();

};
