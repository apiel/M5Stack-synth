#ifndef UI_BASE_H_
#define UI_BASE_H_

class UI_Base
{
public:
    virtual void render() = 0;
    virtual bool update(Event &e) = 0;
};

#endif
