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
File *file = NULL;
void open(CmdArgs *args);
void read(CmdArgs *args);
void remove(CmdArgs *args);
void ext(CmdArgs *args);
void help(CmdArgs *args);
void info(CmdArgs *args);
void removeLine();
int main(int argsN,const char *args[])
{
    /*FILE *fp = fopen("test.dat", "w");
    int a = 100;
    char b = 'a';
    long long c = 923048181;
    fwrite(&a, sizeof(int), 1, fp);
    fwrite(&b, sizeof(char), 1, fp);
    fwrite(&c, sizeof(long long), 1, fp);
    fputs("The boy next door.", fp);
    fclose(fp);*/

    cmdMgr = new CmdManager();
    cmdMgr->registCommand("open", open);
    cmdMgr->handleArgs(argsN, args);

    delete cmdMgr;
    cmdMgr = new CmdManager();
    cmdMgr->registCommand("open", open);
    cmdMgr->registCommand("read", read);
    cmdMgr->registCommand("remove", remove);
    cmdMgr->registCommand("exit", ext);
    cmdMgr->registCommand("help", help);
    cmdMgr->registCommand("info", info);
    cmdMgr->registOp("multi", 'm', true);

    while(true)
    {
        cout << "file-b>";
        vector<string> argsInput = readArgs();
        const char *argsInputArr[argsInput.size() + 1];
        argsInputArr[0] = args[0];
        for (int i = 1; i < argsInput.size() + 1;i++)
        {
            argsInputArr[i] = argsInput[i - 1].c_str();
        }
        cmdMgr->handleArgs(argsInput.size() + 1, argsInputArr);
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
    if(args->args.size()<=0)
        throw runtime_error("Arguments error.");
    map<string, DataType> mapDict;
    map<DataType, string> typeName;
    mapDict["char"] = T_CHAR;
    mapDict["byte"] = T_BYTE;
    mapDict["int16"] = mapDict["short"] = T_INT16;
    mapDict["uint16"] = mapDict["ushort"] = T_UINT16;
    mapDict["int"] = mapDict["int32"] = T_INT32;
    mapDict["uint"] = mapDict["uint32"] = T_UINT32;
    mapDict["long"] = mapDict["int64"] = T_INT64;
    mapDict["ulong"] = mapDict["uint64"] = T_UINT64;
    mapDict["string"] = T_STRING;
    typeName[T_CHAR] = "Char";
    typeName[T_BYTE] = "Byte";
    typeName[T_INT16] = "Int16";
    typeName[T_UINT16] = "UInt16";
    typeName[T_INT32] = "Int32";
    typeName[T_UINT32] = "UInt32";
    typeName[T_INT64] = "Int64";
    typeName[T_UINT64] = "UInt64";
    typeName[T_STRING] = "String";
    string typeStr = args->args[0];
    DataType type = mapDict[typeStr];
    Data *data = file->read(type);
    cursorPreLine(1);
    removeLine();
    printGreen("[%d] ", data->position);
    printCyan("[%s] ", typeName[type].c_str());
    printf("%s\n", data->toString());
}
void open(CmdArgs *args)
{
    if(file)
        file->close();
    if(args->args.size()<=0)
        throw runtime_error("Arguments error.");
    file = new File(args->args[0], "r");
    file->open();
}
void remove(CmdArgs *args)
{
    Data *data = file->dataRead.back();
    file->dataRead.pop_back();
    file->setPosition(file->position - data->rawSize);
    delete data;
    #ifdef __linux__
    removeLine();
    cursorUp(1);
    removeLine();
    cursorUp(1);
    removeLine();

    #endif
}
void ext(CmdArgs *args)
{
    file->close();
    exit(0);
}
void help(CmdArgs *args)
{
    printf("usage:\n");
    printf("\topen <path> \topen a file from given path.\n");
    printf("\tread <type> \tread the data as specific type.\n");
    printf("\tremove\t\tremove the last read data.\n");
    printf("\tinfo\t\tget the info.\n");
    printf("Type \"help\" for more infomation.\n\n");
}
void removeLine()
{
    printf("\r");
    printf("                                                ");
    printf("\r");
}
void info(CmdArgs *args)
{
    cout << "Path: \"" << file->path << "\"" << endl;
    cout << "Current position: " << file->position << endl;
    cout << "Total length: " << file->length << "Bytes" << endl << endl;

}