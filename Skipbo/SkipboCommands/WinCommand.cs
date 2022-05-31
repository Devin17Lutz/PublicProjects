using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class WinCommand : ICommand
    {
        private Game mSkipboGame;
        private bool mWin;
        public bool Win
        {
            get { return mWin; }
        }

        public WinCommand(Game skipboGame)
        {
            mSkipboGame = skipboGame;
            mWin = false;
        }

        public void Execute()
        {
            mWin = mSkipboGame.CheckWinner();
        }
    }
}
