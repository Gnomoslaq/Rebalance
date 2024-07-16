namespace GOTHIC_NAMESPACE
{
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

	//bool bShowPickPocket, PickPocketAmbientNPCs, bPickPocketSneakRequired, GiveAmbientXP;

	static bool forcetrue = false;

	class NewPickPocket
	{
	public:
		~NewPickPocket() {};

		std::vector<oCInfo*> pickpocketInfos;

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

			if (bPickPocketSneakRequired)
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

		void Loop()
		{
			if (!CanBeActive())
			{
				return;
			}

			if (!bNewPickPocket)
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

	};
	std::unique_ptr<NewPickPocket> newPickPocket;

}
