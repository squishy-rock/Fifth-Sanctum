#include "GameState.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
using namespace std;


GameState::GameState() {}

void GameState::Enter()
{
	cout << "Entering GameState..." << endl;
	// Load sprites.
	g_pBGTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "BG1.png");
	g_BG1 = { 0, 0, 1024, 768 };
	g_pPlayerHumanTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "Human.png");
	g_pEnemyTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "ghost.png");
	g_pPlayerWeaponTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "Enemies.png");
	g_player = new Player(100, HEIGHT / 2);
	missileDirection = D;
	g_playerFire.reserve(4);
	g_enemy.reserve(4);
	// Load music sfx, add them to map.
	m_sfx.emplace("shot", Mix_LoadWAV("aud/GunShot5.wav"));
	m_sfx.emplace("boom", Mix_LoadWAV("aud/boom.wav"));
	m_sfx.emplace("BGM1", Mix_LoadWAV("aud/BGMusic1.wav"));
	// Load music track, andd it to map, and play it.
	//m_sounds.emplace("track", Mix_LoadMUS("aud/BackGround1.mp3"));
	//Mix_PlayMusic(m_sounds["track"], -1);

	// Play backGround music
	Mix_PlayChannel(-1, m_sfx["BGM1"], -1);

	//g_enemy.push_back(new Enemy(100 + 100));  // Instead of 68 we could add (g_dst.w/2).
	//g_playerFire.shrink_to_fit();
	//
	//g_enemy[0]->setDestination(g_player->m_dst);

	timerEnemySpawn = new Timer(2000);

	//Get font and put tutorial message and screen
	font = TTF_OpenFont("Curlz.TTF", 40);
	color = { 0, 0,255,255};
	g_pTutorialSurface = TTF_RenderText_Solid(font, "Use WASD to move, spacebar to shoot, and P to Pause.", color);
	g_pTutorialTexture = SDL_CreateTextureFromSurface(Engine::Instance().GetRenderer(), g_pTutorialSurface);
	g_TutorialBox = { 50,50, 500, 150 };
	SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pTutorialTexture, NULL, &g_TutorialBox);
}

