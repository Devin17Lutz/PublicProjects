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
using SkipboLogic;
using SkipboServer;
using SkipboCommands;
using SkipboServerCommands;
using System.Windows.Navigation;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Threading;

namespace SkipboGame
{
    /// <summary>
    /// Interaction logic for GameBoardWindow.xaml
    /// </summary>
    public partial class GameBoardWindow : Window
    {
        private const String mIpAddress = "USE YOUR OWN IP ADDRESS";
        private readonly BackgroundWorker worker = new BackgroundWorker();
        private Player mPlayer;
        private Game mGame;
        private Invoker invoker;
        private ServerInvoker mServerInvoker;
        private Rectangle mSelected;
        private int mNumDeck;
        private String mGameTag;
        private bool mHost;
        private Dictionary<String, Label> mCountDictionary;

        public GameBoardWindow(Player player, String gameTag, int numDeck, bool host)
        {
            InitializeComponent();
            mPlayer = player;
            mGameTag = gameTag;
            mNumDeck = numDeck;
            mHost = host;

            mCountDictionary = new Dictionary<String, Label>();
            mCountDictionary.Add("LeftPile", LeftCount);
            mCountDictionary.Add("RightPile", RightCount);
            mCountDictionary.Add("UpPile", UpCount);
            mCountDictionary.Add("DownPile", DownCount);
            mCountDictionary.Add("P2Pile", P2PileCount);
        }

        public GameBoardWindow(Player player, String gameTag, bool host)
        {
            InitializeComponent();
            mPlayer = player;
            mGameTag = gameTag;
            mHost = host;

            mCountDictionary = new Dictionary<String, Label>();
            mCountDictionary.Add("LeftPile", LeftCount);
            mCountDictionary.Add("RightPile", RightCount);
            mCountDictionary.Add("UpPile", UpCount);
            mCountDictionary.Add("DownPile", DownCount);
            mCountDictionary.Add("P2Pile", P2PileCount);
        }

        private void ReceiveServerData()
        {
            mServerInvoker.SetCommand(new ReceivePacketCommand(mPlayer));
            SkipboPacket packet = mServerInvoker.ExecuteReceiveCommand() as SkipboPacket;

            HandleServerMessage(packet);
        }

        private void SendServerData(String message)
        {
            mServerInvoker.SetCommand(new SendPacketCommand(message, mGame, mPlayer));
            mServerInvoker.ExecuteCommand();
        }

        private void HandleServerMessage(SkipboPacket packet)
        {
            switch (packet.Message)
            {
                case "DATA":
                    mGame = packet.ByteArrayToObject() as Game;
                    break;
                case "LOST":
                    this.Dispatcher.Invoke(() =>
                    {
                        GameOverWindow win = new GameOverWindow("You Were Beaten By The Best!");
                        win.Show();
                        Close();
                    });
                    break;
                default:
                    break;
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            invoker = new Invoker();
            mSelected = new Rectangle();
            mServerInvoker = new ServerInvoker(new ReceivePacketCommand(mPlayer));
            SkipboPacket packet = mServerInvoker.ExecuteReceiveCommand() as SkipboPacket;
            worker.DoWork += worker_HandleServerData;

            HandleServerMessage(packet);
            GetAllCards();

            if (mHost)
            {
                worker.RunWorkerAsync();
            }
        }

        private void worker_HandleServerData(object sender, DoWorkEventArgs e)
        {
            this.Dispatcher.Invoke(() =>
            {
                Opacity = 0.2;
                IsEnabled = false;
            });

            ReceiveServerData();

            this.Dispatcher.Invoke( () =>
            {
                invoker.SetCommand(new CheckHandCardsCommand(mGame));

                if (invoker.ExecuteCheckHandCardsCommand())
                {
                    invoker.SetCommand(new DrawCommand(mGame));
                    invoker.ExecuteCommand();
                }

                GetAllCards();
                Opacity = 1;
                IsEnabled = true;
            });
        }

        private void GetAllCards()
        {
            String image = "";
            
            foreach (Rectangle rect in FindVisualChildren<Rectangle>(this))
            {
                invoker.SetCommand(new GetCardCommand(mGame, rect.Name));
                image = invoker.ExecuteGetCardCommand();

                if (rect.Name == "DrawPile")
                    continue;

                if (image == "WHITE")
                {
                    rect.Fill = Brushes.White;
                }
                else
                {
                    rect.Fill = new ImageBrush(new BitmapImage(new Uri(BaseUriHelper.GetBaseUri(this), image)));
                }
            }

            foreach (KeyValuePair<String,Label> key in mCountDictionary)
            {
                Label label = key.Value;
                invoker.SetCommand(new GetCountCommand(mGame, key.Key));

                label.Content = invoker.ExecuteGetPileCountCommand().ToString();
            }
        }

        private void CollectPile_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle rect = (sender as Rectangle);
            String target = rect.Name,
                   image = "";

            Popup.IsOpen = false;

            invoker.SetCommand(new PutDownCommand(mGame, target));

            if (mSelected != null && invoker.ExecutePutDownCommand())
            {
                invoker.SetCommand(new GetCardCommand(mGame, rect.Name));
                image = invoker.ExecuteGetCardCommand();
                ChangeCardFace(rect,image);

                invoker.SetCommand(new GetCardCommand(mGame, mSelected.Name));
                image = invoker.ExecuteGetCardCommand();
                ChangeCardFace(mSelected, image);

                mSelected.Stroke = Brushes.Black;

                ChangeCounts(rect.Name, mSelected.Name);

                mSelected = null;

                invoker.SetCommand(new SelectCommand(mGame, "", false));
                invoker.ExecuteCommand();
                invoker.SetCommand(new WinCommand(mGame));

                if (invoker.ExecuteWinCommand())
                {
                    SendServerData("WON");

                    GameOverWindow win = new GameOverWindow("You Beat the Best");
                    win.Show();
                    Close();
                }
            }
        }

