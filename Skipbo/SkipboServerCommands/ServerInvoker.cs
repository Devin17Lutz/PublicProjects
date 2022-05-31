using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboServerCommands
{
    public class ServerInvoker
    {
        ICommand mCommand;

        public ServerInvoker()
        { }

        public ServerInvoker(ICommand command)
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

        public object ExecuteReceiveCommand()
        {
            mCommand.Execute();
            return (mCommand as ReceivePacketCommand).Packet;
        }
    }
}
