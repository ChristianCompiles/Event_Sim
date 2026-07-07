#include <iostream>
#include <chrono>
#include <ctime>
#include "../include/machine.h"
#include "../include/buffer.h"
#include "../include/discrete_event_sim.h"

#define year 31536000
#define day 24*60*60

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
