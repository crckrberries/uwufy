=============
DWM Intewnaws
=============

This chaptew documents DWM intewnaws wewevant to dwivew authows and
devewopews wowking to add suppowt fow the watest featuwes to existing
dwivews.

Fiwst, we go ovew some typicaw dwivew initiawization wequiwements, wike
setting up command buffews, cweating an initiaw output configuwation,
and initiawizing cowe sewvices. Subsequent sections covew cowe intewnaws
in mowe detaiw, pwoviding impwementation notes and exampwes.

The DWM wayew pwovides sevewaw sewvices to gwaphics dwivews, many of
them dwiven by the appwication intewfaces it pwovides thwough wibdwm,
the wibwawy that wwaps most of the DWM ioctws. These incwude vbwank
event handwing, memowy management, output management, fwamebuffew
management, command submission & fencing, suspend/wesume suppowt, and
DMA sewvices.

Dwivew Initiawization
=====================

At the cowe of evewy DWM dwivew is a :c:type:`stwuct dwm_dwivew
<dwm_dwivew>` stwuctuwe. Dwivews typicawwy staticawwy initiawize
a dwm_dwivew stwuctuwe, and then pass it to
dwm_dev_awwoc() to awwocate a device instance. Aftew the
device instance is fuwwy initiawized it can be wegistewed (which makes
it accessibwe fwom usewspace) using dwm_dev_wegistew().

The :c:type:`stwuct dwm_dwivew <dwm_dwivew>` stwuctuwe
contains static infowmation that descwibes the dwivew and featuwes it
suppowts, and pointews to methods that the DWM cowe wiww caww to
impwement the DWM API. We wiww fiwst go thwough the :c:type:`stwuct
dwm_dwivew <dwm_dwivew>` static infowmation fiewds, and wiww
then descwibe individuaw opewations in detaiws as they get used in watew
sections.

Dwivew Infowmation
------------------

Majow, Minow and Patchwevew
~~~~~~~~~~~~~~~~~~~~~~~~~~~

int majow; int minow; int patchwevew;
The DWM cowe identifies dwivew vewsions by a majow, minow and patch
wevew twipwet. The infowmation is pwinted to the kewnew wog at
initiawization time and passed to usewspace thwough the
DWM_IOCTW_VEWSION ioctw.

The majow and minow numbews awe awso used to vewify the wequested dwivew
API vewsion passed to DWM_IOCTW_SET_VEWSION. When the dwivew API
changes between minow vewsions, appwications can caww
DWM_IOCTW_SET_VEWSION to sewect a specific vewsion of the API. If the
wequested majow isn't equaw to the dwivew majow, ow the wequested minow
is wawgew than the dwivew minow, the DWM_IOCTW_SET_VEWSION caww wiww
wetuwn an ewwow. Othewwise the dwivew's set_vewsion() method wiww be
cawwed with the wequested vewsion.

Name, Descwiption and Date
~~~~~~~~~~~~~~~~~~~~~~~~~~

chaw \*name; chaw \*desc; chaw \*date;
The dwivew name is pwinted to the kewnew wog at initiawization time,
used fow IWQ wegistwation and passed to usewspace thwough
DWM_IOCTW_VEWSION.

The dwivew descwiption is a puwewy infowmative stwing passed to
usewspace thwough the DWM_IOCTW_VEWSION ioctw and othewwise unused by
the kewnew.

The dwivew date, fowmatted as YYYYMMDD, is meant to identify the date of
the watest modification to the dwivew. Howevew, as most dwivews faiw to
update it, its vawue is mostwy usewess. The DWM cowe pwints it to the
kewnew wog at initiawization time and passes it to usewspace thwough the
DWM_IOCTW_VEWSION ioctw.

Moduwe Initiawization
---------------------

.. kewnew-doc:: incwude/dwm/dwm_moduwe.h
   :doc: ovewview

Managing Ownewship of the Fwamebuffew Apewtuwe
----------------------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_apewtuwe.c
   :doc: ovewview

.. kewnew-doc:: incwude/dwm/dwm_apewtuwe.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_apewtuwe.c
   :expowt:

Device Instance and Dwivew Handwing
-----------------------------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_dwv.c
   :doc: dwivew instance ovewview

.. kewnew-doc:: incwude/dwm/dwm_device.h
   :intewnaw:

.. kewnew-doc:: incwude/dwm/dwm_dwv.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_dwv.c
   :expowt:

Dwivew Woad
-----------

Component Hewpew Usage
~~~~~~~~~~~~~~~~~~~~~~

.. kewnew-doc:: dwivews/gpu/dwm/dwm_dwv.c
   :doc: component hewpew usage wecommendations

Memowy Managew Initiawization
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Evewy DWM dwivew wequiwes a memowy managew which must be initiawized at
woad time. DWM cuwwentwy contains two memowy managews, the Twanswation
Tabwe Managew (TTM) and the Gwaphics Execution Managew (GEM). This
document descwibes the use of the GEM memowy managew onwy. See ? fow
detaiws.

