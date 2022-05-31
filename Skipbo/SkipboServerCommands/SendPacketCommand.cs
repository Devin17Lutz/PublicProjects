using SkipboLogic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboServerCommands
{
    public class SendPacketCommand : ICommand
    {
        private SkipboPacket mPacket;
        public SkipboPacket Packet
        {
            set { mPacket = value; }
            get { return mPacket; }
        }

        private Player mplayer;
        public Player mPlayer
        {
            set { mplayer = value; }
            get { return mplayer; }
        }

        public SendPacketCommand(String message, object data, Player player)
        {
            mPacket = new SkipboPacket(message, data);
            mplayer = player;
        }

        public void Execute()
        {
            mplayer.SendData(mPacket);
        }
    }
}
