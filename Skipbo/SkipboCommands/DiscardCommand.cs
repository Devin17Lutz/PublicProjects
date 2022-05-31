using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class DiscardCommand : ICommand
    {
        private Game mSkipboGame;
        
        private String mTargetPile;
        
        private bool mSuccessful;
        public bool Successful
        {
            get { return mSuccessful; }
        }

        public DiscardCommand(Game skipboGame, String targetPile)
        {
            mSkipboGame = skipboGame;
            mTargetPile = targetPile;
            mSuccessful = false;
        }

        public void Execute()
        {
            if (mSkipboGame.TryDiscard(mTargetPile))
            {
                mSuccessful = true;
            }
        }
    }
}
