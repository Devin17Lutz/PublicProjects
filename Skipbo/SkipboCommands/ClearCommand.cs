using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class ClearCommand : ICommand
    {
        private Game mGame;

        public ClearCommand(Game game)
        {
            mGame = game;
        }

        public void Execute()
        {
            mGame.Selected = null;
            mGame.SelectPile = "";
        }
    }
}
