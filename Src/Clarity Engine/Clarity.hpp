//
//  Clarity.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef Clarity_hpp
#define Clarity_hpp

#include <stdio.h>
#include <iostream>
#include "GameObjectManager.hpp"

class Clarity
{
public:
    static void Start();
    static void Initialize();
    
private:
    static bool IsExiting();
    static void GameLoop();
    static void LevelLoaded();
    
    enum GameState { Initialized, Uninitialized, ShowingSplash, Paused,
        ShowingMenu, Playing, Exiting };
    
    static GameState _gameState;
    
    //System Instances
    static GameObjectManager _gameObjectManager;
    //static sf::RenderWindow _mainWindow;
};

#endif /* Clarity_hpp */
