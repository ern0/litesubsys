#include "event.h"
#include "event_handler.h"

void IEvent::process()
{
    std::lock_guard<std::mutex> guard(g_mutex);
    mProcessed = true;
}

bool IEvent::isPorcessed() const
{
    return mProcessed;
}