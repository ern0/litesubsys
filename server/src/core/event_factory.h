#pragma once

#include <memory>
#include <array>
#include <string>
#include "event.h"

namespace com_c
{

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

using EventCreator = std::shared_ptr<IEvent> (*)(std::string);

///
/// EventFactory is a static class for creating specific events
/// based on the header inforamation from the UDP package. All events are
/// categorized by their module/category/subCategory/type/specific indices.
/// EventFactory contains a factory table which stores the specific creator functors.
///
class EventFactory
{

    public:

    /// @brief Returns the creator functor based on the package indices.
    /// @param iData Input data
    /// @return Event creator for specific event
    static EventCreator getCreator(const UDPData& iData);

    private:

    /// Fills creator table with default crator.
    static void fillCreatorTable();

    /// Creator table.
    static EventCreator mCreators[8][16][16][16][255];

    static bool mCreated;

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

} // com_c
