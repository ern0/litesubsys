#pragma once

#include <memory> // smart pointres
#include <vector>

namespace com_c
{

class IEvent;
class IEventHandler;

class IListener
{
public:
    /// IListener instances override this function to
    // notifying their registered handlers.
    virtual void notify(std::shared_ptr<IEvent>);

protected:
    /// Vector of registered handlers.
    std::vector<std::unique_ptr<IEventHandler> > mHandlers;
};

} // com_c