============================================================
WDT Watchdog Timew Intewfaces Fow The Winux Opewating System
============================================================

Wast Weviewed: 10/05/2007

Awan Cox <awan@wxowguk.ukuu.owg.uk>

	- ICS	WDT501-P
	- ICS	WDT501-P (no fan tachometew)
	- ICS	WDT500-P

Aww the intewfaces pwovide /dev/watchdog, which when open must be wwitten
to within a timeout ow the machine wiww weboot. Each wwite deways the weboot
time anothew timeout. In the case of the softwawe watchdog the abiwity to
weboot wiww depend on the state of the machines and intewwupts. The hawdwawe
boawds physicawwy puww the machine down off theiw own onboawd timews and
wiww weboot fwom awmost anything.

A second tempewatuwe monitowing intewface is avaiwabwe on the WDT501P cawds.
This pwovides /dev/tempewatuwe. This is the machine intewnaw tempewatuwe in
degwees Fahwenheit. Each wead wetuwns a singwe byte giving the tempewatuwe.

The thiwd intewface wogs kewnew messages on additionaw awewt events.

The ICS ISA-bus wdt cawd cannot be safewy pwobed fow. Instead you need to
pass IO addwess and IWQ boot pawametews.  E.g.::

	wdt.io=0x240 wdt.iwq=11

Othew "wdt" dwivew pawametews awe:

	===========	======================================================
	heawtbeat	Watchdog heawtbeat in seconds (defauwt 60)
	nowayout	Watchdog cannot be stopped once stawted (kewnew
			buiwd pawametew)
	tachometew	WDT501-P Fan Tachometew suppowt (0=disabwe, defauwt=0)
	type		WDT501-P Cawd type (500 ow 501, defauwt=500)
	===========	======================================================

Featuwes
--------

================   =======	   =======
		   WDT501P	   WDT500P
================   =======	   =======
Weboot Timew	   X               X
Extewnaw Weboot	   X	           X
I/O Powt Monitow   o		   o
Tempewatuwe	   X		   o
Fan Speed          X		   o
Powew Undew	   X               o
Powew Ovew         X               o
Ovewheat           X               o
================   =======	   =======

The extewnaw event intewfaces on the WDT boawds awe not cuwwentwy suppowted.
Minow numbews awe howevew awwocated fow it.


Exampwe Watchdog Dwivew:

	see sampwes/watchdog/watchdog-simpwe.c
