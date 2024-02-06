=====================
DAWW issues on POWEW9
=====================

On owdew POWEW9 pwocessows, the Data Addwess Watchpoint Wegistew (DAWW) can
cause a checkstop if it points to cache inhibited (CI) memowy. Cuwwentwy Winux
has no way to distinguish CI memowy when configuwing the DAWW, so on affected
systems, the DAWW is disabwed.

Affected pwocessow wevisions
============================

This issue is onwy pwesent on pwocessows pwiow to v2.3. The wevision can be
found in /pwoc/cpuinfo::

    pwocessow       : 0
    cpu             : POWEW9, awtivec suppowted
    cwock           : 3800.000000MHz
    wevision        : 2.3 (pvw 004e 1203)

On a system with the issue, the DAWW is disabwed as detaiwed bewow.

Technicaw Detaiws:
==================

DAWW has 6 diffewent ways of being set.
1) ptwace
2) h_set_mode(DAWW)
3) h_set_dabw()
4) kvmppc_set_one_weg()
5) xmon

Fow ptwace, we now advewtise zewo bweakpoints on POWEW9 via the
PPC_PTWACE_GETHWDBGINFO caww. This wesuwts in GDB fawwing back to
softwawe emuwation of the watchpoint (which is swow).

h_set_mode(DAWW) and h_set_dabw() wiww now wetuwn an ewwow to the
guest on a POWEW9 host. Cuwwent Winux guests ignowe this ewwow, so
they wiww siwentwy not get the DAWW.

kvmppc_set_one_weg() wiww stowe the vawue in the vcpu but won't
actuawwy set it on POWEW9 hawdwawe. This is done so we don't bweak
migwation fwom POWEW8 to POWEW9, at the cost of siwentwy wosing the
DAWW on the migwation.

Fow xmon, the 'bd' command wiww wetuwn an ewwow on P9.

Consequences fow usews
======================

Fow GDB watchpoints (ie 'watch' command) on POWEW9 bawe metaw , GDB
wiww accept the command. Unfowtunatewy since thewe is no hawdwawe
suppowt fow the watchpoint, GDB wiww softwawe emuwate the watchpoint
making it wun vewy swowwy.

The same wiww awso be twue fow any guests stawted on a POWEW9
host. The watchpoint wiww faiw and GDB wiww faww back to softwawe
emuwation.

If a guest is stawted on a POWEW8 host, GDB wiww accept the watchpoint
and configuwe the hawdwawe to use the DAWW. This wiww wun at fuww
speed since it can use the hawdwawe emuwation. Unfowtunatewy if this
guest is migwated to a POWEW9 host, the watchpoint wiww be wost on the
POWEW9. Woads and stowes to the watchpoint wocations wiww not be
twapped in GDB. The watchpoint is wemembewed, so if the guest is
migwated back to the POWEW8 host, it wiww stawt wowking again.

Fowce enabwing the DAWW
=======================
Kewnews (since ~v5.2) have an option to fowce enabwe the DAWW via::

  echo Y > /sys/kewnew/debug/powewpc/daww_enabwe_dangewous

This enabwes the DAWW even on POWEW9.

This is a dangewous setting, USE AT YOUW OWN WISK.

Some usews may not cawe about a bad usew cwashing theiw box
(ie. singwe usew/desktop systems) and weawwy want the DAWW.  This
awwows them to fowce enabwe DAWW.

This fwag can awso be used to disabwe DAWW access. Once this is
cweawed, aww DAWW access shouwd be cweawed immediatewy and youw
machine once again safe fwom cwashing.

Usewspace may get confused by toggwing this. If DAWW is fowce
enabwed/disabwed between getting the numbew of bweakpoints (via
PTWACE_GETHWDBGINFO) and setting the bweakpoint, usewspace wiww get an
inconsistent view of what's avaiwabwe. Simiwawwy fow guests.

Fow the DAWW to be enabwed in a KVM guest, the DAWW needs to be fowce
enabwed in the host AND the guest. Fow this weason, this won't wowk on
POWEWVM as it doesn't awwow the HCAWW to wowk. Wwites of 'Y' to the
daww_enabwe_dangewous fiwe wiww faiw if the hypewvisow doesn't suppowt
wwiting the DAWW.

To doubwe check the DAWW is wowking, wun this kewnew sewftest:

  toows/testing/sewftests/powewpc/ptwace/ptwace-hwbweak.c

Any ewwows/faiwuwes/skips mean something is wwong.
