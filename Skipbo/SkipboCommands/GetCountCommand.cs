using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class GetCountCommand : ICommand
    {
        private Game mGame;
        private String mPileName;

        private int mCount;
        public int Count
        {
            set { mCount = value; }
            get { return mCount; }
        }

        public GetCountCommand(Game game, String pileName)
        {
            mGame = game;
            mPileName = pileName;
        }

        public void Execute()
        {
            mCount = mGame.GetPileCount(mPileName);
        }
    }
}
