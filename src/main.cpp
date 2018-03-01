#include <iostream>
#include <string>
#include <memory>
#include "CSI.h"
#include "file.h"
#include "data.h"

#define MAX_PATH_LEN 2048

using namespace std;

int main(int argsN, char *args[])
{
    string filePath = "test.dat";
    /*if (argsN <= 1)
    {
        filePath = (char *)malloc(sizeof(char) * MAX_PATH_LEN);
        cout << "file:";
        cin >> filePath;
    }
    else
        filePath = args[1];*/
    FILE *fp = fopen("test.dat", "w");
    int a = 0;
    char b = 'a';
    long long c = 923048181;
    fwrite(&a, sizeof(int), 1, fp);
    fwrite(&b, sizeof(char), 1, fp);
    fwrite(&c, sizeof(long long), 1, fp);
    fputs("The boy next door.", fp);
    fclose(fp);
    File file = File(filePath);
    file.open();
    Data *data = file.read(T_INT32);
    printf("%s\n", data->toString());
    data = file.read(T_CHAR);
    printf("%s\n", data->toString());
    data = file.read(T_UINT64);
    printf("%s\n", data->toString());
    data = file.readString(1024);
    printf("%s\n", data->toString());
    return 0;
}