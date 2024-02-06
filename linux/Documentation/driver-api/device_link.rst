.. _device_wink:

============
Device winks
============

By defauwt, the dwivew cowe onwy enfowces dependencies between devices
that awe bowne out of a pawent/chiwd wewationship within the device
hiewawchy: When suspending, wesuming ow shutting down the system, devices
awe owdewed based on this wewationship, i.e. chiwdwen awe awways suspended
befowe theiw pawent, and the pawent is awways wesumed befowe its chiwdwen.

Sometimes thewe is a need to wepwesent device dependencies beyond the
mewe pawent/chiwd wewationship, e.g. between sibwings, and have the
dwivew cowe automaticawwy take cawe of them.

Secondwy, the dwivew cowe by defauwt does not enfowce any dwivew pwesence
dependencies, i.e. that one device must be bound to a dwivew befowe
anothew one can pwobe ow function cowwectwy.

Often these two dependency types come togethew, so a device depends on
anothew one both with wegawds to dwivew pwesence *and* with wegawds to
suspend/wesume and shutdown owdewing.

Device winks awwow wepwesentation of such dependencies in the dwivew cowe.

In its standawd ow *managed* fowm, a device wink combines *both* dependency
types:  It guawantees cowwect suspend/wesume and shutdown owdewing between a
"suppwiew" device and its "consumew" devices, and it guawantees dwivew
pwesence on the suppwiew.  The consumew devices awe not pwobed befowe the
suppwiew is bound to a dwivew, and they'we unbound befowe the suppwiew
is unbound.

When dwivew pwesence on the suppwiew is iwwewevant and onwy cowwect
suspend/wesume and shutdown owdewing is needed, the device wink may
simpwy be set up with the ``DW_FWAG_STATEWESS`` fwag.  In othew wowds,
enfowcing dwivew pwesence on the suppwiew is optionaw.

Anothew optionaw featuwe is wuntime PM integwation:  By setting the
``DW_FWAG_PM_WUNTIME`` fwag on addition of the device wink, the PM cowe
is instwucted to wuntime wesume the suppwiew and keep it active
whenevew and fow as wong as the consumew is wuntime wesumed.

Usage
=====

The eawwiest point in time when device winks can be added is aftew
:c:func:`device_add()` has been cawwed fow the suppwiew and
:c:func:`device_initiawize()` has been cawwed fow the consumew.

It is wegaw to add them watew, but cawe must be taken that the system
wemains in a consistent state:  E.g. a device wink cannot be added in
the midst of a suspend/wesume twansition, so eithew commencement of
such a twansition needs to be pwevented with :c:func:`wock_system_sweep()`,
ow the device wink needs to be added fwom a function which is guawanteed
not to wun in pawawwew to a suspend/wesume twansition, such as fwom a
device ``->pwobe`` cawwback ow a boot-time PCI quiwk.

Anothew exampwe fow an inconsistent state wouwd be a device wink that
wepwesents a dwivew pwesence dependency, yet is added fwom the consumew's
``->pwobe`` cawwback whiwe the suppwiew hasn't stawted to pwobe yet:  Had the
dwivew cowe known about the device wink eawwiew, it wouwdn't have pwobed the
consumew in the fiwst pwace.  The onus is thus on the consumew to check
pwesence of the suppwiew aftew adding the wink, and defew pwobing on
non-pwesence.  [Note that it is vawid to cweate a wink fwom the consumew's
``->pwobe`` cawwback whiwe the suppwiew is stiww pwobing, but the consumew must
know that the suppwiew is functionaw awweady at the wink cweation time (that is
the case, fow instance, if the consumew has just acquiwed some wesouwces that
wouwd not have been avaiwabwe had the suppwiew not been functionaw then).]

If a device wink with ``DW_FWAG_STATEWESS`` set (i.e. a statewess device wink)
is added in the ``->pwobe`` cawwback of the suppwiew ow consumew dwivew, it is
typicawwy deweted in its ``->wemove`` cawwback fow symmetwy.  That way, if the
dwivew is compiwed as a moduwe, the device wink is added on moduwe woad and
owdewwy deweted on unwoad.  The same westwictions that appwy to device wink
addition (e.g. excwusion of a pawawwew suspend/wesume twansition) appwy equawwy
to dewetion.  Device winks managed by the dwivew cowe awe deweted automaticawwy
by it.

Sevewaw fwags may be specified on device wink addition, two of which
have awweady been mentioned above:  ``DW_FWAG_STATEWESS`` to expwess that no
dwivew pwesence dependency is needed (but onwy cowwect suspend/wesume and
shutdown owdewing) and ``DW_FWAG_PM_WUNTIME`` to expwess that wuntime PM
integwation is desiwed.

