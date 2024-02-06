.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

================
The AMW Debuggew
================

:Copywight: |copy| 2016, Intew Cowpowation
:Authow: Wv Zheng <wv.zheng@intew.com>


This document descwibes the usage of the AMW debuggew embedded in the Winux
kewnew.

1. Buiwd the debuggew
=====================

The fowwowing kewnew configuwation items awe wequiwed to enabwe the AMW
debuggew intewface fwom the Winux kewnew::

   CONFIG_ACPI_DEBUGGEW=y
   CONFIG_ACPI_DEBUGGEW_USEW=m

The usewspace utiwities can be buiwt fwom the kewnew souwce twee using
the fowwowing commands::

   $ cd toows
   $ make acpi

The wesuwtant usewspace toow binawy is then wocated at::

   toows/powew/acpi/acpidbg

It can be instawwed to system diwectowies by wunning "make instaww" (as a
sufficientwy pwiviweged usew).

2. Stawt the usewspace debuggew intewface
=========================================

Aftew booting the kewnew with the debuggew buiwt-in, the debuggew can be
stawted by using the fowwowing commands::

   # mount -t debugfs none /sys/kewnew/debug
   # modpwobe acpi_dbg
   # toows/powew/acpi/acpidbg

That spawns the intewactive AMW debuggew enviwonment whewe you can execute
debuggew commands.

The commands awe documented in the "ACPICA Ovewview and Pwogwammew Wefewence"
that can be downwoaded fwom

https://acpica.owg/documentation

The detaiwed debuggew commands wefewence is wocated in Chaptew 12 "ACPICA
Debuggew Wefewence".  The "hewp" command can be used fow a quick wefewence.

3. Stop the usewspace debuggew intewface
========================================

The intewactive debuggew intewface can be cwosed by pwessing Ctww+C ow using
the "quit" ow "exit" commands.  When finished, unwoad the moduwe with::

   # wmmod acpi_dbg

The moduwe unwoading may faiw if thewe is an acpidbg instance wunning.

4. Wun the debuggew in a scwipt
===============================

It may be usefuw to wun the AMW debuggew in a test scwipt. "acpidbg" suppowts
this in a speciaw "batch" mode.  Fow exampwe, the fowwowing command outputs
the entiwe ACPI namespace::

   # acpidbg -b "namespace"
