namespace GOTHIC_NAMESPACE
{
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
		

		newStatusMenu = std::make_unique<NewStatusMenu>();


		newStatusMenu->UpdateStatusMenu();



		newSprint = std::make_unique<NewSprint>();

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

	float timer;

	void Game_Loop()
	{
		if (!ogame->GetShowPlayerStatus())
		{
			newBar_ClearValue();
		}

		if (!ogame->focusBar)
		{
			delete (valueViewFocus); valueViewFocus = 0;
		}


		if (zUtilitiesbars != 0 && BarValues != 0)
		{
			screen->PrintCXY("Zdublowane wyświetlanie wartości pasków, wyłącz jedne z nich!");
		}

		if (ShowPrayMessage)
		{
			PrayMessage();
		}
		
		newSprint->Loop();
		newSprint->SprintTick();

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
	}

	void Game_Pause()
	{
		newBar_ClearValue();
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