        private void ChangeCounts(String destCard, String sourceCard)
        {
            int value = 0;
            Label destLabel = mCountDictionary[destCard];

            if (sourceCard == "P1Pile")
            {
                value = Convert.ToInt32(P1Count.Content);
                P1Count.Content = (--value).ToString();
            }

            value = Convert.ToInt32(destLabel.Content);
            destLabel.Content = (value + 1) != 12 ? (++value).ToString() : "0";
        }

        private void ChangeCardFace(Rectangle rect, String image)
        {
            if (image == "WHITE")
            {
                rect.Fill = Brushes.White;
            }
            else
            {
                rect.Fill = new ImageBrush(new BitmapImage(new Uri(BaseUriHelper.GetBaseUri(this), image)));
            }
        }

        private void Pile_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle rect = sender as Rectangle;
            String pile = rect.Name;
            Popup.IsOpen = false;

            if (rect.Fill == Brushes.White)
            {
                return;
            }

            invoker.SetCommand(new SelectCommand(mGame, pile, true));
            invoker.ExecuteCommand();

            if (mSelected != null)
            {
                mSelected.Stroke = Brushes.Black;
            }

            rect.Stroke = Brushes.Red;
            mSelected = rect;
        }

        private void DiscardPile_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            Rectangle rect = sender as Rectangle;
            String pile = rect.Name;
            String image = "";

            if (mSelected == null)
            {
                if (rect.Fill == Brushes.White)
                {
                    return;
                }

                invoker.SetCommand(new SelectCommand(mGame, pile, true));
                invoker.ExecuteCommand();
                
                rect.Stroke = Brushes.Red;
                mSelected = rect;
            }
            else if (mSelected.Name != "P1Pile")
            {
                invoker.SetCommand(new DiscardCommand(mGame, pile));

                if (invoker.ExecuteDiscardCommand())
                {
                    invoker.SetCommand(new GetCardCommand(mGame, rect.Name));
                    image = invoker.ExecuteGetCardCommand();
                    ChangeCardFace(rect, image);

                    invoker.SetCommand(new GetCardCommand(mGame, mSelected.Name));
                    image = invoker.ExecuteGetCardCommand();
                    ChangeCardFace(mSelected, image);

                    mSelected.Stroke = Brushes.Black;
                    mSelected = null;

                    SendServerData("DATA");
                    Popup.IsOpen = false;

                    worker.RunWorkerAsync();
                }
            }
        }

        private void DrawPile_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            String pile = (sender as Rectangle).Name;
            Popup.IsOpen = false;

            invoker.SetCommand(new CheckHandCardsCommand(mGame));

            if (invoker.ExecuteCheckHandCardsCommand())
            {
                invoker.SetCommand(new DrawCommand(mGame));
                invoker.ExecuteCommand();

                GetAllCards();
            }
        }

        private void DiscardPile_MouseEnter(object sender, MouseEventArgs e)
        {
            Rectangle rect = sender as Rectangle;
            Popup.IsOpen = false;

            invoker.SetCommand(new GetPileCommand(mGame, rect.Name));
            ObservableCollection<Card> list = new ObservableCollection<Card>(invoker.ExecuteGetPileCommand());

            if (list.Count > 1)
            {
                Popup.PlacementTarget = rect;
                PopupItem.ItemsSource = list;
                Popup.IsOpen = true;
            }
        }

        private void Canvas_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.OriginalSource is Rectangle)
                return; 

            Popup.IsOpen = false;

            if (mSelected != null)
                mSelected.Stroke = Brushes.Black;

            invoker.SetCommand(new ClearCommand(mGame));
            invoker.ExecuteCommand();
        }

        public static IEnumerable<T> FindVisualChildren<T>(DependencyObject depObj) where T : DependencyObject
        {
            if (depObj != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(depObj); i++)
                {
                    DependencyObject child = VisualTreeHelper.GetChild(depObj, i);
                    if (child != null && child is T)
                    {
                        yield return (T)child;
                    }

                    foreach (T childOfChild in FindVisualChildren<T>(child))
                    {
                        yield return childOfChild;
                    }
                }
            }
        }
    }
}
