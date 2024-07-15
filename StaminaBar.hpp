namespace GOTHIC_NAMESPACE
{
    std::vector<oCInfo*> pickpocketInfos;

	static bool forcetrue = false;

	bool ShowPickPocketSign, PickPocketAmbientNPCs, ImmersiveMode, GiveAmbientXP;

    bool CanBePickPocket(oCNpc* npc)
    {
     zSTRING focusname = npc->GetInstanceName();
     zSTRING string = zSTRING{ "dia_" } + focusname + zSTRING{ "_pickpocket_doit" };

     auto cond = parser->GetSymbol(string);
     if (cond)
     {
         return true;
     }
     else
     {
         return false;
     }
    }

	bool oCNpc::GiveItemsTo_Union(oCNpc* target, int itemInstanz, int itemAmount)
	{
		if (itemInstanz == -1)
		{
			return false;
		}

		static auto GiveInvItemsIndex = parser->GetIndex("b_giveinvitems");
		if (GiveInvItemsIndex == -1)
		{
			return false;
		}

		static auto GiveInvItemsSymbol = parser->GetSymbol(GiveInvItemsIndex);
		if (!GiveInvItemsSymbol || GiveInvItemsSymbol->type != zPAR_TYPE_FUNC || GiveInvItemsSymbol->ele != 4)
		{
			return false;
		}

		static auto argumentSymbolGiver = []() -> zCPar_Symbol*
			{
				auto symbol = parser->GetSymbol(GiveInvItemsIndex + 1);
				if (!symbol || symbol->type != zPAR_TYPE_INSTANCE)
				{
					return nullptr;
				}

				return symbol;
			}();

		static auto argumentSymbolTaker = []() -> zCPar_Symbol*
			{
				auto symbol = parser->GetSymbol(GiveInvItemsIndex + 2);
				if (!symbol || symbol->type != zPAR_TYPE_INSTANCE)
				{
					return nullptr;
				}

				return symbol;
			}();

		static auto argumentSymbolItem = []() -> zCPar_Symbol*
			{
				auto symbol = parser->GetSymbol(GiveInvItemsIndex + 3);
				if (!symbol || symbol->type != zPAR_TYPE_INT)
				{
					return nullptr;
				}

				return symbol;
			}();

		static auto argumentSymbolAmount = []() -> zCPar_Symbol*
			{
				auto symbol = parser->GetSymbol(GiveInvItemsIndex + 4);
				if (!symbol || symbol->type != zPAR_TYPE_INT)
				{
					return nullptr;
				}

				return symbol;
			}();

		if (!argumentSymbolGiver || !argumentSymbolTaker || !argumentSymbolItem || !argumentSymbolAmount)
		{
			return false;
		}

		this->CreateItems(itemInstanz, itemAmount);

		parser->datastack.Clear();

		argumentSymbolGiver->offset = reinterpret_cast<int>(this);
		parser->datastack.Push(GiveInvItemsIndex + 1);

		argumentSymbolTaker->offset = reinterpret_cast<int>(target);
		parser->datastack.Push(GiveInvItemsIndex + 2);

		argumentSymbolItem->SetValue(itemInstanz, 0);
		parser->datastack.Push(itemInstanz);
		parser->datastack.Push(zPAR_TOK_PUSHINT);

		argumentSymbolAmount->SetValue(itemAmount, 0);
		parser->datastack.Push(itemAmount);
		parser->datastack.Push(zPAR_TOK_PUSHINT);

		int pos;
		GiveInvItemsSymbol->GetStackPos(pos, 0);
		parser->DoStack(pos);

		return true;
	}

	bool oCNpc::GiveItemsTo_Union(oCNpc* target, const zSTRING& itemInstanceName, int itemAmount)
	{
		return this->GiveItemsTo_Union(target, parser->GetIndex(itemInstanceName), itemAmount);
	}

	void GivePlayerXP(int XP)
	{
		static auto GiveXPIndex = []() -> int
			{
				if (auto idx = parser->GetIndex("B_GiveXP"); idx != -1)
				{
					return idx;
				}

				if (auto idx = parser->GetIndex("B_GivePlayerXP"); idx != -1)
				{
					return idx;
				}

				return -1;
			}();

		if (GiveXPIndex != -1)
		{
			parser->CallFunc(GiveXPIndex, XP);
		}
	}

	bool HasPickPocketDialogue(oCNpc* npc, bool checkcond = false)
	{
		for (auto info : pickpocketInfos)
		{
			if (info->GetNpcID() != npc->GetInstance())
			{
				continue;
			}

			if (checkcond)
			{
				forcetrue = true;

				parser->SetInstance("SELF", npc);
				parser->SetInstance("OTHER", player);

				auto cond = info->InfoConditions();
				forcetrue = false;

				if (!cond)
				{
					return false;
				}

				return true;
			}

			return true;
		}

		return false;
	}

	bool CanPickPocketAmbient(oCNpc* npc)
	{
		if (!PickPocketAmbientNPCs)
		{
			return false;
		}

		if (npc->npcType != 0
#if ENGINE < Engine_G2
			&& npc->npcType != 4
			&& npc->npcType != 6
#else
			&& npc->npcType != 3
			&& npc->npcType != 5
			&& npc->npcType != 6
#endif
			)
		{
			return false;
		}

		if (npc->guild > NPC_GIL_HUMANS)
		{
			return false;
		}

		if (npc->attribute[NPC_ATR_HITPOINTS] <= 0)
		{
			return false;
		}

		if (npc->GetAivar_Union(zSTRING{ "aiv_playerhaspickedmypocket" }))
		{
			return false;
		}

		return true;
	}

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

		if (focusNpc && HasPickPocketDialogue(focusNpc, true))
		{
			auto atr_dex = player->GetAttribute(NPC_ATR_DEXTERITY);
			auto atr_steal = parser->GetSymbol("atr_pickpocket");
			auto focusdex = focusNpc->GetAttribute(NPC_ATR_DEXTERITY);
			zSTRING focusNpcName = focusNpc->name[0];
			originalname = focusNpc->name[0];

			auto chance = (((atr_dex * 100 + atr_steal->single_intdata * 100) / focusdex));
			//focusNpc->name[0] = focusNpcName + zSTRING{ " %" };
			if (chance > 100)
			{
				chance = 100;
			}
			focusNpc->name[0] = focusNpcName + zSTRING{ " " } + zSTRING{ chance } + zSTRING{ "%" };
		}

        (this->*Hook_oCGame_UpdatePlayerStatus_Union)();

		auto focusNpc2 = player->GetFocusNpc();
		if (focusNpc2 && HasPickPocketDialogue(focusNpc, true))
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

	int oCNpc::GetAivar_Union(const zSTRING& aivar)
	{
		auto sym = parser->GetSymbol(aivar);
		if (!sym)
		{
			return -1;
		}

		return this->aiscriptvars[sym->single_intdata];
	}

	void oCNpc::SetAivar_Union(const zSTRING& aivar, int value)
	{
		auto sym = parser->GetSymbol(aivar);
		if (!sym)
		{
			return;
		}

		this->aiscriptvars[sym->single_intdata] = value;
	}

	int oCNpc::GetTalent_Union(const zSTRING& talent)
	{
		auto sym = parser->GetSymbol(talent);
		if (!sym)
		{
			return -1;
		}

		return this->GetTalentSkill(sym->single_intdata);
	}

	void oCNpc::AI_PlayAni_Union(const zSTRING& anim)
	{
		oCMsgConversation* msgPlayAni = new oCMsgConversation(oCMsgConversation::EV_PLAYANI_NOOVERLAY, anim);
		msgPlayAni->number = this->GetBodyState();
		msgPlayAni->SetHighPriority(true);
		this->GetEM()->OnMessage(msgPlayAni, this);
	}

	void GetPickPocket()
	{
		pickpocketInfos.clear();

		auto list = ogame->GetInfoManager()->infoList.next;
		while (list) {
			auto info = list->data;
			list = list->next;

			auto infoName = ::Union::StringANSI(info->name).MakeUpper();
			if (!infoName.Contains("PICKPOCKET") && !infoName.Contains("_STEAL") && !infoName.Contains("PICKME"))
			{
				continue;
			}

			if (infoName.Contains("_DOIT") || infoName.Contains("_TRY"))
			{
				continue;
			}

			if (parser->GetIndex(info->name + "_DOIT") == -1 && parser->GetIndex(info->name + "_TRY") == -1)
			{
				continue;
			}

			pickpocketInfos.push_back(info);
		}
	}

	/*
	void TryPickPocketAmbient(oCNpc* npc)
	{
		if (!PickPocketAmbientNPCs)
		{
			return;
		}

		if (npc->npcType != 0
#if ENGINE < Engine_G2
			&& npc->npcType != 4
			&& npc->npcType != 6
#else
			&& npc->npcType != 3
			&& npc->npcType != 5
			&& npc->npcType != 6
#endif
			)
		{
			return;
		}

		auto aivar = zSTRING{ "aiv_playerhaspickedmypocket" };

		if (npc->GetAivar_Union(aivar))
		{
			return;
		}

#if ENGINE >= Engine_G2
		auto Currency = oCItemContainer::GetCurrencyInstanceName();
#else
		auto Currency = zSTRING{ "ItMiNugget" };
#endif

		int XP = static_cast<int>(npc->level * 1.75f);

		if (!npc->GiveItemsTo_Union(player, Currency, randomizer.Random(1, XP)))
		{
			return;
		}

		if (GiveAmbientXP)
		{
			GivePlayerXP(XP);
		}

		npc->SetAivar_Union(aivar, 1);

		player->AI_PlayAni_Union(zSTRING{ "T_STEAL" });
	}
	*/

	void TryPickPocketDialogue(oCNpc* npc)
	{
		for (auto info : pickpocketInfos)
		{
			if (info->GetNpcID() != npc->GetInstance())
			{
				continue;
			}

			forcetrue = true;

			parser->SetInstance("SELF", npc);
			parser->SetInstance("OTHER", player);

			auto cond = info->InfoConditions();
			forcetrue = false;

			if (!cond)
			{
				return;
			}

			player->AI_PlayAni_Union(zSTRING{ "T_STEAL" });

			{
				auto idx = parser->GetIndex(info->name + "_DOIT");
				if (idx != -1)
				{
					parser->CallFunc(idx);
					return;
				}
			}
			{
				auto idx = parser->GetIndex(info->name + "_TRY");
				if (idx != -1)
				{

					parser->CallFunc(idx);
					return;
				}
			}
		}
	}

	void TryPickPocket(oCNpc* npc)
	{
		if (player->GetTalent_Union("npc_talent_pickpocket") <= 0)
		{
			return;
		}

		if (npc->guild > NPC_GIL_HUMANS)
		{
			return;
		}

		if (npc->attribute[NPC_ATR_HITPOINTS] <= 0)
		{
			return;
		}

		if (npc->IsUnconscious())
		{
			return;
		}

		if (player->GetDistanceToVob(*npc) > 200.0f)
		{
			return;
		}

		if (ImmersiveMode)
		{
			if (npc->GetWeaponMode() != NPC_WEAPON_NONE)
			{
				return;
			}

			if (player->anictrl->walkmode != ANI_WALKMODE_SNEAK)
			{
				return;
			}

			if (npc->CanSee(player, 0))
			{
				return;
			}
		}

		if (HasPickPocketDialogue(npc))
		{
			TryPickPocketDialogue(npc);
		}
	}

	bool CanBeActive()
	{
		if (!ogame)
		{
			return false;
		}

		if (ogame->singleStep)
		{
			return false;
		}

		if (ogame->pause_screen)
		{
			return false;
		}

		if (!player)
		{
			return false;
		}

		if (player->IsUnconscious())
		{
			return false;
		}

		if (player->attribute[NPC_ATR_HITPOINTS] <= 0)
		{
			return false;
		}

		if (!player->IsHuman())
		{
			return false;
		}

		if (player->inventory2.IsOpen())
		{
			return false;
		}

		if (ogame->GetWorld()->csPlayer->GetPlayingGlobalCutscene())
		{
			return false;
		}

		if (player->fmode != 0)
		{
			return false;
		}

		if (player->sleepingMode != zVOB_AWAKE)
		{
			return false;
		}

		if (player->interactMob || player->interactItem)
		{
			return false;
		}

		if (player->GetBodyState() >= BS_SWIM)
		{
			return false;
		}

		if (player->anictrl && player->anictrl->IsInWeaponChoose())
		{
			return false;
		}

		if (!oCInformationManager::GetInformationManager().HasFinished())
		{
			return false;
		}

		if (!player->GetEM()->IsEmpty(false))
		{
			return false;
		}

		if (zcon->IsVisible())
		{
			return false;
		}

		return true;
	}

	void PickPocketLoop()
	{
		if (!CanBeActive())
		{
			return;
		}

		auto focus = player->GetFocusNpc();
		if (!focus)
		{
			return;
		}

		if (zinput->GetMouseButtonToggledRight())
		{
			TryPickPocket(focus);
		}
	}
}