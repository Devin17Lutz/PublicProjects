using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboLogic
{
    [Serializable]
    public class Game
    {
        private Deck mDeck;
        public Deck Deck
        {
            set { mDeck = value; }
            get { return mDeck; }
        }

        private Dictionary<String, Stack<Card>> mPiles;
        public Dictionary<String, Stack<Card>> Piles
        {
            set { mPiles = value; }
            get { return mPiles; }
        }

        private Card mSelected;
        public Card Selected
        {
            set { mSelected = value; }
            get { return mSelected; }
        }

        private String mSelectPile;
        public String SelectPile
        {
            set { mSelectPile = value; }
            get { return mSelectPile; }
        }

        public Game()
        {
            mDeck = new Deck();
            mPiles = CreatePiles();
            DistributeDeck();

            mSelected = null;
            mSelectPile = "";
        }

        public Game(int numDecks)
        {
            mDeck = new Deck(numDecks);
            mPiles = CreatePiles();
            DistributeDeck();

            mSelected = null;
            mSelectPile = "";
        }

        public bool CheckHandCards()
        {
            bool areMissing = false;

            if (mPiles["P1H1Card"].Count == 0 || mPiles["P1H2Card"].Count == 0 || mPiles["P1H3Card"].Count == 0 ||
                mPiles["P1H4Card"].Count == 0 || mPiles["P1H5Card"].Count == 0)
            {
                areMissing = true;
            }

            return areMissing;
        }

        public bool CheckWinner()
        {
            return mPiles["P1Pile"].Count == 0;
        }

        public void DrawCards()
        {
            for (int i = 1; i <= 5; i++)
            {
                if (mPiles["P1H" + i + "Card"].Count == 0)
                {
                    mPiles["P1H" + i + "Card"].Push(mPiles["DrawPile"].Pop());
                }
            }
        }

        public String GetCardImage(String targetPile)
        {
            try
            {
                return mPiles[targetPile].Peek().FaceCard;
            }
            catch(Exception)
            {
                return "WHITE";
            }
        }

        public List<Card> GetPile(String pileName)
        {
            return new List<Card>(mPiles[pileName]);
        }

        public void SetSelected(String selectedPile, bool isSelected)
        {
            if (isSelected)
            {
                mSelectPile = selectedPile;
                mSelected = mPiles[mSelectPile].Peek();
            }
            else
            {
                mSelectPile = "";
                mSelected = null;
            }
        }

        public int GetPileCount(String pileName)
        {
            return mPiles[pileName].Count;
        }

        public bool PutDownCard(String targetPile)
        {
            Card targetTopCard = null;
            bool putDown = false;
            int pileCount = mPiles[targetPile].Count;

            if (mSelected == null)
            {
                return false;
            }

            if (pileCount != 0)
            {
                targetTopCard = mPiles[targetPile].Peek();
            }

            if ((mSelected.Num == 1 && targetTopCard == null) ||
                mSelected.Num == 0 || (targetTopCard != null) && mSelected.Num == (pileCount + 1))
            {
                mPiles[mSelectPile].Pop();
                mPiles[targetPile].Push(Selected);

                if (mPiles[targetPile].Count == 12)
                {
                    MoveCards(targetPile);
                }

                mSelected = null;
                mSelectPile = "";
                putDown = true;
            }

            return putDown;
        }

        public bool TryDiscard(String targetPile)
        {
            if (mSelected == null)
            {
                return false;
            }

            mPiles[targetPile].Push(mSelected);
            mPiles[mSelectPile].Pop();

            mSelected = null;
            mSelectPile = "";

            return true;
        }

        private void MoveCards(String targetPile)
        {
            List<Card> list = mPiles["DrawPile"].Concat(mPiles[targetPile]).ToList();
            mPiles["DrawPile"] = new Stack<Card>(mDeck.Shuffle(list));
            mPiles[targetPile] = new Stack<Card>();
        }

        private Dictionary<String, Stack<Card>> CreatePiles()
        {
            Dictionary<String, Stack<Card>> piles = new Dictionary<String, Stack<Card>>();

            piles.Add("P1Pile", new Stack<Card>());
            piles.Add("P2Pile", new Stack<Card>());

            piles.Add("P1H1Card", new Stack<Card>());
            piles.Add("P1H2Card", new Stack<Card>());
            piles.Add("P1H3Card", new Stack<Card>());
            piles.Add("P1H4Card", new Stack<Card>());
            piles.Add("P1H5Card", new Stack<Card>());

            piles.Add("P2H1Card", new Stack<Card>());
            piles.Add("P2H2Card", new Stack<Card>());
            piles.Add("P2H3Card", new Stack<Card>());
            piles.Add("P2H4Card", new Stack<Card>());
            piles.Add("P2H5Card", new Stack<Card>());

            piles.Add("P1D1Pile", new Stack<Card>());
            piles.Add("P1D2Pile", new Stack<Card>());
            piles.Add("P1D3Pile", new Stack<Card>());
            piles.Add("P1D4Pile", new Stack<Card>());

            piles.Add("P2D1Pile", new Stack<Card>());
            piles.Add("P2D2Pile", new Stack<Card>());
            piles.Add("P2D3Pile", new Stack<Card>());
            piles.Add("P2D4Pile", new Stack<Card>());

            piles.Add("UpPile", new Stack<Card>());
            piles.Add("DownPile", new Stack<Card>());
            piles.Add("LeftPile", new Stack<Card>());
            piles.Add("RightPile", new Stack<Card>());

            return piles;
        }

        private void DistributeDeck()
        {
            for (int i = 0; i < 60; i++)
            {
                if (i % 2 == 0)
                {
                    mPiles["P1Pile"].Push(mDeck.GetCard());
                }
                else
                {
                    mPiles["P2Pile"].Push(mDeck.GetCard());
                }
            }

            for (int i = 1; i <= 10; i++)
            {
                if (i <= 5)
                {
                    mPiles["P1H" + i + "Card"].Push(mDeck.GetCard());
                }
                else
                {
                    mPiles["P2H" + (i - 5) + "Card"].Push(mDeck.GetCard());
                }
            }

            mPiles["DrawPile"] = new Stack<Card>(mDeck.CardList);
            mDeck.CardList = null;
        }

        public Game SwapPlayerData()
        {
            Game copy = this;
            String[] keys = mPiles.Keys.ToArray();
            List<String> player1 = new List<String>(), player2 = new List<String>();

            foreach (String str in keys)
            {
                if (str.Contains("P1"))
                {
                    player1.Add(str);
                }
                else if (str.Contains("P2"))
                {
                    player2.Add(str);
                }
            }

            for (int i = 0; i < player1.Count; i++)
            {
                Stack<Card> temp = copy.mPiles[player1[i]];
                copy.mPiles[player1[i]] = copy.mPiles[player2[i]];
                copy.mPiles[player2[i]] = temp;
            }
            return copy;
        }
    }
}
