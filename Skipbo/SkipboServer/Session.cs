using SkipboLogic;
using SkipboServerCommands;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboServer
{
    public class Session
    {
        private String mSessionName;
        public String SessionName
        {
            get { return mSessionName; }
        }

        private Player mPlayer1;
        public Player Player1
        {
            set { mPlayer1 = value; }
            get { return mPlayer1; }
        }

        private Player mPlayer2;
        public Player Player2
        {
            set { mPlayer2 = value; }
            get { return mPlayer2; }
        }

        private Game mGame;

        public Session(Player p1, int numDecks)
        {
            mPlayer1 = p1;
            mSessionName = mPlayer1.GameTag;
            mGame = new Game(numDecks);
        }

        public void PlayGame()
        {
            ServerInvoker invoker = new ServerInvoker();
            int turnNumber = 0;
            bool gameOver = false;

            SendInititalData();

            while (!gameOver)
            {
                Player activePlayer = (turnNumber % 2 == 0) ? mPlayer2 : mPlayer1,
                       passivePlayer = (turnNumber % 2 == 0) ? mPlayer1 : mPlayer2;

                invoker.SetCommand(new ReceivePacketCommand(activePlayer));
                SkipboPacket packet = invoker.ExecuteReceiveCommand() as SkipboPacket;

                gameOver = HandlePlayerMessage(packet, passivePlayer);
                turnNumber++;
            }
        }

        private bool HandlePlayerMessage(SkipboPacket packet, Player passivePlayer)
        {
            ServerInvoker invoker = new ServerInvoker();
            mGame = packet.ByteArrayToObject() as Game;
            bool winner = false;

            switch (packet.Message)
            {
                case "DATA":
                    Game copy = mGame.SwapPlayerData();

                    invoker.SetCommand(new SendPacketCommand("DATA", copy, passivePlayer));
                    invoker.ExecuteCommand();
                    break;
                case "WON":
                    invoker.SetCommand(new SendPacketCommand("LOST", mGame, passivePlayer));
                    invoker.ExecuteCommand();
                    winner = true;
                    break;
            }

            return winner;
        }

        private void SendInititalData()
        {
            ServerInvoker invoker = new ServerInvoker(new SendPacketCommand("DATA", mGame, mPlayer1));
            invoker.ExecuteCommand();

            Game copy = mGame.SwapPlayerData();

            invoker.SetCommand(new SendPacketCommand("DATA", copy, mPlayer2));
            invoker.ExecuteCommand();
        }
    }
}
