namespace GOTHIC_NAMESPACE
{
	static constexpr std::string_view PluginName = "Rebalance";
	static constexpr std::string_view zUtilities = "ZUTILITIES";

	zSTRING SprintKey;
	int BarValues;
	bool showPickPocket;


	void ReadSprintBinds()
	{
		newSprint->sprintkeys.DeleteList();
		void* buffer = 0;
		unsigned long bindSize = 0;
		bindSize = zoptions->ReadRaw("KEYS", "keySprint", buffer, newSprint->sprintkeys.GetArray(), newSprint->sprintkeys.GetNumInList() << 1);
		newSprint->sprintkeys.DeleteList();
		for (int i = 0; i < bindSize >> 1; i++)
		{
			if (((unsigned short*)buffer)[i] != 0)
			{
				newSprint->sprintkeys.Insert(((unsigned short*)buffer)[i]);
			}
		}
		delete[] buffer;
	}

	void UpdatePluginSettings()
	{
		ReadSprintBinds();
		ShowPray = zoptions->ReadBool(PluginName.data(), "ShowPray", true);
		BarValues = zoptions->ReadInt(PluginName.data(), "BarValues", 0);
		ShowPrayMessage = zoptions->ReadBool(PluginName.data(), "ShowPrayMessage", 1);
		crimeuserposx = zoptions->ReadInt(PluginName.data(), "CrimePosX", 0);
		crimeuserposy = zoptions->ReadInt(PluginName.data(), "CrimePosY", 0);
		showPickPocket = zoptions->ReadBool(PluginName.data(), "ShowPickPocket", false);
		ImmersiveMode = zoptions->ReadBool("ezPickPocket", "ImmersiveMode", false);
		PickPocketAmbientNPCs = zoptions->ReadBool("ezPickPocket", "PickPocketAmbientNPCs", false);
		GiveAmbientXP = zoptions->ReadBool("ezPickPocket", "GiveAmbientXP", false);
		ShowPickPocketSign = zoptions->ReadBool("ezPickPocket", "ShowPickPocketSign", true);
	}
}