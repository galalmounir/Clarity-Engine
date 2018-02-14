//
//  GameObjectManager.cpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#include "GameObjectManager.hpp"

// Initialize our static unique objectID generator
int GameObjectManager::nextObjectID = 0;

void GameObjectManager::Awake(){
    for(std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
        (i->second)->Awake();
    }
}

void GameObjectManager::Start(){
    for(std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
        (i->second)->Start();
    }
}

void GameObjectManager::Update(float msec){
    for(std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
        (i->second)->Update(msec);
    }
}

void GameObjectManager::LateUpdate(float msec){
    for(std::map<int, GameObject*>::iterator i = m_Objects.begin(); i != m_Objects.end(); ++i) {
        (i->second)->LateUpdate(msec);
    }
}

GameObject* GameObjectManager::CreateObject()
{
    GameObject* newObj = new GameObject(nextObjectID++);
    m_Objects[newObj->GetObjectID()] = newObj;
    
    return newObj;
}

// Returns true if the object or any components handled the message
bool GameObjectManager::SendMessage(BaseMessage* msg){
    // We look for the object in the scene by its ID
    std::map<int, GameObject*>::iterator objIt = m_Objects.find(msg->m_destObjectID);
    if ( objIt != m_Objects.end() )
    {
        // Object was found, so send it the message
        return objIt->second->SendMessage(msg);
    }

    // Object with the specified ID wasn't found
    return false;
}

