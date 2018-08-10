#pragma once

#include <memory>  // smart pointres
class IEvent;

class IEventHandler
{
    public:
    /// handle an event. All handler should handle corresponding events
    // only and leave other events unprocessed.
    // example:
    // event: ButtonPressed, handler: ButtonPressedHandler
    //
    // auto wEvent = std::dynamic_pointer_cast<ButtonPressed>(iEvent);
    // if(NULL != wEvent)
    // {
    //     doSomethingImportant();
    //     wEvent->process();
    // }
    // else
    // {
    //     // pass;
    // }
    virtual void handle(std::shared_ptr<IEvent>) = 0;
};