void GameState::Update()
{
	timerEnemySpawn->update();
	if (g_enemy.size() < 3)
	{
		if (timerEnemySpawn->getSpawn())
		{
			timerEnemySpawn->resetSpawn();
			g_enemy.push_back(new Enemy(100 + 100));  // Instead of 68 we could add (g_dst.w/2).
			g_playerFire.shrink_to_fit();
		}
	}

	for (unsigned i = 0; i < g_enemy.size(); i++)
	{
		g_enemy[i]->setDestination(g_player->m_dst);
	}

	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Change to PauseState" << endl;
		// Pause the music track.
		Mix_PauseMusic();
		Mix_Pause(-1);
		STMA::PushState(new PauseState());
	}

	// Parse 1 key and play first sfx. 
	if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
	{
		Mix_PlayChannel(-1, m_sfx["shot"], 0);
	}
	// Parse 2 key and play second sfx.
	if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
	{
		Mix_PlayChannel(-1, m_sfx["boom"], 0);
	}
	if (Engine::Instance().KeyDown(SDL_SCANCODE_SPACE)) // Enter.
	{
		if (!firing)
		{
			// Fire dynamic Missile.
			g_playerFire.push_back(new Missile(g_player->m_dst.x + (g_player->m_dst.w / 2) - 10, g_player->m_dst.y + (g_player->m_dst.h / 2) + 5, PLAYER, missileDirection));  // Instead of 68 we could add (g_dst.w/2).
			g_playerFire.shrink_to_fit();
			Mix_PlayChannel(-1, m_sfx["shot"], 0);
			firing = true;
		}
		
	}
	else
	{
		firing = false;
	}

	for (unsigned i = 0; i < g_playerFire.size(); i++) // For each missile.
	{

		for (unsigned j = 0; j < g_enemy.size(); j++)
		{
			if (SDL_HasIntersection(&g_playerFire[i]->m_dst, &g_enemy[j]->m_dst)) // Collision check. AABB.
			{
				/*Mix_PlayChannel(-1, g_pExplosion, 0)*/;
				// Deallocate missile and enemy.
				delete g_playerFire[i]; // Deallocates Missile through pointer.
				g_playerFire[i] = nullptr; // Ensures no dangling pointer.
				g_playerFire.erase(g_playerFire.begin() + i); // Erase element and resize array.
				g_playerFire.shrink_to_fit();
				delete g_enemy[j]; // Deallocates Enemy through pointer.
				g_enemy[j] = nullptr; // Ensures no dangling pointer.
				g_enemy.erase(g_enemy.begin() + j); // Erase element and resize array.
				g_enemy.shrink_to_fit();
				
				break;
			}
		}
	}

	switch (g_player->m_state)
	{
	case IDLE:
		// Transition to move animation.
		if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
		{
			g_player->SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
		{
			g_player->SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
		{
			g_player->SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVEU):
		// Transition to idle animation.
		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(IDLE, 0, 1);
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
		{
			g_player->SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
		{
			g_player->SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVED):
		// Transition to idle animation.
		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(IDLE, 0, 1);
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
		{
			g_player->SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
		{
			g_player->SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case  MOVEL:
		// Transition to idle animation.
		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(IDLE, 0, 1);
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
		{
			g_player->SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
		{
			g_player->SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(MOVER, 0, 4);
			missileDirection = R;
		}
		break;
	case (MOVER):
		// Transition to idle animation.
		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
		{
			g_player->SetAnimation(IDLE, 0, 1);
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
		{
			g_player->SetAnimation(MOVEU, 0, 4);
			missileDirection = U;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
		{
			g_player->SetAnimation(MOVED, 0, 4);
			missileDirection = D;
		}
		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
		{
			g_player->SetAnimation(MOVEL, 0, 4);
			missileDirection = L;
		}
		break;
	}
	g_player->Update();

	//g_enemy[0]->setDestination(g_player->m_dst);

	for (unsigned i = 0; i < g_enemy.size(); i++)
	{
		g_enemy[i]->Update();
		// g_missiles.at(i)->Update();
	}
	
	//cout << "Updating game..." << endl;

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
	// Pause 'X' key and change state to new EndState.
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		cout << "Change to EndState" << endl;
		STMA::ChangeState(new EndState());
	}

}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pBGTexture, NULL, &g_BG1);
	
	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pPlayerWeaponTexture,
			&(g_playerFire[i]->m_src), &(g_playerFire[i]->m_dst));
	}

	for (unsigned i = 0; i < g_enemy.size(); i++)
	{
		SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pEnemyTexture,
			&(g_enemy[i]->m_src), &(g_enemy[i]->m_dst));
	}

	
	SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pPlayerHumanTexture, &g_player->m_src, &g_player->m_dst);
	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // If current state is GameState.
		State::Render();

}

void GameState::Exit()
{
	cout << "Exiting GameState..." << endl;
	for (unsigned i = 0; i < g_playerFire.size(); i++)
	{
		delete g_playerFire[i]; // Deallocates Missile through pointer.
		g_playerFire[i] = nullptr; // Ensures no dangling pointer.
	}
	g_playerFire.clear(); // Removes all elements. Size = 0.
	g_playerFire.shrink_to_fit(); // Sets capacity to size.
	for (unsigned i = 0; i < g_enemy.size(); i++)
	{
		delete g_enemy[i]; // Deallocates Missile through pointer.
		g_enemy[i] = nullptr; // Ensures no dangling pointer.
	}
	g_enemy.clear(); // Removes all elements. Size = 0.
	g_enemy.shrink_to_fit(); // Sets capacity to size.
	
	Mix_FreeMusic(m_sounds["track"]);
	Mix_FreeChunk(m_sfx["shot"]);
	Mix_FreeChunk(m_sfx["boom"]);
	Mix_FreeChunk(m_sfx["BGM1"]);
	SDL_FreeSurface(g_pTutorialSurface);
	SDL_DestroyTexture(g_pTutorialTexture);

	SDL_DestroyTexture(g_pBGTexture);
	SDL_DestroyTexture(g_pPlayerHumanTexture);
}

void GameState::Resume()
{
	cout << "Resuming GameState..." << endl;
	// Resume music track.
	Mix_ResumeMusic();
	Mix_Resume(-1);
}