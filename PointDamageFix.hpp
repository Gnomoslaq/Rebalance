namespace GOTHIC_NAMESPACE
{
	
	// virtual void OnDamage( oSDamageDescriptor& )                                                 zCall( 0x006660E0 );

	auto Hook_oCNpc_OnDamage_Union = ::Union::CreateHook(reinterpret_cast<void*>(0x006660E0), &oCNpc::OnDamage_Union);
	void oCNpc::OnDamage_Union(oSDamageDescriptor& descDamage)
	{
		if (player)
		{
			if (descDamage.enuModeWeapon == 2 && descDamage.enuModeDamage == 64)
			{
				descDamage.bDamageDontKill = 1;
			}
		}

		(this->*Hook_oCNpc_OnDamage_Union)(descDamage);

	}
	
}