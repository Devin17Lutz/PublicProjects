using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class PutDownCommand : ICommand
    {
        private Game mSkipboGame;
        
        private String mTargetPile;
        
        private bool mSuccessful;
        public bool Successful
        {
            get { return mSuccessful; }
        }

        public PutDownCommand(Game skipboGame, String targetPile)
        {
            mSkipboGame = skipboGame;
            mTargetPile = targetPile;
            mSuccessful = false;
        }

        public void Execute()
        {
            if (mSkipboGame.PutDownCard(mTargetPile))
            {
                mSuccessful = true;
            }
        }
    }
}
