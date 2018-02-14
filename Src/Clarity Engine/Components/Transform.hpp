//
//  Transform.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "BaseComponent.hpp"
#include <glm.hpp>
#include <matrix_transform.hpp>

#define X_AXIS glm::vec3(1,0,0)
#define Y_AXIS glm::vec3(0,1,0)
#define Z_AXIS glm::vec3(0,0,1)

struct Vector3
{
public:
    Vector3() : x(0.0f), y(0.0f), z(0.0f){}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z){}
    
    float x, y, z;
};

class Transform : public BaseComponent{
public:
    Transform() : m_Position(), m_Rotation(), m_Scale(1,1,1){}
    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    bool SendMessage(BaseMessage* msg) { return false; }
    Vector3 m_Position;
    Vector3 m_Rotation;
    Vector3 m_Scale;
    
    glm::mat4 transformMatrix;
};

#endif /* Transform_hpp */
