using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace DIAGEXP
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<BranchRecord> visiableRecordC = new ObservableCollection<BranchRecord>();
        private ObservableCollection<BranchRecord> allRecordC = new ObservableCollection<BranchRecord>();
        private string selectedID = null;

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
            some.Add(new BranchRecord("this.regular","RegularNode", "yes!!", "普通过程", "rectangle"));
            some.Add(new BranchRecord("this.judge","Switch&Judge", "yes!!", "分支判定", "rectangle"));
            return some;
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

        private void Visual_MouseUp(object sender, MouseButtonEventArgs e)
        {
            BranchRecord selected = (sender as ListBox).SelectedItem as BranchRecord;
            if (selected == null)
                return;

            this.selectedID = selected.ItemID;
            MessageBox.Show("RBClick");
        }
        
        private void appendText(string xx)
        {
            AutoOutputTab.Text += xx + "\n";
        }

        //---------------------------以下为测试用程序，以上为正式函数--------------------------

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            this.appendText("what fuckljdlakjdf");
        }
        //添加节点的实例程序，成品不应该出现这些代码
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
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
        }

        private void AddArrow(object sender, RoutedEventArgs e)
        {
            ArrowsShape one = new ArrowsShape(Brushes.Blue, new Point(4, 7), new Point(200, 300));
            DrawArea.Children.Add(one.GetPolygonShape());
            Canvas.SetLeft(one.GetPolygonShape(), 0);
            Canvas.SetTop(one.GetPolygonShape(), 0);
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

    public class ArrowsShape
    {
        private Point start,end;
        private Brush fillBrush;
        private Polygon shape;

        public ArrowsShape(Brush ColorBrush,Point start, Point end)
        {
            this.fillBrush = ColorBrush;
            this.start = start;
            this.end = end;
        }

        public void ChangePosition(Point newStart, Point newEnd)
        {
            if (newStart == null && newEnd == null)
                return;

            if(newStart != null)
            {
                this.start = newStart;
            }
            if(newEnd != null)
            {
                this.end = newEnd;
            }

            this.shape.Points.Clear();
            this.shape.Points.Add(new Point((start.X - 2), start.Y));
            this.shape.Points.Add(new Point((end.X - 2), (end.Y - 8)));
            this.shape.Points.Add(new Point((end.X - 6), (end.Y - 8)));
            this.shape.Points.Add(this.end);
            this.shape.Points.Add(new Point((end.X + 6), (end.Y - 8)));
            this.shape.Points.Add(new Point((end.X + 2), (end.Y - 8)));
            this.shape.Points.Add(new Point((start.X + 2), start.Y));
        }

        public Polygon GetPolygonShape()
        {
            shape = new Polygon{ StrokeThickness = 1, Fill = this.fillBrush };

            this.shape.Points.Add(new Point((start.X - 2), start.Y));
            this.shape.Points.Add(new Point((end.X - 2), (end.Y - 8)));
            this.shape.Points.Add(new Point((end.X - 6), (end.Y - 8)));
            this.shape.Points.Add(this.end);
            this.shape.Points.Add(new Point((end.X + 6), (end.Y - 8)));
            this.shape.Points.Add(new Point((end.X + 2), (end.Y - 8)));
            this.shape.Points.Add(new Point((start.X + 2), start.Y));

            shape.MouseLeftButtonDown += Arrows_MouseLBDown;

            return this.shape;
        }

        private void Arrows_MouseLBDown(object sender, MouseButtonEventArgs e)
        {
            MessageBox.Show("Arrows_Click_1");
        }
    }

    public class NodeShape
    {
        private List<ArrowsShape> positiveC = new List<ArrowsShape>();
        private List<ArrowsShape> negativeC = new List<ArrowsShape>();

        public NodeShape() { }

        public void AddPositiveBinding(ArrowsShape o)
        {
            this.positiveC.Add(o);
        }

        public void AddNegativeBinding(ArrowsShape o)
        {
            this.negativeC.Add(o);
        }
    }
}
