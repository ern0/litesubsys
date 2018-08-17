#include "listener.h"
#include "event_handler.h"

namespace com_c
{
 
void IListener::notify(std::shared_ptr<IEvent> iEvent)
{
    for ( auto& handler : mHandlers)
    {
        handler->handle(iEvent);
    }   
}

} // com_c