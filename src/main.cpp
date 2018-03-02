#include <iostream>
#include <string>
#include <memory>
#include "CSI.h"
#include "file.h"
#include "data.h"
#include "cli_mgr.h"

#define MAX_PATH_LEN 2048

using namespace std;

CmdManager *cmdMgr;
File *file;
void open(CmdArgs *args);
void read(CmdArgs *args);
void remove(CmdArgs *args);
int main(int argsN, char *args[])
{
    cmdMgr = new CmdManager();
    cmdMgr->registCommand("open", open);
    cmdMgr->registCommand("read", read);
    cmdMgr->registCommand("remove", remove);
    cmdMgr->registOp("multi", 'm', true);
    cmdMgr->handleArgs(argsN, args);


    while(true)
    {
        vector<string> argsInput = readArgs();
    }
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
void read(CmdArgs *args)
{

}
void open(CmdArgs *args)
{
    if(args->args.size()<=0)
        throw runtime_error("Arguments error.");
    file = new File(args->args[0], "r");
    file->open();
}
void remove(CmdArgs *args)
{

}