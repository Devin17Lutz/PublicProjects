using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class Invoker
    {
        private ICommand mCommand;

        public Invoker() { }

        public Invoker(ICommand command)
        {
            mCommand = command;
        }

        public void SetCommand(ICommand command)
        {
            mCommand = command;
        }

        public void ExecuteCommand()
        {
            mCommand.Execute();
        }

        public bool ExecutePutDownCommand()
        {
            mCommand.Execute();
            return (mCommand as PutDownCommand).Successful;
        }

        public bool ExecuteDiscardCommand()
        {
            mCommand.Execute();
            return (mCommand as DiscardCommand).Successful;
        }

        public String ExecuteGetCardCommand()
        {
            mCommand.Execute();
            return (mCommand as GetCardCommand).Image;
        }

        public bool ExecuteWinCommand()
        {
            mCommand.Execute();
            return (mCommand as WinCommand).Win;
        }

        public bool ExecuteCheckHandCardsCommand()
        {
            mCommand.Execute();
            return (mCommand as CheckHandCardsCommand).Successful;
        }

        public List<Card> ExecuteGetPileCommand()
        {
            mCommand.Execute();
            return (mCommand as GetPileCommand).Pile;
        }

        public int ExecuteGetPileCountCommand()
        {
            mCommand.Execute();
            return (mCommand as GetCountCommand).Count;
        }
    }
}
