#include "cli_mgr.h"
#include <cstring>
#include <iostream>

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
CmdCommand::CmdCommand(string name, CmdFuncPtr func)
{
    this->name = name;
    this->func = func;
}

CmdArgs::CmdArgs()
{
}

CmdOption *CmdArgs::getOption(string fullName)
{
    for (int i = 0; i < options.size(); i++)
    {
        if (options[i]->fullName.compare(fullName) == 0)
            return options[i];
    }
    return NULL;
}

CmdManager::CmdManager()
{
}
void CmdManager::registOp(string name, bool hasValue)
{
    CmdOption op = CmdOption(name, hasValue);
    this->opFullList[name] = op;
}
void CmdManager::registOp(string fullName, char shortName, bool hasValue)
{
    CmdOption op = CmdOption(fullName, shortName, hasValue);
    this->opFullList[fullName] = op;
    this->opShortList[shortName] = op;
}
void CmdManager::registOp(CmdOption cmdOp)
{
    if (cmdOp.fullName.length() >= 0)
        this->opFullList[cmdOp.fullName] = cmdOp;
    if (cmdOp.shortName != '\0')
        this->opShortList[cmdOp.shortName] = cmdOp;
}
CmdCommand CmdManager::registCommand(string name, CmdFuncPtr func)
{
    CmdCommand cmd = CmdCommand(name, func);
    this->cmdList[name] = cmd;
    return cmd;
}
void CmdManager::handleArgs(int argsN, char *args[])
{
    this->argsN = argsN;
    this->args = args;
    workspace = string(args[0]);
    for (int i = 1; i < argsN; i++)
    {
        int offset = -1;
        if (args[i][0] == '-')
        {
            if (args[i][1] == '-')
                offset = handleFullOp(args[i], argsN - i, &args[i + 1]);
            else
                offset = handleShortOp(args[i], argsN - i, &args[i + 1]);
        }
        else
        {
            offset = handleCommand(args[i], argsN - i, &args[i + 1]);
        }
        if (offset < 0)
        {
            activeArgs.push_back(string(args[i]));
            offset = 0;
        }
        i += offset;
    }
    if (activeCmd.func != NULL)
        this->invoke(activeCmd);
}
int CmdManager::handleShortOp(char *arg, int argsRestN, char *argsRest[])
{
    for (int i = 1; i < strlen(arg); i++)
    {
        if (this->opShortList[arg[i]].fullName == "")
            return -1;
        this->activeOp.push_back(this->opShortList[arg[i]]);
    }

    // get value of single option
    if (strlen(arg) == 2 && opShortList[arg[1]].hasValue)
    {
        if (argsRest[0][0] == '-')
            return 0;
    }
}
int CmdManager::handleFullOp(char *arg, int argsRestN, char *argsRest[])
{
    string name = string(arg).substr(2);
    CmdOption op = this->opFullList[name];
    if (op.fullName == "")
        return -1;

    if (op.hasValue && argsN > 0 && argsRest[0][0] != '-')
    {
        op.rawValue = argsRest[0];
        this->activeOp.push_back(op);
        return 1;
    }
    this->activeOp.push_back(op);
    return 0;
}
int CmdManager::handleCommand(char *command, int argsRestN, char *argsRest[])
{
    CmdCommand cmd = this->cmdList[string(command)];
    if (cmd.name.length() == 0)
    {
        return -1;
    }
    this->activeCmd = cmd;
    return 0;
}
void CmdManager::invoke(CmdCommand cmd)
{
    CmdArgs *args = new CmdArgs();
    for (int i = 0; i < this->activeArgs.size(); i++)
    {
        args->args.push_back(this->activeArgs[i]);
    }
    for (int i = 0; i < this->activeOp.size(); i++)
    {
        args->options.push_back(&this->activeOp[i]);
    }

    args->workspace = this->workspace;
    args->command = &cmd;
    cmd.func(args);
}

vector<string> readArgs()
{
    vector<string> args; //= new vector<string>();
    char buffer[4096];
    char slice[1024];
    int sliceLength = 0;
    cin.getline(buffer, 4096);
    int length = strlen(buffer);
    for (int i = 0; i < length; i++)
    {
        bool quote = false;
        for (; i < length; i++)
        {
            // Handle quotes
            if(buffer[i]=='\"')
            {
                if(!quote)
                {
                    quote = true;
                    continue;
                }
                else
                    goto AddSlice;
            }

            // Handle space
            if(buffer[i]==' ')
            {
                if(!quote)
                    goto AddSlice;
            }

            if(buffer[i]=='\n')
                break;

            slice[sliceLength++] = buffer[i];
            slice[sliceLength] = '\0';
            continue;

            AddSlice:
                args.push_back(string(slice));
                slice[0] = '\0';
                sliceLength = 0;
                break;
        }
        if(buffer[i]=='\0' || buffer[i]=='\n')
            break;
    }
    return args;
}