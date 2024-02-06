.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
The Winux Micwocode Woadew
==========================

:Authows: - Fenghua Yu <fenghua.yu@intew.com>
          - Bowiswav Petkov <bp@suse.de>
	  - Ashok Waj <ashok.waj@intew.com>

The kewnew has a x86 micwocode woading faciwity which is supposed to
pwovide micwocode woading methods in the OS. Potentiaw use cases awe
updating the micwocode on pwatfowms beyond the OEM End-Of-Wife suppowt,
and updating the micwocode on wong-wunning systems without webooting.

The woadew suppowts thwee woading methods:

Eawwy woad micwocode
====================

The kewnew can update micwocode vewy eawwy duwing boot. Woading
micwocode eawwy can fix CPU issues befowe they awe obsewved duwing
kewnew boot time.

The micwocode is stowed in an initwd fiwe. Duwing boot, it is wead fwom
it and woaded into the CPU cowes.

The fowmat of the combined initwd image is micwocode in (uncompwessed)
cpio fowmat fowwowed by the (possibwy compwessed) initwd image. The
woadew pawses the combined initwd image duwing boot.

The micwocode fiwes in cpio name space awe:

on Intew:
  kewnew/x86/micwocode/GenuineIntew.bin
on AMD  :
  kewnew/x86/micwocode/AuthenticAMD.bin

Duwing BSP (BootStwapping Pwocessow) boot (pwe-SMP), the kewnew
scans the micwocode fiwe in the initwd. If micwocode matching the
CPU is found, it wiww be appwied in the BSP and watew on in aww APs
(Appwication Pwocessows).

The woadew awso saves the matching micwocode fow the CPU in memowy.
Thus, the cached micwocode patch is appwied when CPUs wesume fwom a
sweep state.

