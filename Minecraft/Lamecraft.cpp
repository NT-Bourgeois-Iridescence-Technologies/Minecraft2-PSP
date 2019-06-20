#include <math.h>
#include <psptypes.h>

#include <Aurealis/Graphics/RenderManager.h>
#include <Aurealis/Utils/Logger.h>
#include <Aurealis/Utils/Timer.h>
#include <Aurealis/System/SystemManager.h>
#include <Aurealis/Graphics/Camera.h>
#include <Aurealis/Utils/StateManager.h>

#include "LameCraft/StateMenu.h"
#include "LameCraft/SplashScreen.h"
#include <Aurealis/Audio/SoundManager.h>
#include "LameCraft/TextureHelper.h"

using namespace Aurealis::Graphics;
using namespace Aurealis::Utils;
using namespace Aurealis::System;
using namespace Aurealis::Audio;
using namespace Aurealis;

PSP_MODULE_INFO("LameCraft", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU|THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(-1024);

int main()
{
	SetupCallbacks();

	scePowerSetClockFrequency(333, 333, 166);

	//initialize render manager
	g_RenderManager.Init();
	g_RenderManager.CollectPerformance(true);
	g_RenderManager.InitDebugFont();

	//set perspectives
	g_RenderManager.SetOrtho(0,0,0,0,0,0);

	//init and load sounds
	TextureHelper::Instance()->Init();
	g_SoundManager.Init();

	srand(time(NULL));

	//new state manager
	StateManager stateManager;
	stateManager.Init();

	g_RenderManager.SetClearColour(0xFF000000);

	//splash screens
	
	SplashScreen* screen = new SplashScreen(TextureHelper::Instance()->GetTexture(TextureHelper::Iridescence), 0, 0, 480, 272, 2);
	screen->ShowSplash();
	delete screen;
	

	SplashScreen* screen2 = new SplashScreen(TextureHelper::Instance()->GetTexture(TextureHelper::Genesis), 0, 0, 480, 272, 2);
	screen2->ShowSplash();
	delete screen2;
	

	g_RenderManager.SetClearColour(0xFFFFFFFF);

	//new active state
	StateMenu *statePlay = new StateMenu();
	statePlay->Init();
	stateManager.ChangeState(statePlay);

	//trun
	while ( stateManager.Running() )
	{
		stateManager.HandleEvents();
		stateManager.Update();
		stateManager.Draw();
	}

	sceGuTerm();			// Terminating the Graphics System
	sceKernelExitGame();	// Quits Application

	return 0;
}
