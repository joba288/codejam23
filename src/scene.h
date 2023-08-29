#pragma once

#include <iostream>
#include <vector>

class Scene
{
 private:
    // Nothing to see here... for now
 public:
    virtual void Tick(float deltaTime)
    {
        (void) deltaTime;
    }
};

class FooScene : public Scene
{
 public:
    void Tick(float deltaTime) override
    {
        std::cout << "This is an e[B]ic test! " << deltaTime << std::endl;
    }
};


class BarScene : public Scene
{
 public:
    void Tick(float deltaTime) override
    {
        std::cout << "What??! " << deltaTime << std::endl;
    }
};

class SceneManager
{
 private:
    int m_sceneIndex;
    std::vector<Scene*> m_scenes;
 public:
    
    SceneManager()
    {
        m_sceneIndex = -1; // No scenes have been added
    }

    void PushScene(Scene *scene)
    {
        if (m_sceneIndex < 0) m_sceneIndex = 0;
        m_scenes.push_back(scene);
    }

    void SwitchScene(int index)
    {
        if (index < 0) {
            std::cerr << "ERROR: Cannot switch to scene " << index << std::endl;
            return;
        }
        if ((size_t)index >= m_scenes.size()) {
            std::cerr << "ERROR: SceneManager.SwitchScene index out of range at " << m_sceneIndex << "!!!!" << std::endl;
            return;
        }

        m_sceneIndex = index;
    }

    void RunScene(float deltaTime)
    {
        // -- HANDLE BAD CONDITIONS --
        if (m_sceneIndex < 0) {
            std::cerr << "ERROR: SceneManager does not have a scene" << std::endl;
            return;
        }
        if ((size_t)m_sceneIndex >= m_scenes.size()) {
            std::cerr << "ERROR: SceneManager index out of range at " << m_sceneIndex << "!!!!" << std::endl;
            return;
        }

        m_scenes[m_sceneIndex]->Tick(deltaTime);
    }
};
