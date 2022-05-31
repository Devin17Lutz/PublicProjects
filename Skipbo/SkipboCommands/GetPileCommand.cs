using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class GetPileCommand : ICommand
    {
        private String mPileName;
        private Game mGame;
        private List<Card> mPile;
        public List<Card> Pile
        {
            get { return mPile; }
        }

        public GetPileCommand(Game game, String pileName)
        {
            mGame = game;
            mPileName = pileName;
        }

        public void Execute()
        {
            mPile = mGame.GetPile(mPileName);
        }
    }
}
