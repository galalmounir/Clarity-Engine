//
//  GameObject.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <stdio.h>
#include "BaseMessage.hpp"
#include "BaseComponent.hpp"
#include "Transform.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include <glm.hpp>
#include <matrix_transform.hpp>

class GameObject{
public:
    GameObject(int uniqueID) : m_UniqueID(uniqueID), m_Parent(NULL){
    }
    
    int GetObjectID() const { return m_UniqueID; }
    
    void AddComponent(BaseComponent* component);
    
    bool SendMessage(BaseMessage* msg);
    
    void SetParent (GameObject& parent) {m_Parent = &parent;}
    void AddChild (GameObject* child);
    
    void Update(float msec);
    void Awake();
    void Start();
    void LateUpdate(float msec);
    
private: // Methods
    bool PassMessageToComponents(BaseMessage* msg);
    
public: // Members
    Transform transform;    //local transform
    
private: // Members
    int m_UniqueID;
    
    GameObject* m_Parent;
    std::vector<GameObject*> m_Children;
    
    glm::mat4 worldTransform;
    std::vector<BaseComponent*> m_Components;
};
#endif /* GameObject_hpp */
