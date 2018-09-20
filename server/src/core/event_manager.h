#pragma once

#include <mutex>
#include <vector>
#include <queue>
#include <memory>

std::mutex events_lock;
std::mutex listeners_lock;

// int main(int argc, char* argv[]);

namespace com_c
{

class IEvent;
class IListener;

struct UDPPackage;

class EventManager
{
private:
    /// @breif Notify registered listeners.
    void notify();
    /// @breif Remove old, unprocessed events.
    void cleanQueue();
    /// @breif Listen UDP
    void listenUDPEvent();
    /// @breif Listen internal event
    void listenInternalEvent();
public:
    /// @breif Add new event to the event queue.
    void registerEvent(std::shared_ptr<IEvent> iEvent);
    /// @breif Add new listener to the listener vector.
    void registerListener(std::shared_ptr<IListener> iListener);
    /// @breif Receive event as UDP package;
    void receiveUDPEvent(const UDPPackage& iPackage);
    /// @breif Listen for events
    void listen();

private:
    std::queue< std::shared_ptr<IEvent> > mEventQueue; /// Event queue.
    std::vector< std::shared_ptr<IListener> > mListeners; /// Listeners.

};

} // com_c
