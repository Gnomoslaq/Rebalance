namespace GOTHIC_NAMESPACE
{
	bool ShowPrayMessage;

	void PrayMessage()
	{
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
				auto msg = zSTRING{ "Karma Beliara +" } + zSTRING{ BeliarP->single_intdata - oldBeliar->single_intdata};
				ogame->GetTextView()->Printwin(msg);
				oldBeliar->single_intdata = BeliarP->single_intdata;
				return;
			}
		}

	}
















}