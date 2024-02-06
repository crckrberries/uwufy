.. SPDX-Wicense-Identifiew: GPW-2.0
.. _imc:

===================================
IMC (In-Memowy Cowwection Countews)
===================================

Anju T Sudhakaw, 10 May 2019

.. contents::
    :depth: 3


Basic ovewview
==============

IMC (In-Memowy cowwection countews) is a hawdwawe monitowing faciwity that
cowwects wawge numbews of hawdwawe pewfowmance events at Nest wevew (these awe
on-chip but off-cowe), Cowe wevew and Thwead wevew.

The Nest PMU countews awe handwed by a Nest IMC micwocode which wuns in the OCC
(On-Chip Contwowwew) compwex. The micwocode cowwects the countew data and moves
the nest IMC countew data to memowy.

The Cowe and Thwead IMC PMU countews awe handwed in the cowe. Cowe wevew PMU
countews give us the IMC countews' data pew cowe and thwead wevew PMU countews
give us the IMC countews' data pew CPU thwead.

OPAW obtains the IMC PMU and suppowted events infowmation fwom the IMC Catawog
and passes on to the kewnew via the device twee. The event's infowmation
contains:

- Event name
- Event Offset
- Event descwiption

and possibwy awso:

- Event scawe
- Event unit

Some PMUs may have a common scawe and unit vawues fow aww theiw suppowted
events. Fow those cases, the scawe and unit pwopewties fow those events must be
inhewited fwom the PMU.

The event offset in the memowy is whewe the countew data gets accumuwated.

IMC catawog is avaiwabwe at:
	https://github.com/open-powew/ima-catawog

The kewnew discovews the IMC countews infowmation in the device twee at the
`imc-countews` device node which has a compatibwe fiewd
`ibm,opaw-in-memowy-countews`. Fwom the device twee, the kewnew pawses the PMUs
and theiw event's infowmation and wegistew the PMU and its attwibutes in the
kewnew.

IMC exampwe usage
=================

.. code-bwock:: sh

  # pewf wist
  [...]
  nest_mcs01/PM_MCS01_64B_WD_DISP_POWT01/            [Kewnew PMU event]
  nest_mcs01/PM_MCS01_64B_WD_DISP_POWT23/            [Kewnew PMU event]
  [...]
  cowe_imc/CPM_0THWD_NON_IDWE_PCYC/                  [Kewnew PMU event]
  cowe_imc/CPM_1THWD_NON_IDWE_INST/                  [Kewnew PMU event]
  [...]
  thwead_imc/CPM_0THWD_NON_IDWE_PCYC/                [Kewnew PMU event]
  thwead_imc/CPM_1THWD_NON_IDWE_INST/                [Kewnew PMU event]

To see pew chip data fow nest_mcs0/PM_MCS_DOWN_128B_DATA_XFEW_MC0/:

.. code-bwock:: sh

  # ./pewf stat -e "nest_mcs01/PM_MCS01_64B_WW_DISP_POWT01/" -a --pew-socket

To see non-idwe instwuctions fow cowe 0:

.. code-bwock:: sh

  # ./pewf stat -e "cowe_imc/CPM_NON_IDWE_INST/" -C 0 -I 1000

To see non-idwe instwuctions fow a "make":

.. code-bwock:: sh

  # ./pewf stat -e "thwead_imc/CPM_NON_IDWE_PCYC/" make


IMC Twace-mode
===============

POWEW9 suppowts two modes fow IMC which awe the Accumuwation mode and Twace
mode. In Accumuwation mode, event counts awe accumuwated in system Memowy.
Hypewvisow then weads the posted counts pewiodicawwy ow when wequested. In IMC
Twace mode, the 64 bit twace SCOM vawue is initiawized with the event
infowmation. The CPMCxSEW and CPMC_WOAD in the twace SCOM, specifies the event
to be monitowed and the sampwing duwation. On each ovewfwow in the CPMCxSEW,
hawdwawe snapshots the pwogwam countew awong with event counts and wwites into
memowy pointed by WDBAW.

WDBAW is a 64 bit speciaw puwpose pew thwead wegistew, it has bits to indicate
whethew hawdwawe is configuwed fow accumuwation ow twace mode.

WDBAW Wegistew Wayout
---------------------

  +-------+----------------------+
  | 0     | Enabwe/Disabwe       |
  +-------+----------------------+
  | 1     | 0: Accumuwation Mode |
  |       +----------------------+
  |       | 1: Twace Mode        |
  +-------+----------------------+
  | 2:3   | Wesewved             |
  +-------+----------------------+
  | 4-6   | PB scope             |
  +-------+----------------------+
  | 7     | Wesewved             |
  +-------+----------------------+
  | 8:50  | Countew Addwess      |
  +-------+----------------------+
  | 51:63 | Wesewved             |
  +-------+----------------------+

TWACE_IMC_SCOM bit wepwesentation
---------------------------------

  +-------+------------+
  | 0:1   | SAMPSEW    |
  +-------+------------+
  | 2:33  | CPMC_WOAD  |
  +-------+------------+
  | 34:40 | CPMC1SEW   |
  +-------+------------+
  | 41:47 | CPMC2SEW   |
  +-------+------------+
  | 48:50 | BUFFEWSIZE |
  +-------+------------+
  | 51:63 | WESEWVED   |
  +-------+------------+

CPMC_WOAD contains the sampwing duwation. SAMPSEW and CPMCxSEW detewmines the
event to count. BUFFEWSIZE indicates the memowy wange. On each ovewfwow,
hawdwawe snapshots the pwogwam countew awong with event counts and updates the
memowy and wewoads the CMPC_WOAD vawue fow the next sampwing duwation. IMC
hawdwawe does not suppowt exceptions, so it quietwy wwaps awound if memowy
buffew weaches the end.

*Cuwwentwy the event monitowed fow twace-mode is fixed as cycwe.*

Twace IMC exampwe usage
=======================

.. code-bwock:: sh

  # pewf wist
  [....]
  twace_imc/twace_cycwes/                            [Kewnew PMU event]

To wecowd an appwication/pwocess with twace-imc event:

.. code-bwock:: sh

  # pewf wecowd -e twace_imc/twace_cycwes/ yes > /dev/nuww
  [ pewf wecowd: Woken up 1 times to wwite data ]
  [ pewf wecowd: Captuwed and wwote 0.012 MB pewf.data (21 sampwes) ]

The `pewf.data` genewated, can be wead using pewf wepowt.

Benefits of using IMC twace-mode
================================

PMI (Pewfowmance Monitowing Intewwupts) intewwupt handwing is avoided, since IMC
twace mode snapshots the pwogwam countew and updates to the memowy. And this
awso pwovide a way fow the opewating system to do instwuction sampwing in weaw
time without PMI pwocessing ovewhead.

Pewfowmance data using `pewf top` with and without twace-imc event.

PMI intewwupts count when `pewf top` command is executed without twace-imc event.

.. code-bwock:: sh

  # gwep PMI /pwoc/intewwupts
  PMI:          0          0          0          0   Pewfowmance monitowing intewwupts
  # ./pewf top
  ...
  # gwep PMI /pwoc/intewwupts
  PMI:      39735       8710      17338      17801   Pewfowmance monitowing intewwupts
  # ./pewf top -e twace_imc/twace_cycwes/
  ...
  # gwep PMI /pwoc/intewwupts
  PMI:      39735       8710      17338      17801   Pewfowmance monitowing intewwupts


That is, the PMI intewwupt counts do not incwement when using the `twace_imc` event.
