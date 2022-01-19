#include "Engine.h"

bool g_running = false;
Uint32 g_start, g_end, g_delta, g_fps;
const Uint8* g_keystates;
SDL_Window* g_pWindow;
SDL_Renderer* g_pRenderer;
SDL_Texture* g_pPlayerHumanTexture;

SDL_Texture* g_pBGTexture; // For background.
SDL_Texture* g_pPlayerWeaponTexture;

SDL_Rect g_playerx; // For primitive rectangle.
// Two destination rectangles for BG
SDL_Rect g_BG1, g_BG2;

Player g_player(WIDTH/2, HEIGHT/2);
vector<Missile*> g_playerFire;


Mix_Chunk* g_pBoom;
Mix_Chunk* g_pMissile; // death.wav
Mix_Chunk* g_pMissileE;
Mix_Chunk* g_pLaser;
Mix_Chunk* g_pExplosion;

Mix_Music* g_pTcats;
Mix_Music* g_pTmnt;
bool g_paused = 0; // For toggle.
////bool Alive = true;

stateDir missileDirection;

// Init function. Sets up SDL and all subsystems and other (dynamic) memory allocation.
int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing game..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay.
	{
		// Try to create the SDL_Window.
		g_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (g_pWindow != nullptr) // If window creation passes.
		{
			// Try to create the SDL_Renderer. (Back buffer)
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if (g_pRenderer != nullptr)
			{
				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
				{
					g_pPlayerHumanTexture = IMG_LoadTexture(g_pRenderer, "Human.png");
					g_pPlayerWeaponTexture = IMG_LoadTexture(g_pRenderer, "Enemies.png");
					g_pBGTexture = IMG_LoadTexture(g_pRenderer, "BGL2.png");
					// Add check of texture pointer later...
				}
				else return false; // Image init failed.

				if (Mix_Init(MIX_INIT_MP3) != 0)
				{
					// Configure mixer.
					Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096); // If any lag in playing sounds, lower to 2048.
					Mix_AllocateChannels(16);
					// Load sounds.
					g_pBoom = Mix_LoadWAV("aud/boom.wav");
					//g_pMissile = Mix_LoadWAV("aud/death.wav");
					g_pMissile = Mix_LoadWAV("aud/GunShot5.wav");
					g_pMissileE = Mix_LoadWAV("aud/GunShot2.wav");
					g_pLaser = Mix_LoadWAV("aud/laser.wav");
					//g_pExplosion = Mix_LoadWAV("aud/Explosion.wav");
					g_pExplosion = Mix_LoadWAV("aud/GunShot4.wav");
					//g_pTcats = Mix_LoadMUS("aud/Thundercats.mp3");
					g_pTcats = Mix_LoadMUS("aud/BackGround1.mp3");
					g_pTmnt = Mix_LoadMUS("aud/Turtles.mp3");
				}
				else return false; // Mixer init failed.
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
	}
	else return false; // Initialization has failed.
	// If everything is okay, we are here...
	g_fps = (Uint32)round(1 / (double)FPS * 1000);
	g_keystates = SDL_GetKeyboardState(nullptr);
	g_playerx = { WIDTH / 2, HEIGHT / 2, 35, 55 };

	g_BG1 = { 0, 0, 1024, 768 };
	g_BG2 = { 0, -768, 1024, 768 };

	g_playerFire.reserve(4);
	Mix_VolumeMusic(16); // 0-128.
	Mix_Volume(-1, 32); // All sfx.
	Mix_PlayMusic(g_pTcats, -1);

	cout << "Initialization successful!" << endl;
	g_running = true;
	return true;
}

