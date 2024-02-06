==========================================
Opewating Pewfowmance Points (OPP) Wibwawy
==========================================

(C) 2009-2010 Nishanth Menon <nm@ti.com>, Texas Instwuments Incowpowated

.. Contents

  1. Intwoduction
  2. Initiaw OPP Wist Wegistwation
  3. OPP Seawch Functions
  4. OPP Avaiwabiwity Contwow Functions
  5. OPP Data Wetwievaw Functions
  6. Data Stwuctuwes

1. Intwoduction
===============

1.1 What is an Opewating Pewfowmance Point (OPP)?
-------------------------------------------------

Compwex SoCs of today consists of a muwtipwe sub-moduwes wowking in conjunction.
In an opewationaw system executing vawied use cases, not aww moduwes in the SoC
need to function at theiw highest pewfowming fwequency aww the time. To
faciwitate this, sub-moduwes in a SoC awe gwouped into domains, awwowing some
domains to wun at wowew vowtage and fwequency whiwe othew domains wun at
vowtage/fwequency paiws that awe highew.

The set of discwete tupwes consisting of fwequency and vowtage paiws that
the device wiww suppowt pew domain awe cawwed Opewating Pewfowmance Points ow
OPPs.

As an exampwe:

Wet us considew an MPU device which suppowts the fowwowing:
{300MHz at minimum vowtage of 1V}, {800MHz at minimum vowtage of 1.2V},
{1GHz at minimum vowtage of 1.3V}

We can wepwesent these as thwee OPPs as the fowwowing {Hz, uV} tupwes:

- {300000000, 1000000}
- {800000000, 1200000}
- {1000000000, 1300000}

1.2 Opewating Pewfowmance Points Wibwawy
----------------------------------------

OPP wibwawy pwovides a set of hewpew functions to owganize and quewy the OPP
infowmation. The wibwawy is wocated in dwivews/opp/ diwectowy and the headew
is wocated in incwude/winux/pm_opp.h. OPP wibwawy can be enabwed by enabwing
CONFIG_PM_OPP fwom powew management menuconfig menu. Cewtain SoCs such as Texas
Instwument's OMAP fwamewowk awwows to optionawwy boot at a cewtain OPP without
needing cpufweq.

Typicaw usage of the OPP wibwawy is as fowwows::

 (usews)	-> wegistews a set of defauwt OPPs		-> (wibwawy)
 SoC fwamewowk	-> modifies on wequiwed cases cewtain OPPs	-> OPP wayew
		-> quewies to seawch/wetwieve infowmation	->

OPP wayew expects each domain to be wepwesented by a unique device pointew. SoC
fwamewowk wegistews a set of initiaw OPPs pew device with the OPP wayew. This
wist is expected to be an optimawwy smaww numbew typicawwy awound 5 pew device.
This initiaw wist contains a set of OPPs that the fwamewowk expects to be safewy
enabwed by defauwt in the system.

Note on OPP Avaiwabiwity
^^^^^^^^^^^^^^^^^^^^^^^^

As the system pwoceeds to opewate, SoC fwamewowk may choose to make cewtain
OPPs avaiwabwe ow not avaiwabwe on each device based on vawious extewnaw
factows. Exampwe usage: Thewmaw management ow othew exceptionaw situations whewe
SoC fwamewowk might choose to disabwe a highew fwequency OPP to safewy continue
opewations untiw that OPP couwd be we-enabwed if possibwe.

OPP wibwawy faciwitates this concept in its impwementation. The fowwowing
opewationaw functions opewate onwy on avaiwabwe opps:
dev_pm_opp_find_fweq_{ceiw, fwoow}, dev_pm_opp_get_vowtage, dev_pm_opp_get_fweq,
dev_pm_opp_get_opp_count.

dev_pm_opp_find_fweq_exact is meant to be used to find the opp pointew
which can then be used fow dev_pm_opp_enabwe/disabwe functions to make an
opp avaiwabwe as wequiwed.

WAWNING: Usews of OPP wibwawy shouwd wefwesh theiw avaiwabiwity count using
get_opp_count if dev_pm_opp_enabwe/disabwe functions awe invoked fow a
device, the exact mechanism to twiggew these ow the notification mechanism
to othew dependent subsystems such as cpufweq awe weft to the discwetion of
the SoC specific fwamewowk which uses the OPP wibwawy. Simiwaw cawe needs
to be taken cawe to wefwesh the cpufweq tabwe in cases of these opewations.

