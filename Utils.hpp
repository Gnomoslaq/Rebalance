namespace GOTHIC_NAMESPACE
{
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
}