#include "03speechManager.h"
#include <algorithm>  //random_shuffle
#include <deque>
#include <ctime>
// 构造函数
SpeechManager::SpeechManager()
{
    //初始化容器和属性
    this->initSpeech();

    //创建12名选手
    this->createSpeaker();

    // 构造时加载往届数据
    this->loadRecord();

    // 将记录的容器也清空，否则6，12，18，24会得到3，6，9，12
    // this->m_Record.clear();
}

// 展示菜单
void SpeechManager::show_Menu()
{
    cout << "*****************************************" << endl;
    cout << "**************欢迎加入演讲比赛*************" << endl;
    cout << "**************1、 开始演讲比赛*************" << endl;
    cout << "**************2、 查看往届记录*************" << endl;
    cout << "**************3、 清空比赛记录*************" << endl;
    cout << "**************4、 退出比赛程序*************" << endl;
    cout << endl;
}

// 退出系统
void SpeechManager::exitSystem()
{
    cout << "欢迎下次使用" << endl;
    //按任意键继续
    exit(0);
}


// 初始化容器和属性
void SpeechManager::initSpeech()
{
    //容器置空
    this->v1.clear();
    this->v2.clear();
    this->vVictory.clear();
    this->m_Speaker.clear();

    //初始化比赛轮数
    this->m_Index = 1;    
}

// 创建12名选手
void SpeechManager::createSpeaker()
{
    string nameSeed = "ABCDEFGHIGKL";
    for (int i = 0; i < nameSeed.size(); i++)
    {
        string name = "选手";
        name += nameSeed[i];

        //创建具体选手
        Speaker sp;
        sp.m_Name = name;
        
        for (int j = 0; j < 2; j++)
        {
            sp.m_Score[j] = 0;
        }

        //创建选手编号，并放到v1容器
        this->v1.push_back(i+10001);

        //选手编号及对应选手 放入到map容器中
        this->m_Speaker.insert(make_pair(i+10001, sp));
        
    }
    
}

//开始比赛, 比赛整个流程控制函数
void SpeechManager::startSpeech()
{
    //第一轮开始比赛
    //  1、抽签
    this->speechDraw();   //this
    //  2、比赛
    this->speechContext();
    //  3、显示晋级结果
    this->showScore();


    //第二轮开始比赛
    this->m_Index++;
    //  1、抽签
    this->speechDraw();
    //  2、比赛
    this->speechContext();
    //  3、显示最终结果
    this->showScore();
    //  4、保存分数到文件中
    this->saveRecord();

    // 重置比赛 获取记录
    //初始化容器和属性
    this->initSpeech();

    //创建12名选手
    this->createSpeaker();

    // 构造时加载往届数据
    this->loadRecord();
    cout << "本届比赛完毕。" << endl;
}

// 1、1抽签
void SpeechManager::speechDraw()
{
    cout << "第<<" << this->m_Index << ">>轮比赛选手正在抽签" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "抽签后演讲顺序如下： " << endl;

    if (this->m_Index == 1)
    {
       random_shuffle(v1.begin(), v1.end());   //这里为什么不需要this
       for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
       {
            cout << *it << "    ";
       }
       cout << endl; 
       
    }
    else
    {
       random_shuffle(v2.begin(), v2.end());   //这里为什么不需要this
       for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
       {
            cout << *it << "    ";
       }
       cout << endl;
    }
    cout << "-----------------------------------------------" << endl;
    // system("pause");   //linux
    cout << endl;
}

// 1、2比赛
void SpeechManager::speechContext()
{
    cout << "-------------第" << this->m_Index << "轮比赛正式开始------------" << endl;

    // 准备临时容器， 存放小组成绩
    multimap<double, int, greater<double>> gourpScore; 

    int num = 0;  //记录人员个数，6人一组

    vector<int> v_Src;   //当前进行比赛选手容器
    if (this->m_Index == 1)
    {
        /* 1轮 */
        v_Src = v1;
    }
    else
    {
        v_Src = v2;
    }

    srand((unsigned int)time(NULL));
    // 遍历所有选手进行比赛
    for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
    {
        num++;
        /* 评委打分 */
        deque<double> d;
        for (int i = 0; i < 10; i++)
        {
            double score = (rand() % 401 + 600) / 10.f;   // 60~100.0
            // cout << score << "   ";
            d.push_back(score);
        }
        // cout << endl;
        
        sort(d.begin(), d.end(), greater<double>());  //排序去除
        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum / d.size();
        // //打印平均分
        // cout << "编号： " << *it << "    姓名为： " << this->m_Speaker[*it].m_Name << "  获取平均分： " << avg << endl;

        // 将平均分放到map里去  m_Speaker[*it].找到value即speaker者类
        this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;  //m_Score[this->m_Index - 1]数组

        //将打分数据 放入到临时小组中
        gourpScore.insert(make_pair(avg, *it));  //key是得分， value是具体编号   为什么得分作key  map根据key排序？？
        //每6人取除前三名
        if (num % 6 == 0)
        {
            cout << "第" << num / 6 << "组小组比赛名次为：   " << endl;
            for (multimap<double, int, greater<double>>::iterator it = gourpScore.begin(); it != gourpScore.end(); it++)   //133 （）
            {
                cout << "编号：  " << it->second << "  姓名为：  " << this->m_Speaker[it->second].m_Name << "       成绩为： "
                        << this->m_Speaker[it->second].m_Score[this->m_Index - 1] << endl;
            }

            // 取走前三名
            int count = 0;
            for (multimap<double, int, greater<double>>::iterator it = gourpScore.begin(); it != gourpScore.end() && count <3; it++, count++)
            {
                if (this->m_Index == 1)
                {
                    v2.push_back((*it).second);    //*it解出来是对组， 选second刚好是v2所欲要的编号
                }
                else
                {
                    vVictory.push_back((*it).second); 
                }
                
            }
            

            gourpScore.clear(); //小组容器清空   
        }
        
    }
    
}

