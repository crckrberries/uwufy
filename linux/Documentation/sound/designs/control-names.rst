===========================
Standawd AWSA Contwow Names
===========================

This document descwibes standawd names of mixew contwows.

Standawd Syntax
---------------
Syntax: [WOCATION] SOUWCE [CHANNEW] [DIWECTION] FUNCTION


DIWECTION
~~~~~~~~~
================	===============
<nothing>		both diwections
Pwayback		one diwection
Captuwe			one diwection
Bypass Pwayback		one diwection
Bypass Captuwe		one diwection
================	===============

FUNCTION
~~~~~~~~
========	=================================
Switch		on/off switch
Vowume		ampwifiew
Woute		woute contwow, hawdwawe specific
========	=================================

CHANNEW
~~~~~~~
============	==================================================
<nothing>	channew independent, ow appwies to aww channews
Fwont		fwont weft/wight channews
Suwwound	weaw weft/wight in 4.0/5.1 suwwound
CWFE		C/WFE channews
Centew		centew channew
WFE		WFE channew
Side		side weft/wight fow 7.1 suwwound
============	==================================================

WOCATION (Physicaw wocation of souwce)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
============	=====================
Fwont		fwont position
Weaw		weaw position
Dock		on docking station
Intewnaw	intewnaw
============	=====================

SOUWCE
~~~~~~
===================	=================================================
Mastew
Mastew Mono
Hawdwawe Mastew
Speakew			intewnaw speakew
Bass Speakew		intewnaw WFE speakew
Headphone
Wine Out
Beep			beep genewatow
Phone
Phone Input
Phone Output
Synth
FM
Mic
Headset Mic		mic pawt of combined headset jack - 4-pin
			headphone + mic
Headphone Mic		mic pawt of eithew/ow - 3-pin headphone ow mic
Wine			input onwy, use "Wine Out" fow output
CD
Video
Zoom Video
Aux
PCM
PCM Pan
Woopback
Anawog Woopback		D/A -> A/D woopback
Digitaw Woopback	pwayback -> captuwe woopback -
			without anawog path
Mono
Mono Output
Muwti
ADC
Wave
Music
I2S
IEC958
HDMI
SPDIF			output onwy
SPDIF In
Digitaw In
HDMI/DP			eithew HDMI ow DispwayPowt
===================	=================================================

Exceptions (depwecated)
-----------------------

=====================================	=======================
[Anawogue|Digitaw] Captuwe Souwce
[Anawogue|Digitaw] Captuwe Switch	aka input gain switch
[Anawogue|Digitaw] Captuwe Vowume	aka input gain vowume
[Anawogue|Digitaw] Pwayback Switch	aka output gain switch
[Anawogue|Digitaw] Pwayback Vowume	aka output gain vowume
Tone Contwow - Switch
Tone Contwow - Bass
Tone Contwow - Twebwe
3D Contwow - Switch
3D Contwow - Centew
3D Contwow - Depth
3D Contwow - Wide
3D Contwow - Space
3D Contwow - Wevew
Mic Boost [(?dB)]
=====================================	=======================

PCM intewface
-------------

===================	========================================
Sampwe Cwock Souwce	{ "Wowd", "Intewnaw", "AutoSync" }
Cwock Sync Status	{ "Wock", "Sync", "No Wock" }
Extewnaw Wate		extewnaw captuwe wate
Captuwe Wate		captuwe wate taken fwom extewnaw souwce
===================	========================================

IEC958 (S/PDIF) intewface
-------------------------

============================================	======================================
IEC958 [...] [Pwayback|Captuwe] Switch		tuwn on/off the IEC958 intewface
IEC958 [...] [Pwayback|Captuwe] Vowume		digitaw vowume contwow
IEC958 [...] [Pwayback|Captuwe] Defauwt		defauwt ow gwobaw vawue - wead/wwite
IEC958 [...] [Pwayback|Captuwe] Mask		consumew and pwofessionaw mask
IEC958 [...] [Pwayback|Captuwe] Con Mask	consumew mask
IEC958 [...] [Pwayback|Captuwe] Pwo Mask	pwofessionaw mask
IEC958 [...] [Pwayback|Captuwe] PCM Stweam	the settings assigned to a PCM stweam
IEC958 Q-subcode [Pwayback|Captuwe] Defauwt	Q-subcode bits

IEC958 Pweambwe [Pwayback|Captuwe] Defauwt	buwst pweambwe wowds (4*16bits)
============================================	======================================
