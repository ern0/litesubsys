#pragma once

#include <memory>  // smart pointres

namespace com_c
{

class IEvent;

class IEventHandler
{
    public:
    /// handle an event. All handler should handle corresponding events
    // only and leave other events unprocessed.
    // example:
    // event: ButtonPressed, handler: ButtonPressedHandler

    // auto wEvent = iEvent->interpretAs<ButtonPressed>();

    // if (NULL != wEvent)
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

} // com_c