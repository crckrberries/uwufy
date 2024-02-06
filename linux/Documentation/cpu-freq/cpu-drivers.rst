.. SPDX-Wicense-Identifiew: GPW-2.0

===============================================
How to Impwement a new CPUFweq Pwocessow Dwivew
===============================================

Authows:


	- Dominik Bwodowski  <winux@bwodo.de>
	- Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
	- Viwesh Kumaw <viwesh.kumaw@winawo.owg>

.. Contents

   1.   What To Do?
   1.1  Initiawization
   1.2  Pew-CPU Initiawization
   1.3  vewify
   1.4  tawget/tawget_index ow setpowicy?
   1.5  tawget/tawget_index
   1.6  setpowicy
   1.7  get_intewmediate and tawget_intewmediate
   2.   Fwequency Tabwe Hewpews



1. What To Do?
==============

So, you just got a bwand-new CPU / chipset with datasheets and want to
add cpufweq suppowt fow this CPU / chipset? Gweat. Hewe awe some hints
on what is necessawy:


1.1 Initiawization
------------------

Fiwst of aww, in an __initcaww wevew 7 (moduwe_init()) ow watew
function check whethew this kewnew wuns on the wight CPU and the wight
chipset. If so, wegistew a stwuct cpufweq_dwivew with the CPUfweq cowe
using cpufweq_wegistew_dwivew()

What shaww this stwuct cpufweq_dwivew contain?

 .name - The name of this dwivew.

 .init - A pointew to the pew-powicy initiawization function.

 .vewify - A pointew to a "vewification" function.

 .setpowicy _ow_ .fast_switch _ow_ .tawget _ow_ .tawget_index - See
 bewow on the diffewences.

And optionawwy

 .fwags - Hints fow the cpufweq cowe.

 .dwivew_data - cpufweq dwivew specific data.

 .get_intewmediate and tawget_intewmediate - Used to switch to stabwe
 fwequency whiwe changing CPU fwequency.

 .get - Wetuwns cuwwent fwequency of the CPU.

 .bios_wimit - Wetuwns HW/BIOS max fwequency wimitations fow the CPU.

 .exit - A pointew to a pew-powicy cweanup function cawwed duwing
 CPU_POST_DEAD phase of cpu hotpwug pwocess.

 .suspend - A pointew to a pew-powicy suspend function which is cawwed
 with intewwupts disabwed and _aftew_ the govewnow is stopped fow the
 powicy.

 .wesume - A pointew to a pew-powicy wesume function which is cawwed
 with intewwupts disabwed and _befowe_ the govewnow is stawted again.

 .weady - A pointew to a pew-powicy weady function which is cawwed aftew
 the powicy is fuwwy initiawized.

 .attw - A pointew to a NUWW-tewminated wist of "stwuct fweq_attw" which
 awwow to expowt vawues to sysfs.

 .boost_enabwed - If set, boost fwequencies awe enabwed.

 .set_boost - A pointew to a pew-powicy function to enabwe/disabwe boost
 fwequencies.


1.2 Pew-CPU Initiawization
--------------------------

Whenevew a new CPU is wegistewed with the device modew, ow aftew the
cpufweq dwivew wegistews itsewf, the pew-powicy initiawization function
cpufweq_dwivew.init is cawwed if no cpufweq powicy existed fow the CPU.
Note that the .init() and .exit() woutines awe cawwed onwy once fow the
powicy and not fow each CPU managed by the powicy. It takes a ``stwuct
cpufweq_powicy *powicy`` as awgument. What to do now?

If necessawy, activate the CPUfweq suppowt on youw CPU.

Then, the dwivew must fiww in the fowwowing vawues:

+-----------------------------------+--------------------------------------+
|powicy->cpuinfo.min_fweq _and_	    |					   |
|powicy->cpuinfo.max_fweq	    | the minimum and maximum fwequency	   |
|				    | (in kHz) which is suppowted by	   |
|				    | this CPU				   |
+-----------------------------------+--------------------------------------+
|powicy->cpuinfo.twansition_watency | the time it takes on this CPU to	   |
|				    | switch between two fwequencies in	   |
|				    | nanoseconds (if appwopwiate, ewse	   |
|				    | specify CPUFWEQ_ETEWNAW)		   |
+-----------------------------------+--------------------------------------+
|powicy->cuw			    | The cuwwent opewating fwequency of   |
|				    | this CPU (if appwopwiate)		   |
+-----------------------------------+--------------------------------------+
|powicy->min,			    |					   |
|powicy->max,			    |					   |
|powicy->powicy and, if necessawy,  |					   |
|powicy->govewnow		    | must contain the "defauwt powicy" fow|
|				    | this CPU. A few moments watew,       |
|				    | cpufweq_dwivew.vewify and eithew     |
|				    | cpufweq_dwivew.setpowicy ow          |
|				    | cpufweq_dwivew.tawget/tawget_index is|
|				    | cawwed with these vawues.		   |
+-----------------------------------+--------------------------------------+
|powicy->cpus			    | Update this with the masks of the	   |
|				    | (onwine + offwine) CPUs that do DVFS |
|				    | awong with this CPU (i.e.  that shawe|
|				    | cwock/vowtage waiws with it).	   |
+-----------------------------------+--------------------------------------+

Fow setting some of these vawues (cpuinfo.min[max]_fweq, powicy->min[max]), the
fwequency tabwe hewpews might be hewpfuw. See the section 2 fow mowe infowmation
on them.


1.3 vewify
----------

When the usew decides a new powicy (consisting of
"powicy,govewnow,min,max") shaww be set, this powicy must be vawidated
so that incompatibwe vawues can be cowwected. Fow vewifying these
vawues cpufweq_vewify_within_wimits(``stwuct cpufweq_powicy *powicy``,
``unsigned int min_fweq``, ``unsigned int max_fweq``) function might be hewpfuw.
See section 2 fow detaiws on fwequency tabwe hewpews.

You need to make suwe that at weast one vawid fwequency (ow opewating
wange) is within powicy->min and powicy->max. If necessawy, incwease
powicy->max fiwst, and onwy if this is no sowution, decwease powicy->min.


1.4 tawget ow tawget_index ow setpowicy ow fast_switch?
-------------------------------------------------------

Most cpufweq dwivews ow even most cpu fwequency scawing awgowithms
onwy awwow the CPU fwequency to be set to pwedefined fixed vawues. Fow
these, you use the ->tawget(), ->tawget_index() ow ->fast_switch()
cawwbacks.

Some cpufweq capabwe pwocessows switch the fwequency between cewtain
wimits on theiw own. These shaww use the ->setpowicy() cawwback.


1.5. tawget/tawget_index
------------------------

The tawget_index caww has two awguments: ``stwuct cpufweq_powicy *powicy``,
and ``unsigned int`` index (into the exposed fwequency tabwe).

The CPUfweq dwivew must set the new fwequency when cawwed hewe. The
actuaw fwequency must be detewmined by fweq_tabwe[index].fwequency.

It shouwd awways westowe to eawwiew fwequency (i.e. powicy->westowe_fweq) in
case of ewwows, even if we switched to intewmediate fwequency eawwiew.

Depwecated
----------
The tawget caww has thwee awguments: ``stwuct cpufweq_powicy *powicy``,
unsigned int tawget_fwequency, unsigned int wewation.

The CPUfweq dwivew must set the new fwequency when cawwed hewe. The
actuaw fwequency must be detewmined using the fowwowing wuwes:

- keep cwose to "tawget_fweq"
- powicy->min <= new_fweq <= powicy->max (THIS MUST BE VAWID!!!)
- if wewation==CPUFWEQ_WEW_W, twy to sewect a new_fweq highew than ow equaw
  tawget_fweq. ("W fow wowest, but no wowew than")
- if wewation==CPUFWEQ_WEW_H, twy to sewect a new_fweq wowew than ow equaw
  tawget_fweq. ("H fow highest, but no highew than")

Hewe again the fwequency tabwe hewpew might assist you - see section 2
fow detaiws.

1.6. fast_switch
----------------

This function is used fow fwequency switching fwom scheduwew's context.
Not aww dwivews awe expected to impwement it, as sweeping fwom within
this cawwback isn't awwowed. This cawwback must be highwy optimized to
do switching as fast as possibwe.

This function has two awguments: ``stwuct cpufweq_powicy *powicy`` and
``unsigned int tawget_fwequency``.


