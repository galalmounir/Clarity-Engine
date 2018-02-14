//
//  GameObjectManager.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef GameObjectManager_hpp
#define GameObjectManager_hpp

#include <stdio.h>
#include "GameObject.hpp"
#include "iostream"
#include <map>
#include <list>
#include <iterator>

class GameObjectManager
{
public:
    bool SendMessage(BaseMessage* msg);
    GameObject* CreateObject();
    
    void Update(float msec);
    void Awake();
    void Start();
    void LateUpdate(float msec);
    
private:
    std::map<int, GameObject*> m_Objects;
    static int nextObjectID;
};
#endif /* GameObjectManager_hpp */
