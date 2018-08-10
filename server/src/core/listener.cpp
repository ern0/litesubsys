#include "listener.h"
#include "event_handler.h"

void IListener::notify(std::shared_ptr<IEvent> iEvent)
{
    for ( auto& handler : mHandlers)
    {
        handler->handle(iEvent);
    }   
}