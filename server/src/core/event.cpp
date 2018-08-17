#include "event.h"
#include "event_handler.h"

namespace com_c
{

void IEvent::process()
{
    //std::lock_guard<std::mutex> guard(g_mutex);
    mProcessed = true;
}

bool IEvent::isPorcessed() const
{
    return mProcessed;
}

} // com_c