// HandleEvents function. Gets input from user, e.g. mouse/keyboard/gamepad events.
void Engine::HandleEvents()
{
	//cout << "Getting input..." << endl;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // Pressing 'X' button of window.
			g_running = false;
			break;
		case SDL_KEYDOWN: // Essential parses every frame. Just like keystates.
			////if (event.key.keysym.sym == SDLK_SPACE) // Pressing spacebar.
			////{
			////	////g_fire = true;
			////	if (!Mix_Playing(8))
			////	{
			////		Mix_SetPanning(8, 255, 128);
			////		Mix_PlayChannel(8, g_pLaser, -1);
			////	}
			////	// cout << "Firin' mah lazor!" << endl;
			////}
			break;
		case SDL_KEYUP: // One-shot
			////if (event.key.keysym.sym == ' ') // Releasing spacebar.
			////{
			////	////g_fire = false;
			////	Mix_HaltChannel(8);
			////	cout << "Done pews..." << endl;
			////}

			/*else */if (event.key.keysym.sym == 13) // Enter.
			{
				// Fire dynamic Missile.
				g_playerFire.push_back(new Missile(g_player.m_dst.x + (g_player.m_dst.w / 2) - 10, g_player.m_dst.y + (g_player.m_dst.h / 2) + 5, PLAYER, missileDirection));  // Instead of 68 we could add (g_dst.w/2).
				g_playerFire.shrink_to_fit();
				Mix_PlayChannel(-1, g_pMissile, 0);
			}
			else if (event.key.keysym.sym == SDLK_1)
			{
				Mix_FadeOutMusic(1000);
				Mix_FadeInMusic(g_pTmnt, -1, 1000);
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				Mix_FadeOutMusic(1000);
				Mix_FadeInMusic(g_pTcats, -1, 1000);
			}
			else if (event.key.keysym.sym == SDLK_p) // Pause/resume toggle.
			{
				if (g_paused)
				{
					Mix_ResumeMusic();
					g_paused = false;
				}
				else
				{
					Mix_PauseMusic();
					Mix_HaltChannel(-1); // Optional. Also stops all sfx.
					g_paused = true;
				}
			}
			break;
		}
	}
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (g_keystates != nullptr)
	{
		if (g_keystates[c] == 1) // Key we're testing for is down.
			return true;
	}
	return false;
}

// Update function. Moves objects, performs physics, e.g. projectiles, gravity, collisions.
void Engine::Update()
{

	switch (g_player.m_state)
	{
	case IDLEN:
		// Transition to move animation.
		if (KeyDown(SDL_SCANCODE_W))
		{
			g_player.SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (KeyDown(SDL_SCANCODE_S))
		{
			g_player.SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (KeyDown(SDL_SCANCODE_A))
		{
			g_player.SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVEU):
		// Transition to idle animation.
		if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_A) && !KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(IDLEN, 0, 1);
		}
		else if (KeyDown(SDL_SCANCODE_S))
		{
			g_player.SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (KeyDown(SDL_SCANCODE_A))
		{
			g_player.SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVED):
		// Transition to idle animation.
		if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_A) && !KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(IDLEN, 0, 1);
		}
		else if (KeyDown(SDL_SCANCODE_W))
		{
			g_player.SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (KeyDown(SDL_SCANCODE_A))
		{
			g_player.SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case  MOVEL:
		// Transition to idle animation.
		if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_A) && !KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(IDLEN, 0, 1);
		}
		else if (KeyDown(SDL_SCANCODE_W))
		{
			g_player.SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (KeyDown(SDL_SCANCODE_S))
		{
			g_player.SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVER):
		// Transition to idle animation.
		if (!KeyDown(SDL_SCANCODE_W) && !KeyDown(SDL_SCANCODE_S) && !KeyDown(SDL_SCANCODE_A) && !KeyDown(SDL_SCANCODE_D))
		{
			g_player.SetAnimation(IDLEN, 0, 1);
		} 
		else if(KeyDown(SDL_SCANCODE_W))
		{
			g_player.SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (KeyDown(SDL_SCANCODE_S))
		{
			g_player.SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (KeyDown(SDL_SCANCODE_A))
		{
			g_player.SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		break;
	}
	g_player.Update();
	//cout << "Updating game..." << endl;
	
	if (KeyDown(SDL_SCANCODE_S) && g_player.m_dst.y < HEIGHT - 32 * 2) {
		g_player.m_dst.y += SPEED;
	}
	if (KeyDown(SDL_SCANCODE_W) && g_player.m_dst.y > 0) {
		g_player.m_dst.y -= SPEED;
	}
	if (KeyDown(SDL_SCANCODE_A) && g_player.m_dst.x > 0) {
		g_player.m_dst.x -= SPEED;
	}
	if (KeyDown(SDL_SCANCODE_D) && g_player.m_dst.x < WIDTH - 32 * 2) {
		g_player.m_dst.x += SPEED;
	}

	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		g_playerFire[i]->Update();
		// g_missiles.at(i)->Update();
	}
	
	// Deallocate missiles that go off screen.
	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		// cout << g_missiles[i]->m_dst.y << " and " << -g_missiles[i]->m_dst.h << endl;
		if (g_playerFire[i]->m_dst.y <= -g_playerFire[i]->m_dst.h || g_playerFire[i]->m_dst.y > HEIGHT || g_playerFire[i]->m_dst.x <= -g_playerFire[i]->m_dst.w || g_playerFire[i]->m_dst.x > WIDTH) // -g_missiles[i]->m_dst.h means the entire object off screen
		{
			delete g_playerFire[i]; // Deallocates Missile through pointer.
			g_playerFire[i] = nullptr; // Ensures no dangling pointer.
			g_playerFire.erase(g_playerFire.begin() + i); // Erase element and resize array.
			g_playerFire.shrink_to_fit();
			// Options:
			break;
		}
	}
}

// Render function. Renders changes in game objects to window.
void Engine::Render()
{
	//cout << "Rendering changes to window..." << endl;
	SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(g_pRenderer);
	SDL_RenderCopy(g_pRenderer, g_pBGTexture, NULL, &g_BG1); // For the bg1.
	SDL_RenderCopy(g_pRenderer, g_pBGTexture, NULL, &g_BG2); // For the bg2.

	// Render player missiles.
	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		SDL_RenderCopy(g_pRenderer, g_pPlayerWeaponTexture,
			&(g_playerFire[i]->m_src), &(g_playerFire[i]->m_dst));
	}
	
	////SDL_RenderCopy(g_pRenderer, g_pPlayerShipTexture, &g_player.m_src, &g_player.m_dst); // For the ship.
	SDL_RenderCopy(g_pRenderer, g_pPlayerHumanTexture, &g_player.m_src, &g_player.m_dst);

	SDL_RenderPresent(g_pRenderer); // Flip buffers - send data to window.
}

