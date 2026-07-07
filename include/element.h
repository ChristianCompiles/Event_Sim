#pragma once
class element
{

public:
    element(){};
    virtual void update_state(const int time){};
    virtual ~element(){};
};
