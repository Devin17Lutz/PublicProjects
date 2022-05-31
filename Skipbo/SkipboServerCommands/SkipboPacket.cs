using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;
using SkipboLogic;

namespace SkipboServerCommands
{
    [Serializable]
    public class SkipboPacket
    {
        String mMessage;
        public String Message
        {
            set { mMessage = value; }
            get { return mMessage; }
        }

        byte[] mData;
        public byte[] Data
        {
            set { mData = value; }
            get { return mData; }
        }

        public SkipboPacket(String message, object obj)
        {
            mMessage = message;

            if (obj != null)
            {
                BinaryFormatter bf = new BinaryFormatter();
                using (var stream = new MemoryStream())
                {
                    bf.Serialize(stream, obj);
                    mData = stream.ToArray();
                }
            }
        }

        public Object ByteArrayToObject()
        {
            if (mData != null)
            {
                using (var memStream = new MemoryStream())
                {
                    var binForm = new BinaryFormatter();
                    memStream.Write(mData, 0, mData.Length);
                    memStream.Seek(0, SeekOrigin.Begin);
                    var obj = binForm.Deserialize(memStream);
                    return obj;
                }
            }
            return null;
        }
    }
}