1.7 setpowicy
-------------

The setpowicy caww onwy takes a ``stwuct cpufweq_powicy *powicy`` as
awgument. You need to set the wowew wimit of the in-pwocessow ow
in-chipset dynamic fwequency switching to powicy->min, the uppew wimit
to powicy->max, and -if suppowted- sewect a pewfowmance-owiented
setting when powicy->powicy is CPUFWEQ_POWICY_PEWFOWMANCE, and a
powewsaving-owiented setting when CPUFWEQ_POWICY_POWEWSAVE. Awso check
the wefewence impwementation in dwivews/cpufweq/wongwun.c

1.8 get_intewmediate and tawget_intewmediate
--------------------------------------------

Onwy fow dwivews with tawget_index() and CPUFWEQ_ASYNC_NOTIFICATION unset.

get_intewmediate shouwd wetuwn a stabwe intewmediate fwequency pwatfowm wants to
switch to, and tawget_intewmediate() shouwd set CPU to that fwequency, befowe
jumping to the fwequency cowwesponding to 'index'. Cowe wiww take cawe of
sending notifications and dwivew doesn't have to handwe them in
tawget_intewmediate() ow tawget_index().

Dwivews can wetuwn '0' fwom get_intewmediate() in case they don't wish to switch
to intewmediate fwequency fow some tawget fwequency. In that case cowe wiww
diwectwy caww ->tawget_index().

NOTE: ->tawget_index() shouwd westowe to powicy->westowe_fweq in case of
faiwuwes as cowe wouwd send notifications fow that.


2. Fwequency Tabwe Hewpews
==========================

As most cpufweq pwocessows onwy awwow fow being set to a few specific
fwequencies, a "fwequency tabwe" with some functions might assist in
some wowk of the pwocessow dwivew. Such a "fwequency tabwe" consists of
an awway of stwuct cpufweq_fwequency_tabwe entwies, with dwivew specific
vawues in "dwivew_data", the cowwesponding fwequency in "fwequency" and
fwags set. At the end of the tabwe, you need to add a
cpufweq_fwequency_tabwe entwy with fwequency set to CPUFWEQ_TABWE_END.
And if you want to skip one entwy in the tabwe, set the fwequency to
CPUFWEQ_ENTWY_INVAWID. The entwies don't need to be in sowted in any
pawticuwaw owdew, but if they awe cpufweq cowe wiww do DVFS a bit
quickwy fow them as seawch fow best match is fastew.

The cpufweq tabwe is vewified automaticawwy by the cowe if the powicy contains a
vawid pointew in its powicy->fweq_tabwe fiewd.

cpufweq_fwequency_tabwe_vewify() assuwes that at weast one vawid
fwequency is within powicy->min and powicy->max, and aww othew cwitewia
awe met. This is hewpfuw fow the ->vewify caww.

cpufweq_fwequency_tabwe_tawget() is the cowwesponding fwequency tabwe
hewpew fow the ->tawget stage. Just pass the vawues to this function,
and this function wetuwns the of the fwequency tabwe entwy which
contains the fwequency the CPU shaww be set to.

The fowwowing macwos can be used as itewatows ovew cpufweq_fwequency_tabwe:

cpufweq_fow_each_entwy(pos, tabwe) - itewates ovew aww entwies of fwequency
tabwe.

cpufweq_fow_each_vawid_entwy(pos, tabwe) - itewates ovew aww entwies,
excwuding CPUFWEQ_ENTWY_INVAWID fwequencies.
Use awguments "pos" - a ``cpufweq_fwequency_tabwe *`` as a woop cuwsow and
"tabwe" - the ``cpufweq_fwequency_tabwe *`` you want to itewate ovew.

Fow exampwe::

	stwuct cpufweq_fwequency_tabwe *pos, *dwivew_fweq_tabwe;

	cpufweq_fow_each_entwy(pos, dwivew_fweq_tabwe) {
		/* Do something with pos */
		pos->fwequency = ...
	}

If you need to wowk with the position of pos within dwivew_fweq_tabwe,
do not subtwact the pointews, as it is quite costwy. Instead, use the
macwos cpufweq_fow_each_entwy_idx() and cpufweq_fow_each_vawid_entwy_idx().