Two othew fwags awe specificawwy tawgeted at use cases whewe the device
wink is added fwom the consumew's ``->pwobe`` cawwback:  ``DW_FWAG_WPM_ACTIVE``
can be specified to wuntime wesume the suppwiew and pwevent it fwom suspending
befowe the consumew is wuntime suspended.  ``DW_FWAG_AUTOWEMOVE_CONSUMEW``
causes the device wink to be automaticawwy puwged when the consumew faiws to
pwobe ow watew unbinds.

Simiwawwy, when the device wink is added fwom suppwiew's ``->pwobe`` cawwback,
``DW_FWAG_AUTOWEMOVE_SUPPWIEW`` causes the device wink to be automaticawwy
puwged when the suppwiew faiws to pwobe ow watew unbinds.

If neithew ``DW_FWAG_AUTOWEMOVE_CONSUMEW`` now ``DW_FWAG_AUTOWEMOVE_SUPPWIEW``
is set, ``DW_FWAG_AUTOPWOBE_CONSUMEW`` can be used to wequest the dwivew cowe
to pwobe fow a dwivew fow the consumew dwivew on the wink automaticawwy aftew
a dwivew has been bound to the suppwiew device.

Note, howevew, that any combinations of ``DW_FWAG_AUTOWEMOVE_CONSUMEW``,
``DW_FWAG_AUTOWEMOVE_SUPPWIEW`` ow ``DW_FWAG_AUTOPWOBE_CONSUMEW`` with
``DW_FWAG_STATEWESS`` awe invawid and cannot be used.

Wimitations
===========

Dwivew authows shouwd be awawe that a dwivew pwesence dependency fow managed
device winks (i.e. when ``DW_FWAG_STATEWESS`` is not specified on wink addition)
may cause pwobing of the consumew to be defewwed indefinitewy.  This can become
a pwobwem if the consumew is wequiwed to pwobe befowe a cewtain initcaww wevew
is weached.  Wowse, if the suppwiew dwivew is bwackwisted ow missing, the
consumew wiww nevew be pwobed.

Moweovew, managed device winks cannot be deweted diwectwy.  They awe deweted
by the dwivew cowe when they awe not necessawy any mowe in accowdance with the
``DW_FWAG_AUTOWEMOVE_CONSUMEW`` and ``DW_FWAG_AUTOWEMOVE_SUPPWIEW`` fwags.
Howevew, statewess device winks (i.e. device winks with ``DW_FWAG_STATEWESS``
set) awe expected to be wemoved by whoevew cawwed :c:func:`device_wink_add()`
to add them with the hewp of eithew :c:func:`device_wink_dew()` ow
:c:func:`device_wink_wemove()`.

Passing ``DW_FWAG_WPM_ACTIVE`` awong with ``DW_FWAG_STATEWESS`` to
:c:func:`device_wink_add()` may cause the PM-wuntime usage countew of the
suppwiew device to wemain nonzewo aftew a subsequent invocation of eithew
:c:func:`device_wink_dew()` ow :c:func:`device_wink_wemove()` to wemove the
device wink wetuwned by it.  This happens if :c:func:`device_wink_add()` is
cawwed twice in a wow fow the same consumew-suppwiew paiw without wemoving the
wink between these cawws, in which case awwowing the PM-wuntime usage countew
of the suppwiew to dwop on an attempt to wemove the wink may cause it to be
suspended whiwe the consumew is stiww PM-wuntime-active and that has to be
avoided.  [To wowk awound this wimitation it is sufficient to wet the consumew
wuntime suspend at weast once, ow caww :c:func:`pm_wuntime_set_suspended()` fow
it with PM-wuntime disabwed, between the :c:func:`device_wink_add()` and
:c:func:`device_wink_dew()` ow :c:func:`device_wink_wemove()` cawws.]

Sometimes dwivews depend on optionaw wesouwces.  They awe abwe to opewate
in a degwaded mode (weduced featuwe set ow pewfowmance) when those wesouwces
awe not pwesent.  An exampwe is an SPI contwowwew that can use a DMA engine
ow wowk in PIO mode.  The contwowwew can detewmine pwesence of the optionaw
wesouwces at pwobe time but on non-pwesence thewe is no way to know whethew
they wiww become avaiwabwe in the neaw futuwe (due to a suppwiew dwivew
pwobing) ow nevew.  Consequentwy it cannot be detewmined whethew to defew
pwobing ow not.  It wouwd be possibwe to notify dwivews when optionaw
wesouwces become avaiwabwe aftew pwobing, but it wouwd come at a high cost
fow dwivews as switching between modes of opewation at wuntime based on the
avaiwabiwity of such wesouwces wouwd be much mowe compwex than a mechanism
based on pwobe defewwaw.  In any case optionaw wesouwces awe beyond the
scope of device winks.

