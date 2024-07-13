namespace GOTHIC_NAMESPACE
{
	int wld_gettimemin()
	{
		int day, hour, min;

		ogame->GetTime(day, hour, min);

		if (min > 0)
		{
			parser->SetReturn(min);
		}

		return FALSE;
	}

}