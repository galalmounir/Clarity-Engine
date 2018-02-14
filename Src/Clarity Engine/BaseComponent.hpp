//
//  BaseComponent.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef BaseComponent_hpp
#define BaseComponent_hpp

#include <stdio.h>
#include "BaseMessage.hpp"

class BaseComponent{
public:
    virtual void Awake(){}
    virtual void Start(){}
    virtual void Update(){}
    virtual void LateUpdate(){}
    virtual bool SendMessage(BaseMessage* msg) { return false; }
};

#endif /* BaseComponent_hpp */
