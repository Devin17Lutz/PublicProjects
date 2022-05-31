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

namespace SkipboGame
{
    /// <summary>
    /// Interaction logic for CreateGameWindow.xaml
    /// </summary>
    public partial class CreateGameWindow : Window
    {
        private const String mIpAddress = "USE YOUR OWN IP ADDRESS";

        public CreateGameWindow()
        {
            InitializeComponent();
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            String gameTaG = GameTagTextBox.Text,
                   numDeckString = DeckComboBox.Text;
            int numDeck = Convert.ToInt32(numDeckString);

            if (gameTaG != "")
            {
                Player hostPlayer = new Player(mIpAddress, gameTaG, numDeck);

                ServerInvoker invoker = new ServerInvoker(new SendPacketCommand("HOST", gameTaG + " " + numDeck, hostPlayer));
                invoker.ExecuteCommand();

                GameBoardWindow board = new GameBoardWindow(hostPlayer, gameTaG, numDeck, true);
                board.Show();
                Close();
            }
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            MainWindow main = new MainWindow();
            main.Show();
            Close();
        }
    }
}
