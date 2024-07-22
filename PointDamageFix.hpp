namespace GOTHIC_NAMESPACE
{
	
	// virtual void OnDamage( oSDamageDescriptor& )                                                 zCall( 0x006660E0 );

	//auto eqweapon = player->GetEquippedMeleeWeapon();
	//zSTRING weapon = eqweapon->GetObjectName();
	//  || player->GetEquippedMeleeWeapon()->GetObjectName() == "ITMW_BELIARLIGHTSUPERWEAPON_1H"
	auto Hook_oCNpc_OnDamage_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x006660E0), &oCNpc::OnDamage_Union);
	void oCNpc::OnDamage_Union(oSDamageDescriptor& descDamage)
	{
		if (player->GetInstanceName() == "PC_Hero")
		{
			if (descDamage.enuModeWeapon == 2)
			{
				if (descDamage.enuModeDamage == 64)
				{
					descDamage.bDamageDontKill = 1;
				}
				if (descDamage.enuModeDamage == (64 | 32))
				{
					descDamage.bDamageDontKill = 1;
				}
			}
		}
		(this->*Hook_oCNpc_OnDamage_Union)(descDamage);		
	}
	
	/*	auto Hook_oCNpc_OnDamage_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x006660E0), &oCNpc::OnDamage_Union);
	void oCNpc::OnDamage_Union(oSDamageDescriptor& descDamage)
	{
		if (player->GetInstanceName() == "PC_Hero")
		{
			if ((descDamage.enuModeWeapon == 2 && descDamage.enuModeDamage == 64))
			{
				descDamage.bDamageDontKill = 1;
			}
		}
		(this->*Hook_oCNpc_OnDamage_Union)(descDamage);
	}*/

}