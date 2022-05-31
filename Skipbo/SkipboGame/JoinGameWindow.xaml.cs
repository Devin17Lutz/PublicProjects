using SkipboLogic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using SkipboServerCommands;
using System.Collections.ObjectModel;

namespace SkipboGame
{
    /// <summary>
    /// Interaction logic for JoinGameWindow.xaml
    /// </summary>
    public partial class JoinGameWindow : Window
    {
        private List<String> mGameList;
        private String mGameTag;
        private const String mIpAddress = "USE YOUR OWN IP ADDRESS";
        private Player mPlayer;


        public class GameTag
        {
            public GameTag(String name) { mName = name; }

            private String mName;
            public String Name
            {
                set { mName = value; }
                get { return mName; }
            }
        }

        public JoinGameWindow()
        {
            InitializeComponent();

            mGameList = new List<String>();
            mGameTag = "";

            ConnectToServer();
            GetGameList();
        }

        private void GetGameList()
        {
            ObservableCollection<GameTag> taglist = new ObservableCollection<GameTag>();

            ServerInvoker invoker = new ServerInvoker(new SendPacketCommand("DATA", null, mPlayer));
            invoker.ExecuteCommand();

            invoker.SetCommand(new ReceivePacketCommand(mPlayer));
            SkipboPacket packet = invoker.ExecuteReceiveCommand() as SkipboPacket;

            ObservableCollection<String> list = new ObservableCollection<String>(packet.ByteArrayToObject() as List<String>);

            foreach (String s in list)
            {
                taglist.Add(new GameTag(s));
            }
            GameTagComboBox.ItemsSource = taglist;
        }

        private void ConnectToServer()
        {
            mPlayer = new Player(mIpAddress, "", 1);
        }

        private void JoinButton_Click(object sender, RoutedEventArgs e)
        {
            mGameTag = (GameTagComboBox.SelectedItem as GameTag).Name;
            ServerInvoker invoker = new ServerInvoker(new SendPacketCommand("JOIN", mGameTag, mPlayer));
            invoker.ExecuteCommand();

            GameBoardWindow win = new GameBoardWindow(mPlayer, mGameTag, false);
            win.Show();
            Close();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow();
            main.Show();
            Close();
        }

        private void GameTagComboBox_DropDownOpened(object sender, EventArgs e)
        {

        }

        private void GameTagComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            mGameTag = GameTagComboBox.Text;
        }
    }
}
