#include "event_manager.h"
#include "event.h"
#include "listener.h"
#include "event_factory.h"
#include "socket.h"

#include <memory>

using namespace com_c;
int main(int argc, char* argv[])
{
	printf("made.\n");

    auto wEventManager = std::make_unique<EventManager>();
}


namespace com_c
{

void EventManager::notify()
{
    std::lock_guard<std::mutex> guard(events_lock);
    while( !mEventQueue.empty() )
    {
        auto wEvent = mEventQueue.front();
        for( auto listener : mListeners)
        {
            listener->notify(wEvent);
        }
        if( !wEvent->isPorcessed())
        {
            /// TODO: Register/Log/Store unprocessed events
            registerEvent(wEvent);
        }
        mEventQueue.pop();
    }
}

void EventManager::cleanQueue()
{
    /// TODO: figure out logic
    // of removing old events from event queue
}

void EventManager::registerEvent(std::shared_ptr<IEvent> iEvent)
{
    std::lock_guard<std::mutex> guard(events_lock);
    mEventQueue.push(iEvent);
}

void EventManager::registerListener(std::shared_ptr<IListener> iListener)
{
    std::lock_guard<std::mutex> guard(listeners_lock);
    mListeners.push_back(iListener);
}

void EventManager::receiveUDPEvent(const UDPPackage& iPackage)
{
    registerEvent(EventFactory::getCreator(iPackage.identifier)(iPackage.payload));
}

void EventManager::listen()
{
    while(true)
    {
        listenUDPEvent();
        listenInternalEvent();
    }
}

void EventManager::listenUDPEvent()
{

}

void EventManager::listenInternalEvent()
{

}

} // com_c
