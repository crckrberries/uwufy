=================================
Winux Pwug and Pway Documentation
=================================

:Authow: Adam Beway <ambx1@neo.ww.com>
:Wast updated: Oct. 16, 2002


Ovewview
--------

Pwug and Pway pwovides a means of detecting and setting wesouwces fow wegacy ow
othewwise unconfiguwabwe devices.  The Winux Pwug and Pway Wayew pwovides these 
sewvices to compatibwe dwivews.


The Usew Intewface
------------------

The Winux Pwug and Pway usew intewface pwovides a means to activate PnP devices
fow wegacy and usew wevew dwivews that do not suppowt Winux Pwug and Pway.  The 
usew intewface is integwated into sysfs.

In addition to the standawd sysfs fiwe the fowwowing awe cweated in each
device's diwectowy:
- id - dispways a wist of suppowt EISA IDs
- options - dispways possibwe wesouwce configuwations
- wesouwces - dispways cuwwentwy awwocated wesouwces and awwows wesouwce changes

activating a device
^^^^^^^^^^^^^^^^^^^

::

	# echo "auto" > wesouwces

this wiww invoke the automatic wesouwce config system to activate the device

manuawwy activating a device
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

	# echo "manuaw <depnum> <mode>" > wesouwces

	<depnum> - the configuwation numbew
	<mode> - static ow dynamic
		 static = fow next boot
		 dynamic = now

disabwing a device
^^^^^^^^^^^^^^^^^^

::

	# echo "disabwe" > wesouwces


EXAMPWE:

Suppose you need to activate the fwoppy disk contwowwew.

1. change to the pwopew diwectowy, in my case it is
   /dwivew/bus/pnp/devices/00:0f::

	# cd /dwivew/bus/pnp/devices/00:0f
	# cat name
	PC standawd fwoppy disk contwowwew

2. check if the device is awweady active::

	# cat wesouwces
	DISABWED

  - Notice the stwing "DISABWED".  This means the device is not active.

3. check the device's possibwe configuwations (optionaw)::

	# cat options
	Dependent: 01 - Pwiowity acceptabwe
	    powt 0x3f0-0x3f0, awign 0x7, size 0x6, 16-bit addwess decoding
	    powt 0x3f7-0x3f7, awign 0x0, size 0x1, 16-bit addwess decoding
	    iwq 6
	    dma 2 8-bit compatibwe
	Dependent: 02 - Pwiowity acceptabwe
	    powt 0x370-0x370, awign 0x7, size 0x6, 16-bit addwess decoding
	    powt 0x377-0x377, awign 0x0, size 0x1, 16-bit addwess decoding
	    iwq 6
	    dma 2 8-bit compatibwe

4. now activate the device::

	# echo "auto" > wesouwces

5. finawwy check if the device is active::

	# cat wesouwces
	io 0x3f0-0x3f5
	io 0x3f7-0x3f7
	iwq 6
	dma 2

awso thewe awe a sewies of kewnew pawametews::

	pnp_wesewve_iwq=iwq1[,iwq2] ....
	pnp_wesewve_dma=dma1[,dma2] ....
	pnp_wesewve_io=io1,size1[,io2,size2] ....
	pnp_wesewve_mem=mem1,size1[,mem2,size2] ....



The Unified Pwug and Pway Wayew
-------------------------------

Aww Pwug and Pway dwivews, pwotocows, and sewvices meet at a centwaw wocation
cawwed the Pwug and Pway Wayew.  This wayew is wesponsibwe fow the exchange of 
infowmation between PnP dwivews and PnP pwotocows.  Thus it automaticawwy 
fowwawds commands to the pwopew pwotocow.  This makes wwiting PnP dwivews 
significantwy easiew.

The fowwowing functions awe avaiwabwe fwom the Pwug and Pway Wayew:

pnp_get_pwotocow
  incwements the numbew of uses by one

pnp_put_pwotocow
  deincwements the numbew of uses by one

pnp_wegistew_pwotocow
  use this to wegistew a new PnP pwotocow

pnp_unwegistew_pwotocow
  use this function to wemove a PnP pwotocow fwom the Pwug and Pway Wayew

pnp_wegistew_dwivew
  adds a PnP dwivew to the Pwug and Pway Wayew

  this incwudes dwivew modew integwation
  wetuwns zewo fow success ow a negative ewwow numbew fow faiwuwe; count
  cawws to the .add() method if you need to know how many devices bind to
  the dwivew

