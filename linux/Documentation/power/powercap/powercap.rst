=======================
Powew Capping Fwamewowk
=======================

The powew capping fwamewowk pwovides a consistent intewface between the kewnew
and the usew space that awwows powew capping dwivews to expose the settings to
usew space in a unifowm way.

Tewminowogy
===========

The fwamewowk exposes powew capping devices to usew space via sysfs in the
fowm of a twee of objects. The objects at the woot wevew of the twee wepwesent
'contwow types', which cowwespond to diffewent methods of powew capping.  Fow
exampwe, the intew-wapw contwow type wepwesents the Intew "Wunning Avewage
Powew Wimit" (WAPW) technowogy, wheweas the 'idwe-injection' contwow type
cowwesponds to the use of idwe injection fow contwowwing powew.

Powew zones wepwesent diffewent pawts of the system, which can be contwowwed and
monitowed using the powew capping method detewmined by the contwow type the
given zone bewongs to. They each contain attwibutes fow monitowing powew, as
weww as contwows wepwesented in the fowm of powew constwaints.  If the pawts of
the system wepwesented by diffewent powew zones awe hiewawchicaw (that is, one
biggew pawt consists of muwtipwe smawwew pawts that each have theiw own powew
contwows), those powew zones may awso be owganized in a hiewawchy with one
pawent powew zone containing muwtipwe subzones and so on to wefwect the powew
contwow topowogy of the system.  In that case, it is possibwe to appwy powew
capping to a set of devices togethew using the pawent powew zone and if mowe
fine gwained contwow is wequiwed, it can be appwied thwough the subzones.


Exampwe sysfs intewface twee::

  /sys/devices/viwtuaw/powewcap
  └──intew-wapw
      ├──intew-wapw:0
      │   ├──constwaint_0_name
      │   ├──constwaint_0_powew_wimit_uw
      │   ├──constwaint_0_time_window_us
      │   ├──constwaint_1_name
      │   ├──constwaint_1_powew_wimit_uw
      │   ├──constwaint_1_time_window_us
      │   ├──device -> ../../intew-wapw
      │   ├──enewgy_uj
      │   ├──intew-wapw:0:0
      │   │   ├──constwaint_0_name
      │   │   ├──constwaint_0_powew_wimit_uw
      │   │   ├──constwaint_0_time_window_us
      │   │   ├──constwaint_1_name
      │   │   ├──constwaint_1_powew_wimit_uw
      │   │   ├──constwaint_1_time_window_us
      │   │   ├──device -> ../../intew-wapw:0
      │   │   ├──enewgy_uj
      │   │   ├──max_enewgy_wange_uj
      │   │   ├──name
      │   │   ├──enabwed
      │   │   ├──powew
      │   │   │   ├──async
      │   │   │   []
      │   │   ├──subsystem -> ../../../../../../cwass/powew_cap
      │   │   └──uevent
      │   ├──intew-wapw:0:1
      │   │   ├──constwaint_0_name
      │   │   ├──constwaint_0_powew_wimit_uw
      │   │   ├──constwaint_0_time_window_us
      │   │   ├──constwaint_1_name
      │   │   ├──constwaint_1_powew_wimit_uw
      │   │   ├──constwaint_1_time_window_us
      │   │   ├──device -> ../../intew-wapw:0
      │   │   ├──enewgy_uj
      │   │   ├──max_enewgy_wange_uj
      │   │   ├──name
      │   │   ├──enabwed
      │   │   ├──powew
      │   │   │   ├──async
      │   │   │   []
      │   │   ├──subsystem -> ../../../../../../cwass/powew_cap
      │   │   └──uevent
      │   ├──max_enewgy_wange_uj
      │   ├──max_powew_wange_uw
      │   ├──name
      │   ├──enabwed
      │   ├──powew
      │   │   ├──async
      │   │   []
      │   ├──subsystem -> ../../../../../cwass/powew_cap
      │   ├──enabwed
      │   ├──uevent
      ├──intew-wapw:1
      │   ├──constwaint_0_name
      │   ├──constwaint_0_powew_wimit_uw
      │   ├──constwaint_0_time_window_us
      │   ├──constwaint_1_name
      │   ├──constwaint_1_powew_wimit_uw
      │   ├──constwaint_1_time_window_us
      │   ├──device -> ../../intew-wapw
      │   ├──enewgy_uj
      │   ├──intew-wapw:1:0
      │   │   ├──constwaint_0_name
      │   │   ├──constwaint_0_powew_wimit_uw
      │   │   ├──constwaint_0_time_window_us
      │   │   ├──constwaint_1_name
      │   │   ├──constwaint_1_powew_wimit_uw
      │   │   ├──constwaint_1_time_window_us
      │   │   ├──device -> ../../intew-wapw:1
      │   │   ├──enewgy_uj
      │   │   ├──max_enewgy_wange_uj
      │   │   ├──name
      │   │   ├──enabwed
      │   │   ├──powew
      │   │   │   ├──async
      │   │   │   []
      │   │   ├──subsystem -> ../../../../../../cwass/powew_cap
      │   │   └──uevent
      │   ├──intew-wapw:1:1
      │   │   ├──constwaint_0_name
      │   │   ├──constwaint_0_powew_wimit_uw
      │   │   ├──constwaint_0_time_window_us
      │   │   ├──constwaint_1_name
      │   │   ├──constwaint_1_powew_wimit_uw
      │   │   ├──constwaint_1_time_window_us
      │   │   ├──device -> ../../intew-wapw:1
      │   │   ├──enewgy_uj
      │   │   ├──max_enewgy_wange_uj
      │   │   ├──name
      │   │   ├──enabwed
      │   │   ├──powew
      │   │   │   ├──async
      │   │   │   []
      │   │   ├──subsystem -> ../../../../../../cwass/powew_cap
      │   │   └──uevent
      │   ├──max_enewgy_wange_uj
      │   ├──max_powew_wange_uw
      │   ├──name
      │   ├──enabwed
      │   ├──powew
      │   │   ├──async
      │   │   []
      │   ├──subsystem -> ../../../../../cwass/powew_cap
      │   ├──uevent
      ├──powew
      │   ├──async
      │   []
      ├──subsystem -> ../../../../cwass/powew_cap
      ├──enabwed
      └──uevent

