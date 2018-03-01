#include <cstdio>
#include <cstring>
#include <memory>
#include "data.h"

using namespace std;

char* Data::toString()
{
    char *str;
    switch(type)
    {
    case T_BYTE:
        str = (char *)malloc(sizeof(char) * 4);
        sprintf(str, "%d", *rawData);
        break;
    case T_INT16:
        str = (char *)malloc(sizeof(char) * 6);
        sprintf(str, "%d", *((short*)rawData));
        break;
    case T_UINT16:
        str = (char *)malloc(sizeof(char) * 6);
        sprintf(str, "%d", *((unsigned short *)rawData));
        break;
    case T_INT32:
        str = (char *)malloc(sizeof(char) * 11);
        sprintf(str, "%ld", *((long *)rawData));
        break;
    case T_UINT32:
        str = (char *)malloc(sizeof(char) * 11);
        sprintf(str, "%ld", *((unsigned long *)rawData));
        break;
    case T_INT64:
        str = (char *)malloc(sizeof(char) * 21);
        sprintf(str, "%lld", *((long long *)rawData));
        break;
    case T_UINT64:
        str = (char *)malloc(sizeof(char) * 21);
        sprintf(str, "%lld", *((unsigned long long *)rawData));
        break;
    case T_CHAR:
        str = (char *)malloc(sizeof(char) * 5);
        sprintf(str, "%c", *rawData);
        break;
    case T_STRING:
        return (char*)rawData;
        break;
    default:
        {
            str = (char *)malloc(sizeof(char) * 1024);
            strcmp(str, "Not supported type.");
        }
    }
    return str;
}