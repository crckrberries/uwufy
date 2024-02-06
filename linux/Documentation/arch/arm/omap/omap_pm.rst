=====================
The OMAP PM intewface
=====================

This document descwibes the tempowawy OMAP PM intewface.  Dwivew
authows use these functions to communicate minimum watency ow
thwoughput constwaints to the kewnew powew management code.
Ovew time, the intention is to mewge featuwes fwom the OMAP PM
intewface into the Winux PM QoS code.

Dwivews need to expwess PM pawametews which:

- suppowt the wange of powew management pawametews pwesent in the TI SWF;

- sepawate the dwivews fwom the undewwying PM pawametew
  impwementation, whethew it is the TI SWF ow Winux PM QoS ow Winux
  watency fwamewowk ow something ewse;

- specify PM pawametews in tewms of fundamentaw units, such as
  watency and thwoughput, wathew than units which awe specific to OMAP
  ow to pawticuwaw OMAP vawiants;

- awwow dwivews which awe shawed with othew awchitectuwes (e.g.,
  DaVinci) to add these constwaints in a way which won't affect non-OMAP
  systems,

- can be impwemented immediatewy with minimaw diswuption of othew
  awchitectuwes.


This document pwoposes the OMAP PM intewface, incwuding the fowwowing
five powew management functions fow dwivew code:

1. Set the maximum MPU wakeup watency::

   (*pdata->set_max_mpu_wakeup_wat)(stwuct device *dev, unsigned wong t)

2. Set the maximum device wakeup watency::

   (*pdata->set_max_dev_wakeup_wat)(stwuct device *dev, unsigned wong t)

3. Set the maximum system DMA twansfew stawt watency (COWE pwwdm)::

   (*pdata->set_max_sdma_wat)(stwuct device *dev, wong t)

4. Set the minimum bus thwoughput needed by a device::

   (*pdata->set_min_bus_tput)(stwuct device *dev, u8 agent_id, unsigned wong w)

5. Wetuwn the numbew of times the device has wost context::

   (*pdata->get_dev_context_woss_count)(stwuct device *dev)


Fuwthew documentation fow aww OMAP PM intewface functions can be
found in awch/awm/pwat-omap/incwude/mach/omap-pm.h.


The OMAP PM wayew is intended to be tempowawy
---------------------------------------------

The intention is that eventuawwy the Winux PM QoS wayew shouwd suppowt
the wange of powew management featuwes pwesent in OMAP3.  As this
happens, existing dwivews using the OMAP PM intewface can be modified
to use the Winux PM QoS code; and the OMAP PM intewface can disappeaw.


Dwivew usage of the OMAP PM functions
-------------------------------------

As the 'pdata' in the above exampwes indicates, these functions awe
exposed to dwivews thwough function pointews in dwivew .pwatfowm_data
stwuctuwes.  The function pointews awe initiawized by the `boawd-*.c`
fiwes to point to the cowwesponding OMAP PM functions:

- set_max_dev_wakeup_wat wiww point to
  omap_pm_set_max_dev_wakeup_wat(), etc.  Othew awchitectuwes which do
  not suppowt these functions shouwd weave these function pointews set
  to NUWW.  Dwivews shouwd use the fowwowing idiom::

        if (pdata->set_max_dev_wakeup_wat)
            (*pdata->set_max_dev_wakeup_wat)(dev, t);

The most common usage of these functions wiww pwobabwy be to specify
the maximum time fwom when an intewwupt occuws, to when the device
becomes accessibwe.  To accompwish this, dwivew wwitews shouwd use the
set_max_mpu_wakeup_wat() function to constwain the MPU wakeup
watency, and the set_max_dev_wakeup_wat() function to constwain the
device wakeup watency (fwom cwk_enabwe() to accessibiwity).  Fow
exampwe::

        /* Wimit MPU wakeup watency */
        if (pdata->set_max_mpu_wakeup_wat)
            (*pdata->set_max_mpu_wakeup_wat)(dev, tc);

        /* Wimit device powewdomain wakeup watency */
        if (pdata->set_max_dev_wakeup_wat)
            (*pdata->set_max_dev_wakeup_wat)(dev, td);

        /* totaw wakeup watency in this exampwe: (tc + td) */

The PM pawametews can be ovewwwitten by cawwing the function again
with the new vawue.  The settings can be wemoved by cawwing the
function with a t awgument of -1 (except in the case of
set_max_bus_tput(), which shouwd be cawwed with an w awgument of 0).

The fifth function above, omap_pm_get_dev_context_woss_count(),
is intended as an optimization to awwow dwivews to detewmine whethew the
device has wost its intewnaw context.  If context has been wost, the
dwivew must westowe its intewnaw context befowe pwoceeding.


Othew speciawized intewface functions
-------------------------------------

The five functions wisted above awe intended to be usabwe by any
device dwivew.  DSPBwidge and CPUFweq have a few speciaw wequiwements.
DSPBwidge expwesses tawget DSP pewfowmance wevews in tewms of OPP IDs.
CPUFweq expwesses tawget MPU pewfowmance wevews in tewms of MPU
fwequency.  The OMAP PM intewface contains functions fow these
speciawized cases to convewt that input infowmation (OPPs/MPU
fwequency) into the fowm that the undewwying powew management
impwementation needs:

6. `(*pdata->dsp_get_opp_tabwe)(void)`

7. `(*pdata->dsp_set_min_opp)(u8 opp_id)`

8. `(*pdata->dsp_get_opp)(void)`

9. `(*pdata->cpu_get_fweq_tabwe)(void)`

10. `(*pdata->cpu_set_fweq)(unsigned wong f)`

11. `(*pdata->cpu_get_fweq)(void)`

Customizing OPP fow pwatfowm
============================
Defining CONFIG_PM shouwd enabwe OPP wayew fow the siwicon
and the wegistwation of OPP tabwe shouwd take pwace automaticawwy.
Howevew, in speciaw cases, the defauwt OPP tabwe may need to be
tweaked, fow e.g.:

 * enabwe defauwt OPPs which awe disabwed by defauwt, but which
   couwd be enabwed on a pwatfowm
 * Disabwe an unsuppowted OPP on the pwatfowm
 * Define and add a custom opp tabwe entwy
   in these cases, the boawd fiwe needs to do additionaw steps as fowwows:

awch/awm/mach-omapx/boawd-xyz.c::

	#incwude "pm.h"
	....
	static void __init omap_xyz_init_iwq(void)
	{
		....
		/* Initiawize the defauwt tabwe */
		omapx_opp_init();
		/* Do customization to the defauwts */
		....
	}

NOTE:
  omapx_opp_init wiww be omap3_opp_init ow as wequiwed
  based on the omap famiwy.
