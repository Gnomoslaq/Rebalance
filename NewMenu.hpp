namespace GOTHIC_NAMESPACE
{
	const int SCREEN_MAX = 8192;
	const int  pageMax = 3;
	const int  pageMin = 1;


	unsigned char GetCharFromDIK(int, int, int) zCall(0x004D2130);
	void HandleResultString(zSTRING) zCall(0x00432EC0);
	static zSTRING resultStr;

	class NewStatusMenu
	{
	public:
		~NewStatusMenu() {}

		void UpdateStatusMenu()
		{

			// page 1
			pStatusTexture->SetFont("FONT_OLD_10_WHITE.TGA");
			pStatusTexture->SetFontColor(zCOLOR(255, 255, 255, 255));
			pStatusTexture->InsertBack(Status_Texture);


			pStatusTexture->SetSize(screen->anx(MenuSizeX), screen->any(MenuSizeY));
			pStatusTexture->SetPos((SCREEN_MAX - screen->anx(MenuSizeX)) / 2, (SCREEN_MAX - screen->any(MenuSizeY)) / 2);

			// page 2
			pStatusTexture2->SetFont("FONT_OLD_10_WHITE.TGA");
			pStatusTexture2->SetFontColor(zCOLOR(255, 255, 255, 255));
			pStatusTexture2->InsertBack(Status_Texture);

			pStatusTexture2->SetSize(screen->anx(MenuSizeX), screen->any(MenuSizeY));
			pStatusTexture2->SetPos((SCREEN_MAX - screen->anx(MenuSizeX)) / 2, (SCREEN_MAX - screen->any(MenuSizeY)) / 2);

			// page 3
			pStatusTexture3->SetFont("FONT_OLD_10_WHITE.TGA");
			pStatusTexture3->SetFontColor(zCOLOR(255, 255, 255, 255));
			pStatusTexture3->InsertBack(Status_Texture);

			pStatusTexture3->SetSize(screen->anx(MenuSizeX), screen->any(MenuSizeY));
			pStatusTexture3->SetPos((SCREEN_MAX - screen->anx(MenuSizeX)) / 2, (SCREEN_MAX - screen->any(MenuSizeY)) / 2);
		}

		void MenuInit()
		{
			MenuActive = true;
			ogame->Pause();
			ogame->SetShowPlayerStatus(false);
			//player->ToggleFocusVob(false);
			resultStr.Clear();

			ShowMenu();
		}

		void MenuClose()
		{
			MenuActive = false;
			ogame->Unpause();
			ogame->SetShowPlayerStatus(true);
			//player->ToggleFocusVob(true);
			HandleResultString(resultStr);

			RemoveItems();
		}

		void ShowMenu()
		{

			if (page == 1)
			{
				//screen->RemoveItem(this->pStatusTexture2);
				screen->InsertItem(pStatusTexture);
				MenuItems1();
				//this->pStatusTexture->Blit();
				//screen->RemoveItem(this->pStatusTexture);

			}

			if (page == 2)
			{
				screen->RemoveItem(pStatusTexture);
				screen->RemoveItem(pStatusTexture3);
				screen->InsertItem(pStatusTexture2);
				MenuItems2();
				//this->pStatusTexture2->Blit();
				//screen->RemoveItem(this->pStatusTexture2);
			}

			if (page == 3)
			{
				screen->RemoveItem(pStatusTexture);
				screen->RemoveItem(pStatusTexture2);
				screen->InsertItem(pStatusTexture3);
				MenuItems3();
				//this->pStatusTexture3->Blit();
				//screen->RemoveItem(this->pStatusTexture3);
			}

		}

		void RemoveItems()
		{
			screen->RemoveItem(pStatusTexture);
			screen->RemoveItem(pStatusTexture2);
			screen->RemoveItem(pStatusTexture3);
			page = 1;
		}
	private:

		void MenuItems1()
		{
			auto prevColor = screen->GetColor();



			auto player_guild = player->GetGuildName();

			auto player_level = player->level;
			auto player_circle = player->GetTalentSkill(7);
			auto player_exp = player->experience_points;
			auto player_exp_next = player->experience_points_next_level;
			auto player_lp = player->learn_points;

			auto atr_str = player->GetAttribute(NPC_ATR_STRENGTH);
			auto atr_dex = player->GetAttribute(NPC_ATR_DEXTERITY);
			auto atr_mana = player->GetAttribute(NPC_ATR_MANA);
			auto atr_mana_max = player->GetAttribute(NPC_ATR_MANAMAX);
			auto atr_hp = player->GetAttribute(NPC_ATR_HITPOINTS);
			auto atr_hp_max = player->GetAttribute(NPC_ATR_HITPOINTSMAX);
			auto atr_stamina = parser->GetSymbol("ATR_STAMINA_MAX");
			auto atr_intellect = parser->GetSymbol("ATR_INTELLECT");

			auto msghp = zSTRING{ atr_hp } + zSTRING{ "/" } + zSTRING{ atr_hp_max };
			auto msgmana = zSTRING{ atr_mana } + zSTRING{ "/" } + zSTRING{ atr_mana_max };

			auto armweapon = player->GetProtectionByType(oEDamageType_Edge);
			auto armpoint = player->GetProtectionByType(oEDamageType_Point);
			auto armfire = player->GetProtectionByType(oEDamageType_Fire);
			auto armmagic = player->GetProtectionByType(oEDamageType_Magic);

			auto onehand = player->GetHitChance(1);
			auto onehandmsg = zSTRING{ onehand } + zSTRING{ "%" };
			auto onehandenum = player->GetTalentSkill(1);

			auto twohand = player->GetHitChance(2);
			auto twohandmsg = zSTRING{ twohand } + zSTRING{ "%" };
			auto twohandenum = player->GetTalentSkill(2);

			auto bow = player->GetHitChance(3);
			auto bowmsg = zSTRING{ bow } + zSTRING{ "%" };
			auto bowenum = player->GetTalentSkill(3);

			auto crossbow = player->GetHitChance(4);
			auto crossbowmsg = zSTRING{ crossbow } + zSTRING{ "%" };
			auto crossbowenum = player->GetTalentSkill(4);

			auto sharp1h = parser->GetSymbol("skillsharpsword");
			auto sharp2h = parser->GetSymbol("skillsharp2hsword");
			auto sharpaxe = parser->GetSymbol("skillsharpaxe");
			auto sharpblade = parser->GetSymbol("skillsharpblade");



			int sharpvalue = sharp1h->single_intdata + sharp2h->single_intdata + sharpaxe->single_intdata + sharpblade->single_intdata;
			auto sharpmsg = zSTRING{ sharpvalue } + zSTRING{ "%" };
			auto sneakenum = player->GetTalentSkill(8);
			auto pickpocketenum = player->GetTalentSkill(12);
			auto atr_pickpocket = parser->GetSymbol("ATR_PICKPOCKET");
			auto lockpickenum = player->GetTalentSkill(5);
			auto acrobaticenum = player->GetTalentSkill(11);
			auto runemakingenum = player->GetTalentSkill(14);
			auto alchemyenum = player->GetTalentSkill(15);
			auto smithenum = player->GetTalentSkill(13);
			auto demonologyenum = player->GetTalentSkill(10);
			auto huntingenum = player->GetTalentSkill(16);
			auto languageenum = player->GetTalentSkill(17);
			auto arrowenum = player->GetTalentSkill(19);
			auto goldvalue = parser->GetSymbol("Hero_HackChance");
			auto goldenum = player->GetTalentSkill(20);
			auto orevalue = parser->GetSymbol("hero_hackchanceore");
			auto oreenum = player->GetTalentSkill(21);
			auto rhetorikenum = player->GetTalentSkill(18);

			//this->PrintPage();
			pStatusTexture->SetFontColor(GFX_GREEN);

			//pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y - 1000, pagemsg);
			screen->PrintCX(7000, pagemsg);

			pStatusTexture->SetFontColor(GFX_WHITE);
			// Player
			pStatusTexture->Print((STAT_A_X4 - STAT_A_X1) / 2, STAT_PLYHEAD_Y, MENU_ITEM_STATUS_HEADING);
			// Guild + Lvl
			pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 0), player_guild);
			pStatusTexture->Print(STAT_A_X2, STAT_PLY_Y + (STAT_DY * 0), MENU_ITEM_LEVEL_TITLE);
			pStatusTexture->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 0), player_level);
			// Magic Circle
			pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 1), MENU_ITEM_TALENT_7_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_PLY_Y + (STAT_DY * 1), MENU_ITEM_TALENT_7_CIRCLE);
			pStatusTexture->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 1), player_circle);
			// XP
			pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 2), MENU_ITEM_EXP_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_PLY_Y + (STAT_DY * 2), player_exp);
			pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 3), MENU_ITEM_LEVEL_NEXT_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_PLY_Y + (STAT_DY * 3), player_exp_next);
			// LP
			pStatusTexture->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 4), MENU_ITEM_LEARN_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_PLY_Y + (STAT_DY * 4), player_lp);
			// Attribute
			pStatusTexture->Print((STAT_A_X4 - STAT_A_X1) / 2, STAT_ATRHEAD_Y, MENU_ITEM_ATTRIBUTE_HEADING);
			// Strength
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 0), MENU_ITEM_ATTRIBUTE_1_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 0), atr_str);
			// Dexterity
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 1), MENU_ITEM_ATTRIBUTE_2_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 1), atr_dex);
			// Mana
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 2), MENU_ITEM_ATTRIBUTE_3_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 2), msgmana);
			// Hp
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 3), MENU_ITEM_ATTRIBUTE_4_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 3), msghp);
			// Stamina
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 4), MENU_ITEM_ATTRIBUTE_5_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 4), atr_stamina->single_intdata);
			// Intellect
			pStatusTexture->Print(STAT_A_X1, STAT_ATR_Y + (STAT_DY * 5), MENU_ITEM_ATTRIBUTE_6_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ATR_Y + (STAT_DY * 5), atr_intellect->single_intdata);
			// Protection
			pStatusTexture->Print((STAT_A_X4 - STAT_A_X1) / 2, STAT_ARMHEAD_Y, MENU_ITEM_ARMOR_HEADING);
			// Edge
			pStatusTexture->Print(STAT_A_X1, STAT_ARM_Y + (STAT_DY * 0), MENU_ITEM_ARMOR_1_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ARM_Y + (STAT_DY * 0), armweapon);
			// Point
			pStatusTexture->Print(STAT_A_X1, STAT_ARM_Y + (STAT_DY * 1), MENU_ITEM_ARMOR_2_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ARM_Y + (STAT_DY * 1), armpoint);
			// Fire
			pStatusTexture->Print(STAT_A_X1, STAT_ARM_Y + (STAT_DY * 2), MENU_ITEM_ARMOR_3_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ARM_Y + (STAT_DY * 2), armfire);
			// Magic
			pStatusTexture->Print(STAT_A_X1, STAT_ARM_Y + (STAT_DY * 3), MENU_ITEM_ARMOR_4_TITLE);
			pStatusTexture->Print(STAT_A_X2, STAT_ARM_Y + (STAT_DY * 3), armmagic);
			// Talents
			pStatusTexture->Print((STAT_B_X3 - STAT_B_X1 / 2), STAT_TALHEAD_Y, MENU_ITEM_TALENTS_HEADING);
			// 1h
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 0), MENU_ITEM_TALENT_1_TITLE);
			pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 0), onehandmsg);

			if (onehandenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 0), MENU_HITCHANCE_TITLE1);
			}
			if (onehandenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 0), MENU_HITCHANCE_TITLE2);
			}
			if (onehandenum == 2)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 0), MENU_HITCHANCE_TITLE3);
			}

			// 2h
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 1), MENU_ITEM_TALENT_2_TITLE);
			pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 1), twohandmsg);

			if (twohandenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 1), MENU_HITCHANCE_TITLE1);
			}
			if (twohandenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 1), MENU_HITCHANCE_TITLE2);
			}
			if (twohandenum == 2)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 1), MENU_HITCHANCE_TITLE3);
			}

			// Bow
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 2), MENU_ITEM_TALENT_3_TITLE);
			pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 2), bowmsg);
			if (bowenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 2), MENU_HITCHANCE_TITLE1);
			}
			if (bowenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 2), MENU_HITCHANCE_TITLE2);
			}
			if (bowenum == 2)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 2), MENU_HITCHANCE_TITLE3);
			}

			// Crossbow
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 3), MENU_ITEM_TALENT_4_TITLE);
			pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 3), crossbowmsg);
			if (crossbowenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 3), MENU_HITCHANCE_TITLE1);
			}
			if (crossbowenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 3), MENU_HITCHANCE_TITLE2);
			}
			if (crossbowenum == 2)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 3), MENU_HITCHANCE_TITLE3);
			}

			//Sharpening
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 5), MENU_ITEM_TALENT_19_TITLE);
			if (sharpvalue == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 5), MENU_ITEM_TALENT_NO);
			}
			if (sharpvalue != 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 5), MENU_ITEM_TALENT_YES);
				pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 5), sharpmsg);
			}
			
		

			//Sneak
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 6), MENU_ITEM_TALENT_5_TITLE);
			if (sneakenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 6), MENU_ITEM_TALENT_NO);
			}
			if (sneakenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 6), MENU_ITEM_TALENT_YES);
			}
			// Pickpocket
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 7), MENU_ITEM_TALENT_6_TITLE);
			if (pickpocketenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 7), MENU_ITEM_TALENT_NO);
			}
			if (pickpocketenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 7), MENU_ITEM_TALENT_YES);
			}
			if (pickpocketenum == 1)
			{
				pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 7), atr_pickpocket->single_intdata);
			}

			// Lockpicking
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 8), MENU_ITEM_TALENT_7p_TITLE);
			if (lockpickenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 8), MENU_ITEM_TALENT_NO);
			}
			if (lockpickenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 8), MENU_ITEM_TALENT_YES);
			}

			// Acrobatic
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 9), MENU_ITEM_TALENT_8_TITLE);
			if (acrobaticenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 9), MENU_ITEM_TALENT_NO);
			}
			if (acrobaticenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 9), MENU_ITEM_TALENT_YES);
			}

			// Rune making
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 10), MENU_ITEM_TALENT_9_TITLE);
			if (runemakingenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 10), MENU_ITEM_TALENT_NO);
			}
			if (runemakingenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 10), MENU_ITEM_TALENT_YES);
			}

			// Alchemy
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 11), MENU_ITEM_TALENT_10_TITLE);
			if (alchemyenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 11), MENU_ITEM_TALENT_NO);
			}
			if (alchemyenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 11), MENU_ITEM_TALENT_YES);
			}

			// Smithing
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 12), MENU_ITEM_TALENT_11_TITLE);
			if (smithenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 12), MENU_ITEM_TALENT_NO);
			}
			if (smithenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 12), MENU_ITEM_TALENT_YES);
			}

			// Demonology
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 13), MENU_ITEM_TALENT_12_TITLE);
			if (demonologyenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 13), MENU_ITEM_TALENT_NO);
			}
			if (demonologyenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 13), MENU_ITEM_TALENT_YES);
			}

			// Hunting
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 14), MENU_ITEM_TALENT_13_TITLE);
			if (huntingenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 14), MENU_ITEM_TALENT_NO);
			}
			if (huntingenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 14), MENU_ITEM_TALENT_YES);
			}

			// Language
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 15), MENU_ITEM_TALENT_14_TITLE);
			if (languageenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 15), MENU_ITEM_TALENT_NO);
			}
			if (languageenum >= 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 15), MENU_ITEM_TALENT_YES);
			}

			// Arrow making
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 16), MENU_ITEM_TALENT_15_TITLE);
			if (arrowenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 16), MENU_ITEM_TALENT_NO);
			}
			if (arrowenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 16), MENU_ITEM_TALENT_YES);
			}

			// Gold mining
			auto goldmsg = zSTRING{ goldvalue->single_intdata } + zSTRING{ "%" };
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 17), MENU_ITEM_TALENT_16_TITLE);
			if (goldenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 17), MENU_ITEM_TALENT_NO);
			}
			if (goldenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 17), MENU_ITEM_TALENT_YES);
				pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 17), goldmsg);
			}

			// Ore mining
			auto oremsg = zSTRING{ orevalue->single_intdata } + zSTRING{ "%" };
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 18), MENU_ITEM_TALENT_17_TITLE);
			if (oreenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 18), MENU_ITEM_TALENT_NO);
			}
			if (oreenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 18), MENU_ITEM_TALENT_YES);
				pStatusTexture->Print(STAT_B_X3, STAT_TAL_Y + (STAT_DY * 18), oremsg);
			}

			// Rhetorik
			pStatusTexture->Print(STAT_B_X1, STAT_TAL_Y + (STAT_DY * 19), MENU_ITEM_TALENT_18_TITLE);
			if (rhetorikenum == 0)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 19), MENU_ITEM_TALENT_NO);
			}
			if (rhetorikenum == 1)
			{
				pStatusTexture->Print(STAT_B_X2, STAT_TAL_Y + (STAT_DY * 19), MENU_ITEM_TALENT_YES);
			}


			screen->SetFontColor(prevColor);

		}

		void MenuItems2()
		{

			auto* speciesKilled = parser->GetSymbol("specieskilled");

			int i = 0;


			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 0), speciesKilled1);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 0), zSTRING{ speciesKilled->intdata[1] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 1), speciesKilled2);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 1), zSTRING{ speciesKilled->intdata[2] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 2), speciesKilled49);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 2), zSTRING{ speciesKilled->intdata[49] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 3), speciesKilled83);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 3), zSTRING{ speciesKilled->intdata[83] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 4), speciesKilled7);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 4), zSTRING{ speciesKilled->intdata[7] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 5), speciesKilled8);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 5), zSTRING{ speciesKilled->intdata[8] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 6), speciesKilled9);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 6), zSTRING{ speciesKilled->intdata[9] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 7), speciesKilled18);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 7), zSTRING{ speciesKilled->intdata[18] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 8), speciesKilled11);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 8), zSTRING{ speciesKilled->intdata[11] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 9), speciesKilled12);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 9), zSTRING{ speciesKilled->intdata[12] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 10), speciesKilled13);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 10), zSTRING{ speciesKilled->intdata[13] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 11), speciesKilled14);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 11), zSTRING{ speciesKilled->intdata[14] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 12), speciesKilled3);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 12), zSTRING{ speciesKilled->intdata[3] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 13), speciesKilled4);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 13), zSTRING{ speciesKilled->intdata[4] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 14), speciesKilled65);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 14), zSTRING{ speciesKilled->intdata[65] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 15), speciesKilled5);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 15), zSTRING{ speciesKilled->intdata[5] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 16), speciesKilled43);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 16), zSTRING{ speciesKilled->intdata[43] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 17), speciesKilled16);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 17), zSTRING{ speciesKilled->intdata[16] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 18), speciesKilled17);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 18), zSTRING{ speciesKilled->intdata[17] });

			pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 19), speciesKilled23);
			pStatusTexture2->Print(STAT_A_X2b, STAT_PLY_Y + (STAT_DY * 19), zSTRING{ speciesKilled->intdata[23] });

			// Second Line
			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 0), speciesKilled24);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 0), zSTRING{ speciesKilled->intdata[24] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 1), speciesKilled25);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 1), zSTRING{ speciesKilled->intdata[25] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 2), speciesKilled26);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 2), zSTRING{ speciesKilled->intdata[26] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 3), speciesKilled54);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 3), zSTRING{ speciesKilled->intdata[54] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 4), speciesKilled56);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 4), zSTRING{ speciesKilled->intdata[56] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 5), speciesKilled57);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 5), zSTRING{ speciesKilled->intdata[57] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 6), speciesKilled63);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 6), zSTRING{ speciesKilled->intdata[63] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 7), speciesKilled27);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 7), zSTRING{ speciesKilled->intdata[27] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 8), speciesKilled37);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 8), zSTRING{ speciesKilled->intdata[37] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 9), speciesKilled50);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 9), zSTRING{ speciesKilled->intdata[50] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 10), speciesKilled60);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 10), zSTRING{ speciesKilled->intdata[60] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 11), speciesKilled59);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 11), zSTRING{ speciesKilled->intdata[59] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 12), speciesKilled10);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 12), zSTRING{ speciesKilled->intdata[10] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 13), speciesKilled64);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 13), zSTRING{ speciesKilled->intdata[64] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 14), speciesKilled55);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 14), zSTRING{ speciesKilled->intdata[55] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 15), speciesKilled35);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 15), zSTRING{ speciesKilled->intdata[35] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 16), speciesKilled36);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 16), zSTRING{ speciesKilled->intdata[36] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 17), speciesKilled52);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 17), zSTRING{ speciesKilled->intdata[36] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 18), speciesKilled66);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 18), zSTRING{ speciesKilled->intdata[66] });

			pStatusTexture2->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 19), speciesKilled32);
			pStatusTexture2->Print(STAT_A_X3b, STAT_PLY_Y + (STAT_DY * 19), zSTRING{ speciesKilled->intdata[32] });

			// Third line

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 0), speciesKilled34);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 0), zSTRING{ speciesKilled->intdata[34] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 1), speciesKilled28);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 1), zSTRING{ speciesKilled->intdata[28] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 2), speciesKilled29);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 2), zSTRING{ speciesKilled->intdata[29] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 3), speciesKilled30);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 3), zSTRING{ speciesKilled->intdata[30] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 4), speciesKilled51);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 4), zSTRING{ speciesKilled->intdata[51] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 5), speciesKilled19);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 5), zSTRING{ speciesKilled->intdata[19] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 6), speciesKilled21);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 6), zSTRING{ speciesKilled->intdata[21] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 7), speciesKilled22);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 7), zSTRING{ speciesKilled->intdata[22] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 8), speciesKilled75);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 8), zSTRING{ speciesKilled->intdata[75] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 9), speciesKilled44);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 9), zSTRING{ speciesKilled->intdata[44] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 10), speciesKilled45);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 10), zSTRING{ speciesKilled->intdata[45] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 11), speciesKilled46);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 11), zSTRING{ speciesKilled->intdata[46] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 12), speciesKilled47);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 12), zSTRING{ speciesKilled->intdata[47] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 13), speciesKilled71);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 13), zSTRING{ speciesKilled->intdata[71] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 14), speciesKilled76);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 14), zSTRING{ speciesKilled->intdata[76] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 15), speciesKilled74);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 15), zSTRING{ speciesKilled->intdata[74] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 16), speciesKilled48);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 16), zSTRING{ speciesKilled->intdata[48] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 17), speciesKilled78);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 17), zSTRING{ speciesKilled->intdata[78] });

			pStatusTexture2->Print(STAT_A_X4a, STAT_PLY_Y + (STAT_DY * 18), speciesKilled82);
			pStatusTexture2->Print(STAT_A_X4b, STAT_PLY_Y + (STAT_DY * 18), zSTRING{ speciesKilled->intdata[82] });

			screen->PrintCX(7000, pagemsg);

			//pStatusTexture2->Print(STAT_A_X1, STAT_PLY_Y - 1000, pagemsg);
			pStatusTexture2->SetFontColor(GFX_WHITE);

			pStatusTexture2->PrintCX(500, "Statystyki zabitych stworzeñ");

			auto monsterKilled = parser->GetSymbol("MonsterKilled");

			auto killedmsg = zSTRING{ "Zabito wszystkich stworzeñ: " } + zSTRING{ monsterKilled->single_intdata };
			pStatusTexture2->Print(STAT_A_X1, 800, killedmsg);




		}

		void MenuItems3()
		{

			auto UsePermSTR = parser->GetSymbol("UsePermSTR");
			auto UsePermSTROrc = parser->GetSymbol("UsePermSTROrc");
			auto UsePermDEX = parser->GetSymbol("UsePermDEX");
			auto UsePermDEXDra = parser->GetSymbol("UsePermDEXDra");
			auto UsePermMana = parser->GetSymbol("UsePermMana");
			auto UsePermHealth = parser->GetSymbol("UsePermHealth");
			auto UsePermStamina = parser->GetSymbol("UsePermStamina");
			auto UsePermStaminaTroll = parser->GetSymbol("UsePermStaminaTroll");
			auto UsePermInt = parser->GetSymbol("UsePermInt");
			auto UsePermDef = parser->GetSymbol("UsePermDef");
			auto UsePermMagDef = parser->GetSymbol("UsePermMagDef");
			auto UsePermDefFire = parser->GetSymbol("UsePermDefFire");
			auto UsePermDefFall = parser->GetSymbol("UsePermDefFall");
			auto UseOrcPotion = parser->GetSymbol("UseOrcPotion");
			auto UseMegaDrink = parser->GetSymbol("UseMegaDrink");
			auto UseMegaPotionSkill = parser->GetSymbol("UseMegaPotionSkill");

			auto MakePermSTR = parser->GetSymbol("MakePermSTR");
			auto MakePermDEX = parser->GetSymbol("MakePermDEX");
			auto MakePermMana = parser->GetSymbol("MakePermMana");
			auto MakePermHealth = parser->GetSymbol("MakePermHealth");
			auto MakePermStamina = parser->GetSymbol("MakePermStamina");
			auto MakePermInt = parser->GetSymbol("MakePermInt");
			auto MakePermDef = parser->GetSymbol("MakePermDef");
			auto MakeMagDef = parser->GetSymbol("MakeMagDef");
			auto MakeDefFire = parser->GetSymbol("MakeDefFire");
			auto MakeDefFall = parser->GetSymbol("MakeDefFall");


			auto msgTitle = zSTRING{ "U¿yte | Stworzone mikstury" };
			auto msgTitleLen = pStatusTexture3->FontSize(msgTitle);
			pStatusTexture3->Print(STAT_A_X1, STAT_PLYHEAD_Y, msgTitle);
			//pStatusTexture3->Print(854, STAT_PLYHEAD_Y, msgTitle);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 0), PermSTR);
			auto msgStr = zSTRING{ UsePermSTR->single_intdata + UsePermSTROrc->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermSTR->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 0), msgStr);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 1), PermDEX);
			auto msgDex = zSTRING{ UsePermDEX->single_intdata + UsePermDEXDra->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermDEX->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 1), msgDex);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 2), PermMana);
			auto msgMana = zSTRING{ UsePermMana->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermMana->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 2), msgMana);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 3), PermHealth);
			auto msgHealth = zSTRING{ UsePermHealth->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermHealth->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 3), msgHealth);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 4), PermStamina);
			auto msgStamina = zSTRING{ UsePermStamina->single_intdata + UsePermStaminaTroll->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermStamina->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 4), msgStamina);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 5), PermInt);
			auto msgInt = zSTRING{ UsePermInt->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermInt->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 5), msgInt);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 6), PermDef);
			auto msgDef = zSTRING{ UsePermDef->single_intdata } + zSTRING{ "|" } + zSTRING{ MakePermDef->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 6), msgDef);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 7), PermDeffire);
			auto msgFireDef = zSTRING{ UsePermDefFire->single_intdata } + zSTRING{ "|" } + zSTRING{ MakeDefFire->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 7), msgFireDef);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 8), PermFallDef);
			auto msgDefFall = zSTRING{ UsePermDefFall->single_intdata } + zSTRING{ "|" } + zSTRING{ MakeDefFall->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 8), msgDefFall);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 9), PermMagDef);
			auto msgMagDef = zSTRING{ UsePermMagDef->single_intdata } + zSTRING{ "|" } + zSTRING{ MakeMagDef->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 9), msgMagDef);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 10), PermOrc);
			auto msgPermOrc = zSTRING{ UseOrcPotion->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 10), UseOrcPotion->single_intdata);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 11), PermMegaDrink);
			auto msgMegaDrink = zSTRING{ UseMegaDrink->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 11), UseMegaDrink->single_intdata);

			pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y + (STAT_DY * 12), PermMegaPotionSkill);
			auto msgPotionSkill = zSTRING{ UseMegaPotionSkill->single_intdata };
			pStatusTexture3->Print(STAT_A_X3, STAT_PLY_Y + (STAT_DY * 12), UseMegaPotionSkill->single_intdata);








			screen->PrintCX(7000, pagemsg);

			//pStatusTexture3->Print(STAT_A_X1, STAT_PLY_Y - 1000, pagemsg);
			pStatusTexture3->SetFontColor(GFX_WHITE);


		}

	public:

		bool CanShowMenu()
		{
			zBOOL moveAllowed = zCAICamera::GetCurrent() ? zCAICamera::GetCurrent()->playerIsMovable : TRUE;

			if (zCConsole::cur_console
				//|| !oCInformationManager::GetInformationManager().HasFinished()
				|| player->GetBodyState() == BS_FALL
				|| player->guild > 19
				|| player->interactMob
				|| player->IsInGlobalCutscene()
				|| !moveAllowed
				|| player->GetEM()->GetCutsceneMode()
				|| player->IsUnconscious()
				|| player->IsDead()
				)
			{
				return false;
			}

			return true;
		}





		bool MenuActive;

		int page = 1;

		// Menu Items
