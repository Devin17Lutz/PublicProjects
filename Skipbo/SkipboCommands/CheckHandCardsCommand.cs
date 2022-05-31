using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class CheckHandCardsCommand : ICommand
    {
        private Game mGame;
        private bool mSuccessful;
        public bool Successful
        {
            get { return mSuccessful; }
        }

        public CheckHandCardsCommand(Game game)
        {
            mGame = game;
        }

        public void Execute()
        {
            if (mGame.CheckHandCards())
            {
                mSuccessful = true;
            }
        }
    }
}
