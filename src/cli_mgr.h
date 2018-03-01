#pragma once
#include <string>
#include <map>
#include <vector>

enum ArgType
{
    ARG_INT,
    ARG_FLOAT,
    ARG_STRING,
};

class CmdArgs;
typedef void (*CmdFuncPtr)(CmdArgs *args);

using namespace std;

struct CmdOption
{
    public:
      CmdOption();
      CmdOption(string name,bool hasValue = false);
      CmdOption(string fullName, char shortName, bool hasValue = false);

      string fullName = "";
      char shortName = '\0';
      bool hasValue = false;
};

struct CmdCommand
{
    CmdCommand();
    CmdCommand(string name, CmdFuncPtr func);
    string name;
    CmdFuncPtr func;
};

class CmdArgs
{
    public:
      int optionsCount;
      int argsCount;
      CmdCommand *command;
      CmdOption *options;
      string *args;
      string workspace;

      CmdOption* getOption(string fullName);
};

class CmdManager
{
    public:
      CmdManager();

      map<string, CmdOption> opFullList;
      map<char, CmdOption> opShortList;
      map<string, CmdCommand> cmdList;
      string workspace;
      vector<CmdOption> activeOp;
      CmdCommand activeCmd;
      vector<string> activeArgs;

      void registOp(string name, bool hasValue = false);
      void registOp(string fullName, char shortName, bool hasValue = false);
      void registOp(CmdOption cmdOp);
      CmdCommand registCommand(string name, CmdFuncPtr func);
      void handleArgs(int argsN, char *args[]);
    
    private:
      int argsN;
      char **args;
      int handleShortOp(char *arg, int argsRestN, char *argsRest[]);
      int handleFullOp(char *arg, int argsRestN, char *argsRest[]);
      int handleCommand(char *command, int argsRestN, char *argsRest[]);
};