//		group 1 {
zSTRING MENU_ITEM_STATUS_HEADING = "POSTAÆ";
zSTRING MENU_ITEM_LEVEL_TITLE = "Poz.";
zSTRING MENU_ITEM_TALENT_7_TITLE = "Magia";
zSTRING MENU_ITEM_TALENT_7_CIRCLE = "Kr¹g";
zSTRING MENU_ITEM_EXP_TITLE = "Doœwiadczenie";
zSTRING MENU_ITEM_LEVEL_NEXT_TITLE = "Nast. Poziom";
zSTRING MENU_ITEM_LEARN_TITLE = "Punkty Nauki";

zSTRING MENU_ITEM_ATTRIBUTE_HEADING = "ATRYBUTY";

zSTRING  MENU_ITEM_ATTRIBUTE_1_TITLE = "Si³a";
zSTRING  MENU_ITEM_ATTRIBUTE_2_TITLE = "Zrêcznoœæ";
zSTRING  MENU_ITEM_ATTRIBUTE_3_TITLE = "Mana";
zSTRING  MENU_ITEM_ATTRIBUTE_4_TITLE = "Punkty trafieñ";
zSTRING  MENU_ITEM_ATTRIBUTE_5_TITLE = "Wytrzyma³oœæ";
zSTRING  MENU_ITEM_ATTRIBUTE_6_TITLE = "Inteligencja";

