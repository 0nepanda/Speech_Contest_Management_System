#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include <map>
#include "04speaker.h"
#include <algorithm>
#include <numeric>
#include <deque>
#include <functional>
#include <fstream>
// 设计演讲比赛管理（flow）类
class SpeechManager
{
public:
    // 构造函数
    SpeechManager();

    // 展示菜单
    void show_Menu();

    // 退出系统
    void exitSystem();

    // 析构函数       
    ~SpeechManager();  //只声明不实现

    // 初始化容器和属性
    void initSpeech();

    // 创建12名选手
    void createSpeaker();

    //开始比赛, 比赛整个流程控制函数
    void startSpeech();

    // 1抽签
    void speechDraw();

    // 2比赛
    void speechContext();

    // 显示得分
    void showScore();

    // 保存记录
    void saveRecord();

    // 2、读取记录
    void loadRecord();

    // 2、2 显示往届记录
    void showRecord();

    // 3、清空文件
    void clearRecord();

    // 成员属性：
    //保存第一轮比赛选手编号容器
    vector<int> v1;

    //第一轮晋级选手编号容器
    vector<int> v2;

    //胜出前三名选手编号容器
    vector<int> vVictory;

    //存放编号及对应选手的容器
    map<int, Speaker> m_Speaker;

    //存放当前比赛轮数
    int m_Index;

    // 判断文件是否为空
    bool fileIsEmpty;

    // 存放往届记录的容器
    map<int, vector<string>> m_Record;

};  