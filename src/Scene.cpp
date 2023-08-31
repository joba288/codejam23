#include "./Scene.h"

// -- Scene --

void Scene::NextScene() { m_manager->NextScene(); }
void Scene::PreviousScene() { m_manager->PreviousScene(); }

void Scene::SwitchScene(int index)
{
    m_manager->SwitchScene(index);
}

Scene::Scene(SceneManager *sm)
{
    m_manager = sm;
}

void Scene::Init()
{
    (void)0;
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
    // Uninitialized and un-pushed first scene must run Init()
    if (m_sceneIndex < 0) {
        m_sceneIndex = 0;
        scene->Init();
    }
    m_scenes.push_back(scene);
}

void SceneManager::PreviousScene()
{
    if (--m_sceneIndex < 0) m_sceneIndex = m_scenes.size(); // Wrap around to big number
    SwitchScene(m_sceneIndex);
}

void SceneManager::NextScene()
{
    m_sceneIndex++;
    SwitchScene(m_sceneIndex % m_scenes.size()); // Wrap around back to 0 if over size
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
    m_scenes[m_sceneIndex]->Init();
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