zSTRING MENU_ITEM_ARMOR_HEADING = "OCHRONA";

zSTRING MENU_ITEM_ARMOR_1_TITLE = "Broñ";
zSTRING MENU_ITEM_ARMOR_2_TITLE = "Pociski";
zSTRING MENU_ITEM_ARMOR_3_TITLE = "Ogieñ";
zSTRING MENU_ITEM_ARMOR_4_TITLE = "Magia";

zSTRING MENU_ITEM_TALENTS_HEADING = "UMIEJÊTNOŒCI";

zSTRING MENU_HITCHANCE_TITLE1 = "Zielony";
zSTRING MENU_HITCHANCE_TITLE2 = "Wojownik";
zSTRING MENU_HITCHANCE_TITLE3 = "Mistrz";
zSTRING  MENU_ITEM_TALENT_1_TITLE = "Br. jednorêczna";
zSTRING  MENU_ITEM_TALENT_2_TITLE = "Br. dwurêczna";
zSTRING  MENU_ITEM_TALENT_3_TITLE = "£uki";
zSTRING  MENU_ITEM_TALENT_4_TITLE = "Kusze";

zSTRING MENU_ITEM_TALENT_NO = "-";
zSTRING MENU_ITEM_TALENT_YES = "Uczony";

zSTRING MENU_ITEM_TALENT_5_TITLE = "Skradanie siê";
zSTRING MENU_ITEM_TALENT_6_TITLE = "Kradzie¿ kieszonkowa";
zSTRING MENU_ITEM_TALENT_7p_TITLE = "Otwieranie zamków";
zSTRING MENU_ITEM_TALENT_8_TITLE = "Akrobatyka";
zSTRING MENU_ITEM_TALENT_9_TITLE = "Tworzenie run";
zSTRING MENU_ITEM_TALENT_10_TITLE = "Alchemia";
zSTRING MENU_ITEM_TALENT_11_TITLE = "Kowalstwo";
zSTRING MENU_ITEM_TALENT_12_TITLE = "Demonologia";
zSTRING MENU_ITEM_TALENT_13_TITLE = "Zbieranie trofeów";
zSTRING MENU_ITEM_TALENT_14_TITLE = "Znajomoœæ jêzyków";
zSTRING MENU_ITEM_TALENT_15_TITLE = "Tworzenie strza³";
zSTRING MENU_ITEM_TALENT_16_TITLE = "Wydobywanie z³ota";
zSTRING MENU_ITEM_TALENT_17_TITLE = "Wydobywanie rudy";
zSTRING MENU_ITEM_TALENT_18_TITLE = "Retoryka";
zSTRING MENU_ITEM_TALENT_19_TITLE = "Ostrzenie";
//		};
		// Positions		
