namespace GOTHIC_NAMESPACE
{
	static constexpr std::string_view PluginName = "Rebalance";
	static constexpr std::string_view zUtilities = "ZUTILITIES";

	zSTRING SprintKey;
	int zUtilitiesbars;

	void ReadSprintBinds()
	{
		newSprint->sprintkeys.DeleteList();
		void* buffer = 0;
		unsigned long bindSize = 0;
		bindSize = zoptions->ReadRaw("KEYS", "keySprint", buffer, newSprint->sprintkeys.GetArray(), newSprint->sprintkeys.GetNumInList() << 1);
		newSprint->sprintkeys.DeleteList();
		for (int i = 0; i < bindSize >> 1; i++)
		{
			if (((unsigned short*)buffer)[i] != 0)
			{
				newSprint->sprintkeys.Insert(((unsigned short*)buffer)[i]);
			}
		}
		delete[] buffer;
	}

	void UpdatePluginSettings()
	{
		ReadSprintBinds();
		ShowPray = zoptions->ReadBool(PluginName.data(), "ShowPray", true);
		BarValues = zoptions->ReadInt(PluginName.data(), "BarValues", 0);
		ShowPrayMessage = zoptions->ReadBool(PluginName.data(), "ShowPrayMessage", 1);
		zUtilitiesbars = zoptions->ReadInt(zUtilities.data(), "StatusBarValueMode", 0);
		zUtilitesEnemyBarAbove = zoptions->ReadBool(zUtilities.data(), "ShowEnemyBarAboveHim", 0);
	}

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
	}

	void Game_PreLoop()
	{
		//GAME PRE LOOP
	}

	float timer;

	void Game_Loop()
	{
		if (zUtilitiesbars != 0 && BarValues != 0)
		{
			screen->PrintCXY("Zdublowane wyświetlanie wartości pasków, wyłącz jedne z nich!");
		}



		auto stamina = parser->GetSymbol("ATR_STAMINA");
		auto stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");

		if (ShowPrayMessage)
		{
			PrayMessage();
		}
		
		newSprint->Loop();
		newSprint->SprintTick();

		/*
		timer += ztimer->frameTimeFloat; // wersja zalezna od factormotion (szybciej spierdala na przyspieszeniu)
		//timer += ztimer->frameTimeFloat / ztimer->factorMotion; // wersja zalezna od czasu rzeczywistego

		if (timer < 1000.0f)
		{
			return;
		}

		timer -= 1000.0f;

		if (newSprint->SprintActive && stamina->single_intdata > 0)
		{
			int StaminaTick = 5;

			if (stamina->single_intdata >= StaminaTick)
			{
				stamina->single_intdata = stamina->single_intdata - StaminaTick;
			}
			if (stamina->single_intdata < StaminaTick)
			{
				stamina->single_intdata = 0;
			}
		}
		*/
		
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
		//GAME DEFINE EXTERNALS
	}

	
}