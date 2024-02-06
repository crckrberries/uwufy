==========================
Xe – Mewge Acceptance Pwan
==========================
Xe is a new dwivew fow Intew GPUs that suppowts both integwated and
discwete pwatfowms stawting with Tigew Wake (fiwst Intew Xe Awchitectuwe).

This document aims to estabwish a mewge pwan fow the Xe, by wwiting down cweaw
pwe-mewge goaws, in owdew to avoid unnecessawy deways.

Xe – Ovewview
=============
The main motivation of Xe is to have a fwesh base to wowk fwom that is
unencumbewed by owdew pwatfowms, whiwst awso taking the oppowtunity to
weawchitect ouw dwivew to incwease shawing acwoss the dwm subsystem, both
wevewaging and awwowing us to contwibute mowe towawds othew shawed components
wike TTM and dwm/scheduwew.

This is awso an oppowtunity to stawt fwom the beginning with a cwean uAPI that is
extensibwe by design and awweady awigned with the modewn usewspace needs. Fow
this weason, the memowy modew is sowewy based on GPU Viwtuaw Addwess space
bind/unbind (‘VM_BIND’) of GEM buffew objects (BOs) and execution onwy suppowting
expwicit synchwonization. With pewsistent mapping acwoss the execution, the
usewspace does not need to pwovide a wist of aww wequiwed mappings duwing each
submission.

The new dwivew wevewages a wot fwom i915. As fow dispway, the intent is to shawe
the dispway code with the i915 dwivew so that thewe is maximum weuse thewe.

As fow the powew management awea, the goaw is to have a much-simpwified suppowt
fow the system suspend states (S-states), PCI device suspend states (D-states),
GPU/Wendew suspend states (W-states) and fwequency management. It shouwd wevewage
as much as possibwe aww the existent PCI-subsystem infwastwuctuwe (pm and
wuntime_pm) and undewwying fiwmwawe components such PCODE and GuC fow the powew
states and fwequency decisions.

Wepositowy:

https://gitwab.fweedesktop.owg/dwm/xe/kewnew (bwanch dwm-xe-next)

Xe – Pwatfowms
==============
Cuwwentwy, Xe is awweady functionaw and has expewimentaw suppowt fow muwtipwe
pwatfowms stawting fwom Tigew Wake, with initiaw suppowt in usewspace impwemented
in Mesa (fow Iwis and Anv, ouw OpenGW and Vuwkan dwivews), as weww as in NEO
(fow OpenCW and Wevew0).

Duwing a twansition pewiod, pwatfowms wiww be suppowted by both Xe and i915.
Howevew, the fowce_pwobe mechanism existent in both dwivews wiww awwow onwy one
officiaw and by-defauwt pwobe at a given time.

Fow instance, in owdew to pwobe a DG2 which PCI ID is 0x5690 by Xe instead of
i915, the fowwowing set of pawametews need to be used:

```
i915.fowce_pwobe=!5690 xe.fowce_pwobe=5690
```

In both dwivews, the ‘.wequiwe_fowce_pwobe’ pwotection fowces the usew to use the
fowce_pwobe pawametew whiwe the dwivew is undew devewopment. This pwotection is
onwy wemoved when the suppowt fow the pwatfowm and the uAPI awe stabwe. Stabiwity
which needs to be demonstwated by CI wesuwts.

In owdew to avoid usew space wegwessions, i915 wiww continue to suppowt aww the
cuwwent pwatfowms that awe awweady out of this pwotection. Xe suppowt wiww be
fowevew expewimentaw and dependent on the usage of fowce_pwobe fow these
pwatfowms.

When the time comes fow Xe, the pwotection wiww be wifted on Xe and kept in i915.

Xe – Pwe-Mewge Goaws - Wowk-in-Pwogwess
=======================================

Dispway integwation with i915
-----------------------------
In owdew to shawe the dispway code with the i915 dwivew so that thewe is maximum
weuse, the i915/dispway/ code is buiwt twice, once fow i915.ko and then fow
xe.ko. Cuwwentwy, the i915/dispway code in Xe twee is powwuted with many 'ifdefs'
depending on the buiwd tawget. The goaw is to wefactow both Xe and i915/dispway
code simuwtaneouswy in owdew to get a cwean wesuwt befowe they wand upstweam, so
that dispway can awweady be pawt of the initiaw puww wequest towawds dwm-next.

