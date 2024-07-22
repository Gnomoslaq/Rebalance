namespace GOTHIC_NAMESPACE
{
	const int LOG_Running = 1;
	const int LOG_SUCCESS = 2;
	const int LOG_FAILED = 3;
	const int LOG_OBSOLETE = 4;

	class QoL
	{
	public:

		void Loop()
		{
			canfocusvob();
		}

	private:
		void canfocusvob()
		{
			auto focus = player->GetFocusVob();
			if (!focus)
			{
				return;
			}
			auto focustype = focus->GetVobType();
			if (!focustype)
			{
				return;			
			}
			if (focustype == zVOB_TYPE_ITEM || focustype == zVOB_TYPE_MOB)
			{
				auto distance = player->GetDistanceToVob(*focus);
				if (!distance)
				{
					return;
				}
				if (distance > 300)
				{
					player->ClearFocusVob();
				}
			}
		}
	};
	std::unique_ptr<QoL> qol;

	void killerguildremind()
	{
		
	}

	// Wld_PlayEffect collide fix
	auto Hook_oCVisualFX_CanThisCollideWith_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x00496AC0), &oCVisualFX::CanThisCollideWith_Union);
	int oCVisualFX::CanThisCollideWith_Union(zCVob* vob)
	{
		zSTRING vfxName = "SPELLFX_ICEBOLT";

		if (vob->GetObjectName() == ("GOBBO_MAGE") || vob->GetObjectName() == ("GOBBO_MAGE_GR1") || vob->GetObjectName() == ("GOBBO_MAGE_GR2") || vob->GetObjectName() == ("GOBBO_MAGE_GR3") || vob->GetObjectName() == ("GOBBO_MAGE_GR4") || vob->GetObjectName() == ("GOBBO_MAGE_GR5") || vob->GetObjectName() == ("GOBBO_MAGE_UNIQ"))
		{
			if (oCVisualFX::fxName == vfxName)
			{
				if (origin != player)
				{
					return 0;
				}
			}
			//(this->*Hook_oCVisualFX_CanThisCollideWith_Union)(vob);
		}

		(this->*Hook_oCVisualFX_CanThisCollideWith_Union)(vob);
	}

}