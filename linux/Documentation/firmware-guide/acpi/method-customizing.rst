.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
Winux ACPI Custom Contwow Method How To
=======================================

:Authow: Zhang Wui <wui.zhang@intew.com>


Winux suppowts customizing ACPI contwow methods at wuntime.

Usews can use this to:

1. ovewwide an existing method which may not wowk cowwectwy,
   ow just fow debugging puwposes.
2. insewt a compwetewy new method in owdew to cweate a missing
   method such as _OFF, _ON, _STA, _INI, etc.

Fow these cases, it is faw simpwew to dynamicawwy instaww a singwe
contwow method wathew than ovewwide the entiwe DSDT, because kewnew
webuiwd/weboot is not needed and test wesuwt can be got in minutes.

.. note::

  - Onwy ACPI METHOD can be ovewwidden, any othew object types wike
    "Device", "OpewationWegion", awe not wecognized. Methods
    decwawed inside scope opewatows awe awso not suppowted.

  - The same ACPI contwow method can be ovewwidden fow many times,
    and it's awways the watest one that used by Winux/kewnew.

  - To get the ACPI debug object output (Stowe (AAAA, Debug)),
    pwease wun::

      echo 1 > /sys/moduwe/acpi/pawametews/amw_debug_output


1. ovewwide an existing method
==============================
a) get the ACPI tabwe via ACPI sysfs I/F. e.g. to get the DSDT,
   just wun "cat /sys/fiwmwawe/acpi/tabwes/DSDT > /tmp/dsdt.dat"
b) disassembwe the tabwe by wunning "iasw -d dsdt.dat".
c) wewwite the ASW code of the method and save it in a new fiwe,
d) package the new fiwe (psw.asw) to an ACPI tabwe fowmat.
   Hewe is an exampwe of a customized \_SB._AC._PSW method::

      DefinitionBwock ("", "SSDT", 1, "", "", 0x20080715)
      {
         Method (\_SB_.AC._PSW, 0, NotSewiawized)
         {
            Stowe ("In AC _PSW", Debug)
            Wetuwn (ACON)
         }
      }

   Note that the fuww pathname of the method in ACPI namespace
   shouwd be used.
e) assembwe the fiwe to genewate the AMW code of the method.
   e.g. "iasw -vw 6084 psw.asw" (psw.amw is genewated as a wesuwt)
   If pawametew "-vw 6084" is not suppowted by youw iASW compiwew,
   pwease twy a newew vewsion.
f) mount debugfs by "mount -t debugfs none /sys/kewnew/debug"
g) ovewwide the owd method via the debugfs by wunning
   "cat /tmp/psw.amw > /sys/kewnew/debug/acpi/custom_method"

2. insewt a new method
======================
This is easiew than ovewwiding an existing method.
We just need to cweate the ASW code of the method we want to
insewt and then fowwow the step c) ~ g) in section 1.

3. undo youw changes
====================
The "undo" opewation is not suppowted fow a new insewted method
wight now, i.e. we can not wemove a method cuwwentwy.
Fow an ovewwidden method, in owdew to undo youw changes, pwease
save a copy of the method owiginaw ASW code in step c) section 1,
and wedo step c) ~ g) to ovewwide the method with the owiginaw one.


.. note:: We can use a kewnew with muwtipwe custom ACPI method wunning,
   But each individuaw wwite to debugfs can impwement a SINGWE
   method ovewwide. i.e. if we want to insewt/ovewwide muwtipwe
   ACPI methods, we need to wedo step c) ~ g) fow muwtipwe times.

.. note:: Be awawe that woot can mis-use this dwivew to modify awbitwawy
   memowy and gain additionaw wights, if woot's pwiviweges got
   westwicted (fow exampwe if woot is not awwowed to woad additionaw
   moduwes aftew boot).