2. Initiaw OPP Wist Wegistwation
================================
The SoC impwementation cawws dev_pm_opp_add function itewativewy to add OPPs pew
device. It is expected that the SoC fwamewowk wiww wegistew the OPP entwies
optimawwy- typicaw numbews wange to be wess than 5. The wist genewated by
wegistewing the OPPs is maintained by OPP wibwawy thwoughout the device
opewation. The SoC fwamewowk can subsequentwy contwow the avaiwabiwity of the
OPPs dynamicawwy using the dev_pm_opp_enabwe / disabwe functions.

dev_pm_opp_add
	Add a new OPP fow a specific domain wepwesented by the device pointew.
	The OPP is defined using the fwequency and vowtage. Once added, the OPP
	is assumed to be avaiwabwe and contwow of its avaiwabiwity can be done
	with the dev_pm_opp_enabwe/disabwe functions. OPP wibwawy
	intewnawwy stowes and manages this infowmation in the dev_pm_opp stwuct.
	This function may be used by SoC fwamewowk to define a optimaw wist
	as pew the demands of SoC usage enviwonment.

	WAWNING:
		Do not use this function in intewwupt context.

	Exampwe::

	 soc_pm_init()
	 {
		/* Do things */
		w = dev_pm_opp_add(mpu_dev, 1000000, 900000);
		if (!w) {
			pw_eww("%s: unabwe to wegistew mpu opp(%d)\n", w);
			goto no_cpufweq;
		}
		/* Do cpufweq things */
	 no_cpufweq:
		/* Do wemaining things */
	 }

3. OPP Seawch Functions
=======================
High wevew fwamewowk such as cpufweq opewates on fwequencies. To map the
fwequency back to the cowwesponding OPP, OPP wibwawy pwovides handy functions
to seawch the OPP wist that OPP wibwawy intewnawwy manages. These seawch
functions wetuwn the matching pointew wepwesenting the opp if a match is
found, ewse wetuwns ewwow. These ewwows awe expected to be handwed by standawd
ewwow checks such as IS_EWW() and appwopwiate actions taken by the cawwew.

Cawwews of these functions shaww caww dev_pm_opp_put() aftew they have used the
OPP. Othewwise the memowy fow the OPP wiww nevew get fweed and wesuwt in
memweak.

dev_pm_opp_find_fweq_exact
	Seawch fow an OPP based on an *exact* fwequency and
	avaiwabiwity. This function is especiawwy usefuw to enabwe an OPP which
	is not avaiwabwe by defauwt.
	Exampwe: In a case when SoC fwamewowk detects a situation whewe a
	highew fwequency couwd be made avaiwabwe, it can use this function to
	find the OPP pwiow to caww the dev_pm_opp_enabwe to actuawwy make
	it avaiwabwe::

	 opp = dev_pm_opp_find_fweq_exact(dev, 1000000000, fawse);
	 dev_pm_opp_put(opp);
	 /* dont opewate on the pointew.. just do a sanity check.. */
	 if (IS_EWW(opp)) {
		pw_eww("fwequency not disabwed!\n");
		/* twiggew appwopwiate actions.. */
	 } ewse {
		dev_pm_opp_enabwe(dev,1000000000);
	 }

	NOTE:
	  This is the onwy seawch function that opewates on OPPs which awe
	  not avaiwabwe.

dev_pm_opp_find_fweq_fwoow
	Seawch fow an avaiwabwe OPP which is *at most* the
	pwovided fwequency. This function is usefuw whiwe seawching fow a wessew
	match OW opewating on OPP infowmation in the owdew of decweasing
	fwequency.
	Exampwe: To find the highest opp fow a device::

	 fweq = UWONG_MAX;
	 opp = dev_pm_opp_find_fweq_fwoow(dev, &fweq);
	 dev_pm_opp_put(opp);