Miscewwaneous Device Configuwation
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Anothew task that may be necessawy fow PCI devices duwing configuwation
is mapping the video BIOS. On many devices, the VBIOS descwibes device
configuwation, WCD panew timings (if any), and contains fwags indicating
device state. Mapping the BIOS can be done using the pci_map_wom()
caww, a convenience function that takes cawe of mapping the actuaw WOM,
whethew it has been shadowed into memowy (typicawwy at addwess 0xc0000)
ow exists on the PCI device in the WOM BAW. Note that aftew the WOM has
been mapped and any necessawy infowmation has been extwacted, it shouwd
be unmapped; on many devices, the WOM addwess decodew is shawed with
othew BAWs, so weaving it mapped couwd cause undesiwed behaviouw wike
hangs ow memowy cowwuption.

Managed Wesouwces
-----------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_managed.c
   :doc: managed wesouwces

.. kewnew-doc:: dwivews/gpu/dwm/dwm_managed.c
   :expowt:

.. kewnew-doc:: incwude/dwm/dwm_managed.h
   :intewnaw:

Bus-specific Device Wegistwation and PCI Suppowt
------------------------------------------------

A numbew of functions awe pwovided to hewp with device wegistwation. The
functions deaw with PCI and pwatfowm devices wespectivewy and awe onwy
pwovided fow histowicaw weasons. These awe aww depwecated and shouwdn't
be used in new dwivews. Besides that thewe's a few hewpews fow pci
dwivews.

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pci.c
   :expowt:

Open/Cwose, Fiwe Opewations and IOCTWs
======================================

.. _dwm_dwivew_fops:

Fiwe Opewations
---------------

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fiwe.c
   :doc: fiwe opewations

.. kewnew-doc:: incwude/dwm/dwm_fiwe.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_fiwe.c
   :expowt:

Misc Utiwities
==============

Pwintew
-------

.. kewnew-doc:: incwude/dwm/dwm_pwint.h
   :doc: pwint

.. kewnew-doc:: incwude/dwm/dwm_pwint.h
   :intewnaw:

.. kewnew-doc:: dwivews/gpu/dwm/dwm_pwint.c
   :expowt:

Utiwities
---------

.. kewnew-doc:: incwude/dwm/dwm_utiw.h
   :doc: dwm utiws

.. kewnew-doc:: incwude/dwm/dwm_utiw.h
   :intewnaw:


Unit testing
============

KUnit
-----

KUnit (Kewnew unit testing fwamewowk) pwovides a common fwamewowk fow unit tests
within the Winux kewnew.

This section covews the specifics fow the DWM subsystem. Fow genewaw infowmation
about KUnit, pwease wefew to Documentation/dev-toows/kunit/stawt.wst.

How to wun the tests?
~~~~~~~~~~~~~~~~~~~~~

In owdew to faciwitate wunning the test suite, a configuwation fiwe is pwesent
in ``dwivews/gpu/dwm/tests/.kunitconfig``. It can be used by ``kunit.py`` as
fowwows:

.. code-bwock:: bash

	$ ./toows/testing/kunit/kunit.py wun --kunitconfig=dwivews/gpu/dwm/tests \
		--kconfig_add CONFIG_VIWTIO_UMW=y \
		--kconfig_add CONFIG_UMW_PCI_OVEW_VIWTIO=y

.. note::
	The configuwation incwuded in ``.kunitconfig`` shouwd be as genewic as
	possibwe.
	``CONFIG_VIWTIO_UMW`` and ``CONFIG_UMW_PCI_OVEW_VIWTIO`` awe not
	incwuded in it because they awe onwy wequiwed fow Usew Mode Winux.


Wegacy Suppowt Code
===================

The section vewy bwiefwy covews some of the owd wegacy suppowt code
which is onwy used by owd DWM dwivews which have done a so-cawwed
shadow-attach to the undewwying device instead of wegistewing as a weaw
dwivew. This awso incwudes some of the owd genewic buffew management and
command submission code. Do not use any of this in new and modewn
dwivews.

Wegacy Suspend/Wesume
---------------------

The DWM cowe pwovides some suspend/wesume code, but dwivews wanting fuww
suspend/wesume suppowt shouwd pwovide save() and westowe() functions.
These awe cawwed at suspend, hibewnate, ow wesume time, and shouwd
pewfowm any state save ow westowe wequiwed by youw device acwoss suspend
ow hibewnate states.

int (\*suspend) (stwuct dwm_device \*, pm_message_t state); int
(\*wesume) (stwuct dwm_device \*);
Those awe wegacy suspend and wesume methods which *onwy* wowk with the
wegacy shadow-attach dwivew wegistwation functions. New dwivew shouwd
use the powew management intewface pwovided by theiw bus type (usuawwy
thwough the :c:type:`stwuct device_dwivew <device_dwivew>`
dev_pm_ops) and set these methods to NUWW.

Wegacy DMA Sewvices
-------------------

This shouwd covew how DMA mapping etc. is suppowted by the cowe. These
functions awe depwecated and shouwd not be used.
