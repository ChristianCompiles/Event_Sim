#include "../include/discrete_event_sim.h"
#include <vector>
#include <memory>
#include <iostream>

discrete_event_sim::discrete_event_sim(std::initializer_list<std::shared_ptr<element>> e) : elements(e)
{
      
}

void discrete_event_sim::update_sim(){
    //std::cout << "update_sim() called." << std::endl;
    for (auto &e : elements)
    {
        e->update_state(time);
    }
    ++time;
}

void discrete_event_sim::pre_run_check(){
    
    if (elements.empty()){
        std::cout << "No elements added to sim. Exiting.\n";
        exit(0);
    }
    
    bool ready{true};

    for (auto &e: elements)
    {
        e->pre_run_check(ready);
    }

    if (!ready){
        std::cout << "Sim pre run check failed. Exiting.\n";
        exit(0);
    }

}

void discrete_event_sim::add_element(std::shared_ptr<element> e)
{
    elements.push_back(e);
}

void discrete_event_sim::run(int duration)
{   
    if (duration < 0){
        std::cout << "run time is less than zero. Exiting.\n";
        exit(0);
    }
    
    pre_run_check();

    c_start = std::clock();
    t_start = std::chrono::high_resolution_clock::now();
    
    for (int i{0}; i < duration; ++i)
        {
            //std::cout << "step: " << i << std::endl;
            update_sim();
            
        }

    t_end = std::chrono::high_resolution_clock::now();
    c_end = std::clock();

    sim_complete = true;
}

void discrete_event_sim::print_results(){

    if (!sim_complete){
        std::cout << "Sim did not run. Cannot print results. Exiting.\n";
        exit(0);
    }

    std::cout << "CPU time: "
    << 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC << " ms\n";
    std::cout << "Wall time: "
    << std::chrono::duration<double, std::milli>(t_end - t_start).count()
    << " ms\n";

    for (auto &e : elements)
    {
        e->print_results();
    }
}
