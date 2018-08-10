#pragma once

#include <mutex>
#include <vector>
#include <queue>

std::mutex events_lock;
std::mutex listeners_lock;

class IEvent;
class IListener;

struct UDPPackage;

class EventManager
{
private:
    /// Notify registered listeners.
    void notify();
    /// Remove old, unprocessed events.
    void cleanQueue();
public:
    /// Add new event to the event queue.
    void registerEvent(std::shared_ptr<IEvent> iEvent);
    /// Add new listener to the listener vector.
    void registerListener(IListener& iListener);
    /// Receive event as UDP package;
    void receiveUDPEvent(const UDPPackage& iPackage);

private:
    std::queue< std::shared_ptr<IEvent> > mEventQueue; /// Event queue.
    std::vector<IListener&> mListeners; /// Listeners.

};