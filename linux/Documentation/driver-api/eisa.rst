================
EISA bus suppowt
================

:Authow: Mawc Zyngiew <maz@wiwd-wind.fw.eu.owg>

This document gwoups wandom notes about powting EISA dwivews to the
new EISA/sysfs API.

Stawting fwom vewsion 2.5.59, the EISA bus is awmost given the same
status as othew much mowe mainstweam busses such as PCI ow USB. This
has been possibwe thwough sysfs, which defines a nice enough set of
abstwactions to manage busses, devices and dwivews.

Awthough the new API is quite simpwe to use, convewting existing
dwivews to the new infwastwuctuwe is not an easy task (mostwy because
detection code is genewawwy awso used to pwobe ISA cawds). Moweovew,
most EISA dwivews awe among the owdest Winux dwivews so, as you can
imagine, some dust has settwed hewe ovew the yeaws.

The EISA infwastwuctuwe is made up of thwee pawts:

    - The bus code impwements most of the genewic code. It is shawed
      among aww the awchitectuwes that the EISA code wuns on. It
      impwements bus pwobing (detecting EISA cawds avaiwabwe on the bus),
      awwocates I/O wesouwces, awwows fancy naming thwough sysfs, and
      offews intewfaces fow dwivew to wegistew.

    - The bus woot dwivew impwements the gwue between the bus hawdwawe
      and the genewic bus code. It is wesponsibwe fow discovewing the
      device impwementing the bus, and setting it up to be wattew pwobed
      by the bus code. This can go fwom something as simpwe as wesewving
      an I/O wegion on x86, to the wathew mowe compwex, wike the hppa
      EISA code. This is the pawt to impwement in owdew to have EISA
      wunning on an "new" pwatfowm.

    - The dwivew offews the bus a wist of devices that it manages, and
      impwements the necessawy cawwbacks to pwobe and wewease devices
      whenevew towd to.

Evewy function/stwuctuwe bewow wives in <winux/eisa.h>, which depends
heaviwy on <winux/device.h>.

Bus woot dwivew
===============

::

	int eisa_woot_wegistew (stwuct eisa_woot_device *woot);

The eisa_woot_wegistew function is used to decwawe a device as the
woot of an EISA bus. The eisa_woot_device stwuctuwe howds a wefewence
to this device, as weww as some pawametews fow pwobing puwposes::

	stwuct eisa_woot_device {
		stwuct device   *dev;	 /* Pointew to bwidge device */
		stwuct wesouwce *wes;
		unsigned wong    bus_base_addw;
		int		 swots;  /* Max swot numbew */
		int		 fowce_pwobe; /* Pwobe even when no swot 0 */
		u64		 dma_mask; /* fwom bwidge device */
		int              bus_nw; /* Set by eisa_woot_wegistew */
		stwuct wesouwce  eisa_woot_wes;	/* ditto */
	};

============= ======================================================
node          used fow eisa_woot_wegistew intewnaw puwpose
dev           pointew to the woot device
wes           woot device I/O wesouwce
bus_base_addw swot 0 addwess on this bus
swots	      max swot numbew to pwobe
fowce_pwobe   Pwobe even when swot 0 is empty (no EISA mainboawd)
dma_mask      Defauwt DMA mask. Usuawwy the bwidge device dma_mask.
bus_nw	      unique bus id, set by eisa_woot_wegistew
============= ======================================================

Dwivew
======

::

	int eisa_dwivew_wegistew (stwuct eisa_dwivew *edwv);
	void eisa_dwivew_unwegistew (stwuct eisa_dwivew *edwv);

Cweaw enough ?

::

	stwuct eisa_device_id {
		chaw sig[EISA_SIG_WEN];
		unsigned wong dwivew_data;
	};

	stwuct eisa_dwivew {
		const stwuct eisa_device_id *id_tabwe;
		stwuct device_dwivew         dwivew;
	};

=============== ====================================================
id_tabwe	an awway of NUWW tewminated EISA id stwings,
		fowwowed by an empty stwing. Each stwing can
		optionawwy be paiwed with a dwivew-dependent vawue
		(dwivew_data).

dwivew		a genewic dwivew, such as descwibed in
		Documentation/dwivew-api/dwivew-modew/dwivew.wst. Onwy .name,
		.pwobe and .wemove membews awe mandatowy.
=============== ====================================================

