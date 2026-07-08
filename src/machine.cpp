#include "../include/machine.h"

machine::machine(int rt, int cap)
{
    rate = rt;
    cap = cap;
}

machine::machine(){};

void machine::add_input(std::shared_ptr<buffer> buf)
{   std::cout << "adding buffer of size: " << buf->get_size() << std::endl;
    this->inputs.push_back(buf);
}

void machine::update_state(const int time)
{   
    //if (processing) {std::cout << "processing.";}
    //else {std::cout << "not processing.\n";}
    if (processing && (time % rate == (rate - 1)))
    {   
        //std::cout << "finished processing.\n";
        processing = false;
        ++output_count;
        return;
    }

    bool pulled_input = false;
    
    for (auto & i : inputs)
    {
        //std::cout << "looping through inputs.\n";
        
        if (!(i->get_buffer_empty())) // make sure the part wasn't generated this time step
        {
            //std::cout << "input buffer size: " << i->get_size() << std::endl;
            //std::cout << "processing now true;\n";
            processing = true;
            pulled_input = true;
            i->dec_size();
            break;
        }
    }
}

int machine::get_output_count()
{
    return output_count;
}

void machine::print_results(){
    std::cout << "Items machined: " << output_count << std::endl;
}