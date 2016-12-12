#include <glew.h>
#include <SDL_image.h>

#include "Game.h"
#include "OpenGLRenderer.h"

Game* Game::_gameInstance(nullptr);

Game* Game::GetGameInstance() {
	if (!_gameInstance) {
		_gameInstance = new Game();
	}
	return _gameInstance;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game()	
{
	_isRunning = true;
	_canLoadNewScene = false;
	_fps = 0.0f; 
	_totalTime = 0.0f;
	_deltaTime = 0.0f;
	_lastUpdateTime = 0.0f;
	_timeSinceLastUpdate = 0.0f;
	
	gameWindow = nullptr;
	currentScene = nullptr; 
	sceneToLoad = nullptr;
}

Game::~Game()
{
	DestroySystems(); // Clean up the game systems
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

hBOOL Game::InitEngine()
{
	//// INIT SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Texture (image) init
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	// GAME TIME
	Clock::init(); // Start the global game clock
	gameTimer = new Timer();
	gameTimer->Start();

	fpsCounter = FPS_COUNTER;
	fpsCounter->Init(MAX_FPS);

	// PROPERTIES
	hProperties = H_PROPERTIES;

	hINT width = hProperties->GetVideoProperties()->screenWidth;
	hINT height = hProperties->GetVideoProperties()->screenHeight;
	hUINT fullscreen = hProperties->GetVideoProperties()->fullScreen;

	hINT master = hProperties->GetAudioProperties()->masterVolume;
	hINT music = hProperties->GetAudioProperties()->musicVolume;
	hINT sound = hProperties->GetAudioProperties()->soundVolume;

	// WINDOW
	gameWindow = new Window();
	gameWindow->Init(width, height);

	if (fullscreen) {
		gameWindow->SetFullScreen(true);
	}

	// AUDIO
	audio = AUDIO;

	// INPUT
	input = INPUT;

	// OPENGL RENDERER
	renderer = new OpenGLRenderer();

	// Make mouse invisible
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

// Load the appropriate scene
void Game::LoadScene(Scene * _scene)
{
	if (sceneToLoad != nullptr) {
		delete sceneToLoad;
	}

	sceneToLoad = _scene;
	_canLoadNewScene = true;
}

// Clean up after ourselves
// REMEMBER: Don't have to delete singletons! (that are created w/ unique pointer)
void Game::DestroySystems()
{
	if (currentScene) {
		delete currentScene;
	}
	currentScene = nullptr;

	delete gameTimer;
	gameTimer = nullptr;

	delete renderer;
	renderer = nullptr;

	delete gameWindow;
	gameWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RUNNING THE GAME AND ENGINE

void Game::Run()
{
	hBOOL init = InitEngine();

	if (!init)
	{
		Debug::ConsoleError("ENGINE INITIALIZATION FAILED", __FILE__, __LINE__);
		GETCHAR();
		return;
	}
	else
	{
		// Allow the game to initialize its own special options
		InitGame();

		// Now start the game loop
		GameLoop();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GAME LOOP LOGIC

void Game::GameLoop()
{
	SDL_Event evnt;

	while (_isRunning)
	{
		// BEGIN FPS COUNT FOR THIS FRAME
		fpsCounter->BeginFrame();

		// CALCULATE DELTA-TIME
		_timeSinceLastUpdate = SDL_GetTicks() - _lastUpdateTime;

		// This is the timestep variable we'll use to 
		_deltaTime = _timeSinceLastUpdate / 1000.0f;

		// Set the last update time w/ ticks from "this" iteration of the game loop
		_lastUpdateTime = SDL_GetTicks();

		

		// Update our input handler
		input->Update();

		// INPUT HANDLING LOOP w/ SDL EVENT
		if (SDL_PollEvent(&evnt))
		{
			// Give the polled event to the input handler
			input->ProcessInput(evnt);
			

			// Quit the game
			// by closing window or press "ESC"
			if (evnt.type == SDL_QUIT || input->IsKeyDown(SDLK_ESCAPE))
			{
				SetRunState(false);
				Debug::ConsoleLog("Exit Game");
			}
			
		}
		SDL_PumpEvents();

		// PASS OUR DELTA TIME TO OUR PHYSICS ENGINE
		PHYSICS->FixedUpdate(_deltaTime);

		// UPDATE THE ENGINE AND GAME
		EngineUpdate(_deltaTime);

		// RENDER
		EngineRender();


		// FRAME RATE UPDATE FOR THIS FRAME
		_fps = fpsCounter->End();

		_totalTime += _deltaTime;

	} // end while (isRunning)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UPDATE
void Game::EngineUpdate(const hFLOAT _timeStep)
{
	// Load a new scene if we need to
	if (_canLoadNewScene) {
		_canLoadNewScene = false;

		if (currentScene) {
			delete currentScene;
		}

		currentScene = sceneToLoad;
		sceneToLoad = nullptr;

		currentScene->InitScene();
	}

	// Update engine stuff before game-specific stuff
	if (currentScene) {
		currentScene->Update(_timeStep);
	}

	// Now we can update the game
	GameUpdate(_timeStep);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// RENDER
void Game::PreRender()
{
	renderer->RenderPrimitive(PrimitiveType::TRIANGLES);
}
void Game::EngineRender()
{
	PreRender();
	if (!_canLoadNewScene) {

		if (currentScene) {
			currentScene->Render();
		}

		GameRender();
	}
	PostRender();
}

void Game::PostRender()
{
	SDL_GL_SwapWindow(gameWindow->GetWindow());
	glFlush();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////