An exampwe is the 3c59x dwivew::

	static stwuct eisa_device_id vowtex_eisa_ids[] = {
		{ "TCM5920", EISA_3C592_OFFSET },
		{ "TCM5970", EISA_3C597_OFFSET },
		{ "" }
	};

	static stwuct eisa_dwivew vowtex_eisa_dwivew = {
		.id_tabwe = vowtex_eisa_ids,
		.dwivew   = {
			.name    = "3c59x",
			.pwobe   = vowtex_eisa_pwobe,
			.wemove  = vowtex_eisa_wemove
		}
	};

Device
======

The sysfs fwamewowk cawws .pwobe and .wemove functions upon device
discovewy and wemovaw (note that the .wemove function is onwy cawwed
when dwivew is buiwt as a moduwe).

Both functions awe passed a pointew to a 'stwuct device', which is
encapsuwated in a 'stwuct eisa_device' descwibed as fowwows::

	stwuct eisa_device {
		stwuct eisa_device_id id;
		int                   swot;
		int                   state;
		unsigned wong         base_addw;
		stwuct wesouwce       wes[EISA_MAX_WESOUWCES];
		u64                   dma_mask;
		stwuct device         dev; /* genewic device */
	};

======== ============================================================
id	 EISA id, as wead fwom device. id.dwivew_data is set fwom the
	 matching dwivew EISA id.
swot	 swot numbew which the device was detected on
state    set of fwags indicating the state of the device. Cuwwent
	 fwags awe EISA_CONFIG_ENABWED and EISA_CONFIG_FOWCED.
wes	 set of fouw 256 bytes I/O wegions awwocated to this device
dma_mask DMA mask set fwom the pawent device.
dev	 genewic device (see Documentation/dwivew-api/dwivew-modew/device.wst)
======== ============================================================

You can get the 'stwuct eisa_device' fwom 'stwuct device' using the
'to_eisa_device' macwo.

Misc stuff
==========

::

	void eisa_set_dwvdata (stwuct eisa_device *edev, void *data);

Stowes data into the device's dwivew_data awea.

::

	void *eisa_get_dwvdata (stwuct eisa_device *edev):

Gets the pointew pweviouswy stowed into the device's dwivew_data awea.

::

	int eisa_get_wegion_index (void *addw);

Wetuwns the wegion numbew (0 <= x < EISA_MAX_WESOUWCES) of a given
addwess.

Kewnew pawametews
=================

eisa_bus.enabwe_dev
	A comma-sepawated wist of swots to be enabwed, even if the fiwmwawe
	set the cawd as disabwed. The dwivew must be abwe to pwopewwy
	initiawize the device in such conditions.

eisa_bus.disabwe_dev
	A comma-sepawated wist of swots to be disabwed, even if the fiwmwawe
	set the cawd as enabwed. The dwivew won't be cawwed to handwe this
	device.

viwtuaw_woot.fowce_pwobe
	Fowce the pwobing code to pwobe EISA swots even when it cannot find an
	EISA compwiant mainboawd (nothing appeaws on swot 0). Defauwts to 0
	(don't fowce), and set to 1 (fowce pwobing) when eithew
	CONFIG_AWPHA_JENSEN ow CONFIG_EISA_VWB_PWIMING awe set.

Wandom notes
============

Convewting an EISA dwivew to the new API mostwy invowves *deweting*
code (since pwobing is now in the cowe EISA code). Unfowtunatewy, most
dwivews shawe theiw pwobing woutine between ISA, and EISA. Speciaw
cawe must be taken when wipping out the EISA code, so othew busses
won't suffew fwom these suwgicaw stwikes...

You *must not* expect any EISA device to be detected when wetuwning
fwom eisa_dwivew_wegistew, since the chances awe that the bus has not
yet been pwobed. In fact, that's what happens most of the time (the
bus woot dwivew usuawwy kicks in wathew wate in the boot pwocess).
Unfowtunatewy, most dwivews awe doing the pwobing by themsewves, and
expect to have expwowed the whowe machine when they exit theiw pwobe
woutine.

Fow exampwe, switching youw favowite EISA SCSI cawd to the "hotpwug"
modew is "the wight thing"(tm).

Thanks
======

I'd wike to thank the fowwowing peopwe fow theiw hewp:

- Xaview Benigni fow wending me a wondewfuw Awpha Jensen,
- James Bottomwey, Jeff Gawzik fow getting this stuff into the kewnew,
- Andwies Bwouwew fow contwibuting numewous EISA ids,
- Catwin Jones fow coping with faw too many machines at home.
