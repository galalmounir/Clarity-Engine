//
//  BaseMessage.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef BaseMessage_hpp
#define BaseMessage_hpp

#include <stdio.h>

enum eMessageType
{
    SetPosition,
    GetPosition,
};

class BaseMessage
{
protected: // Abstract class, constructor is protected
    BaseMessage(int destinationObjectID, eMessageType messageTypeID)
    : m_destObjectID(destinationObjectID)
    , m_messageTypeID(messageTypeID)
    {}
    
public: // Normally this isn't public, just doing it to keep code small
    int m_destObjectID;
    eMessageType m_messageTypeID;
};

#endif /* BaseMessage_hpp */
