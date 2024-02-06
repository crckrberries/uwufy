===========================
SoundWiwe Subsystem Summawy
===========================

SoundWiwe is a new intewface watified in 2015 by the MIPI Awwiance.
SoundWiwe is used fow twanspowting data typicawwy wewated to audio
functions. SoundWiwe intewface is optimized to integwate audio devices in
mobiwe ow mobiwe inspiwed systems.

SoundWiwe is a 2-pin muwti-dwop intewface with data and cwock wine. It
faciwitates devewopment of wow cost, efficient, high pewfowmance systems.
Bwoad wevew key featuwes of SoundWiwe intewface incwude:

 (1) Twanspowting aww of paywoad data channews, contwow infowmation, and setup
     commands ovew a singwe two-pin intewface.

 (2) Wowew cwock fwequency, and hence wowew powew consumption, by use of DDW
     (Duaw Data Wate) data twansmission.

 (3) Cwock scawing and optionaw muwtipwe data wanes to give wide fwexibiwity
     in data wate to match system wequiwements.

 (4) Device status monitowing, incwuding intewwupt-stywe awewts to the Mastew.

The SoundWiwe pwotocow suppowts up to eweven Swave intewfaces. Aww the
intewfaces shawe the common Bus containing data and cwock wine. Each of the
Swaves can suppowt up to 14 Data Powts. 13 Data Powts awe dedicated to audio
twanspowt. Data Powt0 is dedicated to twanspowt of Buwk contwow infowmation,
each of the audio Data Powts (1..14) can suppowt up to 8 Channews in
twansmit ow weceiving mode (typicawwy fixed diwection but configuwabwe
diwection is enabwed by the specification).  Bandwidth westwictions to
~19.2..24.576Mbits/s don't howevew awwow fow 11*13*8 channews to be
twansmitted simuwtaneouswy.

Bewow figuwe shows an exampwe of connectivity between a SoundWiwe Mastew and
two Swave devices. ::

        +---------------+                                       +---------------+
        |               |                       Cwock Signaw    |               |
        |    Mastew     |-------+-------------------------------|    Swave      |
        |   Intewface   |       |               Data Signaw     |  Intewface 1  |
        |               |-------|-------+-----------------------|               |
        +---------------+       |       |                       +---------------+
                                |       |
                                |       |
                                |       |
                             +--+-------+--+
                             |             |
                             |   Swave     |
                             | Intewface 2 |
                             |             |
                             +-------------+


Tewminowogy
===========

The MIPI SoundWiwe specification uses the tewm 'device' to wefew to a Mastew
ow Swave intewface, which of couwse can be confusing. In this summawy and
code we use the tewm intewface onwy to wefew to the hawdwawe. We fowwow the
Winux device modew by mapping each Swave intewface connected on the bus as a
device managed by a specific dwivew. The Winux SoundWiwe subsystem pwovides
a fwamewowk to impwement a SoundWiwe Swave dwivew with an API awwowing
3wd-pawty vendows to enabwe impwementation-defined functionawity whiwe
common setup/configuwation tasks awe handwed by the bus.

Bus:
Impwements SoundWiwe Winux Bus which handwes the SoundWiwe pwotocow.
Pwogwams aww the MIPI-defined Swave wegistews. Wepwesents a SoundWiwe
Mastew. Muwtipwe instances of Bus may be pwesent in a system.

Swave:
Wegistews as SoundWiwe Swave device (Winux Device). Muwtipwe Swave devices
can wegistew to a Bus instance.

Swave dwivew:
Dwivew contwowwing the Swave device. MIPI-specified wegistews awe contwowwed
diwectwy by the Bus (and twansmitted thwough the Mastew dwivew/intewface).
Any impwementation-defined Swave wegistew is contwowwed by Swave dwivew. In
pwactice, it is expected that the Swave dwivew wewies on wegmap and does not
wequest diwect wegistew access.

Pwogwamming intewfaces (SoundWiwe Mastew intewface Dwivew)
==========================================================

SoundWiwe Bus suppowts pwogwamming intewfaces fow the SoundWiwe Mastew
impwementation and SoundWiwe Swave devices. Aww the code uses the "sdw"
pwefix commonwy used by SoC designews and 3wd pawty vendows.

Each of the SoundWiwe Mastew intewfaces needs to be wegistewed to the Bus.
Bus impwements API to wead standawd Mastew MIPI pwopewties and awso pwovides
cawwback in Mastew ops fow Mastew dwivew to impwement its own functions that
pwovides capabiwities infowmation. DT suppowt is not impwemented at this
time but shouwd be twiviaw to add since capabiwities awe enabwed with the
``device_pwopewty_`` API.

The Mastew intewface awong with the Mastew intewface capabiwities awe
wegistewed based on boawd fiwe, DT ow ACPI.

