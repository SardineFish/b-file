#pragma once
#include <cstdio>
#include <vector>
#include "data.h"

using namespace std;

class File
{
    public:
      string path;
      unsigned long long length;
      unsigned long long position;
      vector<Data*> dataRead;
      File();
      File(string path);
      File(string path, string mode);
      void open();
      void close();
      Data* read(DataType type);
      Data** multiRead(DataType type, int count);

    private:
      FILE *fp;
      string mode;
};