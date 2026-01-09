#pragma once
#include "RenderingSystem.hpp"
#include <type_traits>

class Scene
{
public:
	Scene(){}
	virtual void update(void) = 0;
	virtual void drawTop(void) = 0;
	virtual void drawBottom(void) = 0;
	virtual void start(void) = 0;
	virtual void load(void) = 0;
	virtual void unload(void) = 0;
  virtual void prerender(void) {}
	virtual ~Scene(void) = default;
};

namespace SceneManagement{
	extern Scene* activeScene;

	template<class T>
	void unloadScene(void);

	template<class T>
	void loadScene(void);

	void drawActiveTop();
	void drawActiveBottom();
};

// Template implementations must be in header
template<class T>
void SceneManagement::unloadScene()
{
	delete activeScene;
}

template<class T>
void SceneManagement::loadScene()
{
	static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
	unloadScene<T>();
	activeScene = new T();
	RenderSystem::sceneExit();
	activeScene->load();		
	RenderSystem::sceneInit();
	activeScene->start();
}
