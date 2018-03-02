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
      const char *rawValue = NULL;
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
      CmdArgs();
      CmdCommand *command;
      vector<CmdOption *> options;
      vector<string> args;
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
      void handleArgs(int argsN,const char *args[]);
    
    private:
      int argsN;
      const char **args;
      int handleShortOp(const char *arg, int argsRestN, const char *argsRest[]);
      int handleFullOp(const char *arg, int argsRestN, const char *argsRest[]);
      int handleCommand(const char *command, int argsRestN, const char *argsRest[]);
      void invoke(CmdCommand cmd);
};

vector<string> readArgs();