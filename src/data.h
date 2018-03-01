#pragma once

enum DataType
{
    T_BYTE = 1,
    T_CHAR = 2,
    T_INT16 = 3,
    T_UINT16 = 4,
    T_INT32 = 5,
    T_UINT32 = 6,
    T_INT64 = 7,
    T_UINT64 = 8,
    T_STRING = 9,
    T_ARRAY = 10,
    T_STRUCT = 11
};
class File;
typedef unsigned char byte;
struct Data
{
    File *file;
    long position = 0;
    DataType type;
    byte *rawData;
    long rawSize = 0;
    size_t length = 1;
    char *toString();
};