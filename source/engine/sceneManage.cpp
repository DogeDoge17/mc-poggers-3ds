#include "engine/sceneManage.hpp"

namespace SceneManagement{
	Scene* activeScene;

	void drawActiveTop()
	{
		activeScene->drawTop();
	}

	void drawActiveBottom()
	{
		activeScene->drawBottom();
	}
};
