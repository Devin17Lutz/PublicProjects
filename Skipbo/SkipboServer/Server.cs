using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using SkipboLogic;
using SkipboServerCommands;

namespace SkipboServer
{
    public class Server
    {
        TcpListener mServer;
        Dictionary<String, Session> mSessions;
        readonly object sessionLock;

        public Server(Int32 port)
        {
            sessionLock = new object();
            mSessions = new Dictionary<String, Session>();
            CreateServer(port);
        }

        private void CreateServer(Int32 port)
        {
            mServer = new TcpListener(IPAddress.Any, port);
            mServer.Start();
        }

        public void Listen()
        {
            while (true)
            {
                TcpClient client = mServer.AcceptTcpClient();
                Player newPlayer = new Player(client);

                ServerInvoker invoker = new ServerInvoker(new ReceivePacketCommand(newPlayer));
                SkipboPacket packet = invoker.ExecuteReceiveCommand() as SkipboPacket;
                
                HandleMessage(packet, newPlayer);
            }
            //server.Stop();
        }

        private void HandleMessage(SkipboPacket packet, Player newPlayer)
        {
            String args;
            String[] argArray = new String[2];

            if (packet.Data != null)
            {
                args = packet.ByteArrayToObject() as String;
                argArray = args.Split(' ');
            }

            switch (packet.Message)
            {
                case "HOST":
                    newPlayer.GameTag = argArray[0];
                    Session newSession = new Session(newPlayer, Convert.ToInt32(argArray[1]));

                    lock (sessionLock)
                    {
                        mSessions.Add(newSession.SessionName, newSession);
                    }
                    break;

                case "JOIN":
                    Session session;

                    lock (sessionLock)
                    {
                        session = mSessions[argArray[0]];
                        mSessions.Remove(argArray[0]);
                    }

                    session.Player2 = newPlayer;
                    Thread sessionThread = new Thread(HandleSessions);
                    sessionThread.Start(session);
                    break;

                case "DATA":
                    ServerInvoker invoker = new ServerInvoker(new SendPacketCommand("", GetSessionsList(), newPlayer));
                    invoker.ExecuteCommand();

                    invoker = new ServerInvoker(new ReceivePacketCommand(newPlayer));
                    SkipboPacket packet2 = invoker.ExecuteReceiveCommand() as SkipboPacket;

                    HandleMessage(packet2, newPlayer);

                    break;
                default:
                    //Kill the Request
                    newPlayer.Quit();
                    break;
            }
        }

        private List<String> GetSessionsList()
        {
            List<String> list = new List<String>();

            foreach (KeyValuePair<String,Session> session in mSessions)
            {
                list.Add(session.Key);
            }

            return list;
        }

        private void HandleSessions(object obj)
        {
            try
            {
                Session newSession = obj as Session;
                newSession.PlayGame();
            }
            catch (Exception) { }
        }
    }
}
