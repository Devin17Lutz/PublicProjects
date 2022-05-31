using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class DrawCommand : ICommand
    {
        private Game mSkipboGame;

        public DrawCommand(Game skipboGame)
        {
            mSkipboGame = skipboGame;
        }

        public void Execute()
        {
            mSkipboGame.DrawCards();
        }
    }
}
