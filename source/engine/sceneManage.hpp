#pragma once
//#include "../game_stuff/GameStuff.hpp"
#include "RenderingSystem.hpp"
#include <type_traits>
/*class Hierarchy 
{
	std::vector<GameObject*> gameObjects;
};*/


class Scene
{
public:
	Scene(){}
	virtual void update() = 0;
	virtual void drawTop() = 0;
	virtual void drawBottom() = 0;
	virtual void start() = 0;
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual ~Scene() = default;
};

namespace SceneManagement{

	Scene* activeScene;

	template<class T>
	void unloadScene()
	{
		delete activeScene;
	}

	template<class T>
	void loadScene()
	{
		static_assert(std::is_base_of<Scene, T>::value, "T must be derived from Scene");
		unloadScene<T>();
		activeScene = new T();
		RenderSystem::sceneExit();
		activeScene->load();		
		RenderSystem::sceneInit();
		activeScene->start();
	}

	void drawActiveTop()
	{
		activeScene->drawTop();
	}

	void drawActiveBottom()
	{
		activeScene->drawBottom();
	}
};