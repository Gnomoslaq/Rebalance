namespace GOTHIC_NAMESPACE
{
	void wld_gettimehour()
	{
		int day, hour, min;
		ogame->GetTime(day, hour, min);

		screen->PrintCXY(zSTRING{ day } + zSTRING{ hour } + zSTRING{ min });
	}

	void wld_gettimemin()
	{
		int day, hour, min;
		ogame->GetTime(day, hour, min);
	}

}