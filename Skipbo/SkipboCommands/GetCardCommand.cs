using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class GetCardCommand : ICommand
    {
        private Game mSkipboGame;
        
        private String mTargetPile;

        private String mImage;
        public String Image
        {
            get { return mImage; }
        }

        private bool mSuccessful;
        public bool Successful
        {
            get { return mSuccessful; }
        }

        public GetCardCommand(Game skipboGame, String targetPile)
        {
            mSkipboGame = skipboGame;
            mTargetPile = targetPile;
            mSuccessful = false;
            mImage = "";
        }

        public void Execute()
        {
            mImage = mSkipboGame.GetCardImage(mTargetPile);
            mSuccessful = true;
        }
    }
}
