using SkipboLogic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboServerCommands
{
    public class ReceivePacketCommand : ICommand
    {
        private SkipboPacket mPacket;
        public SkipboPacket Packet
        {
            set { mPacket = value; }
            get { return mPacket; }
        }

        private Player _player;
        public Player mPlayer
        {
            set { _player = value; }
            get { return _player; }
        }

        public ReceivePacketCommand(Player player)
        {
            mPlayer = player;
        }

        public void Execute()
        {
            mPacket = mPlayer.GetData() as SkipboPacket;
        }
    }
}
