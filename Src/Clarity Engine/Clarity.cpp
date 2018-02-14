//
//  Clarity.cpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#include "Clarity.hpp"

Clarity::GameState Clarity::_gameState;
GameObjectManager Clarity::_gameObjectManager;

void Clarity::Initialize(){
    //Attept to show splash
    
    //check for minimum requirements.
    
    _gameState = Initialized;
    
}

void Clarity::GameLoop(){
    // update all systems
    _gameObjectManager.Update(0); // change to tick later
    
    // late update all systems
    _gameObjectManager.LateUpdate(0); // change to tick later
}

void Clarity::LevelLoaded(){
    _gameObjectManager.Awake();
    // awake other systems
    
    _gameObjectManager.Start();
    // start other systems
}

void Clarity::Start(void)
{
    if(_gameState != Initialized)
        return;
    
    std::cout<<"Initialized";
    //_mainWindow.Create(sf::VideoMode(1024,768,32),"GameName");
    _gameState = Clarity::Playing;
    
    while(!IsExiting())
    {
        GameLoop();
    }
    
    //_mainWindow.Close();
}

bool Clarity::IsExiting(){
    return true;
}
