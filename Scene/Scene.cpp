////========================================
// Class: Scene
// Author: Hemmy
// Date: 11/07/2018
// Description:
//
// ========================================

#include <iostream>
#include "Scene.hpp"
#include "ScenePriv.hpp"

void Scene::HelloWorld(const char * s)
{
    ScenePriv *theObj = new ScenePriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void ScenePriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

