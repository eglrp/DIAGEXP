using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;

namespace DIAGEXP
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<BranchRecord> visiableRecordC = new ObservableCollection<BranchRecord>();
        private ObservableCollection<BranchRecord> allRecordC = new ObservableCollection<BranchRecord>();

        public MainWindow()
        {
            InitializeComponent();
            ScrollOperation.ScrollToHorizontalOffset(BaseP.Width/5);
            ScrollOperation.ScrollToVerticalOffset(BaseP.Height/5);
            NewBranchTypeList.ItemsSource = getBranchTypeCollection();
            VisiableBranchCollection.ItemsSource = visiableRecordC;
            AllBranchCollection.ItemsSource = allRecordC;
        }
        
        private void GiveOutAAboutWindow(object sender, RoutedEventArgs e)
        {
            Window about = new AboutWindows();
            about.ShowDialog();
        }

        //该集合不需要更新
        private List<BranchRecord> getBranchTypeCollection()
        {
            List<BranchRecord> some = new List<BranchRecord>();
            some.Add(new BranchRecord("alsklsdjfa.asldfkajsdlkf","this.One", "yes!!", "注释信息for ONE", "rectangle"));
            some.Add(new BranchRecord("alskdfasdf.slkdjflaksjdf","this.Two", "yes!!", "注释信息for TWO", "rectangle"));
            some.Add(new BranchRecord("alskdfasdf.sdlkfalskdjfk","this.Three", "no!!", "注释信息for THREE", "rectangle"));
            some.Add(new BranchRecord("alskdfalsd.asldkfjalkdjf","this.Four", "no!!", "注释信息for FOUR", "rectangle"));
            some.Add(new BranchRecord("alskdfasdf.asdlfkasldkff","this.Five", "no!!", "注释信息for FIVE", "rectangle"));
            return some;
        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            visiableRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
            allRecordC.Add(new BranchRecord("aldjfasf", "asldkfjalskdjf", "no!!", "zhushixinxi", "rectangle"));
        }

        private void wheelProc(object sender, MouseWheelEventArgs e)
        {
            if((Keyboard.Modifiers & ModifierKeys.Control) == ModifierKeys.Control)
            {
                int num = e.Delta;
                BaseP.Width = BaseP.Width + num;
                BaseP.Height = BaseP.Height + num;
                e.Handled = true;
            }
        }
        
    }


    // 记录代表条目
    public class BranchRecord:INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, e);
        }

        private string itemID;
        public string ItemID {
            get { return itemID; }
            set { itemID = value;
                OnPropertyChanged(new PropertyChangedEventArgs("BranchRecord"));
            }
        }
        private string branchName;
        public string BranchName
        {
            get { return branchName; }
            set { branchName = value;
                OnPropertyChanged(new PropertyChangedEventArgs("BranchRecord"));
            }
        }
        private string staticOrNot;
        public string StaticV
        {
            get { return staticOrNot; }
            set { staticOrNot = value;
                OnPropertyChanged(new PropertyChangedEventArgs("BranchRecord"));
            }
        }
        private string animation;
        public string Animation
        {
            get { return animation; }
            set { animation = value;
                OnPropertyChanged(new PropertyChangedEventArgs("BranchRecord"));
            }
        }
        private string shapeType;

        public string ShapeType
        {
            get { return shapeType; }
            set { shapeType = value;
                OnPropertyChanged(new PropertyChangedEventArgs("BranchRecord"));
            }
        }
        public BranchRecord(string itemID,string branchName,string staticW,string animation, string shapeType)
        {
            ItemID = itemID;
            StaticV = staticW;
            BranchName = branchName;
            Animation = animation;
            ShapeType = shapeType;
        }
    }
}
