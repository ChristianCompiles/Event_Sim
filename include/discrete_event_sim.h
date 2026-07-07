#pragma once
#include <vector>
#include "element.h"

class discrete_event_sim
{
private:
    int time{0};
    std::vector<element*> elements;

public:
    void update_sim();

    void add_element(element* e);

};
