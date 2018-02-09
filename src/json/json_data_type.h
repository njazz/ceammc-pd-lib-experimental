#ifndef JSON_DATA_TYPES_H
#define JSON_DATA_TYPES_H

#include "ceammc_data.h"
#include "ceammc_atomlist.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace ceammc;

class DataTypeMList;

class DataTypeJSON : public AbstractData {
    json _json = "{}"_json;

    //static DataTypeMList* mListFromJSONArray(nlohmann::json j);
public:
    static const DataType dataType = 200;

    explicit DataTypeJSON(std::string jsonString);

    virtual void dump() override;
    virtual DataType type() const override;
    virtual AbstractData* clone() const override;
    virtual std::string toString() const override;

    const nlohmann::json json() { return _json; }
     void set(std::string key, nlohmann::json j){_json[key] = j;}

    DataTypeMList* toMList();
    AtomList* toList();

    void fromList(const AtomList &a);

    void toFile( std::string fileName);
    void fromFile( std::string fileName);



};

#endif // SDIF_DATA_TYPES_H
