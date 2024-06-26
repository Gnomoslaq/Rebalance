namespace GOTHIC_NAMESPACE
{
    bool ShowPray;
    int StaminaValues;
    bool StaminaText;

    // pointer to bar (not specified by default)
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
        auto symbol1 = parser->GetSymbol("ATR_STAMINA");
        auto symbol2 = parser->GetSymbol("ATR_STAMINA_MAX");

        auto ZombieKilled = parser->GetSymbol("ZombieKilled");

        if (symbol1 && symbol2)
        {
            staminaBar->SetValue(symbol1->single_intdata);
            staminaBar->SetMaxRange(0, symbol2->single_intdata * 10);
            staminaBar->SetRange(0, symbol2->single_intdata * 10);
        }

        // Stamina text
        if (ogame->GetShowPlayerStatus())
        {
            if (StaminaValues == 0)
            {

            }

            if (StaminaValues == 1)
            {
                if (!playerHelper.IsBusy() && !playerHelper.OnPause() && player->GetBodyState() != BS_DIVE && staminaBar)
                {
                    if (StaminaText == 0)
                    {
                        int x, y;
                        staminaBar->GetPos(x, y);
                        y = y - 50 - screen->FontY();
                        auto msg = zSTRING{ symbol1->single_intdata } + zSTRING{ "/" } + zSTRING{ symbol2->single_intdata * 10 };
                        auto msglen = screen->FontSize(msg);
                        x = 4096 - msglen / 2;
                        // printing
                        screen->Print(x, y, msg);
                    }

                    if (StaminaText == 1)
                    {
                        int x, y;
                        staminaBar->GetPos(x, y);
                        y = y - 50 - screen->FontY();
                        auto msg = zSTRING{ "Wytrzyma³oœæ: " } + zSTRING{ symbol1->single_intdata } + zSTRING{ "/" } + zSTRING{ symbol2->single_intdata * 10 };
                        auto msglen = screen->FontSize(msg);
                        x = 4096 - msglen / 2;
                        // printing
                        screen->Print(x, y, msg);
                    }

                }
            }

            if (StaminaValues == 2)
            {
                if (StaminaText == 0)
                {
                    int x, y;
                    staminaBar->GetPos(x, y);
                    y = y - 50 - screen->FontY();
                    auto msg = zSTRING{ symbol1->single_intdata } + zSTRING{ "/" } + zSTRING{ symbol2->single_intdata * 10 };
                    auto msglen = screen->FontSize(msg);
                    x = 4096 - msglen / 2;
                    // printing
                    screen->Print(x, y, msg);
                }

                if (StaminaText == 1)
                {
                    int x, y;
                    staminaBar->GetPos(x, y);
                    y = y - 50 - screen->FontY();
                    auto msg = zSTRING{ "Wytrzyma³oœæ: " } + zSTRING{ symbol1->single_intdata } + zSTRING{ "/" } + zSTRING{ symbol2->single_intdata * 10 };
                    auto msglen = screen->FontSize(msg);
                    x = 4096 - msglen / 2;
                    // printing
                    screen->Print(x, y, msg);
                }
            }

        }


    }

    // pray count 
    void newBar_PrayCount()
    {
        if (ShowPray)
        {
            // Karma 
            if (staminaBar && player)
            {
                auto InnosPray = parser->GetSymbol("INNOSPRAYCOUNT");
                auto InnosCrime = parser->GetSymbol("INNOSCRIMECOUNT");
                auto Beliar = parser->GetSymbol("BELIARPRAYCOUNT");

                if (InnosPray && InnosCrime && Beliar)
                {
                    int Innos = InnosPray->single_intdata - InnosCrime->single_intdata;

                    auto PrayDay = parser->GetSymbol("PRAYDAY");
                    auto PrayIdolDay = parser->GetSymbol("PrayIdolDay");
                    auto player_guild = player->guild;

                    auto GetDay = ogame->wldTimer->GetDay();

                    int posx, posy;
                    ogame->manaBar->GetPos(posx, posy);

                    auto originalcolor = screen->fontColor;

                    // 
                    if (screen && !playerHelper.OnPause())
                    {

                        auto msgInnos = zSTRING{ "Innos: " };
                        auto msgBeliar = zSTRING{ "Beliar: " };

                        auto msgInnosLen = screen->FontSize(msgInnos);
                        auto msgBeliarLen = screen->FontSize(msgBeliar);

                        //7584
                        screen->Print(posx, 7200, msgInnos);
                        screen->Print(posx, 7400, msgBeliar);

                        if (player_guild != 1 && player_guild != 4)
                        {
                            if (PrayIdolDay->single_intdata == GetDay)
                            {
                                screen->SetFontColor(originalcolor);
                                screen->Print(posx + msgBeliarLen, 7400, Beliar->single_intdata);
                            }
                            screen->SetFontColor(originalcolor);

                            // PrayIdolDay != Get Day
                            if (PrayIdolDay->single_intdata != GetDay)
                            {
                                screen->SetFontColor(zCOLOR(255, 0, 0));
                                screen->Print(posx + msgBeliarLen, 7400, Beliar->single_intdata);
                            }
                            screen->SetFontColor(originalcolor);


                        }

                        if (player_guild == 1 || player_guild == 4)
                        {
                            screen->SetFontColor(originalcolor);
                            screen->Print(posx + msgBeliarLen, 7400, Beliar->single_intdata);
                        }

                        // PrayDay == GetDay
                        if (PrayDay->single_intdata == GetDay)
                        {
                            screen->SetFontColor(originalcolor);
                            screen->Print(posx + msgBeliarLen, 7200, Innos);
                        }
                        screen->SetFontColor(originalcolor);

                        // PrayDay != GetDay
                        if (PrayDay->single_intdata != GetDay)
                        {
                            screen->SetFontColor(zCOLOR(255, 0, 0));
                            screen->Print(posx + msgBeliarLen, 7200, Innos);
                        }
                        screen->SetFontColor(originalcolor);
                    }
                }
            }

        }
    }

    // Hooking the function of updating bar values
    auto Hook_oCGame_UpdatePlayerStatus_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x006C3140), &oCGame::UpdatePlayerStatus_Union);
    void oCGame::UpdatePlayerStatus_Union()
    {
        (this->*Hook_oCGame_UpdatePlayerStatus_Union)();

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
            newBar_PrayCount();
        }

        if (screen && staminaBar && playerHelper.OnPause() || playerHelper.IsBusy() || player->GetBodyState() == BS_DIVE || newStatusMenu->MenuActive)
        {
            screen->RemoveItem(staminaBar);
        }
    }



}