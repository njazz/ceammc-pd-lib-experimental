#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "../src/conv/conv_image.h"
#include "../src/conv/conv_json.h"
#include "../src/conv/conv_list.h"
#include "../src/conv/conv_mlist.h"

TEST_CASE("Data type converters: JSON", "[converters]")
{

    SECTION("json<->mlist")
    {
        DataTypeJSON* json = new DataTypeJSON("{\"list\":[1,2,3]}");

        DataTypeMList* mlist = ConvJSON::toMList(json);
        DataTypeJSON* jsonOut = ConvMList::toJSON(mlist);

        std::string outStr = jsonOut->json().dump();

        REQUIRE(!strncmp(outStr.c_str(), "{\"list\":[1,2,3]}", outStr.length()));
    }
}

TEST_CASE("Data type converters: mlist", "[converters]")
{
    SECTION("mlist<->img")
    {
        DataTypeMList* mlist = new DataTypeMList(new AtomList);
    }
}

TEST_CASE("Data type converters: image", "[converters]")
{
}