//		group{ 
		const int STAT_A_X1 = 500;
		const int STAT_A_X2 = 2300;
		const int STAT_A_X2b = 2600;
		const int STAT_A_X3 = 2900;
		const int STAT_A_X3b = 5100;
		const int STAT_A_X4 = 3400;
		const int STAT_A_X4a = 5500;
		const int STAT_A_X4b = 7600;
		const int STAT_B_X1 = 3800;
		const int STAT_B_X2 = 6000;
		const int STAT_B_X3 = 7200;
		const int STAT_B_X4 = 7700;
		const int STAT_PLYHEAD_Y = 1000;
		const int STAT_PLY_Y = 1450;
		const int STAT_ATRHEAD_Y = 3250;
		const int STAT_ATR_Y = 3700;
		const int STAT_ARMHEAD_Y = 5950;
		const int STAT_ARM_Y = 6400;
		const int STAT_TALHEAD_Y = 1000;
		const int STAT_TAL_Y = 1450;
		const int STAT_DY = 300; 
//};
		// Monsters
//		group{ 
			zSTRING speciesKilled = "";
			zSTRING speciesKilled1 = "Chrz¹szczy:";
			zSTRING speciesKilled2 = "Owiec:";
			zSTRING speciesKilled3 = "Goblinów:";
			zSTRING speciesKilled4 = "Czarnych goblinów:";
			zSTRING speciesKilled5 = "Szkieletów-goblinów:";
			zSTRING speciesKilled6 = "Przyzwanych szkieletów-goblinów:";
			zSTRING speciesKilled7 = "Œcierwojadów:";
			zSTRING speciesKilled8 = "Preriowych œcierwojadów:";
			zSTRING speciesKilled9 = "Polnych bestii:";
			zSTRING speciesKilled10 = "Krwiopijców:";
			zSTRING speciesKilled11 = "Jaszczurów:";
			zSTRING speciesKilled12 = "Ognistych jaszczurów:";
			zSTRING speciesKilled13 = "Wilków:";
			zSTRING speciesKilled14 = "Wargów:";
			zSTRING speciesKilled15 = "Przyzwanych wilków:";
			zSTRING speciesKilled16 = "Pe³zaczy:";
			zSTRING speciesKilled17 = "Pe³zaczy-wojowników:";
			zSTRING speciesKilled18 = "Topielców:";
			zSTRING speciesKilled19 = "Szkieletów:";
			zSTRING speciesKilled20 = "Przyzwanych szkieletów:";
			zSTRING speciesKilled21 = "Szkieletów-magów:";
			zSTRING speciesKilled22 = "Zombie:";
			zSTRING speciesKilled23 = "Zêbaczy:";
			zSTRING speciesKilled24 = "Smoczych zêbaczy:";
			zSTRING speciesKilled25 = "Cieniostworów:";
			zSTRING speciesKilled26 = "Szkieletów-cieniostworów:";
			zSTRING speciesKilled27 = "Harpii:";
			zSTRING speciesKilled28 = "Kamiennych golemów:";
			zSTRING speciesKilled29 = "Ognistych golemów:";
			zSTRING speciesKilled30 = "Lodowych golemów:";
			zSTRING speciesKilled31 = "Przyzwanych golemów:";
			zSTRING speciesKilled32 = "Demonów:";
			zSTRING speciesKilled33 = "Przyzwanych demonów:";
			zSTRING speciesKilled34 = "Arcydemonów:";
			zSTRING speciesKilled35 = "Trolli:";
			zSTRING speciesKilled36 = "Czarnych trolli:";
			zSTRING speciesKilled37 = "Wê¿y b³otnych:";
			zSTRING speciesKilled38 = "Ognistych smoków:";
			zSTRING speciesKilled39 = "Lodowych smoków:";
			zSTRING speciesKilled40 = "Kamiennych smoków:";
			zSTRING speciesKilled41 = "Bagiennych smoków:";
			zSTRING speciesKilled42 = "Nieumar³ych smoków:";
			zSTRING speciesKilled43 = "Kretoszczurów:";
			zSTRING speciesKilled44 = "Orków-wojowników:";
			zSTRING speciesKilled45 = "Orków-szamanów:";
			zSTRING speciesKilled46 = "Elitarnych orków:";
			zSTRING speciesKilled47 = "Nieumar³ych orków:";
			zSTRING speciesKilled48 = "Jaszczuroludzi:";
			zSTRING speciesKilled49 = "Ogników:";
			zSTRING speciesKilled50 = "Aligatorów:";
			zSTRING speciesKilled51 = "Bagiennych golemów:";
			zSTRING speciesKilled52 = "Kamiennych stra¿ników:";
			zSTRING speciesKilled53 = "Duchów ognia:";
			zSTRING speciesKilled54 = "Ogarów:";
			zSTRING speciesKilled55 = "Lodowych wilków:";
			zSTRING speciesKilled56 = "K¹saczy:";
			zSTRING speciesKilled57 = "Brzytwiaków:";
			zSTRING speciesKilled58 = "Topielców:";
			zSTRING speciesKilled59 = "Bagiennych szczurów:";
			zSTRING speciesKilled60 = "Polnych pe³zaczy:";
			zSTRING speciesKilled61 = "Przyzwanych kamiennych stra¿ników:";
			zSTRING speciesKilled62 = "Przyzwanych zombie:";
			zSTRING speciesKilled63 = "Dzików:";
			zSTRING speciesKilled64 = "Bagiennych trutni:";
			zSTRING speciesKilled65 = "Leœnych goblinów:";
			zSTRING speciesKilled66 = "Pum:";
			zSTRING speciesKilled67 = "Bagiennych trutni:";
			zSTRING speciesKilled70 = "Lucian:";
			zSTRING speciesKilled71 = "Orków-kuszników:";
			zSTRING speciesKilled72 = "Azgalor, czarny smok:";
			zSTRING speciesKilled73 = "Czerwony smok:";
			zSTRING speciesKilled74 = "Zombie-stra¿ników:";
			zSTRING speciesKilled75 = "Poszukiwaczy:";
			zSTRING speciesKilled76 = "Nieumar³ych szamanów:";
			zSTRING speciesKilled78 = "Duchów kopaczy:";
			zSTRING speciesKilled79 = "Demonikonów:";
			zSTRING speciesKilled80 = "Orków-wojowników:";
			zSTRING speciesKilled81 = "Dusz:";
			zSTRING speciesKilled82 = "Panów cienia:";
			zSTRING speciesKilled83 = "¯ó³wi morskich:"; 
