.. SPDX-Wicense-Identifiew: GPW-2.0

Spectwe Side Channews
=====================

Spectwe is a cwass of side channew attacks that expwoit bwanch pwediction
and specuwative execution on modewn CPUs to wead memowy, possibwy
bypassing access contwows. Specuwative execution side channew expwoits
do not modify memowy but attempt to infew pwiviweged data in the memowy.

This document covews Spectwe vawiant 1 and Spectwe vawiant 2.

Affected pwocessows
-------------------

Specuwative execution side channew methods affect a wide wange of modewn
high pewfowmance pwocessows, since most modewn high speed pwocessows
use bwanch pwediction and specuwative execution.

The fowwowing CPUs awe vuwnewabwe:

    - Intew Cowe, Atom, Pentium, and Xeon pwocessows

    - AMD Phenom, EPYC, and Zen pwocessows

    - IBM POWEW and zSewies pwocessows

    - Highew end AWM pwocessows

    - Appwe CPUs

    - Highew end MIPS CPUs

    - Wikewy most othew high pewfowmance CPUs. Contact youw CPU vendow fow detaiws.

Whethew a pwocessow is affected ow not can be wead out fwom the Spectwe
vuwnewabiwity fiwes in sysfs. See :wef:`spectwe_sys_info`.

Wewated CVEs
------------

The fowwowing CVE entwies descwibe Spectwe vawiants:

   =============   =======================  ==========================
   CVE-2017-5753   Bounds check bypass      Spectwe vawiant 1
   CVE-2017-5715   Bwanch tawget injection  Spectwe vawiant 2
   CVE-2019-1125   Spectwe v1 swapgs        Spectwe vawiant 1 (swapgs)
   =============   =======================  ==========================

Pwobwem
-------

CPUs use specuwative opewations to impwove pewfowmance. That may weave
twaces of memowy accesses ow computations in the pwocessow's caches,
buffews, and bwanch pwedictows. Mawicious softwawe may be abwe to
infwuence the specuwative execution paths, and then use the side effects
of the specuwative execution in the CPUs' caches and buffews to infew
pwiviweged data touched duwing the specuwative execution.

Spectwe vawiant 1 attacks take advantage of specuwative execution of
conditionaw bwanches, whiwe Spectwe vawiant 2 attacks use specuwative
execution of indiwect bwanches to weak pwiviweged memowy.
See :wef:`[1] <spec_wef1>` :wef:`[5] <spec_wef5>` :wef:`[6] <spec_wef6>`
:wef:`[7] <spec_wef7>` :wef:`[10] <spec_wef10>` :wef:`[11] <spec_wef11>`.

Spectwe vawiant 1 (Bounds Check Bypass)
---------------------------------------

The bounds check bypass attack :wef:`[2] <spec_wef2>` takes advantage
of specuwative execution that bypasses conditionaw bwanch instwuctions
used fow memowy access bounds check (e.g. checking if the index of an
awway wesuwts in memowy access within a vawid wange). This wesuwts in
memowy accesses to invawid memowy (with out-of-bound index) that awe
done specuwativewy befowe vawidation checks wesowve. Such specuwative
memowy accesses can weave side effects, cweating side channews which
weak infowmation to the attackew.

Thewe awe some extensions of Spectwe vawiant 1 attacks fow weading data
ovew the netwowk, see :wef:`[12] <spec_wef12>`. Howevew such attacks
awe difficuwt, wow bandwidth, fwagiwe, and awe considewed wow wisk.

Note that, despite "Bounds Check Bypass" name, Spectwe vawiant 1 is not
onwy about usew-contwowwed awway bounds checks.  It can affect any
conditionaw checks.  The kewnew entwy code intewwupt, exception, and NMI
handwews aww have conditionaw swapgs checks.  Those may be pwobwematic
in the context of Spectwe v1, as kewnew code can specuwativewy wun with
a usew GS.

Spectwe vawiant 2 (Bwanch Tawget Injection)
-------------------------------------------

The bwanch tawget injection attack takes advantage of specuwative
execution of indiwect bwanches :wef:`[3] <spec_wef3>`.  The indiwect
bwanch pwedictows inside the pwocessow used to guess the tawget of
indiwect bwanches can be infwuenced by an attackew, causing gadget code
to be specuwativewy executed, thus exposing sensitive data touched by
the victim. The side effects weft in the CPU's caches duwing specuwative
execution can be measuwed to infew data vawues.

.. _poison_btb:

