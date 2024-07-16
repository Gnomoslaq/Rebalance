namespace GOTHIC_NAMESPACE
{
    // pointer to bar 
    oCViewStatusBar* staminaBar = NULL;

    // Texture of the bar strip
    const zSTRING newBar_bar = "BAR_misc.tga";

    // updating the position and size of the new bar
    void newBar_UpdatePosAndSizes()
    {
        // We can get size of new bar from other bars or make a new one
        if (ogame && ogame->hpBar && staminaBar)
        {
            int sx, sy;

            // hpBar sizes
            ogame->hpBar->GetSize(sx, sy);

            // setting same sizes from hpBar
            // staminaBar->SetSize(sx, sy);
            staminaBar->SetSize(1000, sy);
            int x, y;

            // get health bar position
            ogame->hpBar->GetPos(x, y);
            // 3596 <- center of screen - half of bar width
            staminaBar->SetPos(3596, y);
        }
    }

    // update of bar values
    void newBar_UpdateValue()
    {
        // Bar value and range
        auto atr_stamina = parser->GetSymbol("ATR_STAMINA");
        auto atr_stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");

        if (atr_stamina && atr_stamina_max)
        {
            staminaBar->SetValue(atr_stamina->single_intdata);
            staminaBar->SetMaxRange(0, atr_stamina_max->single_intdata * 10);
            staminaBar->SetRange(0, atr_stamina_max->single_intdata * 10);
        }

    }

    // Hooking the function of updating bar values
    auto Hook_oCGame_UpdatePlayerStatus_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x006C3140), &oCGame::UpdatePlayerStatus_Union);
    void oCGame::UpdatePlayerStatus_Union()
    {
		zSTRING originalname;
		auto focusNpc = player->GetFocusNpc();

		if (focusNpc && newPickPocket->HasPickPocketDialogue(focusNpc, true) && bShowPickPocket)
		{
			auto atr_dex = player->GetAttribute(NPC_ATR_DEXTERITY);
			auto atr_steal = parser->GetSymbol("atr_pickpocket");
			auto focusdex = focusNpc->GetAttribute(NPC_ATR_DEXTERITY);
			zSTRING focusNpcName = focusNpc->name[0];
			originalname = focusNpc->name[0];

			auto chance = (((atr_dex * 100 + atr_steal->single_intdata * 100) / focusdex));
			if (chance > 100)
			{
				chance = 100;
			}
			focusNpc->name[0] = focusNpcName + zSTRING{ " " } + zSTRING{ chance } + zSTRING{ "%" };
		}

        (this->*Hook_oCGame_UpdatePlayerStatus_Union)();

		auto focusNpc2 = player->GetFocusNpc();
		if (focusNpc2 && newPickPocket->HasPickPocketDialogue(focusNpc, true) && bShowPickPocket)
		{
			focusNpc2->name[0] = originalname;
		}

        auto valueView = new zCView(0, 0, 8192, 8192);

        // if no bar
        if (!staminaBar)
        {
            // create new bar
            staminaBar = new oCViewStatusBar();

            // if there's screen and new bar
            if (screen && staminaBar)
            {
                // add bar to screen
                screen->InsertItem(staminaBar, FALSE);

                // bar initialization at zero coordinates and scaling x1
                staminaBar->Init(0, 0, 1.0);

                // setting textures for bar
                staminaBar->SetTextures("BAR_BACK.TGA", "BAR_TEMPMAX.TGA", newBar_bar, "");

                // update position and size of new bar
                newBar_UpdatePosAndSizes();

                // after initialization remove bar from screen
                screen->RemoveItem(staminaBar);
            }
        }

        if (screen && staminaBar)
        {
            // remove bar from screen
            screen->RemoveItem(staminaBar);

            // insert bar to screen, placing it in the foreground when rendering zCView elements.
            screen->InsertItem(staminaBar, FALSE);

            // update bar values
            newBar_UpdateValue();
        }

        if (screen && staminaBar && playerHelper.OnPause() || playerHelper.IsBusy() || player->GetBodyState() == BS_DIVE || newStatusMenu->MenuActive)
        {
            screen->RemoveItem(staminaBar);
        }

    }
}