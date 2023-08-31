#include "./Scene.h"

// -- Scene --

void Scene::SwitchScene(int index)
{
    m_manager->SwitchScene(index);
}

Scene::Scene(SceneManager *sm)
{
    m_manager = sm;
}
void Scene::Tick(float deltaTime)
{
    (void) deltaTime;
    std::cout << "WARNING: This is an empty scene." << std::endl;
}

// -- SceneManager --

SceneManager::SceneManager()
{
    m_sceneIndex = -1; // No scenes have been added
}

void SceneManager::PushScene(Scene *scene)
{
    if (m_sceneIndex < 0) m_sceneIndex = 0;
    m_scenes.push_back(scene);
}

void SceneManager::SwitchScene(int index)
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

void SceneManager::RunScene(float deltaTime)
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
