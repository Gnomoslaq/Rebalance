namespace GOTHIC_NAMESPACE
{
    bool ShowPray;
    int BarValues;
    bool zUtilitesEnemyBarAbove;
    int crimeuserposx, crimeuserposy;

    // pointer to bar 
    oCViewStatusBar* staminaBar = NULL;
    zCView* valueViewStamina;
    zCView* valueViewHp;
    zCView* valueViewMana;
    zCView* valueViewFocus;


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

    // clear of text values
    void newBar_ClearValue()
    {
        delete (valueViewStamina); valueViewStamina = 0;
        delete (valueViewHp); valueViewHp = 0;
        delete (valueViewMana); valueViewMana = 0;
        delete (valueViewFocus); valueViewFocus = 0;
    }

    // update of bar values
    void newBar_UpdateValue()
    {
        // Bar value and range
        auto atr_stamina = parser->GetSymbol("ATR_STAMINA");
        auto atr_stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");

        auto atr_mana = player->GetAttribute(NPC_ATR_MANA);
        auto atr_mana_max = player->GetAttribute(NPC_ATR_MANAMAX);

        auto atr_hp = player->GetAttribute(NPC_ATR_HITPOINTS);
        auto atr_hp_max = player->GetAttribute(NPC_ATR_HITPOINTSMAX);


        if (atr_stamina && atr_stamina_max)
        {
            staminaBar->SetValue(atr_stamina->single_intdata);
            staminaBar->SetMaxRange(0, atr_stamina_max->single_intdata * 10);
            staminaBar->SetRange(0, atr_stamina_max->single_intdata * 10);
        }

        // Bars value
        if (ogame->GetShowPlayerStatus())
        {
            if (BarValues == 0)
            {
                newBar_ClearValue();
            }

            if (BarValues == 1)
            {
                if (!playerHelper.IsBusy() && !playerHelper.OnPause() && player->GetBodyState() != BS_DIVE && staminaBar)
                {
                    newBar_ClearValue();
                    {
                        int xs, ys, xh, yh, xm, ym, xf, yf;
                        int sx, sy, sx2, sy2, sx3, sy3;
                        // Stamina
                        {
                            staminaBar->GetPos(xs, ys);
                            ys = ys - 50 - screen->FontY();
                            auto msgs = zSTRING{ atr_stamina->single_intdata } + zSTRING{ "/" } + zSTRING{ atr_stamina_max->single_intdata * 10 };
                            auto msglen = screen->FontSize(msgs);
                            xs = 4096 - msglen / 2;
                            // printing
                            screen->Print(xs, ys, msgs);
                        }

                        // Hp
                        {
                            ogame->hpBar->GetPos(xh, yh);
                            ogame->hpBar->GetSize(sx, sy);
                            yh = yh - 50 - screen->FontY();
                            auto msgh = zSTRING{ atr_hp } + zSTRING{ "/" } + zSTRING{ atr_hp_max};
                            auto msglen = screen->FontSize(msgh);
                            xh = (xh + sx / 2) - msglen / 2;
                            // printing
                            screen->Print(xh, yh, msgh);
                        }

                        // Mana
                        {
                            ogame->manaBar->GetPos(xm, ym);
                            ogame->manaBar->GetSize(sx2, sy2);
                            ym = ym - 50 - screen->FontY();
                            auto msgm = zSTRING{ atr_mana } + zSTRING{ "/" } + zSTRING{ atr_mana_max };
                            auto msglen = screen->FontSize(msgm);
                            xm = (xm + sx2 / 2) - msglen / 2;
                            // printing
                            screen->Print(xm, ym, msgm);
                        }

                        // Focus
                        {
                            if (zUtilitesEnemyBarAbove == 0)
                            {
                                if (player->GetFocusNpc() != 0)
                                {
                                    oCViewStatusBar* focusbar = ogame->focusBar;
                                    focusbar->GetPos(xf, yf);
                                    focusbar->GetSize(sx3, sy3);

                                    int focushp = focusbar->currentValue;
                                    int focusmaxhp = focusbar->maxHigh;

                                    yf = yf + 50 + screen->FontY();
                                    auto msgf = zSTRING{ focushp } + zSTRING{ "/" } + zSTRING{ focusmaxhp };
                                    auto msglen = screen->FontSize(msgf);
                                    xf = (xf + sx3 / 2) - msglen / 2;

                                    valueViewFocus = new zCView(0, 0, 8192, 8192);
                                    screen->InsertItem(valueViewFocus);
                                    valueViewFocus->Print(xf, yf, msgf);
                                    //screen->Print(xf, yf, msgf);
                                }
                            }
                            if (zUtilitesEnemyBarAbove == 1)
                            {
                                if (player->GetFocusNpc() != 0)
                                {
                                    oCViewStatusBar* focusbar = ogame->focusBar;
                                    focusbar->GetPos(xf, yf);
                                    focusbar->GetSize(sx3, sy3);

                                    int focushp = focusbar->currentValue;
                                    int focusmaxhp = focusbar->maxHigh;

                                    yf = yf - 50 - screen->FontY();
                                    auto msgf = zSTRING{ focushp } + zSTRING{ "/" } + zSTRING{ focusmaxhp };
                                    auto msglen = screen->FontSize(msgf);
                                    xf = (xf + sx3 / 2) - msglen / 2;

                                    valueViewFocus = new zCView(0, 0, 8192, 8192);
                                    screen->InsertItem(valueViewFocus);
                                    valueViewFocus->Print(xf, yf, msgf);
                                    //screen->Print(xf, yf, msgf);
                                }
                            }
                        }
                    }
                }
            }

            if (BarValues == 2)
            {
                if (!playerHelper.IsBusy() && !playerHelper.OnPause() && player->GetBodyState() != BS_DIVE && staminaBar)
                {
                    newBar_ClearValue();
                    {
                        int xs, ys, xh, yh, xm, ym, xf, yf;
                        int sx, sy, sx2, sy2, sx3, sy3;
                        // Stamina
                        {
                            staminaBar->GetPos(xs, ys);
                            ys = ys - 50 - screen->FontY();
                            auto msgs = zSTRING {"Wytrzyma³oœæ: "} + zSTRING{atr_stamina->single_intdata} + zSTRING{"/"} + zSTRING{atr_stamina_max->single_intdata * 10};
                            auto msglen = screen->FontSize(msgs);
                            xs = 4096 - msglen / 2;
                            // printing
                            screen->Print(xs, ys, msgs);
                        }

                        // Hp
                        {
                            ogame->hpBar->GetPos(xh, yh);
                            ogame->hpBar->GetSize(sx, sy);
                            yh = yh - 50 - screen->FontY();
                            auto msgh = zSTRING {"Zdrowie: "} + zSTRING{atr_hp} + zSTRING{"/"} + zSTRING{atr_hp_max};
                            auto msglen = screen->FontSize(msgh);
                            xh = (xh + sx / 2) - msglen / 2;
                            // printing
                            screen->Print(xh, yh, msgh);
                        }

                        // Mana
                        {
                            ogame->manaBar->GetPos(xm, ym);
                            ogame->manaBar->GetSize(sx2, sy2);
                            ym = ym - 50 - screen->FontY();
                            auto msgm = zSTRING {"Mana: "} + zSTRING{atr_mana} + zSTRING{"/"} + zSTRING{atr_mana_max};
                            auto msglen = screen->FontSize(msgm);
                            xm = (xm + sx2 / 2) - msglen / 2;
                            // printing
                            screen->Print(xm, ym, msgm);
                        }

                        // Focus
                        {
                            if (zUtilitesEnemyBarAbove == 0)
                            {
                                if (player->GetFocusNpc() != 0)
                                {
                                    oCViewStatusBar* focusbar = ogame->focusBar;
                                    focusbar->GetPos(xf, yf);
                                    focusbar->GetSize(sx3, sy3);

                                    int focushp = focusbar->currentValue;
                                    int focusmaxhp = focusbar->maxHigh;

                                    yf = yf + 50 + screen->FontY();
                                    auto msgf = zSTRING{ focushp } + zSTRING{ "/" } + zSTRING{ focusmaxhp };
                                    auto msglen = screen->FontSize(msgf);
                                    xf = (xf + sx3 / 2) - msglen / 2;

                                    valueViewFocus = new zCView(0, 0, 8192, 8192);
                                    screen->InsertItem(valueViewFocus);
                                    valueViewFocus->Print(xf, yf, msgf);
                                    //screen->Print(xf, yf, msgf);
                                }
                            }
                            if (zUtilitesEnemyBarAbove == 1)
                            {
                                if (player->GetFocusNpc() != 0)
                                {
                                    oCViewStatusBar* focusbar = ogame->focusBar;
                                    focusbar->GetPos(xf, yf);
                                    focusbar->GetSize(sx3, sy3);

                                    int focushp = focusbar->currentValue;
                                    int focusmaxhp = focusbar->maxHigh;

                                    yf = yf - 50 - screen->FontY();
                                    auto msgf = zSTRING{ focushp } + zSTRING{ "/" } + zSTRING{ focusmaxhp };
                                    auto msglen = screen->FontSize(msgf);
                                    xf = (xf + sx3 / 2) - msglen / 2;

                                    valueViewFocus = new zCView(0, 0, 8192, 8192);
                                    screen->InsertItem(valueViewFocus);
                                    valueViewFocus->Print(xf, yf, msgf);
                                    //screen->Print(xf, yf, msgf);
                                }
                            }
                        }
                    }
                }
            }

            if (BarValues == 3)
            {
                auto stamina = parser->GetSymbol("ATR_STAMINA");
                auto stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");
                oCViewStatusBar* focusbar = ogame->focusBar;
                int focushp = focusbar->currentValue;
                int focusmaxhp = focusbar->maxHigh;

                newBar_ClearValue();

                auto strS = zSTRING{ stamina->single_intdata } + zSTRING{ "/" } + zSTRING{ stamina_max->single_intdata * 10 };
                auto strH = zSTRING{ atr_hp } + zSTRING{ "/" } + zSTRING{ atr_hp_max };
                auto strM = zSTRING{ atr_mana } + zSTRING{ "/" } + zSTRING{ atr_mana_max };
                auto strF = zSTRING{ focushp } + zSTRING{ "/" } + zSTRING{ focusmaxhp };

                valueViewStamina = new zCView(0, 0, 8192, 8192);
                valueViewHp = new zCView(0, 0, 8192, 8192);
                valueViewMana = new zCView(0, 0, 8192, 8192);
                valueViewFocus = new zCView(0, 0, 8192, 8192);

                zCView* ownerviewS = staminaBar->range_bar;
                zCView* ownerviewH = ogame->hpBar->range_bar;
                zCView* ownerviewM = ogame->manaBar->range_bar;
                zCView* ownerviewF = ogame->focusBar->range_bar;


                ownerviewS->InsertItem(valueViewStamina);
                ownerviewH->InsertItem(valueViewHp);
                ownerviewM->InsertItem(valueViewMana);
                ownerviewF->InsertItem(valueViewFocus);

                valueViewStamina->PrintCXY(strS);
                valueViewHp->PrintCXY(strH);
                valueViewMana->PrintCXY(strM);
                valueViewFocus->PrintCXY(strF);
            };
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

                    int posx, posy1, posy2;
                    if (crimeuserposx == 0 && crimeuserposy == 0)
                    {
                        ogame->manaBar->GetPos(posx, posy1);
                        posy1 = 7200;
                        posy2 = 7400;
                    }
                    if (crimeuserposx != 0 || crimeuserposy != 0)
                    {
                        posx = crimeuserposx;
                        posy1 = crimeuserposy;
                        posy2 = posy1 + 200;
                    }


                    auto originalcolor = screen->fontColor;

                    // 
                    if (screen && !playerHelper.OnPause())
                    {

                        auto msgInnos = zSTRING{ "Innos: " };
                        auto msgBeliar = zSTRING{ "Beliar: " };

                        auto msgInnosLen = screen->FontSize(msgInnos);
                        auto msgBeliarLen = screen->FontSize(msgBeliar);

                        //7584
                        screen->Print(posx, posy1, msgInnos);
                        screen->Print(posx, posy2, msgBeliar);

                        if (player_guild != 1 && player_guild != 4)
                        {
                            if (PrayIdolDay->single_intdata == GetDay)
                            {
                                screen->SetFontColor(originalcolor);
                                screen->Print(posx + msgBeliarLen, posy2, Beliar->single_intdata);
                            }
                            screen->SetFontColor(originalcolor);

                            // PrayIdolDay != Get Day
                            if (PrayIdolDay->single_intdata != GetDay)
                            {
                                screen->SetFontColor(zCOLOR(255, 0, 0));
                                screen->Print(posx + msgBeliarLen, posy2, Beliar->single_intdata);
                            }
                            screen->SetFontColor(originalcolor);


                        }

                        if (player_guild == 1 || player_guild == 4)
                        {
                            screen->SetFontColor(originalcolor);
                            screen->Print(posx + msgBeliarLen, posy2, Beliar->single_intdata);
                        }

                        // PrayDay == GetDay
                        if (PrayDay->single_intdata == GetDay)
                        {
                            screen->SetFontColor(originalcolor);
                            screen->Print(posx + msgBeliarLen, posy1, Innos);
                        }
                        screen->SetFontColor(originalcolor);

                        // PrayDay != GetDay
                        if (PrayDay->single_intdata != GetDay)
                        {
                            screen->SetFontColor(zCOLOR(255, 0, 0));
                            screen->Print(posx + msgBeliarLen, posy1, Innos);
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
            newBar_PrayCount();
        }

        if (screen && staminaBar && playerHelper.OnPause() || playerHelper.IsBusy() || player->GetBodyState() == BS_DIVE || newStatusMenu->MenuActive)
        {
            screen->RemoveItem(staminaBar);
        }
    }


}