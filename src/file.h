#pragma once
#include <cstdio>
#include <vector>
#include "data.h"

using namespace std;

class File
{
    public:
      string path;
      long length = 0;
      long position = 0;
      long defaultBufferSize = 1024;
      vector<Data*> dataRead;
      File();
      File(string path);
      File(string path, string mode);
      void open();
      void close();
      Data* read(DataType type);
      Data *readString(long maxLength);
      Data** readMultiData(DataType type, int count);
      Data **readMultitring(long maxLength, int count);
      long setPosition(long pos);

    private:
      FILE *fp;
      string mode;
};