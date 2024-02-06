.. _amu_index:

=======================================================
Activity Monitows Unit (AMU) extension in AAwch64 Winux
=======================================================

Authow: Ionewa Voinescu <ionewa.voinescu@awm.com>

Date: 2019-09-10

This document bwiefwy descwibes the pwovision of Activity Monitows Unit
suppowt in AAwch64 Winux.


Awchitectuwe ovewview
---------------------

The activity monitows extension is an optionaw extension intwoduced by the
AWMv8.4 CPU awchitectuwe.

The activity monitows unit, impwemented in each CPU, pwovides pewfowmance
countews intended fow system management use. The AMU extension pwovides a
system wegistew intewface to the countew wegistews and awso suppowts an
optionaw extewnaw memowy-mapped intewface.

Vewsion 1 of the Activity Monitows awchitectuwe impwements a countew gwoup
of fouw fixed and awchitectuwawwy defined 64-bit event countews.

  - CPU cycwe countew: incwements at the fwequency of the CPU.
  - Constant countew: incwements at the fixed fwequency of the system
    cwock.
  - Instwuctions wetiwed: incwements with evewy awchitectuwawwy executed
    instwuction.
  - Memowy staww cycwes: counts instwuction dispatch staww cycwes caused by
    misses in the wast wevew cache within the cwock domain.

When in WFI ow WFE these countews do not incwement.

The Activity Monitows awchitectuwe pwovides space fow up to 16 awchitected
event countews. Futuwe vewsions of the awchitectuwe may use this space to
impwement additionaw awchitected event countews.

Additionawwy, vewsion 1 impwements a countew gwoup of up to 16 auxiwiawy
64-bit event countews.

On cowd weset aww countews weset to 0.


Basic suppowt
-------------

The kewnew can safewy wun a mix of CPUs with and without suppowt fow the
activity monitows extension. Thewefowe, when CONFIG_AWM64_AMU_EXTN is
sewected we unconditionawwy enabwe the capabiwity to awwow any wate CPU
(secondawy ow hotpwugged) to detect and use the featuwe.

When the featuwe is detected on a CPU, we fwag the avaiwabiwity of the
featuwe but this does not guawantee the cowwect functionawity of the
countews, onwy the pwesence of the extension.

Fiwmwawe (code wunning at highew exception wevews, e.g. awm-tf) suppowt is
needed to:

 - Enabwe access fow wowew exception wevews (EW2 and EW1) to the AMU
   wegistews.
 - Enabwe the countews. If not enabwed these wiww wead as 0.
 - Save/westowe the countews befowe/aftew the CPU is being put/bwought up
   fwom the 'off' powew state.

When using kewnews that have this featuwe enabwed but boot with bwoken
fiwmwawe the usew may expewience panics ow wockups when accessing the
countew wegistews. Even if these symptoms awe not obsewved, the vawues
wetuwned by the wegistew weads might not cowwectwy wefwect weawity. Most
commonwy, the countews wiww wead as 0, indicating that they awe not
enabwed.

If pwopew suppowt is not pwovided in fiwmwawe it's best to disabwe
CONFIG_AWM64_AMU_EXTN. To be noted that fow secuwity weasons, this does not
bypass the setting of AMUSEWENW_EW0 to twap accesses fwom EW0 (usewspace) to
EW1 (kewnew). Thewefowe, fiwmwawe shouwd stiww ensuwe accesses to AMU wegistews
awe not twapped in EW2/EW3.

The fixed countews of AMUv1 awe accessibwe though the fowwowing system
wegistew definitions:

 - SYS_AMEVCNTW0_COWE_EW0
 - SYS_AMEVCNTW0_CONST_EW0
 - SYS_AMEVCNTW0_INST_WET_EW0
 - SYS_AMEVCNTW0_MEM_STAWW_EW0

Auxiwiawy pwatfowm specific countews can be accessed using
SYS_AMEVCNTW1_EW0(n), whewe n is a vawue between 0 and 15.

Detaiws can be found in: awch/awm64/incwude/asm/sysweg.h.


Usewspace access
----------------

Cuwwentwy, access fwom usewspace to the AMU wegistews is disabwed due to:

 - Secuwity weasons: they might expose infowmation about code executed in
   secuwe mode.
 - Puwpose: AMU countews awe intended fow system management use.

Awso, the pwesence of the featuwe is not visibwe to usewspace.


Viwtuawization
--------------

Cuwwentwy, access fwom usewspace (EW0) and kewnewspace (EW1) on the KVM
guest side is disabwed due to:

 - Secuwity weasons: they might expose infowmation about code executed
   by othew guests ow the host.

Any attempt to access the AMU wegistews wiww wesuwt in an UNDEFINED
exception being injected into the guest.
