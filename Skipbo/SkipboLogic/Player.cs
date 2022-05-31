using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace SkipboLogic
{
    [Serializable]
    public class Player
    {
        private TcpClient mClient;
        private NetworkStream mStream;
        private string mIpAddress;

        private string mGameTag;
        public String GameTag
        {
            set { mGameTag = value; }
            get { return mGameTag; }
        }

        private int mNumDeck;

        public Player()
        { }

        public Player(String ipAddress, String gameTag, int numDeck)
        {
            mIpAddress = ipAddress;
            mGameTag = gameTag;
            mNumDeck = numDeck;

            ConnectToServer();
        }

        public Player(TcpClient client)
        {
            mClient = client;
            mStream = mClient.GetStream();
        }

        private void ConnectToServer()
        {
            try
            {
                mClient = new TcpClient(mIpAddress, 50000);
                mStream = mClient.GetStream();
            }
            catch (SocketException)
            { }
        }

        public void SendData(object data)
        {
            IFormatter f = new BinaryFormatter();
            
            try
            {
                f.Serialize(mStream, data);
            }
            catch (SerializationException)
            { }
        }

        public object GetData()
        {
            IFormatter f = new BinaryFormatter();

            try
            {
                return f.Deserialize(mStream);
            }
            catch (SerializationException)
            { }

            return null;
        }

        public void Quit()
        {
            mClient.Close();
        }

        //public void SendResponse(String message)
        //{
        //    byte[] msg = System.Text.Encoding.ASCII.GetBytes(message);
        //    mStream.Write(msg, 0, msg.Length);
        //}

        //public String GetResponse()
        //{
        //    Byte[] bytes = new byte[512];
        //    int i = 0;
        //    i = mStream.Read(bytes, 0, bytes.Length);

        //    // Translate data bytes to a ASCII string.
        //    return System.Text.Encoding.ASCII.GetString(bytes, 0, i);
        //}
    }
}
