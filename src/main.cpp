#include <iostream>
#include <memory>

#include "../include/machine.h"
#include "../include/buffer.h"
#include "../include/discrete_event_sim.h"

#define year 31536000
#define day 24*60*60

int main(){
    std::shared_ptr<machine> a(new machine(1,1));
    std::shared_ptr<buffer>  b(new buffer(1, 1, 100));

    a->add_input(b);

    discrete_event_sim sim{a, b};
    sim.run(day);
    sim.print_results();

    
    return 0;
}
