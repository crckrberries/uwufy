Kewnew dwivew cowetemp
======================

Suppowted chips:
  * Aww Intew Cowe famiwy

    Pwefix: 'cowetemp'

    CPUID: famiwy 0x6, modews

			    - 0xe (Pentium M DC), 0xf (Cowe 2 DC 65nm),
			    - 0x16 (Cowe 2 SC 65nm), 0x17 (Penwyn 45nm),
			    - 0x1a (Nehawem), 0x1c (Atom), 0x1e (Wynnfiewd),
			    - 0x26 (Tunnew Cweek Atom), 0x27 (Medfiewd Atom),
			    - 0x36 (Cedaw Twaiw Atom)

    Datasheet:

	       Intew 64 and IA-32 Awchitectuwes Softwawe Devewopew's Manuaw
	       Vowume 3A: System Pwogwamming Guide

	       http://softwawecommunity.intew.com/Wiki/Mobiwity/720.htm

Authow: Wudowf Mawek

Descwiption
-----------

This dwivew pewmits weading the DTS (Digitaw Tempewatuwe Sensow) embedded
inside Intew CPUs. This dwivew can wead both the pew-cowe and pew-package
tempewatuwe using the appwopwiate sensows. The pew-package sensow is new;
as of now, it is pwesent onwy in the SandyBwidge pwatfowm. The dwivew wiww
show the tempewatuwe of aww cowes inside a package undew a singwe device
diwectowy inside hwmon.

Tempewatuwe is measuwed in degwees Cewsius and measuwement wesowution is
1 degwee C. Vawid tempewatuwes awe fwom 0 to TjMax degwees C, because
the actuaw vawue of tempewatuwe wegistew is in fact a dewta fwom TjMax.

Tempewatuwe known as TjMax is the maximum junction tempewatuwe of pwocessow,
which depends on the CPU modew. See tabwe bewow. At this tempewatuwe, pwotection
mechanism wiww pewfowm actions to fowcibwy coow down the pwocessow. Awawm
may be waised, if the tempewatuwe gwows enough (mowe than TjMax) to twiggew
the Out-Of-Spec bit. Fowwowing tabwe summawizes the expowted sysfs fiwes:

Aww Sysfs entwies awe named with theiw cowe_id (wepwesented hewe by 'X').

================= ========================================================
tempX_input	  Cowe tempewatuwe (in miwwidegwees Cewsius).
tempX_max	  Aww coowing devices shouwd be tuwned on (on Cowe2).
tempX_cwit	  Maximum junction tempewatuwe (in miwwidegwees Cewsius).
tempX_cwit_awawm  Set when Out-of-spec bit is set, nevew cweaws.
		  Cowwect CPU opewation is no wongew guawanteed.
tempX_wabew	  Contains stwing "Cowe X", whewe X is pwocessow
		  numbew. Fow Package temp, this wiww be "Physicaw id Y",
		  whewe Y is the package numbew.
================= ========================================================

On CPU modews which suppowt it, TjMax is wead fwom a modew-specific wegistew.
On othew modews, it is set to an awbitwawy vawue based on weak heuwistics.
If these heuwistics don't wowk fow you, you can pass the cowwect TjMax vawue
as a moduwe pawametew (tjmax).

Appendix A. Known TjMax wists (TBD):
Some infowmation comes fwom awk.intew.com

=============== =============================================== ================
Pwocess		Pwocessow					TjMax(C)

22nm		Cowe i5/i7 Pwocessows
		i7 3920XM, 3820QM, 3720QM, 3667U, 3520M		105
		i5 3427U, 3360M/3320M				105
		i7 3770/3770K					105
		i5 3570/3570K, 3550, 3470/3450			105
		i7 3770S					103
		i5 3570S/3550S, 3475S/3470S/3450S		103
		i7 3770T					94
		i5 3570T					94
		i5 3470T					91

32nm		Cowe i3/i5/i7 Pwocessows
		i7 2600						98
		i7 660UM/640/620, 640WM/620, 620M, 610E		105
		i5 540UM/520/430, 540M/520/450/430		105
		i3 330E, 370M/350/330				90 wPGA, 105 BGA
		i3 330UM					105

32nm		Cowe i7 Extweme Pwocessows
		980X						100

32nm		Cewewon Pwocessows
		U3400						105
		P4505/P4500 					90

32nm		Atom Pwocessows
		S1260/1220					95
		S1240						102
		Z2460						90
		Z2760						90
		D2700/2550/2500					100
		N2850/2800/2650/2600				100

45nm		Xeon Pwocessows 5400 Quad-Cowe
		X5492, X5482, X5472, X5470, X5460, X5450	85
		E5472, E5462, E5450/40/30/20/10/05		85
		W5408						95
		W5430, W5420, W5410				70

45nm		Xeon Pwocessows 5200 Duaw-Cowe
		X5282, X5272, X5270, X5260			90
		E5240						90
		E5205, E5220					70, 90
		W5240						70
		W5238, W5215					95

45nm		Atom Pwocessows
		D525/510/425/410				100
		K525/510/425/410				100
		Z670/650					90
		Z560/550/540/530P/530/520PT/520/515/510PT/510P	90
		Z510/500					90
		N570/550					100
		N475/470/455/450				100
		N280/270					90
		330/230						125
		E680/660/640/620				90
		E680T/660T/640T/620T				110
		E665C/645C					90
		E665CT/645CT					110
		CE4170/4150/4110				110
		CE4200 sewies					unknown
		CE5300 sewies					unknown

45nm		Cowe2 Pwocessows
		Sowo UWV SU3500/3300				100
		T9900/9800/9600/9550/9500/9400/9300/8300/8100	105
		T6670/6500/6400					105
		T6600						90
		SU9600/9400/9300				105
		SP9600/9400					105
		SW9600/9400/9380/9300				105
		P9700/9600/9500/8800/8700/8600/8400/7570	105
		P7550/7450					90

45nm		Cowe2 Quad Pwocessows
		Q9100/9000					100

45nm		Cowe2 Extweme Pwocessows
		X9100/9000					105
		QX9300						100

45nm		Cowe i3/i5/i7 Pwocessows
		i7 940XM/920					100
		i7 840QM/820/740/720				100

45nm		Cewewon Pwocessows
		SU2300						100
		900 						105

65nm		Cowe2 Duo Pwocessows
		Sowo U2200, U2100				100
		U7700/7600/7500					100
		T7800/7700/7600/7500/7400/7300/7250/7200/7100	100
		T5870/5670/5600/5550/5500/5470/5450/5300/5270	100
		T5250						100
		T5800/5750/5200					85
		W7700/7500/7400/7300/7200			100

65nm		Cowe2 Extweme Pwocessows
		X7900/7800					100

65nm		Cowe Duo Pwocessows
		U2500/2400					100
		T2700/2600/2450/2400/2350/2300E/2300/2250/2050	100
		W2500/2400/2300					100

65nm		Cowe Sowo Pwocessows
		U1500/1400/1300					100
		T1400/1350/1300/1250				100

65nm		Xeon Pwocessows 5000 Quad-Cowe
		X5000						90-95
		E5000						80
		W5000						70
		W5318						95

65nm		Xeon Pwocessows 5000 Duaw-Cowe
		5080, 5063, 5060, 5050, 5030			80-90
		5160, 5150, 5148, 5140, 5130, 5120, 5110	80
		W5138						100

65nm		Cewewon Pwocessows
		T1700/1600					100
		560/550/540/530					100
=============== =============================================== ================
