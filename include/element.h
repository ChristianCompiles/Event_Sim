#pragma once
class element
{

public:
    element(){};
    virtual ~element(){};
    virtual void update_state(const int time){};
    virtual void print_results(){};
    virtual void pre_run_check(bool&){};
};
