using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboLogic
{
    [Serializable]
    public class Deck
    {
        private int mNumDeck;
        public int NumDeck
        {
            set { mNumDeck = value; }
            get { return mNumDeck; }
        }

        private List<Card> mList;
        public List<Card> CardList
        {
            set { mList = value; }
            get { return mList; }
        }

        private const int mNumCards = 162;

        public Deck()
        {
            mList = new List<Card>();
            mNumDeck = 1;

            CreateDeck();
            mList = Shuffle(mList);
        }

        public Deck(int numDeck)
        {
            mList = new List<Card>();
            mNumDeck = numDeck;

            CreateDeck();
            mList = Shuffle(mList);
        }

        public List<Card> Shuffle(List<Card> list)
        {
            Random random = new Random();
            int rando1 = 0, rando2 = 0, count = list.Count;

            for (int i = 0; i < 100000; i++)
            {
                rando1 = random.Next(0, (count / 2) + 1);
                rando2 = random.Next((count / 2), count);

                Card temp = list[rando1];
                list[rando1] = list[rando2];
                list[rando2] = temp;
            }

            return list;
        }

        public Card GetCard()
        {
            Card topCard = mList[0];
            mList.RemoveAt(0);

            return topCard;
        }

        public void Print()
        {
            for (int i = 0; i < (mNumCards * mNumDeck); i++)
            {
                Console.WriteLine(mList[i].Num);
            }
        }

        public Dictionary<int, int> TestDeck()
        {
            Dictionary<int, int> table = new Dictionary<int, int>();

            for (int i = 0; i < (mNumCards * mNumDeck); i++)
            {
                if (!table.ContainsKey(mList[i].Num))
                {
                    table.Add(mList[i].Num, 1);
                }
                else
                {
                    table[mList[i].Num]++;
                }
            }
            return table;
        }

        private void CreateDeck()
        {
            for (int i = 0; i < 12; i++)
            {
                for (int j = 1; j <= 12; j++)
                {
                    mList.Add(new Card(j, "/Images/" + j + ".png"));
                }
            }

            for (int i = 0; i < mNumDeck; i++)
            {
                for (int j = 0; j < 18; j++)
                {
                    mList.Add(new Card(0, "/Images/0.png"));
                }
            }
        }
    }
}