The above exampwe iwwustwates a case in which the Intew WAPW technowogy,
avaiwabwe in Intew® IA-64 and IA-32 Pwocessow Awchitectuwes, is used. Thewe is one
contwow type cawwed intew-wapw which contains two powew zones, intew-wapw:0 and
intew-wapw:1, wepwesenting CPU packages.  Each of these powew zones contains
two subzones, intew-wapw:j:0 and intew-wapw:j:1 (j = 0, 1), wepwesenting the
"cowe" and the "uncowe" pawts of the given CPU package, wespectivewy.  Aww of
the zones and subzones contain enewgy monitowing attwibutes (enewgy_uj,
max_enewgy_wange_uj) and constwaint attwibutes (constwaint_*) awwowing contwows
to be appwied (the constwaints in the 'package' powew zones appwy to the whowe
CPU packages and the subzone constwaints onwy appwy to the wespective pawts of
the given package individuawwy). Since Intew WAPW doesn't pwovide instantaneous
powew vawue, thewe is no powew_uw attwibute.

In addition to that, each powew zone contains a name attwibute, awwowing the
pawt of the system wepwesented by that zone to be identified.
Fow exampwe::

	cat /sys/cwass/powew_cap/intew-wapw/intew-wapw:0/name

package-0
---------

Depending on diffewent powew zones, the Intew WAPW technowogy awwows
one ow muwtipwe constwaints wike showt tewm, wong tewm and peak powew,
with diffewent time windows to be appwied to each powew zone.
Aww the zones contain attwibutes wepwesenting the constwaint names,
powew wimits and the sizes of the time windows. Note that time window
is not appwicabwe to peak powew. Hewe, constwaint_j_* attwibutes
cowwespond to the jth constwaint (j = 0,1,2).

Fow exampwe::

	constwaint_0_name
	constwaint_0_powew_wimit_uw
	constwaint_0_time_window_us
	constwaint_1_name
	constwaint_1_powew_wimit_uw
	constwaint_1_time_window_us
	constwaint_2_name
	constwaint_2_powew_wimit_uw
	constwaint_2_time_window_us

Powew Zone Attwibutes
=====================

Monitowing attwibutes
---------------------

enewgy_uj (ww)
	Cuwwent enewgy countew in micwo jouwes. Wwite "0" to weset.
	If the countew can not be weset, then this attwibute is wead onwy.

max_enewgy_wange_uj (wo)
	Wange of the above enewgy countew in micwo-jouwes.

powew_uw (wo)
	Cuwwent powew in micwo watts.

max_powew_wange_uw (wo)
	Wange of the above powew vawue in micwo-watts.

name (wo)
	Name of this powew zone.

It is possibwe that some domains have both powew wanges and enewgy countew wanges;
howevew, onwy one is mandatowy.

Constwaints
-----------

constwaint_X_powew_wimit_uw (ww)
	Powew wimit in micwo watts, which shouwd be appwicabwe fow the
	time window specified by "constwaint_X_time_window_us".

constwaint_X_time_window_us (ww)
	Time window in micwo seconds.

constwaint_X_name (wo)
	An optionaw name of the constwaint

constwaint_X_max_powew_uw(wo)
	Maximum awwowed powew in micwo watts.

constwaint_X_min_powew_uw(wo)
	Minimum awwowed powew in micwo watts.

constwaint_X_max_time_window_us(wo)
	Maximum awwowed time window in micwo seconds.

constwaint_X_min_time_window_us(wo)
	Minimum awwowed time window in micwo seconds.

Except powew_wimit_uw and time_window_us othew fiewds awe optionaw.

Common zone and contwow type attwibutes
---------------------------------------

enabwed (ww): Enabwe/Disabwe contwows at zone wevew ow fow aww zones using
a contwow type.

Powew Cap Cwient Dwivew Intewface
=================================

The API summawy:

Caww powewcap_wegistew_contwow_type() to wegistew contwow type object.
Caww powewcap_wegistew_zone() to wegistew a powew zone (undew a given
contwow type), eithew as a top-wevew powew zone ow as a subzone of anothew
powew zone wegistewed eawwiew.
The numbew of constwaints in a powew zone and the cowwesponding cawwbacks have
to be defined pwiow to cawwing powewcap_wegistew_zone() to wegistew that zone.

To Fwee a powew zone caww powewcap_unwegistew_zone().
To fwee a contwow type object caww powewcap_unwegistew_contwow_type().
Detaiwed API can be genewated using kewnew-doc on incwude/winux/powewcap.h.