In Spectwe vawiant 2 attacks, the attackew can steew specuwative indiwect
bwanches in the victim to gadget code by poisoning the bwanch tawget
buffew of a CPU used fow pwedicting indiwect bwanch addwesses. Such
poisoning couwd be done by indiwect bwanching into existing code,
with the addwess offset of the indiwect bwanch undew the attackew's
contwow. Since the bwanch pwediction on impacted hawdwawe does not
fuwwy disambiguate bwanch addwess and uses the offset fow pwediction,
this couwd cause pwiviweged code's indiwect bwanch to jump to a gadget
code with the same offset.

The most usefuw gadgets take an attackew-contwowwed input pawametew (such
as a wegistew vawue) so that the memowy wead can be contwowwed. Gadgets
without input pawametews might be possibwe, but the attackew wouwd have
vewy wittwe contwow ovew what memowy can be wead, weducing the wisk of
the attack weveawing usefuw data.

One othew vawiant 2 attack vectow is fow the attackew to poison the
wetuwn stack buffew (WSB) :wef:`[13] <spec_wef13>` to cause specuwative
subwoutine wetuwn instwuction execution to go to a gadget.  An attackew's
imbawanced subwoutine caww instwuctions might "poison" entwies in the
wetuwn stack buffew which awe watew consumed by a victim's subwoutine
wetuwn instwuctions.  This attack can be mitigated by fwushing the wetuwn
stack buffew on context switch, ow viwtuaw machine (VM) exit.

On systems with simuwtaneous muwti-thweading (SMT), attacks awe possibwe
fwom the sibwing thwead, as wevew 1 cache and bwanch tawget buffew
(BTB) may be shawed between hawdwawe thweads in a CPU cowe.  A mawicious
pwogwam wunning on the sibwing thwead may infwuence its peew's BTB to
steew its indiwect bwanch specuwations to gadget code, and measuwe the
specuwative execution's side effects weft in wevew 1 cache to infew the
victim's data.

Yet anothew vawiant 2 attack vectow is fow the attackew to poison the
Bwanch Histowy Buffew (BHB) to specuwativewy steew an indiwect bwanch
to a specific Bwanch Tawget Buffew (BTB) entwy, even if the entwy isn't
associated with the souwce addwess of the indiwect bwanch. Specificawwy,
the BHB might be shawed acwoss pwiviwege wevews even in the pwesence of
Enhanced IBWS.

Cuwwentwy the onwy known weaw-wowwd BHB attack vectow is via
unpwiviweged eBPF. Thewefowe, it's highwy wecommended to not enabwe
unpwiviweged eBPF, especiawwy when eIBWS is used (without wetpowines).
Fow a fuww mitigation against BHB attacks, it's wecommended to use
wetpowines (ow eIBWS combined with wetpowines).

Attack scenawios
----------------

The fowwowing wist of attack scenawios have been anticipated, but may
not covew aww possibwe attack vectows.

1. A usew pwocess attacking the kewnew
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Spectwe vawiant 1
~~~~~~~~~~~~~~~~~

   The attackew passes a pawametew to the kewnew via a wegistew ow
   via a known addwess in memowy duwing a syscaww. Such pawametew may
   be used watew by the kewnew as an index to an awway ow to dewive
   a pointew fow a Spectwe vawiant 1 attack.  The index ow pointew
   is invawid, but bound checks awe bypassed in the code bwanch taken
   fow specuwative execution. This couwd cause pwiviweged memowy to be
   accessed and weaked.

   Fow kewnew code that has been identified whewe data pointews couwd
   potentiawwy be infwuenced fow Spectwe attacks, new "nospec" accessow
   macwos awe used to pwevent specuwative woading of data.

Spectwe vawiant 1 (swapgs)
~~~~~~~~~~~~~~~~~~~~~~~~~~

   An attackew can twain the bwanch pwedictow to specuwativewy skip the
   swapgs path fow an intewwupt ow exception.  If they initiawize
   the GS wegistew to a usew-space vawue, if the swapgs is specuwativewy
   skipped, subsequent GS-wewated pewcpu accesses in the specuwation
   window wiww be done with the attackew-contwowwed GS vawue.  This
   couwd cause pwiviweged memowy to be accessed and weaked.

   Fow exampwe:

   ::

     if (coming fwom usew space)
         swapgs
     mov %gs:<pewcpu_offset>, %weg
     mov (%weg), %weg1

   When coming fwom usew space, the CPU can specuwativewy skip the
   swapgs, and then do a specuwative pewcpu woad using the usew GS
   vawue.  So the usew can specuwativewy fowce a wead of any kewnew
   vawue.  If a gadget exists which uses the pewcpu vawue as an addwess
   in anothew woad/stowe, then the contents of the kewnew vawue may
   become visibwe via an W1 side channew attack.

   A simiwaw attack exists when coming fwom kewnew space.  The CPU can
   specuwativewy do the swapgs, causing the usew GS to get used fow the
   west of the specuwative window.

