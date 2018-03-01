#include "cli_mgr.h"

CmdOption::CmdOption()
{
    fullName = "";
    shortName = '\0';
}
CmdOption::CmdOption(string fullName, bool hasValue)
{
    this->fullName = fullName;
    this->hasValue = hasValue;
}
CmdOption::CmdOption(string fullName, char shortName, bool hasValue)
{
    this->fullName = fullName;
    this->shortName = shortName;
    this->hasValue = hasValue;
}

CmdCommand::CmdCommand()
{
    name = "";
    func = NULL;
}
CmdCommand::CmdCommand(string name,CmdFuncPtr func)
{
    this->name = name;
    this->func = func;
}

CmdOption* CmdArgs::getOption(string fullName)
{
    for (int i = 0; i < optionsCount;i++)
    {
        if(options[i].fullName.compare(fullName)==0)
            return &options[i];
    }
    return NULL;
}

void CmdManager::registOp(string name, bool hasValue)
{
    CmdOption op = CmdOption(name, hasValue);
    this->opFullList[name] = op;
}
void CmdManager::registOp(string fullName, char shortName, bool hasValue)
{
    CmdOption op = CmdOption(fullName,shortName,hasValue);
    this->opFullList[fullName] = op;
    this->opShortList[shortName] = op;
}
void CmdManager::registOp(CmdOption cmdOp)
{
    if(cmdOp.fullName.length()>=0)
        this->opFullList[cmdOp.fullName] = cmdOp;
    if(cmdOp.shortName!='\0')
        this->opShortList[cmdOp.shortName] = cmdOp;
}
CmdCommand CmdManager::registCommand(string name,CmdFuncPtr func)
{
    CmdCommand cmd = CmdCommand(name, func);
    this->cmdList[name] = cmd;
    return cmd;
}
void CmdManager::handleArgs(int argsN,char *args[])
{
    this->argsN = argsN;
    this->args = args;
    workspace = string(args[0]);
    for (int i = 1; i < argsN;i++)
    {
        int offset = -1;
        if(args[i][0]=='-')
        {
            if(args[i][1]=='-')
                offset = handleFullOp(args[i], argsN - i, &args[i+1]);
            else
                offset = handleShortOp(args[i], argsN - i, &args[i+1]);
        }
        else 
        {
            offset = handleCommand(args[i], argsN - i, &args[i+1]);
        }
        if(offset < 0)
        {
            activeArgs.push_back(string(args[i]));
        }
    }
}
int CmdManager::handleShortOp(char *arg, int argsRestN, char *argsRest[])
{
    for (int i = 1; i < strlen(arg);i++)
    {
        if(this->opShortList[arg[i]].fullName=="")
            return -1;
        this->activeOp.push_back(this->opShortList[arg[i]]);
    }

    // get value of single option
    if(strlen(arg)==2 && opShortList[arg[1]].hasValue)
    {
        if(argsRest[0][0]=='-')
            return 0;
        
    }
}
int CmdManager::handleFullOp(char *arg, int argsRestN, char *argsRest[])
{
}
int CmdManager::handleCommand(char *command, int argsRestN, char *argsRest[])
{

}