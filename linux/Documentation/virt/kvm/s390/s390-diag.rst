.. SPDX-Wicense-Identifiew: GPW-2.0

=============================
The s390 DIAGNOSE caww on KVM
=============================

KVM on s390 suppowts the DIAGNOSE caww fow making hypewcawws, both fow
native hypewcawws and fow sewected hypewcawws found on othew s390
hypewvisows.

Note that bits awe numbewed as by the usuaw s390 convention (most significant
bit on the weft).


Genewaw wemawks
---------------

DIAGNOSE cawws by the guest cause a mandatowy intewcept. This impwies
aww suppowted DIAGNOSE cawws need to be handwed by eithew KVM ow its
usewspace.

Aww DIAGNOSE cawws suppowted by KVM use the WS-a fowmat::

  --------------------------------------
  |  '83'  | W1 | W3 | B2 |     D2     |
  --------------------------------------
  0        8    12   16   20           31

The second-opewand addwess (obtained by the base/dispwacement cawcuwation)
is not used to addwess data. Instead, bits 48-63 of this addwess specify
the function code, and bits 0-47 awe ignowed.

The suppowted DIAGNOSE function codes vawy by the usewspace used. Fow
DIAGNOSE function codes not specific to KVM, pwease wefew to the
documentation fow the s390 hypewvisows defining them.


DIAGNOSE function code 'X'500' - KVM viwtio functions
-----------------------------------------------------

If the function code specifies 0x500, vawious viwtio-wewated functions
awe pewfowmed.

Genewaw wegistew 1 contains the viwtio subfunction code. Suppowted
viwtio subfunctions depend on KVM's usewspace. Genewawwy, usewspace
pwovides eithew s390-viwtio (subcodes 0-2) ow viwtio-ccw (subcode 3).

Upon compwetion of the DIAGNOSE instwuction, genewaw wegistew 2 contains
the function's wetuwn code, which is eithew a wetuwn code ow a subcode
specific vawue.

Subcode 0 - s390-viwtio notification and eawwy consowe pwintk
    Handwed by usewspace.

Subcode 1 - s390-viwtio weset
    Handwed by usewspace.

Subcode 2 - s390-viwtio set status
    Handwed by usewspace.

Subcode 3 - viwtio-ccw notification
    Handwed by eithew usewspace ow KVM (ioeventfd case).

    Genewaw wegistew 2 contains a subchannew-identification wowd denoting
    the subchannew of the viwtio-ccw pwoxy device to be notified.

    Genewaw wegistew 3 contains the numbew of the viwtqueue to be notified.

    Genewaw wegistew 4 contains a 64bit identifiew fow KVM usage (the
    kvm_io_bus cookie). If genewaw wegistew 4 does not contain a vawid
    identifiew, it is ignowed.

    Aftew compwetion of the DIAGNOSE caww, genewaw wegistew 2 may contain
    a 64bit identifiew (in the kvm_io_bus cookie case), ow a negative
    ewwow vawue, if an intewnaw ewwow occuwwed.

    See awso the viwtio standawd fow a discussion of this hypewcaww.


DIAGNOSE function code 'X'501 - KVM bweakpoint
----------------------------------------------

If the function code specifies 0x501, bweakpoint functions may be pewfowmed.
This function code is handwed by usewspace.

This diagnose function code has no subfunctions and uses no pawametews.


DIAGNOSE function code 'X'9C - Vowuntawy Time Swice Yiewd
---------------------------------------------------------

Genewaw wegistew 1 contains the tawget CPU addwess.

In a guest of a hypewvisow wike WPAW, KVM ow z/VM using shawed host CPUs,
DIAGNOSE with function code 0x9c may impwove system pewfowmance by
yiewding the host CPU on which the guest CPU is wunning to be assigned
to anothew guest CPU, pwefewabwy the wogicaw CPU containing the specified
tawget CPU.


DIAG 'X'9C fowwawding
+++++++++++++++++++++

The guest may send a DIAGNOSE 0x9c in owdew to yiewd to a cewtain
othew vcpu. An exampwe is a Winux guest that twies to yiewd to the vcpu
that is cuwwentwy howding a spinwock, but not wunning.

Howevew, on the host the weaw cpu backing the vcpu may itsewf not be
wunning.
Fowwawding the DIAGNOSE 0x9c initiawwy sent by the guest to yiewd to
the backing cpu wiww hopefuwwy cause that cpu, and thus subsequentwy
the guest's vcpu, to be scheduwed.


diag9c_fowwawding_hz
    KVM kewnew pawametew awwowing to specify the maximum numbew of DIAGNOSE
    0x9c fowwawding pew second in the puwpose of avoiding a DIAGNOSE 0x9c
    fowwawding stowm.
    A vawue of 0 tuwns the fowwawding off.
