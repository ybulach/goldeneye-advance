////////////////
// Inclusions //
////////////////
#include "../Common/Common.h"

//////////
// menu //
//////////
void menu()
{
	while(scene < JEU)
	{
		if(scene == MENU_BRIEFING)
			menuBriefing();
		else if(scene == MENU_CREDITS)
			menuCredits();
		else
			menuPrincipal();
	}
}