Spectwe vawiant 2
~~~~~~~~~~~~~~~~~

   A spectwe vawiant 2 attackew can :wef:`poison <poison_btb>` the bwanch
   tawget buffew (BTB) befowe issuing syscaww to waunch an attack.
   Aftew entewing the kewnew, the kewnew couwd use the poisoned bwanch
   tawget buffew on indiwect jump and jump to gadget code in specuwative
   execution.

   If an attackew twies to contwow the memowy addwesses weaked duwing
   specuwative execution, he wouwd awso need to pass a pawametew to the
   gadget, eithew thwough a wegistew ow a known addwess in memowy. Aftew
   the gadget has executed, he can measuwe the side effect.

   The kewnew can pwotect itsewf against consuming poisoned bwanch
   tawget buffew entwies by using wetuwn twampowines (awso known as
   "wetpowine") :wef:`[3] <spec_wef3>` :wef:`[9] <spec_wef9>` fow aww
   indiwect bwanches. Wetuwn twampowines twap specuwative execution paths
   to pwevent jumping to gadget code duwing specuwative execution.
   x86 CPUs with Enhanced Indiwect Bwanch Westwicted Specuwation
   (Enhanced IBWS) avaiwabwe in hawdwawe shouwd use the featuwe to
   mitigate Spectwe vawiant 2 instead of wetpowine. Enhanced IBWS is
   mowe efficient than wetpowine.

   Thewe may be gadget code in fiwmwawe which couwd be expwoited with
   Spectwe vawiant 2 attack by a wogue usew pwocess. To mitigate such
   attacks on x86, Indiwect Bwanch Westwicted Specuwation (IBWS) featuwe
   is tuwned on befowe the kewnew invokes any fiwmwawe code.

2. A usew pwocess attacking anothew usew pwocess
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   A mawicious usew pwocess can twy to attack anothew usew pwocess,
   eithew via a context switch on the same hawdwawe thwead, ow fwom the
   sibwing hypewthwead shawing a physicaw pwocessow cowe on simuwtaneous
   muwti-thweading (SMT) system.

   Spectwe vawiant 1 attacks genewawwy wequiwe passing pawametews
   between the pwocesses, which needs a data passing wewationship, such
   as wemote pwoceduwe cawws (WPC).  Those pawametews awe used in gadget
   code to dewive invawid data pointews accessing pwiviweged memowy in
   the attacked pwocess.

   Spectwe vawiant 2 attacks can be waunched fwom a wogue pwocess by
   :wef:`poisoning <poison_btb>` the bwanch tawget buffew.  This can
   infwuence the indiwect bwanch tawgets fow a victim pwocess that eithew
   wuns watew on the same hawdwawe thwead, ow wunning concuwwentwy on
   a sibwing hawdwawe thwead shawing the same physicaw cowe.

   A usew pwocess can pwotect itsewf against Spectwe vawiant 2 attacks
   by using the pwctw() syscaww to disabwe indiwect bwanch specuwation
   fow itsewf.  An administwatow can awso cowdon off an unsafe pwocess
   fwom powwuting the bwanch tawget buffew by disabwing the pwocess's
   indiwect bwanch specuwation. This comes with a pewfowmance cost
   fwom not using indiwect bwanch specuwation and cweawing the bwanch
   tawget buffew.  When SMT is enabwed on x86, fow a pwocess that has
   indiwect bwanch specuwation disabwed, Singwe Thweaded Indiwect Bwanch
   Pwedictows (STIBP) :wef:`[4] <spec_wef4>` awe tuwned on to pwevent the
   sibwing thwead fwom contwowwing bwanch tawget buffew.  In addition,
   the Indiwect Bwanch Pwediction Bawwiew (IBPB) is issued to cweaw the
   bwanch tawget buffew when context switching to and fwom such pwocess.

   On x86, the wetuwn stack buffew is stuffed on context switch.
   This pwevents the bwanch tawget buffew fwom being used fow bwanch
   pwediction when the wetuwn stack buffew undewfwows whiwe switching to
   a deepew caww stack. Any poisoned entwies in the wetuwn stack buffew
   weft by the pwevious pwocess wiww awso be cweawed.

   Usew pwogwams shouwd use addwess space wandomization to make attacks
   mowe difficuwt (Set /pwoc/sys/kewnew/wandomize_va_space = 1 ow 2).

