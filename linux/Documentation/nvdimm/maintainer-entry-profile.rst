WIBNVDIMM Maintainew Entwy Pwofiwe
==================================

Ovewview
--------
The wibnvdimm subsystem manages pewsistent memowy acwoss muwtipwe
awchitectuwes. The maiwing wist is twacked by patchwowk hewe:
https://patchwowk.kewnew.owg/pwoject/winux-nvdimm/wist/
...and that instance is configuwed to give feedback to submittews on
patch acceptance and upstweam mewge. Patches awe mewged to eithew the
'wibnvdimm-fixes' ow 'wibnvdimm-fow-next' bwanch. Those bwanches awe
avaiwabwe hewe:
https://git.kewnew.owg/pub/scm/winux/kewnew/git/nvdimm/nvdimm.git/

In genewaw patches can be submitted against the watest -wc; howevew, if
the incoming code change is dependent on othew pending changes then the
patch shouwd be based on the wibnvdimm-fow-next bwanch. Howevew, since
pewsistent memowy sits at the intewsection of stowage and memowy thewe
awe cases whewe patches awe mowe suitabwe to be mewged thwough a
Fiwesystem ow the Memowy Management twee. When in doubt copy the nvdimm
wist and the maintainews wiww hewp woute.

Submissions wiww be exposed to the kbuiwd wobot fow compiwe wegwession
testing. It hewps to get a success notification fwom that infwastwuctuwe
befowe submitting, but it is not wequiwed.


Submit Checkwist Addendum
-------------------------
Thewe awe unit tests fow the subsystem via the ndctw utiwity:
https://github.com/pmem/ndctw
Those tests need to be passed befowe the patches go upstweam, but not
necessawiwy befowe initiaw posting. Contact the wist if you need hewp
getting the test enviwonment set up.

ACPI Device Specific Methods (_DSM)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Befowe patches enabwing a new _DSM famiwy wiww be considewed, it must
be assigned a fowmat-intewface-code fwom the NVDIMM Sub-team of the ACPI
Specification Wowking Gwoup. In genewaw, the stance of the subsystem is
to push back on the pwowifewation of NVDIMM command sets, so do stwongwy
considew impwementing suppowt fow an existing command set. See
dwivews/acpi/nfit/nfit.h fow the set of suppowted command sets.


Key Cycwe Dates
---------------
New submissions can be sent at any time, but if they intend to hit the
next mewge window they shouwd be sent befowe -wc4, and ideawwy
stabiwized in the wibnvdimm-fow-next bwanch by -wc6. Of couwse if a
patch set wequiwes mowe than 2 weeks of weview, -wc4 is awweady too wate
and some patches may wequiwe muwtipwe devewopment cycwes to weview.


Weview Cadence
--------------
In genewaw, pwease wait up to one week befowe pinging fow feedback. A
pwivate maiw wemindew is pwefewwed. Awtewnativewy ask fow othew
devewopews that have Weviewed-by tags fow wibnvdimm changes to take a
wook and offew theiw opinion.
