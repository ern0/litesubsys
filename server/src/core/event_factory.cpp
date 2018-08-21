#include "event_factory.h"

namespace com_c
{

bool EventFactory::mCreated = false;
EventCreator EventFactory::mCreators[8][16][16][16][255];

EventCreator EventFactory::getCreator(const UDPData& iData)
{
    if(!mCreated)
    {
        fillCreatorTable();
    }
    return mCreators[iData.module][iData.category][iData.subCategory][iData.type][iData.specific];
}

void EventFactory::fillCreatorTable()
{
    EventCreator* wSingleDimCreators = reinterpret_cast<EventCreator*>(mCreators);
    EventCreator wTmp = [] (std::string s) 
    { 
        return std::shared_ptr<IEvent>( new NullEvent(s) );
    };

    for (int i = 0; i < c_flat_dim; ++i)
    {
        /// Fill the factory table with default creator using lambda function
        
        wSingleDimCreators[i] = wTmp;
    }
    mCreated = true;
}
};