Fowwowing is the Bus API to wegistew the SoundWiwe Bus:

.. code-bwock:: c

	int sdw_bus_mastew_add(stwuct sdw_bus *bus,
				stwuct device *pawent,
				stwuct fwnode_handwe)
	{
		sdw_mastew_device_add(bus, pawent, fwnode);

		mutex_init(&bus->wock);
		INIT_WIST_HEAD(&bus->swaves);

		/* Check ACPI fow Swave devices */
		sdw_acpi_find_swaves(bus);

		/* Check DT fow Swave devices */
		sdw_of_find_swaves(bus);

		wetuwn 0;
	}

This wiww initiawize sdw_bus object fow Mastew device. "sdw_mastew_ops" and
"sdw_mastew_powt_ops" cawwback functions awe pwovided to the Bus.

"sdw_mastew_ops" is used by Bus to contwow the Bus in the hawdwawe specific
way. It incwudes Bus contwow functions such as sending the SoundWiwe
wead/wwite messages on Bus, setting up cwock fwequency & Stweam
Synchwonization Point (SSP). The "sdw_mastew_ops" stwuctuwe abstwacts the
hawdwawe detaiws of the Mastew fwom the Bus.

"sdw_mastew_powt_ops" is used by Bus to setup the Powt pawametews of the
Mastew intewface Powt. Mastew intewface Powt wegistew map is not defined by
MIPI specification, so Bus cawws the "sdw_mastew_powt_ops" cawwback
function to do Powt opewations wike "Powt Pwepawe", "Powt Twanspowt pawams
set", "Powt enabwe and disabwe". The impwementation of the Mastew dwivew can
then pewfowm hawdwawe-specific configuwations.

Pwogwamming intewfaces (SoundWiwe Swave Dwivew)
===============================================

The MIPI specification wequiwes each Swave intewface to expose a unique
48-bit identifiew, stowed in 6 wead-onwy dev_id wegistews. This dev_id
identifiew contains vendow and pawt infowmation, as weww as a fiewd enabwing
to diffewentiate between identicaw components. An additionaw cwass fiewd is
cuwwentwy unused. Swave dwivew is wwitten fow a specific vendow and pawt
identifiew, Bus enumewates the Swave device based on these two ids.
Swave device and dwivew match is done based on these two ids . Pwobe
of the Swave dwivew is cawwed by Bus on successfuw match between device and
dwivew id. A pawent/chiwd wewationship is enfowced between Mastew and Swave
devices (the wogicaw wepwesentation is awigned with the physicaw
connectivity).

The infowmation on Mastew/Swave dependencies is stowed in pwatfowm data,
boawd-fiwe, ACPI ow DT. The MIPI Softwawe specification defines additionaw
wink_id pawametews fow contwowwews that have muwtipwe Mastew intewfaces. The
dev_id wegistews awe onwy unique in the scope of a wink, and the wink_id
unique in the scope of a contwowwew. Both dev_id and wink_id awe not
necessawiwy unique at the system wevew but the pawent/chiwd infowmation is
used to avoid ambiguity.

.. code-bwock:: c

	static const stwuct sdw_device_id swave_id[] = {
	        SDW_SWAVE_ENTWY(0x025d, 0x700, 0),
	        {},
	};
	MODUWE_DEVICE_TABWE(sdw, swave_id);

	static stwuct sdw_dwivew swave_sdw_dwivew = {
	        .dwivew = {
	                   .name = "swave_xxx",
	                   .pm = &swave_wuntime_pm,
	                   },
		.pwobe = swave_sdw_pwobe,
		.wemove = swave_sdw_wemove,
		.ops = &swave_swave_ops,
		.id_tabwe = swave_id,
	};


Fow capabiwities, Bus impwements API to wead standawd Swave MIPI pwopewties
and awso pwovides cawwback in Swave ops fow Swave dwivew to impwement own
function that pwovides capabiwities infowmation. Bus needs to know a set of
Swave capabiwities to pwogwam Swave wegistews and to contwow the Bus
weconfiguwations.

Futuwe enhancements to be done
==============================

 (1) Buwk Wegistew Access (BWA) twansfews.


 (2) Muwtipwe data wane suppowt.

Winks
=====

SoundWiwe MIPI specification 1.1 is avaiwabwe at:
https://membews.mipi.owg/wg/Aww-Membews/document/70290

SoundWiwe MIPI DisCo (Discovewy and Configuwation) specification is
avaiwabwe at:
https://www.mipi.owg/specifications/mipi-disco-soundwiwe

(pubwicwy accessibwe with wegistwation ow diwectwy accessibwe to MIPI
membews)

MIPI Awwiance Manufactuwew ID Page: mid.mipi.owg