//};
		// Potions
//		group{ 

				zSTRING PermSTR = "Eliksir si³y";
				zSTRING PermDEX = "Eliksir zrêcznoœci";
				zSTRING PermMana = "Eliksir ducha";
				zSTRING PermHealth = "Eliksir ¿ycia";
				zSTRING PermStamina = "Eliksir wytrzyma³oœci";
				zSTRING PermInt = "Eliksir umys³u";
				zSTRING PermDef = "Eliksir trolla";
				zSTRING PermDeffire = "Eliksir ochr. przed ogniem";
				zSTRING PermFallDef = "Eliksir ochr. przed upadkiem";
				zSTRING PermMagDef = "Eliksir ochr. przed magi¹";
				zSTRING PermOrc = "Orkowa mikstura";
				zSTRING PermMegaDrink = "Embarla Firgasto";
				zSTRING PermMegaPotionSkill = "Eliksir potêgi";

			


		zCView* pStatusTexture = new zCView(0, 0, SCREEN_MAX, SCREEN_MAX);
		zCView* pStatusTexture2 = new zCView(0, 0, SCREEN_MAX, SCREEN_MAX);
		zCView* pStatusTexture3 = new zCView(0, 0, SCREEN_MAX, SCREEN_MAX);


	private:

		int MenuSizeX = 1230;
		int MenuSizeY = 922;

		zSTRING pagemsg = zSTRING{ "Strona " } + zSTRING{ page } + zSTRING{ "/" } + zSTRING{ pageMax };

		const zSTRING Status_Texture = "status_back.tga";


	};
	std::unique_ptr<NewStatusMenu> newStatusMenu;





	auto Hook_oCGame_HandleEvent = ::Union::CreateHook(reinterpret_cast<void*>(zSwitch(0x0065EEE0, 0x0068A300, 0x0069E980, 0x006FC170)), &oCGame::HandleEvent_Union);
	int oCGame::HandleEvent_Union(int key)
	{
		if (this->GetWorld()->csPlayer->GetPlayingGlobalCutscene()) return FALSE;
		if (!oCNpc::player) return FALSE;

		auto logical = zinput->GetFirstBindedLogicalKey(key);

		if (newStatusMenu->CanShowMenu())
		{
			if (logical == GAME_SCREEN_STATUS && !newStatusMenu->MenuActive)
			{
				if (player->inventory2.IsOpen()) player->inventory2.Close();
				newStatusMenu->MenuInit();

				return TRUE;
			}

			if (logical == GAME_SCREEN_STATUS && newStatusMenu->MenuActive)
			{
				newStatusMenu->MenuClose();

				return TRUE;
			}
		}
				
		if (newStatusMenu->MenuActive)
		{
			if (zinput->KeyToggled(KEY_ESCAPE) || zinput->GetMouseButtonPressedRight())
			{
				newStatusMenu->MenuClose();

				return TRUE;
			}
			// Page Select
			if (zinput->KeyToggled(KEY_RIGHTARROW) && newStatusMenu->page != pageMax || zinput->KeyToggled(KEY_D) && newStatusMenu->page != pageMax)
			{
				newStatusMenu->page = newStatusMenu->page + 1;
				newStatusMenu->ShowMenu();

				//return TRUE;
			}
			if (zinput->KeyToggled(KEY_LEFTARROW) && newStatusMenu->page != pageMin || zinput->KeyToggled(KEY_A) && newStatusMenu->page != pageMin)
			{
				newStatusMenu->page = newStatusMenu->page - 1;
				newStatusMenu->ShowMenu();

				//return TRUE;
			}


			unsigned char ch = GetCharFromDIK(key, 0, 0);
			resultStr += (char)(ch);

			return TRUE;
		}

		//
		return (this->*Hook_oCGame_HandleEvent)(key);
	}

	// Old Status Menu        
	
	auto Hook_oCNpc_OpenScreen_Status_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x0073D980), &oCNpc::OpenScreen_Status_Union);
	void oCNpc::OpenScreen_Status_Union()
	{
		
	}
	
	// Log open hook
	/*auto Hook_oCNpc_OpenScreen_Log_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x0073D5C0), &oCNpc::OpenScreen_Log_Union);
	void oCNpc::OpenScreen_Log_Union()
	{
		(this->*Hook_oCNpc_OpenScreen_Log_Union)();
	}
	*/

}