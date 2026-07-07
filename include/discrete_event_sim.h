#pragma once
#include <vector>
#include <memory>
#include "element.h"

class discrete_event_sim
{
private:
    int time{0};
    std::vector<std::shared_ptr<element>> elements;

public:
    void update_sim();

    void add_element(std::shared_ptr<element> e);

};
