#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "image_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

using json = nlohmann::json;

DataTypeImage::DataTypeImage(CImg<unsigned char> *img)
{
    if (!img)
        return;

    _img = new CImg<unsigned char>(*img);

//    *_img = img;
}

void DataTypeImage::dump()
{
}

DataType DataTypeImage::type() const
{
    return dataType;
}

AbstractData* DataTypeImage::clone() const
{
    //CImg<unsigned char> *img = new CImg<unsigned char>(*_img);
    return new DataTypeImage(_img);
}

std::string DataTypeImage::toString() const
{
    std::string ret = "[image]";
    return ret;
}
