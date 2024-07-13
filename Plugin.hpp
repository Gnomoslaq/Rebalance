namespace GOTHIC_NAMESPACE
{
	float timer;

	void Game_Entry()
	{
		//GAME ENTRY
	}

	void Game_Init()
	{
		//auto PluginKey = parser->GetSymbol("PluginKey");
		/*if (PluginKey->single_intdata != 3891)
		{
			gameMan->ExitGame();
		}
		*/
		
		statusBar = std::make_unique<StatusBar>();
		newStatusMenu = std::make_unique<NewStatusMenu>();
		prayMessage = std::make_unique<PrayMessage>();
		newSprint = std::make_unique<NewSprint>();

		newStatusMenu->UpdateStatusMenu();
		UpdatePluginSettings();
	}
	
	void Game_ApplyOptions()
	{
		UpdatePluginSettings();
		newStatusMenu->UpdateStatusMenu();
		newBar_UpdatePosAndSizes();
	}

	void Game_PreLoop()
	{
		//GAME PRE LOOP
	}



	void Game_Loop()
	{
		prayMessage->Loop();
		newSprint->Loop();
		newSprint->SprintTick();
		statusBar->Loop();

		if (!ogame->GetShowPlayerStatus())
		{
			statusBar->ClearValue();
		}

	}

	void Game_PostLoop()
	{
		//GAME POST LOOP
	}

	void Game_MenuLoop()
	{
			
	}

	void Game_Exit()
	{
		newStatusMenu.release();
		newSprint.release();
		statusBar.release();
		prayMessage.release();
	}

	void Game_Pause()
	{
		statusBar->ClearValue();
	}

	void Game_Unpause()
	{

	}

	void Game_SaveBegin()
	{
		//GAME SAVE BEGIN
	}

	void Game_SaveEnd()
	{
		//GAME SAVE END
	}

	void Game_LoadBegin_NewGame()
	{
		//GAME LOAD BEGIN NEW GAME
	}

	void Game_LoadEnd_NewGame()
	{
		//GAME LOAD END NEW GAME
	}

	void Game_LoadBegin_SaveGame()
	{
		//GAME LOAD BEGIN SAVE GAME
	}

	void Game_LoadEnd_SaveGame()
	{

	}

	void Game_LoadBegin_ChangeLevel()
	{
		//GAME LOAD BEGIN CHANGE LEVEL
	}

	void Game_LoadEnd_ChangeLevel()
	{
		//GAME LOAD END CHANGE LEVEL
	}

	void Game_LoadBegin_Trigger()
	{
		//GAME LOAD BEGIN TRIGGER
	}

	void Game_LoadEnd_Trigger()
	{
		//GAME LOAD END TRIGGER
	}

	void Game_DefineExternals()
	{
		//parser->DefineExternal("wld_gettimemin", wld_gettimemin, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	}

	
}