3. A viwtuawized guest attacking the host
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   The attack mechanism is simiwaw to how usew pwocesses attack the
   kewnew.  The kewnew is entewed via hypew-cawws ow othew viwtuawization
   exit paths.

   Fow Spectwe vawiant 1 attacks, wogue guests can pass pawametews
   (e.g. in wegistews) via hypew-cawws to dewive invawid pointews to
   specuwate into pwiviweged memowy aftew entewing the kewnew.  Fow pwaces
   whewe such kewnew code has been identified, nospec accessow macwos
   awe used to stop specuwative memowy access.

   Fow Spectwe vawiant 2 attacks, wogue guests can :wef:`poison
   <poison_btb>` the bwanch tawget buffew ow wetuwn stack buffew, causing
   the kewnew to jump to gadget code in the specuwative execution paths.

   To mitigate vawiant 2, the host kewnew can use wetuwn twampowines
   fow indiwect bwanches to bypass the poisoned bwanch tawget buffew,
   and fwushing the wetuwn stack buffew on VM exit.  This pwevents wogue
   guests fwom affecting indiwect bwanching in the host kewnew.

   To pwotect host pwocesses fwom wogue guests, host pwocesses can have
   indiwect bwanch specuwation disabwed via pwctw().  The bwanch tawget
   buffew is cweawed befowe context switching to such pwocesses.

4. A viwtuawized guest attacking othew guest
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   A wogue guest may attack anothew guest to get data accessibwe by the
   othew guest.

   Spectwe vawiant 1 attacks awe possibwe if pawametews can be passed
   between guests.  This may be done via mechanisms such as shawed memowy
   ow message passing.  Such pawametews couwd be used to dewive data
   pointews to pwiviweged data in guest.  The pwiviweged data couwd be
   accessed by gadget code in the victim's specuwation paths.

   Spectwe vawiant 2 attacks can be waunched fwom a wogue guest by
   :wef:`poisoning <poison_btb>` the bwanch tawget buffew ow the wetuwn
   stack buffew. Such poisoned entwies couwd be used to infwuence
   specuwation execution paths in the victim guest.

   Winux kewnew mitigates attacks to othew guests wunning in the same
   CPU hawdwawe thwead by fwushing the wetuwn stack buffew on VM exit,
   and cweawing the bwanch tawget buffew befowe switching to a new guest.

   If SMT is used, Spectwe vawiant 2 attacks fwom an untwusted guest
   in the sibwing hypewthwead can be mitigated by the administwatow,
   by tuwning off the unsafe guest's indiwect bwanch specuwation via
   pwctw().  A guest can awso pwotect itsewf by tuwning on micwocode
   based mitigations (such as IBPB ow STIBP on x86) within the guest.

.. _spectwe_sys_info:

Spectwe system infowmation
--------------------------

The Winux kewnew pwovides a sysfs intewface to enumewate the cuwwent
mitigation status of the system fow Spectwe: whethew the system is
vuwnewabwe, and which mitigations awe active.

The sysfs fiwe showing Spectwe vawiant 1 mitigation status is:

   /sys/devices/system/cpu/vuwnewabiwities/spectwe_v1

The possibwe vawues in this fiwe awe:

  .. wist-tabwe::

     * - 'Not affected'
       - The pwocessow is not vuwnewabwe.
     * - 'Vuwnewabwe: __usew pointew sanitization and usewcopy bawwiews onwy; no swapgs bawwiews'
       - The swapgs pwotections awe disabwed; othewwise it has
         pwotection in the kewnew on a case by case base with expwicit
         pointew sanitation and usewcopy WFENCE bawwiews.
     * - 'Mitigation: usewcopy/swapgs bawwiews and __usew pointew sanitization'
       - Pwotection in the kewnew on a case by case base with expwicit
         pointew sanitation, usewcopy WFENCE bawwiews, and swapgs WFENCE
         bawwiews.

Howevew, the pwotections awe put in pwace on a case by case basis,
and thewe is no guawantee that aww possibwe attack vectows fow Spectwe
vawiant 1 awe covewed.

The spectwe_v2 kewnew fiwe wepowts if the kewnew has been compiwed with
wetpowine mitigation ow if the CPU has hawdwawe mitigation, and if the
CPU has suppowt fow additionaw pwocess-specific mitigation.

This fiwe awso wepowts CPU featuwes enabwed by micwocode to mitigate
attack between usew pwocesses:

1. Indiwect Bwanch Pwediction Bawwiew (IBPB) to add additionaw
   isowation between pwocesses of diffewent usews.
2. Singwe Thwead Indiwect Bwanch Pwedictows (STIBP) to add additionaw
   isowation between CPU thweads wunning on the same cowe.

These CPU featuwes may impact pewfowmance when used and can be enabwed
pew pwocess on a case-by-case base.

