GoldenEye Advance
=================

Presentation
------------
GoldenEye Advance is a port for Nintendo GBA of the Nintendo 64 video game GoldenEye, developped by Rareware.

![01](http://www.crazy-lapinou.eu/fichiers/goldeneye_advance/version_dev/01.png) ![02](http://www.crazy-lapinou.eu/fichiers/goldeneye_advance/version_dev/02.png) ![03](http://www.crazy-lapinou.eu/fichiers/goldeneye_advance/version_dev/03.png)

The project is separated in 3 parts:
 * Audio
 * Graphics
 * Code

How to use
===========
This is a GBA homebrew, so you need have 3 main choise to play this game:
 * Playing in your PC, using an emulator. You can found many emulators (like VBA) in Google
 * Playing in your GBA, using a flash card. With this method, you can play in real conditions
 * Playing in a multimedia console (like Dingoo, GP2X)

How to compile
===============
You need a GBA cross-compiler to create a _.gba_ file. There are two _.bat_ file (for Windows users) to easily compile the game. The easiest solution is to install HAM (http://www.ngine.de/) with the .exe executable. The *Build.bat* file is configured to use HAM in *C:\HAM* directory. You should modify this file if you installed HAM at another directory or another hard disk.

For Linux users, the makefile uses the *HAMDIR* environment variable to localize your HAM installation directory.

You should modify this variables in the makefile to switch between Windows and Linux:

| Variable     | Windows Contents | Linux Contents |
|--------------|------------------|----------------|
| PROG_EXT     | .exe             | _empty_        |
| GCC_VERSION  | 3.3.2            | 3.2.2          |
| LIBGCC_STYLE | interwork        | normal         |

_(This is because Linux version of HAM is older than Windows version.)_
