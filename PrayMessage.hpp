namespace GOTHIC_NAMESPACE
{
	class PrayMessage
	{
	public:
        void Loop()
        {
            LoopMessage();
            LoopCount();
        }

		void LoopMessage()
		{
			if (!bShowPrayMessage)
			{
				return;
			}

			auto InnosP = parser->GetSymbol("INNOSPRAYCOUNT");
			auto InnosC = parser->GetSymbol("INNOSCRIMECOUNT");
			int InnosA = InnosP->single_intdata - InnosC->single_intdata;
			auto BeliarP = parser->GetSymbol("BELIARPRAYCOUNT");

			auto oldInnos = parser->GetSymbol("oldInnos");
			auto oldBeliar = parser->GetSymbol("oldBeliar");

			auto printcolorred = zCOLOR(GFX_RED);
			auto printcolorgreen = zCOLOR(GFX_GREEN);
			if (oldInnos->single_intdata != InnosA || oldBeliar->single_intdata != BeliarP->single_intdata)
			{
				if (oldInnos->single_intdata > InnosA)
				{
                    auto msg = zSTRING{ "Karma Innosa -" } + zSTRING{ oldInnos->single_intdata - InnosA };
					ogame->GetTextView()->Printwin(msg);
					oldInnos->single_intdata = InnosA;
					return;
				}
				if (oldInnos->single_intdata < InnosA)
				{
					auto msg = zSTRING{ "Karma Innosa +" } + zSTRING{ InnosA - oldInnos->single_intdata };
					ogame->GetTextView()->Printwin(msg);
					oldInnos->single_intdata = InnosA;
					return;
				}

				if (oldBeliar->single_intdata > BeliarP->single_intdata)
				{
					auto msg = zSTRING{ "Karma Beliara -" } + zSTRING{ oldBeliar->single_intdata - BeliarP->single_intdata };
					ogame->GetTextView()->Printwin(msg);
					oldBeliar->single_intdata = BeliarP->single_intdata;
					return;
				}
				if (oldBeliar->single_intdata < BeliarP->single_intdata)
				{
					auto msg = zSTRING{ "Karma Beliara +" } + zSTRING{ BeliarP->single_intdata - oldBeliar->single_intdata };
					ogame->GetTextView()->Printwin(msg);
					oldBeliar->single_intdata = BeliarP->single_intdata;
					return;
				}
			}

		}

        void LoopCount()
        {
            if (!bShowPray)
            {
                return;
            }
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
                        if (bCrimeUserPosX == 0 && bCrimeUserPosY == 0)
                        {
                            ogame->manaBar->GetPos(posx, posy1);
                            posy1 = 7200;
                            posy2 = 7400;
                        }
                        if (bCrimeUserPosX != 0 || bCrimeUserPosY != 0)
                        {
                            posx = bCrimeUserPosX;
                            posy1 = bCrimeUserPosY;
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
	};
	std::unique_ptr<PrayMessage> prayMessage;


















}