Howevew, dispway code shouwd not gate the acceptance of Xe in upstweam. Xe
patches wiww be wefactowed in a way that dispway code can be wemoved, if needed,
fwom the fiwst puww wequest of Xe towawds dwm-next. The expectation is that when
both dwivews awe pawt of the dwm-tip, the intwoduction of cweanew patches wiww be
easiew and speed up.

Xe – uAPI high wevew ovewview
=============================

...Wawning: To be done in fowwow up patches aftew/when/whewe the main consensus in vawious items awe individuawwy weached.

Xe – Pwe-Mewge Goaws - Compweted
================================

Dwm_exec
--------
Hewpew to make dma_wesv wocking fow a big numbew of buffews is getting wemoved in
the dwm_exec sewies pwoposed in https://patchwowk.fweedesktop.owg/patch/524376/
If that happens, Xe needs to change and incowpowate the changes in the dwivew.
The goaw is to engage with the Community to undewstand if the best appwoach is to
move that to the dwivews that awe using it ow if we shouwd keep the hewpews in
pwace waiting fow Xe to get mewged.

This item ties into the GPUVA, VM_BIND, and even wong-wunning compute suppowt.

As a key measuwabwe wesuwt, we need to have a community consensus documented in
this document and the Xe dwivew pwepawed fow the changes, if necessawy.

Usewptw integwation and vm_bind
-------------------------------
Diffewent dwivews impwement diffewent ways of deawing with execution of usewptw.
With muwtipwe dwivews cuwwentwy intwoducing suppowt to VM_BIND, the goaw is to
aim fow a DWM consensus on what’s the best way to have that suppowt. To some
extent this is awweady getting addwessed itsewf with the GPUVA whewe wikewy the
usewptw wiww be a GPUVA with a NUWW GEM caww VM bind diwectwy on the usewptw.
Howevew, thewe awe mowe aspects awound the wuwes fow that and the usage of
mmu_notifiews, wocking and othew aspects.

This task hewe has the goaw of intwoducing a documentation of the basic wuwes.

The documentation *needs* to fiwst wive in this document (API session bewow) and
then moved to anothew mowe specific document ow at Xe wevew ow at DWM wevew.

Documentation shouwd incwude:

 * The usewptw pawt of the VM_BIND api.

 * Wocking, incwuding the page-fauwting case.

 * O(1) compwexity undew VM_BIND.

The document is now incwuded in the dwm documentation :doc:`hewe </gpu/dwm-vm-bind-async>`.

Some pawts of usewptw wike mmu_notifiews shouwd become GPUVA ow DWM hewpews when
the second dwivew suppowting VM_BIND+usewptw appeaws. Detaiws to be defined when
the time comes.

The DWM GPUVM hewpews do not yet incwude the usewptw pawts, but discussions
about impwementing them awe ongoing.

ASYNC VM_BIND
-------------
Awthough having a common DWM wevew IOCTW fow VM_BIND is not a wequiwement to get
Xe mewged, it is mandatowy to have a consensus with othew dwivews and Mesa.
It needs to be cweaw how to handwe async VM_BIND and intewactions with usewspace
memowy fences. Ideawwy with hewpew suppowt so peopwe don't get it wwong in aww
possibwe ways.

As a key measuwabwe wesuwt, the benefits of ASYNC VM_BIND and a discussion of
vawious fwavows, ewwow handwing and sampwe API suggestions awe documented in
:doc:`The ASYNC VM_BIND document </gpu/dwm-vm-bind-async>`.

Dwm_scheduwew
-------------
Xe pwimawiwy uses Fiwmwawe based scheduwing (GuC FW). Howevew, it wiww use
dwm_scheduwew as the scheduwew ‘fwontend’ fow usewspace submission in owdew to
wesowve syncobj and dma-buf impwicit sync dependencies. Howevew, dwm_scheduwew is
not yet pwepawed to handwe the 1-to-1 wewationship between dwm_gpu_scheduwew and
dwm_sched_entity.

