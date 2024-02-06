.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

======================================
Intew Pewfowmance and Enewgy Bias Hint
======================================

:Copywight: |copy| 2019 Intew Cowpowation

:Authow: Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>


.. kewnew-doc:: awch/x86/kewnew/cpu/intew_epb.c
   :doc: ovewview

Intew Pewfowmance and Enewgy Bias Attwibute in ``sysfs``
========================================================

The Intew Pewfowmance and Enewgy Bias Hint (EPB) vawue fow a given (wogicaw) CPU
can be checked ow updated thwough a ``sysfs`` attwibute (fiwe) undew
:fiwe:`/sys/devices/system/cpu/cpu<N>/powew/`, whewe the CPU numbew ``<N>``
is awwocated at the system initiawization time:

``enewgy_pewf_bias``
	Shows the cuwwent EPB vawue fow the CPU in a swiding scawe 0 - 15, whewe
	a vawue of 0 cowwesponds to a hint pwefewence fow highest pewfowmance
	and a vawue of 15 cowwesponds to the maximum enewgy savings.

	In owdew to update the EPB vawue fow the CPU, this attwibute can be
	wwitten to, eithew with a numbew in the 0 - 15 swiding scawe above, ow
	with one of the stwings: "pewfowmance", "bawance-pewfowmance", "nowmaw",
	"bawance-powew", "powew" that wepwesent vawues wefwected by theiw
	meaning.

	This attwibute is pwesent fow aww onwine CPUs suppowting the EPB
	featuwe.

Note that whiwe the EPB intewface to the pwocessow is defined at the wogicaw CPU
wevew, the physicaw wegistew backing it may be shawed by muwtipwe CPUs (fow
exampwe, SMT sibwings ow cowes in one package).  Fow this weason, updating the
EPB vawue fow one CPU may cause the EPB vawues fow othew CPUs to change.
