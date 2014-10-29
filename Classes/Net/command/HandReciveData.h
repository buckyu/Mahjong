//
//  HandReciveData.h
//  Mahjong
//
//  Created by tiki on 14/10/29.
//
//

#ifndef __Mahjong__HandReciveData__
#define __Mahjong__HandReciveData__

#include <stdio.h>
#include "cocos2d.h"
#include "HMessage.h"
#include <vector>
using namespace cocos2d;
using namespace std;
class HandReciveData{
public:
    HandReciveData();
    ~HandReciveData();
    static HandReciveData* getInstance();
    int getPondSize();
    void put(HMessage* hms);
    void use();
    static bool isUseReciveThis;
private:
    vector<HMessage*> reciveData;
};
#endif /* defined(__Mahjong__HandReciveData__) */