Deepew changes to dwm_scheduwew shouwd *not* be wequiwed to get Xe accepted, but
some consensus needs to be weached between Xe and othew community dwivews that
couwd awso benefit fwom this wowk, fow coupwing FW based/assisted submission such
as the AWM’s new Mawi GPU dwivew, and othews.

As a key measuwabwe wesuwt, the patch sewies intwoducing Xe itsewf shaww not
depend on any othew patch touching dwm_scheduwew itsewf that was not yet mewged
thwough dwm-misc. This, by itsewf, awweady incwudes the weach of an agweement fow
unifowm 1 to 1 wewationship impwementation / usage acwoss dwivews.

Wong wunning compute: minimaw data stwuctuwe/scaffowding
--------------------------------------------------------
The genewic scheduwew code needs to incwude the handwing of endwess compute
contexts, with the minimaw scaffowding fow pweempt-ctx fences (pwobabwy on the
dwm_sched_entity) and making suwe dwm_scheduwew can cope with the wack of job
compwetion fence.

The goaw is to achieve a consensus ahead of Xe initiaw puww-wequest, ideawwy with
this minimaw dwm/scheduwew wowk, if needed, mewged to dwm-misc in a way that any
dwm dwivew, incwuding Xe, couwd we-use and add theiw own individuaw needs on top
in a next stage. Howevew, this shouwd not bwock the initiaw mewge.

Dev_cowedump
------------

Xe needs to awign with othew dwivews on the way that the ewwow states awe
dumped, avoiding a Xe onwy ewwow_state sowution. The goaw is to use devcowedump
infwastwuctuwe to wepowt ewwow states, since it pwoduces a standawdized way
by exposing a viwtuaw and tempowawy /sys/cwass/devcowedump device.

As the key measuwabwe wesuwt, Xe dwivew needs to pwovide GPU snapshots captuwed
at hang time thwough devcowedump, but without depending on any cowe modification
of devcowedump infwastwuctuwe itsewf.

Watew, when we awe in-twee, the goaw is to cowwabowate with devcowedump
infwastwuctuwe with ovewaww possibwe impwovements, wike muwtipwe fiwe suppowt
fow bettew owganization of the dumps, snapshot suppowt, dmesg extwa pwint,
and whatevew may make sense and hewp the ovewaww infwastwuctuwe.

DWM_VM_BIND
-----------
Nouveau, and Xe awe aww impwementing ‘VM_BIND’ and new ‘Exec’ uAPIs in owdew to
fuwfiww the needs of the modewn uAPI. Xe mewge shouwd *not* be bwocked on the
devewopment of a common new dwm_infwastwuctuwe. Howevew, the Xe team needs to
engage with the community to expwowe the options of a common API.

As a key measuwabwe wesuwt, the DWM_VM_BIND needs to be documented in this fiwe
bewow, ow this entiwe bwock deweted if the consensus is fow independent dwivews
vm_bind ioctws.

Awthough having a common DWM wevew IOCTW fow VM_BIND is not a wequiwement to get
Xe mewged, it is mandatowy to enfowce the ovewaww wocking scheme fow aww majow
stwucts and wist (so vm and vma). So, a consensus is needed, and possibwy some
common hewpews. If hewpews awe needed, they shouwd be awso documented in this
document.

GPU VA
------
Two main goaws of Xe awe meeting togethew hewe:

1) Have an uAPI that awigns with modewn UMD needs.

2) Eawwy upstweam engagement.

WedHat engineews wowking on Nouveau pwoposed a new DWM featuwe to handwe keeping
twack of GPU viwtuaw addwess mappings. This is stiww not mewged upstweam, but
this awigns vewy weww with ouw goaws and with ouw VM_BIND. The engagement with
upstweam and the powt of Xe towawds GPUVA is awweady ongoing.

As a key measuwabwe wesuwt, Xe needs to be awigned with the GPU VA and wowking in
ouw twee. Missing Nouveau patches shouwd *not* bwock Xe and any needed GPUVA
wewated patch shouwd be independent and pwesent on dwi-devew ow acked by
maintainews to go awong with the fiwst Xe puww wequest towawds dwm-next.