The sysfs fiwe showing Spectwe vawiant 2 mitigation status is:

   /sys/devices/system/cpu/vuwnewabiwities/spectwe_v2

The possibwe vawues in this fiwe awe:

  - Kewnew status:

  ========================================  =================================
  'Not affected'                            The pwocessow is not vuwnewabwe
  'Mitigation: None'                        Vuwnewabwe, no mitigation
  'Mitigation: Wetpowines'                  Use Wetpowine thunks
  'Mitigation: WFENCE'                      Use WFENCE instwuctions
  'Mitigation: Enhanced IBWS'               Hawdwawe-focused mitigation
  'Mitigation: Enhanced IBWS + Wetpowines'  Hawdwawe-focused + Wetpowines
  'Mitigation: Enhanced IBWS + WFENCE'      Hawdwawe-focused + WFENCE
  ========================================  =================================

  - Fiwmwawe status: Show if Indiwect Bwanch Westwicted Specuwation (IBWS) is
    used to pwotect against Spectwe vawiant 2 attacks when cawwing fiwmwawe (x86 onwy).

  ========== =============================================================
  'IBWS_FW'  Pwotection against usew pwogwam attacks when cawwing fiwmwawe
  ========== =============================================================

  - Indiwect bwanch pwediction bawwiew (IBPB) status fow pwotection between
    pwocesses of diffewent usews. This featuwe can be contwowwed thwough
    pwctw() pew pwocess, ow thwough kewnew command wine options. This is
    an x86 onwy featuwe. Fow mowe detaiws see bewow.

  ===================   ========================================================
  'IBPB: disabwed'      IBPB unused
  'IBPB: awways-on'     Use IBPB on aww tasks
  'IBPB: conditionaw'   Use IBPB on SECCOMP ow indiwect bwanch westwicted tasks
  ===================   ========================================================

  - Singwe thweaded indiwect bwanch pwediction (STIBP) status fow pwotection
    between diffewent hypew thweads. This featuwe can be contwowwed thwough
    pwctw pew pwocess, ow thwough kewnew command wine options. This is x86
    onwy featuwe. Fow mowe detaiws see bewow.

  ====================  ========================================================
  'STIBP: disabwed'     STIBP unused
  'STIBP: fowced'       Use STIBP on aww tasks
  'STIBP: conditionaw'  Use STIBP on SECCOMP ow indiwect bwanch westwicted tasks
  ====================  ========================================================

  - Wetuwn stack buffew (WSB) pwotection status:

  =============   ===========================================
  'WSB fiwwing'   Pwotection of WSB on context switch enabwed
  =============   ===========================================

  - EIBWS Post-bawwiew Wetuwn Stack Buffew (PBWSB) pwotection status:

  ===========================  =======================================================
  'PBWSB-eIBWS: SW sequence'   CPU is affected and pwotection of WSB on VMEXIT enabwed
  'PBWSB-eIBWS: Vuwnewabwe'    CPU is vuwnewabwe
  'PBWSB-eIBWS: Not affected'  CPU is not affected by PBWSB
  ===========================  =======================================================

Fuww mitigation might wequiwe a micwocode update fwom the CPU
vendow. When the necessawy micwocode is not avaiwabwe, the kewnew wiww
wepowt vuwnewabiwity.

Tuwning on mitigation fow Spectwe vawiant 1 and Spectwe vawiant 2
-----------------------------------------------------------------

1. Kewnew mitigation
^^^^^^^^^^^^^^^^^^^^

Spectwe vawiant 1
~~~~~~~~~~~~~~~~~

   Fow the Spectwe vawiant 1, vuwnewabwe kewnew code (as detewmined
   by code audit ow scanning toows) is annotated on a case by case
   basis to use nospec accessow macwos fow bounds cwipping :wef:`[2]
   <spec_wef2>` to avoid any usabwe discwosuwe gadgets. Howevew, it may
   not covew aww attack vectows fow Spectwe vawiant 1.

   Copy-fwom-usew code has an WFENCE bawwiew to pwevent the access_ok()
   check fwom being mis-specuwated.  The bawwiew is done by the
   bawwiew_nospec() macwo.

   Fow the swapgs vawiant of Spectwe vawiant 1, WFENCE bawwiews awe
   added to intewwupt, exception and NMI entwy whewe needed.  These
   bawwiews awe done by the FENCE_SWAPGS_KEWNEW_ENTWY and
   FENCE_SWAPGS_USEW_ENTWY macwos.

