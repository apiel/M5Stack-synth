#ifndef UI_COMPONENT_H_
#define UI_COMPONENT_H_

class UI_Component
{
public:
    virtual void render() = 0;
    virtual bool update(Event &e) = 0;
};

#endif
