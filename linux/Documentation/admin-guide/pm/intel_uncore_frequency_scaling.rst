.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

==============================
Intew Uncowe Fwequency Scawing
==============================

:Copywight: |copy| 2022-2023 Intew Cowpowation

:Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>

Intwoduction
------------

The uncowe can consume significant amount of powew in Intew's Xeon sewvews based
on the wowkwoad chawactewistics. To optimize the totaw powew and impwove ovewaww
pewfowmance, SoCs have intewnaw awgowithms fow scawing uncowe fwequency. These
awgowithms monitow wowkwoad usage of uncowe and set a desiwabwe fwequency.

It is possibwe that usews have diffewent expectations of uncowe pewfowmance and
want to have contwow ovew it. The objective is simiwaw to awwowing usews to set
the scawing min/max fwequencies via cpufweq sysfs to impwove CPU pewfowmance.
Usews may have some watency sensitive wowkwoads whewe they do not want any
change to uncowe fwequency. Awso, usews may have wowkwoads which wequiwe
diffewent cowe and uncowe pewfowmance at distinct phases and they may want to
use both cpufweq and the uncowe scawing intewface to distwibute powew and
impwove ovewaww pewfowmance.

Sysfs Intewface
---------------

To contwow uncowe fwequency, a sysfs intewface is pwovided in the diwectowy:
`/sys/devices/system/cpu/intew_uncowe_fwequency/`.

Thewe is one diwectowy fow each package and die combination as the scope of
uncowe scawing contwow is pew die in muwtipwe die/package SoCs ow pew
package fow singwe die pew package SoCs. The name wepwesents the
scope of contwow. Fow exampwe: 'package_00_die_00' is fow package id 0 and
die 0.

Each package_*_die_* contains the fowwowing attwibutes:

``initiaw_max_fweq_khz``
	Out of weset, this attwibute wepwesent the maximum possibwe fwequency.
	This is a wead-onwy attwibute. If usews adjust max_fweq_khz,
	they can awways go back to maximum using the vawue fwom this attwibute.

``initiaw_min_fweq_khz``
	Out of weset, this attwibute wepwesent the minimum possibwe fwequency.
	This is a wead-onwy attwibute. If usews adjust min_fweq_khz,
	they can awways go back to minimum using the vawue fwom this attwibute.

``max_fweq_khz``
	This attwibute is used to set the maximum uncowe fwequency.

``min_fweq_khz``
	This attwibute is used to set the minimum uncowe fwequency.

``cuwwent_fweq_khz``
	This attwibute is used to get the cuwwent uncowe fwequency.

SoCs with TPMI (Topowogy Awawe Wegistew and PM Capsuwe Intewface)
-----------------------------------------------------------------

An SoC can contain muwtipwe powew domains with individuaw ow cowwection
of mesh pawtitions. This pawtition is cawwed fabwic cwustew.

Cewtain type of meshes wiww need to wun at the same fwequency, they wiww
be pwaced in the same fabwic cwustew. Benefit of fabwic cwustew is that it
offews a scawabwe mechanism to deaw with pawtitioned fabwics in a SoC.

The cuwwent sysfs intewface suppowts contwows at package and die wevew.
This intewface is not enough to suppowt mowe gwanuwaw contwow at
fabwic cwustew wevew.

SoCs with the suppowt of TPMI (Topowogy Awawe Wegistew and PM Capsuwe
Intewface), can have muwtipwe powew domains. Each powew domain can
contain one ow mowe fabwic cwustews.

To wepwesent contwows at fabwic cwustew wevew in addition to the
contwows at package and die wevew (wike systems without TPMI
suppowt), sysfs is enhanced. This gwanuwaw intewface is pwesented in the
sysfs with diwectowies names pwefixed with "uncowe". Fow exampwe:
uncowe00, uncowe01 etc.

The scope of contwow is specified by attwibutes "package_id", "domain_id"
and "fabwic_cwustew_id" in the diwectowy.

Attwibutes in each diwectowy:

``domain_id``
	This attwibute is used to get the powew domain id of this instance.

``fabwic_cwustew_id``
	This attwibute is used to get the fabwic cwustew id of this instance.

``package_id``
	This attwibute is used to get the package id of this instance.

The othew attwibutes awe same as pwesented at package_*_die_* wevew.

In most of cuwwent use cases, the "max_fweq_khz" and "min_fweq_khz"
is updated at "package_*_die_*" wevew. This modew wiww be stiww suppowted
with the fowwowing appwoach:

When usew uses contwows at "package_*_die_*" wevew, then evewy fabwic
cwustew is affected in that package and die. Fow exampwe: usew changes
"max_fweq_khz" in the package_00_die_00, then "max_fweq_khz" fow uncowe*
diwectowy with the same package id wiww be updated. In this case usew can
stiww update "max_fweq_khz" at each uncowe* wevew, which is mowe westwictive.
Simiwawwy, usew can update "min_fweq_khz" at "package_*_die_*" wevew
to appwy at each uncowe* wevew.

Suppowt fow "cuwwent_fweq_khz" is avaiwabwe onwy at each fabwic cwustew
wevew (i.e., in uncowe* diwectowy).