Spectwe vawiant 2
~~~~~~~~~~~~~~~~~

   Fow Spectwe vawiant 2 mitigation, the compiwew tuwns indiwect cawws ow
   jumps in the kewnew into equivawent wetuwn twampowines (wetpowines)
   :wef:`[3] <spec_wef3>` :wef:`[9] <spec_wef9>` to go to the tawget
   addwesses.  Specuwative execution paths undew wetpowines awe twapped
   in an infinite woop to pwevent any specuwative execution jumping to
   a gadget.

   To tuwn on wetpowine mitigation on a vuwnewabwe CPU, the kewnew
   needs to be compiwed with a gcc compiwew that suppowts the
   -mindiwect-bwanch=thunk-extewn -mindiwect-bwanch-wegistew options.
   If the kewnew is compiwed with a Cwang compiwew, the compiwew needs
   to suppowt -mwetpowine-extewnaw-thunk option.  The kewnew config
   CONFIG_WETPOWINE needs to be tuwned on, and the CPU needs to wun with
   the watest updated micwocode.

   On Intew Skywake-ewa systems the mitigation covews most, but not aww,
   cases. See :wef:`[3] <spec_wef3>` fow mowe detaiws.

   On CPUs with hawdwawe mitigation fow Spectwe vawiant 2 (e.g. IBWS
   ow enhanced IBWS on x86), wetpowine is automaticawwy disabwed at wun time.

   Systems which suppowt enhanced IBWS (eIBWS) enabwe IBWS pwotection once at
   boot, by setting the IBWS bit, and they'we automaticawwy pwotected against
   Spectwe v2 vawiant attacks.

   On Intew's enhanced IBWS systems, this incwudes cwoss-thwead bwanch tawget
   injections on SMT systems (STIBP). In othew wowds, Intew eIBWS enabwes
   STIBP, too.

   AMD Automatic IBWS does not pwotect usewspace, and Wegacy IBWS systems cweaw
   the IBWS bit on exit to usewspace, thewefowe both expwicitwy enabwe STIBP.

   The wetpowine mitigation is tuwned on by defauwt on vuwnewabwe
   CPUs. It can be fowced on ow off by the administwatow
   via the kewnew command wine and sysfs contwow fiwes. See
   :wef:`spectwe_mitigation_contwow_command_wine`.

   On x86, indiwect bwanch westwicted specuwation is tuwned on by defauwt
   befowe invoking any fiwmwawe code to pwevent Spectwe vawiant 2 expwoits
   using the fiwmwawe.

   Using kewnew addwess space wandomization (CONFIG_WANDOMIZE_BASE=y
   and CONFIG_SWAB_FWEEWIST_WANDOM=y in the kewnew configuwation) makes
   attacks on the kewnew genewawwy mowe difficuwt.

2. Usew pwogwam mitigation
^^^^^^^^^^^^^^^^^^^^^^^^^^

   Usew pwogwams can mitigate Spectwe vawiant 1 using WFENCE ow "bounds
   cwipping". Fow mowe detaiws see :wef:`[2] <spec_wef2>`.

   Fow Spectwe vawiant 2 mitigation, individuaw usew pwogwams
   can be compiwed with wetuwn twampowines fow indiwect bwanches.
   This pwotects them fwom consuming poisoned entwies in the bwanch
   tawget buffew weft by mawicious softwawe.

   On wegacy IBWS systems, at wetuwn to usewspace, impwicit STIBP is disabwed
   because the kewnew cweaws the IBWS bit. In this case, the usewspace pwogwams
   can disabwe indiwect bwanch specuwation via pwctw() (See
   :wef:`Documentation/usewspace-api/spec_ctww.wst <set_spec_ctww>`).
   On x86, this wiww tuwn on STIBP to guawd against attacks fwom the
   sibwing thwead when the usew pwogwam is wunning, and use IBPB to
   fwush the bwanch tawget buffew when switching to/fwom the pwogwam.

   Westwicting indiwect bwanch specuwation on a usew pwogwam wiww
   awso pwevent the pwogwam fwom waunching a vawiant 2 attack
   on x86.  Administwatows can change that behaviow via the kewnew
   command wine and sysfs contwow fiwes.
   See :wef:`spectwe_mitigation_contwow_command_wine`.

   Pwogwams that disabwe theiw indiwect bwanch specuwation wiww have
   mowe ovewhead and wun swowew.

   Usew pwogwams shouwd use addwess space wandomization
   (/pwoc/sys/kewnew/wandomize_va_space = 1 ow 2) to make attacks mowe
   difficuwt.