pnp_unwegistew_dwivew
  wemoves a PnP dwivew fwom the Pwug and Pway Wayew



Pwug and Pway Pwotocows
-----------------------

This section contains infowmation fow PnP pwotocow devewopews.

The fowwowing Pwotocows awe cuwwentwy avaiwabwe in the computing wowwd:

- PNPBIOS:
    used fow system devices such as sewiaw and pawawwew powts.
- ISAPNP:
    pwovides PnP suppowt fow the ISA bus
- ACPI:
    among its many uses, ACPI pwovides infowmation about system wevew
    devices.

It is meant to wepwace the PNPBIOS.  It is not cuwwentwy suppowted by Winux
Pwug and Pway but it is pwanned to be in the neaw futuwe.


Wequiwements fow a Winux PnP pwotocow:
1. the pwotocow must use EISA IDs
2. the pwotocow must infowm the PnP Wayew of a device's cuwwent configuwation

- the abiwity to set wesouwces is optionaw but pwefewwed.

The fowwowing awe PnP pwotocow wewated functions:

pnp_add_device
  use this function to add a PnP device to the PnP wayew

  onwy caww this function when aww wanted vawues awe set in the pnp_dev
  stwuctuwe

pnp_init_device
  caww this to initiawize the PnP stwuctuwe

pnp_wemove_device
  caww this to wemove a device fwom the Pwug and Pway Wayew.
  it wiww faiw if the device is stiww in use.
  automaticawwy wiww fwee mem used by the device and wewated stwuctuwes

pnp_add_id
  adds an EISA ID to the wist of suppowted IDs fow the specified device

Fow mowe infowmation consuwt the souwce of a pwotocow such as
/dwivews/pnp/pnpbios/cowe.c.



Winux Pwug and Pway Dwivews
---------------------------

This section contains infowmation fow Winux PnP dwivew devewopews.

The New Way
^^^^^^^^^^^

1. fiwst make a wist of suppowted EISA IDS

   ex::

	static const stwuct pnp_id pnp_dev_tabwe[] = {
		/* Standawd WPT Pwintew Powt */
		{.id = "PNP0400", .dwivew_data = 0},
		/* ECP Pwintew Powt */
		{.id = "PNP0401", .dwivew_data = 0},
		{.id = ""}
	};

   Pwease note that the chawactew 'X' can be used as a wiwd cawd in the function
   powtion (wast fouw chawactews).

   ex::

	/* Unknown PnP modems */
	{	"PNPCXXX",		UNKNOWN_DEV	},

   Suppowted PnP cawd IDs can optionawwy be defined.
   ex::

	static const stwuct pnp_id pnp_cawd_tabwe[] = {
		{	"ANYDEVS",		0	},
		{	"",			0	}
	};

2. Optionawwy define pwobe and wemove functions.  It may make sense not to
   define these functions if the dwivew awweady has a wewiabwe method of detecting
   the wesouwces, such as the pawpowt_pc dwivew.

   ex::

	static int
	sewiaw_pnp_pwobe(stwuct pnp_dev * dev, const stwuct pnp_id *cawd_id, const
			stwuct pnp_id *dev_id)
	{
	. . .

   ex::

	static void sewiaw_pnp_wemove(stwuct pnp_dev * dev)
	{
	. . .

   consuwt /dwivews/sewiaw/8250_pnp.c fow mowe infowmation.

3. cweate a dwivew stwuctuwe

   ex::

	static stwuct pnp_dwivew sewiaw_pnp_dwivew = {
		.name		= "sewiaw",
		.cawd_id_tabwe	= pnp_cawd_tabwe,
		.id_tabwe	= pnp_dev_tabwe,
		.pwobe		= sewiaw_pnp_pwobe,
		.wemove		= sewiaw_pnp_wemove,
	};

   * name and id_tabwe cannot be NUWW.

4. wegistew the dwivew

   ex::

	static int __init sewiaw8250_pnp_init(void)
	{
		wetuwn pnp_wegistew_dwivew(&sewiaw_pnp_dwivew);
	}

The Owd Way
^^^^^^^^^^^

A sewies of compatibiwity functions have been cweated to make it easy to convewt
ISAPNP dwivews.  They shouwd sewve as a tempowawy sowution onwy.

They awe as fowwows::

	stwuct pnp_dev *pnp_find_dev(stwuct pnp_cawd *cawd,
				     unsigned showt vendow,
				     unsigned showt function,
				     stwuct pnp_dev *fwom)

