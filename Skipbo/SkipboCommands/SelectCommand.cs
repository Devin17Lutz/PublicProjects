using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboCommands
{
    public class SelectCommand : ICommand
    {
        private Game mSkipboGame;

        private String mSelectedPile;

        private bool mIsSelected;

        private bool mSuccessful;
        public bool Successful
        {
            get { return mSuccessful; }
        }

        public SelectCommand(Game skipboGame, String selectedPile, bool isSelected)
        {
            mSkipboGame = skipboGame;
            mSelectedPile = selectedPile;
            mIsSelected = isSelected;
            mSuccessful = false;
        }

        public void Execute()
        {
            mSkipboGame.SetSelected(mSelectedPile, mIsSelected);
            mSuccessful = true;
        }
    }
}
