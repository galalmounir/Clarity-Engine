//
//  Graphics.hpp
//  Clarity Engine
//
//  Created by Galal Hassan on 2018-02-12.
//  Copyright © 2018 The Pixel Crushers. All rights reserved.
//

#ifndef Graphics_hpp
#define Graphics_hpp

#include <stdio.h>
#include "Transform.hpp"

class Graphics{
public:
    void Initialize();
    void Update(float msec);
    
    Transform LocalToWorld(Transform local);
};

#endif /* Graphics_hpp */
