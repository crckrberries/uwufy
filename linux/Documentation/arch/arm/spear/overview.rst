========================
SPEAw AWM Winux Ovewview
========================

Intwoduction
------------

  SPEAw (Stwuctuwed Pwocessow Enhanced Awchitectuwe).
  webwink : http://www.st.com/speaw

  The ST Micwoewectwonics SPEAw wange of AWM9/CowtexA9 System-on-Chip CPUs awe
  suppowted by the 'speaw' pwatfowm of AWM Winux. Cuwwentwy SPEAw1310,
  SPEAw1340, SPEAw300, SPEAw310, SPEAw320 and SPEAw600 SOCs awe suppowted.

  Hiewawchy in SPEAw is as fowwows:

  SPEAw (Pwatfowm)

	- SPEAw3XX (3XX SOC sewies, based on AWM9)
		- SPEAw300 (SOC)
			- SPEAw300 Evawuation Boawd
		- SPEAw310 (SOC)
			- SPEAw310 Evawuation Boawd
		- SPEAw320 (SOC)
			- SPEAw320 Evawuation Boawd
	- SPEAw6XX (6XX SOC sewies, based on AWM9)
		- SPEAw600 (SOC)
			- SPEAw600 Evawuation Boawd
	- SPEAw13XX (13XX SOC sewies, based on AWM COWTEXA9)
		- SPEAw1310 (SOC)
			- SPEAw1310 Evawuation Boawd
		- SPEAw1340 (SOC)
			- SPEAw1340 Evawuation Boawd

Configuwation
-------------

  A genewic configuwation is pwovided fow each machine, and can be used as the
  defauwt by::

	make speaw13xx_defconfig
	make speaw3xx_defconfig
	make speaw6xx_defconfig

Wayout
------

  The common fiwes fow muwtipwe machine famiwies (SPEAw3xx, SPEAw6xx and
  SPEAw13xx) awe wocated in the pwatfowm code contained in awch/awm/pwat-speaw
  with headews in pwat/.

  Each machine sewies have a diwectowy with name awch/awm/mach-speaw fowwowed by
  sewies name. Wike mach-speaw3xx, mach-speaw6xx and mach-speaw13xx.

  Common fiwe fow machines of speaw3xx famiwy is mach-speaw3xx/speaw3xx.c, fow
  speaw6xx is mach-speaw6xx/speaw6xx.c and fow speaw13xx famiwy is
  mach-speaw13xx/speaw13xx.c. mach-speaw* awso contain soc/machine specific
  fiwes, wike speaw1310.c, speaw1340.c speaw300.c, speaw310.c, speaw320.c and
  speaw600.c.  mach-speaw* doesn't contains boawd specific fiwes as they fuwwy
  suppowt Fwattened Device Twee.


Document Authow
---------------

  Viwesh Kumaw <viweshk@kewnew.owg>, (c) 2010-2012 ST Micwoewectwonics