// 1、3显示得分
void SpeechManager::showScore()
{
    cout << "-------------------第" << this->m_Index << "轮晋级选手信息如下： ----------------------" << endl;

    vector<int> v;
    if (this->m_Index == 1)
    {
        v = this->v2;// v2;      //为什么能看到v2
    }
    else
    {
        v = vVictory;
    }

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "选手编号为： " << *it << "   姓名为：  " << this->m_Speaker[*it].m_Name << "成绩为：  " << 
                this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;

    }
    cout << endl;
    // system("pause");
    // printf("/033c");
    this->show_Menu();
    
}

// 保存记录
void SpeechManager::saveRecord()
{
    ofstream ofs;
    ofs.open("speech.csv", ios::out | ios::app);   //用追加的方式写文件

    // 将每个选手数据写入到文件中
    for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
    {
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;

    ofs.close();
    cout << "记录已经保存！" << endl;
    
    //更改文件不为空的状态
    this->fileIsEmpty = false;
}

// 2、读取记录
void SpeechManager::loadRecord()
{
    ifstream ifs;
    ifs.open("speech.csv", ios::in);   //读文件

    if (!ifs.is_open())
    {
        /* 文件不存在 */
        cout << " 文件不存在" << endl;
        ifs.close();
        return;
    }
    
    // 文件清空状况
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        /* 读到文件尾 */
        cout << "文件为空" << endl;
        this->fileIsEmpty = true;
        ifs.close();
        return;
    }
    
    // 顺序进到这就说明 存在且不为空
    this->fileIsEmpty = false;
    int index = 0;

    ifs.putback(ch);    //将上面读取的单个字符再放回来

    string data;

    while(ifs >> data)
    {
        // cout << data << endl;  //这个data是文件中全部内容吗？
        // 10010,88.4,10004,85.3,10001,84.85,
        vector<string> vInfo;

        int pos = -1;  //没查到”，“位置的变量
        int start = 0;

        while (true)
        {
            pos = data.find(",", start);
            if (pos == -1)
            {
                //没有找到的情况
                break;
            }
            string temp = data.substr(start, pos - start);
            // cout << temp << endl;
            vInfo.push_back(temp);

            start = pos+1;
        }
        
        this->m_Record.insert(make_pair(index, vInfo));
        index++;
    }
    ifs.close();

    // for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
    // {
    //     cout << "冠军编号：  " << it->first << "    分数为：   " << it->second[0] << endl; 
    // }
    
}

// 2、2 显示往届记录
void SpeechManager::showRecord()
{
    cout << "1" << endl;
    cout << fileIsEmpty << endl;
    if (this->fileIsEmpty)
    {
        cout << "文件为空或者记录为空" << endl;
    }
    else 
    {
        for (int i = 0; i < this->m_Record.size(); i++)
        {
            cout << "第" << i+1 << "届:  " << endl;
            cout << "冠军编号是：  " << this->m_Record[i].at(0) << "  得分：  "  << this->m_Record[i][1] << endl;
            cout << "亚军编号是：  " << this->m_Record[i].at(2) << "  得分：  "  << this->m_Record[i][3] << endl;
            cout << "季军编号是：  " << this->m_Record[i].at(4) << "  得分：  "  << this->m_Record[i][5] << endl;
        }
    }
     
}

// 3、清空文件
void SpeechManager::clearRecord()
{
    cout << "是否确认清空文件？" << endl;
    cout << "1、是" << endl;
    cout << "2、否" << endl;

    int select = 0;

    cin >> select;

    if (select == 1)
    {
        //确认清空
        ofstream ofs("speech.csv", ios::trunc);
        ofs.close();

        // 初始化容器和属性
        this->initSpeech();

        // 创建12名选手
        this->createSpeaker();

        // 加载往届记录
        this->loadRecord();

        cout << "清空文件成功" << endl;
    }
    return;
}

// 析构函数       
SpeechManager::~SpeechManager()
{

}