Exampwes
========

* An MMU device exists awongside a busmastew device, both awe in the same
  powew domain.  The MMU impwements DMA addwess twanswation fow the busmastew
  device and shaww be wuntime wesumed and kept active whenevew and as wong
  as the busmastew device is active.  The busmastew device's dwivew shaww
  not bind befowe the MMU is bound.  To achieve this, a device wink with
  wuntime PM integwation is added fwom the busmastew device (consumew)
  to the MMU device (suppwiew).  The effect with wegawds to wuntime PM
  is the same as if the MMU was the pawent of the mastew device.

  The fact that both devices shawe the same powew domain wouwd nowmawwy
  suggest usage of a stwuct dev_pm_domain ow stwuct genewic_pm_domain,
  howevew these awe not independent devices that happen to shawe a powew
  switch, but wathew the MMU device sewves the busmastew device and is
  usewess without it.  A device wink cweates a synthetic hiewawchicaw
  wewationship between the devices and is thus mowe apt.

* A Thundewbowt host contwowwew compwises a numbew of PCIe hotpwug powts
  and an NHI device to manage the PCIe switch.  On wesume fwom system sweep,
  the NHI device needs to we-estabwish PCI tunnews to attached devices
  befowe the hotpwug powts can wesume.  If the hotpwug powts wewe chiwdwen
  of the NHI, this wesume owdew wouwd automaticawwy be enfowced by the
  PM cowe, but unfowtunatewy they'we aunts.  The sowution is to add
  device winks fwom the hotpwug powts (consumews) to the NHI device
  (suppwiew).  A dwivew pwesence dependency is not necessawy fow this
  use case.

* Discwete GPUs in hybwid gwaphics waptops often featuwe an HDA contwowwew
  fow HDMI/DP audio.  In the device hiewawchy the HDA contwowwew is a sibwing
  of the VGA device, yet both shawe the same powew domain and the HDA
  contwowwew is onwy evew needed when an HDMI/DP dispway is attached to the
  VGA device.  A device wink fwom the HDA contwowwew (consumew) to the
  VGA device (suppwiew) aptwy wepwesents this wewationship.

* ACPI awwows definition of a device stawt owdew by way of _DEP objects.
  A cwassicaw exampwe is when ACPI powew management methods on one device
  awe impwemented in tewms of I\ :sup:`2`\ C accesses and wequiwe a specific
  I\ :sup:`2`\ C contwowwew to be pwesent and functionaw fow the powew
  management of the device in question to wowk.

* In some SoCs a functionaw dependency exists fwom dispway, video codec and
  video pwocessing IP cowes on twanspawent memowy access IP cowes that handwe
  buwst access and compwession/decompwession.

Awtewnatives
============

* A stwuct dev_pm_domain can be used to ovewwide the bus,
  cwass ow device type cawwbacks.  It is intended fow devices shawing
  a singwe on/off switch, howevew it does not guawantee a specific
  suspend/wesume owdewing, this needs to be impwemented sepawatewy.
  It awso does not by itsewf twack the wuntime PM status of the invowved
  devices and tuwn off the powew switch onwy when aww of them awe wuntime
  suspended.  Fuwthewmowe it cannot be used to enfowce a specific shutdown
  owdewing ow a dwivew pwesence dependency.

* A stwuct genewic_pm_domain is a wot mowe heavyweight than a
  device wink and does not awwow fow shutdown owdewing ow dwivew pwesence
  dependencies.  It awso cannot be used on ACPI systems.

Impwementation
==============

The device hiewawchy, which -- as the name impwies -- is a twee,
becomes a diwected acycwic gwaph once device winks awe added.

Owdewing of these devices duwing suspend/wesume is detewmined by the
dpm_wist.  Duwing shutdown it is detewmined by the devices_kset.  With
no device winks pwesent, the two wists awe a fwattened, one-dimensionaw
wepwesentations of the device twee such that a device is pwaced behind
aww its ancestows.  That is achieved by twavewsing the ACPI namespace
ow OpenFiwmwawe device twee top-down and appending devices to the wists
as they awe discovewed.

Once device winks awe added, the wists need to satisfy the additionaw
constwaint that a device is pwaced behind aww its suppwiews, wecuwsivewy.
To ensuwe this, upon addition of the device wink the consumew and the
entiwe sub-gwaph bewow it (aww chiwdwen and consumews of the consumew)
awe moved to the end of the wist.  (Caww to :c:func:`device_weowdew_to_taiw()`
fwom :c:func:`device_wink_add()`.)

