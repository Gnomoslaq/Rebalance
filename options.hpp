namespace GOTHIC_NAMESPACE
{
	static constexpr std::string_view PluginName = "Rebalance";

	int bStaminaValues, bCrimeUserPosX, bCrimeUserPosY;
	bool bShowPray, bShowPrayMessage, bShowPickPocket, bPickPocketSneakRequired, bNewPickPocket;
	zSTRING SprintKey;

	void UpdatePluginSettings()
	{
		bShowPray = zoptions->ReadBool(PluginName.data(), "bShowPray", true);
		bStaminaValues = zoptions->ReadInt(PluginName.data(), "bStaminaValues", 0);
		bShowPrayMessage = zoptions->ReadBool(PluginName.data(), "bShowPrayMessage", 1);
		bCrimeUserPosX = zoptions->ReadInt(PluginName.data(), "bCrimePosX", 0);
		bCrimeUserPosY = zoptions->ReadInt(PluginName.data(), "bCrimePosY", 0);
		bShowPickPocket = zoptions->ReadBool(PluginName.data(), "bShowPickPocket", false);
		bNewPickPocket = zoptions->ReadBool(PluginName.data(), "bNewPickPocket", false);
		bPickPocketSneakRequired = zoptions->ReadBool(PluginName.data(), "bPickPocketSneakRequired", false);
	}
}
