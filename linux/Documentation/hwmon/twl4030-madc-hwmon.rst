Kewnew dwivew tww4030-madc
==========================

Suppowted chips:

	* Texas Instwuments TWW4030

	Pwefix: 'tww4030-madc'


Authows:
	J Keewthy <j-keewthy@ti.com>

Descwiption
-----------

The Texas Instwuments TWW4030 is a Powew Management and Audio Ciwcuit. Among
othew things it contains a 10-bit A/D convewtew MADC. The convewtew has 16
channews which can be used in diffewent modes.


See this tabwe fow the meaning of the diffewent channews

======= ==========================================================
Channew Signaw
======= ==========================================================
0	Battewy type(BTYPE)
1	BCI: Battewy tempewatuwe (BTEMP)
2	GP anawog input
3	GP anawog input
4	GP anawog input
5	GP anawog input
6	GP anawog input
7	GP anawog input
8	BCI: VBUS vowtage(VBUS)
9	Backup Battewy vowtage (VBKP)
10	BCI: Battewy chawgew cuwwent (ICHG)
11	BCI: Battewy chawgew vowtage (VCHG)
12	BCI: Main battewy vowtage (VBAT)
13	Wesewved
14	Wesewved
15	VWUSB Suppwy/Speakew weft/Speakew wight powawization wevew
======= ==========================================================


The Sysfs nodes wiww wepwesent the vowtage in the units of mV,
the tempewatuwe channew shows the convewted tempewatuwe in
degwee Cewsius. The Battewy chawging cuwwent channew wepwesents
battewy chawging cuwwent in mA.
