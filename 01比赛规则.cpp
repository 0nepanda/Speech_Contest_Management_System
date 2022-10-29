#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include <algorithm>
#include <numeric>
#include "03speechManager.h"

/*
比赛规则：
            学校举办一场演讲比赛， 共有12个人参加。 比赛共两轮， 第一轮为淘汰赛， 第二轮为决赛
            每名选手都有对应的编号， 如10001~ 10012
            比赛方式：  分组比赛， 每组6人
            第一轮分为两个小组， 整体按照选手编号进行  抽签  后顺序演讲
            是个评委分别给每名选手打分， 去除最高分和最低分， 求的平均分为本轮选手的成绩
            当小组演讲完后， 淘汰组内排名最后的三个选手， 前三名晋级， 进入下一轮的比赛
            第二轮为决赛， 前三名胜出
            每轮比赛过后需要显示晋级选手的信息


*/

int main() {

    // 创建管理类（流）对象
    SpeechManager sm;
    sm.show_Menu();

    // 12创建12名选手的创建
    // for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++ )
    // {
    //     cout << "选手编号： " << it->first << "     姓名为：  " << it->second.m_Name << "      分数为：  " << it->second.m_Score[0] << endl;   //it->second.m_Score这里是数组地址
    // }
    

    int choice;
    cout << "请输入您的选择:  " << endl;

    while (true)
    {
        cin >> choice;

        switch (choice)
        {
        case 1:
            /* 开始比赛 */ 
            sm.startSpeech();
            break;
        case 2:
            /* 查看往届比赛记录 */ 
            sm.showRecord();
            break;
        case 3:
            /* 清空比赛记录 */ 
            sm.clearRecord();
            break;
        case 0:
            /* 退出系统 */ 
            sm.exitSystem();
            break;        
        default:
            cout << " 输入有误， 重新输入" << endl;
            break;
        }
    }
    
    return 0;
}
