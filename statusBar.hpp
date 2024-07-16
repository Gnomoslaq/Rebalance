namespace GOTHIC_NAMESPACE
{
	class StatusBar
	{
	public:
		~StatusBar() {};

		zCView* valueViewStamina;

		void ClearValue()
		{
			delete valueViewStamina; valueViewStamina = 0;
		}

		void Loop()
		{
			if (CanShowValues())
			{
				auto atr_stamina = parser->GetSymbol("ATR_STAMINA");
				auto atr_stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");



				if (!atr_stamina && !atr_stamina_max)
				{
					return;
				}

				if (bStaminaValues == 0)
				{
					ClearValue();
				}

				if (bStaminaValues == 1)
				{
					ClearValue();

					staminaBar->GetPos(xs, ys);
					ys = ys - 50 - screen->FontY();
					auto msgs = zSTRING{ atr_stamina->single_intdata } + zSTRING{ "/" } + zSTRING{ atr_stamina_max->single_intdata * 10 };
					auto msglen = screen->FontSize(msgs);
					xs = 4096 - msglen / 2;
					// printing
					screen->Print(xs, ys, msgs);
				}

				if (bStaminaValues == 2)
				{
					ClearValue();
					
					staminaBar->GetPos(xs, ys);
					ys = ys - 50 - screen->FontY();
					auto msgs = zSTRING{ "Wytrzyma³oœæ: " } + zSTRING{ atr_stamina->single_intdata } + zSTRING{ "/" } + zSTRING{ atr_stamina_max->single_intdata * 10 };
					auto msglen = screen->FontSize(msgs);
					xs = 4096 - msglen / 2;
					// printing
					screen->Print(xs, ys, msgs);		
				}

				if (bStaminaValues == 3)
				{
					ClearValue();

					auto strS = zSTRING{ atr_stamina->single_intdata } + zSTRING{ "/" } + zSTRING{ atr_stamina_max->single_intdata * 10 };

					valueViewStamina = new zCView(0, 0, 8192, 8192);

					zCView* ownerviewS = staminaBar->range_bar;

					ownerviewS->InsertItem(valueViewStamina);

					valueViewStamina->PrintCXY(strS);

				}
			}
		}



	private:
		
		int xs, ys, sx, sy;

		bool CanShowValues()
		{
			if (ogame->GetShowPlayerStatus() && staminaBar && !playerHelper.IsBusy())
			{
				return true;
			}
			return false;
		}

	};
	std::unique_ptr<StatusBar> statusBar;
}
