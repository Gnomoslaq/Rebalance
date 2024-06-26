namespace GOTHIC_NAMESPACE
{
    // New Sprint
    class NewSprint
    {
    public:
        ~NewSprint() {}
        zCArray<unsigned short> sprintkeys;
        void Loop()
        {
            auto stamina = parser->GetSymbol("ATR_STAMINA");
            auto stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");

            this->KeyInput();

            //if (!this->CanUseSprint())
            //{
            //    return;
            //}

            if (this->SprintActive && stamina->single_floatdata > 0)
            {
                player->ApplyOverlay("HUMANS_SPRINT.mds");
            }

            if (this->SprintActive && stamina->single_floatdata == 0)
            {
                this->SprintActive = !this->SprintActive;
                player->RemoveOverlay("HUMANS_SPRINT.mds");
            }
        }
        float timer;
        void SprintTick()
        {


            auto stamina = parser->GetSymbol("ATR_STAMINA");
            auto stamina_max = parser->GetSymbol("ATR_STAMINA_MAX");

            timer += ztimer->frameTimeFloat; // wersja zalezna od factormotion (szybciej spierdala na przyspieszeniu)
            //timer += ztimer->frameTimeFloat / ztimer->factorMotion; // wersja zalezna od czasu rzeczywistego

            if (timer < 1000.0f)
            {
                return;
            }

            timer -= 1000.0f;

            if (SprintActive && stamina->single_intdata > 0)
            {
                int StaminaTick = 5;

                if (stamina->single_intdata >= StaminaTick)
                {
                    stamina->single_intdata = stamina->single_intdata - StaminaTick;
                }
                if (stamina->single_intdata < StaminaTick)
                {
                    stamina->single_intdata = 0;
                }
            }
        }

    public:
        // float timer;
        bool IsSprintBindToggled()
        {
            for (int i = 0; i < sprintkeys.GetNumInList(); i++)
            {
                if (zinput->KeyToggled(sprintkeys[i]))
                {
                    return true;
                }
            }

            return false;
        }



    public:

        void KeyInput()
        {
            if (IsSprintBindToggled())
            {
                this->SprintActive = !this->SprintActive;

                if (!this->SprintActive)
                {
                    player->RemoveOverlay("HUMANS_SPRINT.mds");
                    return;
                }
            }

        }

        bool CanUseSprint()
        {
            zBOOL moveAllowed = zCAICamera::GetCurrent() ? zCAICamera::GetCurrent()->playerIsMovable : TRUE;

            if (ogame->game_testmode
                || zCConsole::cur_console
                || !oCInformationManager::GetInformationManager().HasFinished()
                || player->inventory2.IsOpen()
                || player->GetBodyState() == BS_FALL
                || player->guild > 19
                || player->interactMob
                || player->IsInGlobalCutscene()
                || !moveAllowed
                || player->GetEM()->GetCutsceneMode()
                || player->IsUnconscious()
                || player->IsDead()
                )
            {
                return false;
            }

            return true;
        }

    public:

        zCTimer TimerAni;
        //zCModelAni* RunAni = GetModel()->GetAniFromAniID(anictrl->s_runl[fmode]);

        //zCModelAni* RunAni = player->GetModel()->GetAniFromAniID();
        int LockRegenStaminaTime;
        bool SprintEnabled;
        int StaminaMax;
        int Stamina;


        bool SprintActive;

    };
    std::unique_ptr<NewSprint> newSprint;

}