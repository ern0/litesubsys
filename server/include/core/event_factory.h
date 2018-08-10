#pragma once

#include <memory>
#include <array>
#include <string>
#include "event.h"

struct UDPData
{
    short unsigned int module;
    short unsigned int category;
    short unsigned int subCategory;
    short unsigned int type;
    short unsigned int specific;
};

struct UDPPackage
{
    UDPData identifier;
    std::string payload;
};

typedef std::shared_ptr<IEvent> (*EventCreator)(std::string);

class EventFactory
{
/**
 * EventFactory is a static class for creating specific events
 * based on the header inforamation from the UDP package. All events are 
 * categorized by their module/category/subCategory/type/specific indices.
 * 
 * EventFactory contains a factory table which stores the specific creator functors. 
 */
    public:

    /// Returns the creator functor based on the package indices.
    static auto getCreator(const UDPData& iData)
    {
        return mCreators[iData.module][iData.category][iData.subCategory][iData.type][iData.specific];
    }

    private:

    /// Fills creator table with default crator.
    static void fillCreatorTable();

    /// Creator table.
    static EventCreator mCreators[8][16][16][16][255];

    /// Flat index of crator table.
    // At the moment there could be 
    // 8 modules
    // 16 categories
    // 16 subCategories
    // 16 types
    // 255 specifics
    // It adds up to 8.355.840 possible events.
    static const int c_flat_dim = 8*16*16*16*255;
};

void EventFactory::fillCreatorTable()
{
    EventCreator* wSingleDimCreators = reinterpret_cast<EventCreator*>(mCreators);
    for (int i = 0; i < c_flat_dim; ++i)
    {    
        /// Fill the factory table with default creator using lambda function     
         wSingleDimCreators[i] = [] (std::string s){return std::make_shared<IEvent>( new NullEvent(s));};
    }
}

///
// Example defeinition of an EventCreator function:
// -----------------------------------------------
// Let's assume that VerySpecificEvent is identified as {0,0,0,0,0}
// In this case the below function should be stored at mCreators[0][0][0][0][0]
//
// std::shared_ptr<IEvent> createVerySpecificEvent( std::string payload)
// {
//     return std::make_shared<IEvent>( new NullEvent(payload));
// }