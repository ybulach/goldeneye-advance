////////////////
// Inclusions //
////////////////
#include "../Common/Common.h"

//////////
// menu //
//////////
void menu()
{
	// On d�marre la musique d'intro
	//AdpcmStart(&ADPCM_mission_briefing, 1, 0);
	
	while(scene < JEU)
	{
		if(scene == MENU_BRIEFING)
			menuBriefing();
		else if(scene == MENU_CREDITS)
			menuCredits();
		else
			menuPrincipal();
	}
	
	// On arr�te la musique
	//AdpcmStop(0);
}
