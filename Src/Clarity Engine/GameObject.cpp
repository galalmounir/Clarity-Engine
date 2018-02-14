//
//  GameObject.cpp
//  Clarity


//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#include "GameObject.hpp"

void GameObject::Awake(){
    for(std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
        (*i)->Awake();
    }
//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
//        (*i)->Awake();
//    }
}

void GameObject::Start(){
    for(std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
        (*i)->Start();
    }
//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
//        (*i)->Start();
//    }
}

void GameObject::Update(float msec) {
    if(m_Parent){ //This node has a parent...
        worldTransform = m_Parent->worldTransform * transform.transformMatrix;
    }
    else{ //Root node, world transform is local transform!
        worldTransform = glm::mat4(1.0f) * transform.transformMatrix;
    }
    
    for(std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
        (*i)->Update();
    }
//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
//        (*i)->Update(msec);
//    }
}

void GameObject::LateUpdate(float msec){
    for(std::vector<BaseComponent*>::iterator i = m_Components.begin(); i != m_Components.end(); ++i) {
        (*i)->LateUpdate();
    }
//    for(std::vector<GameObject*>::iterator i = m_Children.begin(); i != m_Children.end(); ++i) {
//        (*i)->LateUpdate(msec);
//    }
}

void GameObject::AddComponent(BaseComponent* component)
{
    m_Components.push_back(component);
}

void GameObject::AddChild (GameObject* child){
    m_Children.push_back(child);
}

bool GameObject::SendMessage(BaseMessage* msg)
{
    bool messageHandled = false;
    
    // Object has a switch for any messages it cares about
    switch(msg->m_messageTypeID)
    {
            //            case SetPosition:
            //            {
            //                MsgSetPosition* msgSetPos = static_cast<MsgSetPosition*>(msg);
            //                m_Position.x = msgSetPos->x;
            //                m_Position.y = msgSetPos->y;
            //                m_Position.z = msgSetPos->z;
            //
            //                messageHandled = true;
            //                cout << "Object handled SetPosition\n";
            //            }
            //                break;
            //            case GetPosition:
            //            {
            //                MsgGetPosition* msgSetPos = static_cast<MsgGetPosition*>(msg);
            //                msgSetPos->x = m_Position.x;
            //                msgSetPos->y = m_Position.y;
            //                msgSetPos->z = m_Position.z;
            //
            //                messageHandled = true;
            //                cout << "Object handling GetPosition\n";
            //            }
            break;
        default:
            return PassMessageToComponents(msg);
    }
    // If the object didn't handle the message but the component
    // did, we return true to signify it was handled by something.
    messageHandled |= PassMessageToComponents(msg);
    
    return messageHandled;
}

bool GameObject::PassMessageToComponents(BaseMessage* msg)
{
    bool messageHandled = false;
    
    std::vector<BaseComponent*>::iterator compIt = m_Components.begin();
    for (compIt; compIt != m_Components.end(); ++compIt )
    {
        messageHandled |= (*compIt)->SendMessage(msg);
    }
    
    return messageHandled;
}