// Clean function. De-initialize SDL and de-allocate memory.
void Engine::Clean()
{
	cout << "Cleaning up..." << endl;
	
	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		delete g_playerFire[i]; // Deallocates Missile through pointer.
		g_playerFire[i] = nullptr; // Ensures no dangling pointer.
	}
	g_playerFire.clear(); // Removes all elements. Size = 0.
	g_playerFire.shrink_to_fit(); // Sets capacity to size.
	 
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_DestroyTexture(g_pPlayerHumanTexture);
	SDL_DestroyTexture(g_pPlayerWeaponTexture);
	SDL_DestroyTexture(g_pBGTexture);

	Mix_FreeChunk(g_pBoom);
	Mix_FreeChunk(g_pMissile);
	Mix_FreeChunk(g_pMissileE);
	Mix_FreeChunk(g_pExplosion);
	Mix_FreeChunk(g_pLaser);
	Mix_FreeMusic(g_pTmnt);
	Mix_FreeMusic(g_pTcats);
	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();
	SDL_Quit();
}

void Engine::Wake()
{
	g_start = SDL_GetTicks(); // Gets milliseconds since SDL initialization.
}

void Engine::Sleep()
{
	g_end = SDL_GetTicks();
	g_delta = g_end - g_start; // 1055 - 1050 = 5ms
	if (g_delta < g_fps) // if (5ms < 17ms)
		SDL_Delay(g_fps - g_delta); // Engine sleeps for 12ms.
}

// Run function. Contains the primary game loop.
int Engine::Run()
{
	if (g_running == true) // If engine is already running.
	{
		return 1;
	}
	if (Init("5TH_SANCTUM", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false) // If initialization failed.
	{
		return 2;
	}
	// If initialization passes, we are here.
	while (g_running) // Primary game loop. "frame"
	{
		Wake();
		HandleEvents(); // Input.
		Update(); // Processing.
		Render(); // Output.
		if (g_running == true)
			Sleep();
	
	}
	cout << "GAME OVER" << endl;
	Clean();
	return 0;
}



