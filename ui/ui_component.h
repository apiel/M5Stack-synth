#ifndef UI_COMPONENT_H_
#define UI_COMPONENT_H_

class UI_Component
{
public:
    virtual void render() = 0;
    virtual uint8_t update(Event &e) = 0;
};

#endif
