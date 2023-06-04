#include "battle.h"
#include<worship.h>
#include<algorithm>

Battle::Battle(){}

void Battle::input(bool camp, int n, worship* s, ...) {
    sum[camp] = n;
    worship** temp = &s;
    for (int i = 0; i < n; ++i) {
        ship[camp].push_back(*temp++);
    }
}
bool attackcmp(worship* w1, worship* w2) {
    return w1->speed < w2->speed;
}
int Battle::attack() {
    //最多进行十轮交火
    bool battleEnd = 0;
    std::vector<worship*> orderOfAttack[2];//进攻顺序
    for (int camp = 0; camp < 2; ++camp) {
        orderOfAttack[camp] = ship[camp];
        sort(orderOfAttack[camp].begin(), orderOfAttack[camp].end(), attackcmp);
    }

    for (int i = 0; i <= 10 && !battleEnd; ++i) {
        //空战和炮击，双方交替
        int curr[2] = { 0 };//记录当前应空战和炮击的舰船

        for (int j = 0; j < fmax(sum[0], sum[1]); ++j) {
            for (int camp = 0; camp < 2; ++camp) { //对两个阵营
                for (; curr[camp] < sum[camp]; ++curr[camp]) {
                    while (orderOfAttack[camp][curr[camp]]->extratk) {
                        ++curr[camp];
                    }//寻找不用鱼雷的舰船
                    if (curr[camp] >= sum[camp])break;

                    worship* attacker = orderOfAttack[camp][curr[camp]]; //当前指向的战舰
                    worship* theAttacked = ship[!camp][0];
                    attacker->Attack(theAttacked);//攻击当前编号最靠前的敌方舰船
                    if (theAttacked->ifsunk) {
                        ship[!camp].erase(ship[!camp].begin());
                        --sum[!camp];
                        --curr[!camp]; //注意！

                        if (sum[!camp] <= 0)
                            return camp;
                    }
                }
            }
        }

        //鱼雷战
        for (int camp = 0; camp < 2; ++camp) {
            for (int i = 0; i < sum[camp]; ++i) {
                orderOfAttack[camp][i]->Extratk(ship[!camp][0]);
                if (ship[!camp][0]->ifsunk) {
                    ship[!camp].erase(ship[!camp].begin());
                    --sum[!camp];

                    if (sum[!camp] <= 0)
                        return camp;
                }
            }
        }
    }
    return -1;
}
//每方是按编号排列的，攻击也是按编队顺序
//分为两轮，空战炮击和鱼雷战