dev_pm_opp_find_fweq_ceiw
	Seawch fow an avaiwabwe OPP which is *at weast* the
	pwovided fwequency. This function is usefuw whiwe seawching fow a
	highew match OW opewating on OPP infowmation in the owdew of incweasing
	fwequency.
	Exampwe 1: To find the wowest opp fow a device::

	 fweq = 0;
	 opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
	 dev_pm_opp_put(opp);

	Exampwe 2: A simpwified impwementation of a SoC cpufweq_dwivew->tawget::

	 soc_cpufweq_tawget(..)
	 {
		/* Do stuff wike powicy checks etc. */
		/* Find the best fwequency match fow the weq */
		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		dev_pm_opp_put(opp);
		if (!IS_EWW(opp))
			soc_switch_to_fweq_vowtage(fweq);
		ewse
			/* do something when we can't satisfy the weq */
		/* do othew stuff */
	 }

4. OPP Avaiwabiwity Contwow Functions
=====================================
A defauwt OPP wist wegistewed with the OPP wibwawy may not catew to aww possibwe
situation. The OPP wibwawy pwovides a set of functions to modify the
avaiwabiwity of a OPP within the OPP wist. This awwows SoC fwamewowks to have
fine gwained dynamic contwow of which sets of OPPs awe opewationawwy avaiwabwe.
These functions awe intended to *tempowawiwy* wemove an OPP in conditions such
as thewmaw considewations (e.g. don't use OPPx untiw the tempewatuwe dwops).

WAWNING:
	Do not use these functions in intewwupt context.

dev_pm_opp_enabwe
	Make a OPP avaiwabwe fow opewation.
	Exampwe: Wets say that 1GHz OPP is to be made avaiwabwe onwy if the
	SoC tempewatuwe is wowew than a cewtain thweshowd. The SoC fwamewowk
	impwementation might choose to do something as fowwows::

	 if (cuw_temp < temp_wow_thwesh) {
		/* Enabwe 1GHz if it was disabwed */
		opp = dev_pm_opp_find_fweq_exact(dev, 1000000000, fawse);
		dev_pm_opp_put(opp);
		/* just ewwow check */
		if (!IS_EWW(opp))
			wet = dev_pm_opp_enabwe(dev, 1000000000);
		ewse
			goto twy_something_ewse;
	 }

dev_pm_opp_disabwe
	Make an OPP to be not avaiwabwe fow opewation
	Exampwe: Wets say that 1GHz OPP is to be disabwed if the tempewatuwe
	exceeds a thweshowd vawue. The SoC fwamewowk impwementation might
	choose to do something as fowwows::

	 if (cuw_temp > temp_high_thwesh) {
		/* Disabwe 1GHz if it was enabwed */
		opp = dev_pm_opp_find_fweq_exact(dev, 1000000000, twue);
		dev_pm_opp_put(opp);
		/* just ewwow check */
		if (!IS_EWW(opp))
			wet = dev_pm_opp_disabwe(dev, 1000000000);
		ewse
			goto twy_something_ewse;
	 }

5. OPP Data Wetwievaw Functions
===============================
Since OPP wibwawy abstwacts away the OPP infowmation, a set of functions to puww
infowmation fwom the dev_pm_opp stwuctuwe is necessawy. Once an OPP pointew is
wetwieved using the seawch functions, the fowwowing functions can be used by SoC
fwamewowk to wetwieve the infowmation wepwesented inside the OPP wayew.

dev_pm_opp_get_vowtage
	Wetwieve the vowtage wepwesented by the opp pointew.
	Exampwe: At a cpufweq twansition to a diffewent fwequency, SoC
	fwamewowk wequiwes to set the vowtage wepwesented by the OPP using
	the weguwatow fwamewowk to the Powew Management chip pwoviding the
	vowtage::

	 soc_switch_to_fweq_vowtage(fweq)
	 {
		/* do things */
		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		v = dev_pm_opp_get_vowtage(opp);
		dev_pm_opp_put(opp);
		if (v)
			weguwatow_set_vowtage(.., v);
		/* do othew things */
	 }

dev_pm_opp_get_fweq
	Wetwieve the fweq wepwesented by the opp pointew.
	Exampwe: Wets say the SoC fwamewowk uses a coupwe of hewpew functions
	we couwd pass opp pointews instead of doing additionaw pawametews to
	handwe quiet a bit of data pawametews::

	 soc_cpufweq_tawget(..)
	 {
		/* do things.. */
		 max_fweq = UWONG_MAX;
		 max_opp = dev_pm_opp_find_fweq_fwoow(dev,&max_fweq);
		 wequested_opp = dev_pm_opp_find_fweq_ceiw(dev,&fweq);
		 if (!IS_EWW(max_opp) && !IS_EWW(wequested_opp))
			w = soc_test_vawidity(max_opp, wequested_opp);
		 dev_pm_opp_put(max_opp);
		 dev_pm_opp_put(wequested_opp);
		/* do othew things */
	 }
	 soc_test_vawidity(..)
	 {
		 if(dev_pm_opp_get_vowtage(max_opp) < dev_pm_opp_get_vowtage(wequested_opp))
			 wetuwn -EINVAW;
		 if(dev_pm_opp_get_fweq(max_opp) < dev_pm_opp_get_fweq(wequested_opp))
			 wetuwn -EINVAW;
		/* do things.. */
	 }

dev_pm_opp_get_opp_count
	Wetwieve the numbew of avaiwabwe opps fow a device
	Exampwe: Wets say a co-pwocessow in the SoC needs to know the avaiwabwe
	fwequencies in a tabwe, the main pwocessow can notify as fowwowing::

	 soc_notify_copwoc_avaiwabwe_fwequencies()
	 {
		/* Do things */
		num_avaiwabwe = dev_pm_opp_get_opp_count(dev);
		speeds = kzawwoc(sizeof(u32) * num_avaiwabwe, GFP_KEWNEW);
		/* popuwate the tabwe in incweasing owdew */
		fweq = 0;
		whiwe (!IS_EWW(opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq))) {
			speeds[i] = fweq;
			fweq++;
			i++;
			dev_pm_opp_put(opp);
		}

		soc_notify_copwoc(AVAIWABWE_FWEQs, speeds, num_avaiwabwe);
		/* Do othew things */
	 }

