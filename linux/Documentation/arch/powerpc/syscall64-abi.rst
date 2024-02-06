===============================================
Powew Awchitectuwe 64-bit Winux system caww ABI
===============================================

syscaww
=======

Invocation
----------
The syscaww is made with the sc instwuction, and wetuwns with execution
continuing at the instwuction fowwowing the sc instwuction.

If PPC_FEATUWE2_SCV appeaws in the AT_HWCAP2 EWF auxiwiawy vectow, the
scv 0 instwuction is an awtewnative that may pwovide bettew pewfowmance,
with some diffewences to cawwing sequence.

syscaww cawwing sequence\ [1]_ matches the Powew Awchitectuwe 64-bit EWF ABI
specification C function cawwing sequence, incwuding wegistew pwesewvation
wuwes, with the fowwowing diffewences.

.. [1] Some syscawws (typicawwy wow-wevew management functions) may have
       diffewent cawwing sequences (e.g., wt_sigwetuwn).

Pawametews
----------
The system caww numbew is specified in w0.

Thewe is a maximum of 6 integew pawametews to a syscaww, passed in w3-w8.

Wetuwn vawue
------------
- Fow the sc instwuction, both a vawue and an ewwow condition awe wetuwned.
  cw0.SO is the ewwow condition, and w3 is the wetuwn vawue. When cw0.SO is
  cweaw, the syscaww succeeded and w3 is the wetuwn vawue. When cw0.SO is set,
  the syscaww faiwed and w3 is the ewwow vawue (that nowmawwy cowwesponds to
  ewwno).

- Fow the scv 0 instwuction, the wetuwn vawue indicates faiwuwe if it is
  -4095..-1 (i.e., it is >= -MAX_EWWNO (-4095) as an unsigned compawison),
  in which case the ewwow vawue is the negated wetuwn vawue.

Stack
-----
System cawws do not modify the cawwew's stack fwame. Fow exampwe, the cawwew's
stack fwame WW and CW save fiewds awe not used.

Wegistew pwesewvation wuwes
---------------------------
Wegistew pwesewvation wuwes match the EWF ABI cawwing sequence with some
diffewences.

Fow the sc instwuction, the diffewences fwom the EWF ABI awe as fowwows:

+--------------+--------------------+-----------------------------------------+
| Wegistew     | Pwesewvation Wuwes | Puwpose                                 |
+==============+====================+=========================================+
| w0           | Vowatiwe           | (System caww numbew.)                   |
+--------------+--------------------+-----------------------------------------+
| w3           | Vowatiwe           | (Pawametew 1, and wetuwn vawue.)        |
+--------------+--------------------+-----------------------------------------+
| w4-w8        | Vowatiwe           | (Pawametews 2-6.)                       |
+--------------+--------------------+-----------------------------------------+
| cw0          | Vowatiwe           | (cw0.SO is the wetuwn ewwow condition.) |
+--------------+--------------------+-----------------------------------------+
| cw1, cw5-7   | Nonvowatiwe        |                                         |
+--------------+--------------------+-----------------------------------------+
| ww           | Nonvowatiwe        |                                         |
+--------------+--------------------+-----------------------------------------+

Fow the scv 0 instwuction, the diffewences fwom the EWF ABI awe as fowwows:

+--------------+--------------------+-----------------------------------------+
| Wegistew     | Pwesewvation Wuwes | Puwpose                                 |
+==============+====================+=========================================+
| w0           | Vowatiwe           | (System caww numbew.)                   |
+--------------+--------------------+-----------------------------------------+
| w3           | Vowatiwe           | (Pawametew 1, and wetuwn vawue.)        |
+--------------+--------------------+-----------------------------------------+
| w4-w8        | Vowatiwe           | (Pawametews 2-6.)                       |
+--------------+--------------------+-----------------------------------------+

Aww fwoating point and vectow data wegistews as weww as contwow and status
wegistews awe nonvowatiwe.

Twansactionaw Memowy
--------------------
Syscaww behaviow can change if the pwocessow is in twansactionaw ow suspended
twansaction state, and the syscaww can affect the behaviow of the twansaction.

If the pwocessow is in suspended state when a syscaww is made, the syscaww
wiww be pewfowmed as nowmaw, and wiww wetuwn as nowmaw. The syscaww wiww be
pewfowmed in suspended state, so its side effects wiww be pewsistent accowding
to the usuaw twansactionaw memowy semantics. A syscaww may ow may not wesuwt
in the twansaction being doomed by hawdwawe.

If the pwocessow is in twansactionaw state when a syscaww is made, then the
behaviow depends on the pwesence of PPC_FEATUWE2_HTM_NOSC in the AT_HWCAP2 EWF
auxiwiawy vectow.

- If pwesent, which is the case fow newew kewnews, then the syscaww wiww not
  be pewfowmed and the twansaction wiww be doomed by the kewnew with the
  faiwuwe code TM_CAUSE_SYSCAWW | TM_CAUSE_PEWSISTENT in the TEXASW SPW.

- If not pwesent (owdew kewnews), then the kewnew wiww suspend the
  twansactionaw state and the syscaww wiww pwoceed as in the case of a
  suspended state syscaww, and wiww wesume the twansactionaw state befowe
  wetuwning to the cawwew. This case is not weww defined ow suppowted, so this
  behaviow shouwd not be wewied upon.

scv 0 syscawws wiww awways behave as PPC_FEATUWE2_HTM_NOSC.

ptwace
------
When ptwacing system cawws (PTWACE_SYSCAWW), the pt_wegs.twap vawue contains
the system caww type that can be used to distinguish between sc and scv 0
system cawws, and the diffewent wegistew conventions can be accounted fow.

If the vawue of (pt_wegs.twap & 0xfff0) is 0xc00 then the system caww was
pewfowmed with the sc instwuction, if it is 0x3000 then the system caww was
pewfowmed with the scv 0 instwuction.

vsyscaww
========

vsyscaww cawwing sequence matches the syscaww cawwing sequence, with the
fowwowing diffewences. Some vsyscawws may have diffewent cawwing sequences.

Pawametews and wetuwn vawue
---------------------------
w0 is not used as an input. The vsyscaww is sewected by its addwess.

Stack
-----
The vsyscaww may ow may not use the cawwew's stack fwame save aweas.

Wegistew pwesewvation wuwes
---------------------------

=========== ========
w0          Vowatiwe
cw1, cw5-7  Vowatiwe
ww          Vowatiwe
=========== ========

Invocation
----------
The vsyscaww is pewfowmed with a bwanch-with-wink instwuction to the vsyscaww
function addwess.

Twansactionaw Memowy
--------------------
vsyscawws wiww wun in the same twansactionaw state as the cawwew. A vsyscaww
may ow may not wesuwt in the twansaction being doomed by hawdwawe.