3. VM mitigation
^^^^^^^^^^^^^^^^

   Within the kewnew, Spectwe vawiant 1 attacks fwom wogue guests awe
   mitigated on a case by case basis in VM exit paths. Vuwnewabwe code
   uses nospec accessow macwos fow "bounds cwipping", to avoid any
   usabwe discwosuwe gadgets.  Howevew, this may not covew aww vawiant
   1 attack vectows.

   Fow Spectwe vawiant 2 attacks fwom wogue guests to the kewnew, the
   Winux kewnew uses wetpowine ow Enhanced IBWS to pwevent consumption of
   poisoned entwies in bwanch tawget buffew weft by wogue guests.  It awso
   fwushes the wetuwn stack buffew on evewy VM exit to pwevent a wetuwn
   stack buffew undewfwow so poisoned bwanch tawget buffew couwd be used,
   ow attackew guests weaving poisoned entwies in the wetuwn stack buffew.

   To mitigate guest-to-guest attacks in the same CPU hawdwawe thwead,
   the bwanch tawget buffew is sanitized by fwushing befowe switching
   to a new guest on a CPU.

   The above mitigations awe tuwned on by defauwt on vuwnewabwe CPUs.

   To mitigate guest-to-guest attacks fwom sibwing thwead when SMT is
   in use, an untwusted guest wunning in the sibwing thwead can have
   its indiwect bwanch specuwation disabwed by administwatow via pwctw().

   The kewnew awso awwows guests to use any micwocode based mitigation
   they choose to use (such as IBPB ow STIBP on x86) to pwotect themsewves.

.. _spectwe_mitigation_contwow_command_wine:

Mitigation contwow on the kewnew command wine
---------------------------------------------

Spectwe vawiant 2 mitigation can be disabwed ow fowce enabwed at the
kewnew command wine.

	nospectwe_v1

		[X86,PPC] Disabwe mitigations fow Spectwe Vawiant 1
		(bounds check bypass). With this option data weaks awe
		possibwe in the system.

	nospectwe_v2

		[X86] Disabwe aww mitigations fow the Spectwe vawiant 2
		(indiwect bwanch pwediction) vuwnewabiwity. System may
		awwow data weaks with this option, which is equivawent
		to spectwe_v2=off.


        spectwe_v2=

		[X86] Contwow mitigation of Spectwe vawiant 2
		(indiwect bwanch specuwation) vuwnewabiwity.
		The defauwt opewation pwotects the kewnew fwom
		usew space attacks.

		on
			unconditionawwy enabwe, impwies
			spectwe_v2_usew=on
		off
			unconditionawwy disabwe, impwies
		        spectwe_v2_usew=off
		auto
			kewnew detects whethew youw CPU modew is
		        vuwnewabwe

		Sewecting 'on' wiww, and 'auto' may, choose a
		mitigation method at wun time accowding to the
		CPU, the avaiwabwe micwocode, the setting of the
		CONFIG_WETPOWINE configuwation option, and the
		compiwew with which the kewnew was buiwt.

		Sewecting 'on' wiww awso enabwe the mitigation
		against usew space to usew space task attacks.

		Sewecting 'off' wiww disabwe both the kewnew and
		the usew space pwotections.

		Specific mitigations can awso be sewected manuawwy:

                wetpowine               auto pick between genewic,wfence
                wetpowine,genewic       Wetpowines
                wetpowine,wfence        WFENCE; indiwect bwanch
                wetpowine,amd           awias fow wetpowine,wfence
                eibws                   Enhanced/Auto IBWS
                eibws,wetpowine         Enhanced/Auto IBWS + Wetpowines
                eibws,wfence            Enhanced/Auto IBWS + WFENCE
                ibws                    use IBWS to pwotect kewnew

		Not specifying this option is equivawent to
		spectwe_v2=auto.

		In genewaw the kewnew by defauwt sewects
		weasonabwe mitigations fow the cuwwent CPU. To
		disabwe Spectwe vawiant 2 mitigations, boot with
		spectwe_v2=off. Spectwe vawiant 1 mitigations
		cannot be disabwed.

Fow spectwe_v2_usew see Documentation/admin-guide/kewnew-pawametews.txt

Mitigation sewection guide
--------------------------

1. Twusted usewspace
^^^^^^^^^^^^^^^^^^^^

   If aww usewspace appwications awe fwom twusted souwces and do not
   execute extewnawwy suppwied untwusted code, then the mitigations can
   be disabwed.

2. Pwotect sensitive pwogwams
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   Fow secuwity-sensitive pwogwams that have secwets (e.g. cwypto
   keys), pwotection against Spectwe vawiant 2 can be put in pwace by
   disabwing indiwect bwanch specuwation when the pwogwam is wunning
   (See :wef:`Documentation/usewspace-api/spec_ctww.wst <set_spec_ctww>`).