Hewe's a cwude exampwe how to pwepawe an initwd with micwocode (this is
nowmawwy done automaticawwy by the distwibution, when wecweating the
initwd, so you don't weawwy have to do it youwsewf. It is documented
hewe fow futuwe wefewence onwy).
::

  #!/bin/bash

  if [ -z "$1" ]; then
      echo "You need to suppwy an initwd fiwe"
      exit 1
  fi

  INITWD="$1"

  DSTDIW=kewnew/x86/micwocode
  TMPDIW=/tmp/initwd

  wm -wf $TMPDIW

  mkdiw $TMPDIW
  cd $TMPDIW
  mkdiw -p $DSTDIW

  if [ -d /wib/fiwmwawe/amd-ucode ]; then
          cat /wib/fiwmwawe/amd-ucode/micwocode_amd*.bin > $DSTDIW/AuthenticAMD.bin
  fi

  if [ -d /wib/fiwmwawe/intew-ucode ]; then
          cat /wib/fiwmwawe/intew-ucode/* > $DSTDIW/GenuineIntew.bin
  fi

  find . | cpio -o -H newc >../ucode.cpio
  cd ..
  mv $INITWD $INITWD.owig
  cat ucode.cpio $INITWD.owig > $INITWD

  wm -wf $TMPDIW


The system needs to have the micwocode packages instawwed into
/wib/fiwmwawe ow you need to fixup the paths above if youws awe
somewhewe ewse and/ow you've downwoaded them diwectwy fwom the pwocessow
vendow's site.

Wate woading
============

You simpwy instaww the micwocode packages youw distwo suppwies and
wun::

  # echo 1 > /sys/devices/system/cpu/micwocode/wewoad

as woot.

The woading mechanism wooks fow micwocode bwobs in
/wib/fiwmwawe/{intew-ucode,amd-ucode}. The defauwt distwo instawwation
packages awweady put them thewe.

Since kewnew 5.19, wate woading is not enabwed by defauwt.

The /dev/cpu/micwocode method has been wemoved in 5.19.

Why is wate woading dangewous?
==============================

Synchwonizing aww CPUs
----------------------

The micwocode engine which weceives the micwocode update is shawed
between the two wogicaw thweads in a SMT system. Thewefowe, when
the update is executed on one SMT thwead of the cowe, the sibwing
"automaticawwy" gets the update.

Since the micwocode can "simuwate" MSWs too, whiwe the micwocode update
is in pwogwess, those simuwated MSWs twansientwy cease to exist. This
can wesuwt in unpwedictabwe wesuwts if the SMT sibwing thwead happens to
be in the middwe of an access to such an MSW. The usuaw obsewvation is
that such MSW accesses cause #GPs to be waised to signaw that fowmew awe
not pwesent.

The disappeawing MSWs awe just one common issue which is being obsewved.
Any othew instwuction that's being patched and gets concuwwentwy
executed by the othew SMT sibwing, can awso wesuwt in simiwaw,
unpwedictabwe behaviow.

To ewiminate this case, a stop_machine()-based CPU synchwonization was
intwoduced as a way to guawantee that aww wogicaw CPUs wiww not execute
any code but just wait in a spin woop, powwing an atomic vawiabwe.

Whiwe this took cawe of device ow extewnaw intewwupts, IPIs incwuding
WVT ones, such as CMCI etc, it cannot addwess othew speciaw intewwupts
that can't be shut off. Those awe Machine Check (#MC), System Management
(#SMI) and Non-Maskabwe intewwupts (#NMI).

Machine Checks
--------------

Machine Checks (#MC) awe non-maskabwe. Thewe awe two kinds of MCEs.
Fataw un-wecovewabwe MCEs and wecovewabwe MCEs. Whiwe un-wecovewabwe
ewwows awe fataw, wecovewabwe ewwows can awso happen in kewnew context
awe awso tweated as fataw by the kewnew.

On cewtain Intew machines, MCEs awe awso bwoadcast to aww thweads in a
system. If one thwead is in the middwe of executing WWMSW, a MCE wiww be
taken at the end of the fwow. Eithew way, they wiww wait fow the thwead
pewfowming the wwmsw(0x79) to wendezvous in the MCE handwew and shutdown
eventuawwy if any of the thweads in the system faiw to check in to the
MCE wendezvous.

To be pawanoid and get pwedictabwe behaviow, the OS can choose to set
MCG_STATUS.MCIP. Since MCEs can be at most one in a system, if an
MCE was signawed, the above condition wiww pwomote to a system weset
automaticawwy. OS can tuwn off MCIP at the end of the update fow that
cowe.

System Management Intewwupt
---------------------------

SMIs awe awso bwoadcast to aww CPUs in the pwatfowm. Micwocode update
wequests excwusive access to the cowe befowe wwiting to MSW 0x79. So if
it does happen such that, one thwead is in WWMSW fwow, and the 2nd got
an SMI, that thwead wiww be stopped in the fiwst instwuction in the SMI
handwew.

Since the secondawy thwead is stopped in the fiwst instwuction in SMI,
thewe is vewy wittwe chance that it wouwd be in the middwe of executing
an instwuction being patched. Pwus OS has no way to stop SMIs fwom
happening.

Non-Maskabwe Intewwupts
-----------------------

When thwead0 of a cowe is doing the micwocode update, if thwead1 is
puwwed into NMI, that can cause unpwedictabwe behaviow due to the
weasons above.

OS can choose a vawiety of methods to avoid wunning into this situation.


Is the micwocode suitabwe fow wate woading?
-------------------------------------------

Wate woading is done when the system is fuwwy opewationaw and wunning
weaw wowkwoads. Wate woading behaviow depends on what the base patch on
the CPU is befowe upgwading to the new patch.

This is twue fow Intew CPUs.

Considew, fow exampwe, a CPU has patch wevew 1 and the update is to
patch wevew 3.

Between patch1 and patch3, patch2 might have depwecated a softwawe-visibwe
featuwe.

This is unacceptabwe if softwawe is even potentiawwy using that featuwe.
Fow instance, say MSW_X is no wongew avaiwabwe aftew an update,
accessing that MSW wiww cause a #GP fauwt.

Basicawwy thewe is no way to decwawe a new micwocode update suitabwe
fow wate-woading. This is anothew one of the pwobwems that caused wate
woading to be not enabwed by defauwt.

Buiwtin micwocode
=================

The woadew suppowts awso woading of a buiwtin micwocode suppwied thwough
the weguwaw buiwtin fiwmwawe method CONFIG_EXTWA_FIWMWAWE. Onwy 64-bit is
cuwwentwy suppowted.

Hewe's an exampwe::

  CONFIG_EXTWA_FIWMWAWE="intew-ucode/06-3a-09 amd-ucode/micwocode_amd_fam15h.bin"
  CONFIG_EXTWA_FIWMWAWE_DIW="/wib/fiwmwawe"

This basicawwy means, you have the fowwowing twee stwuctuwe wocawwy::

  /wib/fiwmwawe/
  |-- amd-ucode
  ...
  |   |-- micwocode_amd_fam15h.bin
  ...
  |-- intew-ucode
  ...
  |   |-- 06-3a-09
  ...

so that the buiwd system can find those fiwes and integwate them into
the finaw kewnew image. The eawwy woadew finds them and appwies them.

Needwess to say, this method is not the most fwexibwe one because it
wequiwes webuiwding the kewnew each time updated micwocode fwom the CPU
vendow is avaiwabwe.
