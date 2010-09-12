#################
# Nom de la ROM #
#################
PROGNAME = goldeneye-advance

##########################
# Options de compilation #
##########################
HAMDIR  = C:\HAM
GCCARM  = $(HAMDIR)/gcc-arm

INCDIR  = -I $(GCCARM)/arm-thumb-elf/include -I $(HAMDIR)/include -I Sources/Common/LibAAS -I Sources/Common/LibAAS/LowLevelAccess
LIBDIR  = -L $(GCCARM)/arm-thumb-elf/lib/interwork -L $(GCCARM)/lib/gcc-lib/arm-thumb-elf/3.3.2/interwork -L $(GCCARM)/lib/ -L Sources/Common/LibAAS/

LD_LIBS = -lgcc -lc
#LD_LIBS += -lAAS

ASFLAGS = -mthumb-interwork
CFLAGS  = $(INCDIR) -c -O2 -mthumb-interwork -mlong-calls -Wall
LDFLAGS = $(LIBDIR) --script $(HAMDIR)/system/lnkscript

AR      = $(GCCARM)/bin/arm-thumb-elf-ar.exe
AS      = $(GCCARM)/bin/arm-thumb-elf-as.exe
CC      = $(GCCARM)/bin/arm-thumb-elf-gcc.exe
LD      = $(GCCARM)/bin/arm-thumb-elf-ld.exe
OBJCOPY = $(GCCARM)/bin/arm-thumb-elf-objcopy.exe
SHELL   = sh.exe

# Celle-ci est pour faire plaisir a VHAM...
ADD_LIBS+=

#################################
# Liste des fichiers a compiler #
#################################
OFILES = Sources/crt0.o	\
			Sources/Common/Common.o \
			Sources/Intro/Intro.o \
			Sources/Jeu/Jeu.o \
			Sources/Jeu/Armes/Armes.o \
			Sources/Jeu/Map/Map.o \
			Sources/Jeu/Personnages/Personnages.o \
			Sources/Main.o	\
			Sources/Menu/Menu.o \
			Sources/Menu/MenuPrincipal.o \
			Sources/Menu/MenuBriefing.o \
			Sources/Menu/MenuCredits.o \
			\
			Graphics/sprites/tir/tir.til.o \
			Graphics/sprites/curseur/curseur.til.o \
			Graphics/sprites/font/font.til.o \
			Graphics/sprites/interface/interface.pal.o \
			Graphics/sprites/james_bond/james_bond.til.o \
			Graphics/sprites/scientifique/scientifique.til.o \
			\
			Graphics/intro/info/info.bmp.o \
			Graphics/intro/info/info.pal.o \
			Graphics/intro/logo/logo.bmp.o \
			Graphics/intro/logo/logo.pal.o \
			Graphics/intro/player_advance/player_advance.bmp.o \
			Graphics/intro/player_advance/player_advance.pal.o \
			\
			Graphics/menu/menu_principal/menu_principal.bmp.o \
			Graphics/menu/menu_principal/menu_principal.pal.o \
			Graphics/menu/menu_briefing/menu_briefing_01.bmp.o \
			Graphics/menu/menu_briefing/menu_briefing_01.pal.o \
			\
			Graphics/maps/exemple/exemple.pal.o \
			Graphics/maps/exemple/exemple.til.o \
			Graphics/maps/exemple/exemple_fond.map.o \
			Graphics/maps/exemple/exemple_plan.map.o \
			Graphics/maps/exemple/exemple_col.map.o \
			\
			Graphics/maps/dam/dam.pal.o \
			Graphics/maps/dam/dam.til.o \
			Graphics/maps/dam/dam_fond.map.o \
			Graphics/maps/dam/dam_plan.map.o \
			Graphics/maps/dam/dam_col.map.o \
			\
#			Sounds/AAS_Data.o \
# Removed: Musics and sounds to reduce size of ROM during development
#			Sounds/musiques/dam.o \
#			Sounds/musiques/theme.o \
#			Sounds/musiques/mission_briefing.o \

#######################
# Targets "standards" #
#######################
all: $(PROGNAME).gba clean

%.gba: %.elf
	$(OBJCOPY) -v -O binary $< $@
	gbafix.exe $@ -t$*

%.a: $(OFILES)
	$(AR) r $(PROGNAME).a $(OFILES)

$(PROGNAME).elf: $(OFILES)
	$(LD) $(LDFLAGS) -o $@ $(OFILES) $(LD_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

%.o: %.s
	$(AS) $(ASFLAGS) -o $@ $<

# Celle-ci est utile lorsqu'on utilise VHAM (F6)
vbawin: all
	vbawin.exe $(PROGNAME).gba

#################################
# Targets speciales a ce projet #
#################################
clean:
	rm -f *.s *.i *.elf *.a

cleanall: clean
	rm -f $(OFILES)

#######
# END #
#######