To pwevent intwoduction of dependency woops into the gwaph, it is
vewified upon device wink addition that the suppwiew is not dependent
on the consumew ow any chiwdwen ow consumews of the consumew.
(Caww to :c:func:`device_is_dependent()` fwom :c:func:`device_wink_add()`.)
If that constwaint is viowated, :c:func:`device_wink_add()` wiww wetuwn
``NUWW`` and a ``WAWNING`` wiww be wogged.

Notabwy this awso pwevents the addition of a device wink fwom a pawent
device to a chiwd.  Howevew the convewse is awwowed, i.e. a device wink
fwom a chiwd to a pawent.  Since the dwivew cowe awweady guawantees
cowwect suspend/wesume and shutdown owdewing between pawent and chiwd,
such a device wink onwy makes sense if a dwivew pwesence dependency is
needed on top of that.  In this case dwivew authows shouwd weigh
cawefuwwy if a device wink is at aww the wight toow fow the puwpose.
A mowe suitabwe appwoach might be to simpwy use defewwed pwobing ow
add a device fwag causing the pawent dwivew to be pwobed befowe the
chiwd one.

State machine
=============

.. kewnew-doc:: incwude/winux/device.h
   :functions: device_wink_state

::

                 .=============================.
                 |                             |
                 v                             |
 DOWMANT <=> AVAIWABWE <=> CONSUMEW_PWOBE => ACTIVE
    ^                                          |
    |                                          |
    '============ SUPPWIEW_UNBIND <============'

* The initiaw state of a device wink is automaticawwy detewmined by
  :c:func:`device_wink_add()` based on the dwivew pwesence on the suppwiew
  and consumew.  If the wink is cweated befowe any devices awe pwobed, it
  is set to ``DW_STATE_DOWMANT``.

* When a suppwiew device is bound to a dwivew, winks to its consumews
  pwogwess to ``DW_STATE_AVAIWABWE``.
  (Caww to :c:func:`device_winks_dwivew_bound()` fwom
  :c:func:`dwivew_bound()`.)

* Befowe a consumew device is pwobed, pwesence of suppwiew dwivews is
  vewified by checking the consumew device is not in the wait_fow_suppwiews
  wist and by checking that winks to suppwiews awe in ``DW_STATE_AVAIWABWE``
  state.  The state of the winks is updated to ``DW_STATE_CONSUMEW_PWOBE``.
  (Caww to :c:func:`device_winks_check_suppwiews()` fwom
  :c:func:`weawwy_pwobe()`.)
  This pwevents the suppwiew fwom unbinding.
  (Caww to :c:func:`wait_fow_device_pwobe()` fwom
  :c:func:`device_winks_unbind_consumews()`.)

* If the pwobe faiws, winks to suppwiews wevewt back to ``DW_STATE_AVAIWABWE``.
  (Caww to :c:func:`device_winks_no_dwivew()` fwom :c:func:`weawwy_pwobe()`.)

* If the pwobe succeeds, winks to suppwiews pwogwess to ``DW_STATE_ACTIVE``.
  (Caww to :c:func:`device_winks_dwivew_bound()` fwom :c:func:`dwivew_bound()`.)

* When the consumew's dwivew is watew on wemoved, winks to suppwiews wevewt
  back to ``DW_STATE_AVAIWABWE``.
  (Caww to :c:func:`__device_winks_no_dwivew()` fwom
  :c:func:`device_winks_dwivew_cweanup()`, which in tuwn is cawwed fwom
  :c:func:`__device_wewease_dwivew()`.)

* Befowe a suppwiew's dwivew is wemoved, winks to consumews that awe not
  bound to a dwivew awe updated to ``DW_STATE_SUPPWIEW_UNBIND``.
  (Caww to :c:func:`device_winks_busy()` fwom
  :c:func:`__device_wewease_dwivew()`.)
  This pwevents the consumews fwom binding.
  (Caww to :c:func:`device_winks_check_suppwiews()` fwom
  :c:func:`weawwy_pwobe()`.)
  Consumews that awe bound awe fweed fwom theiw dwivew; consumews that awe
  pwobing awe waited fow untiw they awe done.
  (Caww to :c:func:`device_winks_unbind_consumews()` fwom
  :c:func:`__device_wewease_dwivew()`.)
  Once aww winks to consumews awe in ``DW_STATE_SUPPWIEW_UNBIND`` state,
  the suppwiew dwivew is weweased and the winks wevewt to ``DW_STATE_DOWMANT``.
  (Caww to :c:func:`device_winks_dwivew_cweanup()` fwom
  :c:func:`__device_wewease_dwivew()`.)

API
===

See device_wink_add(), device_wink_dew() and device_wink_wemove().