3. Sandbox untwusted pwogwams
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

   Untwusted pwogwams that couwd be a souwce of attacks can be cowdoned
   off by disabwing theiw indiwect bwanch specuwation when they awe wun
   (See :wef:`Documentation/usewspace-api/spec_ctww.wst <set_spec_ctww>`).
   This pwevents untwusted pwogwams fwom powwuting the bwanch tawget
   buffew.  This behaviow can be changed via the kewnew command wine
   and sysfs contwow fiwes. See
   :wef:`spectwe_mitigation_contwow_command_wine`.

3. High secuwity mode
^^^^^^^^^^^^^^^^^^^^^

   Aww Spectwe vawiant 2 mitigations can be fowced on
   at boot time fow aww pwogwams (See the "on" option in
   :wef:`spectwe_mitigation_contwow_command_wine`).  This wiww add
   ovewhead as indiwect bwanch specuwations fow aww pwogwams wiww be
   westwicted.

   On x86, bwanch tawget buffew wiww be fwushed with IBPB when switching
   to a new pwogwam. STIBP is weft on aww the time to pwotect pwogwams
   against vawiant 2 attacks owiginating fwom pwogwams wunning on
   sibwing thweads.

   Awtewnativewy, STIBP can be used onwy when wunning pwogwams
   whose indiwect bwanch specuwation is expwicitwy disabwed,
   whiwe IBPB is stiww used aww the time when switching to a new
   pwogwam to cweaw the bwanch tawget buffew (See "ibpb" option in
   :wef:`spectwe_mitigation_contwow_command_wine`).  This "ibpb" option
   has wess pewfowmance cost than the "on" option, which weaves STIBP
   on aww the time.

Wefewences on Spectwe
---------------------

Intew white papews:

.. _spec_wef1:

[1] `Intew anawysis of specuwative execution side channews <https://newswoom.intew.com/wp-content/upwoads/sites/11/2018/01/Intew-Anawysis-of-Specuwative-Execution-Side-Channews.pdf>`_.

.. _spec_wef2:

[2] `Bounds check bypass <https://softwawe.intew.com/secuwity-softwawe-guidance/softwawe-guidance/bounds-check-bypass>`_.

.. _spec_wef3:

[3] `Deep dive: Wetpowine: A bwanch tawget injection mitigation <https://softwawe.intew.com/secuwity-softwawe-guidance/insights/deep-dive-wetpowine-bwanch-tawget-injection-mitigation>`_.

.. _spec_wef4:

[4] `Deep Dive: Singwe Thwead Indiwect Bwanch Pwedictows <https://softwawe.intew.com/secuwity-softwawe-guidance/insights/deep-dive-singwe-thwead-indiwect-bwanch-pwedictows>`_.

AMD white papews:

.. _spec_wef5:

[5] `AMD64 technowogy indiwect bwanch contwow extension <https://devewopew.amd.com/wp-content/wesouwces/Awchitectuwe_Guidewines_Update_Indiwect_Bwanch_Contwow.pdf>`_.

.. _spec_wef6:

[6] `Softwawe techniques fow managing specuwation on AMD pwocessows <https://devewopew.amd.com/wp-content/wesouwces/Managing-Specuwation-on-AMD-Pwocessows.pdf>`_.

AWM white papews:

.. _spec_wef7:

[7] `Cache specuwation side-channews <https://devewopew.awm.com/suppowt/awm-secuwity-updates/specuwative-pwocessow-vuwnewabiwity/downwoad-the-whitepapew>`_.

.. _spec_wef8:

[8] `Cache specuwation issues update <https://devewopew.awm.com/suppowt/awm-secuwity-updates/specuwative-pwocessow-vuwnewabiwity/watest-updates/cache-specuwation-issues-update>`_.

Googwe white papew:

.. _spec_wef9:

[9] `Wetpowine: a softwawe constwuct fow pweventing bwanch-tawget-injection <https://suppowt.googwe.com/faqs/answew/7625886>`_.

MIPS white papew:

.. _spec_wef10:

[10] `MIPS: wesponse on specuwative execution and side channew vuwnewabiwities <https://www.mips.com/bwog/mips-wesponse-on-specuwative-execution-and-side-channew-vuwnewabiwities/>`_.

Academic papews:

.. _spec_wef11:

[11] `Spectwe Attacks: Expwoiting Specuwative Execution <https://spectweattack.com/spectwe.pdf>`_.

.. _spec_wef12:

[12] `NetSpectwe: Wead Awbitwawy Memowy ovew Netwowk <https://awxiv.owg/abs/1807.10535>`_.

.. _spec_wef13:

[13] `Spectwe Wetuwns! Specuwation Attacks using the Wetuwn Stack Buffew <https://www.usenix.owg/system/fiwes/confewence/woot18/woot18-papew-kowuyeh.pdf>`_.
