using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SkipboLogic
{
    [Serializable]
    public class Card
    {
        private static int mID = 0;
        public int ID
        {
            get { return mID; }
        }

        private int mNum;
        public int Num
        {
            set { mNum = value; }
            get { return mNum; }
        }

        private String mFaceCard;
        public String FaceCard
        {
            set { mFaceCard = value; }
            get { return mFaceCard; }
        }

        private const String mBackCard = "/Images/back.png";
        public String BackCard
        {
            get { return mBackCard; }
        }

        public Card()
        { }

        public Card(int num, String faceCard)
        {
            mNum = num;
            mFaceCard = faceCard;
            mID++;
        }
    }
}
