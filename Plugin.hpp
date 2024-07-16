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
		newPickPocket = std::make_unique<NewPickPocket>();

		newStatusMenu->UpdateStatusMenu();
		UpdatePluginSettings();
		ReadSprintBinds();
	}
	
	void Game_ApplyOptions()
	{
		UpdatePluginSettings();
		ReadSprintBinds();
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
		newPickPocket->Loop();

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

	void LoadBegin() {
	}

	void LoadEnd() {
		newPickPocket->GetPickPocket();
	}

	void Game_SaveBegin()
	{

	}

	void Game_SaveEnd()
	{

	}

	void Game_LoadBegin_NewGame()
	{
		LoadBegin();
	}

	void Game_LoadEnd_NewGame()
	{
		LoadEnd();
	}

	void Game_LoadBegin_SaveGame()
	{
		LoadBegin();
	}

	void Game_LoadEnd_SaveGame()
	{
		LoadEnd();
	}

	void Game_LoadBegin_ChangeLevel()
	{
		LoadBegin();
	}

	void Game_LoadEnd_ChangeLevel()
	{
		LoadEnd();
	}

	void Game_LoadBegin_Trigger()
	{

	}

	void Game_LoadEnd_Trigger()
	{

	}

	void Game_DefineExternals()
	{
		//parser->DefineExternal("wld_gettimemin", wld_gettimemin, zPAR_TYPE_INT, zPAR_TYPE_VOID);
	}

	
}