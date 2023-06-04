#include"worship.h"
#include<vector>
#ifndef BATTLE_H
#define BATTLE_H


//战斗类，传入双方数据开始战斗
class Battle {
public:
    std::vector<worship*> ship[2];//我方和敌方(编号分别为0和1)
    int sum[2] = { 0 };//各有舰船数量

    Battle();
    ~Battle() {
        for (int camp = 0; camp < 2; ++camp) {
            if (sum[camp])
                for (auto i = ship[camp].begin(); i != ship[camp].end(); ++i)
                    delete* i;
        }
    };
    void input(bool camp, int n = 0, worship* s = NULL, ...);//输入我方和敌方数据
    int attack();//战斗算法,返回胜利者的阵营，平局返回-1
};
#endif // BATTLE_H
