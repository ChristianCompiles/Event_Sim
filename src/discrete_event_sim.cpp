#include "../include/discrete_event_sim.h"

void discrete_event_sim::update_sim(){
    //std::cout << "update_sim() called." << std::endl;
    for (auto &e : elements)
    {
        e->update_state(time);
    }
    ++time;
}
void discrete_event_sim::add_element(std::shared_ptr<element> e)
{
    elements.push_back(e);
}
