#pragma once

#include <iostream>
#include <vector>
#include <memory>

class SceneManager;

class Scene
{
private:
    SceneManager *m_manager;
protected:
    void SwitchScene(int index);
public:
    explicit Scene(SceneManager *sm);
    virtual void Tick(float deltaTime);
};

class SceneManager
{
 private:
    int m_sceneIndex;
    std::vector<Scene*> m_scenes;
 public:
    SceneManager();
    void PushScene(Scene *scene);
    void SwitchScene(int index);
    void RunScene(float deltaTime);
};
