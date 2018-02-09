#include "m_pd.h"

#include "ceammc_datatypes.h"

#include "image_data_type.h"

#include "ceammc_dataatom.h"

#include "ceammc_atomlist.h"

#include "json.hpp"

using json = nlohmann::json;

DataTypeImage::DataTypeImage(CImg<unsigned char>* img)
{
    if (!img)
        return;

    _img = new CImg<unsigned char>(*img);
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
    return new DataTypeImage(_img);
}

std::string DataTypeImage::toString() const
{
    if (!_img)
        return "[image: empty]";
    std::string ret = "[image " + std::to_string(_img->width()) + "x" + std::to_string(_img->height()) + "]";
    return ret;
}
