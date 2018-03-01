#include <memory>
#include "file.h"

File::File()
{

}
File::File(string path)
{
    this->path = path;
    this->mode = "r";
}
File::File(string path, string mode)
{
    this->path = path;
    this->mode = mode;
}
void File::open()
{
    this->fp = fopen(path.c_str(), mode.c_str());
}
Data* File::read(DataType type)
{
    Data* data = (Data *)malloc(sizeof(Data));
    data->file = this;
    data->type = type;
    data->length = 1;
    switch(type)
    {
        case T_BYTE:
        case T_CHAR:
            data->rawData = (byte *)malloc(sizeof(char));
            data->rawSize = sizeof(char);
            fread(data->rawData, sizeof(char), 1, fp);
            break;
        case T_INT16:
        case T_UINT16:
            data->rawData = (byte *)malloc(sizeof(short));
            data->rawSize = sizeof(short);
            fread(data->rawData, sizeof(short), 1, fp);
            break;
        case T_INT32:
        case T_UINT32:
            data->rawData = (byte *)malloc(8);
            data->rawSize = sizeof(long);
            fread(data->rawData, sizeof(long), 1, fp);
            break;
        case T_INT64:
        case T_UINT64:
            data->rawData = (byte *)malloc(sizeof(long long));
            data->rawSize = sizeof(long long);
            fread(data->rawData, sizeof(long long), 1, fp);
            break;
        case T_STRING:
            delete data;
            data = this->readString(defaultBufferSize);
            break;
        default:
            throw runtime_error("Not supported.");
    }
    data->position = this->position;
    this->position += data->length;
    this->dataRead.push_back(data);
    return data;
}
Data* File::readString(long maxLength)
{
    Data *data = (Data *)malloc(sizeof(Data));
    data->file = this;
    data->type = T_STRING;
    data->length = maxLength;
    data->rawData = (byte *)malloc(sizeof(char) * maxLength);
    data->position = position;
    fgets((char *)data->rawData, maxLength, fp);
    position = ftell(fp);
    data->rawSize = position - data->position;
    this->dataRead.push_back(data);
    return data;
}
Data** File::readMultiData(DataType type,int count)
{
    Data **dataList = (Data **)malloc(sizeof(Data *) * count);
    for (int i = 0; i < count;i++)
    {
        dataList[i] = this->read(type);
    }
    return dataList;
}
Data** File::readMultitring(long maxLength,int count)
{
    Data **dataList = (Data **)malloc(sizeof(Data *) * count);
    for (int i = 0; i < count; i++)
    {
        dataList[i] = this->readString(maxLength);
    }
    return dataList;
}
long File::setPosition(long pos)
{
    fseek(fp, pos, SEEK_SET);
}
void File::close()
{
    fclose(this->fp);
}
