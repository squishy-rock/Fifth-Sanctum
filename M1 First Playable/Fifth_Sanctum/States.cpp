#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
#include "GameState.h"
using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering TitleState..." << endl;
	// Load music track, add it to map, and play it.
	m_sounds.emplace("track", Mix_LoadMUS("aud/Thundercats.mp3"));
	Mix_PlayMusic(m_sounds["track"], -1);
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "Change to GameState" << endl;
		STMA::ChangeState(new GameState());
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	cout << "Exiting TitleState..." << endl;
	// call Mix_FreeMusic on your music track.
	Mix_FreeMusic(m_sounds["track"]);
}

PauseState::PauseState(){}

void PauseState::Enter()
{
	cout << "Entering PauseState..." << endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
		STMA::PopState();
}

void PauseState::Render()
{
	// First render the GameState.
	STMA::GetStates().front()->Render();
	// Now render the rest of PauseState.
	SDL_SetRenderDrawBlendMode(Engine::Instance().GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 255, 0, 0, 128);
	SDL_Rect rect = { 255, 128, 512, 512 };
	SDL_RenderFillRect(Engine::Instance().GetRenderer(), &rect);
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState..." << endl;
}

//GameState::GameState(){}
//
//void GameState::Enter()
//{
//	cout << "Entering GameState..." << endl;
//	// Load sprites.
//	g_pBGTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "BG1.png");
//	g_BG1 = { 0, 0, 1024, 768 };
//	g_pPlayerHumanTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "Human.png");
//	g_pPlayerWeaponTexture = IMG_LoadTexture(Engine::Instance().GetRenderer(), "Enemies.png");
//	g_player = new Player(100, 100);
//
//	g_playerFire.reserve(4);
//	// Load music sfx, add them to map.
//	m_sfx.emplace("shot", Mix_LoadWAV("aud/GunShot5.wav"));
//	m_sfx.emplace("boom", Mix_LoadWAV("aud/boom.wav"));
//	// Load music track, andd it to map, and play it.
//	m_sounds.emplace("track", Mix_LoadMUS("aud/BackGround1.mp3"));
//	Mix_PlayMusic(m_sounds["track"], -1);
//
//	g_pMissile = Mix_LoadWAV("aud/GunShot5.wav");
//}
//
//void GameState::Update()
//{
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
//	{
//		cout << "Change to PauseState" << endl;
//		// Pause the music track.
//		Mix_PauseMusic();
//		STMA::PushState(new PauseState());
//	}
//	
//	// Parse 1 key and play first sfx. 
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
//	{
//		Mix_PlayChannel(-1, m_sfx["shot"], 0);
//	}
//	// Parse 2 key and play second sfx.
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
//	{
//		Mix_PlayChannel(-1, m_sfx["boom"], 0);
//	}
//	//if (Engine::Instance().KeyDown(SDL_SCANCODE_F)) // Enter.
//	//{
//	//	// Fire dynamic Missile.
//	//	g_playerFire.push_back(new Missile(g_player->m_dst.x + (g_player->m_dst.w / 2) - 10, g_player->m_dst.y + (g_player->m_dst.h / 2) + 5, PLAYER, missileDirection));  // Instead of 68 we could add (g_dst.w/2).
//	//	g_playerFire.shrink_to_fit();
//	//	Mix_PlayChannel(-1, g_pMissile, 0);
//	//	
//	//}
//
//	
//	//while (SDL_PollEvent(&event))
//	//{
//	//	switch (event.type)
//	//	{
//	//	case SDL_KEYDOWN:
//	//		if (event.key.keysym.sym == 13)
//	//		{
//	//			// Fire dynamic Missile.
//	//			g_playerFire.push_back(new Missile(g_player->m_dst.x + (g_player->m_dst.w / 2) - 10, g_player->m_dst.y + (g_player->m_dst.h / 2) + 5, PLAYER, missileDirection));  // Instead of 68 we could add (g_dst.w/2).
//	//			g_playerFire.shrink_to_fit();
//	//			Mix_PlayChannel(-1, g_pMissile, 0);
//	//		}
//	//		break;
//	//	}
//	//}
//	
//
//	switch (g_player->m_state)
//	{
//	case IDLEN:
//		// Transition to move animation.
//		if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
//		{
//			g_player->SetAnimation(MOVEU, 0, 4);
//			missileDirection = U;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
//		{
//			g_player->SetAnimation(MOVED, 0, 4);
//			missileDirection = D;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
//		{
//			g_player->SetAnimation(MOVEL, 0, 4);
//			missileDirection = L;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(MOVER, 0, 4);
//			missileDirection = R;
//		}
//		break;
//	case (MOVEU):
//		// Transition to idle animation.
//		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(IDLEN, 0, 1);
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
//		{
//			g_player->SetAnimation(MOVED, 0, 4);
//			missileDirection = D;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
//		{
//			g_player->SetAnimation(MOVEL, 0, 4);
//			missileDirection = L;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(MOVER, 0, 4);
//			missileDirection = R;
//		}
//		break;
//	case (MOVED):
//		// Transition to idle animation.
//		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(IDLEN, 0, 1);
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
//		{
//			g_player->SetAnimation(MOVEU, 0, 4);
//			missileDirection = U;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
//		{
//			g_player->SetAnimation(MOVEL, 0, 4);
//			missileDirection = L;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(MOVER, 0, 4);
//			missileDirection = R;
//		}
//		break;
//	case  MOVEL:
//		// Transition to idle animation.
//		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(IDLEN, 0, 1);
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
//		{
//			g_player->SetAnimation(MOVEU, 0, 4);
//			missileDirection = U;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
//		{
//			g_player->SetAnimation(MOVED, 0, 4);
//			missileDirection = D;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(MOVER, 0, 4);
//			missileDirection = R;
//		}
//		break;
//	case (MOVER):
//		// Transition to idle animation.
//		if (!Engine::Instance().KeyDown(SDL_SCANCODE_W) && !Engine::Instance().KeyDown(SDL_SCANCODE_S) && !Engine::Instance().KeyDown(SDL_SCANCODE_A) && !Engine::Instance().KeyDown(SDL_SCANCODE_D))
//		{
//			g_player->SetAnimation(IDLEN, 0, 1);
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_W))
//		{
//			g_player->SetAnimation(MOVEU, 0, 4);
//			missileDirection = U;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_S))
//		{
//			g_player->SetAnimation(MOVED, 0, 4);
//			missileDirection = D;
//		}
//		else if (Engine::Instance().KeyDown(SDL_SCANCODE_A))
//		{
//			g_player->SetAnimation(MOVEL, 0, 4);
//			missileDirection = L;
//		}
//		break;
//	}
//	g_player->Update();
//	//cout << "Updating game..." << endl;
//
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_S) && g_player->m_dst.y < HEIGHT - 32 * 2) {
//		g_player->m_dst.y += SPEED;
//	}
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_W) && g_player->m_dst.y > 0) {
//		g_player->m_dst.y -= SPEED;
//	}
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_A) && g_player->m_dst.x > 0) {
//		g_player->m_dst.x -= SPEED;
//	}
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_D) && g_player->m_dst.x < WIDTH - 32 * 2) {
//		g_player->m_dst.x += SPEED;
//	}
//
//	for (unsigned i = 0; i < g_playerFire.size(); i++)
//	{
//		g_playerFire[i]->Update();
//		// g_missiles.at(i)->Update();
//	}
//
//	// Deallocate missiles that go off screen.
//	for (unsigned i = 0; i < g_playerFire.size(); i++)
//	{
//		// cout << g_missiles[i]->m_dst.y << " and " << -g_missiles[i]->m_dst.h << endl;
//		if (g_playerFire[i]->m_dst.y <= -g_playerFire[i]->m_dst.h || g_playerFire[i]->m_dst.y > HEIGHT || g_playerFire[i]->m_dst.x <= -g_playerFire[i]->m_dst.w || g_playerFire[i]->m_dst.x > WIDTH) // -g_missiles[i]->m_dst.h means the entire object off screen
//		{
//			delete g_playerFire[i]; // Deallocates Missile through pointer.
//			g_playerFire[i] = nullptr; // Ensures no dangling pointer.
//			g_playerFire.erase(g_playerFire.begin() + i); // Erase element and resize array.
//			g_playerFire.shrink_to_fit();
//			// Options:
//			break;
//		}
//	}
//	// Pause 'X' key and change state to new EndState.
//	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
//	{
//		cout << "Change to EndState" << endl;
//		STMA::ChangeState(new EndState());
//	}
//	
//}
//
//void GameState::Render()
//{
//	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
//	SDL_RenderClear(Engine::Instance().GetRenderer());
//	SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pBGTexture, NULL, &g_BG1);
//	SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pPlayerHumanTexture, &g_player->m_src, &g_player->m_dst);
//	for (unsigned i = 0; i < g_playerFire.size(); i++)
//	{
//		SDL_RenderCopy(Engine::Instance().GetRenderer(), g_pPlayerWeaponTexture,
//			&(g_playerFire[i]->m_src), &(g_playerFire[i]->m_dst));
//	}
//	// This code below prevents SDL_RenderPresent from running twice in one frame.
//	if(dynamic_cast<GameState*>(STMA::GetStates().back())) // If current state is GameState.
//		State::Render();
//	
//}
//
//void GameState::Exit()
//{
//	cout << "Exiting GameState..." << endl;
//	for (unsigned i = 0; i < g_playerFire.size(); i++)
//	{
//		delete g_playerFire[i]; // Deallocates Missile through pointer.
//		g_playerFire[i] = nullptr; // Ensures no dangling pointer.
//	}
//	g_playerFire.clear(); // Removes all elements. Size = 0.
//	g_playerFire.shrink_to_fit(); // Sets capacity to size.
//	Mix_FreeMusic(m_sounds["track"]);
//	Mix_FreeChunk(m_sfx["shot"]);
//	Mix_FreeChunk(m_sfx["boom"]);
//	Mix_FreeChunk(g_pMissile);
//	SDL_DestroyTexture(g_pBGTexture);
//	SDL_DestroyTexture(g_pPlayerHumanTexture);
//}
//
//void GameState::Resume()
//{
//	cout << "Resuming GameState..." << endl;
//	// Resume music track.
//	Mix_ResumeMusic();
//}

EndState::EndState(){}

void EndState::Enter()
{
	cout << "Entering EndState..." << endl;
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Change to TitleState" << endl;
		// Pause the music track.
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 64, 125, 25);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting EndState..." << endl;
}