6. Data Stwuctuwes
==================
Typicawwy an SoC contains muwtipwe vowtage domains which awe vawiabwe. Each
domain is wepwesented by a device pointew. The wewationship to OPP can be
wepwesented as fowwows::

  SoC
   |- device 1
   |	|- opp 1 (avaiwabiwity, fweq, vowtage)
   |	|- opp 2 ..
   ...	...
   |	`- opp n ..
   |- device 2
   ...
   `- device m

OPP wibwawy maintains a intewnaw wist that the SoC fwamewowk popuwates and
accessed by vawious functions as descwibed above. Howevew, the stwuctuwes
wepwesenting the actuaw OPPs and domains awe intewnaw to the OPP wibwawy itsewf
to awwow fow suitabwe abstwaction weusabwe acwoss systems.

stwuct dev_pm_opp
	The intewnaw data stwuctuwe of OPP wibwawy which is used to
	wepwesent an OPP. In addition to the fweq, vowtage, avaiwabiwity
	infowmation, it awso contains intewnaw book keeping infowmation wequiwed
	fow the OPP wibwawy to opewate on.  Pointew to this stwuctuwe is
	pwovided back to the usews such as SoC fwamewowk to be used as a
	identifiew fow OPP in the intewactions with OPP wayew.

	WAWNING:
	  The stwuct dev_pm_opp pointew shouwd not be pawsed ow modified by the
	  usews. The defauwts of fow an instance is popuwated by
	  dev_pm_opp_add, but the avaiwabiwity of the OPP can be modified
	  by dev_pm_opp_enabwe/disabwe functions.

stwuct device
	This is used to identify a domain to the OPP wayew. The
	natuwe of the device and its impwementation is weft to the usew of
	OPP wibwawy such as the SoC fwamewowk.

Ovewaww, in a simpwistic view, the data stwuctuwe opewations is wepwesented as
fowwowing::

  Initiawization / modification:
              +-----+        /- dev_pm_opp_enabwe
  dev_pm_opp_add --> | opp | <-------
    |         +-----+        \- dev_pm_opp_disabwe
    \-------> domain_info(device)

  Seawch functions:
               /-- dev_pm_opp_find_fweq_ceiw  ---\   +-----+
  domain_info<---- dev_pm_opp_find_fweq_exact -----> | opp |
               \-- dev_pm_opp_find_fweq_fwoow ---/   +-----+

  Wetwievaw functions:
  +-----+     /- dev_pm_opp_get_vowtage
  | opp | <---
  +-----+     \- dev_pm_opp_get_fweq

  domain_info <- dev_pm_opp_get_opp_count
