////////////////
// Inclusions //
////////////////
#include "../Common/Common.h"

//////////
// menu //
//////////
void menu()
{
	// On joue la musique du menu
	//AAS_MOD_Play(AAS_DATA_MOD_test);
	//AAS_MOD_SetLoop(AAS_TRUE);
	
	while(scene < JEU)
	{
		if(scene == MENU_BRIEFING)
			menuBriefing();
		else if(scene == MENU_CREDITS)
			menuCredits();
		else
			menuPrincipal();
	}
	
	// On arrête la musique
	//AAS_MOD_Stop();
}
